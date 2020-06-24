#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int read() {
    int ret = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') ret = (ret << 1) + (ret << 3) + (ch ^ '0'), ch = getchar();
    return ret; 
}
void uprt(int x) {
    if (x / 10) uprt(x / 10);
    putchar(x % 10 + '0');
}
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#ifdef _OJ_
#define MAXN 1000005
#else
#define MAXN 105
#endif
int V, E;
// 链式前向星存图
typedef struct Edge {
    int to, next;
}Edge;
Edge edge[MAXN];
int tot = 1, head[MAXN];
int indeg[MAXN]; // 入度
int dis[MAXN];

void addEdge(int u, int v) {
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
    indeg[v]++; // 增加入度
}
int _topoq[MAXN], _frt = 0, _til = -1;
#define empty() (_frt > _til)
#define push(_x) (_topoq[++_til] = _x)
#define pop() (_topoq[_frt++])
#define front() (_topoq[_frt])
void toposort() {
    while (!empty()) {
        int pos = pop();
        for (int i = head[pos]; i != 0; i = edge[i].next) {
            dis[edge[i].to] = max(dis[edge[i].to], dis[pos] + 1);
            if (!--indeg[edge[i].to]){
                push(edge[i].to);
            }
        }
    }
}

int main()
{
    V = read(); E = read();
    for (int i = 0; i < E; i++) {
        int u = read(), v = read();
        addEdge(u, v);
    }
    for (int i = 1; i <= V; i++) {
        if (!indeg[i]) {push(i);dis[i] = 1;}
    }
    toposort();
    int maxdis = 0;
    for (int i = 1; i <= V; i++) {
        maxdis = max(dis[i], maxdis);
    }
    uprt(maxdis);
    return 0;
}