//_DataStructure_C_Impl:
#include<stdio.h>
#include<stdlib.h>
#define StackSize 100
typedef char DataType;
typedef struct{
	DataType stack[StackSize];
	int top;
}SeqStack;
//将栈初始化为空栈只需要把栈顶指针top置为
void InitStack(SeqStack *S){
	S->top=0;//把栈顶指针置为0
}
//判断栈是否为空，栈为空返回1，否则返回0
int StackEmpty(SeqStack S){
	if(S.top==0)
		return 1;
	else
		return 0;
}
//取栈顶元素。将栈顶元素值返回给e，并返回1表示成功；否则返回0表示失败。
int GetTop(SeqStack S,DataType *e){
	if(S.top<=0){		//在取栈顶元素之前，判断栈是否为空
		printf("栈已经空!\n");
		return 0;
	}else{
		*e=S.stack[S.top-1];	//在取栈顶元素
		return 1;
	}
}
//将元素e进栈，元素进栈成功返回1，否则返回0
int PushStack(SeqStack *S,DataType e){
	if(S->top>=StackSize){	//在元素进栈前，判断是否栈已经满
		printf("栈已满，不能进栈！\n");
		return 0;
	}else{
		S->stack[S->top]=e;	//元素e进栈
		S->top++;	//修改栈顶指针
		return 1;
	}
}
//出栈操作。将栈顶元素出栈，并将其赋值给e。出栈成功返回1，否则返回0
int PopStack(SeqStack *S,DataType *e){
	if(S->top<=0){	//元素出栈之前，判断栈是否为空
		printf("栈已经没有元素，不能出栈!\n");
		return 0;
	}else{
		S->top--;	//先修改栈顶指针，即出栈
		*e=S->stack[S->top]; //将出栈元素赋值给e
		return 1;
	}
}
//求栈的长度，即栈中元素个数，栈顶指针的值就等于栈中元素的个数
int StackLength(SeqStack S){
	return S.top;
}
//清空栈的操作
void ClearStack(SeqStack *S){
	S->top=0;
}
//===================================
#include<string.h>
#define MaxSize 50
typedef struct{
	float data[MaxSize];
	int top;
}OpStack;	//操作数栈的类型定义

//将中缀表达式转换为后缀表达式
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
		case '(':		//左括号入栈
			PushStack(&S,ch);
			break;
		case ')':		//如果当前字符是右括号，则将栈中的字符出栈，直到栈中的一个左括号出栈为止
			while(GetTop(S,&e)&&e!='('){
				PopStack(&S,&e);
				exp[j]=e;
				j++;
			}
			PopStack(&S,&e);	//左括号出栈
			break;
		case '+':
		case '-':
			while(!StackEmpty(S)&&GetTop(S,&e)&&e!='('){	//如果当前字符是+号或-号，则将栈中字符出栈，直到遇到左括号为止
				PopStack(&S,&e);
				exp[j]=e;
				j++;
			}
			PushStack(&S,ch);	//将当前字符入栈
			break;
		case '*':
		case '/':
			while(!StackEmpty(S)&&GetTop(S,&e)&&e=='/'||e=='*'){		//如果当前字符是*号或者是/号，则将栈中字符出栈
				PopStack(&S,&e);
				exp[j]=e;
				j++;
			}
			PushStack(&S,ch);		//当前字符入栈
			break;
		case ' ':
			break;
		default:		//处理数字字符
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
//计算后缀表达式的值
float ComputeExpress(char a[]){
	OpStack S;
	int i=0;
	int value;
	float x1,x2;
	float result;
	S.top=-1;
	while(a[i]!='\0'){
		if(a[i]!=' '&&a[i]>='0'&&a[i]<='9'){	//如果当前字符是数字字符，则将其转换为数字并存入栈中
			value=0;
			while(a[i]!=' '){
				value=10* value+a[i]-'0';
				i++;
			}
			S.top++;
			S.data[S.top]=value;
		}else{	//如果当前字符是运算符，则对栈中的数据进行求值，并将结果保存到栈中
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
			printf("表达式错误");
			exit(-1);
		}
	}
}
void main()
{
	char a[MaxSize],b[MaxSize];
	float f;
	printf("请输入一个算术表达式：\n");
	gets(a);
	printf("中缀表达式为：%s\n",a);
	TranslateExpress(a,b);
	printf("后缀表达式为：%s\n",b);
	f=ComputeExpress(b);
	printf("计算结果：%f\n",f);
	system("pause");
} 