#include <bits/stdc++.h>
#include <codecvt>
using namespace std;
#define pb push_back
#define K 2


vector<wstring> v_wstr;
vector<set<wstring>> v_kmer;

wstring utf8_to_utf16(const string& utf8) {
    wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t> convert;
    u16string utf16 = convert.from_bytes(utf8);
    wstring wstr(utf16.begin(), utf16.end());
    return wstr;
}

double Sim(set<wstring> s1, set<wstring> s2) {
    int cdnIntersection = 0;
    set<wstring>::iterator iter;
    for (iter = s1.begin(); iter != s1.end(); iter++) {
        if (s2.find(*iter) != s2.end()) cdnIntersection++;
    }
    int cdnUnion = s1.size() + s2.size() - cdnIntersection;
    double sim = (double) cdnIntersection / cdnUnion;
    return sim;
}

void Input() {
    int n;
    cin >> n;
    string p;
    for(int i=0; i<n; i++) {
        string ss;
        while(1) {
            cin >> p;
            if (p.compare("$") == 0) break;
            int nn = p.size();
            for(int i=0; i<nn; i++) {
                if((p[i] & 0x80) != 0) {
                    ss.push_back(p[i]);
                }
            }
        }
        if (ss.size() == 0) ss = "E" + to_string(i); // Empty String
        wstring w = utf8_to_utf16(ss);
        v_wstr.pb(w);
    }
}
void Compute() {
    for (wstring e : v_wstr) {
        set<wstring> s_wstr;
        for (int i = 0; i <= e.size() - K; i++) {
            s_wstr.insert(e.substr(i, K));
        }
        v_kmer.pb(s_wstr);
    }
    int n = v_kmer.size();
    vector<bool> vBool(2, true);
    vBool.insert(vBool.end(), n - 2, false);
    double mostSim = 0, currSim = 0;
    int sol_i = 1, sol_j = 2;
    do {
        vector<int> vChosen;
        for (int i = 0; i < n; i++) {
            if (vBool[i]) vChosen.pb(i);
        }
        currSim = Sim(v_kmer[vChosen[0]], v_kmer[vChosen[1]]);
        if (currSim > mostSim) {
            mostSim = currSim;
            sol_i = vChosen[0] + 1;
            sol_j = vChosen[1] + 1;
        }
    } while (prev_permutation(vBool.begin(), vBool.end()));
    cout << sol_i << ' ' << sol_j;
}

int main() {
    Input();
    Compute();
    return 0;
}