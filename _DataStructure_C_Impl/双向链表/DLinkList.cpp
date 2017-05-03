//˫������
#include<stdio.h>
#include<stdlib.h>

typedef char DataType;
typedef struct Node{
	DataType data;
	struct Node *prior;
	struct Node *next;
}DListNode,*DLinkList;
//��ʼ��˫��ѭ������
int InitDList(DLinkList *head){  //head �Ƕ���ָ��
	*head=(DLinkList)malloc(sizeof(DListNode));
	if(!head)
		return -1;
	(*head)->next=*head;	//ʹͷ����priorָ���nextָ��ָ���Լ�
	(*head)->prior=*head;
	return 1;
}
//����˫��ѭ������
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
		//�������ɵĽ����뵽˫��ѭ������
		p->next=q->next;
		q->next=p;
		p->prior=q;
		head->prior=p;	//����Ҫע��ͷ����priorָ���²���Ľ��
		q=p;		//qʼ��ָ�����һ�����
		getchar();
	}
	return 1;
}
//���Ҳ����λ�ã��ҵ����ظý���ָ�룬���򷵻�NULL
DListNode *GetElem(DLinkList head,int i){
	DListNode *p;
	int j;
	p=head->next;
	j=1;
	while(p!=head&&j<i){
		p=p->next;
		j++;
	}
	if(p==head||j>i)	//���Ҫλ�ò���ȷ������NULL
		return NULL;
	return p;
}
//��˫��ѭ������ĵ�i��λ�ò���Ԫ��e������ɹ�����1�����򷵻�0
int InsertDList(DLinkList head,int i,char e){
	DListNode *p,*s;
	p=GetElem(head,i);	//���������е�i�����
	if(!p)
		return 0;
	s=(DListNode *)malloc(sizeof(DListNode));
	if(!s)
		return -1;
	s->data=e;
	//��s�����뵽˫��ѭ������
	s->prior=p->prior;
	p->prior->next=s;
	s->next=p;
	p->prior=s;
	return 1;
}
//���˫��ѭ�������е�ÿһ��Ԫ��
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
	printf("����Ԫ�ظ�����");
	scanf("%d",&n);
	getchar();//���ջ���
	CreateDList(h,n);
	printf("�����е�Ԫ�أ�");
	PrintDList(h);
	printf("����������Ԫ�ؼ�λ�ã�");
	scanf("%c",&e);
	getchar();
	scanf("%d",&pos);
	InsertDList(h,pos,e);
	printf("����Ԫ�غ������е�Ԫ�أ�");
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
	printf("����������A��Ԫ�ظ�����");
	scanf("%d",&n);
	getchar();//���ջ���
	CreateDList(A,n);
	printf("����A�е�Ԫ�أ�");
	PrintDList(A);
	InitDList(&B);
	printf("����������B��Ԫ�ظ�����");
	scanf("%d",&n);
	getchar();//���ջ���
	CreateDList(B,n);
	printf("����B�е�Ԫ�أ�");
	PrintDList(B);
	MergeDLink(A,B);
	printf("����A��B�ϲ����Ԫ�أ�");
	PrintDList(A);	
	system("pause");
}
void main(){
	main_DLinkList();
	main_MergeDLink();
}

