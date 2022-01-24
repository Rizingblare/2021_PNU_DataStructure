#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <algorithm>
#define Loop(n) for (int i=0; i<n; i++)

using namespace std;

list<char> cards;
list<char>::iterator it1, it2, it3;
int r1, r2;

void setIter() {
	it1 = cards.begin();
	it2 = it1--;
	advance(it1, r1);
	advance(it2, r2);
}

void frontF()	{ setIter();	cards.splice(cards.begin(), cards, it1, it2); }
void backF() 	{ setIter();	cards.splice(cards.end(), cards, it1, it2); }
void cutF()		{ setIter();	cards.erase(it1, it2); }
void flipF()	{ setIter(); 	reverse(it1, it2); }

void doubleF() {
	setIter();
	auto it3 = it2;
	cards.insert(it3, it1, it2);
}

void reportF() {
	setIter();
	for (auto it = it1; it != it2; it++) cout << *it;
	cout << endl;
}

int main() {
	ifstream fin;
	fin.open("/NESPA/sapiens.txt");
	
	string str;
	getline(fin, str);
	
	char ch;
	while (fin.get(ch)) {
		if (ch == '
') continue;
		cards.push_back(ch);
	}
	
	int N;
	cin >> N;
	
	Loop(N) {
		cin >> str;
		cin >> r1 >> r2;
		
		if (str == "report" && r1 > cards.size()) cout << "NONE" << endl;
		if (r1 > cards.size()) continue;
		if (r2 > cards.size()) r2 = cards.size();
		
		switch (str[1]) {
			case 'r' : frontF(); 	break;
			case 'a' : backF(); 	break;
			case 'u' : cutF(); 		break;
			case 'o' : doubleF(); 	break;
			case 'l' : flipF(); 	break;
			case 'e' : reportF(); 	break;
		}
	}
	fin.close();
	
	return 0;
}