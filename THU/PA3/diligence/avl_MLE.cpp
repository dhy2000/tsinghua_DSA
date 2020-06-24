#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>

using namespace std;


#define max(_a,_b) ((_b)<(_a)?(_a):(_b))
#define min(_a,_b) ((_a)<(_b)?(_a):(_b))

const int AVLSIZE = 100005;

template <typename T> 
struct AVL {
public:
    template <typename TT>
    struct AVLNode {
        TT data; int cnt = 0;
        int child[2] = {0};
        int height;
        inline AVLNode () {}
        inline AVLNode (TT data) : data(data) {}
    };
    AVLNode<T> node[AVLSIZE];
    int root = 0, avlsize = 0;
    inline AVL() {
        memset(node, 0, sizeof(node));
        node[0].height = -1;
    }

    // LL: 向右转, 返回转完的子树树根
    int rotateRight(int rt) {
        int left = node[rt].child[0]; // 不平衡点左儿子
        node[rt].child[0] = node[left].child[1]; // 不平衡点左儿子更新为左儿子的右子树
        node[left].child[1] = rt; // 原不平衡点变为原左子树的右儿子
        // 更新高度
        node[rt].height = max(node[node[rt].child[0]].height, node[node[rt].child[1]].height) + 1;
        node[left].height = max(node[node[left].child[0]].height, node[rt].height) + 1;
        return left;
    }
    // RR: 向左转, 返回转完的子树树根
    int rotateLeft(int rt) {
        int right = node[rt].child[1]; // 不平衡点右儿子
        node[rt].child[1] = node[right].child[0]; // 不平衡右儿子变为right的左儿子
        node[right].child[0] = rt; // 不平衡点左旋为right的左儿子
        // 更新高度
        node[rt].height = max(node[node[rt].child[0]].height, node[node[rt].child[1]].height) + 1;
        node[right].height = max(node[node[right].child[1]].height, node[rt].height) + 1;
        return right;
    }
    // LR: 先左旋再右旋
    inline int rotateLeftRight(int rt) {
        node[rt].child[0] = rotateLeft(node[rt].child[0]);
        return rotateRight(rt);
    }
    // RL: 先右旋再左旋
    inline int rotateRightLeft(int rt) {
        node[rt].child[1] = rotateRight(node[rt].child[1]);
        return rotateLeft(rt);
    }

    int insertelem(int rt, T data) {
        if (!rt)
            rt = ((node[++avlsize] = AVLNode<T>(data)), avlsize);
        if (data < node[rt].data) { // 插入到左子树
            node[rt].child[0] = insertelem(node[rt].child[0], data);
            if (node[node[rt].child[0]].height - node[node[rt].child[1]].height >= 2) {
                if (data < node[node[rt].child[0]].data) // LL
                    rt = rotateRight(rt);
                else rt = rotateLeftRight(rt); // RL
            }
        }
        else if (node[rt].data < data) // 插入到右子树
        {
            node[rt].child[1] = insertelem(node[rt].child[1], data);
            if (node[node[rt].child[1]].height - node[node[rt].child[0]].height >= 2) {
                if (data < node[node[rt].child[1]].data) // RL
                    rt = rotateRightLeft(rt);
                else rt = rotateLeft(rt); // RR
            }
        }
        else {
            node[rt].cnt++;
        }
        // update height
        node[rt].height = max(node[node[rt].child[0]].height, node[node[rt].child[1]].height) + 1;
        return rt;
    }

    int findelem(int rt, T data) {
        while (rt) {
            if (data < node[rt].data) 
                rt = node[rt].child[0];
            else if (node[rt].data < data)
                rt = node[rt].child[1];
            else break; // equals
        }
        return rt;
    }

    void inorder_dfs(int rt) {
        if (node[rt].child[0]) inorder_dfs(node[rt].child[0]);
        cout<<node[rt].data<<" ";
        if (node[rt].child[1]) inorder_dfs(node[rt].child[1]);
    }
public:
    inline int size() {return avlsize;}
    inline void insert(T data) {root = insertelem(root, data);}
    inline int find(T data) { return findelem(root, data);}
    void disp() {
        inorder_dfs(root);
        cout<<"\n";
    }
};

AVL<string> tree;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin>>n;
    string name, mxname; 
    int maxcnt = 0;
    for (int i = 0; i < n; i++) {
        cin>>name;
        tree.insert(name);
        int ccnt = tree.node[tree.find(name)].cnt;
        if (ccnt > maxcnt) {maxcnt = ccnt; mxname = name;}
    }
    cout<<mxname<<" "<<maxcnt<<"\n"; 
    cout<<tree.avlsize<<"\n";   
    return 0;
}