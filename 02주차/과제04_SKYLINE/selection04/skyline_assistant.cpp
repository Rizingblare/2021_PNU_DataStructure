#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Event {
public :
    int x,y,type;

    bool operator <(const Event &E) const {
        if(x != E.x) return x<E.x;
        if(type != E.type) return type > E.type;
        return y > E.y;
    }
};

int main()
{

    int N;
    scanf("%d",&N);
    vector <Event > v(2*N);

    for(int i=0; i<N; i++) {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        v[i].x=a; v[i+N].x=a+c;
        v[i].y=b; v[i+N].y=b;
        v[i].type=-i-1; v[i+N].type=i+1;
    }

    sort(v.begin(),v.end());
    
    int before=0;
    int beforex=0;
    vector<pair<int,int>> ans;
    ans.push_back({0,0});
    multiset <int > M;
    M.insert(0);
    for(int i=0; i<v.size(); i++) {
        if(v[i].type > 0) {
            M.erase(M.lower_bound(v[i].y));
            if(v[i+1].x == v[i].x && v[i+1].type > 0)
                continue;
        }
        if(v[i].type < 0) {
            M.insert(v[i].y);
        }
        int now=*(M.rbegin());
        if(now != before) {
            ans.push_back({v[i].x,now});
            before=now;
        }
    }
    #ifdef DEBUG
    for(int i=1; i<ans.size(); i++) {
        printf("%d %d\n",ans[i].first, ans[i-1].second);
        printf("%d %d\n",ans[i].first, ans[i].second);
    }
    #endif
    for(int i=1; i<ans.size(); i++) {
        printf("%d %d ",ans[i].first-ans[i-1].first, ans[i].second-ans[i-1].second);
    }

    return 0;
}