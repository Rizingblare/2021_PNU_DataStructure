#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
#define all(v) v.begin(), v.end()
const ll MX = 33;
const ll INF = 9e15;
ll n, cnt[MX];
priority_queue<pll> pq;
vector<ll> v[MX];
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin >> n;
	for (int i = 1, x; i <= n; i++) {
		while (cin >> x) {
			if (x == 0) {
				break;
			}
			v[i].push_back(x);
		}
		if (v[i].size()) {
			pq.push({ -v[i][0],-i });
		}
	}
	while (!pq.empty()) {
		ll num = -pq.top().first;
		ll idx = -pq.top().second;
		pq.pop();
		cout << num << "
";
		cnt[idx]++;
		if (cnt[idx] == v[idx].size()) {
			continue;
		}
		else {
			pq.push({ -v[idx][cnt[idx]],-idx });
		}
	}

}