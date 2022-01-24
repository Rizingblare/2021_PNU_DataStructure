#include<bits/stdc++.h>
using namespace std;

#define REP(i, a, b) for(auto i=a;(a<b)?i<b:i>b;(a<b)?i++:i--)
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

pair<int,int> operator+(pair<int,int> x, pair<int,int> y) {
    pair<int,int> res = {x.first+y.first,x.second+y.second};
    return res;
}

pair<int,int> operator-(pair<int,int> x, pair<int,int> y) { 
    pair<int,int> res = {x.first-y.first,x.second-y.second};
    return res;
}

int norm(pair<int,int> x) { return (x.first>0?x.first:-x.first) + (x.second>0?x.second:-x.second); }

int direction(pair<int,int> x) {
    if(x.first != 0)
        return (x.first>0?RIGHT:LEFT);
    if(x.second != 0)
        return (x.second>0?UP:DOWN);
}

ostream& operator<<(ostream& out, pair<int, int> p) { return out << p.first << ' ' << p.second; }



class ROBOCOP {
private:
    vector<pair<int,int>> points;
    vector<pair<int,int>> displacements;
    int period;
public:
    ROBOCOP(vector<pair<int,int>> p): points(p), displacements(), period(0) {setup_robocop();}

    void setup_robocop() {
        REP(iter, points.begin()+1, points.end()) {
            displacements.push_back(*iter - *(iter-1));
            period += norm(*iter - *(iter-1));
        }
        displacements.push_back(points.front() - points.back());
        period += norm(points.front() - points.back());
    }

    pair<int,int> move_robocop(int t) {
        t %= period;
        int i=0;
        for(pair<int,int> d: displacements) {
            if(t > norm(d)) {
                t -= norm(d);
                i += 1;
            }
            else
                break;
        }
        int direct = direction(displacements[i]);
        pair<int,int> movement;
        if(direct == UP)
            movement = {0, t};
        else if(direct == RIGHT)
            movement = {t, 0};
        else if(direct == DOWN)
            movement = {0, -t};
        else if(direct == LEFT)
            movement = {-t, 0};
        
        return points[i] + movement;
    }
};



int main() {
    int n; 
    cin >> n;
    
    vector<pair<int,int>> points;
    REP(i, 0, n) {
        int x,y;
        cin >> x >> y;
        points.push_back({x,y});
    }
    
    ROBOCOP ROB(points);

    int t;
    while(cin >> t)
        cout << ROB.move_robocop(t) << endl;

    return 0;
}