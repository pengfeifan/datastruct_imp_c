#include<stdio.h>
#include<stdlib.h>
typedef int DataType;
typedef struct OLNode{
	int i,j;
	DataType e;
	struct OLNode *right,*down;
}OLNode,*OLink;
typedef struct{
	OLink *rowhead,*colhead;
	int m,n,len;
}CrossList;
//��ʼ��ϡ�����
void InitMatrix(CrossList *M){
	M->rowhead=M->colhead=NULL;
	M->m=M->n=M->len=0;
}
//����ϡ�����
void DestroyMatrix(CrossList *M){
	int i;
	OLink p,q;
	for(i=0;i<M->m;i++){		//�����ͷŽ��ռ�
		p=*(M->rowhead+i);
		while(p){
			q=p;
			p=p->right;
			free(q);
		}
	}
	free(M->rowhead);
	free(M->colhead);
	InitMatrix(M);
}
//ʹ��ʮ������Ĵ洢��ʽ����ϡ�����
void CreateMatrix(CrossList *M){
	int i,k;
	int m,n,num;
	OLNode *p,*q;
	if(M->rowhead)		//��������գ����ͷ�����ռ�
		DestroyMatrix(M);
	printf("������ϡ����������,����,����Ԫ�صĸ���: ");
	scanf("%d,%d,%d",&m,&n,&num);
	M->m=m;
	M->n=n;
	M->len=num;
	M->rowhead=(OLink*)malloc(m*sizeof(OLink));
	if(!M->rowhead)
		exit(-1);
	M->colhead=(OLink*)malloc(n*sizeof(OLink));
	if(!M->colhead)
		exit(-1);
	for(k=0;k<m;k++)		//��ʼ��ʮ���������������ָ����Ϊ��
		M->rowhead[k]=NULL;
	for(k=0;k<n;k++)		//��ʼ��ʮ���������������ָ����Ϊ��
		M->colhead[k]=NULL;
	printf("�밴�����������%d������Ԫ���кš��кż�Ԫ��ֵ:\n",M->len);
	for(k=0;k<num;k++){
		p=(OLNode*)malloc(sizeof(OLNode));	 /*��̬���ɽ��*/
		if(!p)
			exit(-1);
		printf("�������%d������Ԫ���к�(0~%d)���к�(0~%d)��Ԫ��ֵ:",k+1,m,n);
		scanf("%d,%d,%d",&p->i,&p->j,&p->e); /*���������кţ��кź�Ԫ��ֵ*/
		/*-----------------------------�в���p���-----------------------------------*/
		if(M->rowhead[p->i]==NULL||M->rowhead[p->i]->j>p->j)/*����ǵ�һ������ǰԪ�ص��к�С�ڱ�ͷָ���һ����Ԫ��*/
		{
			p->right=M->rowhead[p->i];	
			M->rowhead[p->i]=p;
		}
		else
		{
			q=M->rowhead[p->i];
			while(q->right&&q->right->j<p->j)	/*�ҵ�Ҫ�������λ��*/
				q=q->right; 
			p->right=q->right;					/*��p���뵽q���֮��*/
			q->right=p;
		}
		/*------------------------------�в���p���-----------------------------------*/
		q=M->colhead[p->j];						/*��qָ������������*/
		if(!q||p->i<q->i)						/*���p���к�С�ڱ�ͷָ����кŻ�Ϊ�ձ���ֱ�Ӳ���*/
		{
			p->down=M->colhead[p->j]; 
			M->colhead[p->j]=p;
		}
		else
		{
			while(q->down&&q->down->i<p->i)		/*���q���к�С��p���кţ����������в��Ҳ���λ��*/
				q=q->down; 
			p->down=q->down;					/*��p���뵽q���֮��*/
			q->down=p;
		}
	}
}
//��������ʽ���ʮ������
void PrintMatrix(CrossList M){
	int i,j;
	OLink p;
	for(i=0;i<M.m;i++)
	{ 
		p=M.rowhead[i];				/*pָ����еĵ�1������Ԫ��*/
		for(j=0;j<M.n;j++)			/*�ӵ�һ�е����һ�н������*/
			if(!p||p->j!=j)			/*�ѵ����б�β��ǰ������ֵ�����ڵ�ǰ��ֵ�������0*/
				printf("%-3d",0);
			else
			{
				printf("%-3d",p->e);
				p=p->right;
			}
			printf("\n");
	}
}
//��������p���뵽ϡ�������
void InsertMatrix(CrossList *M,OLink p){
	OLink q=M->rowhead[p->i];		/*qָ������б�*/
	if(!q||p->j<q->j)				/*������б�ջ�p��ָ������ֵС���׽�����ֵ����ֱ�Ӳ���*/
	{
		p->right=M->rowhead[p->i]; 
		M->rowhead[p->i]=p;
	}
	else
	{
		while(q->right&&q->right->j<p->j)	/*q��ָ����β�����q����һ������ֵС��p��ָ������ֵ*/
			q=q->right; 
		p->right=q->right; 
		q->right=p;
	}
	q=M->colhead[p->j];					/*qָ������б�*/
	if(!q||p->i<q->i)					/*������б�ջ�p��ָ������ֵС���׽�����ֵ*/
	{
		p->down=M->colhead[p->j];
		M->colhead[p->j]=p;
	}
	else
	{
		while(q->down&&q->down->i<p->i)	/*q��ָ����β�����q����һ������ֵС��p��ָ������ֵ*/
			q=q->down; 
		p->down=q->down; 
		q->down=p;
	}
	M->len++;
}
//�Ƚ�����Ԫ��ֵ�Ĵ�С�����a>b������1��a=b���򷵻�0��a<b���򷵻�-1
int CompareElement(int a,int b){
	if(a<b)
		return -1;
	if(a==b)
		return 0;
	return 1;
}
//ʮ�������ʾ������ϡ������������
void AddMatrix(CrossList A,CrossList B,CrossList *C){
	int i;
	OLink pa,pb,pc;
	if(A.m!=B.m||A.n!=B.n)
	{
		printf("����������ͬ���͵�,�������\n");
		exit(-1);
	}
	/*��ʼ������Q*/
	C->m=A.m; 
	C->n=A.n;
	C->len=0;				/*����C��Ԫ�ظ����ĳ�ֵΪ0*/
	/*��ʼ��ʮ������*/
	if(!(C->rowhead=(OLink*)malloc(C->m*sizeof(OLink))))	/*��̬�����б�ͷ����*/
		exit(-1);
	if(!(C->colhead=(OLink*)malloc(C->n*sizeof(OLink))))	/*��̬�����б�ͷ����*/
		exit(-1);
	for(i=0;i<C->m;i++)		/*��ʼ������C���б�ͷָ�����飬��������Ϊ��*/
		C->rowhead[i]=NULL;
	for(i=0;i<C->n;i++)		/*��ʼ������C���б�ͷָ�����飬��������Ϊ��*/
		C->colhead[i]=NULL;
	/*��ϡ������е�˳�����*/
	for(i=0;i<A.m;i++)
	{
		pa=A.rowhead[i];	/*paָ�����A�ĵ�i�еĵ�1�����*/
		pb=B.rowhead[i];	/*pbָ�����B�ĵ�i�еĵ�1�����*/
		while(pa&&pb) 
		{
			pc=(OLink)malloc(sizeof(OLNode)); /*�����½��*/
			switch(CompareElement(pa->j,pb->j))
			{
			case -1:				/*���A���к�С��B���кţ�������A�ĵ�ǰԪ��ֵ����C*/
				*pc=*pa; 
				InsertMatrix(C,pc); 
				pa=pa->right; 
				break;
			case  0:				/*�������A��B���к���ȣ�Ԫ��ֵ���*/
				*pc=*pa; 
				pc->e+=pb->e;
				if(pc->e!=0)		/*�����Ϊ���㣬�򽫽����뵽C��*/
					InsertMatrix(C,pc); 
				else
					free(pc); 
				pa=pa->right; 
				pb=pb->right;
				break;
			case  1:				/*���A���кŴ���B���кţ�������B�ĵ�ǰԪ��ֵ����C��*/
				*pc=*pb; 
				InsertMatrix(C,pc); 
				pb=pb->right; 
			}
		}
		while(pa)					/*�������A����δ������ķ���Ԫ�أ���ʣ��Ԫ�ز���C��*/
		{
			pc=(OLink)malloc(sizeof(OLNode)); 
			*pc=*pa;
			InsertMatrix(C,pc); 
			pa=pa->right; 
		}
		while(pb)					/*�������B����δ������ķ���Ԫ�أ���ʣ��Ԫ�ز���C��*/
		{
			pc=(OLink)malloc(sizeof(OLNode));
			*pc=*pb; 
			InsertMatrix(C,pc); 
			pb=pb->right; 
		}
	}
	if(C->len==0)					/*����C�ķ���Ԫ�ظ���Ϊ�㣬��ֱ������C*/
		DestroyMatrix(C);
}
void main(){
	CrossList M,N,Q;
	int row,col;
	DataType value;
	OLink p;
	InitMatrix(&M);		/*��ʼ��ϡ�����*/
	CreateMatrix(&M);	/*����ϡ�����*/
	printf("����M��\n");
	PrintMatrix(M);		/*�Ծ������ʽ���ϡ�����*/

	InitMatrix(&N);		/*��ʼ��ϡ�����*/
	CreateMatrix(&N);	/*����ϡ�����*/
	printf("����N��\n");
	PrintMatrix(N);	/*�Ծ������ʽ���ϡ�����*/
	/*������������*/
	AddMatrix(M,N,&Q);
	printf("����ϡ�������ӽ����M+N=\n");
	PrintMatrix(Q);
	/*�ھ���M�в���һ��Ԫ��*/
	printf("������Ҫ����Ԫ�ص��кš��кź�Ԫ��ֵ��");
	scanf("%d,%d,%d",&row,&col,&value);
	p=(OLNode*)malloc(sizeof(OLNode));
	p->i=row;
	p->j=col;
	p->e=value;
	InsertMatrix(&M,p);
	printf("����Ԫ�غ󣬾���M��\n");
	PrintMatrix(M);
	system("pause");
}