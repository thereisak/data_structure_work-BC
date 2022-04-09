#include<stdio.h>
#include<stdlib.h>
//循环链表实现约瑟夫环问题 
typedef struct LNode{
	int number;
	struct LNode *next;		
}man;
man *initLink(int n){
	//创建共n个人的循环链表 
    man *p=(man*)malloc(sizeof(man));;//头指针 
	man *temp=(man*)malloc(sizeof(man));//首元节点 
	temp->number=1;
	temp->next=NULL;
	p=temp;//头指针指向首元节点

	for (int i = 2; i <=n; i++) {
        man *a = (man*)malloc(sizeof(man));
        a->number = i;
        a->next = NULL;
        temp->next = a;
        temp = temp->next;
    }
    temp->next=p;//将单链表首尾相连得到循环链表 
    return p;
}
void Joseph(man *J,int k,int m){
	man *temp=J;
	man *tail=J;
	while (tail->next != J) {//找第一个节点的上一个节点 
        tail = tail->next;
    }   
	while(temp->number!=k){//查找number为k的人 
		tail=temp;
		temp=temp->next;
	}
	 while (temp->next !=temp) {//进行淘汰至只剩一人 
     //从第k个人开始，找到 第m个人的位置temp，及第m-1个人的位置tail 
        for (int i=1; i<m; i++) {
            tail =temp;
            temp =temp->next;
        }
        tail->next = temp->next;//移除temp 
        printf("编号为%d的人被淘汰\n", temp->number);
        free(temp);
        temp = tail->next;//取被淘汰者的下一个开始新的报数 
    } 
    printf("编号为%d的人是胜利者\n",temp->number);
	free(temp); 
} 
int main(){
	int n,k,m;
	printf("请输入旅客个数n，从第几人开始报数k，报数值m\n");
	scanf("%d%d%d",&n,&k,&m);
	man *J=initLink(n);
	Joseph(J,k,m);
	return 0;
}