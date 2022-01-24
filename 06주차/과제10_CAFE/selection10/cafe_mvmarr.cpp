#include <iostream>
#include <list>
#include <vector>

using namespace std;

typedef struct {
	int id;
	int seat;
	int gap;
} SEAT;
vector<SEAT> result;
list<SEAT> it;
list<SEAT>::iterator iter;
list<SEAT>::iterator iterT;
int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < k; i++) {
		int in_id;
		cin >> in_id;
		if (i == 0) {
			it.push_back({ in_id, 1, n });
			result.push_back({ in_id, 1, n });
		}
		else {
			int eq = 0;
			int max_gap = 0;
			for (iterT = it.begin(); iterT != it.end(); iterT++) {
				if (max_gap < iterT->gap) {
					max_gap = iterT->gap;
					iter = iterT;
				}
				if (in_id == iterT->id) {
					SEAT nex = *iterT;
					iterT = it.erase(iterT);
					if (iterT == it.begin()) iterT = it.end();
					iterT--;
					SEAT cur = *iterT;
					iterT = it.erase(iterT);
					it.insert(iterT, { cur.id, cur.seat, cur.gap + nex.gap });
					eq = 1;
					break;
				}
			}
			if (eq) continue;
			int cur_seat;
			int cur_gap;
			SEAT fro = *iter;
			iterT = iter;
			iter++;
			if (iter == it.end()) {
				iter = it.begin();
				SEAT nex = *iter;
				cur_seat = (fro.seat + nex.seat + n) / 2;
				if (cur_seat > n) cur_seat -= n;
				else iter = it.end();
				cur_gap = (nex.seat + n - fro.seat + 1) / 2;
				it.insert(iter, { in_id, cur_seat,  cur_gap});
				result.push_back({ in_id, cur_seat,  cur_gap });
				iter = iterT;
			}
			else {
				SEAT nex = *iter;
				cur_seat = (fro.seat + nex.seat) / 2;
				cur_gap = (nex.seat - fro.seat + 1) / 2 ;
				iter = it.insert(iter, { in_id, cur_seat, cur_gap});
				result.push_back({ in_id, cur_seat,  cur_gap });
				iter--;
			}
			iter = it.erase(iter);
			it.insert(iter, { fro.id, fro.seat, fro.gap - cur_gap });
		}
	}
	for (int i = 0; i < result.size(); i++) {
		cout << result.at(i).id << " " << result.at(i).seat << endl;
	}
	return 0;
}