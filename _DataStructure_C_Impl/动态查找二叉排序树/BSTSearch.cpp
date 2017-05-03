#include<stdio.h>
#include<stdlib.h>

typedef int KeyType;
//元素的定义
typedef struct{
	KeyType key;
}DataType;
//二叉排序树的类型定义
typedef struct Node{
	DataType data;
	struct Node *lchild,*rchild;
}BiTreeNode,*BiTree;
//二叉排序树的查找，如果找到元素x，则返回指向结点的指针，否则返回NULL
BiTree BSTSearch(BiTree T,DataType x){
	BiTreeNode *p;
	if(T!=NULL){
		p=T;
		while(p!=NULL){		//如果二叉排序树不为空
			if(p->data.key==x.key)	//如果找到，则返回指向该结点的指针
				return p;
			else if(p->data.key>x.key)	//如果关键字小于p指向的结点的值，则在左子树中查找
				p=p->lchild;
			else 
				p=p->rchild;	//如果关键字大于p指向的结点的值，则在右子树中查找
		}
	}
	return NULL;
}
//二叉排序树的插入操作，如果树中不存在元素x，则将x插入到正确的位置并返回1，否则返回0
int BSTInsert(BiTree *T,DataType x){
	BiTreeNode *p,*cur,*parent=NULL;
	cur=*T;
	while(cur!=NULL){
		if(cur->data.key==x.key)	//如果二叉树中存在元素为x的结点，则返回0
			return 0;
		parent=cur;		//parent指向cur的前驱结点
		if(x.key<cur->data.key)		//如果关键字小于p指向的结点的值，则在左子树中查找
			cur=cur->lchild;
		else						//如果关键字大于p指向的结点的值，则在右子树中查找
			cur=cur->rchild;
	}
	p=(BiTreeNode*)malloc(sizeof(BiTreeNode));	//生成结点
	if(!p)
		exit(-1);
	p->data=x;
	p->lchild=NULL;
	p->rchild=NULL;
	if(!parent)				//如果二叉树为空，则第一结点成为根结点
		*T=p;
	else if(x.key<parent->data.key)	//如果关键字小于parent指向的结点，则将x成为parent的左孩子
		parent->lchild=p;
	else							//如果关键字大于parent指向的结点，则将x成为parent的右孩子
		parent->rchild=p;
	return 1;
}
//从二叉排序树中删除结点s，并使该二叉排序树性质不变
void DeleteNode(BiTree *s){
	BiTree q,x,y;
	if(!(*s)->rchild){			//如果s的右子树为空，则使s的左子树成为被删结点双亲结点的左子树
		q=*s;
		*s=(*s)->lchild;
		free(q);
	}else if(!(*s)->lchild){	//如果s的左子树为空，则使s的右子树成为被删结点双亲结点的左子树
		q=*s;
		*s=(*s)->rchild;
		free(q);
	}else{	//*如果s的左、右子树都存在，则使s的直接前驱结点代替s，并使其直接前驱结点的左子树成为其双亲结点的右子树结点
		x=*s;
		y=(*s)->lchild;
		while(y->rchild){	//查找s的直接前驱结点，y为s的直接前驱结点，x为y的双亲结点
			x=y;
			y=y->rchild;
		}
		(*s)->data=y->data;	//结点s被y取代
		if(x!=*s)	//如果结点s的左孩子结点存在右子树
			x->rchild=y->lchild;	//使y的左子树成为x的右子树
		else		//如果结点s的左孩子结点不存在右子树
			x->lchild=y->lchild;	//使y的左子树成为x的左子树
		free(y);
	}
}
//在二叉排序树T中存在值为x的数据元素时，删除该数据元素结点，并返回1，否则返回0
int BSTDelete(BiTree *T,DataType x){
	if(!*T)		//如果不存在值为x的数据元素，则返回0
		return 0;
	else{
		if(x.key==(*T)->data.key)		//如果找到值为x的数据元素，则删除该结点
			DeleteNode(T);
		else if((*T)->data.key>x.key)	//如果当前元素值大于x的值，则在该结点的左子树中查找并删除之
			BSTDelete(&(*T)->lchild,x);
		else							//如果当前元素值小于x的值，则在该结点的右子树中查找并删除之
			BSTDelete(&(*T)->rchild,x);
	}
}
//中序遍历二叉排序的递归实现
void InOrderTraverse(BiTree T){
	if(T)								/*如果二叉排序树不为空*/
	{
		InOrderTraverse(T->lchild);			/*中序遍历左子树*/
		printf("%4d",T->data); 				/*访问根结点*/
		InOrderTraverse(T->rchild); 		/*中序遍历右子树*/
	}
}
void main(){
	BiTree T=NULL,p;
	DataType table[]={37,32,35,62,82,95,73,12,5};
	int n=sizeof(table)/sizeof(table[0]);
	DataType x={73},s={32};
	int i;
	for(i=0;i<n;i++)
		BSTInsert(&T,table[i]);
	printf("中序遍历二叉排序树得到的序列为：\n");
	InOrderTraverse(T);
	p=BSTSearch(T,x);
	if(p!=NULL)
		printf("\n二叉排序树查找，关键字%d存在\n",x.key);
	else
		printf("查找失败！\n");
	BSTDelete(&T,s);
	printf("删除元素%d后，中序遍历二叉排序树得到的序列为：\n",s.key);
	InOrderTraverse(T);
	printf("\n");
	system("pause");
}
/*
//平衡二叉排序树
//当平衡二叉排序树失去平衡时，对LL型的调整
BSTree b;
b=p->lchild;//p是根结点，b指向p的左子树的根结点
p->lchild=b->rchild;//将b的右子树作为p的左子树
b->rchild=p;//将p作为b的右子树，新树以b为根结点
p->bf=b->bf=0;//修改平衡因子
//当平衡二叉排序树失去平衡时，对LR(LRL)型的调整
BSTree b,c;//p为根结点，b为p的左子树的根结点，c为b的右子树的根结点
b=p->lchild;//b为p的左子树的根结点
c=b->rchild;//c为b的右子树的根结点
b->rchild=c->lchild;//c的左子树作为b的右子树
p->lchild=c->rchild;//c的右子树作为p的左子树
c->lchild=b;//b作为c的左子树
c->rchild=p;//p作为c的右子树，新树以c为根结点
//修改平衡因子
p->bf=-1;
b->bf=0;
c->bf=0;
//当平衡二叉排序树失去平衡时，对RL(RLR)型的调整
BSTree b,c;//p为根结点，b为p的右子树的根结点，c为b的左子树的根结点
b=p->rchild;//b为p的右子树的根结点
c=b->lchild;//c为b的左子树的根结点
b->lchild=c->rchild;//c的右子树作为b的左子树
p->rchild=c->lchild;//c的左子树作为p的右子树
c->lchild=p;//p作为c的左子树
c->rchild=b;//b作为c的右子树，新树以c为根结点
//修改平衡因子
p->bf=1;
b->bf=0;
b->bf=0;
//当平衡二叉排序树失去平衡时，对RR型的调整
BSTree b;
b=p->rchild;//p是根结点，b指向p的右子树的根结点
p->rchild=b->lchild;//将b的左子树作为p的右子树
b->lchild=p;//将p作为b的左子树，新树以b为根结点
//修改平衡因子
p->bf=0;
b->bf=0;
//B-树.B+树的动态查找
//B-树的类型定义
#define m 4  //B-树的阶数
typedef struct BTNdoe{
	int keynum;	//每个结点中的关键字个数
	struct BTNode *parent;//指向双亲结点
	KeyType data[m+1];//结点中关键字信息
	struct BTNode *ptr[m+1];//指针向量
}BTNode,*BTree;
*/