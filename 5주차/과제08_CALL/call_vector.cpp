#include <iostream>
#include <string>
#include <vector>

#define FORI for(int i=0;i<n;i++)

using namespace std;

int n;
int k1,k2;
vector <vector<string>> func_list;
vector <string> func_input;
vector <string> func_log;
int open_func[300];
bool exit_;
string MAIN = "M";

void input();
void add_func_log(string);
void output();
bool isUpper(int s){ if (s>='A'&&s<='Z') return 1; else return 0; }

int main(){

    input();

    add_func_log(MAIN);

    output();
}//end of main()

void input(){
    cin >> n;

    cin >> k1 >> k2;

    for (int i=0; i<n; i++){
        string s;

        while(s!="$"){
            cin >> s;

            func_input.push_back(s);

        } // end of while()

        func_list.push_back(func_input);
        func_input.clear();
        vector<string>().swap(func_input);
    } // end of for()
}

void add_func_log(string s){
    if (exit_) return;
    int s_int=*(s.c_str());
    open_func[s_int]++;
    if (open_func[s_int]>1) {exit_++; return;}

    for (auto i:func_list){
        if(i.at(0)==s){
            for (auto j:i){
                int j_int=j.at(0);
                //cout<<"s = "<<s<<" / s_int = "<<s_int<<" / j = "<<j<<" / j.at(0) = "<<j.at(0)<<" / j_int = "<<j_int<<endl;
                if (j=="$") {open_func[s_int]--; return;}
                if (j!=s){
                    if (isUpper(j_int))add_func_log(j);
                    else func_log.push_back(s+"-"+j);
                }
            }//end of for(auto j:i)
        }
    }//end of for (auto i:func_list)
}

void output(){
    if (exit_) {cout<<"DEADLOCK"; return;}
    int item_num = func_log.size();

    //cout<<item_num<<endl;

    if (k1>=1&&k1<=item_num) cout << func_log.at(k1-1) << endl;
    else cout<<"NONE"<<endl;

    if (k2>=1&&k2<=item_num) cout << func_log.at(k2-1) << endl;
    else cout<<"NONE"<<endl;

    //int tmp=0;
    //for(auto i : func_log) {cout<<endl<<tmp+1<<" : "<<i;tmp++;}
}
