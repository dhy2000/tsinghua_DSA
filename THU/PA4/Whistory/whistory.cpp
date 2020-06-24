#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Use Hash with Link List
A double hash is included in the List Node to avoid hash conflict
*/
typedef unsigned int ui;
const int NHASH = 30001;
const ui MULT1 = 131, MULT2 = 37;
const int POOL_SIZE = 1000005;
struct LNode {
    ui hash2;
    int index; // index of input sequence
    struct LNode *next;
};
LNode _memPool[POOL_SIZE], *_pool_sp = _memPool;
LNode *htable[NHASH];
inline LNode* newNode(ui hash2, int idx) {
    _pool_sp->hash2 = hash2;
    _pool_sp->index = idx;
    _pool_sp->next = NULL;
    return _pool_sp++;
}
inline int hashQuery(ui hash1, ui hash2, int idx) {
    hash1 %= NHASH;
    for (LNode *cur = htable[hash1]; cur != NULL ; cur = cur->next) {
        if (cur->hash2 == hash2) 
            return cur->index;
    }
    return 0;
}

int n, m;
char word[1005] = {};

inline int readint() {
    int ret = 0; char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') ret = (ret<<1) + (ret<<3) + (ch ^ '0'), ch = getchar();
    return ret;
}
inline void readstr(char *dst) {
    char ch = getchar();
    while ((ch < 'a' || ch > 'z'))ch = getchar();
    while (ch >= 'a' && ch <= 'z') *(dst++) = ch, ch = getchar();
    *dst = 0;
}

int main()
{
    n = readint(), m = readint();
    ui MULT1N = 1, MULT2N = 1;
    for (int i = 1; i < n; i++) {
        MULT1N *= MULT1;
        MULT2N *= MULT2;
    }
    for (int i = 1; i <= m; i++) {
        ui hash1 = 0, hash2 = 0;
        char ch = getchar();
        while (ch < 'a' || ch > 'z') ch = getchar();
        for (int j = 0; j < n; j++) {
            word[j] = ch;
            hash1 = hash1 * MULT1 + ch;
            hash2 = hash2 * MULT2 + ch;
            ch = getchar();
        }
        // begin to query
        int resid = hashQuery(hash1, hash2, i);
        for (int j = 0; j < n; j++) {
            if (resid) break;
            hash1 -= MULT1N * word[j];
            hash1 = hash1 * MULT1 + word[j];
            hash2 -= MULT2N * word[j];
            hash2 = hash2 * MULT2 + word[j];
            resid = hashQuery(hash1, hash2, i);
        }
        if (resid == 0) {
            hash1 %= NHASH;
            if (htable[hash1] == NULL) htable[hash1] = newNode(hash2, i);
            else {
                LNode *nd = newNode(hash2, i);
                nd->next = htable[hash1];
                htable[hash1] = nd;
            }
        }
        printf("%d\n", resid);
    }
    return 0;
}
/*
8 5
whistory
historyw
farewell
wellfare
orywhist
*/