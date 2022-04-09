#include<stdlib.h>
#include<stdio.h>
#include<string.h>
//���ṹ
typedef struct {
    int weight;//Ȩ��
    int parent, left, right;//����㡢���ӡ��Һ����������е�λ���±�
}HTNode, *HuffmanTree;
//��̬��ά����洢�շ�������� 
typedef char ** HuffmanCode;


//��HT��ѡ��parentΪ0��weight��С�������ڵ�s1��s2(�������е�λ��)
void Select(HuffmanTree HT, int end, int *s1, int *s2) {
//end��ʾ��Ž����HT�����е�����λ��
    int min1, min2;
    int i = 1;
    //�ҵ�parent=0�Ľ��
    while(HT[i].parent != 0 && i <= end){
        i++;
    }
    min1 = HT[i].weight;
    *s1 = i;   
    i++;
    while(HT[i].parent != 0 && i <= end){
        i++;
    }
    //�Ƚ���������С��min1<=min2
    if(HT[i].weight < min1){
        min2 = min1;
        *s2 = *s1;
        min1 = HT[i].weight;
        *s1 = i;
    }else{
        min2 = HT[i].weight;
        *s2 = i;
    }
    //�������ͺ��������parent=0�Ľ��Ƚ�
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

//wΪ�洢���Ȩ��ֵ�����飨����0����nΪ�����Ҷ�ӽ�����
void CreateHuffmanTree(HuffmanTree *HT, int *w, int n)
{
    if(n<=1) return; 
    int m = 2*n-1; // �շ������ܽڵ���
    *HT = (HuffmanTree) malloc((m+1) * sizeof(HTNode)); // 0�ŵ�Ԫ����
    HuffmanTree p = *HT;
    // ��ʼ������Ҷ�ӽ��
    for(int i = 1; i <= n; i++)
    {
        (p+i)->weight = *(w+i-1);
        (p+i)->parent = 0;
        (p+i)->left = 0;
        (p+i)->right = 0;
    }
    //��ʼ����Ҷ�ӽ��
    for(int i = n+1; i <= m; i++)
    {
        (p+i)->weight = 0;
        (p+i)->parent = 0;
        (p+i)->left = 0;
        (p+i)->right = 0;
    }
    //���շ�����
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
    char *cd = (char *)malloc(n*sizeof(char)); //���Ҷ�ӽڵ������ַ�������
    cd[n-1] = '\0';//���������
   
    for(int i=1; i<=n; i++){
        //������
        int start = n-1;      
        int c = i;//��ǰ����������е�λ��
        int j = HT[i].parent;       
        while(j != 0){ 
            // �Ǹ��������ӱ���Ϊ0�����Һ��ӱ���Ϊ1
            if(HT[j].left == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
            //�Ը����Ϊ���ӽ��
            c = j;
            j = HT[j].parent;
        }
        //cd�����д��±�start��ʼ��ŵ��Ǹý��ĺշ�������
        (*HC)[i] = (char *)malloc((n-start)*sizeof(char));
        strcpy((*HC)[i], &cd[start]);
    }
    //�ͷŶ�̬����
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
    printf("�ؼ�������Ϊ��{11,4,6,2,13,25,8,16}\n");
    printf("λ��	Ȩֵ	˫��	����	�Һ���	�շ�������\n") ;
    for(int i=1;i<=n;i++){  	
    	printf("%d	%d	%d	%d	%d	%s\n",i,htree[i].weight,htree[i].parent,htree[i].left,htree[i].right,htable[i]);
	} 
	for(int i=n+1;i<=2*n-1;i++){   	
    	printf("%d	%d	%d	%d	%d\n",i,htree[i].weight,htree[i].parent,htree[i].left,htree[i].right);
	} 
   
    return 0;
}