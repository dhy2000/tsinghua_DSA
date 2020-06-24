// Tsinghua-DSA PA3T1 Broadcast
// 图的染色问题
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VERTEX_LIM 10005
#define EDGE_LIM 30005
int V, E;
typedef struct Edge {
    int to, next;
}Edge;
Edge edge[EDGE_LIM];
int tot, head[VERTEX_LIM];
void addEdge(int u, int v) {
    tot++;
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot;
}
int read() {
    int ret = 0; char c = getchar();
    while (c<'0'||c>'9')c = getchar();
    while (c>='0'&&c<='9')ret=ret*10+(c-'0'),c = getchar();
    return ret;
}
int que[VERTEX_LIM], frt = 0, til = -1;
#define empty (frt>til)
#define push(_x) (que[++til]=(_x))
#define pop (que[frt++])
#define top (que[frt])
int vis[VERTEX_LIM];
int flg = 1;
void bfs(int start) {
    push(start);
    vis[start] = 1;
    while (!empty) {
        int pos = pop, col = vis[pos];
        for (int i = head[pos]; i; i = edge[i].next) {
            if (vis[edge[i].to]) {
                if (vis[edge[i].to] == col) {
                    flg = -1;
                    return ;
                }
                else continue;
            }
            push(edge[i].to);
            vis[edge[i].to] = 3 - col;
        }
    }
}
int main()
{
    V = read(); E = read();
    int u, v;
    for (int i = 1; i <= E; i++) {
        u = read(), v = read();
        addEdge(u, v);
        addEdge(v, u);
    }
    bfs(u);
    if (flg == 1) puts("1");
    else puts("-1");
    return 0;
}