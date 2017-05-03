//单链表
#pragma once
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