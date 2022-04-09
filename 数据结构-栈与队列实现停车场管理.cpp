#include <stdio.h>
#include <stdlib.h>
#define car_park_max 5
#include <iostream>
#include <Windows.h>
#include <time.h>
int car_queue_num=car_park_max*2;//等待队列的车辆编号 
int car_parking_sum=0;//停车场内的车辆总数 
//链表中的节点结构
typedef struct linkStack{
    int data;
    struct linkStack * next;
}linkStack;
//stack为当前的链栈，a表示入栈元素
void push(linkStack * &stack,int a){//top为第一个元素 
   //若a为正整数，则将a存入栈中  
    	if(a>0){
	    	//创建存储新元素的节点    
        linkStack * line=(linkStack*)malloc(sizeof(linkStack));
        line->data=a;
        line->next=stack;
        stack=line; 		 
	    }    	  
      
}
int pop(linkStack * &stack){
	//若栈空，返回-1，不空则将 栈顶元素出栈，返回其值 
    if (!stack){
    	printf("栈内没有元素\n");
    	return -1;
    }   	    
        linkStack * p=stack;
        stack=stack->next;        
        int e=p->data;
        free(p);
        
    return e;
}
int stack_count(linkStack* stack){
	//返回栈的元素个数 
	int n=0;
	while(stack){
		stack=stack->next;
		n++;
	}
	return n;
}
void showStack(linkStack* stack){
	//从栈顶依次出栈内元素 
	printf("此时栈中的元素（栈顶->栈底）：");
	while(stack){
		printf("%d ",stack->data);
		stack=stack->next;
	}
	printf("\n");
} 


typedef struct Queue{//节点结构 
    int data;
    struct Queue * next;
}Queue;
typedef struct {
	Queue *front;//队头指针
	Queue *rear; //队尾指针 
}linkQueue;
void InitQueue(linkQueue &Q){
    //创建空的链式队列
	Q.front=Q.rear=(Queue *)malloc(sizeof(Queue));
	if(!Q.front) exit(0);
	Q.front->next=NULL;
}
void EnQueue(linkQueue &Q,int e){
    //插入元素e为Q的队尾元素 
	Queue *p=(Queue *)malloc(sizeof(Queue));
	if(!p)exit(0);
	p->data=e;p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
}
int DeQueue(linkQueue &Q){
	//若队列为空，返回-2，队列不空，删除队头元素，返回其值 
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
	//从队头显示队列的元素	 
	linkQueue R=Q;
	printf("此时等待队列中的车辆编号（队头->队尾）：");
	while(R.front->next){
		printf("%d ",R.front->next->data);
		R.front=R.front->next;
	}
	printf("\n");
}
void Queue_into_Stack(linkQueue &Q,linkStack * &stack){
	//若栈未满，且队列中有元素，将队列的元素从头放入栈中，直到栈满或队列空 
	
	while(car_parking_sum<car_park_max&&Q.front->next){
		int a= DeQueue(Q);
		if(a>0){
			push(stack,a);
		    car_parking_sum++;
		    printf("编号为%d的车进入停车场\n",a);   
		}		
	}
	if(car_parking_sum>=car_park_max)
    	printf("停车场已满，请等待\n");
		printf("\n");
}
void Stack_out(linkStack * &stack,int n){
	//栈顶开始第n辆车离开停车场
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
    time (&now_time);//获取Unix时间戳。
    lt = localtime (&now_time);//转为时间结构。
    printf ( "现在是%d/%d %d:%d:%d   ",lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
 	printf("编号为%d的车从停车场离开，停留%d小时，收费%d元\n",pop(stack),t,t);
 	for(int i=1;i<=n-1;i++)
 	push(stack,pop(temp));
 	car_parking_sum--;	
 	}	 
}
void Car_into_queue(linkQueue &Q){
	int t=rand()%3+1;
 	Sleep(t * 100); 	
 	EnQueue(Q,car_queue_num);
	printf("编号为%d的车进入等待队列\n",car_queue_num);
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
	printf("停车场最大容量为%d辆，收费为1元/小时\n",car_park_max);
	printf("\n");
	Simulation_parking_lot(Q,stack);

	return 0;
} 