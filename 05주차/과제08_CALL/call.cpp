#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

int n, k1, k2;
vector <string> func_input;
vector <vector<string>> func_list;
vector <string> func_log;
string MAIN = "M";
int open_func[300];
bool finish = 0;

#define REPT(X) for(int i=0;i<X;i++)

void input();
void add_func_log(string s);
int is_upper(char c){if(c>='A'&&c<='Z')return 1;return 0;}
void output();

int main(){

    input();

    add_func_log(MAIN);

    output();
} //end of main( )

void input(){


    cin >> n >> k1 >> k2;

    string tmp;
    REPT(n){
        while(1){
            cin >> tmp;
            if(tmp=="$") break;
            else func_input.push_back(tmp);
        }
        func_list.push_back(func_input);
        func_input.clear();
    }
}//end of input()

void add_func_log(string s){
    if (finish) return;
    if (open_func[s.at(0)]>1) {finish++; return;}
    else open_func[s.at(0)]++;

    for (auto i:func_list){
        if (i.at(0)==s){
            for (auto j:i){
                if (&j==&(i.at(0))) continue;
                if (is_upper(j.at(0))) add_func_log(j);
                else func_log.push_back(s+"-"+j);
            }
        }
    }
    open_func[s.at(0)]--;
}

void output(){
    int log_size = func_log.size();

    if (finish) cout<<"DEADLOCK";
    else {
        if (k1<1||k1>log_size) cout<<"NONE"<<endl;
        else cout<<func_log.at(k1-1)<<endl;

        if (k2<1||k2>log_size) cout<<"NONE";
        else cout<<func_log.at(k2-1);
    }
}
