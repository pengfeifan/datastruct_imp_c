#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"SeqString.h"
typedef char AtomType;
typedef enum{ATOM,LIST} ElemTag;//ATOM=0，表示原子，LIST=1，表示子表

typedef struct GLNode{
	ElemTag tag;	//标志位tag用于区分元素是原子还是子表
	union{
		AtomType atom;	//AtomType是原子结点的值域，用户自己定义类型
		struct GLNode *hp;		//hp指向表头，tp指向表尾
	}ptr;
	struct GLNode *tp;
}*GList,GLNodeList;

//求广义表的表头结点操作
GLNodeList* GetHead(GList L){
	GLNodeList *p;
	p=L->ptr.hp; 					/*将广义表的表头指针赋值给p*/
	if(!p) 							/*如果广义表为空表，则返回1*/
	{
		printf("该广义表是空表！");
		return NULL;
	}
	else if(p->tag==LIST)
		printf("该广义表的表头是非空的子表。");
	else
		printf("该广义表的表头是原子。");
	return p;
}
//求广义表的表尾操作
GLNodeList *GetTail(GList L){
	GLNodeList *p,*tail;
	p=L->ptr.hp;
	if(!p) 							/*如果广义表为空表，则返回1*/
	{
		printf("该广义表是空表！");
		return NULL;
	}
	tail=(GLNodeList*)malloc(sizeof(GLNodeList));	/*生成tail结点*/
	tail->tag=LIST; 						/*将标志域置为LIST*/
	tail->ptr.hp=p->tp; 					/*将tail的表头指针域指向广义表的表尾*/
	tail->tp=NULL; 						/*将tail的表尾指针域置为空*/
	return tail; 							/*返回指向广义表表尾结点的指针*/
}
//求广义表的长度操作
int GListLength(GList L){
	int length=0; 						/*初始化化广义表的长度*/
	GLNodeList *p=L->ptr.hp;
	while(p) 							/*如果广义表非空，则将p指向表尾指针，统计表的长度*/
	{
		length++;
		p=p->tp;
	}
	return length; 
}
//求广义表的深度操作
int GListDepth(GList L){
	int max,depth;
	GLNode *p;
	if(L->tag==LIST&&L->ptr.hp==NULL) 	/*如果广义表非空，则返回1*/
		return 1;
	if(L->tag==ATOM) 					/*如果广义表是原子，则返回0*/
		return 0;
	p=L->ptr.hp;
	for(max=0;p;p=p->tp) 				/*逐层处理广义表*/
	{
		depth=GListDepth(p);
		if(max<depth)
			max=depth;
	}
	return max+1;
}
//广义表的复制操作。由广义表L复制得到广义表T
void CopyList(GList *T,GList L){
	if(!L) 							/*如果广义表为空，则T为空表*/
		*T=NULL;
	else
	{
		*T=(GList)malloc(sizeof(GLNodeList)); 	/*表L不空，为T建立一个表结点*/
		if(*T==NULL)
			exit(-1);
		(*T)->tag=L->tag;
		if(L->tag==ATOM) 						/*复制原子*/
			(*T)->ptr.atom=L->ptr.atom;
		else
			CopyList(&((*T)->ptr.hp),L->ptr.hp);/*递归复制表头*/
		if(L->tp==NULL)
			(*T)->tp=L->tp;
		else
			CopyList(&((*T)->tp),L->tp);		/*递归复制表尾*/
	}
}
//将串Str分离成两个部分，HeadStr为第一个逗号之前的子串，Str为逗号后的子串
void DistributeString(SeqString *Str,SeqString *HeadStr){
	int len,i,k;
	SeqString Ch,Ch1,Ch2,Ch3;
	len=StrLength(*Str);	//len为Str的长度
	StrAssign(&Ch1,",");	//将字符','、'('和')'分别赋给Ch1,Ch2和Ch3
	StrAssign(&Ch2,"("); 
	StrAssign(&Ch3,")"); 
	SubString(&Ch,*Str,1,1);	//Ch保存Str的第一个字符
	for(i=1,k=0;i<=len&&StrCompare(Ch,Ch1)||k!=0;i++) /*搜索Str最外层的第一个括号*/
	{ 
		SubString(&Ch,*Str,i,1);		/*取出Str的第一个字符*/
		if(!StrCompare(Ch,Ch2))			/*如果第一个字符是'('，则令k加1*/
			k++; 
		else if(!StrCompare(Ch,Ch3))	/*如果当前字符是')'，则令k减去1*/
			k--; 
	}
	if(i<=len)							/*串Str中存在','，它是第i-1个字符*/
	{
		SubString(HeadStr,*Str,1,i-2);	/*HeadStr保存串Str','前的字符*/
		SubString(Str,*Str,i,len-i+1);	/*Str保存串Str','后的字符*/
	}
	else								/*串Str中不存在','*/
	{
		StrCopy(HeadStr,*Str);			/*将串Str的内容复制到串HeadStr*/
		StrClear(Str);					/*清空串Str*/
	}
}
//采用头尾链表创建广义表
void CreateList(GList *L,SeqString S){
	SeqString Sub,HeadSub,Empty;
	GList p,q;
	StrAssign(&Empty,"()"); 
	if(!(*L=(GList)malloc(sizeof(GLNodeList))))		/*为广义表生成一个结点*/
		exit(-1);
	if(!StrCompare(S,Empty))					/*如果输入的串是空串则创建一个空的广义表*/
	{
		(*L)->tag=LIST; 
		(*L)->ptr.hp=(*L)->tp=NULL;
	}
	else 
	{

		if(StrLength(S)==1)							/*广义表是原子，则将原子的值赋值给广义表结点*/
		{
			(*L)->tag=ATOM;
			(*L)->ptr.atom=S.str[0];
			(*L)->tp=NULL;
		}
		else										/*如果是子表*/
		{
			(*L)->tag=LIST;
			(*L)->tp=NULL;
			SubString(&Sub,S,2,StrLength(S)-2);		/*将S去除最外层的括号，然后赋值给Sub*/
			DistributeString(&Sub,&HeadSub);		/*将Sub分离出表头和表尾分别赋值给HeadSub和Sub*/
			CreateList(&((*L)->ptr.hp),HeadSub);	/*递归调用生成广义表*/
			p=(*L)->ptr.hp;
			while(!StrEmpty(Sub))					/*如果表尾不空，则生成结点p，并将尾指针域指向p*/
			{
				DistributeString(&Sub,&HeadSub);
				CreateList(&(p->tp),HeadSub);
				p=p->tp;	
			}

		}
	}
}
//输出广义表的元素
void PrintGList(GList L){
	if(L->tag == LIST)
	{
		printf("(");			/*如果子表存在，先输出左括号 */
		if(L->ptr.hp == NULL)	/*如果子表为空，则输出' '字符 */
			printf(" ");
		else					/*递归输出表头*/
			PrintGList(L->ptr.hp);
		printf(")");			/*在子表的最后输出右括号 */
	}
	else						/*如果是原子，则输出结点的值*/
		printf("%c", L->ptr.atom);
	if(L->tp != NULL)		
	{

		printf(", ");			/*输出逗号*/
		PrintGList(L->tp);		/*递归输出表尾*/
	}
}
//------------------------
void main(){
	GList L,T;
	SeqString S;
	int depth,length;
	StrAssign(&S,"(a,(),(a,(b,c)))");	/*将字符串赋值给串S*/
	CreateList(&L,S);				/*由串创建广义表L*/
	printf("输出广义表L中的元素:\n");
	PrintGList(L);					/*输出广义表中的元素*/
	length=GListLength(L);			/*求广义表的长度*/
	printf("\n广义表L的长度length=%2d\n",length);
	depth=GListDepth(L);			/*求广义表的深度*/
	printf("广义表L的深度depth=%2d\n",depth);
	CopyList(&T,L);
	printf("由广义表L复制得到广义表T.\n广义表T的元素为:\n");
	PrintGList(T);
	length=GListLength(T);			/*求广义表的长度*/
	printf("\n广义表T的长度length=%2d\n",length);
	depth=GListDepth(T);			/*求广义表的深度*/
	printf("广义表T的深度depth=%2d\n",depth);
	system("pause");
}

