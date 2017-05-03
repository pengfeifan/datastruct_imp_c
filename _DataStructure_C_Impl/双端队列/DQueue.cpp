//_DataStructure_C_Impl:˫�˶���
#include<stdio.h>
#include<stdlib.h>
#define QueueSize 8		//����˫�˶��еĴ�С
typedef char DataType;
typedef struct DQueue{	//˫�˶��е����Ͷ���
	DataType queue[QueueSize];
	int end1,end2;		//˫�˶��еĶ�βָ��
}DQueue;
//��Ԫ��e���뵽˫�˶����С�����ɹ�����1�����򷵻�0
int EnterQueue(DQueue *DQ,DataType e,int tag){
	switch(tag){
	case 1:		//1��ʾ�ڶ��е�������
		if(DQ->end1!=DQ->end2){		//Ԫ�����֮ǰ�ж϶����Ƿ�Ϊ��
			DQ->queue[DQ->end1]=e;	//Ԫ��e���
			DQ->end1=(DQ->end1-1)%QueueSize;	//�����ƶ�����ָ��
			return 1;
		}else
			return 0;
	case 2:				//2��ʾ�ڶ��е��Ҷ����
		if(DQ->end1!=DQ->end2){
			DQ->queue[DQ->end2]=e;
			DQ->end2=(DQ->end2+1)%QueueSize;	//�����ƶ�����ָ��
			return 1;
		}else
			return 0;
	}
	return 0;
}
//��Ԫ�س����У����������е�Ԫ�ظ�ֵ��e����������гɹ�����1�����򷵻�0
int DeleteQueue(DQueue *DQ,DataType *e,int tag){
	switch(tag){
	case 1:		//1��ʾ�ڶ��е���˳���
		if(((DQ->end1+1)%QueueSize)!=DQ->end2){		//��Ԫ�س�����֮ǰ�ж϶����Ƿ�Ϊ��
			DQ->end1=(DQ->end1+1)%QueueSize;		//�����ƶ�����ָ�룬��Ԫ�س�����
			*e=DQ->queue[DQ->end1];			//�������е�Ԫ�ظ�ֵ��e
			return 1;
		}else
			return 0;
	case 2:
		if(((DQ->end2-1)%QueueSize)!=DQ->end1){
			DQ->end2=(DQ->end2-1)%QueueSize;		//�����ƶ�����ָ�룬��Ԫ�س�����
			*e=DQ->queue[DQ->end2];
			return 1;
		}else
			return 0;
	}
	return 0;
}
void main(){
	DQueue Q;			/*����˫�˶���Q*/
	char ch;			/*�����ַ�*/
	Q.end1=3;			/*���ö��еĳ�ʼ״̬*/
	Q.end2=4;
	/*��Ԫ��a��b��c�ڶ���������*/	
	if(!EnterQueue(&Q,'a',1))			/*Ԫ��������*/
		printf("����������������ӣ�");
	else
		printf("a�����ӣ�\n");
	if(!EnterQueue(&Q,'b',1))
		printf("����������������ӣ�");
	else
		printf("b�����ӣ�\n");
	if(!EnterQueue(&Q,'c',1))
		printf("����������������ӣ�");
	else
		printf("c�����ӣ�\n");
	/*��Ԫ��d��e�ڶ����Ҷ����*/
	if(!EnterQueue(&Q,'d',2))			/*Ԫ���Ҷ����*/
		printf("����������������ӣ�");
	else
		printf("d�Ҷ���ӣ�\n");
	if(!EnterQueue(&Q,'e',2))
		printf("����������������ӣ�");
	else
		printf("e�Ҷ���ӣ�\n");
	/*Ԫ��c��b��e��d���γ�����*/
	printf("������˳���һ�Σ�");
	DeleteQueue(&Q,&ch,1);				/*Ԫ����˳�����*/
	printf("%c\n",ch);
	printf("������˳���һ�Σ�");
	DeleteQueue(&Q,&ch,1);
	printf("%c\n",ch);
	printf("�����Ҷ˳���һ�Σ�");
	DeleteQueue(&Q,&ch,2);				/*Ԫ���Ҷ˳�����*/
	printf("%c\n",ch);
	printf("�����Ҷ˳���һ�Σ�");
	DeleteQueue(&Q,&ch,2);
	printf("%c\n",ch);
	system("pause");
}