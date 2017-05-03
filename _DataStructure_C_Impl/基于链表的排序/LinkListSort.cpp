#include<stdio.h>
#include<stdlib.h>
#include"LinkList.h"

//创建单链表
void CreateList(LinkList L,DataType a[],int n){
	int i;
	for(i=1;i<=n;i++)
		InsertList(L,i,a[i-1]);
}
//用链表实现选择排序。将链表分为两段，p指向应经排序的链表部分，q指向未排序的链表部分
void SelectSort(LinkList L){
	ListNode *p,*q,*t,*s;
	p=L;
	while(p->next->next!=NULL){		//用q指针进行遍历链表
		for(s=p,q=p->next;q->next!=NULL;q=q->next)
			if(q->next->data<s->next->data)
				s=q;			//如果q指针指向的元素值小于s指向的元素值，则s=q
		if(s!=q){		//如果*s不是最后一个结点，则将s指向的结点链接到p指向的链表后面
			t=s->next;		//将结点*t从q指向的链表中取出
			s->next=t->next;
			t->next=p->next;	//将结点*t插入到p指向的链表中
			p->next=t;
		}
		p=p->next;
	}
}
void main_Select(){
	LinkList L,p;
	int n=8;
	DataType a[]={45,67,21,98,12,39,81,53};
	InitList(&L);
	CreateList(L,a,n);
	printf("排序前：\n");
	for(p=L->next;p!=NULL;p=p->next)
		printf("%d ",p->data);
	printf("\n");
	SelectSort(L);
	printf("排序后：\n");
	for(p=L->next;p!=NULL;p=p->next)
		printf("%d ",p->data);
	printf("\n");
	system("pause");
}
//链表的插入排序
void InsertSort(LinkList L){
	ListNode *p=L->next;
	ListNode *pre,*q;
	L->next=NULL;	//初始时，已排序链表为空
	while(p!=NULL){		//p是指向待排序的结点
		if(L->next==NULL){	//如果*p是第一个结点，则插入到L，并令已排序的最后一个结点的指针域为空
			L->next=p;
			p=p->next;
			L->next->next=NULL;
		}else{		//p指向待排序的结点，在L指向的已经排好序的链表中查找插入位置
			pre=L;
			q=L->next;
			while(q!=NULL&&q->data<p->data){	//在q指向的有序表中寻找插入位置
				pre=q;
				q=q->next;
			}
			q=p->next;		//q指向p的下一个结点，保存待排序的指针位置
			p->next=pre->next;	//将结点*p插入到结点*pre的后面
			pre->next=p;		//p指向下一个待排序的结点
			p=q;
		}
	}
}
void main_Insert(){
	LinkList L,p;
	int n=8;
	DataType a[]={87,34,22,93,102,56,39,21};
	InitList(&L);
	CreateList(L,a,n);
	printf("排序前：\n");
	for(p=L->next;p!=NULL;p=p->next)
		printf("%d ",p->data);
	printf("\n");
	InsertSort(L);
	printf("排序后：\n");
	for(p=L->next;p!=NULL;p=p->next)
		printf("%d ",p->data);
	printf("\n");
	system("pause");
}
void main(){
	main_Select();
	main_Insert();
}