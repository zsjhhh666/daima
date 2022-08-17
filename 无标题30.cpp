#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e5 + 5;
const int mod = 1e4 + 7;
int a[maxn];
vector<int> p[maxn];
int maxx = 0,ans = 0;
void dfs(int u,int fa) {
	int maxx1 = 0,sum = 0;
	for(int i = 0;i < p[u].size();i++) {
		int v = p[u][i];
		if(v == fa) continue;
		dfs(v,u);
		maxx1 = max(a[v],maxx1);
		sum = (sum + a[v]) % mod;
	}
	//cout<<maxx1<<' '<<a[fa] * sum<<endl;
	maxx = max(a[fa] * maxx1,maxx);
	ans = (ans + (a[fa] * sum * 2) % mod) % mod;
	int maxx2 = 0,cnt = 0;
	for(int i = 0;i < p[u].size();i++) {
		int v = p[u][i];
		if(v == fa) continue;
		ans = (ans + a[v] * (sum - a[v]) % mod) % mod;
		if(a[v] == maxx1) {
			cnt++;
			continue;
		}
		maxx2 = max(a[v],maxx2);
	}
	if(cnt == 1) {
		maxx = max(maxx1 * maxx2,maxx);
	} else {
		maxx = max(maxx1 * maxx1,maxx);
	}
}
signed main() {
	int n;
	cin>>n;
	int x,y;
	for(int i = 1;i < n;i++) {
		cin>>x>>y;
		p[x].push_back(y);
		p[y].push_back(x);
	}
	for(int i = 1;i <= n;i++) {
		cin>>a[i];
	}
	dfs(1,0);
	cout<<maxx<<' '<<ans % mod<<endl;
	return 0;
}
