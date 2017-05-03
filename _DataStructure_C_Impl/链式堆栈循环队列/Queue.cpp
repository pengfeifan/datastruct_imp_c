//_DataStructure_C_Impl:
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char DataType;

typedef struct snode{	//��ʽ��ջ������Ͷ���
	DataType data;
	struct snode *next;
}LSNode;
typedef struct QNode{	//ֻ�ж�βָ�����ʽѭ���������Ͷ���
	DataType data;
	struct QNode *next;
}LQNode,*LinkQueue;
//��ͷ������ʽ��ջ��ʼ��
void InitStack(LSNode **head){
	if((*head=(LSNode *)malloc(sizeof(LSNode)))==NULL){
		printf("�����㲻�ɹ�");
		exit(-1);
	}else{
		(*head)->next=NULL;
	}
}
//�жϴ�ͷ�����ʽ��ջ�Ƿ�Ϊ�ա������ջΪ�գ�����1�����򷵻�0
int StackEmpty(LSNode *head){
	if(head->next==NULL)
		return 1;
	else 
		return 0;
}
//��ʽ��ջ��ջ����ջ�ɹ�����1�������˳�
int PushStack(LSNode *head,DataType e){
	LSNode *s;
	if((s=(LSNode *)malloc(sizeof(LSNode)))==NULL)	//Ϊ������ռ䣬ʧ���˳����򲢷���-1
		exit(-1);
	else{
		s->data=e;	//��Ԫ��ֵ��ֵ������������
		s->next=head->next;	//�������뵽ջ��
		head->next=s;
		return 1;
	}
}
//��ʽ��ջ��ջ����Ҫ�ж϶�ջ�Ƿ�Ϊ�ա���ջ�ɹ�����1�����򷵻�0
int PopStack(LSNode *head,DataType *e){
	LSNode *s=(LSNode *)malloc(sizeof(LSNode));
	if(!s) exit(-1);
	s=head->next;	//ָ��sָ��ջ�����
	if(StackEmpty(head))	//�ж϶�ջ�Ƿ�Ϊ��
		return 0;
	else{
		head->next=s->next;	//ͷ����ָ��ָ��ڶ������λ��
		*e=s->data;	//Ҫ��ջ�Ľ��Ԫ�ظ�ֵ��e
		free(s);	//�ͷ�Ҫ��ջ�Ľ��ռ�
		return 1;
	}
}
//����ͷ������ʽѭ�����г�ʼ��Ϊ�ն��У���Ҫ��ͷ����ָ��ָ��ͷ���
void InitQueue(LinkQueue *rear){
	if((*rear=(LQNode*)malloc(sizeof(LQNode)))==NULL)
		exit(-1);		//���������ռ�ʧ���˳�
	else
		(*rear)->next=*rear;	//��βָ��ָ��ͷ���
}
//�ж���ʽ�����Ƿ�Ϊ�գ�����Ϊ�շ���1�����򷵻�0
int QueueEmpty(LinkQueue rear){
	if(rear->next==rear)
		return 1;
	else
		return 0;
}
//��Ԫ��e���뵽��ʽ�����У�����ɹ�����1
int EnterQueue(LinkQueue *rear,DataType e){
	LQNode *s;
	s=(LQNode *)malloc(sizeof(LQNode));	//Ϊ��Ҫ��ӵ�Ԫ������һ�����Ŀռ�
	if(!s)
		exit(-1);
	s->data=e;		//��Ԫ��ֵ��ֵ������������
	s->next=(*rear)->next;		//���½�������ʽ����
	(*rear)->next=s;
	*rear=s;	//�޸Ķ�βָ��
	return 1;
}
//ɾ����ʽ�����еĶ�ͷԪ�أ�������Ԫ�ظ�ֵ��e��ɾ���ɹ�����1�����򷵻�0
int DeleteQueue(LinkQueue *rear,DataType *e){
	LQNode *f,*p;
	if(*rear==(*rear)->next)		//��ɾ����ͷԪ�ؼ�������֮ǰ���ж���ʽ�����Ƿ�Ϊ��
		return 0;
	else{
		f=(*rear)->next;	//ʹָ��fָ��ͷ���
		p=f->next;		//ʹָ��pָ��Ҫɾ���Ľ��
		if(p==*rear){		//���������ֻ��һ���������
			*rear=(*rear)->next;		//ʹָ��rearָ��ͷ���
			(*rear)->next=*rear;
		}else{
			f->next=p->next;	//ʹͷ���ָ��Ҫ�����е���һ�����
		}
		*e=p->data;	//�Ѷ�ͷԪ��ֵ��ֵ��e
		free(p);	//�ͷ�ָ��pָ��Ľ��
		return 1;
	}
}
void main(){
	LinkQueue LQueue1,LQueue2;		/*������ʽѭ������*/
	LSNode *LStack1,*LStack2;		/*������ʽ��ջ*/
	char str1[]="XYZAZYX";			/*�����ַ�����1*/
	char str2[]="XYZBZYX";			/*�����ַ�����2*/
	char q1,s1,q2,s2;
	int i;
	InitQueue(&LQueue1);				/*��ʼ����ʽѭ������1*/
	InitQueue(&LQueue2);				/*��ʼ����ʽѭ������2*/
	InitStack(&LStack1);				/*��ʼ����ʽ��ջ1*/
	InitStack(&LStack2);				/*��ʼ����ʽ��ջ2*/
	for(i=0;i<strlen(str1);i++)
	{
		EnterQueue(&LQueue1,str1[i]);	/*���ΰ��ַ�����1���*/
		EnterQueue(&LQueue2,str2[i]);	/*���ΰ��ַ�����2���*/
		PushStack(LStack1,str1[i]);		/*���ΰ��ַ�����1��ջ*/
		PushStack(LStack2,str2[i]);		/*���ΰ��ַ�����2��ջ*/

	}
	printf("�ַ�����1��\n");
	printf("��������  ��ջ����\n");
	while(!StackEmpty(LStack1))			/*�ж϶�ջ1�Ƿ�Ϊ��*/
	{
		DeleteQueue(&LQueue1,&q1);		/*�ַ��������γ��ӣ����ѳ���Ԫ�ظ�ֵ��q*/
		PopStack(LStack1,&s1);			/*�ַ����г�ջ�����ѳ�ջԪ�ظ�ֵ��s*/	
		printf("%5c",q1);				/*����ַ�����1*/
		printf("%10c\n",s1);
		if(q1!=s1)						/*�ж��ַ�����1�Ƿ��ǻ���*/
		{
			printf("�ַ�����1���ǻ��ģ�");
			return;
		}
	}
	printf("�ַ�����1�ǻ��ģ�\n");
	printf("�ַ�����2��\n");
	printf("��������  ��ջ����\n");
	while(!StackEmpty(LStack2))			/*�ж϶�ջ2�Ƿ�Ϊ��*/
	{
		DeleteQueue(&LQueue2,&q2);		/*�ַ��������γ��ӣ����ѳ���Ԫ�ظ�ֵ��q*/
		PopStack(LStack2,&s2);			/*�ַ����г�ջ�����ѳ�ջԪ�ظ�ֵ��s*/
		printf("%5c",q2);				/*����ַ�����2*/
		printf("%10c\n",s2);
		if(q2!=s2)						/*�ж��ַ�����2�Ƿ��ǻ���*/
		{
			printf("�ַ�����2���ǻ��ģ�\n");
			return;
		}
	}
	printf("�ַ�����2�ǻ��ģ�\n");
	system("pause");
}