#include <stdio.h>
#include <stdlib.h>
typedef struct Queue{//节点结构 
    int data;
    struct Queue * next;
}Queue;
typedef struct {
	Queue *front;//队头指针
	Queue *rear; //队尾指针 
}LinkQueue;
void InitQueue(LinkQueue &Q){//创建空的链式队列
	Q.front=Q.rear=(Queue *)malloc(sizeof(Queue));
	if(!Q.front) exit(0);
	Q.front->next=NULL;
}
void EnQueue(LinkQueue &Q,int e){//插入元素e为Q的队尾元素 
	Queue *p=(Queue *)malloc(sizeof(Queue));
	if(!p)exit(0);
	p->data=e;p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;

	//Q.rear->data=e;Q.rear->next=NULL;Q.rear=Q.rear->next;
}
int DeQueue(LinkQueue &Q){
	//若队列不空，删除队头元素，返回其值 
	if(Q.front==Q.rear)exit(0);	
	Queue *temp=Q.front->next;
	int e=temp->data;
	Q.front->next=temp->next;
	 if (Q.rear==temp) {
        Q.rear=Q.front;
    }
	free(temp);
	return e;
}
int main(){
	LinkQueue Q;
	InitQueue(Q);
	int e=1;
	EnQueue (Q,e);EnQueue (Q,2);EnQueue (Q,3);
	printf("%d\n",Q.front->next->data);
	printf("%d\n",DeQueue(Q));
	printf("%d\n",Q.front->next->data);

	return 0;
} 