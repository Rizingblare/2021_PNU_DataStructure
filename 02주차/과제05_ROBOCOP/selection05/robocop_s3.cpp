#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>
using namespace std;
int n, m, k;
bool flag = false;
map<string, vector<string>> mp;
vector<string> answer;
set<string> s;

void dfs(string alpha) {
	for(int i=0; i<mp[alpha].size(); i++) {
		if(flag) return;
		if(mp[alpha][i] == "$") {
			s.erase(alpha);
			return;
		}
		else if(mp[alpha][i].size() == 1 && mp[alpha][i] >= "A" && mp[alpha][i] <= "Z") {
			if(s.find(mp[alpha][i]) != s.end()) {
				flag = true;
				return;
			}
			s.insert(mp[alpha][i]);
			dfs(mp[alpha][i]);
		} 
		else answer.push_back(alpha+"-"+mp[alpha][i]);
	}	
}

void init() {
	cin >> n >> m >> k;
	for(int i=0; i<n; i++) {
		string a;
		vector<string> v;
		cin >> a;
		while(true) {
			string x;
			cin >> x;
			v.push_back(x);
			if(x == "$") break;
		}
		mp[a] = v;
	}
	dfs("M");
	if(flag) {
		cout << "DEADLOCK" << '
';
	}
	else {
		if(m<=answer.size()) cout << answer[m-1] << '\n';
		else cout << "NONE" << '\n';
		if(k<=answer.size()) cout << answer[k-1] << '\n';
		else cout << "NONE" << '\n';
 	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	init();
}