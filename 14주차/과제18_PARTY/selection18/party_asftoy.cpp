#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;


class Graph {
	int numOfVertex;
	vector<char> vertices;
	vector<char> initialLocation;
	vector<vector<int>> eachDistance;
	vector<vector<char>> abj;
	vector<int> result;

public:
	Graph(int n) : numOfVertex(n) {
		for (int i = 0; i < 3; i++) {
			char loc; cin >> loc;
			initialLocation.push_back(loc);
		}
		for (int i = 0; i < numOfVertex; i++) {
			vector<char> abjVertex;
			int index = 0;
			while (true) {
				char v; cin >> v;
				if (index == 0) vertices.push_back(v);
				if (v == '$') break;
				abjVertex.push_back(v);
				index++;
			}
			abj.push_back(abjVertex);
		}
		sort(vertices.begin(), vertices.end());
		sort(abj.begin(), abj.end());
		calcEachDistance();

	} // end of Constructor(int n)

	vector<int> bfs(char v) {
		vector<int> distance(numOfVertex, -1);
		queue<char> q;

		int idx = find(vertices.begin(), vertices.end(), v) - vertices.begin();
		distance.at(idx) = 0;
		q.push(v);
		

		while (!q.empty()) {
			char node = q.front();
			q.pop();

			int nodeIdx = find(vertices.begin(), vertices.end(), node)- vertices.begin();

			for (int i = 1; i < abj[nodeIdx].size(); i++) {
				char nextNode = abj.at(nodeIdx).at(i);

				int nextIdx = find(vertices.begin(), vertices.end(), nextNode) - vertices.begin();

				if (distance.at(nextIdx) == -1) {
					distance.at(nextIdx) = distance.at(nodeIdx) + 1;
					q.push(nextNode);
				}
			}
		}
		return distance;
	} // end of bfs(char v)


	void calcEachDistance() {
		for (int i = 0; i < 3; i++)
			eachDistance.push_back(bfs(initialLocation.at(i)));
	} // end of calcEachDistance()

	void makeParty() {
		vector<int> value(3);
		for (int i = 0; i < numOfVertex; i++) {
			value.push_back(eachDistance.at(0).at(i));
			value.push_back(eachDistance.at(1).at(i));
			value.push_back(eachDistance.at(2).at(i));
			int maxValue = *max_element(value.begin(), value.end());
			result.push_back(maxValue);
			value.clear();
		}
	} // end of getPartyTime()

	void partyTime() {
		makeParty();
		int minValue = *min_element(result.begin(), result.end());
		int minIdx = min_element(result.begin(), result.end()) - result.begin();
		char v = vertices.at(minIdx);

		if (minValue > 1) {
			minValue = minValue + (minValue - 1) * 2;
		}
		else if (minValue == 0) {
			minValue = -1;
			v = '@';
		}
		cout << v << endl << minValue;
	}

}; // end of class Graph

int main(void) {
	int numOfVertex; cin >> numOfVertex;
	Graph city = Graph(numOfVertex);
	city.partyTime();
	return 0;

} // end of main(void)