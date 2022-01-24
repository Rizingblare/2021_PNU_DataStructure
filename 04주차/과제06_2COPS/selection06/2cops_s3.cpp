#include<bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    Point() : x(0), y(0) {};
    Point(int _x, int _y) : x(_x), y(_y) {};
    Point(const Point &point) : x(point.x), y(point.y) {};

    bool operator==(const Point &point) { return this->x == point.x && this->y == point.y; }
    bool operator!=(const Point &point) { return this->x != point.x || this->y != point.y; }
    Point& operator=(const Point &point) { 
        this->x = point.x;
        this->y = point.y;
        return *this;
    }
};
void logPath();
void moveCops();
void printCops();

vector<Point> path;
vector<Point>::iterator c1, c2;
Point startP, middleP;
int N, t, offset;
bool swapCops = false;

int main() {
    logPath();
    moveCops();
    printCops();
    return 0;
}

/*
* 이전에 입력받은 점와 현재 입력받은 점 사이의 점들을 vector<Point> path에 push back
* 첫 점과 마지막 점의 x좌표가 같은지 비교하여 횡or행 이동 출발인지 offset으로 구분
*/
void logPath() {
    cin >> N >> startP.x >> startP.y;
    Point tempP, beforeP(startP.x, startP.y);

    for(int i=2;i<=N;i++) {
        cin >> tempP.x >> tempP.y;
        Point temp2P(beforeP);
        if(i == N/2) middleP = tempP;

        while(temp2P != tempP) {
            path.push_back(temp2P);
            if(tempP.x == beforeP.x) temp2P.y += (tempP.y - beforeP.y) / abs(tempP.y - beforeP.y);
            else temp2P.x += (tempP.x - beforeP.x) / abs(tempP.x - beforeP.x);
        }
        beforeP = tempP;
    }
    if(beforeP.x == startP.x) offset++;

    while(beforeP != startP) {
        path.push_back(beforeP);
        if(beforeP.x == startP.x) beforeP.y += (startP.y - beforeP.y) / abs(startP.y - beforeP.y);
        else beforeP.x += (startP.x - beforeP.x) / abs(startP.x - beforeP.x);
    }
    cin >> t;
}

/*
* path를 도는 2개의 vector iterator(2cops)를 선언하여 서로 다른 방향으로 순회
* iterator가 가르키는 두 점이 만나면 출력 순서를 바꾸는 swapCops를 토글 on/off
*/
void moveCops(){
    c1 = path.begin();
    c2 = find(path.begin(), path.end(), middleP);
    int cooltime = -1;
    
    while(t--) {
        if(c1 == path.end()) c1 = path.begin();

        if((   c1->x == c2->x && abs(c1->y - c2->y) <= 1 
            || c1->y == c2->y && abs(c1->x - c2->x) <= 1) 
            && cooltime < 0) {
            swapCops = !swapCops;
            cooltime = 1;
        }
        cooltime--;
        c1++;

        if(c2 == path.begin()) c2 = path.end();
        c2--;
    }
}

/* t초가 끝나고, swapCops의 순서에 따라 현재 two Cops의 위치 출력 */
void printCops(){
    if(!swapCops) cout << c1->x << ' ' << c1->y << '
' << c2->x << ' ' << c2->y;
    else          cout << c2->x << ' ' << c2->y << '
' << c1->x << ' ' << c1->y;
}\