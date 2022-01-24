#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>

using namespace std;

#define ITER1 auto it1 = seq.begin(); advance(it1,b-1);
#define ITER2 auto it2 = seq.begin(); advance(it2,e);

class DNA{
public:
    list <char> seq;
    void fro (int b, int e){
        auto itb = seq.begin(); ITER1; ITER2;
        seq.splice(itb,seq,it1,it2);
    }
    void bac (int b, int e){
        auto ite = seq.end(); ITER1; ITER2;
        seq.splice(ite,seq,it1,it2);
    }
    void cut (int b, int e){
        ITER1; ITER2;
        seq.erase(it1,it2);
    }
    void dou (int b, int e){
        ITER1; ITER2;
        seq.insert(it2,it1,it2);
    }
    void fli (int b, int e){
        ITER1; ITER2;
        reverse(it1,it2);
    }
    void rep (int b, int e){
        ITER1; ITER2;
        while (it1 != it2) {cout << *it1; it1++;}
        cout << endl;
    }
} D1;

class Info{
public:
    string s;
    int b,e;
} tmp;
vector <Info> infoList;

void link_sapiens();
void manu_input();
void manu_output();
int match_Code(string s){
    vector <string> oper {"front","back","cut","double","flip","report"};
    int code = 0;

    for (auto i : oper){
        if (s==i) return code;
        else code++;
    }
}

int main(){

    link_sapiens();

    manu_input();

    manu_output();

}

void link_sapiens(){

    ifstream fin("/NESPA/sapiens.txt");

    char c;
    fin.ignore(65536,'\n');
    while (fin.get(c)) if(c!='\n')D1.seq.push_back(c);
    fin.close();
}

void manu_input(){
    int n;
    cin >> n;

    string s;
    int b,e;
    for (int i=0; i<n; i++){
        cin >> s >> b >> e;
        tmp.s = s;
        tmp.b = b;
        tmp.e = e;
        infoList.push_back(tmp);
    }
}

void manu_output(){
    for (auto i : infoList){
        int code = match_Code(i.s);
        int siz = D1.seq.size();
        if (i.e > siz) {
            if (i.b > siz) {
                if (code == 5) cout << "NONE" << endl;
                continue;
            }
            i.e = siz;
        }

        switch (code) {
            case 0: D1.fro(i.b,i.e); break;
            case 1: D1.bac(i.b,i.e); break;
            case 2: D1.cut(i.b,i.e); break;
            case 3: D1.dou(i.b,i.e); break;
            case 4: D1.fli(i.b,i.e); break;
            case 5: D1.rep(i.b,i.e); break;
            default: break;
        }
    }
}
