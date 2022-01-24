#include <iostream>
#include <array>
#include <vector>

using namespace std;

#define rep(i,N) for (int i=0; i<(int)(N);i++)

int n;
vector <int> x,y;
array <int,5> second;
int pointX,pointY;
vector <int> routeX,routeY;
//int cnt;
//int lap;

void input();
void makePointRoute();
void output();
void recordPoint();
void movingNextPoint(int,int);

int main(){
    input();

    makePointRoute();

    cout<<"printRoute :"<<endl;

    for(int i=0; i<routeX.size(); i++)
        cout<<"("<<routeX[i]<<","<<routeY[i]<<")"<<endl;

    output();
}// end of main()

void input(){
        cin >> n;

    int a,b;
    for (int i=0; i<n; i++){
        cin >> a >> b;
        x.push_back(a);
        y.push_back(b);
    }

    for (int &i : second)
        cin >> i;
}

void makePointRoute(){
    for(int i=0; i<=n; i++){
        if (i==0) {
            pointX=x[i];
            pointY=y[i];
            recordPoint();
            continue;
        }
        if (i==n) {
            movingNextPoint(n-1,0);
            break;
        }
        movingNextPoint(i-1,i);
    }
}//end of makePointRoute()

void output(){
    int lap = routeX.size()-1;
    for(int i : second){
        cout<<routeX[i%lap]<<" "<<routeY[i%lap]<<endl;
    }
}

void recordPoint(){
    routeX.push_back(pointX);
    routeY.push_back(pointY);
}

void movingNextPoint(int a,int b){
    while (pointX!=x[b] || pointY!=y[b]){
        if(x[b]-x[a]>0) {pointX++; recordPoint(); continue;}
        if(x[b]-x[a]<0) {pointX--; recordPoint(); continue;}
        if(y[b]-y[a]>0) {pointY++; recordPoint(); continue;}
        if(y[b]-y[a]<0) {pointY--; recordPoint(); continue;}
    }
}
