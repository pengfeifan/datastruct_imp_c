#include<stdio.h>
#include<stdlib.h>

typedef int KeyType;
//Ԫ�صĶ���
typedef struct{
	KeyType key;
}DataType;
//���������������Ͷ���
typedef struct Node{
	DataType data;
	struct Node *lchild,*rchild;
}BiTreeNode,*BiTree;
//�����������Ĳ��ң�����ҵ�Ԫ��x���򷵻�ָ�����ָ�룬���򷵻�NULL
BiTree BSTSearch(BiTree T,DataType x){
	BiTreeNode *p;
	if(T!=NULL){
		p=T;
		while(p!=NULL){		//���������������Ϊ��
			if(p->data.key==x.key)	//����ҵ����򷵻�ָ��ý���ָ��
				return p;
			else if(p->data.key>x.key)	//����ؼ���С��pָ��Ľ���ֵ�������������в���
				p=p->lchild;
			else 
				p=p->rchild;	//����ؼ��ִ���pָ��Ľ���ֵ�������������в���
		}
	}
	return NULL;
}
//�����������Ĳ��������������в�����Ԫ��x����x���뵽��ȷ��λ�ò�����1�����򷵻�0
int BSTInsert(BiTree *T,DataType x){
	BiTreeNode *p,*cur,*parent=NULL;
	cur=*T;
	while(cur!=NULL){
		if(cur->data.key==x.key)	//����������д���Ԫ��Ϊx�Ľ�㣬�򷵻�0
			return 0;
		parent=cur;		//parentָ��cur��ǰ�����
		if(x.key<cur->data.key)		//����ؼ���С��pָ��Ľ���ֵ�������������в���
			cur=cur->lchild;
		else						//����ؼ��ִ���pָ��Ľ���ֵ�������������в���
			cur=cur->rchild;
	}
	p=(BiTreeNode*)malloc(sizeof(BiTreeNode));	//���ɽ��
	if(!p)
		exit(-1);
	p->data=x;
	p->lchild=NULL;
	p->rchild=NULL;
	if(!parent)				//���������Ϊ�գ����һ����Ϊ�����
		*T=p;
	else if(x.key<parent->data.key)	//����ؼ���С��parentָ��Ľ�㣬��x��Ϊparent������
		parent->lchild=p;
	else							//����ؼ��ִ���parentָ��Ľ�㣬��x��Ϊparent���Һ���
		parent->rchild=p;
	return 1;
}
//�Ӷ�����������ɾ�����s����ʹ�ö������������ʲ���
void DeleteNode(BiTree *s){
	BiTree q,x,y;
	if(!(*s)->rchild){			//���s��������Ϊ�գ���ʹs����������Ϊ��ɾ���˫�׽���������
		q=*s;
		*s=(*s)->lchild;
		free(q);
	}else if(!(*s)->lchild){	//���s��������Ϊ�գ���ʹs����������Ϊ��ɾ���˫�׽���������
		q=*s;
		*s=(*s)->rchild;
		free(q);
	}else{	//*���s���������������ڣ���ʹs��ֱ��ǰ��������s����ʹ��ֱ��ǰ��������������Ϊ��˫�׽������������
		x=*s;
		y=(*s)->lchild;
		while(y->rchild){	//����s��ֱ��ǰ����㣬yΪs��ֱ��ǰ����㣬xΪy��˫�׽��
			x=y;
			y=y->rchild;
		}
		(*s)->data=y->data;	//���s��yȡ��
		if(x!=*s)	//������s�����ӽ�����������
			x->rchild=y->lchild;	//ʹy����������Ϊx��������
		else		//������s�����ӽ�㲻����������
			x->lchild=y->lchild;	//ʹy����������Ϊx��������
		free(y);
	}
}
//�ڶ���������T�д���ֵΪx������Ԫ��ʱ��ɾ��������Ԫ�ؽ�㣬������1�����򷵻�0
int BSTDelete(BiTree *T,DataType x){
	if(!*T)		//���������ֵΪx������Ԫ�أ��򷵻�0
		return 0;
	else{
		if(x.key==(*T)->data.key)		//����ҵ�ֵΪx������Ԫ�أ���ɾ���ý��
			DeleteNode(T);
		else if((*T)->data.key>x.key)	//�����ǰԪ��ֵ����x��ֵ�����ڸý����������в��Ҳ�ɾ��֮
			BSTDelete(&(*T)->lchild,x);
		else							//�����ǰԪ��ֵС��x��ֵ�����ڸý����������в��Ҳ�ɾ��֮
			BSTDelete(&(*T)->rchild,x);
	}
}
//���������������ĵݹ�ʵ��
void InOrderTraverse(BiTree T){
	if(T)								/*���������������Ϊ��*/
	{
		InOrderTraverse(T->lchild);			/*�������������*/
		printf("%4d",T->data); 				/*���ʸ����*/
		InOrderTraverse(T->rchild); 		/*�������������*/
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
	printf("������������������õ�������Ϊ��\n");
	InOrderTraverse(T);
	p=BSTSearch(T,x);
	if(p!=NULL)
		printf("\n�������������ң��ؼ���%d����\n",x.key);
	else
		printf("����ʧ�ܣ�\n");
	BSTDelete(&T,s);
	printf("ɾ��Ԫ��%d��������������������õ�������Ϊ��\n",s.key);
	InOrderTraverse(T);
	printf("\n");
	system("pause");
}
/*
//ƽ�����������
//��ƽ�����������ʧȥƽ��ʱ����LL�͵ĵ���
BSTree b;
b=p->lchild;//p�Ǹ���㣬bָ��p���������ĸ����
p->lchild=b->rchild;//��b����������Ϊp��������
b->rchild=p;//��p��Ϊb����������������bΪ�����
p->bf=b->bf=0;//�޸�ƽ������
//��ƽ�����������ʧȥƽ��ʱ����LR(LRL)�͵ĵ���
BSTree b,c;//pΪ����㣬bΪp���������ĸ���㣬cΪb���������ĸ����
b=p->lchild;//bΪp���������ĸ����
c=b->rchild;//cΪb���������ĸ����
b->rchild=c->lchild;//c����������Ϊb��������
p->lchild=c->rchild;//c����������Ϊp��������
c->lchild=b;//b��Ϊc��������
c->rchild=p;//p��Ϊc����������������cΪ�����
//�޸�ƽ������
p->bf=-1;
b->bf=0;
c->bf=0;
//��ƽ�����������ʧȥƽ��ʱ����RL(RLR)�͵ĵ���
BSTree b,c;//pΪ����㣬bΪp���������ĸ���㣬cΪb���������ĸ����
b=p->rchild;//bΪp���������ĸ����
c=b->lchild;//cΪb���������ĸ����
b->lchild=c->rchild;//c����������Ϊb��������
p->rchild=c->lchild;//c����������Ϊp��������
c->lchild=p;//p��Ϊc��������
c->rchild=b;//b��Ϊc����������������cΪ�����
//�޸�ƽ������
p->bf=1;
b->bf=0;
b->bf=0;
//��ƽ�����������ʧȥƽ��ʱ����RR�͵ĵ���
BSTree b;
b=p->rchild;//p�Ǹ���㣬bָ��p���������ĸ����
p->rchild=b->lchild;//��b����������Ϊp��������
b->lchild=p;//��p��Ϊb����������������bΪ�����
//�޸�ƽ������
p->bf=0;
b->bf=0;
//B-��.B+���Ķ�̬����
//B-�������Ͷ���
#define m 4  //B-���Ľ���
typedef struct BTNdoe{
	int keynum;	//ÿ������еĹؼ��ָ���
	struct BTNode *parent;//ָ��˫�׽��
	KeyType data[m+1];//����йؼ�����Ϣ
	struct BTNode *ptr[m+1];//ָ������
}BTNode,*BTree;
*/