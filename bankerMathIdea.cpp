#include <stdio.h>
#include<stdlib.h>

#define PRONUM 5	//进程数 

struct progress	//模拟数组结构体 
{
	char proName;	//进程名 
	int max[4]; 	//所需最大资源数 
	int allocation[4]; //已分配资源数 
	int need[4];	//还需资源数 
	int finish;	//0为未完成，1为完成 
};
typedef struct progress Pro;


/*
获取数据 
*/ 
void getValue(Pro *pro)
{ 
	int i=0;
	for(int i = 0;i < PRONUM;i++)
	{
		for(int j = 0;j < 4; j++)
		{
			pro[i].need[j] = pro[i].max[j] - pro[i].allocation[j];
		}
		pro[i].finish = 0;
	}	
}



/*
获取可分配资源 
*/
void getAvailable(int *pAvailable,Pro *pPro)
{
	for(int i =0 ;i < PRONUM;i++)
	{
		for(int j = 0;j < 4;j++)
		{
			pAvailable[j] -= pPro[i].allocation[j]; 
		}	
	}
}





/*
输出程序基本数据 
*/
void dataPrintf(Pro *pPro)
{
	printf("进程\t分配矩阵\t最大需求矩阵\t\n");
	for(int i = 0; i < PRONUM; i++)
	{
		printf("%c\t",pPro[i].proName);
		for(int j = 0;j < 4;j++)
			printf("%d ",pPro[i].allocation[j]);
		
		printf("\t");
		for(int j = 0;j < 4; j++)
			printf("%d ",pPro[i].max[j]);
		printf("\n");
	}
	
 } 

//输出可用资源 
void printAvailable(int *available)	 
{
	printf("可用资源："); 
	for(int i = 0;i < 4; i++)
	{
		printf("%d ",available[i]); 
	}
	printf("\n\n");		
}


//输出进程运行状态 
void printfProgress(int i,int n,Pro *pPro,int *available)
{
	if(n < PRONUM)
	{
		printf("-----------------------\n当前运行程序%c\n需要资源：",pPro[i].proName);
		for(int j = 0;j < 4; j++)
			printf("%d ",pPro[i].need[j]);
		printf("\n");
		
		printAvailable(available); //输出当前可用资源数 
		
		if(pPro[i].finish == 1)
		{
			printf("可用资源足够，运行%c程序......\n运行完毕......\n释放%c占用资源......\n",pPro[i].proName,pPro[i].proName); 
		}
		
		else
			printf("可用资源不足，暂时跳过%c程序......\n\n",pPro[i].proName);
		
	}
}


//银行家算法 
void bankerSuanFa(Pro *pPro,int *pAvailable)
{
	int n =0;
	int i = 0;
	while(n  < PRONUM )	//当还有进程未执行时 
	{
		if(pPro[i].finish == 0)	//当该进程未完成时 
		{
			int target = 0;
			for(int j = 0;j < 4 && pPro[i].need[j] <= pAvailable[j];j++)	//检查各种资源数量是否能够满足该进程 
			{
				target++;
			}
			
			if(target == 4) 	//当可用资源满足当前进程时 
			{
				pPro[i].finish = 1;	//将其标志为完成状态 
				
				printfProgress(i,n,pPro,pAvailable);
								
				//运行该进程后，收回其占用资源 
				for(int k = 0;k < 4;k++)
				{
					pAvailable[k] +=  pPro[i].allocation[k];
				}
			
				printAvailable(pAvailable);				
				n++;//已运行进程数量加一 
			}
			else
			{
				printfProgress(i,n,pPro,pAvailable);
			}

		}
		
		i = (i+1)%PRONUM;
	}
	printf("所有程序执行完成！！！！"); 
}
 
int main()
{
	Pro pro[PRONUM] = {{'A',4,1,1,1,3,0,1,1},{'B',0,2,1,2,0,1,0,0},{'C',4,2,1,0,1,1,1,0},{'D',1,1,1,1,1,1,0,1},{'E',2,1,1,0,0,0,0,0}};	//所有进程 
	int allResouce[4] = {6,3,4,2}; //系统所有资源 	
	int max[4];	//程序所需最大资源 
	int allocation[4];	//程序已分配资源
	 
	getValue(pro);	//从文本中读取数据
	
	printf("资源总向量：");
	for(int i = 0 ;i < 4;i++)
		printf("%d ",allResouce[i]); 
	printf("\n");
	
	dataPrintf(pro);
	
	int available[4] = {6,3,4,2}; //系统可分配资源 
	getAvailable(available,pro);
	
	printAvailable(available);
	
	bankerSuanFa(pro,available); 
	
	return 0;
}
