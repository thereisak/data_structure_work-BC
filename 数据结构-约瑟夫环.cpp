#include<stdio.h>
#include<stdlib.h>
//ѭ������ʵ��Լɪ������ 
typedef struct LNode{
	int number;
	struct LNode *next;		
}man;
man *initLink(int n){
	//������n���˵�ѭ������ 
    man *p=(man*)malloc(sizeof(man));;//ͷָ�� 
	man *temp=(man*)malloc(sizeof(man));//��Ԫ�ڵ� 
	temp->number=1;
	temp->next=NULL;
	p=temp;//ͷָ��ָ����Ԫ�ڵ�

	for (int i = 2; i <=n; i++) {
        man *a = (man*)malloc(sizeof(man));
        a->number = i;
        a->next = NULL;
        temp->next = a;
        temp = temp->next;
    }
    temp->next=p;//����������β�����õ�ѭ������ 
    return p;
}
void Joseph(man *J,int k,int m){
	man *temp=J;
	man *tail=J;
	while (tail->next != J) {//�ҵ�һ���ڵ����һ���ڵ� 
        tail = tail->next;
    }   
	while(temp->number!=k){//����numberΪk���� 
		tail=temp;
		temp=temp->next;
	}
	 while (temp->next !=temp) {//������̭��ֻʣһ�� 
     //�ӵ�k���˿�ʼ���ҵ� ��m���˵�λ��temp������m-1���˵�λ��tail 
        for (int i=1; i<m; i++) {
            tail =temp;
            temp =temp->next;
        }
        tail->next = temp->next;//�Ƴ�temp 
        printf("���Ϊ%d���˱���̭\n", temp->number);
        free(temp);
        temp = tail->next;//ȡ����̭�ߵ���һ����ʼ�µı��� 
    } 
    printf("���Ϊ%d������ʤ����\n",temp->number);
	free(temp); 
} 
int main(){
	int n,k,m;
	printf("�������ÿ͸���n���ӵڼ��˿�ʼ����k������ֵm\n");
	scanf("%d%d%d",&n,&k,&m);
	man *J=initLink(n);
	Joseph(J,k,m);
	return 0;
}