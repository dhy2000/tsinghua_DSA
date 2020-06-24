#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char A[100005], B[100005], AA[200005];
int main()
{
    while (scanf("%s %s", A, B) != EOF) {
        strcpy(AA, A);
        strcat(AA, A);
        if (strlen(A) == strlen(B) && strstr(AA, B) != NULL) puts("YES");
        else puts("NO");
    }

    return 0;
}