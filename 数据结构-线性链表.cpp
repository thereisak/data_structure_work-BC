#include<stdio.h>
#include<stdlib.h>
typedef struct LNode{
	int data;
	struct LNode *next;		
}LinkList;
LinkList *initLink(){
//初始化带头结点 链表 ，输入n个数 
	LinkList *p=(LinkList*)malloc(sizeof(LinkList));;//头指针 
	LinkList *temp=(LinkList*)malloc(sizeof(LinkList));//首元节点 
	temp->data=1;
	temp->next=NULL;
	p=temp;//头指针指向首元节点
	int n;
	printf("请输入节点个数：");
	scanf("%d", &n);
	printf("\n请输入节点的值：");
	while(n){
		int x;
		scanf("%d", &x);
		LinkList *a = (LinkList*)malloc(sizeof(LinkList));
		a->data = x;
        a->next = NULL;
        temp->next = a;
        temp = temp->next;
        n--;
	} 
/*	for (int i = 1; i < 5; i++) {
        LinkList *a = (LinkList*)malloc(sizeof(LinkList));
        a->data = i;
        a->next = NULL;
        temp->next = a;
        temp = temp->next;
    }
*/
    return p;
}
LinkList *ListInsert_L(LinkList *L,int n,int e){
//在带头结点的单链线性表L第n个位置前插入元素e 
	LinkList *temp=L;	
	int i=1;
	while(temp&&i<n){//找到要插入位置的上一个节点 
		temp=temp->next;i++;
	}
	if(!temp||i>n){
		printf("插入位置无效\n");
		exit(0);
	} 
	LinkList *a=(LinkList*)malloc(sizeof(LinkList));//创建插入节点a 
	a->data=e; 
	a->next=temp->next;
	temp->next=a;
	return L;
} 
int ListDelete_L(LinkList *L,int n){
//删除带头结点的单链线性表L第n个元素，返回被删除的值 
	LinkList *temp=L;	
	int i=1;
	while(temp->next&&i<n){//找到要删除位置的上一个节点 
		temp=temp->next;i++;
	}
	if(!temp||i>n){
		printf("删除位置无效\n");
		exit(0);
	} 
	 
	LinkList *del=NULL;//删除节点 
	del=temp->next;temp->next=del->next;
	int e=del->data;
	free(del);//释放节点 
	return e; 
}
int GetElem_L(LinkList *L,int n){
	//查找带头结点单链表的第n个元素 
	LinkList *t=L->next;
	int i=1;
	while(t&&i<n){ 
		t=t->next;i++;
	}
	if(!t||i>n){
		printf("不存在第%d个元素\n",n);
		exit(0);	  	
	} 
	return t->data;
} 
void show(LinkList *p){//输出链表 
    LinkList* temp=p;//将temp指针指向头结点
    while (temp->next) {//输出节点data直到为NULL 
        temp=temp->next;
        printf("%d",temp->data);
    }
    printf("\n");
}
int main(){
	LinkList *link=NULL;
	link = initLink();//创建单链线性表 
    show(link);
    link=ListInsert_L(link,2,1);//插入操作 ，第二个位置插入1 
    show(link);
    int e=ListDelete_L(link,2);//删除操作 ，删除第二个元素 
	printf("%d\n",e);
	show(link); 
	int x=GetElem_L(link,2);//查找 ，查找第二个元素 
	printf("%d\n",x);
    return 0;
}