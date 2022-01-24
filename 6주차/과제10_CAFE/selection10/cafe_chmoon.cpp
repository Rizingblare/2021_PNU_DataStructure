#include <cstdio>
#include <iostream>
#include <set>
#include <unordered_map>
#include <utility>
#include <tuple>

#define f first
#define s second
using namespace std;
typedef pair<int, int> pii;
typedef unordered_map<int, tuple<int, int, int>> it_umap;
typedef unordered_map<int, int> ii_umap;


struct cmp {
    bool operator() (const pair<pii, pii> &a, const pair<pii, pii> &b) const {
        if (a.f.f == b.f.f)
            return a.f.s < b.f.s;
        else
            return a.f.f > b.f.f;
    }
};
typedef set<pair<pii, pii>, cmp> gset;


void sit(gset &g_s, it_umap &id_um, ii_umap &st_um, int id, int n) {
    int g, m, l, r, dif_l, dif_r, lmid, rmid, idl, idr;

    if (id_um.size() == 0) {
        m = 1;
        id_um[id] = make_tuple(1, 1, 1);
        g_s.insert({{n, 1 + n / 2}, {1, 1}});
    }
    else {
        g = g_s.begin()->f.f;
        m = g_s.begin()->f.s;
        l = g_s.begin()->s.f;
        r = g_s.begin()->s.s;
        idl = st_um[l];
        idr = st_um[r];
        dif_l = (l < m ? m - l : m + n - l);
        dif_r = (m < r ? r - m : r + n - m);
        lmid = (l + dif_l / 2 <= n ? l + dif_l / 2 : l + dif_l / 2 - n);
        rmid = (m + dif_r / 2 <= n ? m + dif_r / 2 : m + dif_r / 2 - n);

        id_um[id] = make_tuple(m, l, r);
        g_s.erase({{g, m}, {l, r}});
        id_um[idl] = make_tuple(get<0>(id_um[idl]), get<1>(id_um[idl]), m);
        id_um[idr] = make_tuple(get<0>(id_um[idr]), m, get<2>(id_um[idr]));
        g_s.insert({{dif_l, lmid}, {l, m}});
        g_s.insert({{dif_r, rmid}, {m, r}});
    }
    st_um[m] = id;
}


void dlt(gset &g_s, it_umap &id_um, ii_umap &st_um, int id, int n) {
    int dif_l, dif_r, lmid, rmid, mid, big_gap;
    
    int m = get<0>(id_um[id]);
    int l = get<1>(id_um[id]);
    int r = get<2>(id_um[id]);
    int idl = st_um[l];
    int idr = st_um[r];

    id_um.erase(id);
    id_um[idl] = make_tuple(get<0>(id_um[idl]), get<1>(id_um[idl]), r);
    id_um[idr] = make_tuple(get<0>(id_um[idr]), l, get<2>(id_um[idr]));

    dif_l = (l < m ? m - l : m + n - l);
    dif_r = (m < r ? r - m : r + n - m);
    lmid = (l + dif_l / 2 <= n ? l + dif_l / 2 : l + dif_l / 2 - n);
    rmid = (m + dif_r / 2 <= n ? m + dif_r / 2 : m + dif_r / 2 - n);
    big_gap = (l < r ? r - l : r + n - l);
    mid = l + big_gap / 2 <= n ? l + big_gap / 2 : l + big_gap / 2 - n;

    g_s.erase({{dif_l, lmid}, {l, m}});
    g_s.erase({{dif_r, rmid}, {m, r}});
    g_s.insert({{big_gap, mid}, {l, r}});
}


int main(int argc, const char * argv[]) {
    int n, k, id;
    it_umap id_um;
    ii_umap st_um;
    gset g_s;
    
    scanf("%d%d", &n, &k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &id);
        if (id_um.count(id) == 0 && id_um.size() != n) {
            sit(g_s, id_um, st_um, id, n);
            printf("%d %d
", id, get<0>(id_um[id]));
        }
        else
            dlt(g_s, id_um, st_um, id, n);
    }
    return 0;
}
