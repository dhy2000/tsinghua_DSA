#include <stdio.h>

#define MAXN 3200005

int stk[MAXN], sp = -1;
int q[MAXN], hd = 0;
int n, m;
int op[MAXN], opsz = 0;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &q[i]);
    int overflow = 0;
    for (int i = 1; i <= n; i++) {
        stk[++sp] = i; op[opsz++] = 1;
        if (sp + 1 > m)overflow = 1;
        while (sp >= 0 && hd < n && stk[sp] == q[hd])
        {
            op[opsz++] = 2;
            sp--; hd++;
        }
    }
    if (sp == -1 && !overflow) {
        for (int i = 0; i < opsz; i++)
        {
            if (op[i] == 1)printf("push\n");
            else printf("pop\n"); 
        }
    }
    else printf("No\n");





    return 0;
}