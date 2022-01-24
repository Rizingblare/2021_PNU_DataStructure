#include <bits/stdc++.h>
using namespace std;

string Only_Hangul(string p ){
    string Ohan  ;
    int nn = p.size();
    for(int i=0; i<nn; i++) {
         if((p[i] & 0x80) != 0) {
             Ohan.push_back(p[i]);
         }
    } // end of for(i)
    return ( Ohan ) ;
} // end of ONly_Hangul( )


void input(vector<string> &line) {
    int numInput = 0;
    string sentence = "";
    char word;
    cin >> numInput;
    while(numInput--) {
        sentence = "";
        cin >> word;
        while(word != '$') {
            sentence += word;
            cin >> word;
        }
        sentence = Only_Hangul( sentence ) ;
        line.push_back(sentence);
    }
}

void makeSub(vector<string> &line, vector<set<string>> &substring) {
    string sub="";
    for(auto l : line) {
        set<string> twoMer;
        if(l.size() < 6) { substring.push_back({""}); continue; }
        for(int i =0; i< l.size() -3; i+=3) {
            sub =  l[i];                sub = sub + l[i+1]; sub = sub + l[i+2];
            sub = sub + l[i+3];  sub = sub + l[i+4]; sub = sub + l[i+5];
            twoMer.insert(sub);
        }
        substring.push_back(twoMer);
    }
}

void calculate(vector<set<string>> &substring, priority_queue<tuple<float, int, int>> &similarity) {
    float total = 0;
    float sim =0;
    for(int i =0 ; i < substring.size() -1; i++) {
        for(int j = i+1; j < substring.size(); j++) {
            set<string> similar;
            set_union(substring[i].begin(), substring[i].end(), substring[j].begin(), substring[j].end(), inserter(similar, similar.begin()));
            total = substring[i].size() + substring[j].size();
            if(*substring[i].begin()=="") sim = 0;
            else sim = ( total - similar.size() ) / total;
            similarity.emplace(sim, i, j);
        }
    }
}

void out(priority_queue<tuple<float, int, int>> &similarity) {
    float best = get<0>(similarity.top());
    int sentence1 = 1, sentence2 = 2;
    while(best == get<0>(similarity.top())) {
        sentence1 = get<1>(similarity.top()) +1;
        sentence2 = get<2>(similarity.top()) +1;
        similarity.pop();
    }
    cout << sentence1 << " " << sentence2;
}

int main() {
    vector<string> line;
    vector<set<string>> substring;
    priority_queue<tuple<float, int, int>> similarity;
    input(line);
    makeSub(line, substring);
    calculate(substring, similarity);
    out(similarity);

    return 0;
}
