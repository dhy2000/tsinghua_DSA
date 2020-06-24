#include <cstdio>
#include <cstring>
#include <cstdlib>

const int MAXV = 200005, MAXE = 2000005;
int V, E;
struct Edge {
    int w, to, next;
}edge[MAXE];
int head[MAXV], tot;
int indeg[MAXV];
inline void addEdge(int u, int v, int w) {
    tot++;
    edge[tot].w = w;
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot;
    indeg[v]++;
}
inline int read() {
    int ret = 0; char c = getchar();
    while ((c<'0'||c>'9'))c = getchar();
    while ((c>='0'&&c<='9'))ret = ret * 10 + (c - '0'), c = getchar();
    return ret;
}
const int MAX_HEAPSIZE = MAXE;
template <typename T>
inline void swap(T *pa, T *pb) {T tmp = *pa; *pa = *pb; *pb = tmp;}
// 维护大顶堆
template <typename T>
struct heap {
    T Ele[MAX_HEAPSIZE]; 
    int heapsize;
    heap() {heapsize = 0; memset(Ele, 0, sizeof(Ele));}
    void siftdown(int rt) {
        // 维护大顶堆
        // 左儿子和右儿子里找到比自己大并且最大的元素交换，如果没有交换则停止
        int exc = rt;
        if ((rt<<1) <= heapsize && Ele[exc] < Ele[(rt<<1)]) {
            exc = (rt<<1);
        }
        if (((rt<<1)|1) <= heapsize && Ele[exc]< Ele[((rt<<1)|1)]) {
            exc = (rt<<1)|1;
        }
        if (exc == rt) return;
        else {
            swap(&Ele[rt], &Ele[exc]);
            siftdown(exc);
        }
    }
    void siftup(int rt) {
        bool flg = false;
        while (rt != 1 && !flg) {
            if (Ele[(rt>>1)] < Ele[rt]) {
                swap(&Ele[(rt>>1)], &Ele[rt]);
            }
            else flg = true;
            rt /= 2;
        }
    }
    inline void clear() {heapsize = 0; memset(Ele, 0, sizeof(Ele));}
    inline int size() {return heapsize;}
    inline bool empty() {return !heapsize;}
    inline void push(T x) {
        Ele[++heapsize] = x;
        siftup(heapsize);
    }
    inline T pop() {
        T ret = Ele[1];
        swap(&Ele[1], &Ele[heapsize]);
        memset(&Ele[heapsize], 0, sizeof(Ele[heapsize]));
        heapsize--;
        siftdown(1);
        return ret;
    }
    inline T top() {return Ele[1];}
    inline void popthenpush(T x) {
        Ele[1] = x;
        siftdown(1);
    }

};
struct P {
    int id;
    inline bool operator < (const P &b) {
        return id > b.id;
    }
};
heap<P> hp;

int topo[MAXV], toposp = 0;
void toposort() {
    for (int i = 1; i <= V; i++) {
        if (indeg[i] == 0) {hp.push({i});}
    }
    while (!hp.empty()) {
        P tp = hp.top(); hp.pop();
        int pos = tp.id;
        for (int i = head[pos]; i != 0; i = edge[i].next) {
            indeg[edge[i].to]--;
            if (indeg[edge[i].to] == 0) {hp.push({edge[i].to});}
        }
        topo[toposp++] = pos;
    }
}
int dis[MAXV], frm[MAXV];

int prt[MAXV], prtsp = 0;

int main()
{
    V = read(); E = read();
    for (int i = 0; i < E; i++) {
        int u=read(), v=read(), w=read();
        addEdge(u,v,w);
    }
    toposort();
    int maxdis = 0, maxi = 0;
    for (int i = 0; i < toposp; i++) {
        int pos = topo[i];
        for (int j = head[pos]; j != 0; j = edge[j].next) {
            if (dis[pos] + edge[j].w > dis[edge[j].to]) {
                dis[edge[j].to] = dis[pos] + edge[j].w;
                frm[edge[j].to] = pos;
            }
        }
    }
    
    for (int i = 0; i < toposp; i++) {
        if (dis[topo[i]] > maxdis) {maxdis = dis[topo[i]]; maxi = topo[i];}
    }

    // printf("%d\n", maxdis);
    
    for (int i = maxi; i != 0; i = frm[i]) {
        prt[prtsp++] = i;
    }
    for (int i = prtsp - 1; i >= 0; i--) {
        printf("%d ", prt[i]);
    }
    
    return 0;
}