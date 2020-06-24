#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
typedef long long ll;
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
// 最长路径
int dis[MAXV];
bool vis[MAXV];
struct P {
    int dis, id;
    inline bool operator < (const P &b) const {
        if (dis != b.dis) return dis < b.dis;
        else // 节点编号小为大，先出堆
            return b.id < id;
    }
};
heap<P> pq;
void Dijkstra(int start) {
    memset(dis, -1, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[start] = 0;
    pq.push({0, start});
    while (!pq.empty()) {
        P top = pq.top();
        pq.pop();
        if (dis[top.id] > top.dis) continue;
        vis[top.id] = 1;
        for (int i = head[top.id]; i != 0; i = edge[i].next) {
            if (!vis[edge[i].to] && dis[edge[i].to] < dis[top.id] + edge[i].w) {
                dis[edge[i].to] = dis[top.id] + edge[i].w;
                pq.push({dis[edge[i].to], edge[i].to});
            }
        }
    }
}

int main()
{
    V = read(); E = read();
    for (int i = 0; i < E; i++) {
        int u=read(), v=read(), w=read();
        addEdge(u,v,w);
    }
    for (int i = 1; i <= V; i++) {
        if (indeg[i] == 0)
            addEdge(0, i, 0);
    }
    Dijkstra(0);
    int maxdis = 0;
    for (int i = 1; i <= V; i++) {
        if (dis[i] > maxdis) maxdis = dis[i];
    }
    printf("%d\n", maxdis);

    return 0;
}