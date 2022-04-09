#include <stdio.h>
#include <stdlib.h>
#define car_park_max 5
#include <iostream>
#include <Windows.h>
#include <time.h>
int car_queue_num=car_park_max*2;//�ȴ����еĳ������ 
int car_parking_sum=0;//ͣ�����ڵĳ������� 
//�����еĽڵ�ṹ
typedef struct linkStack{
    int data;
    struct linkStack * next;
}linkStack;
//stackΪ��ǰ����ջ��a��ʾ��ջԪ��
void push(linkStack * &stack,int a){//topΪ��һ��Ԫ�� 
   //��aΪ����������a����ջ��  
    	if(a>0){
	    	//�����洢��Ԫ�صĽڵ�    
        linkStack * line=(linkStack*)malloc(sizeof(linkStack));
        line->data=a;
        line->next=stack;
        stack=line; 		 
	    }    	  
      
}
int pop(linkStack * &stack){
	//��ջ�գ�����-1�������� ջ��Ԫ�س�ջ��������ֵ 
    if (!stack){
    	printf("ջ��û��Ԫ��\n");
    	return -1;
    }   	    
        linkStack * p=stack;
        stack=stack->next;        
        int e=p->data;
        free(p);
        
    return e;
}
int stack_count(linkStack* stack){
	//����ջ��Ԫ�ظ��� 
	int n=0;
	while(stack){
		stack=stack->next;
		n++;
	}
	return n;
}
void showStack(linkStack* stack){
	//��ջ�����γ�ջ��Ԫ�� 
	printf("��ʱջ�е�Ԫ�أ�ջ��->ջ�ף���");
	while(stack){
		printf("%d ",stack->data);
		stack=stack->next;
	}
	printf("\n");
} 


typedef struct Queue{//�ڵ�ṹ 
    int data;
    struct Queue * next;
}Queue;
typedef struct {
	Queue *front;//��ͷָ��
	Queue *rear; //��βָ�� 
}linkQueue;
void InitQueue(linkQueue &Q){
    //�����յ���ʽ����
	Q.front=Q.rear=(Queue *)malloc(sizeof(Queue));
	if(!Q.front) exit(0);
	Q.front->next=NULL;
}
void EnQueue(linkQueue &Q,int e){
    //����Ԫ��eΪQ�Ķ�βԪ�� 
	Queue *p=(Queue *)malloc(sizeof(Queue));
	if(!p)exit(0);
	p->data=e;p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
}
int DeQueue(linkQueue &Q){
	//������Ϊ�գ�����-2�����в��գ�ɾ����ͷԪ�أ�������ֵ 
	if(Q.front==Q.rear){//exit(0);	
		return -2;
	}
	Queue *temp=Q.front->next;
	int e=temp->data;
	Q.front->next=temp->next;
	 if (Q.rear==temp) {
        Q.rear=Q.front;
    }
	free(temp);
	return e;
}
void showQueue(linkQueue&Q){
	//�Ӷ�ͷ��ʾ���е�Ԫ��	 
	linkQueue R=Q;
	printf("��ʱ�ȴ������еĳ�����ţ���ͷ->��β����");
	while(R.front->next){
		printf("%d ",R.front->next->data);
		R.front=R.front->next;
	}
	printf("\n");
}
void Queue_into_Stack(linkQueue &Q,linkStack * &stack){
	//��ջδ�����Ҷ�������Ԫ�أ������е�Ԫ�ش�ͷ����ջ�У�ֱ��ջ������п� 
	
	while(car_parking_sum<car_park_max&&Q.front->next){
		int a= DeQueue(Q);
		if(a>0){
			push(stack,a);
		    car_parking_sum++;
		    printf("���Ϊ%d�ĳ�����ͣ����\n",a);   
		}		
	}
	if(car_parking_sum>=car_park_max)
    	printf("ͣ������������ȴ�\n");
		printf("\n");
}
void Stack_out(linkStack * &stack,int n){
	//ջ����ʼ��n�����뿪ͣ����
	 if(stack){
 		linkStack *temp=NULL;
	 for(int i=1;i<=n-1;i++){
 		push(temp,pop(stack));
 	}
 	//srand((unsigned)time(NULL));
 	int t=rand()%5+1;
 	Sleep(t * 1000);
 	time_t now_time;
    struct tm * lt;
    time (&now_time);//��ȡUnixʱ�����
    lt = localtime (&now_time);//תΪʱ��ṹ��
    printf ( "������%d/%d %d:%d:%d   ",lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
 	printf("���Ϊ%d�ĳ���ͣ�����뿪��ͣ��%dСʱ���շ�%dԪ\n",pop(stack),t,t);
 	for(int i=1;i<=n-1;i++)
 	push(stack,pop(temp));
 	car_parking_sum--;	
 	}	 
}
void Car_into_queue(linkQueue &Q){
	int t=rand()%3+1;
 	Sleep(t * 100); 	
 	EnQueue(Q,car_queue_num);
	printf("���Ϊ%d�ĳ�����ȴ�����\n",car_queue_num);
	showQueue(Q);
	printf("\n");
 	car_queue_num++;
}
void Simulation_parking_lot(linkQueue &Q,linkStack * &stack){
	Queue_into_Stack(Q,stack);
	while(stack){
		int n=rand()%stack_count(stack)+1;
		Stack_out(stack,n);
		Queue_into_Stack(Q,stack);
		Car_into_queue(Q);
	}	
}	
int main(){	
	linkStack *stack=NULL;
	linkQueue Q;
	InitQueue(Q);
	for(int i=1;i<=9;i++)
	EnQueue (Q,i);
	showQueue(Q);
	printf("ͣ�����������Ϊ%d�����շ�Ϊ1Ԫ/Сʱ\n",car_park_max);
	printf("\n");
	Simulation_parking_lot(Q,stack);

	return 0;
} 