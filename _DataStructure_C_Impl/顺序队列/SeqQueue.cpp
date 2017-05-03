//_DataStructure_C_Impl:˳�����
#include<stdio.h>
#include<stdlib.h>
#define QueueSize 50
typedef char DataType;
typedef struct Squeue{	//˳��������Ͷ���
	DataType queue[QueueSize];
	int front,rear;	//��ͷָ��Ͷ�βָ��
}SeqQueue;
//��˳����г�ʼ��Ϊ�ն���ֻ��Ҫ�Ѷ�ͷָ��Ͷ�βָ��ͬʱ��Ϊ0
void InitQueue(SeqQueue *SQ){
	SQ->front=SQ->rear=0;	//�Ѷ�ͷָ��Ͷ�βָ��ͬʱ��Ϊ0
}
//�ж϶����Ƿ�Ϊ�գ�����Ϊ�շ���1�����򷵻�0
int QueueEmpty(SeqQueue SQ){
	if(SQ.front==SQ.rear)
		return 1;
	else
		return 0;
}
//��Ԫ��x���뵽˳�����SQ�У�����ɹ�����1�����򷵻�0
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
//ɾ��˳������еĶ�ͷԪ�أ�������Ԫ�ظ�ֵ��e��ɾ���ɹ�����1�����򷵻�0
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
	printf("�����е�Ԫ��Ϊ:%c\n",x);	//��ʾ��������е�Ԫ��
	printf("˳������е�Ԫ��Ϊ:");
	if(!QueueEmpty(Q)){
		for(i=Q.front;i<Q.rear;i++)
			printf("%c",Q.queue[i]);
	}
	printf("\n");
	system("pause");
}