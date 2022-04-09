#include<stdio.h>
#include<stdlib.h>
typedef struct LNode{
	int data;
	struct LNode *next;		
}LinkList;
LinkList *initLink(){
//��ʼ����ͷ��� ���� ������n���� 
	LinkList *p=(LinkList*)malloc(sizeof(LinkList));;//ͷָ�� 
	LinkList *temp=(LinkList*)malloc(sizeof(LinkList));//��Ԫ�ڵ� 
	temp->data=1;
	temp->next=NULL;
	p=temp;//ͷָ��ָ����Ԫ�ڵ�
	int n;
	printf("������ڵ������");
	scanf("%d", &n);
	printf("\n������ڵ��ֵ��");
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
//�ڴ�ͷ���ĵ������Ա�L��n��λ��ǰ����Ԫ��e 
	LinkList *temp=L;	
	int i=1;
	while(temp&&i<n){//�ҵ�Ҫ����λ�õ���һ���ڵ� 
		temp=temp->next;i++;
	}
	if(!temp||i>n){
		printf("����λ����Ч\n");
		exit(0);
	} 
	LinkList *a=(LinkList*)malloc(sizeof(LinkList));//��������ڵ�a 
	a->data=e; 
	a->next=temp->next;
	temp->next=a;
	return L;
} 
int ListDelete_L(LinkList *L,int n){
//ɾ����ͷ���ĵ������Ա�L��n��Ԫ�أ����ر�ɾ����ֵ 
	LinkList *temp=L;	
	int i=1;
	while(temp->next&&i<n){//�ҵ�Ҫɾ��λ�õ���һ���ڵ� 
		temp=temp->next;i++;
	}
	if(!temp||i>n){
		printf("ɾ��λ����Ч\n");
		exit(0);
	} 
	 
	LinkList *del=NULL;//ɾ���ڵ� 
	del=temp->next;temp->next=del->next;
	int e=del->data;
	free(del);//�ͷŽڵ� 
	return e; 
}
int GetElem_L(LinkList *L,int n){
	//���Ҵ�ͷ��㵥����ĵ�n��Ԫ�� 
	LinkList *t=L->next;
	int i=1;
	while(t&&i<n){ 
		t=t->next;i++;
	}
	if(!t||i>n){
		printf("�����ڵ�%d��Ԫ��\n",n);
		exit(0);	  	
	} 
	return t->data;
} 
void show(LinkList *p){//������� 
    LinkList* temp=p;//��tempָ��ָ��ͷ���
    while (temp->next) {//����ڵ�dataֱ��ΪNULL 
        temp=temp->next;
        printf("%d",temp->data);
    }
    printf("\n");
}
int main(){
	LinkList *link=NULL;
	link = initLink();//�����������Ա� 
    show(link);
    link=ListInsert_L(link,2,1);//������� ���ڶ���λ�ò���1 
    show(link);
    int e=ListDelete_L(link,2);//ɾ������ ��ɾ���ڶ���Ԫ�� 
	printf("%d\n",e);
	show(link); 
	int x=GetElem_L(link,2);//���� �����ҵڶ���Ԫ�� 
	printf("%d\n",x);
    return 0;
}