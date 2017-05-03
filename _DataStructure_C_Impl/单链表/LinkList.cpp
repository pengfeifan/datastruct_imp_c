//线性表的链式存储：单链表
#include<stdio.h>
#include<stdlib.h>
typedef int DataType;

typedef struct Node
{
	DataType data;	//数据域
	struct Node *next;	//指针域
}ListNode,*LinkList;

//将单链表初始化为空。动态生成一个头结点，并将头结点的指针域置为空
void InitList(LinkList *head){
	if((*head=(LinkList)malloc(sizeof(ListNode)))==NULL)
		exit(-1);
	(*head)->next=NULL;
}
//判断单链表是否为空，就是通过判断头结点的指针域是否为空
int ListEmpty(LinkList head){
	if(head->next==NULL)
		return 1;
	else
		return 0;
}
//查找单链表中第i个结点。查找成功返回该结点的指针表示成功；否则返回NULL表示失败
ListNode *Get(LinkList head,int i){
	ListNode *p;
	int j;
	if(ListEmpty(head))
		return NULL;
	if(i<1)
		return NULL;
	j=0;
	p=head;
	while(p->next!=NULL&&j<i){
		p=p->next;
		j++;
	}
	if(j==i)
		return p;
	else
		return NULL;
}
//查找线性表中元素值为e的元素，查找成功将对应元素的结点指针返回，否则返回NULL表示失败
ListNode *LocateElem(LinkList head,DataType e){
	ListNode *p;
	p=head->next;
	while(p){
		if(p->data!=e)
			p=p->next;
		else
			break;
	}
	return p;
}
//查找线性表中元素值为e的元素，查找成功将对应元素的序号返回，否则返回0表示失败
int LocatePos(LinkList head,DataType e){
	ListNode *p;
	int i;
	if(ListEmpty(head))
		return 0;
	p=head->next;
	i=1;
	while(p){
		if(p->data==e)
			return i;
		else{
			p=p->next;
			i++;
		}
	}
	if(!p)
		return 0;
}
//在单链表中第i个位置插入一个结点，结点的元素值为e。插入成功返回1，失败返回
int InsertList(LinkList head,int i,DataType e){
	ListNode *p,*pre;
	int j;
	pre=head;
	j=0;
	while(pre->next!=NULL&&j<i-1){
		pre=pre->next;
		j++;
	}
	if(!pre){
		printf("wrong place\n");
		return 0;
	}
	if((p=(LinkList)malloc(sizeof(ListNode)))==NULL)
		exit(-1);
	p->data=e;
	p->next=pre->next;
	pre->next=p;
	return 1;
}
//删除单链表中的第i个位置的结点。删除成功返回1，失败返回0
int DeleteList(LinkList head,int i,DataType *e){
	ListNode *pre,*p;
	int j;
	pre=head;
	j=0;
	while(p->next!=NULL&&pre->next->next!=NULL&&j<i-1){
		pre=pre->next;
		j++;
	}
	if(j!=i-1){
		printf("delete wrong place\n");
		return 0;
	}
	p=pre->next;
	pre->next=p->next;
	free(p);
	return 1;
}
int ListLength(LinkList head){
	ListNode *p;
	int count=0;
	p=head;
	while(p->next!=NULL){
		p=p->next;
		count++;
	}
	return count;
}
void DestroyList(LinkList head){
	ListNode *p,*q;
	p=head;
	while(p!=NULL){
		q=p;
		p=p->next;
		free(q);
	}
}
//*****************************************************
//删除A中出现B的元素的函数
void DelElem(LinkList A,LinkList B){
	int i,pos;
	DataType e;
	ListNode *p;
	//在单链表B中，取出每个元素与单链表A中的元素比较，如果相等则删除A中元素对应的结点
	for(i=0;i<=ListLength(B);i++){
		p=Get(B,i);//取出B中的每个结点，将指针返回给p
		if(p){
			pos=LocatePos(A,p->data);//比较B中的元素是否与A中的元素相等
			if(pos>0)
				DeleteList(A,pos,&e);//如果相等，将其从A中删除
		}
	}
}
void DelElem2(LinkList A,LinkList B){
	ListNode *pre,*p,*r,*q;
	pre=A;
	p=A->next;
	//在单链表B中，取出每个元素与单链表A中的元素比较，如果相等则删除A中元素对应的结点
	while(p!=NULL){
		q=B->next;
		while(q!=NULL&&q->data!=p->data)
			q=q->next;
		if(q!=NULL){
			r=p;
			pre->next=p->next;
			p=r->next;
			free(r);
		}else{
			pre=p;
			p=p->next;
		}
	}
}
void main_DelElem(){
	int i;
	DataType a[]={2,3,6,7,9,14,56,45,65,67};
	DataType b[]={3,4,7,11,34,54,45,67};

	LinkList A,B;					/*声明单链表A和B*/
	ListNode *p;
	InitList(&A);					/*初始化单链表A*/
	InitList(&B);					/*初始化单链表B*/
	for(i=1;i<=sizeof(a)/sizeof(a[0]);i++)	/*将数组a中元素插入到单链表A中*/
	{
		if(InsertList(A,i,a[i-1])==0)
		{
			printf("位置不合法\n");
			return;
		}
	}
	for(i=1;i<=sizeof(b)/sizeof(b[0]);i++)	/*将数组b中元素插入单链表B中*/
	{
		if(InsertList(B,i,b[i-1])==0)
		{
			printf("位置不合法\n");
			return;
		}
	}
	printf("单链表A中的元素有%d个：\n",ListLength(A));
	for(i=1;i<=ListLength(A);i++)	/*输出单链表A中的每个元素*/
	{
		p=Get(A,i);					/*返回单链表A中的每个结点的指针*/
		if(p)
			printf("%4d",p->data);	/*输出单链表A中的每个元素*/
	}
	printf("\n");
	printf("单链表B中的元素有%d个：\n",ListLength(B));
	for(i=1;i<=ListLength(B);i++)	
	{
		p=Get(B,i);					/*返回单链表B中的每个每个结点的指针*/
		if(p)
			printf("%4d",p->data);	/*输出单链表B中的每个元素*/
	}
	printf("\n");
	DelElem2(A,B);					/*将在单链表A中出现的B的元素删除，即A-B*/
	printf("将在A中出现B的元素删除后(A-B)，现在A中的元素还有%d个：\n",ListLength(A));
	for(i=1;i<=ListLength(A);i++)		
	{
		p=Get(A,i);					/*返回单链表A中每个结点的指针*/
		if(p)
			printf("%4d",p->data);	/*显示输出删除后A中所有元素*/
	}
	printf("\n");
	system("pause");
}
//**************************************************
//单链表A和B中的元素非递减排列，将单链表A和B中的元素合并到C中，C中的元素仍按照非递减排列
void MergeList(LinkList A,LinkList B,LinkList *C){
	ListNode *pa,*pb,*pc;
	pa=A->next;
	pb=B->next;
	*C=A;//将单链表A的头结点作为C的头结点
	(*C)->next=NULL;
	pc=*C;
	//依次将链表A和B中较小的元素存入链表C中
	while(pa&&pb){
		if(pa->data<=pb->data){
			pc->next=pa;//如果A中的元素小于或等于B中的元素，将A中的元素的结点作为C的结点
			pc=pa;
			pa=pa->next;
		}else{
			pc->next=pb;//如果A中的元素大于B中的元素，将B中的元素的结点作为C的结点
			pc=pb;
			pb=pb->next;
		}
	}
	pc->next=pa?pa:pb;//将剩余的结点插入C中
	free(B);//释放B的头结点
}
void main_MergeList(){
	int i;
	DataType a[]={6,7,9,14,37,45,65,67};
	DataType b[]={3,7,11,34,45,89};

	LinkList A,B,C;					/*声明单链表A和B*/
	ListNode *p;
	InitList(&A);					/*初始化单链表A*/
	InitList(&B);					/*初始化单链表B*/
	for(i=1;i<=sizeof(a)/sizeof(a[0]);i++)	/*将数组a中元素插入到单链表A中*/
	{
		if(InsertList(A,i,a[i-1])==0)
		{
			printf("位置不合法\n");
			return;
		}
	}
	for(i=1;i<=sizeof(b)/sizeof(b[0]);i++)	/*将数组b中元素插入单链表B中*/
	{
		if(InsertList(B,i,b[i-1])==0)
		{
			printf("位置不合法\n");
			return;
		}
	}
	printf("单链表A中的元素有%d个：\n",ListLength(A));
	for(i=1;i<=ListLength(A);i++)	/*输出单链表A中的每个元素*/
	{
		p=Get(A,i);					/*返回单链表A中的每个结点的指针*/
		if(p)
			printf("%4d",p->data);	/*输出单链表A中的每个元素*/
	}
	printf("\n");
	printf("单链表B中的元素有%d个：\n",ListLength(B));
	for(i=1;i<=ListLength(B);i++)	
	{
		p=Get(B,i);					/*返回单链表B中的每个每个结点的指针*/
		if(p)
			printf("%4d",p->data);	/*输出单链表B中的每个元素*/
	}
	printf("\n");
	MergeList(A,B,&C);					/*将单链表A和B中的元素合并到C中*/
	printf("将单链表A和B的元素合并到C中后，C中的元素有%d个：\n",ListLength(C));
	for(i=1;i<=ListLength(C);i++)		
	{
		p=Get(C,i);					/*返回单链表C中每个结点的指针*/
		if(p)
			printf("%4d",p->data);	/*显示输出C中所有元素*/
	}
	printf("\n");
	system("pause");
}
//**************************************************
//逆置链表
void ReverseList(LinkList H){
	ListNode *p,*q;
	p=H->next;		//p指向链表的第一个结点
	H->next=NULL;
	while(p){		//利用头插法将结点依次插入到链表的头部
		q=p->next;
		//
		p->next=H->next;
		H->next=p;
		p=q;
	}
}
//输出链表
void DisplayList(LinkList L){
	int i;
	ListNode *p;
	for(i=0;i<=ListLength(L);i++){
		p=Get(L,i);
		if(p)
			printf("%4d",p->data);
	}
	printf("\n");
}
void main_ReverseList(){
	int a[]={1,2,3,4,5,6,7,8,9,10};
	int i;
	LinkList L;
	InitList(&L);							/*初始化单链表L*/
	for(i=1;i<=sizeof(a)/sizeof(a[0]);i++)	/*将数组a中元素插入到单链表L中*/
	{
		if(InsertList(L,i,a[i-1])==0)
		{
			printf("位置不合法");
			return;
		}
	}
	printf("逆置前链表中的元素：\n");
	DisplayList(L);
	ReverseList(L);
	printf("逆置后链表中的元素：\n");
	DisplayList(L);
	system("pause");
}
void main(){
	main_DelElem();
	main_MergeList();
	main_ReverseList();
}