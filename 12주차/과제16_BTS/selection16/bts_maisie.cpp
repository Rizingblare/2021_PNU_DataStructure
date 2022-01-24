#include <bits/stdc++.h>
using namespace std;

struct data{
    data(string s, string l = "", string r = "", int d = 1)
        :str(s), Ll(l), Rl(r), depth(d){}
    string str; string Ll; string Rl; int depth;
};
vector<data> bts;
struct Find{
    string str;
    bool operator()(data tmp) {
        return (tmp.str == str);
    }
};
int fdata(string instr){
    Find name;
    name.str = instr;
    auto iter = find_if(bts.begin(), bts.end(), name);
    int dis = distance(bts.begin(), iter); return dis;
}
int calldep = 1;
void link(string instr, int tmp){
    calldep++;
    if(instr > bts[tmp].str){
        if(bts[tmp].Rl == ""){
            bts[tmp].Rl = instr;
            bts.back().depth = calldep;
            calldep--; return;
        }
        else link(instr, fdata(bts[tmp].Rl));
    }
    else if(instr < bts[tmp].str){
        if(bts[tmp].Ll == ""){
            bts[tmp].Ll = instr;
            bts.back().depth = calldep;
            calldep--; return;
        }
        else link(instr, fdata(bts[tmp].Ll));
    }
    calldep--; return;
}
void Add(){
    string str; cin >> str;
    if(bts.empty()) bts.push_back(data(str));
    else{
        if(fdata(str) == bts.size()){
            bts.push_back(data(str));
            link(str, 0);
        }
    }
}
void flow(bool st, int tmp, int deli){
    if(bts[deli].Ll == "" && bts[deli].Rl == ""){
        for(auto &i : bts){
            if(i.Ll == bts[deli].str) i.Ll = "";
            else if(i.Rl == bts[deli].str) i.Rl = "";
        }
        bts.erase(bts.begin()+deli);
        return;
    }
    else{
        if(st){
            if(bts[tmp].Rl == ""){
                for(auto &i : bts){
                    if(i.Ll == bts[deli].str) i.Ll = bts[tmp].str;
                    else if(i.Rl == bts[deli].str) i.Rl = bts[tmp].str;
                    else if(i.Ll == bts[tmp].str) i.Ll = bts[deli].str;
                    else if(i.Rl == bts[tmp].str) i.Rl = bts[deli].str;
                }
                string temp_name  = bts[tmp].str;
                bts[tmp].str = bts[deli].str;
                bts[deli].str = temp_name;
                flow(st, fdata(bts[tmp].Ll), tmp);
            }
            else flow(st, fdata(bts[tmp].Rl), deli);
        }
        else{
            if(bts[tmp].Ll == ""){
                for(auto &i : bts){
                    if(i.Ll == bts[deli].str) i.Ll = bts[tmp].str;
                    else if(i.Rl == bts[deli].str) i.Rl = bts[tmp].str;
                    else if(i.Ll == bts[tmp].str) i.Ll = bts[deli].str;
                    else if(i.Rl == bts[tmp].str) i.Rl = bts[deli].str;
                }
                string temp_name  = bts[tmp].str;
                bts[tmp].str = bts[deli].str;
                bts[deli].str  = temp_name;
                flow(st, fdata(bts[tmp].Rl), tmp);
            }
            else flow(st, fdata(bts[tmp].Ll), deli);
        }
    }
    return;
}
void Delete(){
    string str; cin >> str;
    int dis = fdata(str);
    if(dis != bts.size()){
        if(fdata(bts[dis].Ll) != bts.size()) flow(true, fdata(bts[dis].Ll), dis);
        else flow(false, fdata(bts[dis].Rl), dis);
    }
}
void Depth(){
    int k; cin >> k;
    vector<string> dep_k;
    for(auto &i : bts) if(i.depth == k) dep_k.push_back(i.str);
    if(dep_k.empty()) cout << "NO";
    else{
        sort(dep_k.begin(), dep_k.end());
        for(auto &i : dep_k) cout << i << " ";
    }
    cout << endl;
}
void Leaf(){
    vector<string> l_v;
    for(auto &i : bts){
        if(i.Ll == "" && i.Rl == "") l_v.push_back(i.str);
    }
    sort(l_v.begin(), l_v.end());
    for(auto &i : l_v) cout << i << " ";
    cout << endl;
}
int main(){
    string str; cin >> str;
    while(str != "quit"){
        if(str == "+") Add(); else if(str == "-") Delete(); else if(str == "depth") Depth(); else if(str == "leaf") Leaf();
        cin >> str;
    }
}
