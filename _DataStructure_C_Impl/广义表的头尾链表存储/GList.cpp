#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"SeqString.h"
typedef char AtomType;
typedef enum{ATOM,LIST} ElemTag;//ATOM=0����ʾԭ�ӣ�LIST=1����ʾ�ӱ�
typedef struct Node
{
	ElemTag tag;			 	/*��־λtag��������Ԫ����ԭ�ӻ����ӱ�*/
	union
	{
		AtomType atom; 		/*AtomType��ԭ�ӽ���ֵ���û��Լ���������*/
		struct
		{
			struct Node *hp,*tp;		/*hpָ���ͷ��tpָ���β*/
		}ptr;
	};
}*GList,GLNode;


GLNode* GetHead(GList L)
	/*������ı�ͷ������*/
{
	GLNode *p;
	if(!L) 							/*��������Ϊ�ձ��򷵻�1*/
	{
		printf("�ù�����ǿձ�");
		return NULL;
	}
	p=L->ptr.hp; 					/*�������ı�ͷָ�븳ֵ��p*/
	if(!p)
		printf("�ù����ı�ͷ�ǿձ�.");
	else if(p->tag==LIST)
		printf("�ù����ı�ͷ�Ƿǿյ��ӱ�");
	else
		printf("�ù����ı�ͷ��ԭ�ӡ�");
	return p;
}
GLNode* GeTail(GList L)
	/*������ı�β����*/
{
	if(!L) 							/*��������Ϊ�ձ��򷵻�1*/
	{
		printf("�ù�����ǿձ�");
		return NULL;
	}
	return L->ptr.tp; 				/*���������ǿձ��򷵻�ָ���β����ָ��*/
}
int GListLength(GList L)
	/*������ĳ��Ȳ���*/
{
	int length=0;
	while(L) 							/*��������ǿգ���pָ���βָ�룬ͳ�Ʊ�ĳ���*/
	{
		L=L->ptr.tp;
		length++;
	}
	return length; 
}
int GListDepth(GList L)
	/*���������Ȳ���*/
{
	int max,depth;
	GLNode *p;
	if(!L) 							/*��������ǿգ��򷵻�1*/
		return 1;
	if(L->tag==ATOM) 				/*����������ԭ�ӣ��򷵻�0*/
		return 0;
	for(max=0,p=L;p;p=p->ptr.tp) 		/*��㴦������*/
	{
		depth=GListDepth(p->ptr.hp);
		if(max<depth)
			max=depth;
	}
	return max+1;
}
void CopyList(GList *T,GList L)
	/*�����ĸ��Ʋ������ɹ����L���Ƶõ������T*/
{
	if(!L) 							/*��������Ϊ�գ���TΪ�ձ�*/
		*T=NULL;
	else
	{
		*T=(GList)malloc(sizeof(GLNode)); 	/*��L���գ�ΪT����һ������*/
		if(*T==NULL)
			exit(-1);
		(*T)->tag=L->tag;
		if(L->tag==ATOM) 			/*����ԭ��*/
			(*T)->atom=L->atom;
		else						/*�ݹ鸴���ӱ�*/
		{
			CopyList(&((*T)->ptr.hp),L->ptr.hp);
			CopyList(&((*T)->ptr.tp),L->ptr.tp);
		}
	}
}
//------------
void DistributeString(SeqString *Str,SeqString *HeadStr)
	/*����Str������������֣�HeadStrΪ��һ������֮ǰ���Ӵ���StrΪ���ź���Ӵ�*/
{ 
	int len,i,k; 
	SeqString Ch,Ch1,Ch2,Ch3;
	len=StrLength(*Str);				/*lenΪStr�ĳ���*/
	StrAssign(&Ch1,",");				/*���ַ�','��'('��')'�ֱ𸳸�Ch1,Ch2��Ch3*/
	StrAssign(&Ch2,"("); 
	StrAssign(&Ch3,")"); 
	SubString(&Ch,*Str,1,1);			/*Ch����Str�ĵ�һ���ַ�*/
	for(i=1,k=0;i<=len&&StrCompare(Ch,Ch1)||k!=0;i++) /*����Str�����ĵ�һ������*/
	{ 
		SubString(&Ch,*Str,i,1);		/*ȡ��Str�ĵ�һ���ַ�*/
		if(!StrCompare(Ch,Ch2))			/*�����һ���ַ���'('������k��1*/
			k++; 
		else if(!StrCompare(Ch,Ch3))	/*�����ǰ�ַ���')'������k��ȥ1*/
			k--; 
	}
	if(i<=len)							/*��Str�д���','�����ǵ�i-1���ַ�*/
	{
		SubString(HeadStr,*Str,1,i-2);	/*HeadStr���洮Str','ǰ���ַ�*/
		SubString(Str,*Str,i,len-i+1);	/*Str���洮Str','����ַ�*/
	}
	else								/*��Str�в�����','*/
	{
		StrCopy(HeadStr,*Str);			/*����Str�����ݸ��Ƶ���HeadStr*/
		StrClear(Str);					/*��մ�Str*/
	}
}
void CreateList(GList *L,SeqString S)
	/*����ͷβ�����������*/
{
	SeqString Sub,HeadSub,Empty;
	GList p,q;
	StrAssign(&Empty,"()"); 
	if(!StrCompare(S,Empty))			/*�������Ĵ��ǿմ��򴴽�һ���յĹ����*/
		*L=NULL; 
	else 
	{
		if(!(*L=(GList)malloc(sizeof(GLNode))))		/*Ϊ���������һ�����*/
			exit(-1);
		if(StrLength(S)==1)							/*�������ԭ�ӣ���ԭ�ӵ�ֵ��ֵ���������*/
		{
			(*L)->tag=ATOM;
			(*L)->atom=S.str[0];
		}
		else										/*������ӱ�*/
		{
			(*L)->tag=LIST;
			p=*L;
			SubString(&Sub,S,2,StrLength(S)-2);		/*��Sȥ�����������ţ�Ȼ��ֵ��Sub*/
			do
			{ 
				DistributeString(&Sub,&HeadSub);	/*��Sub�������ͷ�ͱ�β�ֱ�ֵ��HeadSub��Sub*/
				CreateList(&(p->ptr.hp),HeadSub);	/*�ݹ�������ɹ����*/
				q=p;
				if(!StrEmpty(Sub))					/*�����β���գ������ɽ��p������βָ����ָ��p*/
				{
					if(!(p=(GLNode *)malloc(sizeof(GLNode))))
						exit(-1);
					p->tag=LIST;
					q->ptr.tp=p;
				}
			}while(!StrEmpty(Sub));
			q->ptr.tp=NULL;
		}
	}
}
void PrintGList(GList L)
	/*���������Ԫ��*/
{
	if(L)								/*����������*/
	{
		if(L->tag==ATOM)				/*�����ԭ�ӣ������*/
			printf("%c ",L->atom);
		else 
		{
			PrintGList(L->ptr.hp);		/*�ݹ����L�ı�ͷ*/
			PrintGList(L->ptr.tp);		/*�ݹ����L�ı�β*/
		}
	}
}
void main(){
	GList L,T;
	SeqString S;
	int depth,length;
	StrAssign(&S,"(a,(),(a,(b,c)))");	/*���ַ�����ֵ����S*/
	CreateList(&L,S);				/*�ɴ����������L*/
	printf("��������L�е�Ԫ��:\n");
	PrintGList(L);					/*���������е�Ԫ��*/
	length=GListLength(L);			/*������ĳ���*/
	printf("\n�����L�ĳ���length=%2d\n",length);
	depth=GListDepth(L);			/*����������*/
	printf("�����L�����depth=%2d\n",depth);
	CopyList(&T,L);
	printf("�ɹ����L���Ƶõ������T.\n�����T��Ԫ��Ϊ:\n");
	PrintGList(T);
	length=GListLength(T);			/*������ĳ���*/
	printf("\n�����T�ĳ���length=%2d\n",length);
	depth=GListDepth(T);			/*����������*/
	printf("�����T�����depth=%2d\n",depth);
	system("pause");
}