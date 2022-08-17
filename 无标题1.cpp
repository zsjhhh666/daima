#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e9;
void get_ans(int i) {
	for(int i = 1;i <= n;i++) {
		
	}
}
int f[maxn];
int main() {
	int t;
	cin>>t;
	
	while(t--) {
		int ans = 0;
		cin>>n>>m;
		for(int i = 1;i <= sqrt(n);i++) {
			if(n % i != 0) {
				continue;
			}
			if(i >= m) {
				ans += get_ans(i);
			}
			if(n / i >= m) {
				ans += get_ans(n / i);
			}
		}
	}
	return 0;
}
