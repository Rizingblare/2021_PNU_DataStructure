#include <iostream>
#include <string>
#include <vector>

#define FORI for(int i=0;i<n;i++)

using namespace std;

int n;
int k1,k2;
vector <vector<string>> func_list;
vector <string> func_input;
vector <string> resultVector;
string MAIN = "M";

void input();
void add_func_log(string);
void output();
bool isUpper(string s){ if (*(s.c_str())>=65&&*(s.c_str())<=90) return 1; }

int main(){

    input();

    add_func_log(MAIN);

    // for (auto i:resultVector) {cout<<i<<endl;}

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
    } // end of for()

    /*
    for (auto i : func_list){
        cout << "*";
        for (auto j: i)
            cout << j << " ";
        cout << endl;
    }
    */
}

void add_func_log(string s){
    for (auto i:func_list){
        if(i.at(0)==s){
            for (auto j:i){
                if (j=="$") return;
                if (j!=s){
                    if (isUpper(j))add_func_log(j);
                    else resultVector.push_back(s+"-"+j);
                }
            }
        }
    }
} //$는 벡터 추가 안하도록 수정해야함, 대문자는 -로 결합 안하도록 수정해야함, 재귀함수로 구현되도록 수정해야함.

void output(){
    cout<<resultVector.at(k1)<<endl;
    cout<<resultVector.at(k2)<<endl;
}
