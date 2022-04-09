#include<stdlib.h>
#include<stdio.h>
#include<string.h>
//结点结构
typedef struct {
    int weight;//权重
    int parent, left, right;//父结点、左孩子、右孩子在数组中的位置下标
}HTNode, *HuffmanTree;
//动态二维数组存储赫夫曼编码表 
typedef char ** HuffmanCode;


//在HT中选择parent为0且weight最小的两个节点s1和s2(在数组中的位置)
void Select(HuffmanTree HT, int end, int *s1, int *s2) {
//end表示存放结点在HT数组中的最终位置
    int min1, min2;
    int i = 1;
    //找到parent=0的结点
    while(HT[i].parent != 0 && i <= end){
        i++;
    }
    min1 = HT[i].weight;
    *s1 = i;   
    i++;
    while(HT[i].parent != 0 && i <= end){
        i++;
    }
    //比较两个结点大小，min1<=min2
    if(HT[i].weight < min1){
        min2 = min1;
        *s2 = *s1;
        min1 = HT[i].weight;
        *s1 = i;
    }else{
        min2 = HT[i].weight;
        *s2 = i;
    }
    //两个结点和后面的所有parent=0的结点比较
    for(int j=i+1; j <= end; j++)
    {
        if(HT[j].parent != 0){
            continue;
        }
        if(HT[j].weight < min1){
            min2 = min1;
            min1 = HT[j].weight;
            *s2 = *s1;
            *s1 = j;
        }
        else if(HT[j].weight >= min1 && HT[j].weight < min2){
            min2 = HT[j].weight;
            *s2 = j;
        }
    }
}

//w为存储结点权重值的数组（大于0），n为编码的叶子结点个数
void CreateHuffmanTree(HuffmanTree *HT, int *w, int n)
{
    if(n<=1) return; 
    int m = 2*n-1; // 赫夫曼树总节点数
    *HT = (HuffmanTree) malloc((m+1) * sizeof(HTNode)); // 0号单元不用
    HuffmanTree p = *HT;
    // 初始化所有叶子结点
    for(int i = 1; i <= n; i++)
    {
        (p+i)->weight = *(w+i-1);
        (p+i)->parent = 0;
        (p+i)->left = 0;
        (p+i)->right = 0;
    }
    //初始化非叶子结点
    for(int i = n+1; i <= m; i++)
    {
        (p+i)->weight = 0;
        (p+i)->parent = 0;
        (p+i)->left = 0;
        (p+i)->right = 0;
    }
    //建赫夫曼树
    for(int i = n+1; i <= m; i++)
    {
        int s1, s2;
        Select(*HT, i-1, &s1, &s2);
        (*HT)[s1].parent = (*HT)[s2].parent = i;
        (*HT)[i].left = s1;
        (*HT)[i].right = s2;
        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }
}
void HuffmanCoding(HuffmanTree HT, HuffmanCode *HC,int n){
    *HC = (HuffmanCode) malloc((n+1) * sizeof(char *));
    char *cd = (char *)malloc(n*sizeof(char)); //存放叶子节点编码的字符串数组
    cd[n-1] = '\0';//编码结束符
   
    for(int i=1; i<=n; i++){
        //逆序存放
        int start = n-1;      
        int c = i;//当前结点在数组中的位置
        int j = HT[i].parent;       
        while(j != 0){ 
            // 是父结点的左孩子编码为0，是右孩子编码为1
            if(HT[j].left == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
            //以父结点为孩子结点
            c = j;
            j = HT[j].parent;
        }
        //cd数组中从下标start开始存放的是该结点的赫夫曼编码
        (*HC)[i] = (char *)malloc((n-start)*sizeof(char));
        strcpy((*HC)[i], &cd[start]);
    }
    //释放动态数组
    free(cd);
}
int main()
{
    int w[8] = {11,4,6,2,13,25,8,16};
    int n = 8;
    HuffmanTree htree;
    HuffmanCode htable;
    CreateHuffmanTree(&htree, w, n);
    HuffmanCoding(htree, &htable, n);
    printf("关键字序列为：{11,4,6,2,13,25,8,16}\n");
    printf("位置	权值	双亲	左孩子	右孩子	赫夫曼编码\n") ;
    for(int i=1;i<=n;i++){  	
    	printf("%d	%d	%d	%d	%d	%s\n",i,htree[i].weight,htree[i].parent,htree[i].left,htree[i].right,htable[i]);
	} 
	for(int i=n+1;i<=2*n-1;i++){   	
    	printf("%d	%d	%d	%d	%d\n",i,htree[i].weight,htree[i].parent,htree[i].left,htree[i].right);
	} 
   
    return 0;
}