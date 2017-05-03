//_DataStructure_C_Impl:��ʽ����
#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100
typedef int DataType;
typedef struct QNode{
	DataType data;
	struct QNode *next;
}LQNode,*QueuePtr;
typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

//����ͷ������ʽ���г�ʼ��Ϊ�ն�����Ҫ��ͷ����ָ������Ϊ0
void InitQueue(LinkQueue *LQ){
	LQ->front=LQ->rear=(LQNode *)malloc(sizeof(LQNode));
	if(LQ->front==NULL)
		exit(-1);
	LQ->front->next=NULL;	//��ͷ����ָ������ΪΪ0
	LQ->rear=LQ->front;
}
//�ж���ʽ�����Ƿ�Ϊ�գ�����Ϊ�շ���1�����򷵻�0
int QueueEmpty(LinkQueue LQ){
	if(LQ.rear->next==NULL)
		return 1;
	else
		return 0;
}
//��Ԫ��e���뵽��ʽ����LQ�У�����ɹ�����1
int EnterQueue(LinkQueue *LQ,DataType e){
	LQNode *s;
	s=(LQNode *)malloc(sizeof(LQNode));	//Ϊ��Ҫ��ӵ�Ԫ������һ�����Ŀռ�
	if(!s)		//�������ռ�ʧ�ܣ����˳������ز���-1
		exit(-1);
	s->data=e;		//��Ԫ��ֵ��ֵ������������
	s->next=NULL;	//������ָ������Ϊ��
	LQ->rear->next=s;	//��ԭ�����еĶ�βָ��ָ��s
	LQ->rear=s;	//����βָ��ָ��s
	return 1;
}
//ȡ��ʽ�����еĶ�ͷԪ�أ�������Ԫ�ظ�ֵ��e��ȡԪ�سɹ�����1�����򷵻�0
int GetHead(LinkQueue LQ,DataType *e){
	LQNode *s;
	if(LQ.front==LQ.rear)	//��ȡ��ͷԪ��֮ǰ���ж���ʽ�����Ƿ�Ϊ��
		return 0;
	else{
		s=LQ.front->next;	//��ָ��sָ����еĵ�һ��Ԫ�ؼ���ͷԪ��
		*e=s->data;		//����ͷԪ�ظ�ֵ��e��ȡ����ͷԪ��
		return 1;
	}
}
//������Q�Ķ�ͷԪ�س��ӣ�����ŵ�x��ָ�Ĵ洢�ռ���
int DeleteQueue(LinkQueue *Q,DataType *x){
	LQNode *p;
	if(Q->front==Q->rear)
		return 0;
	p=Q->front->next;
	Q->front->next=p->next;	//��ͷԪ��p����
	if(Q->front==NULL)	//�������ֻ��һ��Ԫ��p����p���Ӻ��Ϊ�ն�
		Q->rear=Q->front;
	*x=p->data;
	free(p);	//�ͷŴ洢�ռ�
	return 1;
}
//��ն���
void ClearQueue(LinkQueue *LQ){
	while(LQ->front!=NULL){
		LQ->rear=LQ->front->next;
		free(LQ->front);
		LQ->front=LQ->rear;
	}
}
//*********************************
void PrintArray(int a[],int n,int N){
	int i;
	static int count=0;	//��¼�������
	for(i=0;i<N-count;i++)		//��ӡ�ո�
		printf(" ");
	count++;
	for(i=0;i<n;i++)		//��ӡ�����е�Ԫ��
		printf("%6d",a[i]);
	printf("\n");
}
//��ʽ����ʵ�ִ�ӡ�������
void YangHuiTriangle(int N){
	int i,j,k,n;
	DataType e,t;
	int temp[MaxSize];
	LinkQueue Q;
	k=0;
	InitQueue(&Q);
	EnterQueue(&Q,1);
	for(n=2;n<=N;n++){
		k=0;
		EnterQueue(&Q,1);
		for(i=1;i<=n-2;i++){
			DeleteQueue(&Q,&t);
			temp[k++]=t;
			GetHead(Q,&e);
			t=t+e;
			EnterQueue(&Q,t);
		}
		DeleteQueue(&Q,&t);
		temp[k++]=t;
		PrintArray(temp,k,N);
		EnterQueue(&Q,1);
	}
	k=0;
	while(!QueueEmpty(Q)){
		DeleteQueue(&Q,&t);
		temp[k++]=t;
		if(QueueEmpty(Q))
			PrintArray(temp,k,N);
	}
}
void main(){
	int n;
	printf("������Ҫ��ӡ��������n=:");
	scanf("%d",&n);	
	YangHuiTriangle(n);	
	system("pause");
}