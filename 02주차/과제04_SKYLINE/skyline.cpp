#include <iostream>

using namespace std;

void input();
void find_minX_maxX();
void makeSkyline();
void printSkyline();

/* 드라이브 루틴 시도,
모든 변수를 글로벌 변수로 선언하는 방법 말고는 아직 섣불리 시도하기 어려움.
레퍼런스 변수를 사용하는 등, 입력받은 배열 값 등을 다른 함수에서도 활용할 수 있는
드라이브 루틴에 대한 심화 강의도 제공해 주신다면 정말 좋을 것 같습니다!
*/
int volume;
int x[10001],v[10001],h[10001];
int minX=2147483647,maxX=0;
int skyline[1000000];

int main(){

    input();

    find_minX_maxX();

    makeSkyline();

    printSkyline();
}                   // end of main()

void input(){
    cin >> volume;
    for (int i=0; i<volume; i++){
        cin >> x[i] >> v[i] >> h[i];
    }
}
void find_minX_maxX(){
    for (int i=0; i<volume; i++){
            if (minX > x[i]     ) minX=x[i];
            if (maxX < x[i]+h[i]) maxX=x[i]+h[i];
    }
}
void makeSkyline(){
    for (int i=0; i<volume; i++){
        for (int j = x[i]; j < x[i] + h[i]; j++){
            if(v[i] > skyline[j]) skyline[j]=v[i];
        }
    }
}
void printSkyline(){
    cout << minX <<" ";
    int cnt = 0;
    for (int i=minX; i<=maxX; i++) {
            if (skyline[i]!=skyline[i-1]){
                if (i==minX)    cout<<skyline[i]<<" ";
                else           {cout<<cnt<<" "<<skyline[i]-skyline[i-1]<<" "; cnt = 0;}
            }
            cnt++;
    }
}
