#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100
/*�������������Ͷ���*/
typedef char DataType;
typedef enum {Link,Thread}PointerTag;//Link=0��ʾָ���ӽڵ㣬Thread=1��ʾָ��ǰ���ڵ���̽ڵ�
typedef struct Node{
	DataType data;
	struct Node *lchild,*rchild;	//ָ�����Һ��ӽڵ��ָ��
	PointerTag ltag,rtag;		//������־��
}BiThrNode;
typedef BiThrNode* BiThrTree;	//����������

BiThrTree pre;//preʼ��ָ���Ѿ��������Ľ��
//��������Ƕ�׵��ַ���������������
void CreateBitTree2(BiThrTree *T,char str[]){
	char ch;
	BiThrTree stack[MaxSize];
	int top=-1;
	int flag,k;
	BiThrNode *p;
	*T=NULL;
	k=0;
	ch=str[k];
	while(ch!='\0'){
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
			p=(BiThrTree)malloc(sizeof(BiThrNode));
			p->data=ch;
			p->lchild=NULL;
			p->rchild=NULL;

			if(*T==NULL)
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
				if(stack[top]->lchild)
					stack[top]->ltag=Link;
				if(stack[top]->rchild)
					stack[top]->rtag=Link;
			}
		}
		ch=str[++k];
	}
}
//����������������
void InThreading(BiThrTree p){
	if(p){
		InThreading(p->lchild);	//������������
		if(!p->lchild){		//ǰ��������
			p->ltag=Thread;
			p->lchild=pre;
		}
		if(!pre->rchild){	//���������
			pre->rtag=Thread;
			pre->rchild=p;
		}
		pre=p;	//preָ��Ľ����������ϣ�ʹpָ��Ľ���Ϊǰ��
		InThreading(p->rchild);	//������������
	}
}
//ͨ���������������T��ʹT������������Thrt��ָ��ͷ����ָ��
int InOrderThreading(BiThrTree *Thrt,BiThrTree T){
	if(!(*Thrt=(BiThrTree)malloc(sizeof(BiThrNode))))	//Ϊͷ�������ڴ浥Ԫ
		exit(-1);
	//��ͷ���������
	(*Thrt)->ltag=Link;			//�޸�ǰ��������־
	(*Thrt)->rtag=Thread;		//�޸ĺ��������־
	(*Thrt)->rchild=*Thrt;		//��ͷ����rchildָ��ָ���Լ�
	if(!T)		//���������Ϊ�գ���lchildָ��ָ���Լ�
		(*Thrt)->lchild=*Thrt;
	else{
		(*Thrt)->lchild=T;		//��ͷ������ָ��ָ������
		pre=*Thrt;				//��preָ���Ѿ��������Ľ��
		InThreading(T);			//���������������������
		//�����һ�����������
		pre->rchild=*Thrt;		//�����һ��������ָ��ָ��ͷ���
		pre->rtag=Thread;		//�޸����һ������rtag��־��
		(*Thrt)->rchild=pre;	//��ͷ����rchildָ��ָ�����һ�����
	}
	return 1;
}
//��ӡ�����������еĽ�㼰����
int Print(BiThrTree T){
	static int k=1;
	printf("%2d\t%s\t  %2c\t  %s\t\n",k++,T->ltag==0?"Link":"Thread",
		T->data,
		T->rtag==1?"Thread":"Link");
	return 1;
}
//�����������������������visit�Ǻ���ָ�룬ָ����ʽ��ĺ���ʵ��
int InOrderTraverse(BiThrTree T,int (* visit)(BiThrTree e)){
	BiThrTree p;
	p=T->lchild;		//pָ������
	while(p!=T){		//�������������ʱ��p==T
		while(p->ltag==Link)
			p=p->lchild;
		if(!visit(p))		//��ӡ
			return 0;
		while(p->rtag==Thread&&p->rchild!=T){		//���ʺ�̽��
			p=p->rchild;
			visit(p);
		}
		p=p->rchild;
	}
	return 1;
}
//���������������ҽ��*p������ֱ��ǰ��
BiThrNode *InOrderPre(BiThrNode *p){
	BiThrNode *pre;
	if(p->ltag==Thread)		//���p�ı�־��ltagΪ��������p����������㼴Ϊǰ��
		return p->lchild;
	else{
		pre=p->lchild;		//����p�����ӵ������¶˽��
		while(pre->rtag==Link)		//�������ǿ�ʱ�����������²���
			pre=pre->rchild;
		return pre;		//pre���������¶˽��
	}
}
//�������������в��ҽ��*p������ֱ�Ӻ��
BiThrNode *InOrderPost(BiThrNode *p){
	BiThrNode *pre;
	if(p->rtag==Thread)		//���p�ı�־��ltagΪ��������p����������㼴Ϊ���
		return p->rchild;
	else{
		pre=p->rchild;		//����p���Һ��ӵ������¶˽��
		while(pre->ltag==Link)
			pre=pre->lchild;		//�������ǿ�ʱ�����������²���
		return pre;		//pre���������¶˽��
	}
}
//�����������������������Ԫ��ֵΪe�Ľ���ָ��
BiThrNode *FindPoint(BiThrTree T,DataType e){
	BiThrTree p;
	p=T->lchild;
	while(p!=T){
		while(p->ltag==Link)
			p=p->lchild;
		if(p->data==e)		//�ҵ���㣬����ָ��
			return p;
		while(p->rtag==Thread&&p->rchild!=T){		//���ʺ�̽��
			p=p->rchild;
			if(p->data==e)		//�ҵ���㣬����ָ��
				return p;
		}
		p=p->rchild;
	}
	return NULL;
}
//���ٶ���������
void DestroyBitTree(BiThrTree *T){
	if(*T){		//����Ƿǿն�����
		if((*T)->lchild)
			DestroyBitTree(&((*T)->lchild));
		if((*T)->rchild)
			DestroyBitTree(&((*T)->rchild));
		free(*T);
		*T=NULL;
	}
}
void main(){
	BiThrTree T,Thrt;
	BiThrNode *p,*pre,*post;
	CreateBitTree2(&T,"(A(B(,D(G)),C(E(,H),F))");
	printf("������������������У�\n");
	InOrderThreading(&Thrt,T);
	printf("����   ǰ����־   ���  ��̱�־\n");
	InOrderTraverse(Thrt,Print);
	p=FindPoint(Thrt,'D');
	pre=InOrderPre(p);
	printf("Ԫ��D������ֱ��ǰ��Ԫ����:%c\n",pre->data);
	post=InOrderPost(p);
	printf("Ԫ��D������ֱ�Ӻ��Ԫ����:%c\n",post->data);
	p=FindPoint(Thrt,'E');
	pre=InOrderPre(p);
	printf("Ԫ��E������ֱ��ǰ��Ԫ����:%c\n",pre->data);
	post=InOrderPost(p);
	printf("Ԫ��E������ֱ�Ӻ��Ԫ����:%c\n",post->data);
	//DestroyBitTree(&Thrt);
	system("pause");
}