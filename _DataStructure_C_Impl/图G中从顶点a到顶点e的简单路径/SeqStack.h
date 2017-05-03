#pragma once
#include<stdio.h>
#include<stdlib.h>
#define StackSize 100
typedef int DataType;	//ջԪ�����Ͷ���
typedef struct{
	DataType stack[StackSize];
	int top;
}SeqStack;
//��ջ��ʼ��Ϊ��ջֻ��Ҫ��ջ��ָ��top��Ϊ
void InitStack(SeqStack *S){
	S->top=0;//��ջ��ָ����Ϊ0
}
//�ж�ջ�Ƿ�Ϊ�գ�ջΪ�շ���1�����򷵻�0
int StackEmpty(SeqStack S){
	if(S.top==0)
		return 1;
	else
		return 0;
}
//ȡջ��Ԫ�ء���ջ��Ԫ��ֵ���ظ�e��������1��ʾ�ɹ������򷵻�0��ʾʧ�ܡ�
int GetTop(SeqStack S,DataType *e){
	if(S.top<=0){		//��ȡջ��Ԫ��֮ǰ���ж�ջ�Ƿ�Ϊ��
		printf("ջ�Ѿ���!\n");
		return 0;
	}else{
		*e=S.stack[S.top-1];	//��ȡջ��Ԫ��
		return 1;
	}
}
//��Ԫ��e��ջ��Ԫ�ؽ�ջ�ɹ�����1�����򷵻�0
int PushStack(SeqStack *S,DataType e){
	if(S->top>=StackSize){	//��Ԫ�ؽ�ջǰ���ж��Ƿ�ջ�Ѿ���
		printf("ջ���������ܽ�ջ��\n");
		return 0;
	}else{
		S->stack[S->top]=e;	//Ԫ��e��ջ
		S->top++;	//�޸�ջ��ָ��
		return 1;
	}
}
//��ջ��������ջ��Ԫ�س�ջ�������丳ֵ��e����ջ�ɹ�����1�����򷵻�0
int PopStack(SeqStack *S,DataType *e){
	if(S->top<=0){	//Ԫ�س�ջ֮ǰ���ж�ջ�Ƿ�Ϊ��
		printf("ջ�Ѿ�û��Ԫ�أ����ܳ�ջ!\n");
		return 0;
	}else{
		S->top--;	//���޸�ջ��ָ�룬����ջ
		*e=S->stack[S->top]; //����ջԪ�ظ�ֵ��e
		return 1;
	}
}
//��ջ�ĳ��ȣ���ջ��Ԫ�ظ�����ջ��ָ���ֵ�͵���ջ��Ԫ�صĸ���
int StackLength(SeqStack S){
	return S.top;
}
//���ջ�Ĳ���
void ClearStack(SeqStack *S){
	S->top=0;
}
