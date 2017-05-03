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
//初始化稀疏矩阵
void InitMatrix(CrossList *M){
	M->rowhead=M->colhead=NULL;
	M->m=M->n=M->len=0;
}
//销毁稀疏矩阵
void DestroyMatrix(CrossList *M){
	int i;
	OLink p,q;
	for(i=0;i<M->m;i++){		//按行释放结点空间
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
//使用十字链表的存储方式创建稀疏矩阵
void CreateMatrix(CrossList *M){
	int i,k;
	int m,n,num;
	OLNode *p,*q;
	if(M->rowhead)		//如果链表不空，则释放链表空间
		DestroyMatrix(M);
	printf("请输入稀疏矩阵的行数,列数,非零元素的个数: ");
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
	for(k=0;k<m;k++)		//初始化十字链表，将链表的行指针置为空
		M->rowhead[k]=NULL;
	for(k=0;k<n;k++)		//初始化十字链表，将链表的列指针置为空
		M->colhead[k]=NULL;
	printf("请按任意次序输入%d个非零元的行号、列号及元素值:\n",M->len);
	for(k=0;k<num;k++){
		p=(OLNode*)malloc(sizeof(OLNode));	 /*动态生成结点*/
		if(!p)
			exit(-1);
		printf("请输入第%d个非零元的行号(0~%d)、列号(0~%d)及元素值:",k+1,m,n);
		scanf("%d,%d,%d",&p->i,&p->j,&p->e); /*依次输入行号，列号和元素值*/
		/*-----------------------------行插入p结点-----------------------------------*/
		if(M->rowhead[p->i]==NULL||M->rowhead[p->i]->j>p->j)/*如果是第一个结点或当前元素的列号小于表头指向的一个的元素*/
		{
			p->right=M->rowhead[p->i];	
			M->rowhead[p->i]=p;
		}
		else
		{
			q=M->rowhead[p->i];
			while(q->right&&q->right->j<p->j)	/*找到要插入结点的位置*/
				q=q->right; 
			p->right=q->right;					/*将p插入到q结点之后*/
			q->right=p;
		}
		/*------------------------------列插入p结点-----------------------------------*/
		q=M->colhead[p->j];						/*将q指向待插入的链表*/
		if(!q||p->i<q->i)						/*如果p的行号小于表头指针的行号或为空表，则直接插入*/
		{
			p->down=M->colhead[p->j]; 
			M->colhead[p->j]=p;
		}
		else
		{
			while(q->down&&q->down->i<p->i)		/*如果q的行号小于p的行号，则在链表中查找插入位置*/
				q=q->down; 
			p->down=q->down;					/*将p插入到q结点之下*/
			q->down=p;
		}
	}
}
//按矩阵形式输出十字链表
void PrintMatrix(CrossList M){
	int i,j;
	OLink p;
	for(i=0;i<M.m;i++)
	{ 
		p=M.rowhead[i];				/*p指向该行的第1个非零元素*/
		for(j=0;j<M.n;j++)			/*从第一列到最后一列进行输出*/
			if(!p||p->j!=j)			/*已到该行表尾或当前结点的列值不等于当前列值，则输出0*/
				printf("%-3d",0);
			else
			{
				printf("%-3d",p->e);
				p=p->right;
			}
			printf("\n");
	}
}
//按照行序将p插入到稀疏矩阵中
void InsertMatrix(CrossList *M,OLink p){
	OLink q=M->rowhead[p->i];		/*q指向待插行表*/
	if(!q||p->j<q->j)				/*待插的行表空或p所指结点的列值小于首结点的列值，则直接插入*/
	{
		p->right=M->rowhead[p->i]; 
		M->rowhead[p->i]=p;
	}
	else
	{
		while(q->right&&q->right->j<p->j)	/*q所指不是尾结点且q的下一结点的列值小于p所指结点的列值*/
			q=q->right; 
		p->right=q->right; 
		q->right=p;
	}
	q=M->colhead[p->j];					/*q指向待插列表*/
	if(!q||p->i<q->i)					/*待插的列表空或p所指结点的行值小于首结点的行值*/
	{
		p->down=M->colhead[p->j];
		M->colhead[p->j]=p;
	}
	else
	{
		while(q->down&&q->down->i<p->i)	/*q所指不是尾结点且q的下一结点的行值小于p所指结点的行值*/
			q=q->down; 
		p->down=q->down; 
		q->down=p;
	}
	M->len++;
}
//比较两个元素值的大小。如果a>b，返回1，a=b，则返回0，a<b，则返回-1
int CompareElement(int a,int b){
	if(a<b)
		return -1;
	if(a==b)
		return 0;
	return 1;
}
//十字链表表示的两个稀疏矩阵相加运算
void AddMatrix(CrossList A,CrossList B,CrossList *C){
	int i;
	OLink pa,pb,pc;
	if(A.m!=B.m||A.n!=B.n)
	{
		printf("两个矩阵不是同类型的,不能相加\n");
		exit(-1);
	}
	/*初始化矩阵Q*/
	C->m=A.m; 
	C->n=A.n;
	C->len=0;				/*矩阵C的元素个数的初值为0*/
	/*初始化十字链表*/
	if(!(C->rowhead=(OLink*)malloc(C->m*sizeof(OLink))))	/*动态生成行表头数组*/
		exit(-1);
	if(!(C->colhead=(OLink*)malloc(C->n*sizeof(OLink))))	/*动态生成列表头数组*/
		exit(-1);
	for(i=0;i<C->m;i++)		/*初始化矩阵C的行表头指针数组，各行链表为空*/
		C->rowhead[i]=NULL;
	for(i=0;i<C->n;i++)		/*初始化矩阵C的列表头指针数组，各列链表为空*/
		C->colhead[i]=NULL;
	/*将稀疏矩阵按行的顺序相加*/
	for(i=0;i<A.m;i++)
	{
		pa=A.rowhead[i];	/*pa指向矩阵A的第i行的第1个结点*/
		pb=B.rowhead[i];	/*pb指向矩阵B的第i行的第1个结点*/
		while(pa&&pb) 
		{
			pc=(OLink)malloc(sizeof(OLNode)); /*生成新结点*/
			switch(CompareElement(pa->j,pb->j))
			{
			case -1:				/*如果A的列号小于B的列号，将矩阵A的当前元素值插入C*/
				*pc=*pa; 
				InsertMatrix(C,pc); 
				pa=pa->right; 
				break;
			case  0:				/*如果矩阵A和B的列号相等，元素值相加*/
				*pc=*pa; 
				pc->e+=pb->e;
				if(pc->e!=0)		/*如果和为非零，则将结点插入到C中*/
					InsertMatrix(C,pc); 
				else
					free(pc); 
				pa=pa->right; 
				pb=pb->right;
				break;
			case  1:				/*如果A的列号大于B的列号，将矩阵B的当前元素值插入C中*/
				*pc=*pb; 
				InsertMatrix(C,pc); 
				pb=pb->right; 
			}
		}
		while(pa)					/*如果矩阵A还有未处理完的非零元素，则将剩余元素插入C中*/
		{
			pc=(OLink)malloc(sizeof(OLNode)); 
			*pc=*pa;
			InsertMatrix(C,pc); 
			pa=pa->right; 
		}
		while(pb)					/*如果矩阵B还有未处理完的非零元素，则将剩余元素插入C中*/
		{
			pc=(OLink)malloc(sizeof(OLNode));
			*pc=*pb; 
			InsertMatrix(C,pc); 
			pb=pb->right; 
		}
	}
	if(C->len==0)					/*矩阵C的非零元素个数为零，则直接消耗C*/
		DestroyMatrix(C);
}
void main(){
	CrossList M,N,Q;
	int row,col;
	DataType value;
	OLink p;
	InitMatrix(&M);		/*初始化稀疏矩阵*/
	CreateMatrix(&M);	/*创建稀疏矩阵*/
	printf("矩阵M：\n");
	PrintMatrix(M);		/*以矩阵的形式输出稀疏矩阵*/

	InitMatrix(&N);		/*初始化稀疏矩阵*/
	CreateMatrix(&N);	/*创建稀疏矩阵*/
	printf("矩阵N：\n");
	PrintMatrix(N);	/*以矩阵的形式输出稀疏矩阵*/
	/*两个矩阵的相加*/
	AddMatrix(M,N,&Q);
	printf("两个稀疏矩阵相加结果：M+N=\n");
	PrintMatrix(Q);
	/*在矩阵M中插入一个元素*/
	printf("请输入要插入元素的行号、列号和元素值：");
	scanf("%d,%d,%d",&row,&col,&value);
	p=(OLNode*)malloc(sizeof(OLNode));
	p->i=row;
	p->j=col;
	p->e=value;
	InsertMatrix(&M,p);
	printf("插入元素后，矩阵M：\n");
	PrintMatrix(M);
	system("pause");
}