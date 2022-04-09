#include<stdio.h>
#include <malloc.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 10
#define LISTINCREMENT 1
typedef struct{ 
	int *elem;//存储空间基址 
	int length;//当前长度 
	int listsize;//存储容量 
}SqList;
void InitList_Sq(SqList &L){//建立空线性表 
	;
	L.elem=(int *) malloc(LIST_INIT_SIZE*sizeof(int));
	if(! L.elem) exit (0);
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	//return L;
}
SqList ListInsert_Sq(SqList &L,int n,int e){
	//在线性顺序表L中第n个位置之前插入元素e
	 if(n<1||n>L.length+1){
	    printf("插入位置n的值不合法\n");//n的值不合法
	    exit(0);
     } 
	 if(L.length>=L.listsize){//空间不足则增加分配 
 		L.elem=(int *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(int));
 		if(!L.elem){
 			printf("空间分配失败/n");
		    exit(0);
	    } 
		 L.listsize+=LISTINCREMENT;		
 	} 

	 for(int j=L.length-1;j>=n-1;j--) //后移 
	 L.elem[j+1]=L.elem[j];
	 L.elem[n-1]=e;
	 ++L.length;
	 return L; 	 
} 
int ListDelete_Sq(SqList &L,int n){
	//在顺序线性表L中删除第n个元素 ，返回被删除的元素 
	if(n<1||n>L.length){//n的值不合法
		printf("删除位置n的值不合法\n");
		exit(0);
	}
	
	int e=L.elem[n-1];
	for(int i=n-1;i<L.length-1;i++)//前移 
	L.elem[i]=L.elem[i+1];
	L.length--; 
	return e;
}
void show(SqList &L){//显示线性表 
	for(int i=0;i<L.length;i++)
	printf("%d",L.elem[i]);
	printf("\n");
}
int main(){
    SqList  list;
    InitList_Sq(list);//建立线性表 
	for(int i=1;i<=9;i++){
		list.elem[i-1]=i;
		list.length++;
	}
	show(list);
	list=ListInsert_Sq(list,3,9);//插入操作，在第3个位置插入9 
	show(list);
	int e=ListDelete_Sq(list,3);//删除操作，删除第三个元素 
	printf("被删除的值为%d\n",e);
	show(list);
	return 0;
}








