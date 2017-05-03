//һԪ����ʽ
#include<stdio.h>
#include<stdlib.h>

typedef struct ployn{
	float coef;	//���һԪ����ʽ��ϵ��
	int expn;	//���һԪ����ʽ��ָ��
	struct ployn *next;
}PolyNode,*PolyNomial;
//����һԪ����ʽ
PolyNomial CreatePolyn(){
	PolyNode *p,*q,*s;
	PolyNode *head=NULL;
	int expn2;
	float coef2;
	head=(PolyNomial)malloc(sizeof(PolyNode));
	if(!head)
		return NULL;
	head->coef=0;
	head->expn=0;
	head->next=NULL;
	do{
		printf("����ϵ��coef");
		scanf("%f",&coef2);
		printf("����ָ��exp(����0 0 ����)");
		scanf("%d",&expn2);
		if((long)coef2==0&&expn2==0)
			break;
		s=(PolyNode *)malloc(sizeof(PolyNode));
		if(!s)
			return NULL;
		s->expn=expn2;
		s->coef=coef2;
		q=head->next;
		p=head;
		//����һ������ʽ��ʹ����ʽ����ָ���ݼ�����
		while(q&&expn2<q->expn){
			p=q;
			q=q->next;
		}
		if(q==NULL||expn2>q->expn){
			p->next=s;
			s->next=q;
		}else{
			q->coef+=coef2;		//���ָ����ͬ���ϲ�ͬ����
		}
	}while(1);
	return head;
}
//��������
PolyNode *Reverse(PolyNomial head){
	PolyNode *q,*r,*p=NULL;
	q=head->next;
	while(q){
		r=q->next;
		q->next=p;
		p=q;
		q=r;
	}
	head->next=p;
	return head;
}
//һԪ����ʽ�����
PolyNode *MultiplyPolyn(PolyNomial A,PolyNomial B){
	PolyNode *pa,*pb,*pc,*u,*head;
	int k,maxExp;
	float coef;
	head=(PolyNomial)malloc(sizeof(PolyNode));
	if(!head)
		return NULL;
	head->coef=0.0;
	head->expn=0;
	head->next=NULL;
	if(A->next!=NULL&&B->next!=NULL)	//�����������ʽ�˻�����ָ����
		maxExp=A->next->expn+B->next->expn;
	else
		return head;
	pc=head;
	B=Reverse(B);	//������ʽB����
	for(k=maxExp;k>=0;k--){
		pa=A->next;
		while(pa!=NULL&&pa->expn>k)
			pa=pa->next;
		pb=B->next;
		while(pb!=NULL&&pa!=NULL&&(pa->expn+pb->expn)<k)
			pb=pb->next;
		coef=0.0;
		while(pa!=NULL&&pb!=NULL){
			if(pa->expn+pb->expn==k){
				coef+=pa->coef*pb->coef;
				pa=pa->next;
				pb=pb->next;
			}else if(pa->expn+pb->expn>k)
				pa=pa->next;
			else
				pb=pb->next;
		}
		if(coef!=0.0){
			u=(PolyNode *)malloc(sizeof(PolyNode));
			u->coef=coef;
			u->expn=k;
			u->next=pc->next;
			pc->next=u;
			pc=u;
		}
	}
	B=Reverse(B);
	return head;
}
//���һԪ����ʽ
void OutPut(PolyNomial head){
	PolyNode *p=head->next;
	while(p){
		printf("%1.1f",p->coef);
		if(p->expn)
			printf("*x^%d",p->expn);
		if(p->next&&p->next->coef>0)
			printf("+");
		p=p->next;
	}
}
void main(){
	PolyNomial A,B,C;
	A=CreatePolyn();
	printf("A(x)=");
	OutPut(A);
	printf("\n");
	B=CreatePolyn();
	printf("B(x)=");
	OutPut(B);
	printf("\n");
	C=MultiplyPolyn(A,B);
	printf("C(x)=A(x)*B(x)=");
	OutPut(C);
	printf("\n"); 
	system("pause");
}