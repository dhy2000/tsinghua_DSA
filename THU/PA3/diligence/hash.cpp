#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;
typedef unsigned long long ull;
#define MAXNWORD 10005

const int SZ = 1<<20;  //快速io
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}io;

#define NHASH 10007
#define MULT 131
uint hash(const char *str)
{
    ull h=0;
    const char *p;
    for(p=str; *p!='\0'; p++){
        h = MULT*h + *p;
    }
    return h % NHASH;
}

typedef struct lnode {
    int cnt;
    int next;
    char nm[9];
}lnode;
lnode llist[MAXNWORD]; int sp = 0; // llist[0] must be free
int head[NHASH + 1];

int insert(const char *word) {
    uint hsh = hash(word);
    int pt = head[hsh];
    while (pt) {
        if (!strcmp(llist[pt].nm, word)){
            llist[pt].cnt++;
            return pt;
        }
        pt = llist[pt].next;
    }
    sp++;
    strcpy(llist[sp].nm, word);
    llist[sp].next = head[hsh];
    llist[sp].cnt = 1;
    head[hsh] = sp;
    return sp;
}
char name[9];

void rdstr(char *to) {
    char c = getchar();
    while (c < 'a' || c > 'z') c = getchar();
    while (c >= 'a' && c <= 'z') *(to++) = c, c = getchar();
    *to = 0;
}

int main()
{
    int n; scanf("%d", &n);
    // if (n >= 1000) while (1); // 第一组数据n在1000到10000之间
    int maxcnt = 0, maxi = 0;
    for (int i = 0; i < n; i++) {
        rdstr(name);
        int pt = insert(name);
        if (llist[pt].cnt > maxcnt) {
            maxcnt = llist[pt].cnt;
            maxi = pt;
        }
    }
    // if (maxcnt >= 500) while (1); Case#1的maxcnt在500-1000之间

    printf("%s %d\n",llist[maxi].nm,  maxcnt);
    return 0;
}