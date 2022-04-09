#include<stdio.h> 
#define  MAX_VERTEX_NUM 20//��󶥵����
#define  INF 999//��������� 
typedef struct ArcNode{
    int adjvex;//�ߵļ�ͷ���������е�λ���±�
    struct ArcNode * nextarc;
    int weight;//Ȩֵ 
}ArcNode;
typedef struct VNode{
    int data;//������
    ArcNode * firstarc;//��һ����
}VNode,AdjList[MAX_VERTEX_NUM];//����ͷ��������
typedef struct {
    AdjList vertices;
    int vexnum,arcnum;//�������ͱ߻���
}ALGraph;
bool visited[MAX_VERTEX_NUM];
void CountOutDegree(ALGraph *G){
	//���������ĳ��� 
	int n=G->vexnum;//������� 
	int out[n]; 
	for(int i=0;i<n ;i++){
		ArcNode *p=G->vertices[i].firstarc;
		out[i]=0;
		while(p){//������δ��ĩβ 
			out[i]++;
			p=p->nextarc;
		}
	}
	printf("������ĳ���:");		
	for(int i=0;i<n ;i++)
	printf("%d	",out[i]);
	printf("\n");		
}
void CountInDegree(ALGraph *G){
	//������������� 
	int n=G->vexnum;
	int a[n];
	for(int i=0;i<n ;i++)a[i]=0;//��ʼ�� 
	for(int i=0;i<n ;i++){
		ArcNode *p=G->vertices[i].firstarc;
		while(p){
			int invex=p->adjvex;//�����ڱ��е�λ��  
			a[invex]++;
			p=p->nextarc;
		}
	}
	printf("����������:");		
	for(int i=0;i<n ;i++)
	printf("%d	",a[i]);
	printf("\n");
}

void DFS(ALGraph *G,int v){
	//�Ӷ���v������ȱ���G 
	visited[v] = true;//�ѷ��� 
	printf("%d ",G->vertices[v].data);	
       ArcNode *p=G->vertices[v].firstarc;	     
		while(p){
		if(!visited[p->adjvex])DFS(G,p->adjvex);
		p=p->nextarc;
	}
}
void DFSTraverse(ALGraph *G){
	//���G���������������� 
	for(int i = 0; i <G->vexnum; i++)
		visited[i] = false;
	printf("��������������η����˶��㣺");	
	for(int i = 0; i <G->vexnum; i++)
		if(!visited[i])
			DFS(G,i);
	printf("\n");			
}
void ShowGraph(ALGraph *G){
	//��ʾͼ�Ķ�����Ϣ 
	printf("�����ֵ��   "); 
    for(int i=0;i<G->vexnum ;i++)
     printf("%d	",G->vertices[i].data);	printf("\n");
     printf("���е�λ�ã� ");
    for(int i=0;i<G->vexnum ;i++)
     printf("%d	",i);	printf("\n");
}
void CreateALGraph(ALGraph *&G){
	//����һ�������Ȩͼ 
	G->vexnum=4;G->arcnum=8;
	for(int i=0;i<4 ;i++)
	G->vertices[i].data=i+1;
    ArcNode *arc1=new ArcNode();ArcNode *arc2=new ArcNode();ArcNode *arc3=new ArcNode();
	ArcNode *arc4=new ArcNode();ArcNode *arc5=new ArcNode();ArcNode *arc6=new ArcNode();
	ArcNode *arc7=new ArcNode();ArcNode *arc8=new ArcNode();
	arc1->adjvex=1;arc2->adjvex=2;arc3->adjvex=3;arc4->adjvex=2;
	arc5->adjvex=0;arc6->adjvex=3;arc7->adjvex=0;arc8->adjvex=2;
	arc1->weight=2;arc2->weight=6;arc3->weight=4;arc4->weight=3;
	arc5->weight=7;arc6->weight=1;arc7->weight=5;arc8->weight=12;
    arc1->nextarc=arc2;arc2->nextarc=arc3;arc3->nextarc=NULL; 
    arc4->nextarc=NULL;
	arc5->nextarc=arc6;arc6->nextarc=NULL;
	arc7->nextarc=arc8;arc8->nextarc=NULL;

	G->vertices[0].firstarc=arc1;
	G->vertices[1].firstarc=arc4;
	G->vertices[2].firstarc=arc5;
	G->vertices[3].firstarc=arc7;
}

void Floyd(ALGraph *&G){
    //��ͼ������������·���ͳ��� 
	//��ʼ���������(��¼Ȩֵ��D��·������ P
	//��ʼ��·������P[][]�����ɴ�Ϊ-INF�����ڱߵļ�¼β�˵㣬��P[i][i]=-1
	int n=G->vexnum;
	int D[n][n];int P[n][n];		
	int i,j,k,t,w;
	for(i=0;i<n;i++)
	for(j=0;j<n;j++){
		D[i][j]=INF;
		P[i][j]=-INF;
	}	
	for(i=0;i<n;i++){//�Խ��߸�ֵ 
		D[i][i]=0;//���������Ϊ0 
		P[i][i]=-1;//������·����-1��ʾ 
	}  
	for(i=0;i<4;i++){
		ArcNode *p=G->vertices[i].firstarc;		
		while(p){
		t=p->adjvex;w=p->weight;	
		D[i][t]=w;P[i][t]=i;//β�˵���ͷ�ı߼�¼β��ֵ 
		p=p->nextarc;
		}
	}
	//�����ʼ��Ϣ 
	printf("��ʼ�������Ϊ��\n");
	for(i=0;i<4;i++){	
	for(j=0;j<4;j++)
	printf("%d	",D[i][j]);
	printf("\n");
	}	
	printf("��ʼ·������Ϊ������¼�ڽӱ��е�λ�ã�\n");
	for(i=0;i<4;i++){	
	for(j=0;j<4;j++)
	printf("%d	",P[i][j]);
	printf("\n");
	}	
	
	 //�����������·������
    for(k=0;k<n;k++)	  
    for(i=0;i<n;i++)   
    for(j=0;j<n;j++)   
     if(D[i][j]>D[i][k]+D[k][j]){
     	 D[i][j]=D[i][k]+D[k][j]; 
     	 P[i][j]=k;
     } 
	 //���������P��D����  
   	printf("�����������Ϊ��\n");
	for(i=0;i<4;i++){	
	for(j=0;j<4;j++)
	printf("%d	",D[i][j]);
	printf("\n");
	}	
	printf("�����·������Ϊ��\n");
	for(i=0;i<4;i++){	
	for(j=0;j<4;j++)
	printf("%d	",P[i][j]);
	printf("\n");
	}
	//�����������������·���;���
	for(i=0;i<n;i++)   
    for(j=0;j<n;j++){
	//����·��
	if(P[i][j]==-INF){
	printf("%d���%d�㲻�ɴ�\n",i+1,j+1);
	continue;		
	} 
	if(i==j)continue;//������ĵ㲻���
	
	int record[n],s,temp;record[n-1]=j;s=n-1;temp=j;
	while(P[i][temp]!=-1){		
		record[--s]=P[i][temp];
		temp=P[i][temp];
	} 
	printf("%d��%d�����·��Ϊ��",i+1,j+1);
 	for(s=s;s<n;s++)
 	printf("%d-->",record[s]+1);
 	printf(",����Ϊ%d\n",D[i][j]);
    }	 
}
int main(){
	ALGraph *G=new ALGraph();
	CreateALGraph(G);ShowGraph(G);DFSTraverse(G);
	CountInDegree(G);CountOutDegree(G);
	Floyd(G); 
}
	
	

