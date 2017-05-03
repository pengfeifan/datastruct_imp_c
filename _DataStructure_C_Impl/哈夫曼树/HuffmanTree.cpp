#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define infinity 10000		//����һ�����޴��ֵ
//�����������Ͷ���
typedef struct{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char **HuffmanCode;//��Ź���������
//��������n�������Ȩֵ��С�Ľ�����
int Min(HuffmanTree t,int n){
	int i,flag;
	int f=infinity;		//fΪһ�����޴��ֵ
	for(i=1;i<=n;i++)
		if(t[i].weight<f&&t[i].parent==0){
			f=t[i].weight;
			flag=i;
		}
	t[flag].parent=1;	//��ѡ�еĽ���˫�׽�㸳ֵ1�������ٴβ��Ҹý��
	return flag;
}
//��n�������ѡ������Ȩֵ��С�Ľ����ţ�����s1��С��s2��С
void Select(HuffmanTree *t,int n,int *s1,int *s2){
	int x;
	*s1=Min(*t,n);
	*s2=Min(*t,n);
	if((*t)[*s1].weight>(*t)[*s2].weight){		//������s1��Ȩֵ�������s2��Ȩֵ�������߽�����ʹs1��С��s2��С
		x=*s1;
		*s1=*s2;
		*s2=x;
	}
}
//�����������HT�����������ı�������HC�У�wΪn���ַ���Ȩֵ
void HuffmanCoding(HuffmanTree *HT,HuffmanCode *HC,int *w,int n){ //Ҷ�ӽ�㵽��������
	int m,i,s1,s2,start;
	unsigned int c,f;
	HuffmanTree p;
	char *cd;
	if(n<=1)
		return;
	m=2*n-1;
	*HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));	//�������Ԫδ��
	for(p=*HT+1,i=1;i<=n;++i,++p,++w){		//��ʼ��n��Ҷ�ӽ��
		(*p).weight=*w;
		(*p).parent=0;
		(*p).lchild=0;
		(*p).rchild=0;
	}
	for(;i<=m;++i,++p){			//��n-1����Ҷ�ӽ���˫�׽���ʼ����Ϊ0
		(*p).parent=0;
	}
	for(i=n+1;i<=m;++i){		//�����������
		Select(HT,i-1,&s1,&s2);	//��������Ȩֵ��С���������
		(*HT)[s1].parent=(*HT)[s2].parent=i;
		(*HT)[i].lchild=s1;
		(*HT)[i].rchild=s2;
		(*HT)[i].weight=(*HT)[s1].weight+(*HT)[s2].weight;
	}
	//��Ҷ�ӽ�㵽�������ÿ���ַ��Ĺ���������
	*HC=(HuffmanCode)malloc((n+1)*sizeof(char *));
	cd=(char *)malloc(n*sizeof(char));		//Ϊ���������붯̬����ռ�
	cd[n-1]='\0';
	//��n��Ҷ�ӽ��Ĺ���������
	for(i=1;i<=n;i++){
		start=n-1;		//���������λ��
		for(c=i,f=(*HT)[i].parent;f!=0;c=f,f=(*HT)[f].parent)	//��Ҷ�ӽ�㵽����������
			if((*HT)[f].lchild==c)
				cd[--start]='0';
			else
				cd[--start]='1';
		(*HC)[i]=(char *)malloc((n-start)*sizeof(char));	//Ϊ��i���ַ��������ռ�
		strcpy((*HC)[i],&cd[start]);	//����ǰ������Ĺ��������븴�Ƶ�HC
	}
	free(cd);
}
//�����������HT�����Ӹ���㵽Ҷ�ӽ����շ������벢������HC��
void HuffmanCoding2(HuffmanTree *HT,HuffmanCode *HC,int *w,int n){
	int s1,s2,i,m; 
	unsigned int r,cdlen; 
	char *cd;
	HuffmanTree p;

	if(n<=1)
		return;
	m=2*n-1;
	*HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode)); 
	for(p=*HT+1,i=1;i<=n;i++,p++,w++)
	{
		(*p).weight=*w;
		(*p).parent=0;
		(*p).lchild=0;
		(*p).rchild=0;
	}
	for(;i<=m;++i,++p)
		(*p).parent=0;
	/*�����������HT*/
	for(i=n+1;i<=m;i++) 
	{ 
		Select(HT,i-1,&s1,&s2);
		(*HT)[s1].parent=(*HT)[s2].parent=i;
		(*HT)[i].lchild=s1;
		(*HT)[i].rchild=s2;
		(*HT)[i].weight=(*HT)[s1].weight+(*HT)[s2].weight;
	}
	/*�Ӹ���㵽Ҷ�ӽ����շ������벢������HC��*/
	*HC=(HuffmanCode)malloc((n+1)*sizeof(char*));
	cd=(char*)malloc(n*sizeof(char)); 
	r=m;						/*�Ӹ���㿪ʼ*/
	cdlen=0;					/*���볤�ȳ�ʼ��Ϊ0*/
	for(i=1;i<=m;i++)
		(*HT)[i].weight=0;		/*��weight����Ϊ״̬��־*/
	while(r)
	{
		if((*HT)[r].weight==0)/*���weight������㣬˵�����ӽ��û�б���*/
		{ 
			(*HT)[r].weight=1;	/*�޸ı�־*/
			if((*HT)[r].lchild!=0)/*����������ӽ�㣬�򽫱�����Ϊ0*/
			{
				r=(*HT)[r].lchild;
				cd[cdlen++]='0';
			}
			else if((*HT)[r].rchild==0)/*�����Ҷ�ӽ�㣬�򽫵�ǰ����ı��뱣�浽HC��*/
			{ 
				(*HC)[r]=(char *)malloc((cdlen+1)*sizeof(char));
				cd[cdlen]='\0';
				strcpy((*HC)[r],cd);
			}
		}
		else if((*HT)[r].weight==1)/*����Ѿ����ʹ����ӽ�㣬������Һ��ӽ��*/
		{ 
			(*HT)[r].weight=2;		/*�޸ı�־*/
			if((*HT)[r].rchild!=0)
			{
				r=(*HT)[r].rchild;
				cd[cdlen++]='1';
			}
		}
		else						/*������ӽ����Һ��ӽ�㶼�Ѿ����ʹ������˻ص�˫�׽��*/
		{ 
			(*HT)[r].weight=0;
			r=(*HT)[r].parent;
			--cdlen;					/*���볤�ȼ�1*/
		}
	}
	free(cd);
}
void main(){
	HuffmanTree HT;
	HuffmanCode HC;
	int *w,n,i;
	printf("������Ҷ�ӽ��ĸ���: ");
	scanf("%d",&n);
	w=(int*)malloc(n*sizeof(int));		/*Ϊn������Ȩֵ�����ڴ�ռ�*/
	for(i=0;i<n;i++)
	{
		printf("�������%d������Ȩֵ:",i+1);
		scanf("%d",w+i);
	}
	HuffmanCoding(&HT,&HC,w,n);
	for(i=1;i<=n;i++)
	{
		printf("����������:");
		puts(HC[i]);
	}

	HuffmanCoding2(&HT,&HC,w,n);
	for(i=1;i<=n;i++)
	{
		printf("����������:");
		puts(HC[i]);
	}

	/*�ͷ��ڴ�ռ�*/
	for(i=1;i<=n;i++)
		free(HC[i]);
	free(HC);
	free(HT);
	system("pause");
}