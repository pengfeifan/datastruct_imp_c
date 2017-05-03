#include<stdio.h>
#include<stdlib.h>
#include"LinkList.h"

//����������
void CreateList(LinkList L,DataType a[],int n){
	int i;
	for(i=1;i<=n;i++)
		InsertList(L,i,a[i-1]);
}
//������ʵ��ѡ�����򡣽������Ϊ���Σ�pָ��Ӧ������������֣�qָ��δ�����������
void SelectSort(LinkList L){
	ListNode *p,*q,*t,*s;
	p=L;
	while(p->next->next!=NULL){		//��qָ����б�������
		for(s=p,q=p->next;q->next!=NULL;q=q->next)
			if(q->next->data<s->next->data)
				s=q;			//���qָ��ָ���Ԫ��ֵС��sָ���Ԫ��ֵ����s=q
		if(s!=q){		//���*s�������һ����㣬��sָ��Ľ�����ӵ�pָ����������
			t=s->next;		//�����*t��qָ���������ȡ��
			s->next=t->next;
			t->next=p->next;	//�����*t���뵽pָ���������
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
	printf("����ǰ��\n");
	for(p=L->next;p!=NULL;p=p->next)
		printf("%d ",p->data);
	printf("\n");
	SelectSort(L);
	printf("�����\n");
	for(p=L->next;p!=NULL;p=p->next)
		printf("%d ",p->data);
	printf("\n");
	system("pause");
}
//����Ĳ�������
void InsertSort(LinkList L){
	ListNode *p=L->next;
	ListNode *pre,*q;
	L->next=NULL;	//��ʼʱ������������Ϊ��
	while(p!=NULL){		//p��ָ�������Ľ��
		if(L->next==NULL){	//���*p�ǵ�һ����㣬����뵽L����������������һ������ָ����Ϊ��
			L->next=p;
			p=p->next;
			L->next->next=NULL;
		}else{		//pָ�������Ľ�㣬��Lָ����Ѿ��ź���������в��Ҳ���λ��
			pre=L;
			q=L->next;
			while(q!=NULL&&q->data<p->data){	//��qָ����������Ѱ�Ҳ���λ��
				pre=q;
				q=q->next;
			}
			q=p->next;		//qָ��p����һ����㣬����������ָ��λ��
			p->next=pre->next;	//�����*p���뵽���*pre�ĺ���
			pre->next=p;		//pָ����һ��������Ľ��
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
	printf("����ǰ��\n");
	for(p=L->next;p!=NULL;p=p->next)
		printf("%d ",p->data);
	printf("\n");
	InsertSort(L);
	printf("�����\n");
	for(p=L->next;p!=NULL;p=p->next)
		printf("%d ",p->data);
	printf("\n");
	system("pause");
}
void main(){
	main_Select();
	main_Insert();
}