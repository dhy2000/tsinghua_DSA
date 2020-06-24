#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Block {
    char color;
    int num;
    struct Block *prev, *next;
}Block, *ListNode;
ListNode head, tail;

ListNode addNode(ListNode to, char col, int n) {
    ListNode nd = (ListNode)malloc(sizeof(Block));
    nd->color = col; nd->num = n;
    nd->prev = to; nd->next = to->next;
    if (nd->next != NULL) nd->next->prev = nd;
    to->next = nd;
    return nd;
}

ListNode query(int count) {
    int cnt = 0;
    ListNode pt = head;
    while (cnt < count) {
        cnt += pt->num;
        if (cnt >= count) break;
        if (pt->next != NULL) pt = pt->next; else break;
    }
    return pt;
}

ListNode delNode(ListNode del) {
    ListNode ret = del->prev;
    if (del->prev)del->prev->next = del->next;
    if (del->next)del->next->prev = del->prev;
    free(del);
    return ret;
}

ListNode merge(ListNode nd) {
    if (nd->next && nd->next->color == nd->color) {
        nd->num += nd->next->num;
        delNode(nd->next);
    }
    return nd;
}

void disp() {
    if (head->next == NULL) {puts("-");return;}
    ListNode pt = head->next;
    while (pt) {
        for (int i = 0; i < pt->num; i++) {
            putchar(pt->color);
        }
        pt = pt->next;
    }
    putchar('\n');
}

char s[10005];

void buildList() {
    if (!s[0])return;
    int cnt = 1, i;
    for (i = 1; s[i]; i++) {
        if (s[i] == s[i - 1])cnt++;
        else {
            tail = addNode(tail, s[i - 1], cnt);
            cnt = 1;
        }
    }
    tail = addNode(tail, s[i - 1], cnt);
}


int main() {
    head = tail = (ListNode)malloc(sizeof(Block)); 
    head->color = head->num = 0;
    head->prev = head->next = NULL;
    gets(s); buildList();
    int T; scanf("%d", &T);
    // disp();
    while (T--) {
        int pos; char b;
        scanf("%d %c", &pos, &b);
        ListNode pt = query(pos);
        if (b == pt->color) {
            pt->num++;
            if (pt->num >= 3) {
                while (pt && pt != head && pt->num >= 3) {
                    pt = delNode(pt);
                    pt = merge(pt);
                }
            }
        }
        else if (pt->next && b == pt->next->color) {
            pt = pt->next;
            pt->num++;
            if (pt->num >= 3) {
                while (pt && pt != head && pt->num >= 3) {
                    pt = delNode(pt);
                    pt = merge(pt);
                }
            }
        }
        else {
            addNode(pt, b, 1);
        }
        disp();
    }
    return 0;
}