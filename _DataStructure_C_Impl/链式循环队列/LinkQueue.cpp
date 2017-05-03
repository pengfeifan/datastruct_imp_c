//_DataStructure_C_Impl:链式队列
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

//将带头结点的链式队列初始化为空队列需要把头结点的指针域置为0
void InitQueue(LinkQueue *LQ){
	LQ->front=LQ->rear=(LQNode *)malloc(sizeof(LQNode));
	if(LQ->front==NULL)
		exit(-1);
	LQ->front->next=NULL;	//把头结点的指针域置为为0
	LQ->rear=LQ->front;
}
//判断链式队列是否为空，队列为空返回1，否则返回0
int QueueEmpty(LinkQueue LQ){
	if(LQ.rear->next==NULL)
		return 1;
	else
		return 0;
}
//将元素e插入到链式队列LQ中，插入成功返回1
int EnterQueue(LinkQueue *LQ,DataType e){
	LQNode *s;
	s=(LQNode *)malloc(sizeof(LQNode));	//为将要入队的元素申请一个结点的空间
	if(!s)		//如果申请空间失败，则退出并返回参数-1
		exit(-1);
	s->data=e;		//将元素值赋值给结点的数据域
	s->next=NULL;	//将结点的指针域置为空
	LQ->rear->next=s;	//将原来队列的队尾指针指向s
	LQ->rear=s;	//将队尾指针指向s
	return 1;
}
//取链式队列中的队头元素，并将该元素赋值给e，取元素成功返回1，否则返回0
int GetHead(LinkQueue LQ,DataType *e){
	LQNode *s;
	if(LQ.front==LQ.rear)	//在取队头元素之前，判断链式队列是否为空
		return 0;
	else{
		s=LQ.front->next;	//将指针s指向队列的第一个元素即队头元素
		*e=s->data;		//将队头元素赋值给e，取出队头元素
		return 1;
	}
}
//将队列Q的队头元素出队，并存放到x所指的存储空间中
int DeleteQueue(LinkQueue *Q,DataType *x){
	LQNode *p;
	if(Q->front==Q->rear)
		return 0;
	p=Q->front->next;
	Q->front->next=p->next;	//队头元素p出队
	if(Q->front==NULL)	//如果队中只有一个元素p，则p出队后成为空队
		Q->rear=Q->front;
	*x=p->data;
	free(p);	//释放存储空间
	return 1;
}
//清空队列
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
	static int count=0;	//记录输出的行
	for(i=0;i<N-count;i++)		//打印空格
		printf(" ");
	count++;
	for(i=0;i<n;i++)		//打印数组中的元素
		printf("%6d",a[i]);
	printf("\n");
}
//链式队列实现打印杨辉三角
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
	printf("请输入要打印的行数：n=:");
	scanf("%d",&n);	
	YangHuiTriangle(n);	
	system("pause");
}