#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
int N;

ifstream in("/NESPA/sapiens.txt");
list<char> chromosome;
list<char>::iterator Begin, End;
int b, e;

void Input() {
	string line;
	getline(in, line);
	
	while(getline(in, line)) {
		for(auto c : line) {
			chromosome.push_back(c);
		}
	}
	
	cin >> N;
}

void Initialize() {
	Begin = End = chromosome.begin();
}

void SetRange() {
	advance(Begin, b-1);
	advance(End, e);
}

void Front() {
	chromosome.splice(chromosome.begin(), chromosome, Begin, End);
}

void Back() {
	chromosome.splice(chromosome.end(), chromosome, Begin, End);
}

void Cut() {
	while(Begin!=End) {
		Begin = chromosome.erase(Begin);
	}
}
void Double() {
	int cnt = e-b+1;
	
	while(cnt--) {
		chromosome.insert(End, *Begin);
		Begin++;
	}
	
}

void Flip() {
	reverse(Begin, End);
}

void Report() {
	int size = chromosome.size();
	
	while(Begin!=End) {
		cout << *Begin;
		Begin++;
	}
	
	cout << endl;
}

void Solution() {
	string operation;
	cin >> operation;
	cin >> b >> e;
	
	int size = chromosome.size();
	
	if(b>=size) return;
	else if(e>size) {
		e = size;
	}
	SetRange();
	
	vector<string> ops {"front", "back", "cut", "double", "flip", "report"};
	
	int idx = find(ops.begin(), ops.end(), operation)-ops.begin();
	
	switch(idx) {
		case 0 : 
			Front();
			break;
		case 1 : 
			Back();
			break;
		case 2 : 
			Cut();
			break;
		case 3 : 
			Double();
			break;
		case 4 : 
			Flip();
			break;
		case 5 : 
			Report();
			break;
		default :
			cerr << "ERROR MESSAGE" << endl;
	}
}

void Solve() {
	Input();
	while(N--) {
		Initialize();
		Solution();
		//Print(); //debug
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	Solve();
}