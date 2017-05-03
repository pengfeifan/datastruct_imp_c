#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"SeqString.h"
/*����������*/
int B_FIndex(SeqString S,int pos,SeqString T,int *count);
int KMP_Index(SeqString S,int pos,SeqString T,int next[],int *count);
void GetNext(SeqString T,int next[]);
void GetNextVal(SeqString T,int nextval[]);
void PrintArray(SeqString T,int next[],int nextval[],int length);
void main(){
	SeqString S,T;
	int count1=0,count2=0,count3=0,find;
	int next[40],nextval[40];

	StrAssign(&S,"abaababaddecab");		/*������S��ֵ*/
	StrAssign(&T,"abad");				/*��ģʽ��T��ֵ*/
	GetNext(T,next);					/*��next����ֵ������next����*/
	GetNextVal(T,nextval);				/*���Ľ����next����ֵ������nextval����*/
	printf("ģʽ��T��next�͸Ľ����nextֵ:\n");
	PrintArray(T,next,nextval,StrLength(T));	/*���ģʽ��T��nextֵ��nextvalֵ*/
	find=B_FIndex(S,1,T,&count1);				/*��ͳ��ģʽ��ƥ��*/
	if(find>0)
		printf("Brute-Force�㷨�ıȽϴ���Ϊ:%2d\n",count1);
	find=KMP_Index(S,1,T,next,&count2);
	if(find>0)
		printf("����next��KMP�㷨�ıȽϴ���Ϊ:%2d\n",count2);
	find=KMP_Index(S,1,T,nextval,&count3);
	if(find>0)
		printf("����nextval��KMPƥ���㷨�ıȽϴ���Ϊ:%2d\n",count3);

	StrAssign(&S,"cbccccbcacbccbacbccbcbcbc");	/*������S��ֵ*/
	StrAssign(&T,"cbccbcbc");					/*��ģʽ��T��ֵ*/
	GetNext(T,next);							/*��next����ֵ������next����*/
	GetNextVal(T,nextval);						/*���Ľ����next����ֵ������nextval����*/
	printf("ģʽ��T��next�͸Ľ����nextֵ:\n");
	PrintArray(T,next,nextval,StrLength(T));	/*���ģʽ��T��nextֵ��nextvalֵ*/
	find=B_FIndex(S,1,T,&count1);				/*��ͳ��ģʽ��ƥ��*/
	if(find>0)
		printf("Brute-Force�㷨�ıȽϴ���Ϊ:%2d\n",count1);
	find=KMP_Index(S,1,T,next,&count2);
	if(find>0)
		printf("����next��KMP�㷨�ıȽϴ���Ϊ:%2d\n",count2);
	find=KMP_Index(S,1,T,nextval,&count3);
	if(find>0)
		printf("����nextval��KMPƥ���㷨�ıȽϴ���Ϊ:%2d\n",count3);
	system("pause");
}
//������S�еĵ�pos��λ�ÿ�ʼ�����Ӵ�T������ҵ������Ӵ���������λ�ã����򣬷���-1
int B_FIndex(SeqString S,int pos,SeqString T,int *count){
	int i,j;
	i=pos-1;
	j=0;
	*count=0;		//count����������ģʽ���ıȽϴ���
	while(i<S.length&&j<T.length){
		if(S.str[i]==T.str[j]){	//�����S�ʹ�T�ж�Ӧλ���ַ���ȣ�������Ƚ���һ���ַ�
			i++;
			j++;
		}else{		//�����ǰ��Ӧλ�õ��ַ�����ȣ���Ӵ�S����һ���ַ���ʼ��T�ĵ�0���ַ���ʼ�Ƚ�
			i=i-j+1;
			j=0;
		}
		(*count)++;
	}
	if(j>=T.length)
		return i-j+1;		//�����S���ҵ���T���򷵻��Ӵ�T������S��λ��
	else
		return -1;
}
//KMPģʽƥ���㷨������ģʽ��T��next����������S�еĵ�pos��λ�ÿ�ʼ�����Ӵ�T������ҵ������Ӵ���������λ�ã����򣬷���-1
int KMP_Index(SeqString S,int pos,SeqString T,int next[],int *count){
	int i,j;
	i=pos-1;
	j=0;
	*count=0;
	while(i<S.length&&j<T.length){
		if(j==-1||S.str[i]==T.str[j]){
			i++;
			j++;
		}else
			j=next[j];
		(*count)++;
	}
	if(j>=T.length)
		return i-T.length+1;
	else 
		return -1;
}
//��ģʽ��T��next����ֵ����������next
void GetNext(SeqString T,int next[]){
	int j,k;
	j=0;
	k=-1;
	next[0]=-1;
	while(j<T.length){
		if(k==-1||T.str[j]==T.str[k]){		//���k=-1��ǰ�ַ���ȣ�������ȽϺ�����ַ���������ֵ���뵽next����
			j++;
			k++;
			next[j]=k;
		}else
			k=next[k];	//�����ǰ�ַ�����ȣ���ģʽ�������ƶ������Ƚ�
	}
}
//��ģʽ��T��next����ֵ������ֵ����������next
void GetNextVal(SeqString T,int nextval[]){
	int j,k;
	j=0;
	k=-1;
	nextval[0]=-1;
	while(j<T.length){
		if(k==-1||T.str[j]==T.str[k]){	//���k=-1��ǰ�ַ���ȣ�������ȽϺ�����ַ���������ֵ���뵽nextval����
			j++;
			k++;
			if(T.str[j]!=T.str[k])		//��������nextval[j]�����е�nextval[k]����ȣ���k�����nextval��
				nextval[j]=k;
			else
				nextval[j]=nextval[k];
		}else			//�����ǰ�ַ�����ȣ���ģʽ�������ƶ������Ƚ�
			k=nextval[k];
	}
}
//ģʽ��T��nextֵ��nextvalֵ�������
void PrintArray(SeqString T,int next[],int nextval[],int length){
	int j;
	printf("j:\t\t");
	for(j=0;j<length;j++)
		printf("%3d",j);
	printf("\n");
	printf("ģʽ��:\t\t");
	for(j=0;j<length;j++)
		printf("%3c",T.str[j]);
	printf("\n");
	printf("next[j]:\t");
	for(j=0;j<length;j++)
		printf("%3d",next[j]);
	printf("\n");
	printf("nextval[j]:\t");
	for(j=0;j<length;j++)
		printf("%3d",nextval[j]);
	printf("\n");
}