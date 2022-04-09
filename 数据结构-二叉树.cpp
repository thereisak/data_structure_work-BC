#include<stdio.h>
#include<iostream>
using namespace std;
 
//定义节点
typedef struct node{
	char data;
	node *left;
	node *right;	
}BiTreeNode, *BiTree; 
  
//前序顺序建立二叉树
void createBiTree(BiTree &T){ 
//输入：ABD***C*E**
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
 
//前序遍历
void preTraverse(BiTree T){
	if (T)
	{
		cout << T->data << " ";
		preTraverse(T->left);
		preTraverse(T->right);
	}
	return; 
}
//中序遍历
void midTraverse(BiTree T){
	if (T)
	{
		midTraverse(T->left);
		cout << T->data << " ";
		midTraverse(T->right);
	}
}
//后续遍历
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
    printf("请输入字符串：\n"); //ABD***C*E**                         
	createBiTree(T);
	printf("前序顺序建立二叉树完成\n");  
	printf("前序遍历结果：\n");  
	preTraverse(T);
	printf("\n");printf("中序遍历结果：\n");
	midTraverse(T);
    printf("\n");printf("后序遍历结果：\n");
	postTraverse(T);
	return 0;
}