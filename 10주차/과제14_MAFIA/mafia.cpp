#include <iostream>
#include <string>
#include <list>

using namespace std;

class M_Info{
public:
    string name;
    string boss_name;
    list <M_Info>::iterator bossP;
    int depth;
    int child;
} tmpInfo;

void M_input();
void make_M_tree();
void set_root(string);
void set_depth();
void set_child();
void M_output();

bool M_Rank(M_Info m1, M_Info m2){
    if (m1.child == m2.child){
        if (m1.depth == m2.depth) return m1.name < m2.name;
        return m1.depth < m2.depth;
    }
    return m1.child > m2.child;
} // end of M_Rank()


int N;
list <M_Info> member_list;


int main(){

    M_input();

    make_M_tree();

    set_depth();

    set_child();

    member_list.sort(M_Rank);

    M_output();

    return 0;
} // end of main()

void M_input(){

    cin >> N;

    for (int i = 1; i < N; i++){
        cin >> tmpInfo.name >> tmpInfo.boss_name;
        member_list.push_back(tmpInfo);
    }
} // end of M_input()

void make_M_tree(){
    for (auto &i : member_list){
        string myBoss = i.boss_name;
        if (myBoss == "NULL") break;

        i.bossP = member_list.begin();
        for (auto j : member_list){
            if (j.name == myBoss) break; /// iter가 자신(i)의 보스를 가리킬 때
            (i.bossP)++;
        }
        if (i.bossP == member_list.end()){ /// list를 순회하고도 자신의 boss를 찾지 못했을 때
            set_root(myBoss);
            (i.bossP)--;
        }
    }
} // end of make_M_tree()

void set_root(string boss){
    tmpInfo.boss_name="NULL";
    tmpInfo.name = boss;
    member_list.push_back(tmpInfo);
} // end of set_root()

void set_depth(){
    for (auto &i : member_list){
        int myDepth = 0;
        auto myPointer = i;
        while(myPointer.boss_name!="NULL"){
            myPointer = *(myPointer.bossP);
            myDepth++;
        }
        i.depth = myDepth;
    }
} // end of set_depth()

void set_child(){
    for (auto i : member_list){
        auto myPointer = i;
        while(myPointer.boss_name!="NULL"){
            auto& myBoss = *(myPointer.bossP);
            myBoss.child++;
            myPointer = myBoss;
        }
    }
} // end of set_child()

void M_output(){
    for (auto i : member_list)
        cout << i.name << endl;
} // end of M_output()
