#include <bits/stdc++.h>
using namespace std;
list<char> gn;
list<char>::iterator itgb, itge;
int main(){
    ifstream dna;
    vector<string> ops = {"front", "back", "cut", "double", "flip","report"};
    char g;
    int n, b, e, idx;
    string op;
    dna.open("/NESPA/sapiens.txt");
    getline(dna, op);
    while(dna >> g) gn.push_back(g);
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> op >> b >> e;
        if(b <= gn.size()){
            itgb = gn.begin();
            itge = gn.begin();
            advance(itgb, b-1);
            advance(itge, e);
            idx = find(ops.begin(), ops.end(), op) - ops.begin();
            switch(idx){
                case 0:
                    gn.splice(gn.begin(), gn, itgb, itge);
                    break;
                case 1:
                    gn.splice(gn.end(), gn, itgb, itge);
                    break;
                case 2:
                    gn.erase(itgb, itge);
                    break;
                case 3:
                    gn.insert(itge, itgb, itge);
                    break;
                case 4:
                    reverse(itgb, itge);
                    break;
                case 5:
                    for(itgb; itgb != itge; itgb++) cout << *itgb;
                    cout << '
';
                    break;
            }
        }
        else cout << "NONE" << '\n';
    }
    dna.close();
}