#include <bits/stdc++.h>
using namespace std;

// ÇÑ±Û ÀÎÄÚµù ¹ÙÀÌÆ® ¼ö    // k-mer ÀÇ k
const int KOR_BYTES = 3, MERS = 2;

void input(vector<set<string> > &sets) {
    int N; cin >> N;
    while(N--) {
        string word, tmp;
        
        while(cin >> word && word!="$")
            for(auto &c : word)
                if(c & 0x80) tmp.push_back(c);

        set<string> twomer;
        for(int i=0; i <= (int) tmp.length() / KOR_BYTES - MERS; i++)
            twomer.insert(tmp.substr(KOR_BYTES * i, KOR_BYTES * MERS));

        sets.push_back(twomer);
    }
}

pair<int, int> getMaxSimilar(vector<set<string> > &sets) {
    tuple<double, int, int> maxSim = {0.0, 1, 2};

    for(int i=0;i<sets.size()-1;i++)
    for(int j=i+1;j<sets.size();j++) {
        set<string> uni, intr;

        set_union(sets[i].begin(), sets[i].end(), sets[j].begin(), sets[j].end(), inserter(uni, uni.begin()));
        set_intersection(sets[i].begin(), sets[i].end(), sets[j].begin(), sets[j].end(), inserter(intr, intr.begin()));

        if(uni.size() == 0) continue;
        double result =  (double) intr.size() / (double) uni.size();

        if(get<0>(maxSim) < result) maxSim = {result, i+1, j+1};
    }
    return { get<1>(maxSim), get<2>(maxSim) };
}

int main(){ 
    vector<set<string> > sets;   
    input(sets);
    auto result = getMaxSimilar(sets);
    cout << result.first << ' ' << result.second << '\n';
}