// _DataStructure_C_Impl:共享栈
#include<stdio.h>
#include<stdlib.h>
#define StackSize 100
typedef char DataType;
//两个共享栈的数据结构类型定义
typedef struct  
{
	DataType stack[StackSize];
	int top[2];
}SSeqStack;
//共享栈的初始化操作
void InitStack(SSeqStack *S){
	S->top[0]=0;
	S->top[1]=StackSize-1;
}
//共享栈进栈操作。进栈成功返回1，否则返回0
int PushStack(SSeqStack *S,DataType e,int flag){
	if(S->top[0]==S->top[1])	//在进栈操作之前，判断共享栈是否为空
		return 0;
	switch(flag){
	case 0:		//当flag为0，表示元素要进左端的栈
		S->stack[S->top[0]]=e;	//元素进栈
		S->top[0]++;	//修改栈顶指针
		break;
	case 1:		//当flag为1，表示元素要进右端的栈
		S->stack[S->top[1]]=e;	//元素进栈
		S->top[1]--;	//修改栈顶指针
		break;
	default:
		return 0;
	}
	return 1;
}
//出栈操作
int PopStack(SSeqStack *S,DataType *e,int flag){
	switch(flag){		//在出栈操作之前，判断是哪个栈要进行出栈操作
	case 0:
		if(S->top[0]==0)	//左端的栈为空，则返回0，表示出栈操作失败
			return 0;
		S->top[0]--;	//修改栈顶指针
		*e=S->stack[S->top[0]];	//将出栈的元素赋值给e
		break;
	case 1:		
		if(S->top[1]==StackSize-1)		////右端的栈为空，则返回0，表示出栈操作失败
			return 0;
		S->top[1]++;		//修改栈顶指针
		*e=S->stack[S->top[1]];		//将出栈的元素赋值给e
		break;
	default:
		return 0;
	}
	return 1;
}
//取栈顶元素。将栈顶元素值返回给e，并返回1表示成功；否则返回0表示失败。
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
	SSeqStack S1,S2;			/*定义一个栈*/
	int i;
	DataType a[]={'a','b','c','d','e'};
	DataType b[]={'x','y','z','r'};
	DataType e1,e2;
	InitStack(&S1);					/*初始化栈*/
	InitStack(&S2);
	for(i=0;i<sizeof(a)/sizeof(a[0]);i++)	/*将数组a中元素依次进栈*/
	{
		if(PushStack(&S1,a[i],0)==0)
		{
			printf("栈已满，不能进栈！");
			return;
		}
	}
	for(i=0;i<sizeof(b)/sizeof(b[0]);i++)	/*将数组b中元素依次进栈*/
	{
		if(PushStack(&S2,b[i],1)==0)
		{
			printf("栈已满，不能进栈！");
			return;
		}
	}	
	if(GetTop(S1,&e1,0)==0)
	{
		printf("栈已空");
		return;
	}
	if(GetTop(S2,&e2,1)==0)
	{
		printf("栈已空");
		return;
	}
	printf("栈S1的栈顶元素是：%c，栈S2的栈顶元素是:%c\n",e1,e2);
	printf("S1出栈的元素次序是：");
	i=0;
	while(!StackEmpty(S1,0))	
	{
		PopStack(&S1,&e1,0);
		printf("%4c",e1);	
	}
	printf("\n");
	printf("S2出栈的元素次序是：");
	while(!StackEmpty(S2,1))	
	{
		PopStack(&S2,&e2,1);
		printf("%4c",e2);
	}
	printf("\n");	
	system("pause");
}