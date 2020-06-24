#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
const int SEGSIZE = 2500005;
typedef unsigned long long ull;
typedef unsigned int uint;
// 节点上不存l和r了，l和r的计算体现在递归过程当中
struct TNode {
    ull lazy, sum;
    int left, right;
};
TNode seg[(SEGSIZE<<2) + 5];
int TRoot = 1, sp = 1;
#define MID(l,r) ((l)+(((r)-(l))>>1))
#define leftl l
#define leftr mid
#define rightl (mid+1)
#define rightr r
#define self rt,l,r
#define lchild seg[rt].left,l,mid
#define rchild seg[rt].right,mid+1,r

// @param: 节点编号，节点对应的l和r
void pushdown(int rt, uint l, uint r) {
    if (!seg[rt].lazy) return ;
    int mid = MID(l, r);
    // int leftl = l, leftr = mid, rightl = mid + 1, rightr = r;
    seg[seg[rt].left].sum += seg[rt].lazy * (leftr - leftl + 1);
    seg[seg[rt].left].lazy += seg[rt].lazy;
    seg[seg[rt].right].sum += seg[rt].lazy * (rightr - rightl + 1);
    seg[seg[rt].right].lazy += seg[rt].lazy;
    seg[rt].lazy = 0;
}
uint qleft, qright; ull dx = 1; // 查询or更新的区间，更新加上的数值
void update(int rt, uint l, uint r) {
    // 当前节点对应的区间包含于待更新区间
    if (qleft <= l && r <= qright) {
        seg[rt].sum += dx * (r - l + 1);
        seg[rt].lazy += dx;
        return ;
    }
    int mid = MID(l, r);
    if (!seg[rt].left) { // 子节点尚未建立
        seg[rt].left = ++sp;
        seg[rt].right = ++sp;
    }
    pushdown(self);
    if (qright <= leftr)
        update(lchild);
    else if (qleft >= rightl)
        update(rchild);
    else {
        update(lchild);
        update(rchild);
    }
    seg[rt].sum = seg[seg[rt].left].sum + seg[seg[rt].right].sum;
}
ull query(int rt, uint l, uint r) {
    int mid = MID(l, r);
    // int leftl = l, leftr = mid, rightl = mid + 1, rightr = r;
    if (qleft <= l && r <= qright) 
        return seg[rt].sum;
    if (qright < l || qleft > r)
        return 0;
    if (!seg[rt].left) { // 子节点尚未建立
        seg[rt].left = ++sp;
        seg[rt].right = ++sp;
    }
    pushdown(self);
    ull ql = query(lchild), qr = query(rchild);
    return ql + qr;
}
int main()
{
    int m;
    uint n;
    scanf("%u%d", &n, &m);
    while (m--) {
        char op; uint l, r;
        scanf(" %c %u %u", &op,&l, &r);
        qleft = l, qright = r;
        if (op == 'H')
            update(TRoot, 1, n);
        else if (op == 'Q')
            printf("%llu\n", query(TRoot, 1, n));
    }
    return 0;
}