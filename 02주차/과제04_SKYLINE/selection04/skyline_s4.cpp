#include <iostream>
#include <cstdio>
#include <utility>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>

#define f first
#define s second
#define max_N 10001

using namespace std;

int main()
{
    int N, hz;
    pair<pair<int, int>, int> bldng_a[max_N];
    vector<int> x_v;
    set<int> x_s;

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d%d%d", &bldng_a[i].f.f, &bldng_a[i].s, &hz);
        bldng_a[i].f.s = bldng_a[i].f.f + hz;
        if (x_s.count(bldng_a[i].f.f) == 0) {
            x_v.push_back(bldng_a[i].f.f);
            x_s.insert(bldng_a[i].f.f);
        }
        if (x_s.count(bldng_a[i].f.s) == 0) {
            x_v.push_back(bldng_a[i].f.s);
            x_s.insert(bldng_a[i].f.s);
        }
    }
    sort(x_v.begin(), x_v.end());
    sort(bldng_a, bldng_a + N);
    
    
    int prv_x = 0, now_h = 0, next_h, cnt = 0;
    priority_queue<pair<int, int>> pq;
    for (auto x : x_v) {
        while (cnt < N && bldng_a[cnt].f.f <= x) {
            pq.push({bldng_a[cnt].s, bldng_a[cnt].f.s});
            cnt++;
        }
        next_h = 0;
        while (!pq.empty()) {
            if (x < pq.top().s) {
                next_h = pq.top().f;
                break ;
            }
            pq.pop();
        }
        if (now_h != next_h) {
            printf("%d %d ", x - prv_x, next_h - now_h);
            prv_x = x;
            now_h = next_h;
        }
    }
    return 0;
}
