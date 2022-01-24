#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int,int> pii;
typedef vector<int> vec;

#define f first
#define s second
#define FOR(i,a,b) for(int i = int(a); i < int(b); i ++)
#define REP(i,b) FOR(i,0,b)
#define num 100001

pair<pii,int> cor[num];
map<int,int> box;
vec cor_x; //x좌표
priority_queue<pii> pq;

int main(){
    int n, num_x=0; //num_x = x좌표의 개수
    cin >> n;
    int x,v,h;

    REP(i,n){
        scanf("%d%d%d",&x,&v,&h);
        cor[i].f.f = x;
        cor[i].s = v;
        cor[i].f.s = x+h;

        box[cor[i].f.f]= box[cor[i].f.s] = 0;
    }
    
    for( auto i : box ){ box[i.f]=num_x++; cor_x.push_back(i.f); } //트리의 key값 설정
    sort(cor,cor+n);

    int now=0, j=0, next_x=0;

    REP(i,num_x){
    while( j<n && box[cor[j].f.f]<=i ){
            pq.push({cor[j].s,box[cor[j].f.s]});
            j++;
        }
        int next = 0;
        while( !pq.empty() ){
            if( i < pq.top().s ){
                next = pq.top().f;
                break;
            }
            pq.pop();
        }
        if( now!=next ){
            now = next-now;
            cout << cor_x[i]-next_x << " " << now << " ";
            next_x = cor_x[i];
            now = next;
        }
    }

    return 0;
}