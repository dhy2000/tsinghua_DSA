#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
const int MAXN = 2010005;
typedef unsigned int uint;
typedef unsigned long long ull;
struct TNode {
    uint l, r;
    ull lazy, sum;
    int left, right;
};
TNode seg[(MAXN << 2) + 5];
int sp = 0, TRoot = 1;
/* int buildSegTree(int l, int r) { // 一开始全是0
    int i = ++sp;
    seg[i].l = l, seg[i].r = r;
    seg[i].lazy = 0;
    if (l == r) {
        seg[i].sum = 0;
        seg[i].left = seg[i].right = 0;
        return i;
    }
    else {
        int mid = (l + r) / 2;
        seg[i].left = buildSegTree(l, mid);
        seg[i].right = buildSegTree(mid + 1, r);
        seg[i].sum = seg[seg[i].left].sum + seg[seg[i].right].sum;
        return i;
    }
}*/

// 只向下建立一个节点
inline int buildSegTree(uint l, uint r) {
    int pos = ++sp;
    seg[pos].l = l, seg[pos].r = r;
    seg[pos].lazy = seg[pos].sum = 0;
    seg[pos].left = seg[pos].right = 0;
    return pos;
}

/* 这个题的n非常非常大，因此不可能建够所有的节点
 * 线段树可以先只建立一部分，最笼统的，细化的区间在有pushdown需求时再进行。
 */
void pushdown(int rt) {
    if (!seg[rt].lazy) return;
    /*if (!seg[rt].left && !seg[rt].right) {
        uint mid = seg[rt].l + (seg[rt].r - seg[rt].l) / 2;
        seg[rt].left = buildSegTree(seg[rt].l, mid);
        seg[rt].right = buildSegTree(mid + 1, seg[rt].r);
    }*/
    seg[seg[rt].left].sum += seg[rt].lazy * (seg[seg[rt].left].r - seg[seg[rt].left].l + 1);
    seg[seg[rt].left].lazy += seg[rt].lazy;
    seg[seg[rt].right].sum += seg[rt].lazy * (seg[seg[rt].right].r - seg[seg[rt].right].l + 1);
    seg[seg[rt].right].lazy += seg[rt].lazy;
    seg[rt].lazy = 0;
}
void update(int rt, uint left, uint right, ull dx) {
    // 当前节点的区间小于待更新区间
    if (left <= seg[rt].l && seg[rt].r <= right) {
        seg[rt].sum += dx * (seg[rt].r - seg[rt].l + 1);
        seg[rt].lazy += dx;
        return;
    }
    if (!seg[rt].left && !seg[rt].right) {
        uint mid = seg[rt].l + (seg[rt].r - seg[rt].l) / 2;
        seg[rt].left = buildSegTree(seg[rt].l, mid);
        seg[rt].right = buildSegTree(mid + 1, seg[rt].r);
    }
    pushdown(rt);
    if (right <= seg[seg[rt].left].r)
        update(seg[rt].left, left, right, dx);
    else if (left >= seg[seg[rt].right].l)
        update(seg[rt].right, left, right, dx);
    else {
        update(seg[rt].left, left, right, dx);
        update(seg[rt].right, left, right, dx);
    }
    seg[rt].sum = seg[seg[rt].left].sum + seg[seg[rt].right].sum;
}

ull query(int rt, uint left, uint right) {
    if (left <= seg[rt].l && seg[rt].r <= right )
        return seg[rt].sum;
    if (seg[rt].r < left || seg[rt].l > right)
        return 0;
    
    if (!seg[rt].left && !seg[rt].right) {
        uint mid = seg[rt].l + (seg[rt].r - seg[rt].l) / 2;
        seg[rt].left = buildSegTree(seg[rt].l, mid);
        seg[rt].right = buildSegTree(mid + 1, seg[rt].r);
    }
    pushdown(rt);
    ull q1 = query(seg[rt].left, left, right), q2 = query(seg[rt].right, left, right);
    return  q1+q2 ;
}


int main()
{
    int m;
    uint n;
    scanf("%u%d", &n, &m);
    buildSegTree(1, n);
    while (m--) {
        char op; uint l, r;
        scanf(" %c %u %u", &op,&l, &r);
        if (op == 'H')
            update(TRoot, l, r, 1);
        else if (op == 'Q')
            printf("%llu\n", query(TRoot, l, r));
    }
    return 0;
}