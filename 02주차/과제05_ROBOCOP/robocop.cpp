#include <iostream>

using namespace std;

#define rep(i,N) for (int i=0; i<(int)(N);i++)

int n;
int x[51],y[51];
int second[5];
int pointX,pointY;
int routeX[100000],routeY[100000];
int cnt;
int lap;

void input();
void makePointRoute();
void output();
void recordPoint();
void movingNextPoint(int,int);

int main(){
    input();

    makePointRoute();

    output();
}// end of main()

void input(){
        cin >> n;

    for (int i=0; i<n; i++)
        cin >> x[i] >> y[i];

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
    lap=cnt-1;
}//end of makePointRoute()

void output(){
    for(int i : second){
        cout<<routeX[i%lap]<<" "<<routeY[i%lap]<<endl;
    }
}

void recordPoint(){
    routeX[cnt]=pointX;
    routeY[cnt]=pointY;
    cnt++;
}

void movingNextPoint(int a,int b){
    while (pointX!=x[b] || pointY!=y[b]){
        if(x[b]-x[a]>0) {pointX++; recordPoint(); continue;}
        if(x[b]-x[a]<0) {pointX--; recordPoint(); continue;}
        if(y[b]-y[a]>0) {pointY++; recordPoint(); continue;}
        if(y[b]-y[a]<0) {pointY--; recordPoint(); continue;}
    }
}
