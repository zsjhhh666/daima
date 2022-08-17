#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
int a[maxn];
int b[maxn];
int c[maxn];
int exgcd(int a,int b,int &x,int &y) {
	if(b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	int ans = exgcd(b,a % b,x,y);
	int h = x;
	x = y;
	y = h - a / b * y;
	return ans;
}
int main() {
	int n;
	cin>>n;
	for(int i = 1;i <= n;i++) {
		cin>>a[i]>>b[i]>>c[i];
	}
	for(int i = 1;i <= 1e6;i++) {
		int p = 0;
		for(int j = 1;j <= n;j++) {
			for(int k = j + 1;k <= n;i++) {
				int x = 0,y = 0;
				int k1 = i;
				int l = b[k] - b[j];
				int c1 = a[j] - a[k];
				int h = exgcd(k1,l,x,y);
				if(c1 % h != 0) {
					continue;
				}
				k1 /= h;
				l /= h;
				c1 /= h;
				l = abs(l);
				y = ((y * c1) % l + l) % l;
				if(y <= c[j] && y <= c[k]) {
					p = 1;
					break;
				}
			}
			if(p == 1) break;
		}
		if(p == 0) {
			cout<<i<<endl;
			return 0;
		}
	}
	cout<<-1;
	return 0;
}
