#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"SeqStack.h"
typedef char VertexType[4];
typedef char InfoPtr;
typedef int VRType;
#define MaxSize 50	//��󶥵����
typedef enum{DG,DN,UG,UN}GraphKind;	//ͼ�����ͣ�����ͼ��������������ͼ��������
//�߽������Ͷ���
typedef struct ArcNode{
	int adjvex;		//��ָ��Ķ����λ��
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
	AdjList vertex;	 //ͷ���
	int vexnum,arcnum;	//ͼ�Ķ�����Ŀ�뻡����Ŀ
	GraphKind kind;	//ͼ������
}AdjGraph;
//��ͼG�дӶ���u������v��һ����·��
void BriefPath(AdjGraph G,int u,int v){
	int k,i;
	SeqStack S;
	ArcNode *p;
	int visited[MaxSize];
	int parent[MaxSize];	//�洢�Ѿ����ʶ����ǰ������
	InitStack(&S);
	for(k=0;k<G.vexnum;k++)
		visited[k]=0;	//���ʱ�־��ʼ��
	PushStack(&S,u);	//��ʼ������ջ
	visited[u]=1;		//���ʱ�־��Ϊ1
	while(!StackEmpty(S)){	//������ȱ���ͼ������·����parent�洢
		PopStack(&S,&k);
		p=G.vertex[k].firstarc;
		while(p!=NULL){
			if(p->adjvex==v){	//����ҵ�����v
				parent[p->adjvex]=k;		//����v��ǰ�����������k
				printf("����%s������%s��·���ǣ�",G.vertex[u].data,G.vertex[v].data);
				i=v;
				do{			//�Ӷ���v��ʼ��·���еĶ���������ջ
					PushStack(&S,i);
					i=parent[i];
				}while(i!=u);
				PushStack(&S,u);
				while(!StackEmpty(S)){ //�Ӷ���u��ʼ���u��v��·���Ķ���
					PopStack(&S,&i);
					printf("%s ",G.vertex[i].data);
				}
				printf("\n");
			}else if(visited[p->adjvex]==0){	//���δ�ҵ�����v���ڽӵ�δ���ʹ��������Ѱ��
				visited[p->adjvex]=1;
				parent[p->adjvex]=k;
				PushStack(&S,p->adjvex);
			}
			p=p->nextarc;
		}
	}
}
//����ͼ�ж����Ӧ��λ��
int LocateVertex(AdjGraph G,VertexType v){
	int i;
	for(i=0;i<G.vexnum;i++)
		if(strcmp(G.vertex[i].data,v)==0)
			return i;
	return -1;
}
//�����ڽӱ�洢�ṹ����������ͼN
void CreateGraph(AdjGraph *G){
	int i,j,k,w;
	VertexType v1,v2;					/*������������v1��v2*/
	ArcNode *p;
	printf("������ͼ�Ķ�����,����(�Զ��ŷָ�): ");
	scanf("%d,%d",&(*G).vexnum,&(*G).arcnum);
	printf("������%d�������ֵ:",G->vexnum);
	for(i=0;i<G->vexnum;i++)			/*������洢��ͷ�����*/
	{
		scanf("%s",G->vertex[i].data);
		G->vertex[i].firstarc=NULL;		/*��������Ķ�����Ϊ��*/
	}
	printf("������ߵ���������(�Կո���Ϊ�ָ�):\n");
	for(k=0;k<G->arcnum;k++)			/*����������*/
	{
		scanf("%s%s",v1,v2);
		i=LocateVertex(*G,v1);
		j=LocateVertex(*G,v2);
		/*jΪ���iΪ���ߴ����ڽӱ�*/
		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=j;
		p->info=(InfoPtr*)malloc(sizeof(InfoPtr));
		/*��pָ��Ľ����뵽�߱���*/
		p->nextarc=G->vertex[i].firstarc;
		G->vertex[i].firstarc=p;
		/*iΪ���jΪ���ߴ����ڽӱ�*/
		p=(ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex=i;
		p->info=NULL;
		p->nextarc=G->vertex[j].firstarc;
		G->vertex[j].firstarc=p;
	}
	(*G).kind=UG;
}
//��������ͼG
void DestroyGraph(AdjGraph *G){
	int i;
	ArcNode *p,*q;
	for(i=0;i<G->vexnum;++i)		/*�ͷ�ͼ�еı߱���*/
	{
		p=G->vertex[i].firstarc;	/*pָ��߱�ĵ�һ�����*/
		if(p!=NULL)					/*����߱�Ϊ�գ����ͷű߱�Ľ��*/
		{
			q=p->nextarc;
			free(p);
			p=q;
		}
	}
	(*G).vexnum=0;					/*����������Ϊ0*/
	(*G).arcnum=0;					/*���ߵ���Ŀ��Ϊ0*/
}
//ͼG���ڽӱ�����
void DisplayGraph(AdjGraph G){
	int i;
	ArcNode *p;
	printf("��ͼ����%d�����㣺",G.vexnum);
	for(i=0;i<G.vexnum;i++)
		printf("%s ",G.vertex[i].data);
	printf("\nͼ�й���%d����:\n",2*G.arcnum);
	for(i=0;i<G.vexnum;i++)
	{
		p=G.vertex[i].firstarc;
		while(p)
		{
			printf("(%s,%s) ",G.vertex[i].data,G.vertex[p->adjvex].data);
			p=p->nextarc;
		}
		printf("\n");
	}
}
void main(){
	AdjGraph G;
	CreateGraph(&G);		/*�����ڽӱ�洢�ṹ����ͼG*/
	DisplayGraph(G);		/*�������ͼG*/
	BriefPath(G,0,4);		/*��ͼG�дӶ���a������e�ļ�·��*/
	DestroyGraph(&G);		/*����ͼG*/
	system("pause");
}