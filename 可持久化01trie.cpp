#include<bits/stdc++.h>
using namespace std;
const int maxn = 6e5 + 5;
int a[maxn];
int root[maxn];
struct x {
	int l,r,maxx;
};
x tree[maxn * 25];
int tot = 0;
void insert(int &now,int old,int u,int k,int h) {
	now = ++tot;
	if(h <= 0) {tree[now].maxx = k;return;}
	tree[now] = tree[old];
	if((u & (1 << (h - 1))) == 0) insert(tree[now].l,tree[old].l,u,k,h - 1);
	else insert(tree[now].r,tree[old].r,u - (1 << (h - 1)),k,h - 1);
	tree[now].maxx = max({tree[tree[now].l].maxx,tree[tree[now].r].maxx,tree[now].maxx});
	tree[old].maxx = max({tree[tree[old].l].maxx,tree[tree[old].r].maxx,tree[old].maxx});
	//cout<<tree[now].l<<' '<<tree[now].r<<' '<<h<<' '<<tree[now].maxx<<endl;
}
int query(int now,int u,int l,int k) {
	if(k <= 0) return 0;
	if(tree[now].maxx < l || (tree[now].l < l && tree[now].r < l)) {
		return 0;
	}
	if(!tree[now].l && !tree[now].r) return 0;
	//cout<<((u >> (k - 1)) ^ 0)<<' '<<((u >> (k - 1)) ^ 1)<<endl;
	if(!tree[now].r || tree[tree[now].r].maxx < l) return (1 << (k - 1)) * ((u >> (k - 1)) ^ 0) + query(tree[now].l,u % (1 << (k - 1)),l,k - 1);
	if(!tree[now].l || tree[tree[now].l].maxx < l) return  (1 << (k - 1)) * ((u >> (k - 1)) ^ 1) + query(tree[now].r,u % (1 << (k - 1)),l,k - 1);
	if(((u >> (k - 1)) ^ 0) == 1) {
		return (1 << (k - 1)) * ((u >> (k - 1)) ^ 0) + query(tree[now].l,u % (1 << (k - 1)),l,k - 1);
	} else {
		return (1 << (k - 1)) * ((u >> (k - 1)) ^ 1) + query(tree[now].r,u % (1 << (k - 1)),l,k - 1);
	}
}
int main() {
	int n,m;
	cin>>n>>m;
	for(int i = 1;i <= n;i++) {
		cin>>a[i];
		a[i] ^= a[i - 1];
		//cout<<a[i]<<endl;
	}
	insert(root[0],0,0,0,25);
	tree[0].maxx = -1;
	for(int i = 1;i <= n;i++) {
		insert(root[i],root[i - 1],a[i],i,25);
		//cout<<"hhhhhh"<<endl;
	}
	//cout<<666<<endl;
	char a1;
	int b,c,p;
	int tot1 = n;
	for(int i = 1;i <= m;i++) {
		cin>>a1>>b;
		if(a1 == 'A') {
			b ^= a[tot1];
			tot1++;
			a[tot1] = b;
			insert(root[tot1],root[tot1 - 1],b,tot1,25);
		} else if(a1 == 'Q') {
			cin>>c>>p;
			int val = (a[tot1] ^ p);
			//cout<<val<<endl;
			cout<<query(root[c - 1],val,b - 1,25)<<endl;
		}
	}
	return 0;
}
// 1010
// 0100
// 101
// 100
