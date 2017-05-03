#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
#define MaxArraySize 2
typedef int DataType;
typedef struct{
	DataType *base;	//数组元素的基地址
	int dim;		//数组的维数
	int *bounds;	//数组的每一维之间的界限的地址
	int *constants; //数组存储映像常量基地址
}Array;
//数组的初始化操作
int InitArray(Array *A,int dim,...){
	int elemtotal=1,i;	//elemtotal是数组元素总数，初值为1
	va_list ap;		//声明va_list
	if(dim<1||dim>MaxArraySize)		//如果维数不合法，返回0
		return 0;
	A->dim=dim;
	A->bounds=(int *)malloc(dim*sizeof(int));	//分配一个dim大小的内存单元
	if(!A->bounds)
		exit(-1);
	va_start(ap,dim);		//dim是一个固定参数，即可变参数的前一个参数
	for(i=0;i<dim;++i){
		A->bounds[i]=va_arg(ap,int);	//依次取得可变参数，即各维的长度
		if(A->bounds[i]<0)
			return -1;
		elemtotal*=A->bounds[i];	//得到数组中元素总的个数
	}
	va_end(ap);
	A->base=(DataType *)malloc(elemtotal*sizeof(DataType));	//为数组分配所有元素分配内存空间
	if(!A->base)
		exit(-1);
	A->constants=(int *)malloc(dim*sizeof(int));	//为数组的常量基址分配内存单元
	if(!A->constants)
		exit(-1);
	A->constants[dim-1]=1;
	for(i=dim-2;i>=0;--i)
		A->constants[i]=A->bounds[i+1]*A->constants[i+1];
	return 1;
}
//销毁数组。将动态申请的内存单元释放
void DestroyArray(Array *A){
	if(A->base)
		free(A->base);
	if(A->bounds)
		free(A->bounds);
	if(A->constants)
		free(A->constants);
	A->base=A->bounds=A->constants=NULL;	//将各个指针指向空
	A->dim=0;
}
//根据数组中元素的下标，求出该元素在A中的相对地址offset
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
//返回数组中指定的元素，将指定的数组的下标的元素赋值给e
int GetValue(DataType *e,Array A,...){
	va_list ap;
	int offset;
	va_start(ap,A);
	if(LocateArray(A,ap,&offset)==0)	//找到元素在数组中的相对位置
		return 0;
	va_end(ap);
	*e=*(A.base+offset);	//将元素值赋值给e
	return 1;
}
//数组的赋值操作。将e的值赋给的指定的数组元素
int AssignValue(Array A,DataType e,...){
	va_list ap;
	int offset;
	va_start(ap,e);
	if(LocateArray(A,ap,&offset)==0)	//找到元素在数组中的相对位置
		return 0;
	va_end(ap);
	*(A.base+offset)=e;	//将e赋值给该元素
	return 1;
}
void main(){
	Array A;
	DataType B[4][3]={{5,6,7},{23,45,67},{35,2,34},{12,36,90}};
	int i,j;
	int dim=2,bound1=4,bound2=3;			/*初始化数组的维数和各维的长度*/
	DataType e;
	InitArray(&A,dim,bound1,bound2);		/*构造一个4×3的二维数组A*/
	printf("数组A的各维的长度是:");
	for(i=0;i<dim;i++)						/*输出数组A的各维的长度*/
		printf("%3d",A.bounds[i]);

	printf("\n数组A的常量基址是:");
	for(i=0;i<dim;i++)						/*输出数组A的常量基址*/
		printf("%3d",A.constants[i]);
	printf("\n%d行%d列的矩阵元素如下:\n",bound1,bound2);
	for(i=0;i<bound1;i++)
	{
		for(j=0;j<bound2;j++)
		{
			AssignValue(A,B[i][j],i,j);		/*将数组B的元素赋值给A*/
			GetValue(&e,A,i,j);				/*将数组A中的元素赋值给e*/
			printf("A[%d][%d]=%3d\t",i,j,e); /*输出数组A中的元素*/	
		}
		printf("\n");
	}
	printf("按照数组的线性序列输出元素,即利用基地址输出元素:\n");
	for(i=0;i<bound1*bound2;i++)			/*按照线性序列输出数组A中的元素*/
	{
		printf("第%d个元素=%3d\t",i+1,A.base[i]);
		if((i+1)%bound2==0)
			printf("\n");
	}
	DestroyArray(&A);
	system("pause");
}