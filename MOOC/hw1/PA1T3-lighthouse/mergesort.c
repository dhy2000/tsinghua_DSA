#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;
typedef unsigned long long ull;

#define MAXN 4000005

ull cntrev = 0;

void merge2(int *dest, int a[], int b[], int na, int nb) {
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb) {
        if (a[i] < b[j])
            dest[k++] = a[i++];
        else 
            dest[k++] = b[j++], cntrev += 1LLU * na - i;
    }
    if (j < nb)
        while(j < nb)dest[k++] = b[j++];
    else
        while(i < na)dest[k++] = a[i++];
}

void mergesort(int arr[], int tmp[], int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    mergesort(arr, tmp, l, mid);
    mergesort(arr, tmp, mid+1, r);
    merge2(&tmp[l], &arr[l], &arr[mid+1], mid-l+1, r-mid);
    for (int i = l; i <= r; i++)
        arr[i] = tmp[i];
}

int n, y[MAXN];
int tmp[MAXN];

typedef struct Point {int x, y;}Point;
Point tower[MAXN];
int cmp(const void *a, const void *b) {
    Point *pa = (Point*)a, *pb = (Point*)b;
    return pa->x < pb->x ? -1 : 1;
}


int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &tower[i].x, &tower[i].y);
    qsort(tower, n, sizeof(Point), cmp);
    for (int i = 0; i < n; i++)
        y[i] = tower[i].y;
    mergesort(y, tmp, 0, n - 1);
    ull cnt2 = 1LLU * n * (n - 1) / 2;
    printf("%llu\n", cnt2 - cntrev);
    return 0;
}