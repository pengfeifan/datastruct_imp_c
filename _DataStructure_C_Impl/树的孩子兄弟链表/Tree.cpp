/*
//树的存储结构
#define MaxSize 200
typedef char DataType;
//树的双亲表示法
typedef struct PNode{	//双亲表示法的结点定义
	DataType data;
	int parent;		//指示结点的双亲
}PNode;
typedef struct{		//双亲表示法的类型定义
	PNode node[MaxSize];
	int num;		//结点的个数
}PTree;
//树的孩子表示法
typedef struct CNode{  //孩子结点的类型定义
	int child;
	struct CNode *next; //指向下一个结点
}ChildNode;
typedef struct{   //n个结点数据与孩子链表的指针构成一个结构
	DataType data;
	ChildNode *firstchild;	//孩子链表的指针
}DataNode;
typedef struct{				//孩子表示法类型定义
	DataNode node[MaxSize];
	int num,root;  //结点的个数，根结点在顺序表中的位置
}CTree;
//孩子兄弟表示法
typedef struct CSNode{	//孩子兄弟表示法的类型定义
	DataType e;
	struct CSNode *fristchild,*nextsibling; //指向第一个孩子和下一个兄弟
}CSNode,*CSTree;
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//树的孩子兄弟链表定义
typedef int DataType;
typedef struct CSNode{
	struct CSNode *firstchild,*nextsibling;
	DataType data;
}CSNode,*CSTree;
//树的初始化
void InitCSTree(CSTree *T){
	*T=0;
}
//树的销毁操作
void DestroyCSTree(CSTree *T){
	CSTree p=*T;
	if(p)
	{
		DestroyCSTree(&(p->firstchild));/*销毁第一个孩子结点*/
		DestroyCSTree(&(p->nextsibling));/*销毁兄弟结点*/
		free(p);
		*T = 0;
	}
}
//创建树操作
void CreateCSTree(CSTree *T,DataType *e,int *index){
	if(e[*index]==0){
		*T=0;
		(*index)++;
	}else{
		*T=(CSTree)malloc(sizeof(CSNode));	//生成结点
		(*T)->data=e[*index];
		(*index)++;
		CreateCSTree(&((*T)->firstchild),e,index);/*创建第一个孩子结点*/
		CreateCSTree(&((*T)->nextsibling),e,index);/*创建兄弟结点*/
		return;
	}
}
//求树的深度
int DepCSTree(CSTree T){
	CSNode *p;
	int k,d=0;
	if(T==NULL)		//如果是空树，返回0
		return 0;
	p=T->firstchild;	//p指向树的第一孩子结点
	while(p!=NULL){
		k=DepCSTree(p);	//求子p树的深度
		if(d<k)
			d=k;		//*d保存树的最大深度
		p=p->nextsibling;  //进入p的下一个结点
	}
	return d+1;
}
//树的先根遍历
void PreTraverseCSTree(CSTree T,void (*visit)(DataType *e)){
	if(T)
	{
		(*visit)(&T->data);
		PreTraverseCSTree(T->firstchild,visit);
		PreTraverseCSTree(T->nextsibling,visit);
	}
}
//树的后根遍历
void PostTraverseCSTree(CSTree T,void(*visit)(DataType *e)){
	if(T)
	{
		PostTraverseCSTree(T->firstchild,visit);
		(*visit)(&T->data);
		PostTraverseCSTree(T->nextsibling,visit);
	}
}
//输出树的结点
void DisplayCSTree(DataType *e){
	printf("%2c",*e);
}
void main(){
	int test[] = {'A','B','E',0,'F','H',0,'I',0,'J',0,0,0,'C',0,'D','G',0,0,0,0};
	int h=0;
	CSTree T;
	InitCSTree(&T);
	CreateCSTree(&T,test,&h);
	printf("树的先根遍历结果是:\n");
	PreTraverseCSTree(T,DisplayCSTree);
	printf("\n");
	printf("树的后根遍历结果是:\n");
	PostTraverseCSTree(T,DisplayCSTree);
	printf("\n");
	printf("树的深度是:%2d",DepCSTree(T));
	printf("\n");
	DestroyCSTree(&T);
	system("pause");
}