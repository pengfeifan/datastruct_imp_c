//双向链表
#include<stdio.h>
#include<stdlib.h>

typedef char DataType;
typedef struct Node{
	DataType data;
	struct Node *prior;
	struct Node *next;
}DListNode,*DLinkList;
//初始化双向循环链表
int InitDList(DLinkList *head){  //head 是二级指针
	*head=(DLinkList)malloc(sizeof(DListNode));
	if(!head)
		return -1;
	(*head)->next=*head;	//使头结点的prior指针和next指针指向自己
	(*head)->prior=*head;
	return 1;
}
//创建双向循环链表
int CreateDList(DLinkList head,int n){
	DListNode *p,*q;
	int i;
	char e;
	q=head;
	for(i=1;i<=n;i++){
		printf("input %d data:",i);
		e=getchar();
		p=(DLinkList)malloc(sizeof(DListNode));
		p->data=e;
		//将新生成的结点插入到双向循环链表
		p->next=q->next;
		q->next=p;
		p->prior=q;
		head->prior=p;	//这里要注意头结点的prior指向新插入的结点
		q=p;		//q始终指向最后一个结点
		getchar();
	}
	return 1;
}
//查找插入的位置，找到返回该结点的指针，否则返回NULL
DListNode *GetElem(DLinkList head,int i){
	DListNode *p;
	int j;
	p=head->next;
	j=1;
	while(p!=head&&j<i){
		p=p->next;
		j++;
	}
	if(p==head||j>i)	//如果要位置不正确，返回NULL
		return NULL;
	return p;
}
//在双向循环链表的第i个位置插入元素e。插入成功返回1，否则返回0
int InsertDList(DLinkList head,int i,char e){
	DListNode *p,*s;
	p=GetElem(head,i);	//查找链表中第i个结点
	if(!p)
		return 0;
	s=(DListNode *)malloc(sizeof(DListNode));
	if(!s)
		return -1;
	s->data=e;
	//将s结点插入到双向循环链表
	s->prior=p->prior;
	p->prior->next=s;
	s->next=p;
	p->prior=s;
	return 1;
}
//输出双向循环链表中的每一个元素
void PrintDList(DLinkList head){
	DListNode *p;
	p=head->next;
	while(p!=head){
		printf("%c ",p->data);
		p=p->next;
	}
	printf("\n");
}
void main_DLinkList(){
	DLinkList h;
	int n;
	int pos;
	char e;
	InitDList(&h);
	printf("输入元素个数：");
	scanf("%d",&n);
	getchar();//接收换行
	CreateDList(h,n);
	printf("链表中的元素：");
	PrintDList(h);
	printf("请输入插入的元素及位置：");
	scanf("%c",&e);
	getchar();
	scanf("%d",&pos);
	InsertDList(h,pos,e);
	printf("插入元素后链表中的元素：");
	PrintDList(h);
	system("pause");
}
//**************************************************
void MergeDLink(DLinkList A,DLinkList B){
	DListNode *p,*q,*r,*qt,*pt;
	p=A->next;
	q=B->next;
	A->prior=A->next=A;
	r=A;
	while(p!=A&&q!=B){
		if(p->data<=q->data){
			pt=p->next;
			p->next=r->next;
			p->prior=r;
			r->next->prior=p;
			r->next=p;
			r=p;
			p=pt;
		}else{
			qt=q->next;
			q->next=r->next;
			q->prior=r;
			r->next->prior=q;
			r->next=q;
			r=q;
			q=qt;
		}
	}
	if(p!=A){
		r->next=p;
		p->prior=r;
	}else if(q!=B){
		r->next=q;
		q->prior=r;
		B->prior->next=A;
		A->prior=B->prior;
	}
	free(B);
}
void main_MergeDLink(){
	DLinkList A,B;
	int n;
	int pos;
	char e;
	InitDList(&A);
	printf("请输入链表A的元素个数：");
	scanf("%d",&n);
	getchar();//接收换行
	CreateDList(A,n);
	printf("链表A中的元素：");
	PrintDList(A);
	InitDList(&B);
	printf("请输入链表B的元素个数：");
	scanf("%d",&n);
	getchar();//接收换行
	CreateDList(B,n);
	printf("链表B中的元素：");
	PrintDList(B);
	MergeDLink(A,B);
	printf("链表A和B合并后的元素：");
	PrintDList(A);	
	system("pause");
}
void main(){
	main_DLinkList();
	main_MergeDLink();
}

