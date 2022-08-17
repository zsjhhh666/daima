#include<bits/stdc++.h>
using namespace std;
int n,m,p,c;
const int maxn = 5e4 + 5;
const int maxn1 = 1e7 + 5;
int a[maxn];
struct x {
	int sum;
	int minn;
};
int a1,b,bl,bl1[35][maxn1],bl2[35][maxn1];
void init() {
	int p1 = p;
	for(int i = 1;i <= 35;i++) {
		if(p1 == 1) break;
		bl1[i][0] = bl2[i][0] = 1 % p1;
		for(int j = 1;j <= bl;j++) bl1[i][j] = bl1[i][j - 1] * c % p1;
		for(int j = 1;j <= bl;i++) bl2[i][j] = bl2[i][j - 1] * bl1[i][bl] % p1;
		p1 = phi[pl];
	}
}
int p1(int a,int b,int cnt) {
	return b <= bl ? bl1[cnt][b] : bl2[cnt][b / bl] * bl1[cnt][b - b / bl * bl] % p;
}
x tree[maxn << 2];
void pushup(int u) {
	tree[u].sum = (tree[u << 1].sum + tree[u << 1 | 1].sum) % p;
	tree[u].minn = min(tree[u << 1].minn,tree[u << 1 | 1].minn);
}
bool not_prime[maxn1];
int phi[maxn1];
int prime[maxn1];
int cnt = 0;
void get_phi(int u) {
	for(int i = 2;i <= p;i++) {
		if(not_prime[i] == false) {
			prime[++cnt] = i;
			phi[i] = i - 1;
		}
		for(int j = 1;j <= cnt && i * prime[j] <= n;j++) {
			not_prime[i * prime[j]] = true;
			if(i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			} else {
				phi[i * prime[j]] = phi[i] * phi[j];
			}
		}
	}
}
void build(int l,int r,int u) {
	if(l == r) {
		tree[u].minn = 0;
		tree[u].sum = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l,mid,u << 1);
	build(mid + 1,r,u << 1 | 1);
	pushup(u);
}
int f = 0;
int get_sum(int a,int u,int h,int cnt) {
	if(u == 1) {
		if(a > h) {
			f = 1;
		}
		return a % h;
	}
	int sum = get_sum(a,u - 1,phi[m],cnt + 1);
	if(f == 1) {
		sum += phi[m];
	}
	return p1(c,sum,cnt);
}
void update(int l,int r,int u,int L,int R) {
	if(l == r) {
		tree[u].minn = min(tree[u].minn + 1,35);
		tree[u].sum = get_sum(a[l],tree[u].minn,m,1);
		return;
	}
	int mid = (l + r) >> 1;
	if(L <= mid) {
		update(l,mid,u << 1,L,R);
	}
	if(R > mid) {
		update(mid + 1,r,u << 1 | 1,L,R);
	}
	pushup(u);
}
int query(int l,int r,int u,int L,int R) {
	if(L <= l && r <= R) {
		return tree[u].sum % p;
	}
	int ans = 0;
	int mid = (l + r) >> 1;
	if(L <= mid) {
		ans += query(l,mid,u << 1,L,R);
		ans %= p;
	}
	if(R > mid) {
		ans += query(mid + 1,r,u << 1 | 1,L,R);
		ans %= p;
	}
	return ans;
}
int main() {
	cin>>n>>m>>p>>c;
	bl = sqrt(p);
	for(int i = 1;i <= n;i++) {
		cin>>a[i];
	}
	build(1,n,1);
	int x,y,z;
	for(int i = 1;i <= m;i++) {
		cin>>x>>y>>z;
		if(x == 0) {
			update(1,n,1,y,z);
		} else {
			cout<<query(1,n,1,y,z)<<endl;
		}
	}
	return 0;
}
