#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

#define P pair<int,int>

struct cmp1{
    bool operator()(P l,P r){
        return l.first > r.first;
    }
};

int N;
int time[1000001];
priority_queue <P,vector<P>,cmp1> seg_list;

void peak_input();
void peak_record();
void peak_output();

int main(){
    peak_input();

    //peak_record();

   //peak_output();
return 0;
} // end of main()

void peak_input(){

    ifstream cin("01.inp");

    cin >> N;

    P tmp;
    for (int i = 0; i < N; i++){
        cin >> tmp.first >> tmp.second;
        seg_list.push(tmp);
    }


    for (int i = 0; i < N; i++){
        tmp = seg_list.top();
        cout << tmp.first << " " << tmp.second << endl;
        seg_list.pop();
    }


} // end of peak_input()
