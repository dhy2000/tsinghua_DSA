#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#define MAX 4000
#define DICLEN 15000
using namespace std;

char * DiligentMan = new char[9];
long long int Maxtimes = 1;

unsigned int BKDRHash(char* str){
	unsigned long long int seed = 131;
	unsigned long long int hash = 0;
	while(*str!=0)
		hash = hash*seed +(long long) (*str++);
	return hash % 15000;
}

typedef struct Node{
	char* data ;
	long long int times;
	bool empty;
	struct Node* next;
	
}Node;

typedef struct Hashtable{
	Node* phead;
	Node** chainhash;
}Hashtable;
//借鉴 网上hashtable的代码实现 
Node* create_node()
{//开辟节点
    Node* pnode = (Node*)malloc(sizeof(Node));
    memset(pnode, 0, sizeof(Node));

    pnode->data = (char*)malloc(9* sizeof(char));
    memset(pnode->data, 0,  9*sizeof(char));
    pnode->next = NULL;
	
    return pnode;
}

Hashtable* create_hash()
{//创建hash表
    Hashtable* new_hash_table = (Hashtable*)malloc(sizeof(Hashtable));
    memset(new_hash_table, 0, sizeof(Hashtable));

    new_hash_table->phead = create_node();
    new_hash_table->chainhash = (Node**)malloc(DICLEN * sizeof(Node*));

    for(int i = 0; i < DICLEN; i++){        
        new_hash_table->chainhash[i] = (Node*)malloc(sizeof(Node));
        
        memset(new_hash_table->chainhash[i], 0, sizeof(Node));
        new_hash_table->chainhash[i]->empty = true;
    }
	
    return new_hash_table;
}

//插入同时更新刷题最多的人和刷题数 
bool  insert(Hashtable* hash, Node* phead, char* data){
	if(hash == NULL)
		return false;
	
	if(hash->chainhash[BKDRHash(data)]->empty==true){
		Node* newnode = create_node();
		strcpy(newnode->data,data);
		newnode->next = NULL;
		newnode->times = 1;
		hash->chainhash[BKDRHash(data)]->data = newnode->data;
		hash->chainhash[BKDRHash(data)]->next = newnode->next;
		hash->chainhash[BKDRHash(data)]->empty = false;
		hash->chainhash[BKDRHash(data)]->times = newnode->times;//更新刷题数 
		free(newnode);
		return true;
	}
//以链表的方式解决冲突并记录结果 
	
	else if(strcmp(data,hash->chainhash[BKDRHash(data)]->data)==0){
		hash->chainhash[BKDRHash(data)]->times++;
		if(hash->chainhash[BKDRHash(data)]->times > Maxtimes){
			Maxtimes = hash->chainhash[BKDRHash(data)]->times;
			strcpy(DiligentMan,data);
		}
		else{
			phead = hash->chainhash[BKDRHash(data)];
			while(phead->next!= NULL&&(strcmp(data,phead->next->data)!=0))
				phead = phead->next;
			if(phead->next==NULL){
				phead->next = create_node();
				strcpy(phead->next->data,data);
				phead->next->next= NULL;
				phead->next->empty = false;
				phead->next->times++;
			}
			else{
				phead->next->times++;
				if(phead->next->times>Maxtimes){
					Maxtimes = phead->next->times;
					strcpy( DiligentMan,phead->next->data);
				}
			}
			
		}
	}
}
int main(){
	setvbuf(stdin, new char[1 << 20], _IOFBF, 1 << 20);
	setvbuf(stdout, new char[1 << 20], _IOFBF, 1 << 20);
	int n;
	scanf("%d",&n);
	Hashtable* record  = create_hash();
	char* name = new char[9];
	int i = 0;
//输入人名并插入至hashtable	
	while(i<n&&scanf("%s",name)!=EOF){
	insert(record,record->phead,name);
	i++;
	}
//输出刷题数最多的人并输出刷题数目 
	printf("%s %d",DiligentMan, Maxtimes);
	free(record);
	return 0;
}
