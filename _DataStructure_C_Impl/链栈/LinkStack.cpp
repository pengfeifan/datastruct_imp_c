//_DataStructure_C_Impl:链栈
#include<stdio.h>
#include<stdlib.h>

typedef char DataType;
typedef struct node{
	DataType data;
	struct node *next;
}LStackNode,*LinkStack;
//将链栈初始化为空。动态生成头结点，并将头结点的指针域置为空
void InitStack(LinkStack *top){
	if((*top=(LinkStack)malloc(sizeof(LStackNode)))==NULL)		//为头结点分配一个存储空间
		exit(-1);
	(*top)->next=NULL;		//将链栈的头结点指针域置为空
}
//判断链栈是否为空，就是通过判断头结点的指针域是否为空
int StackEmpty(LinkStack top){
	if(top->next==NULL)		//当链栈为空时，返回1；否则返回0
		return 1;
	else 
		return 0;
}
//进栈操作就是要在链表的第一个结点前插入一个新结点，进栈成功返回1
int PushStack(LinkStack top,DataType e){
	LStackNode *p;	//指针p指向新生成的结点
	if((p=(LStackNode *)malloc(sizeof(LStackNode)))==NULL){
		printf("内存分配失败\n");
		exit(-1);
	}
	p->data=e;
	p->next=top->next;	//指针p指向表头结点
	top->next=p;
	return 1;
}
//删除单链表中的第i个位置的结点。删除成功返回1，失败返回0
int PopStack(LinkStack top,DataType *e){
	LStackNode *p;
	p=top->next;
	if(!p){		//判断链栈是否为空
		printf("栈已空\n");
		return 0;
	}
	top->next=p->next;	//将栈顶结点与链表断开，即出栈
	*e=p->data;		//将出栈元素赋值给e
	free(p);		//释放p指向的结点
	return 1;
}
//取栈顶元素操作
int GetTop(LinkStack top,DataType *e){
	LStackNode *p;
	p=top->next;
	if(!p){		//判断链栈是否为空
		printf("栈已空\n");
		return 0;
	}
	*e=p->data;	//将栈顶元素赋值给e
	return 1;
}
//求表长操作
int StackLength(LinkStack top){
	LStackNode *p;
	int count=0;
	p=top;
	while(p->next!=NULL){
		p=p->next;
		count++;
	}
	return count;
}
//销毁链栈操作
void DestroyStack(LinkStack top){
	LStackNode *p,*q;
	p=top;
	while(!p){
		q=p;
		p=p->next;
		free(q);
	}
}
void main_LinkStack(){
	LinkStack S;
	DataType ch[50],e,*p;
	InitStack(&S);
	printf("请输入进栈的字符：\n");
	gets(ch);
	p=&ch[0];
	while(*p){
		PushStack(S,*p);
		p++;
	}
	printf("当前栈顶的元素是：");  
	if(GetTop(S,&e)==0){
		printf("栈已空！\n");
		return ;
	}else{
		printf("%4c\n",e);
	}
	printf("当前栈中的元素个数是：%d\n",StackLength(S));
	printf("元素出栈的序列是：");
	while(!StackEmpty(S)){
		PopStack(S,&e);
		printf("%4c",e);
	}
	printf("\n");
	system("pause");
}
//********************************
int Match(DataType e,DataType ch){
	if(e=='('&&ch==')')
		return 1;
	else if(e=='['&&ch==']')
		return 1;
	else if(e=='{'&&ch=='}')
		return 1;
	else
		return 0;
}
void main_Match(){
	LinkStack S;
	char *p;
	DataType e;
	DataType ch[100];
	InitStack(&S);
	printf("请输入带括号的表达式('{}','[]','()').\n");
	gets(ch);
	p=ch;
	while(*p){
		switch(*p){
		case '(':
		case '[':
		case '{':
			PushStack(S,*p++);
			break;
		case ')':
		case ']':
		case '}':
			if(StackEmpty(S)){
				printf("缺少左括号.\n");
				return;
			}else{
				GetTop(S,&e);
				if(Match(e,*p))
					PopStack(S,&e);
				else{
					printf("左右括号不配对.\n");
					return;
				}
			}
		default:
			p++;
		}
	}
	if(StackEmpty(S))
		printf("括号匹配.\n");
	else
		printf("缺少右括号.\n");
	system("pause");
}
//===========
void main(){
	main_LinkStack();
	main_Match();
}