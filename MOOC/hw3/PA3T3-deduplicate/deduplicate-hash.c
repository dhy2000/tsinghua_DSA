#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAXN 600005
typedef struct LNode {
    char word[45];
    bool vis;
    int next;
}LNode;
LNode llist[MAXN];
int ltot;
#define MOD 50331653
#define HASH_P 131
int hash(const char *str) {
    int hsh = 0;
    for (; *str; str++) {
        hsh = (1LL * hsh * HASH_P + (*str-'a')) % MOD;
    }
    return hsh;
}
int hashtable[MOD]; // 链表形式，0表示没有，否则是起始节点在llist[]的下标

int read() {
    int ret = 0; char c = getchar();
    while (c<'0'||c>'9')c = getchar();
    while (c>='0'&&c<='9')ret=ret*10+(c-'0'),c = getchar();
    return ret;
}
int newnode(const char *s) {
    ltot++;
    strcpy(llist[ltot].word, s);
    llist[ltot].vis = 0;
    llist[ltot].next = 0;
    return ltot;
}
int insertWord(const char *s) {
    int hsh = hash(s);
    if (!hashtable[hsh]) {
        hashtable[hsh] = newnode(s);
        return 0;
    }
    else {
        int pt = hashtable[hsh];
        while (pt) {
            if (strcmp(s, llist[pt].word)) {
                pt = llist[pt].next;
            }
            else {
                if (!llist[pt].vis) return llist[pt].vis = 1;
                else return 2;
            }
        }
        int nn = newnode(s);
        llist[nn].next = hashtable[hsh];
        hashtable[hsh] = nn;
        return 0;
    }
}
char dish[45];
int main()
{
    gets(dish);
    while (gets(dish) != NULL) {
        if (insertWord(dish) == 1) 
            puts(dish);
    }
    return 0;
}