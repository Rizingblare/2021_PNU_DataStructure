#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

int n;
pair<int,int> idx;
float maxSim=0.0;
string s, ss;
vector<set<string>> kmer;
vector<string> inStr;

void read() {
    cin >> n;

    for(int i=0; i<n; i++) {
        ss = "";
        while(1) {
            cin >> s;
            if (s.compare("$") == 0) break;
            int nn = s.size();
            for(int i=0; i<nn; i++) {
                if((s[i] & 0x80) != 0) {
                    ss.push_back(s[i]);
                }
            }
        }
        inStr.push_back(ss);
    }
}

void solve() {
    idx.first = 0; idx.second = 0;

    for (int i =0; i<n;i++) {
        set<string> mini;
        if (inStr[i].length() >= 2) {
            for (int j=0; j<(inStr[i].length()/3)-1; j++) {
                string sss;
                sss = inStr[i].substr(j*3,6);
                mini.insert(sss);
            }
        }
        kmer.push_back(mini);
    }

    for (int i=0;i<n-1;i++) {
        for (int j=i+1;j<n;j++) {
            int x,y;
            set<string> inSimSet;
            float inSimNum;
            x = kmer[i].size(); y = kmer[j].size();
            set<string>::iterator iter;
            for (iter = kmer[i].begin();iter!=kmer[i].end();iter++) inSimSet.insert(*iter);
            for (iter = kmer[j].begin();iter!=kmer[j].end();iter++) inSimSet.insert(*iter);
            inSimNum = (float)(x+y-inSimSet.size())/(float)(x+y);
            if (inSimNum>maxSim) {
                maxSim = inSimNum;
                idx.first = i+1; idx.second = j+1;
            }
        }
    }
}

void print() {
    cout << idx.first << " " << idx.second;
}

int main() {
    read();
    solve();
    print();
    return 0;
}