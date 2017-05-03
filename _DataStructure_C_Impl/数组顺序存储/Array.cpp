#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#define MaxArraySize 2
typedef int DataType;
typedef struct{
	DataType *base;	//����Ԫ�صĻ���ַ
	int dim;		//�����ά��
	int *bounds;	//�����ÿһά֮��Ľ��޵ĵ�ַ
	int *constants; //����洢ӳ��������ַ
}Array;
//����ĳ�ʼ������
int InitArray(Array *A,int dim,...){
	int elemtotal=1,i;	//elemtotal������Ԫ����������ֵΪ1
	va_list ap;		//����va_list
	if(dim<1||dim>MaxArraySize)		//���ά�����Ϸ�������0
		return 0;
	A->dim=dim;
	A->bounds=(int *)malloc(dim*sizeof(int));	//����һ��dim��С���ڴ浥Ԫ
	if(!A->bounds)
		exit(-1);
	va_start(ap,dim);		//dim��һ���̶����������ɱ������ǰһ������
	for(i=0;i<dim;++i){
		A->bounds[i]=va_arg(ap,int);	//����ȡ�ÿɱ����������ά�ĳ���
		if(A->bounds[i]<0)
			return -1;
		elemtotal*=A->bounds[i];	//�õ�������Ԫ���ܵĸ���
	}
	va_end(ap);
	A->base=(DataType *)malloc(elemtotal*sizeof(DataType));	//Ϊ�����������Ԫ�ط����ڴ�ռ�
	if(!A->base)
		exit(-1);
	A->constants=(int *)malloc(dim*sizeof(int));	//Ϊ����ĳ�����ַ�����ڴ浥Ԫ
	if(!A->constants)
		exit(-1);
	A->constants[dim-1]=1;
	for(i=dim-2;i>=0;--i)
		A->constants[i]=A->bounds[i+1]*A->constants[i+1];
	return 1;
}
//�������顣����̬������ڴ浥Ԫ�ͷ�
void DestroyArray(Array *A){
	if(A->base)
		free(A->base);
	if(A->bounds)
		free(A->bounds);
	if(A->constants)
		free(A->constants);
	A->base=A->bounds=A->constants=NULL;	//������ָ��ָ���
	A->dim=0;
}
//����������Ԫ�ص��±꣬�����Ԫ����A�е���Ե�ַoffset
int LocateArray(Array A,va_list ap,int *offset){
	int i,instand;
	*offset=0;
	for(i=0;i<A.dim;i++){
		instand=va_arg(ap,int);
		if(instand<0||instand>=A.bounds[i])
			return 0;
		*offset+=A.constants[i]*instand;
	}
	return 1;
}
//����������ָ����Ԫ�أ���ָ����������±��Ԫ�ظ�ֵ��e
int GetValue(DataType *e,Array A,...){
	va_list ap;
	int offset;
	va_start(ap,A);
	if(LocateArray(A,ap,&offset)==0)	//�ҵ�Ԫ���������е����λ��
		return 0;
	va_end(ap);
	*e=*(A.base+offset);	//��Ԫ��ֵ��ֵ��e
	return 1;
}
//����ĸ�ֵ��������e��ֵ������ָ��������Ԫ��
int AssignValue(Array A,DataType e,...){
	va_list ap;
	int offset;
	va_start(ap,e);
	if(LocateArray(A,ap,&offset)==0)	//�ҵ�Ԫ���������е����λ��
		return 0;
	va_end(ap);
	*(A.base+offset)=e;	//��e��ֵ����Ԫ��
	return 1;
}
void main(){
	Array A;
	DataType B[4][3]={{5,6,7},{23,45,67},{35,2,34},{12,36,90}};
	int i,j;
	int dim=2,bound1=4,bound2=3;			/*��ʼ�������ά���͸�ά�ĳ���*/
	DataType e;
	InitArray(&A,dim,bound1,bound2);		/*����һ��4��3�Ķ�ά����A*/
	printf("����A�ĸ�ά�ĳ�����:");
	for(i=0;i<dim;i++)						/*�������A�ĸ�ά�ĳ���*/
		printf("%3d",A.bounds[i]);

	printf("\n����A�ĳ�����ַ��:");
	for(i=0;i<dim;i++)						/*�������A�ĳ�����ַ*/
		printf("%3d",A.constants[i]);
	printf("\n%d��%d�еľ���Ԫ������:\n",bound1,bound2);
	for(i=0;i<bound1;i++)
	{
		for(j=0;j<bound2;j++)
		{
			AssignValue(A,B[i][j],i,j);		/*������B��Ԫ�ظ�ֵ��A*/
			GetValue(&e,A,i,j);				/*������A�е�Ԫ�ظ�ֵ��e*/
			printf("A[%d][%d]=%3d\t",i,j,e); /*�������A�е�Ԫ��*/	
		}
		printf("\n");
	}
	printf("��������������������Ԫ��,�����û���ַ���Ԫ��:\n");
	for(i=0;i<bound1*bound2;i++)			/*�������������������A�е�Ԫ��*/
	{
		printf("��%d��Ԫ��=%3d\t",i+1,A.base[i]);
		if((i+1)%bound2==0)
			printf("\n");
	}
	DestroyArray(&A);
	system("pause");
}