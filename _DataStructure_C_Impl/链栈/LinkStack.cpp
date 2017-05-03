//_DataStructure_C_Impl:��ջ
#include<stdio.h>
#include<stdlib.h>

typedef char DataType;
typedef struct node{
	DataType data;
	struct node *next;
}LStackNode,*LinkStack;
//����ջ��ʼ��Ϊ�ա���̬����ͷ��㣬����ͷ����ָ������Ϊ��
void InitStack(LinkStack *top){
	if((*top=(LinkStack)malloc(sizeof(LStackNode)))==NULL)		//Ϊͷ������һ���洢�ռ�
		exit(-1);
	(*top)->next=NULL;		//����ջ��ͷ���ָ������Ϊ��
}
//�ж���ջ�Ƿ�Ϊ�գ�����ͨ���ж�ͷ����ָ�����Ƿ�Ϊ��
int StackEmpty(LinkStack top){
	if(top->next==NULL)		//����ջΪ��ʱ������1�����򷵻�0
		return 1;
	else 
		return 0;
}
//��ջ��������Ҫ������ĵ�һ�����ǰ����һ���½�㣬��ջ�ɹ�����1
int PushStack(LinkStack top,DataType e){
	LStackNode *p;	//ָ��pָ�������ɵĽ��
	if((p=(LStackNode *)malloc(sizeof(LStackNode)))==NULL){
		printf("�ڴ����ʧ��\n");
		exit(-1);
	}
	p->data=e;
	p->next=top->next;	//ָ��pָ���ͷ���
	top->next=p;
	return 1;
}
//ɾ���������еĵ�i��λ�õĽ�㡣ɾ���ɹ�����1��ʧ�ܷ���0
int PopStack(LinkStack top,DataType *e){
	LStackNode *p;
	p=top->next;
	if(!p){		//�ж���ջ�Ƿ�Ϊ��
		printf("ջ�ѿ�\n");
		return 0;
	}
	top->next=p->next;	//��ջ�����������Ͽ�������ջ
	*e=p->data;		//����ջԪ�ظ�ֵ��e
	free(p);		//�ͷ�pָ��Ľ��
	return 1;
}
//ȡջ��Ԫ�ز���
int GetTop(LinkStack top,DataType *e){
	LStackNode *p;
	p=top->next;
	if(!p){		//�ж���ջ�Ƿ�Ϊ��
		printf("ջ�ѿ�\n");
		return 0;
	}
	*e=p->data;	//��ջ��Ԫ�ظ�ֵ��e
	return 1;
}
//�������
int StackLength(LinkStack top){
	LStackNode *p;
	int count=0;
	p=top;
	while(p->next!=NULL){
		p=p->next;
		count++;
	}
	return count;
}
//������ջ����
void DestroyStack(LinkStack top){
	LStackNode *p,*q;
	p=top;
	while(!p){
		q=p;
		p=p->next;
		free(q);
	}
}
void main_LinkStack(){
	LinkStack S;
	DataType ch[50],e,*p;
	InitStack(&S);
	printf("�������ջ���ַ���\n");
	gets(ch);
	p=&ch[0];
	while(*p){
		PushStack(S,*p);
		p++;
	}
	printf("��ǰջ����Ԫ���ǣ�");  
	if(GetTop(S,&e)==0){
		printf("ջ�ѿգ�\n");
		return ;
	}else{
		printf("%4c\n",e);
	}
	printf("��ǰջ�е�Ԫ�ظ����ǣ�%d\n",StackLength(S));
	printf("Ԫ�س�ջ�������ǣ�");
	while(!StackEmpty(S)){
		PopStack(S,&e);
		printf("%4c",e);
	}
	printf("\n");
	system("pause");
}
//********************************
int Match(DataType e,DataType ch){
	if(e=='('&&ch==')')
		return 1;
	else if(e=='['&&ch==']')
		return 1;
	else if(e=='{'&&ch=='}')
		return 1;
	else
		return 0;
}
void main_Match(){
	LinkStack S;
	char *p;
	DataType e;
	DataType ch[100];
	InitStack(&S);
	printf("����������ŵı��ʽ('{}','[]','()').\n");
	gets(ch);
	p=ch;
	while(*p){
		switch(*p){
		case '(':
		case '[':
		case '{':
			PushStack(S,*p++);
			break;
		case ')':
		case ']':
		case '}':
			if(StackEmpty(S)){
				printf("ȱ��������.\n");
				return;
			}else{
				GetTop(S,&e);
				if(Match(e,*p))
					PopStack(S,&e);
				else{
					printf("�������Ų����.\n");
					return;
				}
			}
		default:
			p++;
		}
	}
	if(StackEmpty(S))
		printf("����ƥ��.\n");
	else
		printf("ȱ��������.\n");
	system("pause");
}
//===========
void main(){
	main_LinkStack();
	main_Match();
}