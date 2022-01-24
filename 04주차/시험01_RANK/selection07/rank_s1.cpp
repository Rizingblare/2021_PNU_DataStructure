#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define all(v) v.begin(), v.end()
const ll MX = 303030;
const ll INF = 9e15;
ll n;
struct info {
	string s;
	vector<ll> v;
	bool operator<(info x) {
		if (v.size() != x.v.size()) {
			return v.size() > x.v.size();
		}
		else {
			for (int i = 0; i < v.size(); i++) {
				if (v[i] != x.v[i]) {
					return v[i] > x.v[i];
				}
			}
			return s < x.s;
		}
	}
};

vector<info> arr;
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		vector<ll> v;
		ll x;
		while (cin >> x) {
			if (x == 0) break;
			v.push_back(x);
		}
		sort(all(v));
		arr.push_back({ s,v });
	}
	sort(all(arr));

	for (int i = 0; i < n; i++) {
		cout << arr[i].s << "\n";
	}
}