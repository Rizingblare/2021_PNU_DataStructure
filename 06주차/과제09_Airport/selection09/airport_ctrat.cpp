#include <iostream>
#include <queue>

using namespace std;
int main() {
    int k;
    cin >> k;
    queue<int> tq;
    vector<queue<int>> Qvec;
    for(int i = 0; i < k; i++){
        Qvec.push_back(tq);
        while(1){
            int tmp;
            cin >> tmp;
            if (tmp == 0) break;
            else Qvec.at(i).push(tmp);
        }
    }

    while(1){
        bool flag = false;
        for(int i = 0; i < k; i++){
            if(Qvec.at(i).size() != 0){
                flag = true;
                break;
            }
        }
        if(flag == false) break;

        int prior = 10000;
        int index = 0;
        for(int i = 0; i < k; i++){
            if (prior > Qvec.at(i).front() && !Qvec.at(i).empty()){
                prior = Qvec.at(i).front();
                index = i;
            }
        }
        cout << Qvec.at(index).front() << endl;
        Qvec.at(index).pop();
    }