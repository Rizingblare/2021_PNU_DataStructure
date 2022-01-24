#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

struct P{
    long long x,y;
};

int get_dist(P A, P B) {
    return abs(A.x - B.x) + abs(A.y - B.y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int N;
    long long sum=0;
    
    cin >> N;
    
    vector < P > p(N);
    vector < long long > dist(N,0);
    
    for(int i=0; i<N; i++) {
        cin >> p[i].x >> p[i].y;
        if(i > 0) {
            dist[i-1] = get_dist(p[i], p[i-1]);
            sum += dist[i-1];
        }
    }
    dist[N-1] = get_dist(p[0], p[N-1]);
    sum += dist[N-1];
    //cout << "sum: " << sum << "\n";
    
    for(int i=0; i<5; i++) {
        int time;
        cin >> time;
        time %= sum;
        P ans = p[0];
        for(int k=0; time > 0 && k<N; k++) {
            if(time >= dist[k]) {
                time -= dist[k];
                ans = p[(k+1)%N];
            }
            else {
                int m = time, n=dist[k]-time;
                P p1=p[k], p2 = p[(k+1)%N];
                ans.x = (m*p2.x+n*p1.x)/(m+n);
                ans.y = (m*p2.y+n*p1.y)/(m+n);
                time = 0;
            }
            // cout << "time " << time << ": " << ans.x << ' ' << ans.y << "\n";
        }
        cout << ans.x << ' ' << ans.y << "\n";
    }
    
    return 0;
}