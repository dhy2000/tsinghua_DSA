// 前缀和
#include <stdio.h>

#define MAXN 10000005
int cnt[MAXN] = {0}; // Prefix Sum

int main() {
    int n, q;
    int min_range = 0x7FFFFFFF, max_range = 0;
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        if (x < min_range)min_range = x;
        if (x > max_range)max_range = x;
        cnt[x] = 1;
    }
    for (int i = min_range + 1; i <= max_range ; i++)
        cnt[i] += cnt[i - 1];
    for (int T = 0; T < q; T++) {
        int l, r;
        scanf("%d%d", &l, &r);
        if (r > max_range)r = max_range;
        if (l < min_range)l = min_range;
        if (l == 0) printf("%d\n", cnt[r]);
        else printf("%d\n", cnt[r] - cnt[l - 1]);
    }
    return 0;
}