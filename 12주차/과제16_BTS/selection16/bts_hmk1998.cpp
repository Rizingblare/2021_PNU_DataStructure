#include <iostream>
#include <queue>
#include <array>
#include <list>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

typedef struct{
    string com01; string com02;
} TreeCommand;

struct Node{
    array<int,2> sub;
    string temp;
    array<list<struct Node>::iterator,3> idx;
};
typedef struct Node Node;

list<Node> NodeTmp;
list<Node>::iterator Iter;
queue<TreeCommand> InComd;
array<string,5> Table = {"+","-","depth","leaf","quit"};
int Ck;

void CommandIn();
void DoTreeTask();
void DoPlus (string str,list<Node>::iterator id);
void DoMinus(string str,list<Node>::iterator id);
void DoDepth(int n,list<Node>::iterator id);
void DoLeaf (list<Node>::iterator id);

int main(){
    CommandIn();
    DoTreeTask();
    return 0;
}

void CommandIn(){
    string tmp00, tmp01;
    TreeCommand tmp03;
    int id;
    do{
        getline(cin,tmp00);
        istringstream strbuffer(tmp00);
        strbuffer >> tmp00;
        tmp03.com02 = "NOT";
        id = find(Table.begin(),Table.end(),tmp00) - Table.begin();
        switch(id){
            case 0:
            case 1:
            case 2: strbuffer >> tmp01;   tmp03.com02 = tmp01;
            case 3:
            case 4: tmp03.com01 = tmp00;
        }
        InComd.push(tmp03);
    }while(tmp00!="quit");
}

void DoTreeTask(){
    int tmp00; Node nd;
    string tmp01;
    while(!InComd.empty()){
        tmp00 = find(Table.begin(),Table.end(),InComd.front().com01) - Table.begin();
        Iter=NodeTmp.begin();   tmp01=InComd.front().com02;
        if(NodeTmp.empty()){
            if(tmp00==0){
                nd.temp=tmp01;  nd.sub[0]=nd.sub[1]=0;  nd.idx[2]=Iter;
                NodeTmp.push_back(nd);
            }
            InComd.pop();
            continue;
        }
        switch(tmp00){
            case 0: DoPlus(tmp01,Iter);
                    break;
            case 1: DoMinus(tmp01,Iter);
                    break;
            case 2: Ck=0; DoDepth(stoi(tmp01),Iter);
                    if(Ck==0) cout << "NO";
                    cout << endl;
                    break;
            case 3: DoLeaf(Iter); 
                    cout << endl;
            case 4: break;
        }
        InComd.pop();
    }
}

void DoPlus(string str,list<Node>::iterator id){
    Node nd01; int k1;
    nd01.temp=str;  nd01.sub[0]=nd01.sub[1]=0;  nd01.idx[2]=id;
    if(id->temp==str);
    else{
        k1 = id->temp>str? 0:1;
        if(id->sub[k1]==0){
            NodeTmp.push_back(nd01);
            id->sub[k1]=1;
            Iter=NodeTmp.end();  id->idx[k1]=--Iter;
        }
        else DoPlus(str,id->idx[k1]);
    }
}
void DoMinus(string str,list<Node>::iterator id){
    int k1;
    if(id->temp!=str){
        k1=id->temp>str? 0:1;
        if(id->sub[k1]==1) DoMinus(str,id->idx[k1]);
    }
    else{
        if(id->sub[0]+id->sub[1]==0){
            if(id!=NodeTmp.begin()){
                k1=id==(id->idx[2]->idx[0])? 0:1;
                id->idx[2]->sub[k1]=0;
            }
            NodeTmp.erase(id);
        }
        else{
            k1=id->sub[0]==1? 0:1;  Iter=id->idx[k1];
            while(Iter->sub[1-k1]==1) Iter=Iter->idx[1-k1];
            id->temp=Iter->temp;
            DoMinus(Iter->temp,Iter);
        }
    }
}
void DoDepth(int n,list<Node>::iterator id){
    switch(n){
        case  1: cout << id->temp << " ";    Ck=1;
                 break;
        default: if(id->sub[0]==1) DoDepth(n-1,id->idx[0]);
                 if(id->sub[1]==1) DoDepth(n-1,id->idx[1]);
    }
}
void DoLeaf(list<Node>::iterator id){
    switch(id->sub[0]+id->sub[1]){
        case  0 : cout << id->temp << " ";
                  break;
        default : if(id->sub[0]==1) DoLeaf(id->idx[0]);
                  if(id->sub[1]==1) DoLeaf(id->idx[1]);
    }
}