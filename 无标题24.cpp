#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 5;
const int mod = 998244353;
int a[maxn];
int b[maxn];
int dp[maxn];
int cnt1 = 0;
string n,s;
int m;
int dfs(int u,int p,int cnt,int h) {
	int ans = 0;
	//cout<<u<<' '<<p<<' '<<cnt<<' '<<h<<endl;
	if(u == n.size()) {
		if(h < m) return 0;
		else return 1;
	}
	if(u == 0) {
		int ans = 0;
		if(n[u] - '0' < s[cnt] - '0') {
			ans += (n[u] - '0' - 1) * dfs(u + 1,1,0,0);
			ans += 1 * dfs(u + 1,0,0,0);
			return ans;
		} else {
			if(p == 0 && n[u] - '0' == s[cnt] - '0') return dfs(u + 1,0,cnt + 1,h) + (n[u] - '0') * dfs(u + 1,1,0,h);
			else return dfs(u + 1,1,cnt + 1,h) + (n[u] - '0' - 1) * dfs(u + 1,1,0,h) + dfs(u + 1,p,0,h);
		}
	} else {
		if(n[u] - '0' < s[cnt] - '0' && p == 0) {
			return (n[u] - '0') * dfs(u + 1,1,0,h) + dfs(u + 1,p,0,h);
		}
		if(p == 0) {
			if(cnt == s.size() - 1) {
				if(n[u] - '0' == s[cnt] - '0') return dfs(u + 1,p,cnt1,h + 1) + (n[u] - '0') * dfs(u + 1,1,0,h);
				else return dfs(u + 1,1,cnt1,h + 1) + (n[u] - '0' - 1) * dfs(u + 1,1,0,h) + dfs(u + 1,p,0,h);
			}
			if(n[u] - '0' == s[cnt] - '0') return dfs(u + 1,p,cnt + 1,h) + (n[u] - '0') * dfs(u + 1,1,0,h);
			else return dfs(u + 1,1,cnt + 1,h) + (n[u] - '0' - 1) * dfs(u + 1,1,0,h) + dfs(u + 1,p,0,h);
		} else {
			if(cnt == s.size() - 1) {
				return dfs(u + 1,p,cnt1,h + 1) + 9 * dfs(u + 1,1,0,h);
			}
			return dfs(u + 1,p,cnt + 1,h) + 9 * dfs(u + 1,1,0,h);
		}
	}
}
int main() {
	cin>>m;
	cin>>n;
	cin>>s;
	int j1 = 0;
	for(int i = 1;i < s.size();i++) {
		int p = 1;
		for(int j = i;j < s.size();j++) {
			if(s[j] != s[j1]) {
				p = 0;
				break;
			}
			j1++;
		}
		if(p == 1) {
			cnt1 = i; 
		}
	}
	//cout<<cnt1<<endl;
	cout<<dfs(0,0,0,0);
	return 0;
}
