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

    int ans = 2147483645;               // �ּҰ� �ʱ�ȭ
    int w[7],h[7];

    for (int i = 1;i<=3; i++){          // �Է�
        cin>>w[i]>>h[i];
    }

    for (int i = 4; i<=5; i++){         // 90�� ȸ����Ų ����
        w[i]=h[i%3];
        h[i]=w[i%3];
    }

    w[6]=h[3];                          // �������� 0�� �Ǵ� 3�� ���
    h[6]=w[3];

    for(int i = 1; i<=6;i++){
        for(int j=1; j<=6;j++){
            for(int k=1; k<=6; k++){
                if (i%3==j%3||j%3==k%3||k%3==i%3) continue;                                 // ���� ���� �ߺ����� ����
                ans = min(ans,getResult(w[i]+w[j]+w[k],max(h[i],max(h[j],h[k]))));          // �� ���� ���ڸ� �Ϸķ� �迭
                ans = min(ans,getResult(max(w[i]+w[j],w[j]+w[k]),max(h[i]+h[k],h[j])));     // �� ���� ���ڸ� ���ٷ� �迭
                }
            }
        }
    cout << ans;

    }
