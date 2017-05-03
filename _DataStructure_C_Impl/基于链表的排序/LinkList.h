//������
#pragma once
#include<stdio.h>
#include<stdlib.h>
typedef int DataType;

typedef struct Node
{
	DataType data;	//������
	struct Node *next;	//ָ����
}ListNode,*LinkList;

//���������ʼ��Ϊ�ա���̬����һ��ͷ��㣬����ͷ����ָ������Ϊ��
void InitList(LinkList *head){
	if((*head=(LinkList)malloc(sizeof(ListNode)))==NULL)
		exit(-1);
	(*head)->next=NULL;
}
//�жϵ������Ƿ�Ϊ�գ�����ͨ���ж�ͷ����ָ�����Ƿ�Ϊ��
int ListEmpty(LinkList head){
	if(head->next==NULL)
		return 1;
	else
		return 0;
}
//���ҵ������е�i����㡣���ҳɹ����ظý���ָ���ʾ�ɹ������򷵻�NULL��ʾʧ��
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
//�������Ա���Ԫ��ֵΪe��Ԫ�أ����ҳɹ�����ӦԪ�صĽ��ָ�뷵�أ����򷵻�NULL��ʾʧ��
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
//�������Ա���Ԫ��ֵΪe��Ԫ�أ����ҳɹ�����ӦԪ�ص���ŷ��أ����򷵻�0��ʾʧ��
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
//�ڵ������е�i��λ�ò���һ����㣬����Ԫ��ֵΪe������ɹ�����1��ʧ�ܷ���
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
//ɾ���������еĵ�i��λ�õĽ�㡣ɾ���ɹ�����1��ʧ�ܷ���0
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