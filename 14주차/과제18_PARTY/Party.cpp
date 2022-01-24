#include <iostream>
#include <vector>
#include <deque>
#include <array>

using namespace std;

struct Info{
    bool visit;
    int dist;
};

class Graph{
public:
    vector<vector<char>> adjVec;

    Graph() {adjVec.resize(26);}

    void BFS(char);
} graph1;

void party_input();
void party_research();
void party_possible_check();
void party_location_check();
void party_output();

int N;
array <array<Info,26>,26> placeInfo;
char TRIO[3];
bool Success = 0;
int min_dist = 1234567890;
char min_loc = 0;

void Graph::BFS(char startVertex){
        deque <char> que;
        que.push_back(startVertex);

        int svI = startVertex-'a';        /// svI (startVertexIndex)
        placeInfo[svI][svI].visit = true;

        int dist = 1;
        while(!que.empty()){
            int sz = que.size();

            for (int i = 0; i < sz; i++){
                char nowVertex = que.front();
                int nvI = nowVertex - 'a';      /// nvI (nowVertexIndex)
                que.pop_front();

                for (auto adj : adjVec[nvI]){
                    int adjI = adj-'a';         /// adjI (adjacentVertexIndex)

                    if (placeInfo[svI][adjI].visit == false){
                        que.push_back(adj);
                        placeInfo[svI][adjI].visit = true;
                        placeInfo[svI][adjI].dist = dist;
                    }
                }
            }
            dist += 3;
        }
}

int main(){
    party_input();

    party_research();

    party_output();

return 0;
} // end of main()

void party_input(){

    cin >> N;

    for (int i=0;i<3;i++)
        cin >> TRIO[i];

    char tmp;
    char myVertex;
    int mvI;        /// mvI (myVertexIndex)
    for (int i=0;i<N;i++){
        cin >> tmp;
        if (tmp=='$') continue;
        else {
            myVertex = tmp;
            mvI = myVertex - 'a';
        }

        while(1){
            cin >> tmp;
            if (tmp=='$') break;
            else graph1.adjVec[mvI].push_back(tmp);
        }
    }
} // end of party_input()

void party_research(){

    for (int i = 0; i<3; i++)
        graph1.BFS(TRIO[i]);

    party_possible_check();

    if (Success)
        party_location_check();

} // end of party_research()

void party_possible_check(){

    for (int alpha = 0; alpha<26; alpha++){
        int user = 0;

        for (int i = 0; i<3; i++){
            int tvI = TRIO[i]-'a';        /// tvI (trioVertexIndex)
            if (placeInfo[tvI][alpha].visit==true)
                user++;
        }
        if (user == 3){Success = 1; break;}
    }

} // end of party_possible_check()

void party_location_check(){

    for (int alpha = 0; alpha<26; alpha++){
        int dist = 0;
        int user = 0;
        for (int i = 0; i<3; i++){
            int tvI = TRIO[i]-'a';        /// tvI (trioVertexIndex)
            if (placeInfo[tvI][alpha].visit==true)
                user++;
            if (placeInfo[tvI][alpha].dist > dist)
                dist = placeInfo[tvI][alpha].dist;
        }

        if (user == 3){
            if (dist < min_dist) {min_dist = dist; min_loc = alpha +'a';}
        }
    }
} // end of party_location_check()

void party_output(){
    if (Success)
        cout << min_loc << endl << min_dist << endl;
    else
        cout << "@" << endl << -1 << endl;
} // end of party_output()
