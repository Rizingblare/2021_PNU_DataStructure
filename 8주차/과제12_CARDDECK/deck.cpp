#include <iostream>
#include <deque>
#include <list>
#include <iterator>

#define FOR(N) for (int i = 1; i<=N; i++)
using namespace std;

class MixInfo{
public:
    MixInfo():shuf(0),cut(0),cutB(0),cutE(0){}
    bool shuf;
    bool cut;
    int cutB;
    int cutE;
};

void input();
void cardMix();
void output();

int n,k;
deque <MixInfo> oper_list;
list <int> deck;

int main(){
    input();

    cardMix();

    output();
return 0;
} // end of main()

void input(){
    cin >> n >> k;
    FOR(n){ deck.push_back(i); }
    FOR(k){
        MixInfo tmpC;
        string tmpS;
        int tmpB,tmpE;

        cin >> tmpS;
        if (tmpS == "Shuffle") tmpC.shuf = 1;
        else if (tmpS == "Cut") {
            tmpC.cut = 1;
            cin >> tmpB >> tmpE;
            tmpC.cutB = tmpB;
            tmpC.cutE = tmpE;
        }
        oper_list.push_back(tmpC);
    }
} // end of input()

void cardMix(){
    while (!oper_list.empty()){
        MixInfo nowC = oper_list.front();
        oper_list.pop_front();

        if (nowC.shuf){
            auto it1 = deck.begin(); it1++;
            auto it2 = deck.begin(); advance(it2,n/2);
            auto itE = deck.begin(); advance(itE,n-1);
            while (it2 != itE) deck.splice(it1++,deck,it2++);
        }
        else if (nowC.cut){
            auto it1 = deck.begin(); advance(it1,nowC.cutB-1);
            auto it2 = deck.begin(); advance(it2,nowC.cutE);
            auto itE = deck.begin(); advance(itE,n);
            deck.splice(itE,deck,it1,it2);
        }
    }
} // end of cardMix()

void output(){
    auto it = deck.begin(); cout << *it <<" ";
    advance(it,n/2-1); cout << *it <<" ";
    advance(it,n/2); cout << *it <<" ";
} // end of output()
