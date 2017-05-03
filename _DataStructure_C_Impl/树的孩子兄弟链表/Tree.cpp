/*
//���Ĵ洢�ṹ
#define MaxSize 200
typedef char DataType;
//����˫�ױ�ʾ��
typedef struct PNode{	//˫�ױ�ʾ���Ľ�㶨��
	DataType data;
	int parent;		//ָʾ����˫��
}PNode;
typedef struct{		//˫�ױ�ʾ�������Ͷ���
	PNode node[MaxSize];
	int num;		//���ĸ���
}PTree;
//���ĺ��ӱ�ʾ��
typedef struct CNode{  //���ӽ������Ͷ���
	int child;
	struct CNode *next; //ָ����һ�����
}ChildNode;
typedef struct{   //n����������뺢�������ָ�빹��һ���ṹ
	DataType data;
	ChildNode *firstchild;	//���������ָ��
}DataNode;
typedef struct{				//���ӱ�ʾ�����Ͷ���
	DataNode node[MaxSize];
	int num,root;  //���ĸ������������˳����е�λ��
}CTree;
//�����ֵܱ�ʾ��
typedef struct CSNode{	//�����ֵܱ�ʾ�������Ͷ���
	DataType e;
	struct CSNode *fristchild,*nextsibling; //ָ���һ�����Ӻ���һ���ֵ�
}CSNode,*CSTree;
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//���ĺ����ֵ�������
typedef int DataType;
typedef struct CSNode{
	struct CSNode *firstchild,*nextsibling;
	DataType data;
}CSNode,*CSTree;
//���ĳ�ʼ��
void InitCSTree(CSTree *T){
	*T=0;
}
//�������ٲ���
void DestroyCSTree(CSTree *T){
	CSTree p=*T;
	if(p)
	{
		DestroyCSTree(&(p->firstchild));/*���ٵ�һ�����ӽ��*/
		DestroyCSTree(&(p->nextsibling));/*�����ֵܽ��*/
		free(p);
		*T = 0;
	}
}
//����������
void CreateCSTree(CSTree *T,DataType *e,int *index){
	if(e[*index]==0){
		*T=0;
		(*index)++;
	}else{
		*T=(CSTree)malloc(sizeof(CSNode));	//���ɽ��
		(*T)->data=e[*index];
		(*index)++;
		CreateCSTree(&((*T)->firstchild),e,index);/*������һ�����ӽ��*/
		CreateCSTree(&((*T)->nextsibling),e,index);/*�����ֵܽ��*/
		return;
	}
}
//���������
int DepCSTree(CSTree T){
	CSNode *p;
	int k,d=0;
	if(T==NULL)		//����ǿ���������0
		return 0;
	p=T->firstchild;	//pָ�����ĵ�һ���ӽ��
	while(p!=NULL){
		k=DepCSTree(p);	//����p�������
		if(d<k)
			d=k;		//*d��������������
		p=p->nextsibling;  //����p����һ�����
	}
	return d+1;
}
//�����ȸ�����
void PreTraverseCSTree(CSTree T,void (*visit)(DataType *e)){
	if(T)
	{
		(*visit)(&T->data);
		PreTraverseCSTree(T->firstchild,visit);
		PreTraverseCSTree(T->nextsibling,visit);
	}
}
//���ĺ������
void PostTraverseCSTree(CSTree T,void(*visit)(DataType *e)){
	if(T)
	{
		PostTraverseCSTree(T->firstchild,visit);
		(*visit)(&T->data);
		PostTraverseCSTree(T->nextsibling,visit);
	}
}
//������Ľ��
void DisplayCSTree(DataType *e){
	printf("%2c",*e);
}
void main(){
	int test[] = {'A','B','E',0,'F','H',0,'I',0,'J',0,0,0,'C',0,'D','G',0,0,0,0};
	int h=0;
	CSTree T;
	InitCSTree(&T);
	CreateCSTree(&T,test,&h);
	printf("�����ȸ����������:\n");
	PreTraverseCSTree(T,DisplayCSTree);
	printf("\n");
	printf("���ĺ�����������:\n");
	PostTraverseCSTree(T,DisplayCSTree);
	printf("\n");
	printf("���������:%2d",DepCSTree(T));
	printf("\n");
	DestroyCSTree(&T);
	system("pause");
}