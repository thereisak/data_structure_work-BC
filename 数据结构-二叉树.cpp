#include<stdio.h>
#include<iostream>
using namespace std;
 
//����ڵ�
typedef struct node{
	char data;
	node *left;
	node *right;	
}BiTreeNode, *BiTree; 
  
//ǰ��˳����������
void createBiTree(BiTree &T){ 
//���룺ABD***C*E**
	char c;
	cin >> c;
	if ('*' == c)            
		T = NULL;
	else{	
		T = new BiTreeNode;
		T->data = c;
		createBiTree(T->left);
		createBiTree(T->right);
	}
}
 
//ǰ�����
void preTraverse(BiTree T){
	if (T)
	{
		cout << T->data << " ";
		preTraverse(T->left);
		preTraverse(T->right);
	}
	return; 
}
//�������
void midTraverse(BiTree T){
	if (T)
	{
		midTraverse(T->left);
		cout << T->data << " ";
		midTraverse(T->right);
	}
}
//��������
void postTraverse(BiTree T){
	if (T)
	{
		postTraverse(T->left);
		postTraverse(T->right);
		cout << T->data << " ";
	}
}
int main(){
	BiTree T;
    printf("�������ַ�����\n"); //ABD***C*E**                         
	createBiTree(T);
	printf("ǰ��˳�������������\n");  
	printf("ǰ����������\n");  
	preTraverse(T);
	printf("\n");printf("������������\n");
	midTraverse(T);
    printf("\n");printf("������������\n");
	postTraverse(T);
	return 0;
}