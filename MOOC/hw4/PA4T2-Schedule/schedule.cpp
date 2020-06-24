#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
typedef unsigned int ui;
const int BUFF_SZ = 1<<20;
struct fastio{
    char inbuf[BUFF_SZ], outbuf[BUFF_SZ];
    fastio() {
        setvbuf(stdin, inbuf, _IOFBF, BUFF_SZ);
        setvbuf(stdout, outbuf, _IOFBF, BUFF_SZ);
    }
}io;

const int MAX_HEAPSIZE = 4000005;
template <typename T>
struct heap {
    T Ele[MAX_HEAPSIZE] = {}; 
    int heapsize;
    bool isdel = false;
    heap() {heapsize = 0; memset(Ele, 0, sizeof(Ele));}

    void siftdown(int pos) {
        // 维护大顶堆
        // 左儿子和右儿子里找到比自己大并且最大的元素交换，如果没有交换则停止
        T tmp = Ele[pos];
        while (pos < heapsize) {
            int nxt = pos << 1;
            if (nxt > heapsize) break;
            if (nxt + 1 <= heapsize && Ele[nxt] < Ele[nxt + 1])
                nxt++;
            if (Ele[nxt] < tmp) break;
            Ele[pos] = Ele[nxt];
            pos = nxt;
        }
        Ele[pos] = tmp;
    }
    void siftup(int pos) {
        T tmp = Ele[pos];
        while (pos > 1) {
            int fa = pos >> 1;
            if (Ele[fa] < tmp) Ele[pos] = Ele[fa];
            else break;
            pos = fa;
        }
        Ele[pos] = tmp;
    }

    inline bool empty() {return !heapsize || !(heapsize - isdel);}
    inline int size() {return heapsize - isdel;}
    inline void push(T x) {
        if (isdel) {
            Ele[1] = x;
            siftdown(1);
            isdel = false;
        }
        else {
            Ele[++heapsize] = x;
            siftup(heapsize);
        }
    }
    inline void pop() {
        if (isdel) {
            Ele[1] = Ele[heapsize--];
            siftdown(1);
        }
        else isdel = true;
    }
    inline T top() {
        if (isdel) {
            Ele[1] = Ele[heapsize--];
            siftdown(1);
            isdel = false;
        }
        return Ele[1];
    }
};
struct Task {
    ui prior;
    char name[10];
    inline bool operator < (const Task &b) const {
        if (prior != b.prior) return prior > b.prior;
        else return strcmp(name, b.name) > 0;
    }
};
heap<Task> hp;

inline ui readint() {
    ui ret = 0; char c = getchar();
    while ((c<'0'||c>'9'))c = getchar();
    while ((c>='0'&&c<='9'))ret = (ret<<1)+(ret<<3) + (c ^ '0'), c = getchar();
    return ret;
}
inline void readstr(char *dest) {
    char c = getchar();
    while (c<'a'||c>'z')c = getchar();
    while (c>='a'&&c<='z')*(dest++)=c,c=getchar();
    *dest = 0;
}

int main()
{
    int n = readint(), m = readint();
    for (int i = 1; i <= n; i++) {
        Task tsk;
        tsk.prior = readint();
        readstr(tsk.name);
        hp.push(tsk);
    }
    for (int i = 1; i <= m; i++) {
        if (hp.empty()) break;
        Task top = hp.top();
        hp.pop();
        puts(top.name);
        if (top.prior < 0x80000000) {
            top.prior <<= 1;
            hp.push(top);
        }
    }
    return 0;
}