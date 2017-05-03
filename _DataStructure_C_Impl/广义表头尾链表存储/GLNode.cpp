#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"SeqString.h"
typedef char AtomType;
typedef enum{ATOM,LIST} ElemTag;//ATOM=0����ʾԭ�ӣ�LIST=1����ʾ�ӱ�

typedef struct GLNode{
	ElemTag tag;	//��־λtag��������Ԫ����ԭ�ӻ����ӱ�
	union{
		AtomType atom;	//AtomType��ԭ�ӽ���ֵ���û��Լ���������
		struct GLNode *hp;		//hpָ���ͷ��tpָ���β
	}ptr;
	struct GLNode *tp;
}*GList,GLNodeList;

//������ı�ͷ������
GLNodeList* GetHead(GList L){
	GLNodeList *p;
	p=L->ptr.hp; 					/*�������ı�ͷָ�븳ֵ��p*/
	if(!p) 							/*��������Ϊ�ձ��򷵻�1*/
	{
		printf("�ù�����ǿձ�");
		return NULL;
	}
	else if(p->tag==LIST)
		printf("�ù����ı�ͷ�Ƿǿյ��ӱ�");
	else
		printf("�ù����ı�ͷ��ԭ�ӡ�");
	return p;
}
//������ı�β����
GLNodeList *GetTail(GList L){
	GLNodeList *p,*tail;
	p=L->ptr.hp;
	if(!p) 							/*��������Ϊ�ձ��򷵻�1*/
	{
		printf("�ù�����ǿձ�");
		return NULL;
	}
	tail=(GLNodeList*)malloc(sizeof(GLNodeList));	/*����tail���*/
	tail->tag=LIST; 						/*����־����ΪLIST*/
	tail->ptr.hp=p->tp; 					/*��tail�ı�ͷָ����ָ������ı�β*/
	tail->tp=NULL; 						/*��tail�ı�βָ������Ϊ��*/
	return tail; 							/*����ָ�������β����ָ��*/
}
//������ĳ��Ȳ���
int GListLength(GList L){
	int length=0; 						/*��ʼ���������ĳ���*/
	GLNodeList *p=L->ptr.hp;
	while(p) 							/*��������ǿգ���pָ���βָ�룬ͳ�Ʊ�ĳ���*/
	{
		length++;
		p=p->tp;
	}
	return length; 
}
//���������Ȳ���
int GListDepth(GList L){
	int max,depth;
	GLNode *p;
	if(L->tag==LIST&&L->ptr.hp==NULL) 	/*��������ǿգ��򷵻�1*/
		return 1;
	if(L->tag==ATOM) 					/*����������ԭ�ӣ��򷵻�0*/
		return 0;
	p=L->ptr.hp;
	for(max=0;p;p=p->tp) 				/*��㴦������*/
	{
		depth=GListDepth(p);
		if(max<depth)
			max=depth;
	}
	return max+1;
}
//�����ĸ��Ʋ������ɹ����L���Ƶõ������T
void CopyList(GList *T,GList L){
	if(!L) 							/*��������Ϊ�գ���TΪ�ձ�*/
		*T=NULL;
	else
	{
		*T=(GList)malloc(sizeof(GLNodeList)); 	/*��L���գ�ΪT����һ������*/
		if(*T==NULL)
			exit(-1);
		(*T)->tag=L->tag;
		if(L->tag==ATOM) 						/*����ԭ��*/
			(*T)->ptr.atom=L->ptr.atom;
		else
			CopyList(&((*T)->ptr.hp),L->ptr.hp);/*�ݹ鸴�Ʊ�ͷ*/
		if(L->tp==NULL)
			(*T)->tp=L->tp;
		else
			CopyList(&((*T)->tp),L->tp);		/*�ݹ鸴�Ʊ�β*/
	}
}
//����Str������������֣�HeadStrΪ��һ������֮ǰ���Ӵ���StrΪ���ź���Ӵ�
void DistributeString(SeqString *Str,SeqString *HeadStr){
	int len,i,k;
	SeqString Ch,Ch1,Ch2,Ch3;
	len=StrLength(*Str);	//lenΪStr�ĳ���
	StrAssign(&Ch1,",");	//���ַ�','��'('��')'�ֱ𸳸�Ch1,Ch2��Ch3
	StrAssign(&Ch2,"("); 
	StrAssign(&Ch3,")"); 
	SubString(&Ch,*Str,1,1);	//Ch����Str�ĵ�һ���ַ�
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
//����ͷβ�����������
void CreateList(GList *L,SeqString S){
	SeqString Sub,HeadSub,Empty;
	GList p,q;
	StrAssign(&Empty,"()"); 
	if(!(*L=(GList)malloc(sizeof(GLNodeList))))		/*Ϊ���������һ�����*/
		exit(-1);
	if(!StrCompare(S,Empty))					/*�������Ĵ��ǿմ��򴴽�һ���յĹ����*/
	{
		(*L)->tag=LIST; 
		(*L)->ptr.hp=(*L)->tp=NULL;
	}
	else 
	{

		if(StrLength(S)==1)							/*�������ԭ�ӣ���ԭ�ӵ�ֵ��ֵ���������*/
		{
			(*L)->tag=ATOM;
			(*L)->ptr.atom=S.str[0];
			(*L)->tp=NULL;
		}
		else										/*������ӱ�*/
		{
			(*L)->tag=LIST;
			(*L)->tp=NULL;
			SubString(&Sub,S,2,StrLength(S)-2);		/*��Sȥ�����������ţ�Ȼ��ֵ��Sub*/
			DistributeString(&Sub,&HeadSub);		/*��Sub�������ͷ�ͱ�β�ֱ�ֵ��HeadSub��Sub*/
			CreateList(&((*L)->ptr.hp),HeadSub);	/*�ݹ�������ɹ����*/
			p=(*L)->ptr.hp;
			while(!StrEmpty(Sub))					/*�����β���գ������ɽ��p������βָ����ָ��p*/
			{
				DistributeString(&Sub,&HeadSub);
				CreateList(&(p->tp),HeadSub);
				p=p->tp;	
			}

		}
	}
}
//���������Ԫ��
void PrintGList(GList L){
	if(L->tag == LIST)
	{
		printf("(");			/*����ӱ���ڣ������������ */
		if(L->ptr.hp == NULL)	/*����ӱ�Ϊ�գ������' '�ַ� */
			printf(" ");
		else					/*�ݹ������ͷ*/
			PrintGList(L->ptr.hp);
		printf(")");			/*���ӱ�������������� */
	}
	else						/*�����ԭ�ӣ����������ֵ*/
		printf("%c", L->ptr.atom);
	if(L->tp != NULL)		
	{

		printf(", ");			/*�������*/
		PrintGList(L->tp);		/*�ݹ������β*/
	}
}
//------------------------
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

