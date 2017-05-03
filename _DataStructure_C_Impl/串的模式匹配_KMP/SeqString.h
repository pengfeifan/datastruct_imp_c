#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MaxLength 60
typedef struct{
	char str[MaxLength];
	int length;
}SeqString;
//���ĸ�ֵ����
void StrAssign(SeqString *S,char cstr[]){
	int i;
	for(i=0;cstr[i]!='\0';i++)
		S->str[i]=cstr[i];	//������cstr�е��ַ���ֵ����S
	S->length=i;
}
//�жϴ��Ƿ�Ϊ�գ���Ϊ�շ���1�����򷵻�0
int StrEmpty(SeqString S){
	if(S.length==0)
		return 1;
	else
		return 0;
}
//�󴮵ĳ��Ȳ���
int StrLength(SeqString S){
	return S.length;
}
//���ĸ��Ʋ���
void StrCopy(SeqString *T,SeqString S){
	int i;
	for(i=0;i<S.length;i++)	//����S���ַ���ֵ����T
		T->str[i]=S.str[i];
	T->length=S.length;	//����S�ĳ��ȸ�ֵ����T
}
//���ıȽϲ���
int StrCompare(SeqString S,SeqString T){	//�Ƚ��������е��ַ�
	int i;
	for(i=0;i<S.length&&i<T.length;i++){		//�Ƚ��������е��ַ�
		if(S.str[i]!=T.str[i])		//��������ַ���ͬ���򷵻������ַ��Ĳ�ֵ
			return (S.str[i]-T.str[i]);
	}
	return (S.length-T.length);	//����Ƚ���ϣ������������ĳ��ȵĲ�ֵ
}
//���Ĳ����������S�е�pos��λ�ò���T��Ϊ�������
int StrInsert(SeqString *S,int pos,SeqString T){
	int i;
	if(pos<0||pos-1>S->length){	//����λ�ò���ȷ������0
		printf("����λ�ò���ȷ");
		return 0;
	}
	if(S->length+T.length<=MaxLength){	//��һ������������Ӵ��󴮳���MaxLength�����Ӵ�T�����ز��뵽��S��
		for(i=S->length+T.length-1;i>=pos+T.length-1;i--)	//�ڲ����Ӵ�Tǰ����S��pos����ַ�����ƶ�len��λ��
			S->str[i]=S->str[i-T.length];
		for(i=0;i<T.length;i++)	//�������뵽S��
			S->str[pos+i-1]=T.str[i];
		S->length=S->length+T.length;
		return 1;
	}else if(pos+T.length<=MaxLength){	//�ڶ���������Ӵ�������ȫ���뵽S�У�����S�е��ַ����ᱻ�ص�
		for(i=MaxLength-1;i>T.length+pos-i;i--)		//��S��pos�Ժ���ַ������ƶ�����������
			S->str[i]=S->str[i-T.length];
		for(i=0;i<T.length;i++)		//��T���뵽S��
			S->str[i+pos-1]=T.str[i];
		S->length=MaxLength;
		return 0;
	}else{		//������������Ӵ�T���ܱ���ȫ���뵽S�У�T�н������ַ�������
		for(i=0;i<MaxLength-pos;i++)	//��Tֱ�Ӳ��뵽S�У�����֮ǰ����Ҫ�ƶ�S�е��ַ�
			S->str[i+pos-1]=T.str[i];
		S->length=MaxLength;
		return 0;
	}
}
//�ڴ�S��ɾ��pos��ʼ��len���ַ�
int StrDelete(SeqString *S,int pos,int len){
	int i;
	if(pos<0||len<0||pos+len-1>S->length){
		printf("ɾ��λ�ò���ȷ������len���Ϸ�");
		return 0;
	}else{
		for(i=pos+len;i<=S->length-1;i++)
			S->str[i-len]=S->str[i];
		S->length=S->length-len;
		return 1;
	}
}
//�������Ӳ���
int StrCat(SeqString *T,SeqString S){
	int i,flag;
	if(T->length+S.length<=MaxLength){
		for(i=T->length;i<T->length+S.length;i++)
			T->str[i]=S.str[i-T->length];
		T->length=T->length+S.length;
		flag=1;
	}else if(T->length<MaxLength){
		for(i=T->length;i<MaxLength;i++)
			T->str[i]=S.str[i-T->length];
		T->length=MaxLength;
		flag=0;
	}
	return flag;
}
//��ȡ�Ӵ�����
int SubString(SeqString *Sub,SeqString S,int pos,int len){
	int i;
	if(pos<0||len<0||pos+len-1>S.length){
		printf("����pos��len���Ϸ�");
		return 0;
	}else{
		for(i=0;i<len;i++)
			Sub->str[i]=S.str[i+pos-1];
		Sub->length=len;
		return 1;
	}
}
//���Ķ�λ����
int StrIndex(SeqString S,int pos,SeqString T){
	int i,j;
	if(StrEmpty(T))
		return 0;
	i=pos;
	j=0;
	while(i<S.length&&j<T.length){
		if(S.str[i]==T.str[j]){
			i++;
			j++;
		}else{
			i=i-j+1;
			j=0;
		}
	}
	if(j>=T.length)
		return i-j+1;
	else 
		return 0;
}
//�����滻����
int StrReplace(SeqString *S,SeqString T,SeqString V){
	//��S�����е�T�滻ΪV
	int i;
	int flag;
	if(StrEmpty(T))
		return 0;
	i=0;
	do{
		i=StrIndex(*S,i,T);//�ҵ�T��S�е�λ��
		if(i){
			StrDelete(S,i,StrLength(T));	//ɾ���ҵ���T
			flag=StrInsert(S,i,V);	//��iλ�ò���V
			if(!flag)
				return 0;
			i+=StrLength(V);
		}
	}while(i);
	return 1;
}
//������ղ���
void StrClear(SeqString *S){
	S->length=0;
}
//===========
void StrPrint(SeqString S){
	int i;
	for(i=0;i<S.length;i++){
		printf("%c",S.str[i]);
	}
	printf("\n");
}