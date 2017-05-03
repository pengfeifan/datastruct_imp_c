//CycList:循环单链表
#include<stdio.h>
#include<stdlib.h>

typedef int DataType;
typedef struct Node{
	DataType data;
	struct Node *next;
}ListNode,*LinkList;
//创建一个不带头结点的循环单链表
LinkList CreateCycList(int n){
	DataType e;
	LinkList head=NULL;
	ListNode *p,*q;
	int i;
	i=1;
	while(i<=n){
		printf("请输入第%d个元素:",i);
		scanf("%d",&e);
		if(i==1){		//创建第一个结点
			head=(LinkList)malloc(sizeof(ListNode));
			head->data=e;
			head->next=NULL;
			q=head;		//指针q指向链表的最后一个结点
		}else{
			p=(ListNode *)malloc(sizeof(ListNode));
			p->data=e;
			p->next=NULL;
			q->next=p;		//将新结点连接到链表中
			q=p;		//q始终指向最后一个结点
		}
		i++;
	}
	if(q!=NULL)
		q->next=head;		//将最后一个结点的指针指向头指针，使其形成一个循环链表 
	return head;
}
//输出循环链表的每一个元素
void DisplayCycList(LinkList head){
	ListNode *p;
	p=head;
	if(p==NULL){
		printf("该链表是空表");
		return;
	}
	while(p->next!=head){
		printf("%4d",p->data);//如果不是最后一个结点，输出该结点
		p=p->next;
	}
	printf("%4d\n",p->data);//输出最后一个结点
}
//将两个链表head1和head2连接在一起形成一个循环链表
LinkList Link(LinkList head1,LinkList head2){
	ListNode *p,*q;
	p=head1;
	while(p->next!=head1)//指针p指向链表的最后一个结点
		p=p->next;
	q=head2;
	while(q->next!=head2)//指针q指向链表的最后一个结点
		q=q->next;
	p->next=head2;//将第一个链表的尾端连接到第二个链表的第一个结点
	q->next=head1;//将第二个链表的尾端连接到第一个链表的第一个结点
	return head1;
}
void main_Link(){
	LinkList h1,h2;
	int n;
	printf("创建一个循环单链表h1：\n");
	printf("请输入元素个数：\n");
	scanf("%d",&n);
	h1=CreateCycList(n);
	printf("创建一个循环单链表h2：\n");
	printf("请输入元素个数：\n");
	scanf("%d",&n);
	h2=CreateCycList(n);
	printf("输出循环单链表h1\n");
	DisplayCycList(h1);				
	printf("输出循环单链表h2\n");
	DisplayCycList(h2);
	h1=Link(h1,h2);
	printf("输出连接后的循环单链表h1+h2\n");
	DisplayCycList(h1);
	system("pause");
}
//***************************
//在长度为n的循环单链表中，从第k个人开始报数，数到m的人出列
void Josephus(LinkList head,int n,int m,int k){
	ListNode *p,*q;
	int i;
	p=head;
	for(i=1;i<k;i++){		//从第k个人开始报数
		q=p;
		p=q->next;
	}
	while(p->next!=p){
		for(i=1;i<m;i++){		//数到m的人出列
			q=p;
			p=q->next;
		}
		q->next=p->next;	//将p指向的结点删除，即报数为m的人出列
		printf("%4d",p->data);
		free(p);
		p=q->next;		//p指向下一个结点，重新开始报数
	}
	printf("%4d\n",p->data);
}
LinkList CreateCycList_(int n)
{
	LinkList head=NULL;
	ListNode *s,*r;
	int i;
	for(i=1;i<=n;i++)
	{
		s=(ListNode*)malloc(sizeof(ListNode));
		s->data=i;
		s->next=NULL;
		if(head==NULL)
			head=s;
		else
			r->next=s;
		r=s;
	}
	r->next=head;
	return head;
}
void main_Josephus()
{

	LinkList h;
	int n,k,m;
	printf("输入环中人的个数n=");
	scanf("%d",&n);
	printf("输入开始报数的序号k=");
	scanf("%d",&k);
	printf("报数为m的人出列m=");
	scanf("%d",&m);
	h=CreateCycList_(n);
	Josephus(h,n,m,k);
	system("pause");
}
void main(){
	main_Link();
	main_Josephus();
}