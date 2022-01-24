#include <iostream>
#include <vector>

using namespace std;

int n,t;
vector <int> x,y;
int pointX,pointY;
vector <int> routeX,routeY;
int c1,c2;

void input();
void makePointRoute();
void robotMovement();
void output();
void recordPoint();
void movingNextPoint(int,int);

int main(){

    input();

    makePointRoute();

    robotMovement();

    output();

    return 0;
} //end of main()

void input(){
    cin >> n;

    int a,b;
    for (int i=0; i<n; i++){
        cin >> a >> b;
        x.push_back(a);
        y.push_back(b);
    }

    cin >> t;
}


void makePointRoute(){
    for(int i=0; i<=n; i++){
        if(pointX==x[n/2-1]&&pointY==y[n/2-1]){
            c1=0, c2=routeX.size()-1;
        }
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

void robotMovement(){
    int clockwise = 1;
    int lap = routeX.size()-1;
    for (int i=0; i<t; i++){
        c1+=clockwise;
        c2-=clockwise;

        if (c1== -1)    c1=lap-1;
        if (c1==lap)    c1=0;
        if (c2== -1)    c2=lap-1;
        if (c2==lap)    c2=0;

        if (c1==c2||c1+1==c2||c1-1==c2){
            clockwise = -clockwise;
            if (c1+1==c2||c1-1==c2) i++;
        }
        //cout<<"t= "<<i<<" // "<< "c1: "<<c1<<", "<<"c2: "<<c2<<endl;
    }
}

void output(){
    cout << routeX[c1] << " " << routeY[c1]<< endl;
    cout << routeX[c2] << " " << routeY[c2]<< endl;
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
