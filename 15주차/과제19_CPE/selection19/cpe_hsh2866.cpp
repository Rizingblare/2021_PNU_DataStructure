#include <bits/stdc++.h>
using namespace std;

vector<string> P_vec;
vector<set<string>> Kmer_sets;

void inputOnlyKor(int n){
    string str;
    for(int i=0; i<n; i++) {
        string k_str;
        while(1) {
            cin >> str;
            if (str.compare("$") == 0) break;
            int str_len = str.size();
            for(int i=0; i < str_len; i++) {
                if((str[i] & 0x80) != 0) {
                    k_str.push_back(str[i]);
                }
            }
        }
        P_vec.push_back(k_str);
    }
}

void getKmerSet(int n){
    set<string> kmer_set;
    for (auto k : P_vec){
        int kmer_len = k.size();
        for (int i = 0; i < kmer_len - 5; i += 3){
            kmer_set.insert(k.substr(i, 6));
        }
        Kmer_sets.push_back(kmer_set);
        kmer_set.clear();
    }
}

float getSim(int i, int j){
    float p_sim = 0.0f;
    set<string> p1 = Kmer_sets[i], p2 = Kmer_sets[j];
    set<string> p_union, p_common;
    set_union(p1.begin(), p1.end(), p2.begin(), p2.end(), inserter(p_union, p_union.begin()));
    set_intersection(p1.begin(), p1.end(), p2.begin(), p2.end(), inserter(p_common, p_common.begin()));
    if (p_common.size() != 0)  p_sim = (float) p_common.size() / p_union.size();
    return p_sim;
}

pair<int, int> findCopyPair(int n){
    pair<int, int> copy_pair;
    float max_sim = 0.0f, p_sim;
    for (int i = 0; i < n-1; i++){
        for (int j = i+1; j < n; j++){
            p_sim = getSim(i, j);
            if (p_sim > max_sim){
                max_sim = p_sim;
                copy_pair = make_pair(i+1, j+1);
            }
        }
    }
    return copy_pair;
}

int main() {
    int n;
    cin >> n;
    inputOnlyKor(n);
    getKmerSet  (n);
    pair<int, int> copyPair = findCopyPair(n);
    cout << copyPair.first << " " << copyPair.second;
}