#include<bits/stdc++.h>
using namespace std;
int n,m,k;
const int maxn = 2e6 + 5;
struct X {
	int x,y;
};
int a[maxn];
int fa[maxn];
vector<X> tree[maxn];
void insert(int l,int r,int u,int L,int R,int x,int y) {
	if(L <= l & r <= R) {
		X l;
		l.x = x;
		l.y = y;
		tree[u].push_back(l);
		return;
	}
	int mid = (l + r) >> 1;
	if(mid >= L) insert(l,mid,u << 1,L,R,x,y);
	else insert(mid + 1,r,u << 1 | 1,L,R,x,y);
}
int find(int x) {
	return fa[x] != x ? x : 0;
}
void get_ans(int l,int r,int u) {
	int h = 0;
	for(int i = 0;i < tree[u].size();i++) {
		int x = tree[u][i].x;
		int y = tree[u][i].y;
		int x1 = find(x);
		int y1 = find(y);
		int x2 = find(x + n);
		int y2 = find(y + n);
		if(y2 == x1 || y2 == x2 || y1 == x1 || y1 == x2) {
			break;
		}
		h = i;
		fa[x1] = y2;
		fa[x2] = y1;
	}
	if(h == tree[u].size() - 1) {
		int mid = (l + r) >> 1;
		get_ans(l,mid,u << 1);
		get_ans(mid + 1,r,u << 1 | 1);
	} else if(!tree[u].size()) {
		cout<<"Yes"<<endl;
	} else {
		for(int i = l;i <= r;i++) {
			cout<<"No"<<endl;
		}
	}
	for(int i = 0;i < l;i++) {
		int x = tree[u][i].x;
		int y = tree[u][i].y;
		int x1 = find(x);
		int y1 = find(y);
		int x2 = find(x + n);
		int y2 = find(y + n);
		fa[x1] = x1;
		fa[x2] = x2;
	}
}
int main() {
	cin>>n>>m>>k;
	int x,y,l,r;
	for(int i = 1;i <= m;i++) {
		cin>>x>>y>>l>>r;
		insert(1,n,1,l,r,x + n,y);
		insert(1,n,1,l,r,x,y + n);
	}
	for(int i = 1;i <= n;i++) {
		fa[i] = i;
	}
	get_ans(1,n,1);
	return 0;
}
