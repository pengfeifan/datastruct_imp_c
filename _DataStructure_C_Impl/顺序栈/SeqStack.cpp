// _DataStructure_C_Impl:顺序栈
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
			printf("栈已满，不能进栈！");
			return;
		}
	}
	printf("出栈的元素是：");
	if(PopStack(&S,&e)==1)
		printf("%4c",e);
	if(PopStack(&S,&e)==1)
		printf("%4c",e);  
	printf("\n");
	printf("当前栈顶的元素是：");  
	if(GetTop(S,&e)==0)
	{
		printf("栈已空！");
		return;
	}
	else
		printf("%4c\n",e);
	if(PushStack(&S,'f')==0)
	{
		printf("栈已满，不能进栈！");
		return;
	}
	if(PushStack(&S,'g')==0)
	{
		printf("栈已满，不能进栈！");
		return;
	}
	printf("当前栈中的元素个数是：%d\n",StackLength(S));
	printf("元素出栈的序列是：");
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
	printf("输入字符序列(#表示前一个字符无效，@表示当前行字符无效).\n");
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
	printf("请输入一个正整数(n<15)：");
	scanf("%d",&n);
	printf("递归实现n的阶乘:");
	f=fact(n);
	printf("n!=%4d\n",f);
	f=fact_Stack(n);
	printf("利用栈非递归实现n的阶乘:");
	printf("n!=%4d\n",f);
	system("pause");
}
//============
void main(){
	main_SeqStack();
	main_LineEdit();
	main_fact();
}