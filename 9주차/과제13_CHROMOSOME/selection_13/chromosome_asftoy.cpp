#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#define listout(x) for(auto i : x){cout << i << "";} cout << endl;
using namespace std;

const vector<string> OPERATIONS = { "front", "back", "cut", "double", "flip", "report" };

list<char> readFile() {
	ifstream fin("/NESPA/sapiens.txt");
	int i = 0;
	string str, temp;
	while (getline(fin, temp)) {
		if ((i++) == 0) continue;
		str += temp;
	}
	list<char> s(str.begin(), str.end());
	fin.close();
	return s;
}

int main(void) {
	int t; cin >> t;
	
	list<char> genome = readFile();
	for (int i = 0; i < t; i++) {
		string op; int s, e;  cin >> op >> s >> e;

		if (e > genome.size()) { e = genome.size(); }
		
		int idx = find(OPERATIONS.begin(), OPERATIONS.end(), op) - OPERATIONS.begin();

		if (idx != 5 and s > genome.size()) { continue; }
		if (idx == 5 and s > genome.size()) { cout << "NONE" << endl; continue; }

		auto A = next(genome.begin(), s - 1);
		auto B = next(genome.begin(), e);

		switch (idx) {
		case 0: //front
			genome.splice(genome.begin(), genome, A, B);
			break;
		case 1: //back
			genome.splice(genome.end(), genome, A, B);
			break;
		case 2: //cut
			genome.erase(A, B);
			break;
		case 3: //double
			genome.insert(B, A, B);
			break;
		case 4: //flip
			reverse(A, B);
			break;
		case 5: //report
			for (A; A != B; A++) {
				cout << *A;
			}
			cout << endl;
			break;
		}
	}
	return 0;
}