#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 5;
struct x1 {
	int ch[2];
	int sum;
	int fa;
	int t;
	int a;
};
x1 tree[maxn];
int t(int x) {
	if(tree[tree[x].fa].ch[0] == x) {
		return 0;
	}
	if(tree[tree[x].fa].ch[1] == x) {
		return 1;
	}
	return -1;
}
void pushup(int x) {
	tree[x].sum = tree[tree[x].ch[0]].sum ^ tree[tree[x].ch[1]].sum ^ tree[x].a;
}
void pushdown(int x) {
	if(tree[x].t) {
		if(tree[x].ch[0]) {
			tree[tree[x].ch[0]].t ^= tree[x].t;
			swap(tree[tree[x].ch[0]].ch[0],tree[tree[x].ch[0]].ch[1]);
		}
		if(tree[x].ch[1]) {
			tree[tree[x].ch[1]].t ^= tree[x].t;
			swap(tree[tree[x].ch[1]].ch[0],tree[tree[x].ch[1]].ch[1]);
		}
	}
	tree[x].t = 0;
}
void r(int x) {
	int y = tree[x].fa;
	int z = tree[y].fa;
	int t1 = t(x);
	if(t(y) != -1) {
		tree[z].ch[t(y)] = x;
	}
	tree[x].fa = z;
	tree[y].ch[t1] = tree[x].ch[t1 ^ 1];
	tree[tree[x].ch[t1 ^ 1]].fa = y;
	tree[x].ch[t1 ^ 1] = y;
	tree[y].fa = x;
	pushup(y);
	pushup(x);
}
void d(int x) {
	if(t(x) != -1) {
		d(tree[x].fa);
	}
	pushdown(x);
}
void splay(int x) {
	d(x);
	for(;t(x) != -1;r(x)) {
		if(t(tree[x].fa) != -1) {
			if(t(tree[x].fa) == t(x)) {
				r(tree[x].fa);
			} else {
				r(x);
			}
		}
	}
}
void across(int x) {
	int y = 0;
	while(x) {
		splay(x);
		tree[x].ch[1] = y;
		pushup(x);
		y = x;
		x = tree[x].fa;
	}
}
void makeroot(int x) {
	across(x);
	splay(x);
	tree[x].t ^= 1;
	swap(tree[x].ch[0],tree[x].ch[1]);
}
int findroot(int x) {
	across(x);
	splay(x);
	while(tree[x].ch[0]) pushdown(x),x = tree[x].ch[0];
	return x;
}
void spilt(int x,int y) {
	makeroot(x);
	across(y);
	splay(y);
}
void link(int x,int y) {
	makeroot(x);
	tree[x].fa = y;
}
void cut(int x,int y) {
	spilt(x,y);
	if(findroot(y) != x || tree[x].fa != y || tree[x].ch[1]) return;
	tree[x].fa = tree[y].ch[0] = 0;
	pushup(y);
}
int main() {
	int n,m;
	cin>>n>>m;
	for(int i = 1;i <= n;i++) {
		cin>>tree[i].a;
	}
	int id,x,y;
	for(int i = 1;i <= m;i++) {
		//cout<<"hhh666"<<endl;
		cin>>id>>x>>y;
		if(id == 0) {
			spilt(x,y);
			cout<<tree[y].sum<<endl;
		} else if(id == 1) {
			if(findroot(x) != findroot(y)) link(x,y);
		} else if(id == 2) {
			if(findroot(x) == findroot(y)) cut(x,y);
		} else {
			tree[x].a = y;
			splay(x);
		}
	}
	return 0;
}
