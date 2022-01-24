#include <bits/stdc++.h>
using namespace std;

/*class fu {
	char char1;
	char char2;
	char char3;
	char char4;
public:
	fu(char _char1, char _char2, char _char3, char _char4){
		
	}
};*/

double calcSimilarity(int i, int j, vector<set<string>>& sets){
    set<string> setUnion;
    set<string> setIntersection;
    set_union(sets[i].begin(), sets[i].end(), sets[j].begin(), sets[j].end(), inserter(setUnion, setUnion.begin()));
    set_intersection(sets[i].begin(), sets[i].end(), sets[j].begin(), sets[j].end(), inserter(setIntersection, setIntersection.begin()));
    //cout << sets[i].size() << "//" << sets[j].size() << endl;
    //cout << i << "," << j <<setIntersection.size() << "/"<<setUnion.size() << ":"<<double(setIntersection.size())/setUnion.size()<< endl;
    if(setUnion.size() == 0) return 0;
    return double(setIntersection.size())/setUnion.size();
}

int main() {
    int n;
    vector < set<string> > v;
    
    cin >> n;
    string p;
    for(int j=0; j<n; j++) {
        string ss;
        bool fin = false;
        while(1) {
            cin >> p;
            int nn = p.size();
            for(int i=0; i<nn; i++) {
            	if (p[i]== '$'){
                		fin = true;
						break;
					}
                if((p[i] & 0x80) != 0) {
                    ss.push_back(p[i]);
                }
            }
            if (fin == true)break;
        }
        set<string> a;
        if(ss.length()>=6){
        	for(int i=0; i<ss.length()-3; i += 3){
			a.insert(ss.substr(i,6));
			}
		}
        v.push_back(a);
        //for(auto dd : a){
        //    cout << dd << ", ";
        //}
        //cout << a.size();
        //cout << "!" << endl;
    }
    double similarityMax = -1.0;
    pair<int, int> similarityMaxPair;
    
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            double similarityTemp = calcSimilarity(i, j,v);
            if(similarityMax < similarityTemp){
                similarityMax = similarityTemp;
                similarityMaxPair = make_pair(i,j);
            }
        }
    }
    cout << similarityMaxPair.first+1 << " " << similarityMaxPair.second+1 << endl;
}