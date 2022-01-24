#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <string>
#include <map>
#include <tuple>
#include <algorithm>

using namespace std;

bool isCompleteGraph = true;
vector<char> firstVertex;
vector<char> allVertex;
map<char,tuple<int,int,int>> vertexTime;
map<char,list<char>> adjacentList;

void read() {
    int n;
    char v1,v2;
    cin >> n;
    for (int i =0;i<3;i++) {
        cin >>v1;
        firstVertex.push_back(v1);
    }
    for (int i=0;i<n;i++) {
        list<char> mini;
        cin >> v1;
        allVertex.push_back(v1);
        do {
            cin >>v2;
            if (v2 != '$') mini.push_back(v2);
        }
        while (v2 != '$');
        adjacentList.insert({v1,mini});
    }
}

void solve() {
    tuple<int,int,int> minitime = make_tuple(0,0,0);
    sort(allVertex.begin(),allVertex.end());
    for (int i=0;i<allVertex.size();i++) vertexTime.insert({allVertex[i],minitime});
    for (int i=0;i<3;i++) {
        string isVisit = "";
        queue<char> bfs;
        int plusTime = 3;
        isVisit += firstVertex[i];
        bfs.push(firstVertex[i]);
        while (!bfs.empty()) {
            auto it = adjacentList.find(bfs.front());
            for (auto j : it->second) {
                if (find(isVisit.begin(),isVisit.end(),j) != isVisit.end()) continue;
                isVisit += j;
                bfs.push(j);
                if (bfs.front() == firstVertex[i]) plusTime = 1;
                else plusTime = 3;
                switch (i) {
                case 0 :
                    get<0>(vertexTime.find(j) -> second) = get<0>(vertexTime.find(bfs.front()) -> second) + plusTime;
                    break;
                case 1 :
                    get<1>(vertexTime.find(j) -> second) = get<1>(vertexTime.find(bfs.front()) -> second) + plusTime;
                    break;
                case 2 :
                    get<2>(vertexTime.find(j) -> second) = get<2>(vertexTime.find(bfs.front()) -> second) + plusTime;
                    break;
                default:
                    break;
                }
            }
            bfs.pop();
        }
        if (isVisit.length() < allVertex.size()) {
            isCompleteGraph = false;
            break;
        }
    }
}

void print() {
    if (isCompleteGraph) {
        int minTime = 100;
        char party;
        for (int i=0;i<allVertex.size();i++) {
            if (minTime > max({get<0>(vertexTime.find(allVertex[i])-> second), get<1>(vertexTime.find(allVertex[i])-> second), get<2>(vertexTime.find(allVertex[i])-> second)})) {
                minTime = max({get<0>(vertexTime.find(allVertex[i])-> second), get<1>(vertexTime.find(allVertex[i])-> second), get<2>(vertexTime.find(allVertex[i])-> second)});
                party = allVertex[i];
            }
        }
        cout << party << endl << minTime;
    }
    else cout << "@\n-1";
}

int main() {
    read();
    solve();
    print();
}