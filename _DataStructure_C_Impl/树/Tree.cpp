#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MaxSize 100
//���������Ͷ���
typedef struct Node{
	char data;
	struct Node *lchild,*rchild;
}BitNode,*BiTree;
//���������������Ľ��
void PrintLevel(BiTree T){
	BiTree Queue[MaxSize];
	int front,rear;
	if(T==NULL)
		return;
	front=-1;
	rear=0;
	Queue[rear]=T;
	while(front!=rear){		//������в���
		front++;		//����ͷԪ�س���
		printf("%4c",Queue[front]->data);	//�����ͷԪ��
		if(Queue[front]->lchild!=NULL){	//�����ͷԪ�ص����ӽ�㲻Ϊ�գ����������
			rear++;
			Queue[rear]=Queue[front]->lchild;
		}
		if(Queue[front]->rchild!=NULL){	//�����ͷԪ�ص��Һ��ӽ�㲻Ϊ�գ����Һ������
			rear++;
			Queue[rear]=Queue[front]->rchild;
		}
	}
}
//��������������Ľ��
void PrintTLR(BiTree T){
	if(T!=NULL)
	{ 
		printf("%4c ",T->data);	/*��������*/
		PrintTLR(T->lchild);	/*�������������*/
		PrintTLR(T->rchild);	/*�������������*/
	}
}
//��������������Ľ��
void PrintLRT(BiTree T){
	if (T!=NULL)
	{ 
		PrintLRT(T->lchild);	/*�������������*/
		PrintLRT(T->rchild);	/*�������������*/
		printf("%4c",T->data);	/*��������*/	
	}
}
//���ʽ��e
void Visit(BiTree T,BiTree pre,char e,int i){
	if(T==NULL&&pre==NULL) 
	{ 
		printf("\n�Բ����㻹û�н������������Ƚ����ٽ��з��ʣ�\n");
		return;
	}
	if(T==NULL) 
		return;
	else if(T->data==e)				/*����ҵ����e�����������˫�׽��*/
	{ 
		if(pre!=NULL)
		{
			printf("%2c��˫�׽������:%2c\n",e,pre->data);
			printf("%2c�����%2d����\n",e,i);
		}
		else
			printf("%2cλ�ڵ�1�㣬��˫�׽�㣡\n",e);  
	}
	else
	{
		Visit(T->lchild,T,e,i+1);/*����������*/
		Visit(T->rchild,T,e,i+1);/*����������*/
	} 
}
//���������к��������й��������
void CreateBiTree1(BiTree *T,char *pre,char *in,int len){
	int k;
	char *temp;
	if(len<=0){
		*T=NULL;
		return;
	}
	*T=(BitNode*)malloc(sizeof(BitNode));	//���ɸ����
	(*T)->data=*pre;
	for(temp=in;temp<in+len;temp++)		//����������in���ҵ���������ڵ�λ��
		if(*pre==*temp)
			break;
	k=temp-in;		//�������ĳ���
	CreateBiTree1(&((*T)->lchild),pre+1,in,k);		//����������
	CreateBiTree1(&((*T)->rchild),pre+1+k,temp+1,len-1-k);		//����������
}
//���������кͺ������й��������
void CreateBiTree2(BiTree *T,char *in,char *post,int len){
	int k;
	char *temp;
	if(len<=0){
		*T==NULL;
		return ;
	}
	for(temp=in;temp<in+len;temp++)		//����������in���ҵ���������ڵ�λ��
		if(*(post+len-1)==*temp){
			k=temp-in;		//�������ĳ���
			(*T)=(BitNode*)malloc(sizeof(BitNode));
			(*T)->data=*temp;
			break;
		}
	CreateBiTree2(&((*T)->lchild),in,post,k);				/*����������*/
	CreateBiTree2(&((*T)->rchild),in+k+1,post+k,len-k-1); /*����������*/	
}
void main(){
	BiTree T,ptr=NULL;
	char ch;
	int len;
	char pre[MaxSize],in[MaxSize],post[MaxSize];
	T=NULL;
	/*���������кͺ������й��������*/
	printf("���������к��������й����������\n");
	printf("��������������ַ������У�");
	gets(pre);
	printf("��������������ַ������У�");
	gets(in);
	len=strlen(pre);
	CreateBiTree1(&T,pre,in,len);
	/*����Ͳ������������Ľ��*/
	printf("�㽨���Ķ����������������ǣ�\n");
	PrintLRT(T);
	printf("\n�㽨���Ķ�������α�������ǣ�\n");
	PrintLevel(T);
	printf("\n");
	printf("����������Ҫ���ʵĽ�㣺");
	ch=getchar();getchar();
	Visit(T,ptr,ch,1); 
	/*���������кͺ������й��������*/
	printf("���������к��������й����������\n");
	printf("��������������ַ������У�");
	gets(in);
	printf("�������������ַ������У�");
	gets(post);
	len=strlen(post);
	CreateBiTree2(&T,in,post,len);
	/*����Ͳ������������Ľ��*/
	printf("\n�㽨���Ķ����������������ǣ�\n");
	PrintTLR(T);
	printf("\n�㽨���Ķ�������α�������ǣ�\n");
	PrintLevel(T);
	printf("\n");
	printf("����������Ҫ���ʵĽ�㣺");
	ch=getchar();getchar();
	Visit(T,ptr,ch,1); 
	system("pause");
}
