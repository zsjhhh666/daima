#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 9;
const int maxn = 2e3 + 5;
int a[maxn];
int b[maxn];
int dp[maxn][maxn];
int k[maxn];
int l[maxn];
int g[maxn];
int p[maxn];
int main() {
	int n,m;
	cin>>n>>m;
	for(int i = 1;i <= n;i++) {
		cin>>a[i];
	}
	for(int i = 1;i <= n;i++) {
		cin>>b[i];
	}
	sort(a + 1,a + n + 1);
	sort(b + 1,b + n + 1);
	for(int i = 1;i <= n;i++) {
		int l = 1,r = n;
		while(l <= r) {
			int mid = (l + r) >> 1;
			if(b[mid] < a[i]) {
				k[i] = mid;
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
	}
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= m;j++) {
			dp[i][j] = (dp[i - 1][j] + (k[i] - j + 1) * dp[i - 1][j - 1] % mod) % mod;
		}
	}
	l[1] = 1;
	for(int i = 2;i <= n;i++) {
		l[i] = (i * l[i - 1]) % mod;
	}
	for(int i = 1;i <= n;i++) {
		g[i] = dp[n][i] * l[n - i];
	}
	p[1] = 1;
	for(int i=2;i<=n;i++) {
		p[i] = - ((mod / i) * p[mod % i] + p) % mod;
	}
	
	return 0;
}
