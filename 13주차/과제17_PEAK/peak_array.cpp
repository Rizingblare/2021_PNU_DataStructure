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
int time[1000002];
priority_queue <P,vector<P>,cmp1> seg_list;

void peak_input();
void peak_record();
void peak_output();

int main(){
    peak_input();

    peak_record();

    peak_output();
return 0;
} // end of main()

void peak_input(){

    ifstream cin("03.inp");

    cin >> N;

    P tmp;
    for (int i = 0; i < N; i++){
        cin >> tmp.first >> tmp.second;
        seg_list.push(tmp);
    }

} // end of peak_input()

void peak_record(){

    P tmp;

    while (!(seg_list.empty())){
        tmp = seg_list.top();
        for (int i = tmp.first; i < tmp.second; i++){
            time[i]++;
        }
        seg_list.pop();
    }

    for (int i = 0; i<1000001; i++){
        if (time[i]) cout << "i = " << i << ", time[i] = " << time[i] << endl;
    }

} // end of peak_record()

void peak_output(){

    int peak=0;
    int max_peak=0;

    int left=0;
    int right=0;

    int max_left=0;
    int max_right=0;

    int isPeak = 0;

    for (int i = 1; i<=1000000; i++){
        if (!isPeak){
            if (time[i] >= peak){
                cout << "time[i] =" << time[i] << endl;
                if (time[i] > peak)
                    isPeak = 1;
                else if (time[i] == peak)
                    isPeak = 2;
                peak = time[i];
                left = i;
            }
        }
        if (isPeak){
            if (time[i] == peak) continue;
            else if (time[i] > peak){
                if (time[i] > peak)
                    isPeak = 1;
                peak = time[i];
                left = i;
            }
            else {
                right = i;
                if (isPeak = 2){
                    if ((max_right - max_left) < (right - left)){
                        max_left = left;
                        max_right = right;
                    }
                    else if ((max_right - max_left) == (right - left)){
                        if (max_left < left){
                            max_left = left;
                            max_right = right;
                        }
                    }
                }
                isPeak = 0;
            }

        }

    }

    cout << max_left << " " << max_right << endl;
}
