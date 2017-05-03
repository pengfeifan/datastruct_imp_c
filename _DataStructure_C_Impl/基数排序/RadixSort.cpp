#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define MaxNumKey 6 /*�ؼ������������ֵ*/
#define Radix 10	/*�ؼ��ֻ�������ʱ��ʮ���������Ļ���*/
#define MaxSize 1000
#define N 6
typedef int KeyType; /*����ؼ�������*/
typedef struct
{
	KeyType key[MaxNumKey]; /*�ؼ���*/
	int next;
}SListCell;	/*��̬����Ľ������*/

typedef struct
{
	SListCell data[MaxSize];		/*�洢Ԫ�أ�data[0]Ϊͷ���*/
	int keynum;						/*ÿ��Ԫ�صĵ�ǰ�ؼ��ָ���*/
	int length;						/*��̬����ĵ�ǰ����*/
}SList;		/*��̬��������*/
typedef int addr[Radix]; /*ָ����������*/

typedef struct
{
	KeyType key; /* �ؼ����� */
}DataType;

void PrintList(SList L);
void PrintList2(SList L);
void InitList(SList *L,DataType d[],int n);
int trans(char c);
void Distribute(SListCell data[],int i,addr f,addr r);
void Collect(SListCell data[],addr f,addr r);
void RadixSort(SList *L);
void InitList(SList *L,DataType a[],int n)
	/* ��ʼ����̬����L(������D�е����ݴ���L��) */
{ 
	char ch[MaxNumKey],ch2[MaxNumKey];
	int i,j,max=a[0].key;
	for(i=1;i<n;i++)					/*�����Ĺؼ��ִ���max*/
		if(max<a[i].key)
			max=a[i].key;
	(*L).keynum=(int)(log10((float)max))+1;	/*��ؼ��ֵĸ���*/
	(*L).length=n;						/*���������*/
	for(i=1;i<=n;i++)
	{
		itoa(a[i-1].key,ch,10);					/*������ת��Ϊ�ַ�,������ch*/
		for(j=strlen(ch);j<(*L).keynum;j++)		/*���ch�ĳ���<max��λ��,����chǰ��'0'*/
		{
			strcpy(ch2,"0");
			strcat(ch2,ch);
			strcpy(ch,ch2);
		}
		for(j=0;j<(*L).keynum;j++)				/*��ÿ���ؼ��ֵĸ���λ������key*/
			(*L).data[i].key[j]=ch[(*L).keynum-1-j];
	}
	for(i=0;i<(*L).length;++i)				/*��ʼ����̬����*/
		(*L).data[i].next=i+1;
	(*L).data[(*L).length].next=0; 
}

int trans(char c)
	/*���ַ�cת��Ϊ��Ӧ������*/
{ 
	return c-'0';
}
void Distribute(SListCell data[],int i,addr f,addr r) 
	/*Ϊdata�еĵ�i���ؼ���key[i]����Radix���ӱ�ʹͬһ�ӱ���Ԫ�ص�key[i]��ͬ*/
	/*f[0..Radix-1]��r[0..Radix-1]�ֱ�ָ������ӱ��е�һ�������һ��Ԫ��*/
{ 
	int j,p;
	for(j=0;j<Radix;j++)				/*�������ӱ��ʼ��Ϊ�ձ�*/
		f[j]=0;							
	for(p=data[0].next;p;p=data[p].next)
	{
		j=trans(data[p].key[i]);		/*����Ӧ�Ĺؼ����ַ�ת��Ϊ��������*/
		if(!f[j])						/*f[j]�ǿձ���f[j]ָʾ��һ��Ԫ��*/
			f[j]=p;
		else
			data[r[j]].next=p;
		r[j]=p;							/*��p��ָ�Ľ������j���ӱ���*/
	}
}



void Collect(SListCell data[],addr f,addr r)
	/*��key[i]��f[0..Radix-1]��ָ���ӱ��������ӳ�һ����̬����*/
{ 
	int j,t;
	for(j=0;!f[j];j++);	/*�ҵ�һ���ǿ��ӱ�succΪ���̺���*/
	data[0].next=f[j];
	t=r[j];				/*r[0].nextָ���һ���ǿ��ӱ��е�һ�����*/
	while(j<Radix-1)
	{
		for(j=j+1;j<Radix-1&&!f[j];j++);	/*����һ���ǿ��ӱ�*/
		if(f[j])							/*���ǿ�����������һ��*/
		{									
			data[t].next=f[j];
			t=r[j];
		}
	}
	data[t].next=0;		/*tָ�����һ���ǿ��ӱ��е����һ�����*/
}

void RadixSort(SList *L)
	/*��L���л�������ʹ��L��Ϊ���ؼ��ַǵݼ��ľ�̬����L.r[0]Ϊͷ���*/
{ 
	int i;
	addr f,r;
	for(i=0;i<(*L).keynum;i++)			/*�ɵ�λ����λ���ζԸ��ؼ��ֽ��з�����ռ�*/
	{				
		Distribute((*L).data,i,f,r);	/*��i�˷���*/
		Collect((*L).data,f,r);			/*��i���ռ�*/
		printf("��%d���ռ���:",i+1);
		PrintList2(*L);
	}
}



void main()
{
	DataType d[N]={268,126,63,730,587,184};
	SList L;
	InitList(&L,d,N);
	printf("������Ԫ�ظ�����%d�����ؼ��ָ���Ϊ%d��\n",L.length,L.keynum);
	printf("����ǰ��Ԫ��:\n");
	PrintList2(L);
	printf("����ǰ��Ԫ�صĴ��λ��:\n");
	PrintList(L);
	RadixSort(&L);
	printf("�����Ԫ�صĴ��λ��:\n");
	PrintList(L);
	system("pause");
}
void PrintList(SList L)
	/*�����������ʽ�����̬����*/
{ 
	int i,j;
	printf("��� �ؼ��� ��ַ\n");
	for(i=1;i<=L.length;i++)
	{
		printf("%2d    ",i);
		for(j=L.keynum-1;j>=0;j--)
			printf("%c",L.data[i].key[j]);
		printf("    %d\n",L.data[i].next);
	}
}
void PrintList2(SList L)
	/*��������ʽ�����̬����*/
{
	int i=L.data[0].next,j;
	while(i)
	{
		for(j=L.keynum-1;j>=0;j--)
			printf("%c",L.data[i].key[j]);
		printf(" ");
		i=L.data[i].next;
	}
	printf("\n");
}