#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100
typedef char DataType;
typedef struct Node{		//二叉链表存储结构类型定义
	DataType data;			//数据域
	struct Node *lchild;	//指向左孩子结点
	struct Node *rchild;	//指向右孩子结点
}*BiTree,BitNode;
//二叉树的初始化操作
void InitBitTree(BiTree *T){
	*T=NULL;
}
//销毁二叉树操作
void DestroyBitTree(BiTree *T){
	if(*T){		//如果是非空二叉树
		if((*T)->lchild)
			DestroyBitTree(&((*T)->lchild));
		if((*T)->rchild)
			DestroyBitTree(&((*T)->rchild));
		free(*T);
		*T=NULL;
	}
}
//递归创建二叉树
void CreateBitTree(BiTree *T){
	DataType ch;
	scanf("%c",&ch);
	if(ch=='#')
		*T=NULL;
	else{
		*T=(BiTree)malloc(sizeof(BitNode));	//生成根结点
		if(!(*T))
			exit(-1);
		(*T)->data=ch;
		CreateBitTree(&((*T)->lchild));	//构造左子树
		CreateBitTree(&((*T)->rchild));	//构造右子树
	}
}
//二叉树的左插入操作
int InsertLeftChild(BiTree p,BiTree c){
	if(p){		//如果指针p不空
		c->rchild=p->lchild;	//p的原来的左子树成为c的右子树
		p->lchild=c;	//子树c作为p的左子树
		return 1;
	}
	return 0;
}
//二叉树的右插入操作
int InsertRightChild(BiTree p,BiTree c){
	if(p){		//如果指针p不空
		c->rchild=p->rchild;	//p的原来的右子树作为c的右子树
		p->rchild=c;		//子树c作为p的右子树
		return 1;
	}
	return 0;
}
//查找元素值为e的结点的指针
BiTree Point(BiTree T,DataType e){
	BiTree Q[MaxSize];	//定义一个队列，用于存放二叉树中结点的指针
	int front=0,rear=0;	//初始化队列
	BitNode *p;
	if(T){	//如果二叉树非空
		Q[rear]=T;
		rear++;

		while(front!=rear){	//如果队列非空
			p=Q[front];	//取出队头指针
			front++;	//将队头指针出队
			if(p->data==e)
				return p;
			if(p->lchild){	//如果左孩子结点存在，将左孩子指针入队
				Q[rear]=p->lchild;	//左孩子结点的指针入队
				rear++;
			}
			if(p->rchild){	//如果右孩子结点存在，将右孩子指针入队
				Q[rear]=p->rchild;	//右孩子结点的指针入队
				rear++;
			}
		}
	}
	return NULL;
}
//返回二叉树的左孩子结点元素值操作
DataType LeftChild(BiTree T,DataType e){
	BiTree p;
	if(T){		//如果二叉树不空
		p=Point(T,e);	//p是元素值e的结点的指针
		if(p&&p->lchild)		//如果p不为空且p的左孩子结点存在
			return p->lchild->data;		//返回p的左孩子结点的元素值
	}
	return 0;
}
//返回二叉树的右孩子结点元素值操作
DataType RightChild(BiTree T,DataType e){
	BiTree p;
	if(T){
		p=Point(T,e);		//p是元素值e的结点的指针
		if(p&&p->rchild)		//如果p不为空且p的右孩子结点存在
			return p->rchild->data;		//返回p的右孩子结点的元素值
	}
	return 0;
}
//二叉树的左删除操作
int DeleteLeftChild(BiTree p){
	if(p){
		DestroyBitTree(&(p->lchild));	//删除左子树
		return 1;
	}
	return 0;
}
//二叉树的右删除操作
int DeleteRightChild(BiTree p){
	if(p){
		DestroyBitTree(&(p->rchild));	//删除右子树
		return 1;
	}
	return 0;
}
//==================================================
//利用括号嵌套的字符串建立二叉链表
void CreateBitTree2(BiTree *T,char str[]){
	char ch;
	BiTree stack[MaxSize];	//定义栈，用于存放指向二叉树中结点的指针
	int top=-1;		//初始化栈顶指针
	int flag,k;
	BitNode *p;
	*T=NULL;
	k=0;
	ch=str[k];
	while(ch!='\0'){	//如果字符串没有结束
		switch(ch){
		case '(':
			stack[++top]=p;
			flag=1;
			break;
		case ')':
			top--;
			break;
		case ',':
			flag=2;
			break;
		default:
			p=(BiTree)malloc(sizeof(BitNode));
			p->data=ch;
			p->lchild=NULL;
			p->rchild=NULL;
			if(*T==NULL)	//如果是第一个结点，表示是根结点
				*T=p;
			else{
				switch(flag){
				case 1:
					stack[top]->lchild=p;
					break;
				case 2:
					stack[top]->rchild=p;
					break;
				}
			}
		}
		ch=str[++k];
	}
}
//先序遍历二叉树的递归实现
void PreOrderTraverse(BiTree T){
	if(T){
		printf("%2c",T->data);		//访问根结点
		PreOrderTraverse(T->lchild);//先序遍历左子树
		PreOrderTraverse(T->rchild);//先序遍历右子树
	}
}
//中序遍历二叉树的递归实现
void InOrderTraverse(BiTree T){
	if(T){
		InOrderTraverse(T->lchild);//中序遍历左子树
		printf("%2c",T->data);		//访问根结点
		InOrderTraverse(T->rchild);//中序遍历右子树
	}
}
//后序遍历二叉树的递归实现
void PostOrderTraverse(BiTree T){
	if(T){
		PostOrderTraverse(T->lchild);//后序遍历左子树
		PostOrderTraverse(T->rchild);//后序遍历右子树
		printf("%2c",T->data);		//访问根结点
	}
}
//先序遍历二叉树的非递归实现
void PreOrderTraverse2(BiTree T){
	BiTree stack[MaxSize];	//定义一个栈，用于存放结点的指针
	int top;		//定义栈顶指针
	BitNode *p;	//定义一个结点的指针
	top=0;	//初始化栈
	p=T;
	while(p!=NULL||top>0){
		while(p!=NULL){	//如果p不空，访问根结点，遍历左子树
			printf("%2c",p->data);	//访问根结点
			stack[top++]=p;	//将p入栈
			p=p->lchild;	//遍历左子树
		}
		if(top>0){	//如果栈不空
			p=stack[--top];		//栈顶元素出栈
			p=p->rchild;		//遍历右子树
		}
	}
}
//中序遍历二叉树的非递归实现
void InOrderTraverse2(BiTree T){
	BiTree stack[MaxSize];	//定义一个栈，用于存放结点的指针
	int top;		//定义栈顶指针
	BitNode *p;	//定义一个结点的指针
	top=0;	//初始化栈
	p=T;
	while(p!=NULL||top>0){
		while(p!=NULL){	//如果p不空，访问根结点，遍历左子树
			stack[top++]=p;	//将p入栈
			p=p->lchild;	//遍历左子树
		}
		if(top>0){	//如果栈不空
			p=stack[--top];		//栈顶元素出栈
			printf("%2c",p->data);	//访问根结点
			p=p->rchild;		//遍历右子树
		}
	}
}
//后序遍历二叉树的非递归实现
void PostOrderTraverse2(BiTree T){
	BiTree stack[MaxSize];	//定义一个栈，用于存放结点的指针
	int top;		//定义栈顶指针
	BitNode *p,*q;	//定义一个结点的指针
	top=0;	//初始化栈
	p=T;
	q=NULL;
	while(p!=NULL||top>0){
		while(p!=NULL){	//如果p不空，访问根结点，遍历左子树
			stack[top++]=p;	//将p入栈
			p=p->lchild;	//遍历左子树
		}
		if(top>0){	//如果栈不空
			p=stack[top-1];	//取栈顶元素
			if(p->rchild==NULL||p->rchild==q){	//如果p没有右孩子结点，或右孩子结点已经访问过
				printf("%2c",p->data);	//访问根结点
				q=p;
				p=NULL;
				top--;
			}else
				p=p->rchild;
		}
	}
}
void main_Traverse(){
	BiTree T,root;
	InitBitTree(&T);
	printf("根据输入二叉树的先序序列创建二叉树('#'表示结束)：\n");
	//ABD#G##EH##I##CF#J###
	CreateBitTree(&T);
	printf("二叉树的先序序列：\n");
	printf("递归：\t");
	PreOrderTraverse(T);
	printf("\n");
	printf("非递归：");
	PreOrderTraverse2(T);
	printf("\n");
	printf("二叉树的中序序列：\n");
	printf("递归：\t");
	InOrderTraverse(T);
	printf("\n");
	printf("非递归：");
	InOrderTraverse2(T);
	printf("\n");
	printf("二叉树的后序序列：\n");
	printf("递归：\t");
	PostOrderTraverse(T);
	printf("\n");
	printf("非递归：");
	PostOrderTraverse2(T);
	printf("\n");
	printf("根据括号嵌套的字符串建立二叉树:\n");
	CreateBitTree2(&root,"(a(b(c,d),e(f(,g),h(i)))");
	printf("二叉树的先序序列：\n");
	PreOrderTraverse(root);
	printf("\n");
	printf("二叉树的中序序列：\n");
	InOrderTraverse(root);
	printf("\n");
	printf("二叉树的后序序列：\n");
	PostOrderTraverse(root);
	printf("\n");
	DestroyBitTree(&T);
	DestroyBitTree(&root);
	system("pause");
}
//===================================================
//按层次打印二叉树中的结点
void LevelPrint(BiTree T){
	BiTree queue[MaxSize];	//定义一个队列，用于存放结点的指针
	BitNode *p;
	int front,rear;	//定义队列的队头指针和队尾指针
	front=rear=-1;	//队列初始化为空
	rear++;			//队尾指针加1
	queue[rear]=T;	//将根结点指针入队
	while(front!=rear){	//如果队列不为空*
		front=(front+1)%MaxSize;
		p=queue[front];	//取出队头元素
		printf("%c",p->data);	//输出根结点
		if(p->lchild!=NULL){	//如果左孩子不为空，将左孩子结点指针入队
			rear=(rear+1)%MaxSize;
			queue[rear]=p->lchild;
		}
		if(p->rchild!=NULL){	//如果右孩子不为空，将右孩子结点指针入队
			rear=(rear+1)%MaxSize;
			queue[rear]=p->rchild;
		}
	}
}
//按树状打印的二叉树
void TreePrint(BiTree T,int level){
	int i;
	if(T==NULL)	//如果指针为空，返回上一层
		return ;
	TreePrint(T->rchild,level+1);	//打印右子树，并将层次加1
	for(i=0;i<level;i++)	//按照递归的层次打印空格
		printf("	");
	printf("%c\n",T->data);	//输出根结点
	TreePrint(T->lchild,level+1);	//打印左子树，并将层次加1
}
//******************
void main_Print(){
	BiTree T,root;
	printf("根据括号嵌套(a(b(c,d),e(f(,g),h(i)))建立二叉树:\n");
	CreateBitTree2(&T,"(a(b(c,d),e(f(,g),h(i)))");
	printf("按层次输出二叉树的序列：\n");
	LevelPrint(T);
	printf("\n");
	printf("按树状打印二叉树：\n");
	TreePrint(T,1);
	printf("根据括号嵌套(A(B(D(,H),E(,I)),C(F,G)))建立二叉树:\n");
	CreateBitTree2(&root,"(A(B(D(,H),E(,I)),C(F,G)))");
	printf("按层次输出二叉树的序列：\n");
	LevelPrint(root);
	printf("\n");
	printf("按树状打印二叉树：\n");
	TreePrint(root,1);
	DestroyBitTree(&T);
	DestroyBitTree(&root);
	system("pause");
}
//==============================
//统计二叉树中叶子结点数目
int LeafCount(BiTree T){
	if(!T)				//如果是空二叉树，返回0
		return 0;
	else 
		if(!T->lchild&&!T->rchild)		//如果左子树和右子树都为空，返回1
			return 1;
		else
			return LeafCount(T->lchild)+LeafCount(T->rchild);		//将左子树叶子结点个数与右子树叶子结点个数相加
}
//统计二叉树中非叶子结点数目
int NotLeafCount(BiTree T){
	if(!T)		//如果是空二叉树，返回0
		return 0;
	else if(!T->lchild&&!T->rchild)		//如果是叶子结点，返回0
		return 0;
		else
			return NotLeafCount(T->lchild)+NotLeafCount(T->rchild)+1;		//左右子树的非叶子结点数目加上根结点的个数

}
//统计二叉树中结点数目
int TreeCount(BiTree T){
	if(T==NULL)
		return 0;
	return 1+TreeCount(T->lchild)+TreeCount(T->rchild);
}
//计算二叉树的深度
int BitTreeDepth(BiTree T){
	if(T == NULL) 
		return 0;
	return 
		BitTreeDepth(T->lchild)>BitTreeDepth(T->rchild)?1+BitTreeDepth(T->lchild):1+BitTreeDepth(T->rchild);
}
int Depth(BiTree T)
{
	if(T == NULL) 
		return 0;

	if(T->lchild==NULL&&T->rchild==NULL)
		return 1;
	return 
		Depth(T->lchild)>Depth(T->rchild) ? 1+Depth(T->lchild) : 1+Depth(T->rchild);
}
void main_Count(){
	BiTree T,root;
	int num,depth;
	printf("根据括号嵌套(a(b(c,d),e(f(,g),h(i)))建立二叉树:\n");
	CreateBitTree2(&root,"(a(b(c,d),e(f(,g),h(i)))");
	num=TreeCount(root);
	printf("二叉树结点个数=%2d\n",num);
	num=LeafCount(root);
	printf("叶子结点个数=%2d\n",num);
	num=NotLeafCount(root);
	printf("非叶子结点个数=%2d\n",num);
	depth=BitTreeDepth(root);
	printf("二叉树的深度=%2d\n",depth);
	printf("根据括号嵌套(A(B(D(,H(J)),E(,I(K,L))),C(F,G)))建立二叉树:\n");
	CreateBitTree2(&T,"(A(B(D(,H(J)),E(,I(K,L))),C(F,G)))");
	num=LeafCount(T);
	printf("叶子结点个数=%2d\n",num);
	num=NotLeafCount(T);
	printf("非叶子结点个数=%2d\n",num);
	depth=BitTreeDepth(T);
	printf("二叉树的深度=%2d\n",depth);
	DestroyBitTree(&T);
	DestroyBitTree(&root);
	system("pause");
}
void main(){
	main_Traverse();
	main_Print();
	main_Count();
}