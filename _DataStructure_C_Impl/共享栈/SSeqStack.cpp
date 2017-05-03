// _DataStructure_C_Impl:����ջ
#include<stdio.h>
#include<stdlib.h>
#define StackSize 100
typedef char DataType;
//��������ջ�����ݽṹ���Ͷ���
typedef struct  
{
	DataType stack[StackSize];
	int top[2];
}SSeqStack;
//����ջ�ĳ�ʼ������
void InitStack(SSeqStack *S){
	S->top[0]=0;
	S->top[1]=StackSize-1;
}
//����ջ��ջ��������ջ�ɹ�����1�����򷵻�0
int PushStack(SSeqStack *S,DataType e,int flag){
	if(S->top[0]==S->top[1])	//�ڽ�ջ����֮ǰ���жϹ���ջ�Ƿ�Ϊ��
		return 0;
	switch(flag){
	case 0:		//��flagΪ0����ʾԪ��Ҫ����˵�ջ
		S->stack[S->top[0]]=e;	//Ԫ�ؽ�ջ
		S->top[0]++;	//�޸�ջ��ָ��
		break;
	case 1:		//��flagΪ1����ʾԪ��Ҫ���Ҷ˵�ջ
		S->stack[S->top[1]]=e;	//Ԫ�ؽ�ջ
		S->top[1]--;	//�޸�ջ��ָ��
		break;
	default:
		return 0;
	}
	return 1;
}
//��ջ����
int PopStack(SSeqStack *S,DataType *e,int flag){
	switch(flag){		//�ڳ�ջ����֮ǰ���ж����ĸ�ջҪ���г�ջ����
	case 0:
		if(S->top[0]==0)	//��˵�ջΪ�գ��򷵻�0����ʾ��ջ����ʧ��
			return 0;
		S->top[0]--;	//�޸�ջ��ָ��
		*e=S->stack[S->top[0]];	//����ջ��Ԫ�ظ�ֵ��e
		break;
	case 1:		
		if(S->top[1]==StackSize-1)		////�Ҷ˵�ջΪ�գ��򷵻�0����ʾ��ջ����ʧ��
			return 0;
		S->top[1]++;		//�޸�ջ��ָ��
		*e=S->stack[S->top[1]];		//����ջ��Ԫ�ظ�ֵ��e
		break;
	default:
		return 0;
	}
	return 1;
}
//ȡջ��Ԫ�ء���ջ��Ԫ��ֵ���ظ�e��������1��ʾ�ɹ������򷵻�0��ʾʧ�ܡ�
int GetTop(SSeqStack S,DataType *e,int flag){
	switch(flag){
	case 0:
		if(S.top[0]==0)
			return 0;
		*e=S.stack[S.top[0]-1];
		break;
	case 1:
		if(S.top[1]==StackSize-1)
			return 0;
		*e=S.stack[S.top[1]+1];
		break;
	default:
		return 0;
	}
	return 1;
}
int StackEmpty(SSeqStack S,int flag){
	switch(flag){
	case 0:
		if(S.top[0]==0)
			return 1;
		break;
	case 1:
		if(S.top[1]==StackSize-1)
			return 1;
		break;
	default:
		return 0;
	}
	return 0;
}
void main(){
	SSeqStack S1,S2;			/*����һ��ջ*/
	int i;
	DataType a[]={'a','b','c','d','e'};
	DataType b[]={'x','y','z','r'};
	DataType e1,e2;
	InitStack(&S1);					/*��ʼ��ջ*/
	InitStack(&S2);
	for(i=0;i<sizeof(a)/sizeof(a[0]);i++)	/*������a��Ԫ�����ν�ջ*/
	{
		if(PushStack(&S1,a[i],0)==0)
		{
			printf("ջ���������ܽ�ջ��");
			return;
		}
	}
	for(i=0;i<sizeof(b)/sizeof(b[0]);i++)	/*������b��Ԫ�����ν�ջ*/
	{
		if(PushStack(&S2,b[i],1)==0)
		{
			printf("ջ���������ܽ�ջ��");
			return;
		}
	}	
	if(GetTop(S1,&e1,0)==0)
	{
		printf("ջ�ѿ�");
		return;
	}
	if(GetTop(S2,&e2,1)==0)
	{
		printf("ջ�ѿ�");
		return;
	}
	printf("ջS1��ջ��Ԫ���ǣ�%c��ջS2��ջ��Ԫ����:%c\n",e1,e2);
	printf("S1��ջ��Ԫ�ش����ǣ�");
	i=0;
	while(!StackEmpty(S1,0))	
	{
		PopStack(&S1,&e1,0);
		printf("%4c",e1);	
	}
	printf("\n");
	printf("S2��ջ��Ԫ�ش����ǣ�");
	while(!StackEmpty(S2,1))	
	{
		PopStack(&S2,&e2,1);
		printf("%4c",e2);
	}
	printf("\n");	
	system("pause");
}