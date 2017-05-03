#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char VertexType[4];
typedef char InfoPtr;
typedef int VRType;
#define INFINITY 100000		//����һ�����޴��ֵ
#define MaxSize 50	//��󶥵����
typedef int PathMatrix[MaxSize][MaxSize][MaxSize];	//����һ���������·���Ķ�ά����
typedef int ShortPathLength[MaxSize][MaxSize];	//����һ������Ӷ���v0������v����̾��������
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
	for(i=0;i<N.vexnum;++i)				/*������Ķ���*/
		printf("%s ",N.vex[i]);
	printf("\n������N��:\n");			/*�����N�Ļ�*/
	printf("���i=");
	for(i=0;i<N.vexnum;i++)
		printf("%11d",i);
	printf("\n");
	for(i=0;i<N.vexnum;i++)
	{
		printf("       %-6d   ",i);
		for(j=0;j<N.vexnum;j++)
			printf("%-11d",N.arc[i][j].adj);
		printf("\n"); 
	}
}
//��Floyd�㷨��������N�ĸ�����v��w֮������·��������path[v][w][u]��ʾu�Ǵ�v��w��ǰ������·���ϵĶ���
void Floyd(MGraph N,PathMatrix path,ShortPathLength dist){
	int u,v,w,i;
	for(v=0;v<N.vexnum;v++)		//��ʼ������path��dist
		for(w=0;w<N.vexnum;w++){
			dist[v][w]=N.arc[v][w].adj;	//��ʼʱ������v������w�����·��Ϊv��w�Ļ���Ȩֵ
			for(u=0;u<N.vexnum;u++)
				path[v][w][u]=0;	//·�������ʼ��Ϊ��
			if(dist[v][w]<INFINITY){	//���v��w��·��,����v��w��·������v��w����
				path[v][w][v]=1;
				path[v][w][w]=1;
			}
		}
	for(u=0;u<N.vexnum;u++)
		for(v=0;v<N.vexnum;v++)
			for(w=0;w<N.vexnum;w++)
				if(dist[v][u]<INFINITY&&dist[u][w]<INFINITY&&(dist[v][u]+dist[u][w]<dist[v][w])){	//��v��u��w��һ��·��Ϊ��ǰ��̵�·��
					dist[v][w]=dist[v][u]+dist[u][w];	//����v��w�����·��
					for(i=0;i<N.vexnum;i++) 	//��v��w��·��������v��u�ʹ�u��w������·��
						path[v][w][i]=path[v][u][i]||path[u][w][i];
				}
}
void main(){
	int w,u,v,vnum=3,arcnum=4;
	MGraph N;
	GNode value[]={{0,1,5},{1,0,10},{1,2,6},{2,0,9}};
	VertexType ch[]={"v0","v1","v2"};
	PathMatrix path;						/*�ö�ά���������·���������Ķ���*/
	ShortPathLength dist;					/*��һά���������·������*/
	CreateGraph(&N,value,vnum,arcnum,ch); /*����������N*/
	for(v=0;v<N.vexnum;v++)
		N.arc[v][v].adj=0;				/*���������㷨Ҫ��Խ�Ԫ��ֵΪ0����Ϊ������ͬ�������Ϊ0 */
	DisplayGraph(N);					/*���������N*/
	Floyd(N,path,dist);
	printf("����֮������·�����Ⱦ���dist:\n");
	for(u=0;u<N.vexnum;u++)
	{
		for(v=0;v<N.vexnum;v++)
			printf("%6d",dist[u][v]);
		printf("\n");
	}
	for(u=0;u<N.vexnum;u++)
		for(v=0;v<N.vexnum;v++)
			if(u!=v)
				printf("%s��%s����̾���Ϊ%d\n",N.vex[u],N.vex[v],dist[u][v]);
	printf("������֮������·���������Ķ��㣺\n");
	for(u=0;u<N.vexnum;u++)
		for(v=0;v<N.vexnum;v++)
			if(u!=v)
			{
				printf("��%s��%s������",N.vex[u],N.vex[v]);
				for(w=0;w<N.vexnum;w++)
					if(path[u][v][w]==1)
						printf("%s ",N.vex[w]);
				printf("\n");
			}
	system("pause");
}