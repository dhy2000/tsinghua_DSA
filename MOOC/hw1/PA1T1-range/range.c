// 前缀和
#include <stdio.h>

#define MAXN 10000001
int cnt[MAXN + 5] = {0}; // Prefix Sum

int main() {
    int n, q;
    
    scanf("%d%d", &n, &q);
    
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        cnt[x + 1] = 1;
    }
    for (int i = 1; i <= MAXN; i++)
        cnt[i] += cnt[i - 1];
    for (int i = 0; i < q; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%d\n", cnt[r + 1] - cnt[l]);
    }


    return 0;
}