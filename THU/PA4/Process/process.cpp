#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;
typedef long long ll;
const int MAX_N = 1000005;

const int MAX_HEAPSIZE = 1000005;

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

    inline bool empty() {return !heapsize;}
    inline int size() {return heapsize;}
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
                hp.popthenpush(top);
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