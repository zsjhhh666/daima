#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 5e5 + 5;
int a[maxn];
int s[maxn];
struct x {
	int l,r,val;
};
x tree[maxn];
int tot = 0;
void pushup(int u) {
	tree[u].val = tree[tree[u].l].val + tree[tree[u].r].val;
}
void insert(int &now,int old,int u,int k) {
	now = ++tot;
	tree[now] = tree[old];
	if(k <= 0) {
		tree[now].val++;
		return;
	}
	if(((u >> k) & 1LL) == 0) {
		insert(tree[now].l,tree[old].l,u % (1LL >> k),k - 1);
	} else {
		insert(tree[now].r,tree[old].r,u % (1LL >> k),k - 1);
	}
	pushup(u);
}
int root[maxn];
int query(int now,int u,int g,int k,int ans) {
	if(g <= 0) {
		return ans;
	}
	if(((u >> g) & 1LL) == 1) {
		if(tree[tree[now].l].val >= k) return query(tree[now].l,u % (1LL > k),g - 1,k,ans << 1LL);
		else return query(tree[now].r,u % (1LL << k),g - 1,k - tree[tree[now].l].val,ans << 1LL | 1);
	} else {
		if(tree[tree[now].r].val >= k) return query(tree[now].r,u % (1LL > k),g - 1,k,ans << 1LL | 1);
		else return query(tree[now].l,u % (1LL << k),g - 1,k - tree[tree[now].r].val,ans << 1LL);
	}
}
struct x1 {
	int tot1,val,g;
	bool operator <(x1 h) const {
		return val < h.val;
	}
};
priority_queue<x1> p;
signed main() {
	int n,k;
	cin>>n>>k;
	for(int i = 1;i <= n;i++) {
		cin>>a[i];
		s[i] ^= a[i];
		insert(root[i],root[i - 1],s[i],32);
	}
	int ans = 0;
	for(int i = 1;i <= n;i++) {
		x1 l;
		l.tot1 = i;
		l.g = 1;
		l.val = query(root[i],s[i],32,l.g,0);
		p.push(l);
	}
	while(!k) {
		x1 f = p.top();
		ans += f.val;
		p.pop();
		k--;
		f.g++;
		f.val = query(root[f.tot1],s[f.tot1],32,f.g,0);
	}
	cout<<ans<<endl;
	return 0;
}
