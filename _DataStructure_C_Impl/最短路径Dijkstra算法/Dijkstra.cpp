// _DataStructure_C_Impl:Dijkstra
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char VertexType[4];
typedef char InfoPtr;
typedef int VRType;
#define INFINITY 100000		//����һ�����޴��ֵ
#define MaxSize 50	//��󶥵����
typedef int PathMatrix[MaxSize][MaxSize];	//����һ���������·���Ķ�ά����
typedef int ShortPathLength[MaxSize];	//����һ������Ӷ���v0������v����̾��������
typedef enum{DG,DN,UG,UN}GraphKind;
typedef struct{
	VRType adj;		//������Ȩͼ����1��ʾ���ڣ�0��ʾ�����ڣ����ڴ�Ȩͼ���洢Ȩֵ
	InfoPtr *info;	//�뻡��ߵ������Ϣ
}ArcNode,AdjMatrix[MaxSize][MaxSize];
//ͼ�����Ͷ���
typedef struct{
	VertexType vex[MaxSize];	//���ڴ洢����
	AdjMatrix arc;		//�ڽӾ��󣬴洢�߻򻡵���Ϣ
	int vexnum,arcnum;	//�������ͱߣ���������Ŀ
	GraphKind kind;	//ͼ������
}MGraph;
//���һ���洢�����С��к�Ȩֵ�����Ͷ���
typedef struct{
	int row;
	int col;
	int weight;
}GNode;
//�����ڽӾ����ʾ������������N
void CreateGraph(MGraph *N,GNode *value,int vnum,int arcnum,VertexType *ch){
	int i,j,k,w;
	char s[MaxSize];
	VertexType v1,v2;
	N->vexnum=vnum;
	N->arcnum=arcnum;
	for(i=0;i<vnum;i++)
		strcpy(N->vex[i],ch[i]);
	//��ʼ���ڽӾ���
	for(i=0;i<N->vexnum;i++)	
		for(j=0;j<N->vexnum;j++){
			N->arc[i][j].adj=INFINITY;
			N->arc[i][j].info=NULL;	//������Ϣ��ʼ��Ϊ��
		}
	for(k=0;k<arcnum;k++){
		i=value[k].row;
		j=value[k].col;
		N->arc[i][j].adj=value[k].weight;
	}
	N->kind=DN;	//ͼ������Ϊ������
}
//����ڽӾ���洢��ʾ��ͼN
void DisplayGraph(MGraph N){
	int i,j;
	printf("����������%d������%d����������������: ",N.vexnum,N.arcnum);
	for(i=0;i<N.vexnum;++i)				//������Ķ���
		printf("%s ",N.vex[i]);
	printf("\n������N��:\n");			//�����N�Ļ�
	printf("���i=");
	for(i=0;i<N.vexnum;i++)
		printf("%8d",i);
	printf("\n");
	for(i=0;i<N.vexnum;i++)
	{
		printf("%8d",i);
		for(j=0;j<N.vexnum;j++)
			printf("%8d",N.arc[i][j].adj);
		printf("\n"); 
	}
}
/*��Dijkstra�㷨��������N��v0���㵽���������v�����·��P[v]����Ȩ����D[v]*/
/*final[v]Ϊ1��ʾv��S�����Ѿ������v0��v�����·��*/
void Dijkstra(MGraph N,int v0,PathMatrix path,ShortPathLength dist){
	int v,w,i,k,min;
	int final[MaxSize];	//��¼v0���ö�������·���Ƿ������
	for(v=0;v<N.vexnum;v++){	//����dist�洢v0��v����̾��룬��ʼ��Ϊv0��v�Ļ��ľ���
		final[v]=0;
		dist[v]=N.arc[v0][v].adj;
		for(w=0;w<N.vexnum;w++)
			path[v][w]=0;
		if(dist[v]<INFINITY){	//�����v0��v��ֱ��·�������ʼ��·������
			path[v][v0]=1;
			path[v][v]=1;
		}
	}
	dist[v0]=0;	//v0��v0��·��Ϊ0
	final[v0]=1;//v0���㲢�뼯��S
	/*��v0������G.vexnum-1����������·���������ö��㲢�뼯��S*/
	for(i=1;i<N.vexnum;i++){
		min=INFINITY;
		for(w=0;w<N.vexnum;w++)
			if(!final[w]&&dist[w]<min){	//�ڲ����ڼ���S�Ķ������ҵ���v0����Ķ���
				v=w;					//������v0����Ķ���w����v������븳��min
				min=dist[w];
			}
		final[v]=1;  //��v���뼯��S
		for(w=0;w<N.vexnum;w++)	//�����²��뼯��S�Ķ��㣬����v0�������ڼ���S�Ķ�������·�����Ⱥ����·������
			if(!final[w]&&min<INFINITY&&N.arc[v][w].adj<INFINITY&&(min+N.arc[v][w].adj<dist[w])){
				dist[w]=min+N.arc[v][w].adj;
				for(k=0;k<N.vexnum;k++)
					path[w][k]=path[v][k];
				path[w][w]=1;
			}
	}
}
void main(){
	int i,j,vnum=6,arcnum=9;
	MGraph N;
	GNode value[]={{0,1,30},{0,2,60},{0,4,150},{0,5,40},
	{1,2,40},{1,3,100},{2,3,50},{3,4,30},{4,5,10}};
	VertexType ch[]={"v0","v1","v2","v3","v4","v5"};
	PathMatrix path;						/*�ö�ά���������·���������Ķ���*/
	ShortPathLength dist;				/*��һά���������·������*/
	CreateGraph(&N,value,vnum,arcnum,ch); /*����������N*/
	DisplayGraph(N);						/*���������N*/
	Dijkstra(N,0,path,dist);
	printf("%s������������·������Ϊ��\n",N.vex[0]);
	for(i=0;i<N.vexnum;++i)
		if(i!=0)
			printf("%s-%s:%d\n",N.vex[0],N.vex[i],dist[i]);
	system("pause");
}