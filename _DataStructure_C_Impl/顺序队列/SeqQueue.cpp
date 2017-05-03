//_DataStructure_C_Impl:顺序队列
#include<stdio.h>
#include<stdlib.h>
#define QueueSize 50
typedef char DataType;
typedef struct Squeue{	//顺序队列类型定义
	DataType queue[QueueSize];
	int front,rear;	//队头指针和队尾指针
}SeqQueue;
//将顺序队列初始化为空队列只需要把队头指针和队尾指针同时置为0
void InitQueue(SeqQueue *SQ){
	SQ->front=SQ->rear=0;	//把队头指针和队尾指针同时置为0
}
//判断队列是否为空，队列为空返回1，否则返回0
int QueueEmpty(SeqQueue SQ){
	if(SQ.front==SQ.rear)
		return 1;
	else
		return 0;
}
//将元素x插入到顺序队列SQ中，插入成功返回1，否则返回0
int EnterQueue(SeqQueue *SQ,DataType x){
	if(SQ->rear==QueueSize)
		return 0;
	SQ->queue[SQ->rear]=x;
	SQ->rear+=1;
	return 1;
}
int EnterSCQueue(SeqQueue *SCQ,DataType e){
	if(SCQ->front==(SCQ->rear+1)%QueueSize)
		return 0;
	SCQ->queue[SCQ->rear]=e;
	SCQ->rear=(SCQ->rear+1)%QueueSize;
	return 1;
}
//删除顺序队列中的队头元素，并将该元素赋值给e，删除成功返回1，否则返回0
int DeleteQueue(SeqQueue *SQ,DataType *e){
	if(SQ->front==SQ->rear)
		return 0;
	else{
		*e=SQ->queue[SQ->front];
		SQ->front+=1;
		return 1;
	}
}
int DeleteSCQueue(SeqQueue *SCQ,DataType *e){
	if(SCQ->front==SCQ->rear)
		return 0;
	else{
		*e=SCQ->queue[SCQ->front];
		SCQ->front=(SCQ->front+1)%QueueSize;
		return 1;
	}
}
int GetHead(SeqQueue SCQ,DataType *e){
	if(SCQ.front==SCQ.rear)
		return 0;
	else{
		*e=SCQ.queue[SCQ.front];
		return 1;
	}
}
void ClearQueue(SeqQueue *SCQ){
	SCQ->front=SCQ->rear=0;
}
void main(){
	SeqQueue Q;
	char str[]="ABCDEFGH";
	int i,length=8;
	char x;
	InitQueue(&Q);
	for(i=0;i<length;i++){
		EnterQueue(&Q,str[i]);
	}
	DeleteQueue(&Q,&x);
	printf("出队列的元素为:%c\n",x);	//显示输出出队列的元素
	printf("顺序队列中的元素为:");
	if(!QueueEmpty(Q)){
		for(i=Q.front;i<Q.rear;i++)
			printf("%c",Q.queue[i]);
	}
	printf("\n");
	system("pause");
}