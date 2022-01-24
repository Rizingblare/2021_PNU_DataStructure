#include <stdio.h>
int ans = 2147483645;
int w[7], h[7];
int max(int a, int b) {
   return a > b ? a : b;
}

int min(int a, int b) {
   return a > b ? b : a;
}

int getresult(int w, int h) {
   return w*w + h*h;
}

int is_same(int a, int b) {
   return a % 3 == b % 3; // ���� �ڽ� ���� ���� (1 == 4(1�� ȸ��))
}

int main() {
   for(int i = 1 ; i <= 3 ; i++) {
      scanf("%d %d", &w[i], &h[i]);
   }

   for(int i = 4 ; i <= 6 ; i++) {
      w[i] = h[i % 3]; // ȸ�� ���
      h[i] = w[i % 3]; // ȸ�� ���
   }

   for(int i = 1 ; i <= 6 ; i++) {
      for(int j = 1 ; j <= 6 ; j++) {
         for(int k = 1 ; k <= 6 ; k++) {
            if(is_same(i, j) || is_same(j, k) || is_same(i, k)) continue;
            ans = min(ans, getresult(w[i] + w[j] + w[k], max(h[i], max(h[j], h[k])))); // �� ���� ���ڷ� ���� ��� ���
            ans = min(ans, getresult(max(w[i], w[j]) + w[k], max(h[i] + h[j],  h[k]))); // 2, 1�� ������ ���� ��� ���
         }
      }
   }
   printf("%d\n", ans);
}
