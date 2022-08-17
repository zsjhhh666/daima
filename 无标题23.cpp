#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e7 + 5;
long long phi[maxn + 2];
bool not_prime[maxn + 2];
int prime[maxn + 2];
int c[11][11];
int b[11];
int cnt = 0;
int k1(int a,int m) {
	int ans = 1;
	a %= mod;
	while(m) {
		if(m & 1) {
			ans = ans * a % mod;
		}
		a = (a * a) % mod;
		m >>= 1;
	}
	return ans;
}
void init() {
	for(int i = 0;i < 10;i++) {
		c[i][0] = c[i][i] = 1;
	}
	for(int i = 2;i < 10;i++) {
		for(int j = 1;j < i;j++) {
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
		}
	}
	b[0] = 1;
	for(int i = 1;i < 10;i++) {
		if(i == 9) {
			break;
		}
		int sum = 0;
		for(int j = 0;j < i;j++) {
			sum = (sum + (c[i + 1][j] * b[j]) % mod) % mod;
		}
		sum = (sum * k1(i + 1,mod - 2)) % mod;
		b[i] = (mod - sum) % mod;
		//cout<<b[i]<<endl;
	}
	not_prime[1] = true;
	phi[1] = 1;
	for(int i = 2;i <= maxn;i++) {
		//cout<<i<<endl;
		if(not_prime[i] == false) {
			prime[++cnt] = i;
			phi[i] = i - 1;
		}
		for(int j = 1;j <= cnt && i * prime[j] <= maxn;j++) {
			not_prime[i * prime[j]] = true;
			if(i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			} else {
				phi[i * prime[j]] = phi[i] * phi[prime[j]];
			}
		}
	}
	for(int i = 2;i <= maxn;i++) {
		phi[i] += phi[i - 1];
	}
}
int h(int n,int k) {
	int ans = 0;
	for(int i = 1;i <= k + 1;i++) {
		ans = (ans + ((c[k + 1][i] * b[k + 1 - i]) % mod * k1(n + 1,i)) % mod) % mod;
	}
	ans = ans * k1(k + 1,mod - 2) % mod;
	//cout<<ans<<endl;
	return ans;
}
int get_h(int l,int r,int k) {
	int suml = h(l,k);
	int sumr = h(r,k);
	//cout<<((sumr - suml) % mod + mod) % mod<<endl;
	return ((sumr - suml) % mod + mod) % mod;
}
int n;
unordered_map<int,long long> dp1;
long long get_phi(long long x) {
	if(x <= maxn) return phi[x];
	if(dp1[x]) return dp1[x];
	long long l,r;
	long long ans = 1ll * x * (x + 1) / 2;
	for(l = 2;l <= x;l = r + 1) {
		r = x / (x / l);
		ans -= (r - l + 1) * get_phi(x / l);
	}
	return dp1[x] = ans;
}
int get_ans(int n,int m) {
	int l = 0,r = 0;
	int ans = 0;
	for(int l = 1;l <= n;l = r + 1) {
		r = n / (n / l);
		ans = (ans + (get_phi(n / l) * get_h(l - 1,r,m) % mod)) % mod;
	}
	ans *= 2;
	ans = ((ans - h(n,m)) % mod + mod) % mod;
	return ans;
}
signed main() {
	init();
	int n,m;
	cin>>n>>m;
	cout<<get_ans(n,m)<<endl;
	return 0;
}
