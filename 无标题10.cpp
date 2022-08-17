#include<bits/stdc++.h>
using namespace std;
int size1 = 0;
const int maxn = 1e5 + 5;
struct x {
	int l,r,val;
};
x tree[maxn * 40];
vector<int> p[maxn];
int tot = 0;
void pushup(int u) {
	tree[u].val = tree[tree[u].l].val + tree[tree[u].r].val;
}
void insert(int &new1,int old,int l,int r,int val) {
	new1 = ++tot;
	if(l == r) {
		tree[new1].val++;
		return;
	}
	tree[new1] = tree[old];
	int mid = (l + r) >> 1;
	if(val <= mid) insert(tree[new1].l,tree[old].l,l,mid,val);
	else insert(tree[new1].r,tree[old].r,mid + 1,r,val);
	pushup(new1);
}
int a[maxn];
int dp[maxn][19];
int dep[maxn];
int root[maxn];
void dfs(int u,int fa) {
	dp[u][0] = fa;
	dep[u] = dep[fa] + 1;
	insert(root[u],root[fa],1,size1,a[u]);
	for(int i = 0;i < p[u].size();i++) {
		int v = p[u][i];
		if(v == fa) continue;
		dfs(v,u);
	}
}
int get_lca(int x,int y) {
	if(dep[x] < dep[y]) swap(x,y);
	if(dep[x] != dep[y]) {
		for(int i = 18;i >= 0;i--) {
			if(dep[dp[x][i]] >= dep[y]) {
				x = dp[x][i];
			}
		}
	}
	if(x == y) {
		return x;
	}
	for(int i = 18;i >= 0;i--) {
		if(dp[x][i] != dp[y][i]) {
			x = dp[x][i];
			y = dp[y][i];
		}
	}
	return dp[x][0];
}
int query(int l,int r,int tot1,int tot2,int tot3,int k) {
	if(l == r) {
		return l;
	}
	int mid = (l + r) >> 1;
	if(tree[tot2].val + tree[tot3].val - 2 * tree[tot1].val >= k) {
		return query(l,mid,tree[tot1].l,tree[tot2].l,tree[tot3].l,k);
	} else {
		return query(mid + 1,r,tree[tot1].r,tree[tot2].r,tree[tot3].r,k - (tree[tot2].val + tree[tot3].val - 2 * tree[tot1].val));
	}
}
bool cmp(int s,int s1) {
	return a[s] < a[s1];
}
int b[maxn];
int main() {
	int n,m;
	cin>>n>>m;
	for(int i = 1;i <= n;i++) {
		cin>>a[i];
		b[i] = a[i];
	}
	int x,y;
	for(int i = 1;i < n;i++) {
		cin>>x>>y;
		p[x].push_back(y);
		p[y].push_back(x);
	}
	sort(b + 1,b + n + 1,cmp);
	size1 = unique(b + 1,b + n + 1) - b;
	for(int i = 1;i <= n;i++) {
		a[i] = lower_bound(b + 1,b + size1 + 1,a[i]) - b;
		cout<<a[i]<<endl;
	}
	dfs(1,0);
	for(int j = 1;j <= 18;j++) {
		for(int i = 1;i <= n;i++) {
			dp[i][j] = dp[dp[i][j - 1]][j - 1];
		}
	}
	int u,v,k;
	int last = 0;
	for(int i = 1;i <= m;i++) {
		cin>>u>>v>>k;
		u ^= last;
		int lca = get_lca(u,v);
		cout<<b[query(1,size1,root[lca],root[u],root[v],k)]<<endl;
		last = b[query(1,size1,root[lca],root[u],root[v],k)];
	}
	return 0;
}
