// BFS and Hash
// Use Cantor to hash a permutation
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
/* ---- Defination of Permutation and Cantor ---- */
const int N = 8;
const int fact[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
int perm[9];
int hash(int p[]) {
    int sum = 0;
    for (int i = 1; i <= N; i++) {
        int cnt = 0;
        for (int j = i + 1; j <= N; j++) {
            if (p[j] < p[i]) cnt++;
        }
        sum += fact[N - i] * cnt;
    }
    return sum;
}
void unhash(int idx, int p[]) {
    bool vis[N + 1] = {};
    for (int i = 1; i <= N; i++) {
        int n = idx / fact[N - i];
        idx %= fact[N - i];
        for (int j = 1; j <= N; j++) {
            if (!vis[j]) {
                if (!n) {p[i] = j; vis[j] = 1; break;}
                n--;
            }
        }
    }
}

/* ---- Defination of BFS and Queue ---- */
template<typename T>
struct Queue {
    struct LNode {
        T val;
        struct LNode *next;
    };
    LNode _memPool[100005], *_pool_sp = _memPool;
    LNode *_recBin[100005], **_rec_sp = _recBin;
    inline LNode* newNode (T v) {
        LNode *ret;
        if (_rec_sp == _recBin) ret = _pool_sp++;
        else ret = *--_rec_sp;
        ret->val = v;
        ret->next = NULL;
        return ret;
    }
    inline void rmNode(LNode *del) {
        *(_rec_sp++) = del;
    }

    LNode *head = NULL, *tail = NULL;
    int siz = 0;
    inline bool empty() {return head == NULL;}
    inline bool size() {return siz;}
    inline void push(T v) {
        if (head == NULL && tail == NULL) 
            head = tail = newNode(v);
        else {
            tail->next = newNode(v);
            tail = tail->next;
        }
        siz++;
    }
    inline void pop() {
        if (head == NULL || siz == 0) return ;
        if (head == tail) {
            rmNode(head);
            head = tail = NULL;
            siz = 0;
        }
        else {
            LNode *del = head;
            head = head->next;
            rmNode(del);
            siz--;
        }
    }
    inline T front() {
        if (siz) return head->val;
        else return 0;
    }
};

Queue<int> q;
int dis[40321];
void BFS_all() {
    memset(dis, -1, sizeof(dis));
    q.push(0);
    dis[0] = 0;
    while (!q.empty()) {
        int cur = q.front(); q.pop();
        int nxt = -1, tmp;
        // 1. Exchange the upper and lower
        unhash(cur, perm);
        for (int i = 1; i <= 4; i++) {
            tmp = perm[i];
            perm[i] = perm[9 - i];
            perm[9 - i] = tmp;
        }
        
        nxt = hash(perm);
        if (dis[nxt] == -1) {dis[nxt] = dis[cur] + 1; q.push(nxt);}
        // 2. Loop left shift (inverse `loop right`)
        unhash(cur, perm);
        tmp = perm[1];
        for (int i = 1; i <= 3; i++) perm[i] = perm[i + 1];
        perm[4] = tmp;
        tmp = perm[8];
        for (int i = 8; i >= 6; i--) perm[i] = perm[i - 1];
        perm[5] = tmp;
        nxt = hash(perm);
        if (dis[nxt] == -1) {dis[nxt] = dis[cur] + 1; q.push(nxt);}
        // 3. Rotate anticlockwise (inverse clockwise)
        unhash(cur, perm);

        tmp = perm[2]; perm[2] = perm[3]; perm[3] = perm[6]; perm[6] = perm[7]; perm[7] = tmp;
        
        nxt = hash(perm);
        if (dis[nxt] == -1) {dis[nxt] = dis[cur] + 1; q.push(nxt);}
    }
}


#ifndef _OJ_
#include <cassert>
void checkAll() {
    freopen("outlist.txt", "w", stdout);
    for (int i = 0; i < 40320; i++) {
        unhash(i, perm);
        printf("%d [", i);
        for (int j = 1; j <= N; j++) {
            printf("%d%c",perm[j], j==N?']':',');
        }
        printf(" : %d\n", dis[i]);
        assert(hash(perm) == i);
    }
}
#endif
inline int readint() {
    int ret = 0; char c = getchar();
    while ((c<'0'||c>'9'))c = getchar();
    while ((c>='0'&&c<='9'))ret = (ret<<1)+(ret<<3) + (c ^ '0'), c = getchar();
    return ret;
}
int main()
{
    BFS_all();
    int q = readint();
    while (q--) {
        for (int i = 1; i <= N; i++) perm[i] = readint();
        printf("%d\n", dis[hash(perm)]);
    }

    return 0;
}