#include <bits/stdc++.h>
using namespace std;
struct simPair {
    pair<int, int> pr;
    float similarity;
};
struct Compare {
    bool operator()(const simPair& left, const simPair& right) {
        if (left.similarity != right.similarity)
            return (left.similarity < right.similarity) ? true : false;
        if (left.pr.first != right.pr.first)
            return (left.pr.first > right.pr.first) ? true : false;
        return (left.pr.second > right.pr.second) ? true : false;
    }
};
vector<set<string>> kmer;
priority_queue<simPair, vector<simPair>, Compare> pq;

void removePunc(string& text) {
    text.erase(remove_if(begin(text), end(text), [](const char& ch) {
                   return ispunct(ch);
               }),
               end(text));
    text.erase(remove_if(begin(text), end(text), [](const char& ch) {
                   return (ch == ' ') ? true : false;
               }),
               end(text));
    text.erase(remove_if(begin(text), end(text), [](const char& ch) {
                   int num = ch - '0';
                   return (0 <= num && num <= 9) ? true : false;
               }),
               end(text));
}
void makeKmer(const string& text) {
    string temp;
    set<string> tempset;

    int textSize = text.size();
    for (int i = 0; i < textSize - 3; i += 3) {
        temp = text.substr(i, 3) + text.substr(i + 3, 3);
        tempset.insert(temp);
    }
    kmer.push_back(tempset);
}
void calculateSim() {
    set<string> uniset, interset;
    float similarity = 0.0;

    int kmerSize = kmer.size();
    for (int i = 0; i < kmerSize - 1; i++) {
        for (int j = i + 1; j < kmer.size(); j++) {
            set_union(begin(kmer[i]), end(kmer[i]), begin(kmer[j]), end(kmer[j]), inserter(uniset, begin(uniset)));
            set_intersection(begin(kmer[i]), end(kmer[i]), begin(kmer[j]), end(kmer[j]), inserter(interset, begin(interset)));
            similarity = (float)interset.size() / uniset.size();

            pq.push({make_pair(i + 1, j + 1), similarity});
            uniset.clear();
            interset.clear();
        }
    }
}
void printResult() {
    auto top = pq.top();
    cout << top.pr.first << " " << top.pr.second;
}

int main(void) {
    int n;
    vector<string> v;

    cin >> n;
    string p;
    for (int i = 0; i < n; i++) {
        string ss;
        while (1) {
            cin >> p;
            if (p.compare("$") == 0) break;
            int nn = p.size();
            for (int i = 0; i < nn; i++) {
                if ((p[i] & 0x80) != 0) {
                    ss.push_back(p[i]);
                }
            }
        }
        removePunc(ss);
        makeKmer(ss);
    }
    calculateSim();
    printResult();
    return 0;
}