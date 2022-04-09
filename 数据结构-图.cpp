#include<stdio.h> 
#define  MAX_VERTEX_NUM 20//最大顶点个数
#define  INF 999//定义无穷大 
typedef struct ArcNode{
    int adjvex;//边的箭头点在数组中的位置下标
    struct ArcNode * nextarc;
    int weight;//权值 
}ArcNode;
typedef struct VNode{
    int data;//数据域
    ArcNode * firstarc;//第一条边
}VNode,AdjList[MAX_VERTEX_NUM];//链表头结点的数组
typedef struct {
    AdjList vertices;
    int vexnum,arcnum;//顶点数和边或弧数
}ALGraph;
bool visited[MAX_VERTEX_NUM];
void CountOutDegree(ALGraph *G){
	//输出各顶点的出度 
	int n=G->vexnum;//顶点个数 
	int out[n]; 
	for(int i=0;i<n ;i++){
		ArcNode *p=G->vertices[i].firstarc;
		out[i]=0;
		while(p){//当链表未到末尾 
			out[i]++;
			p=p->nextarc;
		}
	}
	printf("各个点的出度:");		
	for(int i=0;i<n ;i++)
	printf("%d	",out[i]);
	printf("\n");		
}
void CountInDegree(ALGraph *G){
	//输出各顶点的入度 
	int n=G->vexnum;
	int a[n];
	for(int i=0;i<n ;i++)a[i]=0;//初始化 
	for(int i=0;i<n ;i++){
		ArcNode *p=G->vertices[i].firstarc;
		while(p){
			int invex=p->adjvex;//顶点在表中的位置  
			a[invex]++;
			p=p->nextarc;
		}
	}
	printf("各个点的入度:");		
	for(int i=0;i<n ;i++)
	printf("%d	",a[i]);
	printf("\n");
}

void DFS(ALGraph *G,int v){
	//从顶点v深度优先遍历G 
	visited[v] = true;//已访问 
	printf("%d ",G->vertices[v].data);	
       ArcNode *p=G->vertices[v].firstarc;	     
		while(p){
		if(!visited[p->adjvex])DFS(G,p->adjvex);
		p=p->nextarc;
	}
}
void DFSTraverse(ALGraph *G){
	//输出G的深度优先搜索结果 
	for(int i = 0; i <G->vexnum; i++)
		visited[i] = false;
	printf("深度优先搜索依次访问了顶点：");	
	for(int i = 0; i <G->vexnum; i++)
		if(!visited[i])
			DFS(G,i);
	printf("\n");			
}
void ShowGraph(ALGraph *G){
	//显示图的顶点信息 
	printf("顶点的值：   "); 
    for(int i=0;i<G->vexnum ;i++)
     printf("%d	",G->vertices[i].data);	printf("\n");
     printf("表中的位置： ");
    for(int i=0;i<G->vexnum ;i++)
     printf("%d	",i);	printf("\n");
}
void CreateALGraph(ALGraph *&G){
	//建立一个有向带权图 
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
    //求图中任意点间的最短路径和长度 
	//初始化距离矩阵(记录权值）D、路径矩阵 P
	//初始化路径矩阵P[][]，不可达为-INF，存在边的记录尾端点，且P[i][i]=-1
	int n=G->vexnum;
	int D[n][n];int P[n][n];		
	int i,j,k,t,w;
	for(i=0;i<n;i++)
	for(j=0;j<n;j++){
		D[i][j]=INF;
		P[i][j]=-INF;
	}	
	for(i=0;i<n;i++){//对角线赋值 
		D[i][i]=0;//到自身距离为0 
		P[i][i]=-1;//到自身路径用-1表示 
	}  
	for(i=0;i<4;i++){
		ArcNode *p=G->vertices[i].firstarc;		
		while(p){
		t=p->adjvex;w=p->weight;	
		D[i][t]=w;P[i][t]=i;//尾端到箭头的边记录尾端值 
		p=p->nextarc;
		}
	}
	//输出初始信息 
	printf("初始距离矩阵为：\n");
	for(i=0;i<4;i++){	
	for(j=0;j<4;j++)
	printf("%d	",D[i][j]);
	printf("\n");
	}	
	printf("初始路径矩阵为：（记录邻接表中的位置）\n");
	for(i=0;i<4;i++){	
	for(j=0;j<4;j++)
	printf("%d	",P[i][j]);
	printf("\n");
	}	
	
	 //计算距离矩阵和路径矩阵
    for(k=0;k<n;k++)	  
    for(i=0;i<n;i++)   
    for(j=0;j<n;j++)   
     if(D[i][j]>D[i][k]+D[k][j]){
     	 D[i][j]=D[i][k]+D[k][j]; 
     	 P[i][j]=k;
     } 
	 //输出计算后的P、D矩阵  
   	printf("计算后距离矩阵为：\n");
	for(i=0;i<4;i++){	
	for(j=0;j<4;j++)
	printf("%d	",D[i][j]);
	printf("\n");
	}	
	printf("计算后路径矩阵为：\n");
	for(i=0;i<4;i++){	
	for(j=0;j<4;j++)
	printf("%d	",P[i][j]);
	printf("\n");
	}
	//给出任意两点间的最短路径和距离
	for(i=0;i<n;i++)   
    for(j=0;j<n;j++){
	//计算路径
	if(P[i][j]==-INF){
	printf("%d点和%d点不可达\n",i+1,j+1);
	continue;		
	} 
	if(i==j)continue;//到自身的点不输出
	
	int record[n],s,temp;record[n-1]=j;s=n-1;temp=j;
	while(P[i][temp]!=-1){		
		record[--s]=P[i][temp];
		temp=P[i][temp];
	} 
	printf("%d到%d的最短路径为：",i+1,j+1);
 	for(s=s;s<n;s++)
 	printf("%d-->",record[s]+1);
 	printf(",距离为%d\n",D[i][j]);
    }	 
}
int main(){
	ALGraph *G=new ALGraph();
	CreateALGraph(G);ShowGraph(G);DFSTraverse(G);
	CountInDegree(G);CountOutDegree(G);
	Floyd(G); 
}
	
	

