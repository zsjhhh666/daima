#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 66;
bool is_prime(int u) {
	for(int i = 2;i <= sqrt(u);i++) {
		if(u % i == 0) {
			return false;
		}
	}
	return true;
}
int a[maxn];
int b[maxn];
int c[maxn];
int tot = 0;
signed main() {
	int n,m;
	cin>>n>>m;
	int ans = 0;
	for(int i = 1;i <= sqrt(n);i++) {
		if(n % i != 0) continue;
		if(is_prime(i) == true) {
			a[++tot] = i;
			while(n % i == 0) {
				n /= i;
				b[tot]++;
			}
		} else if(is_prime(n / i) == true) {
			a[++tot] = n / i;
			int x = n / i;
			while(n % x == 0) {
				n /= x;
				b[tot]++;
			}
		}
	}
	for(int i = 1;;i++) {
		for(int j = 1;j <= tot;j++) {
			c[j] += n / a[j];
			a[j] *= a[j];
			if(c[j] < b[j]) {
				cout<<i - 1<<endl;
				return 0;
			}
			c[j] -= b[j];
		}
	}
	return 0;
}
