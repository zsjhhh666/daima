#include<bits/stdc++.h>
#define int long long
using namespace std;
bool is_prime(int n) {
	if(n == 1) return false;
	for(int i = 2;i <= sqrt(n);i++) {
		if(n % i == 0) return false;
	}
	return true;
}
int get_phi(int a) {
	int ans = a;
	for(int i = 2;i <= sqrt(a);i++) {
		if(a % i != 0) continue;
		if(is_prime(i) == true) {
			ans = ans / i * (i - 1);
		}
	}
	return ans;
}
int b[maxn];
int a[maxn];
signed main() {
	int n,m;
	cin>>n>>m;
	for(int i = 1;i <= n;i++) {
		cin>>a[i];
		b[i] = get_phi(a[i]);
	}
	
	return 0;
}
