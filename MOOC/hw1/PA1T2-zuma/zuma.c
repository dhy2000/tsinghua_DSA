#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    char color;
    struct Node *prev, *next;
}Node, *listnode;
listnode head, tail;

listnode newNode(char col, listnode pv, listnode nx) {
    listnode nd = (listnode)malloc(sizeof(Node));
    nd->color = col; nd->prev = pv; nd->next = nx;
    return nd;
}

listnode insert(listnode pos, char col) {
    // assert pos != tail
    listnode nd = newNode(col, pos, pos->next);
    nd->next->prev = nd;
    nd->prev->next = nd;
    return nd;
}

listnode delNode(listnode bg, listnode ed) {
    // delete all nodes between bg with ed, assert bg->...->ed
    listnode pv = bg->prev, nx = ed->next;
    pv->next = nx; nx->prev = pv;
    listnode pt = bg;
    while (pt != ed) {
        listnode pdel = pt;
        pt = pt->next;
        free(pdel);
    }
    return pv;
}

char s[10005];
void buildList() {
    head = newNode(0, NULL, NULL);
    tail = newNode(0, NULL, NULL);
    head->next = tail; tail->prev = head;
    for (int i = 0; s[i] && isupper(s[i]); i++) {
        insert(tail->prev, s[i]);
    }
}

listnode count(int cnt) {
    listnode pt = head;
    for (int i = 0; i < cnt; i++) {
        if (pt->next == tail)break;
        else pt = pt->next;
    }
    return pt;
}

listnode zuma(listnode pos) {
    if (!pos->color || head->next == tail) return NULL;
    int cnt = 1;
    listnode ed = pos;
    while (ed->next->color == pos->color)cnt++, ed = ed->next;
    listnode bg = pos;
    while (bg->prev->color == pos->color)cnt++, bg = bg->prev;
    if (cnt < 3) return NULL;
    else return delNode(bg, ed);
}

void disp() {
    if (head->next == tail) putchar('-');
    for (listnode pt = head->next; pt != tail; pt = pt->next) {
        putchar(pt->color);
    }
    putchar('\n');
}

int main() {
    fgets(s, 10002, stdin);
    buildList();
    int T; scanf("%d", &T);
    while (T--) {
        int pos; char b;
        scanf("%d %c", &pos, &b);
        listnode pt = count(pos);
        pt = insert(pt, b);
        while ((pt = zuma(pt)) != NULL);
        disp();
    }
    return 0;
}