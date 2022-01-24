#include <bits/stdc++.h>
using namespace std;
int N;
vector<queue<int>> v;
queue<int> seq;

void Read() {
	int input;
	cin >> N;

	for(int i = 0; i < N; i++) {
		queue<int> q;
		do{
			cin >> input;
			q.push(input);
		} while(input != 0);
		v.push_back(q);
	}
}

void  Set(){
	int len = 0;

	for(auto i : v) {
		len += (i.size() - 1);
	}
	while(len) {
		int j, Max = 10001;
		for(int i = 0; i < N; i++) {
			if(v[i].front() != 0 && v[i].front() < Max) {
				Max = v[i].front();
				j = i;
			}
		}
		seq.push(Max);
		v[j].pop();
		len--;
	}
}

void Print() {
	while(!seq.empty()) {
		cout << seq.front() << endl;
		seq.pop();
	}
}

int main() {
	Read();
	Set();
	Print();
	return 0;
}