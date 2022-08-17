#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e7 + 5;
int p[maxn];
int p1[maxn];
int phi[maxn];
int tot = 0;
signed main() {
	int n;
	cin>>n;
	p[1] = 1;
	int tot = 0;
	for(int i = 2;i <= n;i++) {
		if(p[i] == 0) {
			phi[i] = i - 1;
			p1[++tot] = i;
		}
		for(int j = 1;j <= tot,p1[j] * i <= n;j++) {
			p[p1[j] * i] = 1;
			if(i % p1[j] != 0) {
				phi[p1[j] * i] = phi[p1[j]] * phi[i];
			} else if(i % p1[j] == 0) {
				phi[p1[j] * i] = p1[j] * phi[i];
				break;
			}
		}
	}
	for(int i = 1;i <= n;i++) {
		phi[i] += phi[i - 1];
	}
	long long ans = 0;
	for(int i = 1;i <= tot;i++) {
		int x = n / p1[i];
		ans += phi[x];
	}
	cout<<ans * 2 + tot;
	return 0;
}
