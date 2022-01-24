#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#define FOR(i, a, b) for(int i = a; i < b; ++i)
#define left first 
#define right second 
using namespace std;
int n, k;
typedef pair<int, int> pii;
list<pii> len;
list<pii>::iterator it;
vector<int> customer(10001, 0);

int Get_Mid(int a, int b){
  int l;
  if(a > b){
    l = n - a - 1 + b;
    // 홀수
    if(l % 2 != 0){ 
      if(a+1+l/2 == n) return 1;
      else {
        if(a+1+l/2 > n) return (a+1+l/2 - n);
        else            return (a+1+l/2);
      }
    }
    //짝수
    if(a+1+l/2 > n) return (a+1+l/2 - n);
    else            return (a+1+l/2);
  }
  else{
    return (a+b+1)/2;
  }
}

// 길이가 더 큰 것 반환 + 인덱스 작은것 반환
bool Length_Compare(pii a, pii b){
  int len1 = a.right - a.left;
  int len2 = b.right - b.left;
  if(a.left > a.right){
    len1 = n - a.left + a.right;
  }
  if(b.left > b.right){
    len2 = n - b.left + b.right;
  }

  if(len1==len2){
    int t1, t2;
    t1 = Get_Mid(a.left, a.right);
    t2 = Get_Mid(b.left, b.right);
    return (t1 > t2);
  }
  return (len1 < len2);
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  cin >> n >> k;
  int tmp;
  FOR(i, 0, k){
    cin >> tmp;
    // 유저 ID에 대한 방문 여부 및 좌석 인덱스
    if(len.empty()){ // 아무도 없는 경우
      customer[tmp] = 1;
      len.push_back(make_pair(1, n));
      cout << tmp << ' ' << 1 << '
';
      continue;
    }

    if(customer[tmp] == 0){ // 새로 온 경우
      it = max_element(len.begin(), len.end(), Length_Compare);
      int left_ = (*it).left, right_ = (*it).right;
      int mid_ = Get_Mid(left_, right_);
      customer[tmp] = mid_;
      cout << tmp << ' ' << mid_ << '
';
      len.insert(it, make_pair(left_, mid_-1));
      len.insert(it, make_pair(mid_, right_));
      len.erase(it);
    }
    else{ // 나가는 경우
      int idx = customer[tmp], idx_;
      customer[tmp] = 0;
      int left_, right_;
      list<pii>::iterator it1, it2;

      if(idx == 1) idx_ = n;
      else idx_ = idx - 1;

      for(it = len.begin(); it != len.end(); ++it){
        if((*it).left == idx){
          right_ = (*it).right;
          it1 = it;
        }
        if((*it).right == idx_) {
          left_ = (*it).left;
          it2 = it;
        }
      }
      // cout << left_ << ' ' << right_ << '
';
      len.insert(it1, make_pair(left_, right_));
      len.erase(it1);
      len.erase(it2);
    }
  }
}