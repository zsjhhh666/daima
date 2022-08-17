#include<bits/stdc++.h>
using namespace std;
const int maxn = 7000000;
long long phi[maxn + 2];
long long mu[maxn + 2];
bool not_prime[maxn + 2];
int prime[maxn + 2];
int cnt = 0;
void init() {
	not_prime[1] = true;
	mu[1] = 1;
	phi[1] = 1;
	for(int i = 2;i <= maxn;i++) {
		//cout<<i<<endl;
		if(not_prime[i] == false) {
			prime[++cnt] = i;
			phi[i] = i - 1;
			mu[i] = -1;
		}
		for(int j = 1;j <= cnt && i * prime[j] <= maxn;j++) {
			not_prime[i * prime[j]] = true;
			if(i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			} else {
				phi[i * prime[j]] = phi[i] * phi[prime[j]];
				mu[i * prime[j]] = -mu[i];
			}
		}
	}
	for(int i = 2;i <= maxn;i++) {
		phi[i] += phi[i - 1];
		mu[i] += mu[i - 1];
	}
}
int n;
unordered_map<int,int> dp;
unordered_map<int,long long> dp1;
long long get_mu(int x) {
	if(x <= maxn) return mu[x];
	if(dp[x]) return dp[x];
	long long l,r;
	long long ans = 1ll;
	for(l = 2;l <= x;l = r + 1) {
		r = x / (x / l);
		ans -= (r - l + 1) * get_mu(x / l);
	}
	return dp[x] = ans;
}
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
int main() {
	init();
	int t;
	cin>>t;
	while(t--) {
		cin>>n;
		printf("%lld %lld\n",get_phi(n),get_mu(n));
	}
	return 0;
}
