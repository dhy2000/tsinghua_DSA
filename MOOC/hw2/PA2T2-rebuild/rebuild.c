#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 4001005
int Tsize;
int pre[MAXN], post[MAXN];
int preidx[MAXN], postidx[MAXN];
int order[MAXN];

typedef struct TNode {
    int idx;
    int lchild, rchild;
}TNode;
TNode tr[MAXN]; int sp = 1;


int read() {
    int ret = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') ret = (ret << 1) + (ret << 3) + (ch ^ '0'), ch = getchar();
    return ret; 
}
void uprt(int x) {
    if (x / 10) uprt(x / 10);
    putchar(x % 10 + '0');
}

void parseTree(int rt, int l, int r) {
    // 递归地解析子树
    // 将先序序列中的某一段解析为一棵子树，pre[l:r] = [p l ...... r ......]
    // 可以保证pre[l]是这棵子树根节点的编号，pre[l + 1]是lchild(rt)的编号
    if (l > r) return;
    tr[rt].idx = pre[l]; 
    if (l == r) return; // 自己没有叶子了
    int post_pos = postidx[pre[l]]; // 当前子树根节点在后序序列中出现的位置
    int rchild_id = post[post_pos - 1]; // 当前子树右儿子编号
    int rchild_pos = preidx[rchild_id]; // 右儿子在先序序列中的位置
    parseTree((tr[rt].lchild = (++sp)), l + 1, rchild_pos - 1);
    parseTree((tr[rt].rchild = (++sp)), rchild_pos, r);
}

void inOrder(int rt) {
    if (tr[rt].lchild) inOrder(tr[rt].lchild);
    uprt(tr[rt].idx); putchar(' ');
    if (tr[rt].rchild) inOrder(tr[rt].rchild);
}

int main()
{
    Tsize = read();
    for (int i = 1; i <= Tsize; i++){
        pre[i] = read();
        preidx[pre[i]] = i;
    }
    for (int i = 1; i <= Tsize; i++){
        post[i] = read();
        postidx[post[i]] = i;
    }
    parseTree(1, 1, Tsize);
    inOrder(1);

    return 0;
}