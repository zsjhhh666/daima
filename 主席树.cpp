#include<bits/stdc++.h>
using namespace std;
struct x {
	int l,r,val;
};
x tree[maxn * 40];
int root[maxn];
int tot = 0;
void pushup(int now) {
	tree[now].val = tree[tree[now].l].val + tree[tree[now].r].val;
}
void insert(int l,int r,int &now,int old,int x) {
	now = ++tot;
	tree[now] = tree[old];
	if(l == r) {
		tree[now].val++;
		return;
	}
	int mid = (l + r) >> 1;
	if(mid >= x) {
		insert(l,mid,tree[now].l,tree[old].l,x);
	} else {
		insert(mid + 1,r,tree[now].r,tree[old].r,x);
	}
	pushup(now);
}
int query(int l,int r,int now,int old,int k) {
	if(!tree[now].val) return -1;
	if(l == r) return l;
	int mid = (l + r) >> 1;
	if(tree[tree[now].l].val - tree[tree[old].l].val >= k) {
		return query(l,mid,tree[now].l,tree[old].l,k);
	} else {
		return query(mid + 1,r,tree[now].r,tree[old].r,k - tree[tree[now].l].val + tree[tree[old].l].val);
	}
}
int main() {
	int n;
	cin>>n;
	for(int i = 1;i <= n;i++) {
		cin>>a;
		insert(1,1e5,root[i],root[i - 1],a);
	}
	int t;
	cin>>t;
	while(t--) {
		cin>>l>>r>>k;
		cout<<query(1,1e5,root[r],root[l - 1],k)<<endl;
	}
	return 0;
}
