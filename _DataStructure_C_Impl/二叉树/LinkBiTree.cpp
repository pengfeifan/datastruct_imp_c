#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100
typedef char DataType;
typedef struct Node{		//��������洢�ṹ���Ͷ���
	DataType data;			//������
	struct Node *lchild;	//ָ�����ӽ��
	struct Node *rchild;	//ָ���Һ��ӽ��
}*BiTree,BitNode;
//�������ĳ�ʼ������
void InitBitTree(BiTree *T){
	*T=NULL;
}
//���ٶ���������
void DestroyBitTree(BiTree *T){
	if(*T){		//����Ƿǿն�����
		if((*T)->lchild)
			DestroyBitTree(&((*T)->lchild));
		if((*T)->rchild)
			DestroyBitTree(&((*T)->rchild));
		free(*T);
		*T=NULL;
	}
}
//�ݹ鴴��������
void CreateBitTree(BiTree *T){
	DataType ch;
	scanf("%c",&ch);
	if(ch=='#')
		*T=NULL;
	else{
		*T=(BiTree)malloc(sizeof(BitNode));	//���ɸ����
		if(!(*T))
			exit(-1);
		(*T)->data=ch;
		CreateBitTree(&((*T)->lchild));	//����������
		CreateBitTree(&((*T)->rchild));	//����������
	}
}
//����������������
int InsertLeftChild(BiTree p,BiTree c){
	if(p){		//���ָ��p����
		c->rchild=p->lchild;	//p��ԭ������������Ϊc��������
		p->lchild=c;	//����c��Ϊp��������
		return 1;
	}
	return 0;
}
//���������Ҳ������
int InsertRightChild(BiTree p,BiTree c){
	if(p){		//���ָ��p����
		c->rchild=p->rchild;	//p��ԭ������������Ϊc��������
		p->rchild=c;		//����c��Ϊp��������
		return 1;
	}
	return 0;
}
//����Ԫ��ֵΪe�Ľ���ָ��
BiTree Point(BiTree T,DataType e){
	BiTree Q[MaxSize];	//����һ�����У����ڴ�Ŷ������н���ָ��
	int front=0,rear=0;	//��ʼ������
	BitNode *p;
	if(T){	//����������ǿ�
		Q[rear]=T;
		rear++;

		while(front!=rear){	//������зǿ�
			p=Q[front];	//ȡ����ͷָ��
			front++;	//����ͷָ�����
			if(p->data==e)
				return p;
			if(p->lchild){	//������ӽ����ڣ�������ָ�����
				Q[rear]=p->lchild;	//���ӽ���ָ�����
				rear++;
			}
			if(p->rchild){	//����Һ��ӽ����ڣ����Һ���ָ�����
				Q[rear]=p->rchild;	//�Һ��ӽ���ָ�����
				rear++;
			}
		}
	}
	return NULL;
}
//���ض����������ӽ��Ԫ��ֵ����
DataType LeftChild(BiTree T,DataType e){
	BiTree p;
	if(T){		//�������������
		p=Point(T,e);	//p��Ԫ��ֵe�Ľ���ָ��
		if(p&&p->lchild)		//���p��Ϊ����p�����ӽ�����
			return p->lchild->data;		//����p�����ӽ���Ԫ��ֵ
	}
	return 0;
}
//���ض��������Һ��ӽ��Ԫ��ֵ����
DataType RightChild(BiTree T,DataType e){
	BiTree p;
	if(T){
		p=Point(T,e);		//p��Ԫ��ֵe�Ľ���ָ��
		if(p&&p->rchild)		//���p��Ϊ����p���Һ��ӽ�����
			return p->rchild->data;		//����p���Һ��ӽ���Ԫ��ֵ
	}
	return 0;
}
//����������ɾ������
int DeleteLeftChild(BiTree p){
	if(p){
		DestroyBitTree(&(p->lchild));	//ɾ��������
		return 1;
	}
	return 0;
}
//����������ɾ������
int DeleteRightChild(BiTree p){
	if(p){
		DestroyBitTree(&(p->rchild));	//ɾ��������
		return 1;
	}
	return 0;
}
//==================================================
//��������Ƕ�׵��ַ���������������
void CreateBitTree2(BiTree *T,char str[]){
	char ch;
	BiTree stack[MaxSize];	//����ջ�����ڴ��ָ��������н���ָ��
	int top=-1;		//��ʼ��ջ��ָ��
	int flag,k;
	BitNode *p;
	*T=NULL;
	k=0;
	ch=str[k];
	while(ch!='\0'){	//����ַ���û�н���
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
			if(*T==NULL)	//����ǵ�һ����㣬��ʾ�Ǹ����
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
//��������������ĵݹ�ʵ��
void PreOrderTraverse(BiTree T){
	if(T){
		printf("%2c",T->data);		//���ʸ����
		PreOrderTraverse(T->lchild);//�������������
		PreOrderTraverse(T->rchild);//�������������
	}
}
//��������������ĵݹ�ʵ��
void InOrderTraverse(BiTree T){
	if(T){
		InOrderTraverse(T->lchild);//�������������
		printf("%2c",T->data);		//���ʸ����
		InOrderTraverse(T->rchild);//�������������
	}
}
//��������������ĵݹ�ʵ��
void PostOrderTraverse(BiTree T){
	if(T){
		PostOrderTraverse(T->lchild);//�������������
		PostOrderTraverse(T->rchild);//�������������
		printf("%2c",T->data);		//���ʸ����
	}
}
//��������������ķǵݹ�ʵ��
void PreOrderTraverse2(BiTree T){
	BiTree stack[MaxSize];	//����һ��ջ�����ڴ�Ž���ָ��
	int top;		//����ջ��ָ��
	BitNode *p;	//����һ������ָ��
	top=0;	//��ʼ��ջ
	p=T;
	while(p!=NULL||top>0){
		while(p!=NULL){	//���p���գ����ʸ���㣬����������
			printf("%2c",p->data);	//���ʸ����
			stack[top++]=p;	//��p��ջ
			p=p->lchild;	//����������
		}
		if(top>0){	//���ջ����
			p=stack[--top];		//ջ��Ԫ�س�ջ
			p=p->rchild;		//����������
		}
	}
}
//��������������ķǵݹ�ʵ��
void InOrderTraverse2(BiTree T){
	BiTree stack[MaxSize];	//����һ��ջ�����ڴ�Ž���ָ��
	int top;		//����ջ��ָ��
	BitNode *p;	//����һ������ָ��
	top=0;	//��ʼ��ջ
	p=T;
	while(p!=NULL||top>0){
		while(p!=NULL){	//���p���գ����ʸ���㣬����������
			stack[top++]=p;	//��p��ջ
			p=p->lchild;	//����������
		}
		if(top>0){	//���ջ����
			p=stack[--top];		//ջ��Ԫ�س�ջ
			printf("%2c",p->data);	//���ʸ����
			p=p->rchild;		//����������
		}
	}
}
//��������������ķǵݹ�ʵ��
void PostOrderTraverse2(BiTree T){
	BiTree stack[MaxSize];	//����һ��ջ�����ڴ�Ž���ָ��
	int top;		//����ջ��ָ��
	BitNode *p,*q;	//����һ������ָ��
	top=0;	//��ʼ��ջ
	p=T;
	q=NULL;
	while(p!=NULL||top>0){
		while(p!=NULL){	//���p���գ����ʸ���㣬����������
			stack[top++]=p;	//��p��ջ
			p=p->lchild;	//����������
		}
		if(top>0){	//���ջ����
			p=stack[top-1];	//ȡջ��Ԫ��
			if(p->rchild==NULL||p->rchild==q){	//���pû���Һ��ӽ�㣬���Һ��ӽ���Ѿ����ʹ�
				printf("%2c",p->data);	//���ʸ����
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
	printf("����������������������д���������('#'��ʾ����)��\n");
	//ABD#G##EH##I##CF#J###
	CreateBitTree(&T);
	printf("���������������У�\n");
	printf("�ݹ飺\t");
	PreOrderTraverse(T);
	printf("\n");
	printf("�ǵݹ飺");
	PreOrderTraverse2(T);
	printf("\n");
	printf("���������������У�\n");
	printf("�ݹ飺\t");
	InOrderTraverse(T);
	printf("\n");
	printf("�ǵݹ飺");
	InOrderTraverse2(T);
	printf("\n");
	printf("�������ĺ������У�\n");
	printf("�ݹ飺\t");
	PostOrderTraverse(T);
	printf("\n");
	printf("�ǵݹ飺");
	PostOrderTraverse2(T);
	printf("\n");
	printf("��������Ƕ�׵��ַ�������������:\n");
	CreateBitTree2(&root,"(a(b(c,d),e(f(,g),h(i)))");
	printf("���������������У�\n");
	PreOrderTraverse(root);
	printf("\n");
	printf("���������������У�\n");
	InOrderTraverse(root);
	printf("\n");
	printf("�������ĺ������У�\n");
	PostOrderTraverse(root);
	printf("\n");
	DestroyBitTree(&T);
	DestroyBitTree(&root);
	system("pause");
}
//===================================================
//����δ�ӡ�������еĽ��
void LevelPrint(BiTree T){
	BiTree queue[MaxSize];	//����һ�����У����ڴ�Ž���ָ��
	BitNode *p;
	int front,rear;	//������еĶ�ͷָ��Ͷ�βָ��
	front=rear=-1;	//���г�ʼ��Ϊ��
	rear++;			//��βָ���1
	queue[rear]=T;	//�������ָ�����
	while(front!=rear){	//������в�Ϊ��*
		front=(front+1)%MaxSize;
		p=queue[front];	//ȡ����ͷԪ��
		printf("%c",p->data);	//��������
		if(p->lchild!=NULL){	//������Ӳ�Ϊ�գ������ӽ��ָ�����
			rear=(rear+1)%MaxSize;
			queue[rear]=p->lchild;
		}
		if(p->rchild!=NULL){	//����Һ��Ӳ�Ϊ�գ����Һ��ӽ��ָ�����
			rear=(rear+1)%MaxSize;
			queue[rear]=p->rchild;
		}
	}
}
//����״��ӡ�Ķ�����
void TreePrint(BiTree T,int level){
	int i;
	if(T==NULL)	//���ָ��Ϊ�գ�������һ��
		return ;
	TreePrint(T->rchild,level+1);	//��ӡ��������������μ�1
	for(i=0;i<level;i++)	//���յݹ�Ĳ�δ�ӡ�ո�
		printf("	");
	printf("%c\n",T->data);	//��������
	TreePrint(T->lchild,level+1);	//��ӡ��������������μ�1
}
//******************
void main_Print(){
	BiTree T,root;
	printf("��������Ƕ��(a(b(c,d),e(f(,g),h(i)))����������:\n");
	CreateBitTree2(&T,"(a(b(c,d),e(f(,g),h(i)))");
	printf("�������������������У�\n");
	LevelPrint(T);
	printf("\n");
	printf("����״��ӡ��������\n");
	TreePrint(T,1);
	printf("��������Ƕ��(A(B(D(,H),E(,I)),C(F,G)))����������:\n");
	CreateBitTree2(&root,"(A(B(D(,H),E(,I)),C(F,G)))");
	printf("�������������������У�\n");
	LevelPrint(root);
	printf("\n");
	printf("����״��ӡ��������\n");
	TreePrint(root,1);
	DestroyBitTree(&T);
	DestroyBitTree(&root);
	system("pause");
}
//==============================
//ͳ�ƶ�������Ҷ�ӽ����Ŀ
int LeafCount(BiTree T){
	if(!T)				//����ǿն�����������0
		return 0;
	else 
		if(!T->lchild&&!T->rchild)		//�������������������Ϊ�գ�����1
			return 1;
		else
			return LeafCount(T->lchild)+LeafCount(T->rchild);		//��������Ҷ�ӽ�������������Ҷ�ӽ��������
}
//ͳ�ƶ������з�Ҷ�ӽ����Ŀ
int NotLeafCount(BiTree T){
	if(!T)		//����ǿն�����������0
		return 0;
	else if(!T->lchild&&!T->rchild)		//�����Ҷ�ӽ�㣬����0
		return 0;
		else
			return NotLeafCount(T->lchild)+NotLeafCount(T->rchild)+1;		//���������ķ�Ҷ�ӽ����Ŀ���ϸ����ĸ���

}
//ͳ�ƶ������н����Ŀ
int TreeCount(BiTree T){
	if(T==NULL)
		return 0;
	return 1+TreeCount(T->lchild)+TreeCount(T->rchild);
}
//��������������
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
	printf("��������Ƕ��(a(b(c,d),e(f(,g),h(i)))����������:\n");
	CreateBitTree2(&root,"(a(b(c,d),e(f(,g),h(i)))");
	num=TreeCount(root);
	printf("������������=%2d\n",num);
	num=LeafCount(root);
	printf("Ҷ�ӽ�����=%2d\n",num);
	num=NotLeafCount(root);
	printf("��Ҷ�ӽ�����=%2d\n",num);
	depth=BitTreeDepth(root);
	printf("�����������=%2d\n",depth);
	printf("��������Ƕ��(A(B(D(,H(J)),E(,I(K,L))),C(F,G)))����������:\n");
	CreateBitTree2(&T,"(A(B(D(,H(J)),E(,I(K,L))),C(F,G)))");
	num=LeafCount(T);
	printf("Ҷ�ӽ�����=%2d\n",num);
	num=NotLeafCount(T);
	printf("��Ҷ�ӽ�����=%2d\n",num);
	depth=BitTreeDepth(T);
	printf("�����������=%2d\n",depth);
	DestroyBitTree(&T);
	DestroyBitTree(&root);
	system("pause");
}
void main(){
	main_Traverse();
	main_Print();
	main_Count();
}