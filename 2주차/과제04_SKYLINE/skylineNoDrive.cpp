#include <iostream>

using namespace std;

int main(){

    int n;

    cin >> n;

    int skyline[1000000]={};
    int x[10001],v[10001],h[10001];

    for (int i=0; i<n; i++){
        cin >> x[i] >> v[i] >> h[i];
    }

    int minX=2147483647,maxX=0;
    for (int i=0; i<n; i++) {
            if (minX > x[i]     ) minX=x[i];
            if (maxX < x[i]+h[i]) maxX=x[i]+h[i];
    }
    //cout << minX <<","<<maxX<<endl;

    for (int i=0; i<n; i++){
        for (int j = x[i]; j < x[i] + h[i]; j++){
            if(v[i] > skyline[j]) skyline[j]=v[i];
        }
    }
    /*
    for (int i=0; i<maxX; i++){
        cout<< skyline[i] << " ";
    }
    */
    cout << minX <<" ";
    int cnt = 0;
    for (int i=minX; i<=maxX; i++) {
            if (skyline[i]!=skyline[i-1]){
                if (i==minX)    cout<<skyline[i]<<" ";
                else           {cout<<cnt<<" "<<skyline[i]-skyline[i-1]<<" "; cnt = 0;}
            }
            cnt++;
    }
} // end of main()
