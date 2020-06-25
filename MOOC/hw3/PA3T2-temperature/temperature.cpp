// https://blog.csdn.net/shahdza/article/details/7844836
// https://blog.csdn.net/silangquan/article/details/41483689

#include "temperature.h"
#include <cstdlib>
#include <ctime>
#ifndef _OJ_
// #include <cstdio>
#include "temperature_lib.c"
#endif // _OJ_
typedef long long ll;
const int MAXN = 50005;
int nStation;
struct Station {
    int pos[2]; // position
    ll Temp; // Temperature
};
Station sta[MAXN];

/* KDTree */
typedef Station DataType;
struct KDNode {
    DataType data;
    struct KDNode *left, *right;
};
typedef KDNode *KDTree;
KDTree root = NULL;
KDNode _memPool[MAXN], *_pool_sp = _memPool;
inline KDTree newKDNode(DataType data) {
    _pool_sp->data = data;
    _pool_sp->left = _pool_sp->right = NULL;
    return _pool_sp++;
}
void insertKDTree(DataType data, KDTree rt) {
    // non-recursive
    // assert rt != NULL
    if (rt == NULL) return ;
    KDTree cur = rt;
    int d = 0;
    while (1) {
        if (data.pos[d] < cur->data.pos[d]) {
            if (cur->left) cur = cur->left;
            else {
                cur->left = newKDNode(data);
                break;
            }
        }
        else {
            if (cur->right) cur = cur->right;
            else {
                cur->right = newKDNode(data);
                break;
            }
        }
    }
}

ll Tsum = 0; int cnt = 0;
int lo[2], hi[2];
void recRangeQuery(KDTree rt, int d) {
    if (rt == NULL) return ;
    if (
        (lo[0] <= rt->data.pos[0] && rt->data.pos[0] <= hi[0]) && 
        (lo[1] <= rt->data.pos[1] && rt->data.pos[1] <= hi[1])
    ) {
        Tsum += rt->data.Temp;
        cnt++;
    }
    if (lo[d] <= rt->data.pos[d]) 
        recRangeQuery(rt->left, 1 - d);
    if (hi[d] >= rt->data.pos[d])
        recRangeQuery(rt->right, 1 - d);
}

/* ---- Random Permutation ---- */
void randOrder() {
    srand(time(NULL));
    for (int r = nStation; r > 1; r--) {
        int idx = rand() % r;
        DataType tmp = sta[idx];
        sta[idx] = sta[r - 1];
        sta[r - 1] = tmp;
    }
}

int main()
{
    nStation = GetNumOfStation();
    for (int i = 0; i < nStation; i++) {
        int x, y, temp;
        GetStationInfo(i, &x, &y, &temp);
        sta[i].pos[0] = x; sta[i].pos[1] = y;
        sta[i].Temp = temp;
    }
    randOrder();
    /* Build KD-Tree */
    root = newKDNode(sta[0]);
    for (int i = 1; i < nStation; i++) {
        insertKDTree(sta[i], root);
    }
    /* Range Query */
    int x1, y1, x2, y2;
    while (GetQuery(&x1, &y1, &x2, &y2)) {
        lo[0] = x1, lo[1] = y1;
        hi[0] = x2, hi[1] = y2;
        Tsum = cnt = 0;
        recRangeQuery(root, 0);
        int ave = cnt ? Tsum / cnt : 0;
        Response(ave);
    }


    return 0;
}