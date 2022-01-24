#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

void disorder_input();
void disorder_output();

map<set<int>,set<int>> gSet_list;
vector<vector<int>> output_list;

int main(){

    disorder_input();

    disorder_output();
return 0;
} // end of main()

void disorder_input(){

    char tmpC;

    cin >> tmpC;

    while(tmpC != '$'){
        set<int> cur_gSet;
        int gene;
        if (tmpC == 'R'){
            cin >> gene;

            while (gene > 0){
                cur_gSet.insert(gene);
                cin >> gene;
            }

            gSet_list[cur_gSet].insert(gene);
        }
        else if (tmpC == 'Q'){
            cin >> gene;

            while (gene != 0){
                cur_gSet.insert(gene);
                cin >> gene;
            }
            vector<int> tmpV;
            if (gSet_list.count(cur_gSet)==0) tmpV.push_back(0);
            else {
                for (auto w : gSet_list.at(cur_gSet))
                    tmpV.push_back(w);
            }
            output_list.push_back(tmpV);
        }

        cin >> tmpC;
    }

} // end of disorder_input()

void disorder_output(){
    for (auto i : output_list){
        if (i.at(0) == 0) cout << "None" << endl;
        else {
            sort(i.begin(),i.end(),greater<int>());
            for (auto j : i) cout << j << " ";
            cout << endl;
        }
    }
} // end of disorder_output()
