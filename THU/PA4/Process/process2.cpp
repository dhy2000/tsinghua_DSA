#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;
typedef long long ll;
const int MAX_N = 1000005;

const int MAX_HEAPSIZE = 1000005;

template <typename T>
inline void swap(T *pa, T *pb) {T tmp = *pa; *pa = *pb; *pb = tmp;}

template <typename T>
struct heap {
    T Ele[MAX_HEAPSIZE] = {}; 
    int heapsize;
    bool isdel = false;
    heap() {heapsize = 0; memset(Ele, 0, sizeof(Ele));}

    void siftdown(int pos) {
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
struct P {
    int index; // 输入的顺序
    int pid, prio, tcreate, tproc;
    // tproc: 进程的【剩余时间】，一开始是执行时间
    inline bool operator < (const P &b) const {
        // a < b: b先出队列
        if (prio != b.prio) 
            return prio < b.prio; // 优先级大先执行
        else {
            if (tcreate != b.tcreate)  
                return tcreate > b.tcreate; // 时间小先执行
            else 
                return pid > b.pid; // 进程号小先执行
        }
    }
};
heap<P> hp;

// ll endtime[MAX_N];

inline int read() {
    int ret = 0; char c = getchar();
    while ((c<'0'||c>'9')&&c!=EOF)c = getchar();
    if (c==EOF) return EOF;
    while ((c>='0'&&c<='9'))ret = ret * 10 + (c - '0'), c = getchar();
    return ret;
}

int main() {
    P top, nxt;
    int N = read();
    int CLK = 0;
    for (int i = 1; i <= N; i++) {
        nxt.index = i;
        nxt.pid = read(); nxt.prio = read(); nxt.tcreate = read(); nxt.tproc = read();
        while (!hp.empty()) {
            top = hp.top();
            if (CLK + top.tproc <= nxt.tcreate) // 执行完毕
            {
                hp.pop();
                printf("%d %d\n", top.pid, (CLK += top.tproc));
            }
            else {
                top.tproc -= (nxt.tcreate - CLK);
                // hp.popthenpush(top);
                hp.pop(); hp.push(top);
                break;
            }
        }
        CLK = nxt.tcreate;
        hp.push(nxt);
    }
    while (!hp.empty()) {
        top = hp.top();
        hp.pop();
        printf("%d %d\n", top.pid, (CLK += top.tproc));
    }
    return 0;
}
