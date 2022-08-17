#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
struct X {
	int h,p,q;
	friend bool operator < (const X &a,const X &b) {
		return (a.h == b.h) ? ((a.p == b.p) ? (a.q < b.q) : (a.p < b.p)) : (a.h < b.h);
	}
};
std::map<X,int> p2[maxn];
int gcd(int x,int y) {
	return (y == 0) ? x : gcd(y,x % y);
}
void exgcd(int a,int b,int &x,int &y) {
	if(a == 1) {
		x = 1;
		y = 0;
		return;
	}
	exgcd(b,a % b,y,x);
	y -= a / b * x;
}
int inv(int a,int b) {
	int x,y;
	exgcd(a,b,x,y);
	return (x % b + b) % b;
}
int n,m;
void init() {
	int f1,f2,cnt;
	for(int i = 2;i <= m;i++) {
		if(m % i == 0) {
			f1 = 1;
			f2 = 0;
			cnt = 0;
			//cout<<"hhh666"<<endl;
			while(1) {
				if(f1 != 0 && f2 != 0) {
					int p1 = gcd(f1,i);
					int q1 = gcd(f2,i);
					int m1 = i / p1 / q1;
					int h = (int)(1ll * (f2 / q1) * inv((f1 / p1),m1) % m1);
					if(p2[i].find((X){h,p1,q1}) == p2[i].end()) {
						p2[i][(X){h,p1,q1}] = cnt;
					}
					//cout<<h<<' '<<p1<<' '<<q1<<endl;
				}
				int l = f2;
				f2 = (f2 + f1) % i;
				f1 = l;
				cnt++;
				if(f1 == 1 && f2 == 0) break;
			}
		}
	}
}
int main() {
	cin>>n>>m;
	init();
	//cout<<"hhh666"<<endl;
	int a,b;
	for(int i = 1;i <= n;i++) {
		cin>>a>>b;
		b = (m - b) % m;
		if(a == 0) {
			cout<<0<<endl;
			continue;
		}
		if(b == 0) {
			cout<<1<<endl;
			continue;
		}
		int m2 = m;
		int d = gcd(gcd(a,b),m2);
		m2 /= d;
		a /= d;
		b /= d;
		int p = gcd(a,m2);
		int q = gcd(b,m2);
		a /= p;
		b /= q;
		//cout<<m2<<endl;
		//cout<<"hhh666"<<endl;
		int k = (int)(1ll * a * inv(b,(m2 / p / q)) % (m2 / p / q));
		//cout<<"hhh666"<<endl;
		//cout<<k<<' '<<p<<' '<<q<<endl;
		if(p2[m2].count((X){k , q , p}) ) {
			cout<<p2[m2][(X){k,q,p}]<<endl;
		} else {
			cout<<-1<<endl;
		}
	}
	return 0;
}
