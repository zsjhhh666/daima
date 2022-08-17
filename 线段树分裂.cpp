#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
long long a[maxn];
struct x {
	long long val;
	int l,r;
} tree[maxn * 40];
int root[maxn];
int tot = 0;
void pushup(int u) {
	tree[u].val = tree[tree[u].l].val + tree[tree[u].r].val;
}
void build(int l,int r,int &u) {
	u = ++tot;
	if(l == r) {
		tree[u].val = a[l] - a[l - 1];
		return;
	}
	int mid = (l + r) >> 1;
	if(a[mid] - a[l - 1] > 0)
		build(l,mid,tree[u].l);
	if(a[r] - a[mid] > 0)
		build(mid + 1,r,tree[u].r);
	//	cout<<tree[u].val<<endl;
	pushup(u);
}
void spilt(int l,int r,int &u,int &u1,int L,int R) {
	if(!u) return;
	if(L <= l && r <= R) {
		u1 = u;
		u = 0;
		return;
	}
	u1 = ++tot;
	int mid = (l + r) >> 1;
	if(mid >= L) spilt(l,mid,tree[u].l,tree[u1].l,L,R);
	if(R > mid) spilt(mid + 1,r,tree[u].r,tree[u1].r,L,R);
	pushup(u);
	pushup(u1);
}
void insert(int l,int r,int &u,int L,int y) {
	if(!u) u = ++tot;
	if(l == r) {
		tree[u].val += y;
		//cout<<tree[u].val<<' '<<l<<' '<<r<<endl;
		return;
	}
	int mid = (l + r) >> 1;
	if(mid >= L)
		insert(l,mid,tree[u].l,L,y);
	else
		insert(mid + 1,r,tree[u].r,L,y);
	pushup(u);
	//cout<<tree[u].val<<' '<<l<<' '<<r<<endl;
}
void merge(int l,int r,int &u,int u1) {
	if(!u || !u1) {
		u = u | u1;
		return;
	}
	tree[u].val += tree[u1].val;
	int mid = (l + r) >> 1;
	merge(l,mid,tree[u].l,tree[u1].l);
	merge(mid + 1,r,tree[u].r,tree[u1].r);
}
long long query(int l,int r,int u,int L,int R) {
	if(L <= l && r <= R) {
		return tree[u].val;
	}
	int mid = (l + r) >> 1;
	long long ans = 0;
	if(L <= mid) ans += query(l,mid,tree[u].l,L,R);
	if(R > mid) ans += query(mid + 1,r,tree[u].r,L,R);
	return ans;
}
int kth(int l,int r,int u,int k) {
	if(l == r) {
		return l;
	}
	int mid = (l + r) >> 1;
	if(tree[tree[u].l].val >= k)
		return kth(l,mid,tree[u].l,k);
	return kth(mid + 1,r,tree[u].r,k - tree[tree[u].l].val);
}
int main() {
	int n,m;
	cin>>n>>m;
	int b;
	for(int i = 1;i <= n;i++) {
		cin>>b;
		a[i] = b;
	}
	for(int i = 1;i <= n;i++) a[i] += a[i - 1];
	int h = 1;
	build(1,n,root[1]);
	int c,x,y,z;
	for(int i = 1;i <= m;i++) {
		cin>>c;
		if(c == 0) {
			cin>>x>>y>>z;
			spilt(1,n,root[x],root[++h],y,z);
		} else if(c == 1) {
			cin>>x>>y;
			merge(1,n,root[x],root[y]);
		} else if(c == 2) {
			cin>>x>>y>>z;
			insert(1,n,root[x],z,y);
		} else if(c == 3) {
			cin>>x>>y>>z;
			cout<<query(1,n,root[x],y,z)<<endl;
		} else {
			cin>>x>>y;
			if(tree[root[x]].val < y) {
				cout<<-1<<endl;
				continue;
			}
			cout<<kth(1,n,root[x],y)<<endl;
		}
	}
	return 0;
}
