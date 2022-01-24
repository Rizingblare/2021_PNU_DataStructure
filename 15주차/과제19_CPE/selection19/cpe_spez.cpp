#include <bits/stdc++.h>
#define TIID tuple<int, int, double>

using namespace std;

int N, K = 2;
vector < string > v;
vector < set<string> > cmp_set;
vector < pair<int, int> > combi;
vector < TIID > result;

void Read() {
    cin >> N;
    string p;
    for(int i=0; i<N; i++) {
        string ss;
        while(1) {
            cin >> p;
            if (p.compare("$") == 0) break;
            int nn = p.size();
            for(int i=0; i<nn; i++) {
                if((p[i] & 0x80) != 0) {
                    ss.push_back(p[i]);
                }
            }
        }
        v.push_back(ss);
    }
}

void get_combination() {
	int i;
	vector < int > n;
	vector < bool > ind;

	for(i = 0; i < N    ; i++) { n.push_back(i);       }
	for(i = 0; i < N - K; i++) { ind.push_back(false); }
	for(i = 0; i < K    ; i++) { ind.push_back(true);  }

	do{
		int j = 0;
		array < int, 2 > temp;
		for(i = 0; i < ind.size(); i++) {
			if(ind[i] == true) { temp[j++] = n[i]; }
		}
		pair < int, int > p = make_pair(temp.at(0), temp.at(1));
		combi.push_back(p);
	} while(next_permutation(ind.begin(), ind.end()));
}

void Setting() {
	for(auto p : v) {
		set<string> temp;
		if(p != "") {
			for(int i = 0; i < p.size() - 5; i+=3) {
				string ss1;
				ss1.push_back(p[i]  );
				ss1.push_back(p[i+1]);
				ss1.push_back(p[i+2]);
				ss1.push_back(p[i+3]);
				ss1.push_back(p[i+4]);
				ss1.push_back(p[i+5]);
				temp.insert(ss1);
			}
		}
		cmp_set.push_back(temp);
	}
	get_combination();
}

bool pred(TIID t1, TIID t2) {
	if(get<2>(t1) == get<2>(t2)) {
		if(get<0>(t1) == get<0>(t2)) { return get<1>(t1) < get<1>(t2); }
		return get<0>(t1) < get<0>(t2);
	}
	return get<2>(t1) > get<2>(t2);
}

double sim(set< string > s1, set< string > s2) {
	if     (s1.size() == 0 && s2.size() == 0) return 1.0;
	else if(s1.size() == 0 || s2.size() == 0) return 0.0;
	float inter_size;
	set< string > uni(s2);
	for(auto i : s1) { uni.insert(i); }

	inter_size = s1.size() + s2.size() - uni.size();
	return inter_size / uni.size();
}

void get_Sim() {
	for(auto i : combi) {
		double d = sim(cmp_set[i.first], cmp_set[i.second]);
		TIID temp = make_tuple(i.first, i.second, d);
		result.push_back(temp);
	}
	sort(result.begin(), result.end(), pred);
}

void Outcome() {
	cout << get<0>(result.front()) + 1 << " " \n		 << get<1>(result.front()) + 1 << endl;
}

int main() {
    Read();
    Setting();
	get_Sim();
	Outcome();
    return 0;
}
