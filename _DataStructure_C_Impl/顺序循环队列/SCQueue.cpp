//_DataStructure_C_Impl:˳��ѭ������
#include<stdio.h>
#include<stdlib.h>
#define QueueSize 10		//����˳��ѭ�����е��������
typedef char DataType;
typedef struct Squeue{		//˳��ѭ�����е����Ͷ���
	DataType queue[QueueSize];
	int front,rear;		//��ͷָ��Ͷ�βָ��
	int tag;		//���пա����ı�־
}SCQueue;
//��˳��ѭ�����г�ʼ��Ϊ�ն��У���Ҫ�Ѷ�ͷָ��Ͷ�βָ��ͬʱ��Ϊ0���ұ�־λ��Ϊ0
void InitQueue(SCQueue *SCQ){
	SCQ->front=SCQ->rear=0;		//��ͷָ��Ͷ�βָ�붼��Ϊ0
	SCQ->tag=0;		//��־λ��Ϊ0
}
//�ж�˳��ѭ�������Ƿ�Ϊ�գ�����Ϊ�շ���1�����򷵻�0
int QueueEmpty(SCQueue SCQ){
	if(SCQ.front==SCQ.rear&&SCQ.tag==0)	//��ͷָ��Ͷ�βָ�붼Ϊ0�ұ�־λΪ0��ʾ�����ѿ�
		return 1;
	else
		return 0;
}
//��Ԫ��e���뵽˳��ѭ������SQ�У�����ɹ�����1�����򷵻�0
int EnterQueue(SCQueue *SCQ,DataType e){
	if(SCQ->front==SCQ->rear&&SCQ->tag==1){	//�ڲ����µ�Ԫ��֮ǰ���ж��Ƿ��βָ�뵽����������ֵ�����Ƿ�����
		printf("˳��ѭ������������������ӣ�");
		return 0;
	}else{
		SCQ->queue[SCQ->rear]=e;	//�ڶ�β����Ԫ��e
		SCQ->rear+=1;	//��βָ������ƶ�һ��λ�ã�ָ���µĶ�β
		SCQ->tag=1;	//����ɹ�����־λ��Ϊ1
		return 1;
	}
}
//ɾ��˳��ѭ�������еĶ�ͷԪ�أ�������Ԫ�ظ�ֵ��e��ɾ���ɹ�����1�����򷵻�0
int DeleteQueue(SCQueue *SCQ,DataType *e){
	if(QueueEmpty(*SCQ)){
		printf("˳��ѭ�������Ѿ��ǿն��У������ٽ��г����в�����");
		return 0;
	}else{
		*e=SCQ->queue[SCQ->front];	//Ҫ�����е�Ԫ��ֵ��ֵ��e 
		SCQ->front+=1;	//��ͷָ������ƶ�һ��λ�ã�ָ���µĶ�ͷԪ��
		SCQ->tag=0;		//ɾ���ɹ�����־λ��Ϊ0
		return 1;
	}
}
//˳��ѭ�����е���ʾ��������������ж϶����Ƿ�Ϊ�գ����ʱ��Ӧ���Ƕ�ͷָ��Ͷ�βָ��ֵ�Ĵ�С����
void DisplayQueue(SCQueue SCQ){
	int i;
	if(QueueEmpty(SCQ))	// �ж�˳��ѭ�������Ƿ�Ϊ��
		return ;
	if(SCQ.front<SCQ.rear){		//�����ͷָ��ֵС�ڶ�βָ���ֵ����Ѷ�ͷָ�뵽��βָ��ָ���Ԫ���������
		for(i=SCQ.front;i<=SCQ.rear;i++)
			printf("%c",SCQ.queue[i]);
	}else{		//�����ͷָ��ֵ���ڶ�βָ���ֵ����Ѷ�βָ�뵽��ͷָ��ָ���Ԫ���������
		for(i=SCQ.front;i<=SCQ.rear+QueueSize;i++)
			printf("%c",SCQ.queue[i%QueueSize]);
	}
	printf("\n");
}
void main(){
	SCQueue Q;	//����һ��˳��ѭ������
	char e;		//����һ���ַ����ͱ��������ڴ�ų����е�Ԫ��
	InitQueue(&Q);		//��ʼ��˳��ѭ������
	/*��3��Ԫ��A��B��C���ν���˳��ѭ������*/
	printf("A���\n");
	EnterQueue(&Q,'A');
	printf("B���\n");
	EnterQueue(&Q,'B');
	printf("C���\n");
	EnterQueue(&Q,'C');
	/*��˳��ѭ�������е�Ԫ����ʾ���*/
	printf("������Ԫ�أ�");
	DisplayQueue(Q);
	/*��˳��ѭ�������еĶ�ͷԪ�س�����*/
	printf("��ͷԪ�ص�һ�γ���\n");
	DeleteQueue(&Q,&e);
	printf("���ӵ�Ԫ�أ�");
	printf("%c\n",e);
	printf("��ͷԪ�صڶ��γ���\n");
	DeleteQueue(&Q,&e);
	printf("���ӵ�Ԫ�أ�");
	printf("%c\n",e);
	/*��˳��ѭ�������е�Ԫ����ʾ���*/
	printf("������Ԫ�أ�");
	DisplayQueue(Q);
	/*��3��Ԫ��D��E��F���ν���˳��ѭ������*/
	printf("D���\n");
	EnterQueue(&Q,'D');
	printf("E���\n");
	EnterQueue(&Q,'E');
	printf("F���\n");
	EnterQueue(&Q,'F');
	/*��˳��ѭ�������е�Ԫ����ʾ���*/
	printf("������Ԫ�أ�");
	DisplayQueue(Q);
	system("pause");
}