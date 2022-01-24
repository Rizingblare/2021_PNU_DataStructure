#include <iostream>

using namespace std;

int min(int a, int b){
    return a > b ? b : a;
}

int max(int a, int b){
    return a > b ? a : b;
}

int getResult(int a, int b){
    return a*a + b*b;
}

int main(){

    int ans = 2147483645;               // 최소값 초기화
    int w[7],h[7];

    for (int i = 1;i<=3; i++){          // 입력
        cin>>w[i]>>h[i];
    }

    for (int i = 4; i<=5; i++){         // 90도 회전시킨 상자
        w[i]=h[i%3];
        h[i]=w[i%3];
    }

    w[6]=h[3];                          // 나머지가 0이 되는 3의 배수
    h[6]=w[3];

    for(int i = 1; i<=6;i++){
        for(int j=1; j<=6;j++){
            for(int k=1; k<=6; k++){
                if (i%3==j%3||j%3==k%3||k%3==i%3) continue;                                 // 같은 상자 중복선택 제거
                ans = min(ans,getResult(w[i]+w[j]+w[k],max(h[i],max(h[j],h[k]))));          // 세 개의 상자를 일렬로 배열
                ans = min(ans,getResult(max(w[i]+w[j],w[j]+w[k]),max(h[i]+h[k],h[j])));     // 세 개의 상자를 두줄로 배열
                }
            }
        }
    cout << ans;

    }
