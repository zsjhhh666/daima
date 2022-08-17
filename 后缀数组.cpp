#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e3 + 5;
int x[maxn];
int y[maxn];
int c[maxn];
int sa[maxn];
int h[maxn];
int l[maxn];
void get_sa(string n,int m) {
	int s = n.size();
	for(int i = 0;i < s;i++) c[x[i] = n[i]]++;
	for(int i = 0;i < m;i++) c[i] += c[i - 1];
	for(int i = s - 1;i >= 0;i--) sa[--c[x[i]]] = i;
	for(int k = 1;k <= s;k <<= 1) {
		int p = 0;
		for(int i = s - k;i < s;i++) y[p++] = i;
		for(int i = 0;i < s;i++) if(sa[i] >= k) y[p++] = sa[i] - k;
		for(int i = 0;i < m;i++) c[i] = 0;
		for(int i = 0;i < s;i++) c[x[y[i]]]++;
		for(int i = 0;i < m;i++) c[i] += c[i - 1];
		for(int i = s - 1;i >= 0;i--) sa[--c[x[y[i]]]] = y[i];
		swap(x,y);
		p = 1;
		x[sa[0]] = 0;
		for(int i = 1;i < s;i++) x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? p - 1 : p++;
		if(p >= s) break;
		m = p;
	}
}
void get_h(string n) {
	int s = n.size();
	for(int i = 0;i < s;i++) {
		l[sa[i]] = i;
	}
	int k = 0;
	for(int i = 0;i < s;i++) {
		if(k) k--;
		int j = sa[l[i] - 1];
		while(n[i + k] == n[j + k]) k++;
		h[l[i]] = k;
	}
}
void get_ans(string n) {
	int s = n.size(),ans = 0;
	for(int k = 1;k <= s;k++) {
		int l = 0,r = 0,p = 0;
		for(int i = 0;i < s;i++) {
			if(h[i] >= k) {
				r = i;
				p = 1;
			} else {
				if(p == 1 && r >= l && abs(sa[r] - sa[l]) + 1 >= k) {
					ans += 1;
				}
				l = i + 1;
			}
			//cout<<l<<' '<<r<<endl;
		}
	}
	cout<<ans<<endl;
}
int main() {
	freopen("password.in","r",stdin);
	freopen("password.out","w",stdout);
	string n;
	cin>>n;
	n += '$';
	get_sa(n,131);
	//for(int i = 0;i < n.size();i++) cout<<sa[i]<<' ';
	get_h(n);
	for(int i = 0;i < n.size();i++) cout<<h[i]<<' ';
	get_ans(n);
	return 0;
}
