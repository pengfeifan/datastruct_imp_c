// _DataStructure_C_Impl:˳��ջ
#include<stdio.h>
#include<stdlib.h>
#define StackSize 100
typedef char DataType;
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
//********************
void main_SeqStack(){
	SeqStack S;
	int i;
	DataType a[]={'a','b','c','d','e'};
	DataType e;
	InitStack(&S);
	for(i=0;i<sizeof(a)/sizeof(a[0]);i++)
	{
		if(PushStack(&S,a[i])==0)
		{
			printf("ջ���������ܽ�ջ��");
			return;
		}
	}
	printf("��ջ��Ԫ���ǣ�");
	if(PopStack(&S,&e)==1)
		printf("%4c",e);
	if(PopStack(&S,&e)==1)
		printf("%4c",e);  
	printf("\n");
	printf("��ǰջ����Ԫ���ǣ�");  
	if(GetTop(S,&e)==0)
	{
		printf("ջ�ѿգ�");
		return;
	}
	else
		printf("%4c\n",e);
	if(PushStack(&S,'f')==0)
	{
		printf("ջ���������ܽ�ջ��");
		return;
	}
	if(PushStack(&S,'g')==0)
	{
		printf("ջ���������ܽ�ջ��");
		return;
	}
	printf("��ǰջ�е�Ԫ�ظ����ǣ�%d\n",StackLength(S));
	printf("Ԫ�س�ջ�������ǣ�");
	while(!StackEmpty(S))
	{
		PopStack(&S,&e);
		printf("%4c",e);
	}
	printf("\n");
	system("pause");
}
//********************
void main_LineEdit(){
	SeqStack S;
	char ch;
	DataType e;
	DataType a[50];
	int i,j=0;
	InitStack(&S);
	printf("�����ַ�����(#��ʾǰһ���ַ���Ч��@��ʾ��ǰ���ַ���Ч).\n");
	ch=getchar();
	while(ch!='\n'){
		switch(ch){
		case '#':
			if(!StackEmpty(S))
				PopStack(&S,&ch);
			break;
		case '@':
			ClearStack(&S);
			break;
		default:
			PushStack(&S,ch);
		}
		ch=getchar();
	}
	while(!StackEmpty(S)){
		PopStack(&S,&e);
		a[j++]=e;
	}
	for(i=j-1;i>=0;i--)
		printf("%c",a[i]);
	printf("\n");
	ClearStack(&S);
	system("pause");
}
//***************************
int fact(int n){
	int f,i;
	f=1;
	for(i=1;i<=n;i++)
		f=f*i;
	return f;
}
#define Max 100
int fact_Stack(int n){
	int s[Max][2],top=-1;
	top++;
	s[top][0]=n;
	s[top][1]=0;
	do{
		if(s[top][0]==1)
			s[top][1]=1;
		if(s[top][0]>1&&s[top][1]==0){
			top++;
			s[top][0]=s[top-1][0]-1;
			s[top][1]=0;
		}
		if(s[top][1]!=0){
			s[top-1][1]=s[top][1]*s[top-1][0];
			top--;
		}
	}while(top>0);
	return s[0][1];
}
void main_fact()
{
	int f,n;
	printf("������һ��������(n<15)��");
	scanf("%d",&n);
	printf("�ݹ�ʵ��n�Ľ׳�:");
	f=fact(n);
	printf("n!=%4d\n",f);
	f=fact_Stack(n);
	printf("����ջ�ǵݹ�ʵ��n�Ľ׳�:");
	printf("n!=%4d\n",f);
	system("pause");
}
//============
void main(){
	main_SeqStack();
	main_LineEdit();
	main_fact();
}