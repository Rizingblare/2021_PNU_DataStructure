#include <bits/stdc++.h>
using namespace std;

int N;
vector<string> onlyHpara;
vector<set<string>> vecKmer;
vector<pair<float, pair<int,int>>> result;

void read_data();
void solve();
void print_data();

string Only_Hangul(string p);
void k_mer(string str);
float get_sim(set<string> &si, set<string> &sj);

int main() {
    read_data();
    solve();
    print_data();
}

void read_data() {
    cin >> N;
    string word, sentence;
    for (int i = 0; i < N; ++i) {
        sentence.clear();
        while (true){
            cin >> word;
            if(word=="$") break;
            sentence.append(Only_Hangul(word));
        }
        onlyHpara.push_back(sentence);
    }
}

void solve() {
    for (const auto& i:onlyHpara) {
        k_mer(i);
    }
    float sim;
    pair<int,int> ind;
    for (int i = 0; i < vecKmer.size()-1; ++i) {
        for (int j = i+1; j < vecKmer.size(); ++j) {
            sim = get_sim(vecKmer[i], vecKmer[j]);
            ind = {i + 1, j + 1};
            result.emplace_back(sim,ind);
        }
    }
}

float get_sim(set<string> &si, set<string> &sj) {
    set<string> s_inter,s_union;
    set_intersection(si.begin(), si.end(), sj.begin(),sj.end(), inserter(s_inter, s_inter.end()));
    set_union(si.begin(), si.end(), sj.begin(),sj.end(), inserter(s_union, s_union.end()));

    if(s_union.empty()) return 0L;
    return ((float)s_inter.size() / s_union.size());
}

bool mysort(pair<float, pair<int,int>> p1, pair<float, pair<int,int>> p2){
    if(p1.first==p2.first){
        return p1.second<p2.second;
    }else return p1.first>p2.first;
}

void print_data() {
    sort(result.begin(),result.end(), mysort);
    cout << result[0].second.first << " " << result[0].second.second << endl;
}

string Only_Hangul(string p ){
    string Ohan  ;
    for(int i=0; i<p.size(); i++) {
        if((p[i] & 0x80) != 0) {
            Ohan.push_back(p[i]);
        }
    } // end of for(i)
    return ( Ohan ) ;
} // end of ONly_Hangul( )

void k_mer(string str){
    if(str.empty()){
        vecKmer.emplace_back();
        return;
    }
    set<string> kmer;
    for (int i = 0; i < str.size()-3; i=i+3) {
        kmer.insert(str.substr(i,6));
    }
    vecKmer.push_back(kmer);
}
