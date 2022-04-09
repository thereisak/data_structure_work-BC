#include<stdio.h>
#include <malloc.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 10
#define LISTINCREMENT 1
typedef struct{ 
	int *elem;//�洢�ռ��ַ 
	int length;//��ǰ���� 
	int listsize;//�洢���� 
}SqList;
void InitList_Sq(SqList &L){//���������Ա� 
	;
	L.elem=(int *) malloc(LIST_INIT_SIZE*sizeof(int));
	if(! L.elem) exit (0);
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	//return L;
}
SqList ListInsert_Sq(SqList &L,int n,int e){
	//������˳���L�е�n��λ��֮ǰ����Ԫ��e
	 if(n<1||n>L.length+1){
	    printf("����λ��n��ֵ���Ϸ�\n");//n��ֵ���Ϸ�
	    exit(0);
     } 
	 if(L.length>=L.listsize){//�ռ䲻�������ӷ��� 
 		L.elem=(int *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(int));
 		if(!L.elem){
 			printf("�ռ����ʧ��/n");
		    exit(0);
	    } 
		 L.listsize+=LISTINCREMENT;		
 	} 

	 for(int j=L.length-1;j>=n-1;j--) //���� 
	 L.elem[j+1]=L.elem[j];
	 L.elem[n-1]=e;
	 ++L.length;
	 return L; 	 
} 
int ListDelete_Sq(SqList &L,int n){
	//��˳�����Ա�L��ɾ����n��Ԫ�� �����ر�ɾ����Ԫ�� 
	if(n<1||n>L.length){//n��ֵ���Ϸ�
		printf("ɾ��λ��n��ֵ���Ϸ�\n");
		exit(0);
	}
	
	int e=L.elem[n-1];
	for(int i=n-1;i<L.length-1;i++)//ǰ�� 
	L.elem[i]=L.elem[i+1];
	L.length--; 
	return e;
}
void show(SqList &L){//��ʾ���Ա� 
	for(int i=0;i<L.length;i++)
	printf("%d",L.elem[i]);
	printf("\n");
}
int main(){
    SqList  list;
    InitList_Sq(list);//�������Ա� 
	for(int i=1;i<=9;i++){
		list.elem[i-1]=i;
		list.length++;
	}
	show(list);
	list=ListInsert_Sq(list,3,9);//����������ڵ�3��λ�ò���9 
	show(list);
	int e=ListDelete_Sq(list,3);//ɾ��������ɾ��������Ԫ�� 
	printf("��ɾ����ֵΪ%d\n",e);
	show(list);
	return 0;
}








