//���Ա����ʽ�洢��������
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
//*****************************************************
//ɾ��A�г���B��Ԫ�صĺ���
void DelElem(LinkList A,LinkList B){
	int i,pos;
	DataType e;
	ListNode *p;
	//�ڵ�����B�У�ȡ��ÿ��Ԫ���뵥����A�е�Ԫ�رȽϣ���������ɾ��A��Ԫ�ض�Ӧ�Ľ��
	for(i=0;i<=ListLength(B);i++){
		p=Get(B,i);//ȡ��B�е�ÿ����㣬��ָ�뷵�ظ�p
		if(p){
			pos=LocatePos(A,p->data);//�Ƚ�B�е�Ԫ���Ƿ���A�е�Ԫ�����
			if(pos>0)
				DeleteList(A,pos,&e);//�����ȣ������A��ɾ��
		}
	}
}
void DelElem2(LinkList A,LinkList B){
	ListNode *pre,*p,*r,*q;
	pre=A;
	p=A->next;
	//�ڵ�����B�У�ȡ��ÿ��Ԫ���뵥����A�е�Ԫ�رȽϣ���������ɾ��A��Ԫ�ض�Ӧ�Ľ��
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

	LinkList A,B;					/*����������A��B*/
	ListNode *p;
	InitList(&A);					/*��ʼ��������A*/
	InitList(&B);					/*��ʼ��������B*/
	for(i=1;i<=sizeof(a)/sizeof(a[0]);i++)	/*������a��Ԫ�ز��뵽������A��*/
	{
		if(InsertList(A,i,a[i-1])==0)
		{
			printf("λ�ò��Ϸ�\n");
			return;
		}
	}
	for(i=1;i<=sizeof(b)/sizeof(b[0]);i++)	/*������b��Ԫ�ز��뵥����B��*/
	{
		if(InsertList(B,i,b[i-1])==0)
		{
			printf("λ�ò��Ϸ�\n");
			return;
		}
	}
	printf("������A�е�Ԫ����%d����\n",ListLength(A));
	for(i=1;i<=ListLength(A);i++)	/*���������A�е�ÿ��Ԫ��*/
	{
		p=Get(A,i);					/*���ص�����A�е�ÿ������ָ��*/
		if(p)
			printf("%4d",p->data);	/*���������A�е�ÿ��Ԫ��*/
	}
	printf("\n");
	printf("������B�е�Ԫ����%d����\n",ListLength(B));
	for(i=1;i<=ListLength(B);i++)	
	{
		p=Get(B,i);					/*���ص�����B�е�ÿ��ÿ������ָ��*/
		if(p)
			printf("%4d",p->data);	/*���������B�е�ÿ��Ԫ��*/
	}
	printf("\n");
	DelElem2(A,B);					/*���ڵ�����A�г��ֵ�B��Ԫ��ɾ������A-B*/
	printf("����A�г���B��Ԫ��ɾ����(A-B)������A�е�Ԫ�ػ���%d����\n",ListLength(A));
	for(i=1;i<=ListLength(A);i++)		
	{
		p=Get(A,i);					/*���ص�����A��ÿ������ָ��*/
		if(p)
			printf("%4d",p->data);	/*��ʾ���ɾ����A������Ԫ��*/
	}
	printf("\n");
	system("pause");
}
//**************************************************
//������A��B�е�Ԫ�طǵݼ����У���������A��B�е�Ԫ�غϲ���C�У�C�е�Ԫ���԰��շǵݼ�����
void MergeList(LinkList A,LinkList B,LinkList *C){
	ListNode *pa,*pb,*pc;
	pa=A->next;
	pb=B->next;
	*C=A;//��������A��ͷ�����ΪC��ͷ���
	(*C)->next=NULL;
	pc=*C;
	//���ν�����A��B�н�С��Ԫ�ش�������C��
	while(pa&&pb){
		if(pa->data<=pb->data){
			pc->next=pa;//���A�е�Ԫ��С�ڻ����B�е�Ԫ�أ���A�е�Ԫ�صĽ����ΪC�Ľ��
			pc=pa;
			pa=pa->next;
		}else{
			pc->next=pb;//���A�е�Ԫ�ش���B�е�Ԫ�أ���B�е�Ԫ�صĽ����ΪC�Ľ��
			pc=pb;
			pb=pb->next;
		}
	}
	pc->next=pa?pa:pb;//��ʣ��Ľ�����C��
	free(B);//�ͷ�B��ͷ���
}
void main_MergeList(){
	int i;
	DataType a[]={6,7,9,14,37,45,65,67};
	DataType b[]={3,7,11,34,45,89};

	LinkList A,B,C;					/*����������A��B*/
	ListNode *p;
	InitList(&A);					/*��ʼ��������A*/
	InitList(&B);					/*��ʼ��������B*/
	for(i=1;i<=sizeof(a)/sizeof(a[0]);i++)	/*������a��Ԫ�ز��뵽������A��*/
	{
		if(InsertList(A,i,a[i-1])==0)
		{
			printf("λ�ò��Ϸ�\n");
			return;
		}
	}
	for(i=1;i<=sizeof(b)/sizeof(b[0]);i++)	/*������b��Ԫ�ز��뵥����B��*/
	{
		if(InsertList(B,i,b[i-1])==0)
		{
			printf("λ�ò��Ϸ�\n");
			return;
		}
	}
	printf("������A�е�Ԫ����%d����\n",ListLength(A));
	for(i=1;i<=ListLength(A);i++)	/*���������A�е�ÿ��Ԫ��*/
	{
		p=Get(A,i);					/*���ص�����A�е�ÿ������ָ��*/
		if(p)
			printf("%4d",p->data);	/*���������A�е�ÿ��Ԫ��*/
	}
	printf("\n");
	printf("������B�е�Ԫ����%d����\n",ListLength(B));
	for(i=1;i<=ListLength(B);i++)	
	{
		p=Get(B,i);					/*���ص�����B�е�ÿ��ÿ������ָ��*/
		if(p)
			printf("%4d",p->data);	/*���������B�е�ÿ��Ԫ��*/
	}
	printf("\n");
	MergeList(A,B,&C);					/*��������A��B�е�Ԫ�غϲ���C��*/
	printf("��������A��B��Ԫ�غϲ���C�к�C�е�Ԫ����%d����\n",ListLength(C));
	for(i=1;i<=ListLength(C);i++)		
	{
		p=Get(C,i);					/*���ص�����C��ÿ������ָ��*/
		if(p)
			printf("%4d",p->data);	/*��ʾ���C������Ԫ��*/
	}
	printf("\n");
	system("pause");
}
//**************************************************
//��������
void ReverseList(LinkList H){
	ListNode *p,*q;
	p=H->next;		//pָ������ĵ�һ�����
	H->next=NULL;
	while(p){		//����ͷ�巨��������β��뵽�����ͷ��
		q=p->next;
		//
		p->next=H->next;
		H->next=p;
		p=q;
	}
}
//�������
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
	InitList(&L);							/*��ʼ��������L*/
	for(i=1;i<=sizeof(a)/sizeof(a[0]);i++)	/*������a��Ԫ�ز��뵽������L��*/
	{
		if(InsertList(L,i,a[i-1])==0)
		{
			printf("λ�ò��Ϸ�");
			return;
		}
	}
	printf("����ǰ�����е�Ԫ�أ�\n");
	DisplayList(L);
	ReverseList(L);
	printf("���ú������е�Ԫ�أ�\n");
	DisplayList(L);
	system("pause");
}
void main(){
	main_DelElem();
	main_MergeList();
	main_ReverseList();
}