#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int a[maxn];
int b[maxn];
int main() {
	int t;
	cin>>t;
	while(t--) {
		int n;
		cin>>n;
		int cnt = 1,tot = 0;
		a[0] = -1;
		char a1;
		cin>>a1;
		a[1] = a1 - '0';
		for(int i = 2;i <= n;i++) {
			cin>>a1;
			a[i] = a1 - '0';
			if(a[i] != a[i - 1]) {
				b[++tot] = cnt;
				cnt = 1;
			} else {
				cnt++;
			}
		}
		b[++tot] = cnt;
		int cnt1 = 0;
		for(int i = 1;i <= tot;i++) {
			//cout<<b[i]<<endl;
			if(b[i] % 2 != 0 && b[i + 1] % 2 != 0) {
				cnt1++;
				i++;
				if(b[i + 1] == 1) {
					b[i + 2] = b[i + 2] + b[i + 1] + b[i];
					b[i + 1] = 0;
					b[i] = 0;
				}
			} else if(b[i] % 2 != 0) {
				cnt1 += min(b[i],b[i + 1] + b[i - 1]);
				if(min(b[i],b[i + 1] + b[i - 1]) == b[i]) {
					b[i + 1] = b[i] + b[i + 1] + b[i - 1];
					b[i] = 0;
					b[i - 1] = 0;
				} else {
					b[i + 2] = b[i + 2] + b[i + 1] + b[i] + b[i - 1] + b[i - 2];
					b[i + 1] = 0;
					b[i] = 0;
					b[i - 1] = 0;
					b[i - 2] = 0;
				}
			}
			//cout<<b[i]<<' '<<cnt1<<endl;
		}
		cout<<cnt1<<endl;
	}
	return 0;
}
//00111000011
//001111111
//1001111111111111111111111111111110011
