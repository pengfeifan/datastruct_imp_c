//_DataStructure_C_Impl:
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
//===================================
#include<string.h>
#define MaxSize 50
typedef struct{
	float data[MaxSize];
	int top;
}OpStack;	//������ջ�����Ͷ���

//����׺���ʽת��Ϊ��׺���ʽ
void TranslateExpress(char str[],char exp[]){
	SeqStack S;
	char ch;
	DataType e;
	int i=0,j=0;
	InitStack(&S);
	ch=str[i];
	i++;
	while(ch!='\0'){
		switch(ch){
		case '(':		//��������ջ
			PushStack(&S,ch);
			break;
		case ')':		//�����ǰ�ַ��������ţ���ջ�е��ַ���ջ��ֱ��ջ�е�һ�������ų�ջΪֹ
			while(GetTop(S,&e)&&e!='('){
				PopStack(&S,&e);
				exp[j]=e;
				j++;
			}
			PopStack(&S,&e);	//�����ų�ջ
			break;
		case '+':
		case '-':
			while(!StackEmpty(S)&&GetTop(S,&e)&&e!='('){	//�����ǰ�ַ���+�Ż�-�ţ���ջ���ַ���ջ��ֱ������������Ϊֹ
				PopStack(&S,&e);
				exp[j]=e;
				j++;
			}
			PushStack(&S,ch);	//����ǰ�ַ���ջ
			break;
		case '*':
		case '/':
			while(!StackEmpty(S)&&GetTop(S,&e)&&e=='/'||e=='*'){		//�����ǰ�ַ���*�Ż�����/�ţ���ջ���ַ���ջ
				PopStack(&S,&e);
				exp[j]=e;
				j++;
			}
			PushStack(&S,ch);		//��ǰ�ַ���ջ
			break;
		case ' ':
			break;
		default:		//���������ַ�
			while(ch>='0'&&ch<='9'){
				exp[j]=ch;
				j++;
				ch=str[i];
				i++;
			}
			i--;
			exp[j]=' ';
			j++;
		}
		ch=str[i];
		i++;
	}
	while(!StackEmpty(S)){
		PopStack(&S,&e);
		exp[j]=e;
		j++;
	}
	exp[j]='\0';
}
//�����׺���ʽ��ֵ
float ComputeExpress(char a[]){
	OpStack S;
	int i=0;
	int value;
	float x1,x2;
	float result;
	S.top=-1;
	while(a[i]!='\0'){
		if(a[i]!=' '&&a[i]>='0'&&a[i]<='9'){	//�����ǰ�ַ��������ַ�������ת��Ϊ���ֲ�����ջ��
			value=0;
			while(a[i]!=' '){
				value=10* value+a[i]-'0';
				i++;
			}
			S.top++;
			S.data[S.top]=value;
		}else{	//�����ǰ�ַ�������������ջ�е����ݽ�����ֵ������������浽ջ��
			switch(a[i]){
			case '+':
				x1=S.data[S.top];
				S.top--;
				x2=S.data[S.top];
				S.top--;
				result=x1+x2;
				S.top++;
				S.data[S.top]=result;
				break;
			case '-':
				x1=S.data[S.top];
				S.top--;
				x2=S.data[S.top];
				S.top--;
				result=x2-x1;
				S.top++;
				S.data[S.top]=result;
				break;
			case '*':
				x1=S.data[S.top];
				S.top--;
				x2=S.data[S.top];
				S.top--;
				result=x1*x2;
				S.top++;
				S.data[S.top]=result;
				break;
			case '/':
				x1=S.data[S.top];
				S.top--;
				x2=S.data[S.top];
				S.top--;
				result=x2/x1;
				S.top++;
				S.data[S.top]=result;
				break;
			}
			i++;
		}
	}
	if(!S.top!=-1){
		result=S.data[S.top];
		S.top--;
		if(S.top==-1)
			return result;
		else{
			printf("���ʽ����");
			exit(-1);
		}
	}
}
void main()
{
	char a[MaxSize],b[MaxSize];
	float f;
	printf("������һ���������ʽ��\n");
	gets(a);
	printf("��׺���ʽΪ��%s\n",a);
	TranslateExpress(a,b);
	printf("��׺���ʽΪ��%s\n",b);
	f=ComputeExpress(b);
	printf("��������%f\n",f);
	system("pause");
} 