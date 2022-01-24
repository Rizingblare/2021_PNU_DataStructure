#include <bits/stdc++.h>

using namespace std;

vector<set<string>> result;
struct info{
    int first;
    int second;
    double sim;
} whichBig ={1, 2, 0};
int main() {
    int N, i, j, k;
    string str;

    char c[701] = {0,};
    char val[7] = {0,};

    cin >> N;

    for(i = 0; i < N; i++){
        k = 0;
        fill_n(c, 701, 0);
        set<string> ss;
        getline(cin, str, '$');
        for(j = 0; j < str.length(); j++){
            if((str[j] & 0x80) == 0x80){
                c[k++] = str[j];
            }
        }
        for(j = 0; j < k - 3; j += 3){
            strncpy(val, c + j, 6);
            ss.insert(val);
        }
        result.push_back(ss);
    }
    i = 1;
    for(auto x = result.begin(); x != result.end(); x++){
        j = 1;
        set<string> x1 = *x;
        if(i > result.size()) break;
        for(auto y = result.begin() + i; y != result.end(); y++){
            set<string> y1 = *y;
            set<string> uni;
            set<string> inter;
            set_union(x1.begin(), x1.end(), y1.begin(), y1.end(), inserter(uni, uni.begin()));
            set_intersection(x1.begin(), x1.end(), y1.begin(), y1.end(), inserter(inter, inter.begin()));
            if((inter.size() / (double)uni.size()) > whichBig.sim){
                whichBig.sim = (inter.size() / (double)uni.size());
                whichBig.first = i;
                whichBig.second = i + j;
            }
            j++;
        }
        i++;
    }
    cout << whichBig.first << " " << whichBig.second << endl;
	return 0;
}