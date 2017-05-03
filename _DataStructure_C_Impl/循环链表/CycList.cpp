//CycList:ѭ��������
#include<stdio.h>
#include<stdlib.h>

typedef int DataType;
typedef struct Node{
	DataType data;
	struct Node *next;
}ListNode,*LinkList;
//����һ������ͷ����ѭ��������
LinkList CreateCycList(int n){
	DataType e;
	LinkList head=NULL;
	ListNode *p,*q;
	int i;
	i=1;
	while(i<=n){
		printf("�������%d��Ԫ��:",i);
		scanf("%d",&e);
		if(i==1){		//������һ�����
			head=(LinkList)malloc(sizeof(ListNode));
			head->data=e;
			head->next=NULL;
			q=head;		//ָ��qָ����������һ�����
		}else{
			p=(ListNode *)malloc(sizeof(ListNode));
			p->data=e;
			p->next=NULL;
			q->next=p;		//���½�����ӵ�������
			q=p;		//qʼ��ָ�����һ�����
		}
		i++;
	}
	if(q!=NULL)
		q->next=head;		//�����һ������ָ��ָ��ͷָ�룬ʹ���γ�һ��ѭ������ 
	return head;
}
//���ѭ�������ÿһ��Ԫ��
void DisplayCycList(LinkList head){
	ListNode *p;
	p=head;
	if(p==NULL){
		printf("�������ǿձ�");
		return;
	}
	while(p->next!=head){
		printf("%4d",p->data);//����������һ����㣬����ý��
		p=p->next;
	}
	printf("%4d\n",p->data);//������һ�����
}
//����������head1��head2������һ���γ�һ��ѭ������
LinkList Link(LinkList head1,LinkList head2){
	ListNode *p,*q;
	p=head1;
	while(p->next!=head1)//ָ��pָ����������һ�����
		p=p->next;
	q=head2;
	while(q->next!=head2)//ָ��qָ����������һ�����
		q=q->next;
	p->next=head2;//����һ�������β�����ӵ��ڶ�������ĵ�һ�����
	q->next=head1;//���ڶ��������β�����ӵ���һ������ĵ�һ�����
	return head1;
}
void main_Link(){
	LinkList h1,h2;
	int n;
	printf("����һ��ѭ��������h1��\n");
	printf("������Ԫ�ظ�����\n");
	scanf("%d",&n);
	h1=CreateCycList(n);
	printf("����һ��ѭ��������h2��\n");
	printf("������Ԫ�ظ�����\n");
	scanf("%d",&n);
	h2=CreateCycList(n);
	printf("���ѭ��������h1\n");
	DisplayCycList(h1);				
	printf("���ѭ��������h2\n");
	DisplayCycList(h2);
	h1=Link(h1,h2);
	printf("������Ӻ��ѭ��������h1+h2\n");
	DisplayCycList(h1);
	system("pause");
}
//***************************
//�ڳ���Ϊn��ѭ���������У��ӵ�k���˿�ʼ����������m���˳���
void Josephus(LinkList head,int n,int m,int k){
	ListNode *p,*q;
	int i;
	p=head;
	for(i=1;i<k;i++){		//�ӵ�k���˿�ʼ����
		q=p;
		p=q->next;
	}
	while(p->next!=p){
		for(i=1;i<m;i++){		//����m���˳���
			q=p;
			p=q->next;
		}
		q->next=p->next;	//��pָ��Ľ��ɾ����������Ϊm���˳���
		printf("%4d",p->data);
		free(p);
		p=q->next;		//pָ����һ����㣬���¿�ʼ����
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
	printf("���뻷���˵ĸ���n=");
	scanf("%d",&n);
	printf("���뿪ʼ���������k=");
	scanf("%d",&k);
	printf("����Ϊm���˳���m=");
	scanf("%d",&m);
	h=CreateCycList_(n);
	Josephus(h,n,m,k);
	system("pause");
}
void main(){
	main_Link();
	main_Josephus();
}