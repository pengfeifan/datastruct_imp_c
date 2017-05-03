//_DataStructure_C_Impl:CriticalPath
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"SeqStack.h"
//ͼ���ڽӱ����Ͷ���
typedef char VertexType[4];
typedef int InfoPtr;	//����Ϊ���ͣ�Ϊ�˴��Ȩֵ
typedef int VRType;

#define MaxSize 50	 //��󶥵����
typedef enum{DG,DN,UG,UN}GraphKind;		//ͼ�����ͣ�����ͼ��������������ͼ��������
//�߽������Ͷ���
typedef struct ArcNode{
	int adjvex;	//�ڽӵ���,��ָ��Ķ����λ��
	InfoPtr *info;	//����Ȩֵ
	struct ArcNode *nextarc;	//ָʾ��һ����ö������ڽӵĶ���
}ArcNode;
//ͷ�������Ͷ���
typedef struct VNode{
	VertexType data;	//���ڴ洢����
	ArcNode *firstarc;	//ָʾ��һ����ö����ڽӵĶ���
}VNode,AdjList[MaxSize];
//ͼ�����Ͷ���
typedef struct{
	AdjList vertex;
	int vexnum,arcnum;	//ͼ�Ķ�����Ŀ�뻡����Ŀ
	GraphKind kind;	//ͼ������
}AdjGraph;
//����ͼ�ж����Ӧ��λ��
int LocateVertex(AdjGraph G,VertexType v){
	int i;
	for(i=0;i<G.vexnum;i++)
		if(strcmp(G.vertex[i].data,v)==0)
			return i;
	return -1;
}
//�����ڽӱ�洢�ṹ������������N
void CreateGraph(AdjGraph *N){
	int i,j,k,w;
	VertexType v1,v2;	//������������v1��v2
	ArcNode *p;
	printf("������ͼ�Ķ�����,����(���ŷָ�): ");
	scanf("%d,%d",&(*N).vexnum,&(*N).arcnum);
	printf("������%d�������ֵ:\n",N->vexnum);
	for(i=0;i<N->vexnum;i++){
		scanf("%s",N->vertex[i].data);
		N->vertex[i].firstarc=NULL;	//��������Ķ�����Ϊ��
	}
	printf("�����뻡β�ͻ�ͷ(�Կո���Ϊ���):\n");
	for(k=0;k<N->arcnum;k++){	//����������
		scanf("%s%s%*c%d",v1,v2,&w);
		i=LocateVertex(*N,v1);
		j=LocateVertex(*N,v2);
		//jΪ��ͷiΪ��β�����ڽӱ�
		p=(ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex=j;
		p->info=(InfoPtr*)malloc(sizeof(InfoPtr));
		*(p->info)=w;
		//��pָ��Ľ����뵽�߱���
		p->nextarc=N->vertex[i].firstarc;
		N->vertex[i].firstarc=p;
	}
	(*N).kind=DN;
}
//��������ͼG
void DestroyGraph(AdjGraph *G){
	int i;
	ArcNode *p,*q;
	for(i=0;i<(*G).vexnum;++i){	//�ͷ�ͼ�еı߱���
		p=G->vertex[i].firstarc;	//pָ��߱�ĵ�һ�����
		if(p!=NULL){	//����߱�Ϊ�գ����ͷű߱�Ľ��
			q=p->nextarc;
			free(p);
			p=q;
		}
	}
	(*G).vexnum=0;	//����������Ϊ0
	(*G).arcnum=0;	//���ߵ���Ŀ��Ϊ0
}
//���ͼ���ڽӱ�
void DisplayGraph(AdjGraph G){
	int i;
	ArcNode *p;
	printf("%d�����㣺\n",G.vexnum);
	for(i=0;i<G.vexnum;i++)
		printf("%s ",G.vertex[i].data);
	printf("\n%d����:\n",G.arcnum);
	for(i=0;i<G.vexnum;i++)
	{
		p=G.vertex[i].firstarc;
		while(p)
		{
			printf("<%s,%s,%d> ",G.vertex[i].data,G.vertex[p->adjvex].data,*(p->info));
			p=p->nextarc;
		}
		printf("\n");
	}
}
//*********************************************************
int ve[MaxSize]; //ve����¼����緢��ʱ��
/*�����ڽӱ�洢�ṹ��������N���������򣬲���������Ӧ�¼������緢��ʱ��ve*/
/*���N�޻�·��������ջT����N��һ����������,������1,����Ϊ0*/
int TopologicalOrder(AdjGraph N,SeqStack *T){
	int i,k,count=0;
	int indegree[MaxSize];	//����indegree�洢����������
	SeqStack S;
	ArcNode *p;
	//��ͼ�и��������ȱ���������indegree��
	for(i=0;i<N.vexnum;i++) //������indegree����ֵ
		indegree[i]=0;
	for(i=0;i<N.vexnum;i++){
		p=N.vertex[i].firstarc;
		while(p!=NULL){
			k=p->adjvex;
			indegree[k]++;
			p=p->nextarc;
		}
	}
	//��ʼ��ջS
	InitStack(&S);
	printf("�������У�");
	for(i=0;i<N.vexnum;i++)
		if(!indegree[i])	//�����Ϊ��Ķ�����ջ
			PushStack(&S,i);
	InitStack(T);	//��ʼ�����������򶥵�ջ
	for(i=0;i<N.vexnum;i++)	//��ʼ��ve
		ve[i]=0;
	while(!StackEmpty(S)){	//���ջS��Ϊ��
		PopStack(&S,&i);	//��ջS������������Ķ���i����
		printf("%s ",N.vertex[i].data);
		PushStack(T,i);	//i�Ŷ���������������ջT
		count++;	//����ջT�Ķ������
		for(p=N.vertex[i].firstarc;p;p=p->nextarc){	//������Ϊi�Ķ����ÿ���ڽӵ�
			k=p->adjvex;		//�������Ϊk
			if(--indegree[k]==0)	//���k����ȼ�1���Ϊ0����k��ջS
				PushStack(&S,k);
			if(ve[i]+*(p->info)>ve[k])	//���㶥��k��Ӧ���¼������緢��ʱ��
				ve[k]=ve[i]+*(p->info);
		}
	}
	if(count<N.vexnum){
		printf("���������л�·\n");
		return 0;
	}else
		return 1;
}
//���AOE��N�Ĺؼ�·��
int CriticalPath(AdjGraph N){
	int vl[MaxSize];	//�¼�������ʱ��
	SeqStack T;
	int i,j,k,e,l,dut,value,count,e1[MaxSize],e2[MaxSize];
	ArcNode *p;
	if(!TopologicalOrder(N,&T))	//����л����ڣ��򷵻�0
		return 0;
	value=ve[0];
	for(i=1;i<N.vexnum;i++)
		if(ve[i]>value)
			value=ve[i];	//valueΪ�¼������緢��ʱ������ֵ
	for(i=0;i<N.vexnum;i++) //�������¼���������ʱ���ʼ��
		vl[i]=value;
	while(!StackEmpty(T))	//��������������������vlֵ
		for(PopStack(&T,&j),p=N.vertex[j].firstarc;p;p=p->nextarc){ //����ջT��Ԫ��,����j,pָ��j�ĺ���¼�k
			k=p->adjvex;
			dut=*(p->info);	//dutΪ��<j,k>��Ȩֵ
			if(vl[k]-dut<vl[j])//�����¼�j����ٷ���ʱ��
				vl[j]=vl[k]-dut;
		}
		printf("\n�¼������緢��ʱ���������ʱ��\ni ve[i] vl[i]\n");
		for(i=0;i<N.vexnum;i++)		//��������Ӧ���¼������緢��ʱ��������ʱ��
			printf("%d   %d     %d\n",i,ve[i],vl[i]);
		printf("�ؼ�·��Ϊ��(");
		for(i=0;i<N.vexnum;i++) //����ؼ�·�������Ķ���
			if(ve[i]==vl[i])
				printf("%s ",N.vertex[i].data);
		printf(")\n");
		count=0;
		printf("����翪ʼʱ�������ʼʱ��\n   ��    e   l   l-e\n");
		for(j=0;j<N.vexnum;j++)
			for(p=N.vertex[j].firstarc;p;p=p->nextarc){
				k=p->adjvex;
				dut=*(p->info);	//dutΪ��<j,k>��Ȩֵ
				e=ve[j];		//e���ǻ<j,k>�����翪ʼʱ��
				l=vl[k]-dut;	//l���ǻ<j,k>������ʼʱ��
				printf("%s��%s %3d %3d %3d\n",N.vertex[j].data,N.vertex[k].data,e,l,l-e);
				if(e==l){	//���ؼ��������������
					e1[count]=j;
					e2[count]=k;
					count++;
				}
			}
		printf("�ؼ��Ϊ��");
		for(k=0;k<count;k++)		//����ؼ�·��
		{
			i=e1[k];
			j=e2[k];
			printf("(%s��%s) ",N.vertex[i].data,N.vertex[j].data);
		}
		printf("\n");
	return 1;
}
void main(){
	AdjGraph N;
	CreateGraph(&N);		/*�����ڽӱ�洢�ṹ����������N*/
	DisplayGraph(N);		/*���������N*/
	CriticalPath(N);		/*����N�Ĺؼ�·��*/
	DestroyGraph(&N);		/*������N*/
	system("pause");
}