#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

vector<int> bd(2000001);
vector<int> result;

int main()
{
	int num;
	cin >> num;
	int s, v, h;

	int start = 50000000;
	int finish = 0;

	for (int i = 0; i < num; i++) {
		cin >> s >> v >> h;

		if (start > s) {
			start = s;
		}

		if (finish < s + h) {
			finish = s + h;
		}
		
		for (int j = s; j < s + h; j++) {
			if (bd[j] < v) {
				bd[j] = v;
			}
		}
	}

	int past=0;
	int now=0;
	int garo = 1;

	result.push_back(start);

	for (int i = start; i < finish+1; i++) {
		now = bd[i];
		if (past != now) {
			result.push_back(garo);
			result.push_back(now - past);
			garo = 1;
		}
		else garo++;
		past = bd[i];
	}

	result.erase(result.begin() + 1);
	
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << ' ';
	}
}