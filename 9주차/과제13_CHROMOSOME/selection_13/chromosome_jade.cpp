#include <bits/stdc++.h>
using namespace std;
list<char> dna;
list<char>::iterator it1, it2;
int i, j, N;

static constexpr uint32_t const_hash(const char* p) {
	return *p ? static_cast<uint32_t>(*p) + 33 * const_hash(p + 1) : 5381;
}

void readFile() {
	ifstream in("/NESPA/sapiens.txt");
	// ignore first line
	string fline;
	getline(in, fline);

	char c;
	while (in.get(c)) {
		if(c!='
') dna.push_back(c);
	}
}

void iter() {
	it1 = dna.begin(), it2 = dna.begin();
	advance(it1, i - 1);
	advance(it2, j);
}

void report() {
	if (j > dna.size())
		j = dna.size();
	iter();
	for (auto it = it1; it != it2; it++) {
		cout << *it;
	}
	cout << endl;
}

int main() {
	readFile();
	cin >> N;

	while (N--) {
		string func;
		cin >> func >> i >> j;
		iter();
		switch (const_hash(func.c_str())) {
		case const_hash("front"):
			dna.splice(dna.begin(), dna, it1, it2);
			break;
		case const_hash("back"):
			dna.splice(dna.end(), dna, it1, it2);
			break;
		case const_hash("cut"):
			dna.erase(it1, it2);
			break;
		case const_hash("double"):
			dna.insert(it1, it1, it2);
			break;
		case const_hash("flip"):
			reverse(it1, it2);
			break;
		case const_hash("report"):
			report();
		}
	}
}