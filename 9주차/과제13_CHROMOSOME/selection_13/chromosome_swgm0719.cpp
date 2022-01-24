#include <bits/stdc++.h>
using namespace std;
list <char> dna;
int i, j;
auto first = dna.begin();
auto A(first), B(first);
list <char> cop;
vector <string> func = {"front", "back", "cut", "double", "flip", "report"};

void file_input(){
    ifstream in("/NESPA/sapiens.txt");
    string line;
    getline(in, line);
    char one;
    while(!in.eof()){
        in >> one;
        if (in.fail()) break;
        dna.push_back(one);
    }
    in.close();
}

void Double() {
    cop.clear();
    copy(A, B, back_inserter(cop));
    dna.splice(B, cop);
}

void Report() {
    cop.clear();
    copy(A, B, back_inserter(cop));
    string c = "";
    for(auto w:cop){
        c+=w;
    }
    cout << c << endl;
}

int main(){
    file_input();
    int N;
    cin >> N;
    string opr;
    for(int k=0; k < N; k++){
        cin >> opr;
        cin >> i >> j;
        A = next(first, i  );
        B = next(first, j+1);
        int code = find(func.begin(), func.end(), opr)-func.begin();
        switch (code) {
            case 0 :  dna.splice(dna.begin(), dna, A, B);  break;
            case 1 :  dna.splice(dna.end(), dna, A, B);   break;
            case 2 :  dna.erase(A, B);   break;
            case 3 :  Double(); break;
            case 4 :  reverse(A, B);  break;
            case 5 :  Report(); break;
        }
    }
}
