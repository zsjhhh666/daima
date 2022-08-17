#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 5;
const int T = 1e9;
int a[maxn];
struct x {
	int l,r,val;
};
x tree[maxn * 400];
int root[maxn];
int tot = 0;
void pushup(int u) {
	tree[u].val = tree[tree[u].l].val + tree[tree[u].r].val;
}
void update(int l,int r,int &u,int val,int g) {
	if(!u) u = ++tot;
	if(l == r) {
		tree[u].val += g;
		return;
	}
	int mid = (l + r) >> 1;
	if(mid >= val) update(l,mid,tree[u].l,val,g);
	else update(mid + 1,r,tree[u].r,val,g);
	pushup(u);
}
int lowbit(int x) {
	return x & (-x);
}
int b[maxn];
int c[maxn];
int query(int l1,int r1,int k) {
	int tot = 0;
	int tot1 = 0;
	for(int i = l1;i >= 1;i -= lowbit(i)) {
		b[++tot] = root[i];
	}
	for(int i = r1;i >= 1;i -= lowbit(i)) {
		c[++tot1] = root[i];
	}
	int l = 0,r = T;
	while(l < r) {
		int ans = 0;
		for(int i = 1;i <= tot;i++) {
			ans -= tree[tree[b[i]].l].val;
		}
		for(int i = 1;i <= tot1;i++) {
			ans += tree[tree[c[i]].l].val;
		}
		//cout<<ans<<endl;
		if(ans >= k) {
			r = (l + r) >> 1;
			for(int i = 1;i <= tot;i++) {
				b[i] = tree[b[i]].l;
			}
			for(int i = 1;i <= tot1;i++) {
				c[i] = tree[c[i]].l;
			}
		} else {
			l = ((l + r) >> 1) + 1;
			for(int i = 1;i <= tot;i++) {
				b[i] = tree[b[i]].r;
			}
			for(int i = 1;i <= tot1;i++) {
				c[i] = tree[c[i]].r;
			}
			k -= ans;
		}
	}
	return l;
}
int main() {
	int n,m;
	cin>>n>>m;
	for(int i = 1;i <= n;i++) {
		cin>>a[i];
		for(int j = i;j <= n;j += lowbit(j)) {
			update(0,T,root[j],a[i],1);
		}
	}
	char k;
	int l,r,p,x,y;
	for(int i = 1;i <= m;i++) {
		cin>>k;
		if(k == 'Q') {
			cin>>l>>r>>p;
			l -= 1;
			cout<<query(l,r,p)<<endl;
		} else {
			cin>>x>>y;
			for(int j = x;j <= n;j += lowbit(j)) {
				update(0,T,root[j],a[x],-1);
				update(0,T,root[j],y,1);
			}
			a[x] = y;
		}
	}
	return 0;
}
