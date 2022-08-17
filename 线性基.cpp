#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 5 * 10 + 5;
int a[maxn];
int p[maxn];
void insert(int x) {
	for(int i = 50;i >= 0;i--) {
		if(!(x >> (long long)i)) continue;
		if(!p[i]) {p[i] = x;break;}
		x ^= p[i];
	}
}
signed main() {
	int n;
	cin>>n;
	for(int i = 1;i <= n;i++) {
		cin>>a[i];
	}
	for(int i = 1;i <= n;i++) {
		insert(a[i]);
	}
	int ans = 0;
	for(int i = 50;i >= 0;i--) {
		if((ans ^ p[i]) > ans) ans ^= p[i];
	}
	cout<<ans<<endl;
	return 0;
}
