#include <stdio.h>
#include<stdlib.h>

#define PRONUM 5	//������ 

struct progress	//ģ������ṹ�� 
{
	char proName;	//������ 
	int max[4]; 	//���������Դ�� 
	int allocation[4]; //�ѷ�����Դ�� 
	int need[4];	//������Դ�� 
	int finish;	//0Ϊδ��ɣ�1Ϊ��� 
};
typedef struct progress Pro;


/*
��ȡ���� 
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
��ȡ�ɷ�����Դ 
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
�������������� 
*/
void dataPrintf(Pro *pPro)
{
	printf("����\t�������\t����������\t\n");
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

//���������Դ 
void printAvailable(int *available)	 
{
	printf("������Դ��"); 
	for(int i = 0;i < 4; i++)
	{
		printf("%d ",available[i]); 
	}
	printf("\n\n");		
}


//�����������״̬ 
void printfProgress(int i,int n,Pro *pPro,int *available)
{
	if(n < PRONUM)
	{
		printf("-----------------------\n��ǰ���г���%c\n��Ҫ��Դ��",pPro[i].proName);
		for(int j = 0;j < 4; j++)
			printf("%d ",pPro[i].need[j]);
		printf("\n");
		
		printAvailable(available); //�����ǰ������Դ�� 
		
		if(pPro[i].finish == 1)
		{
			printf("������Դ�㹻������%c����......\n�������......\n�ͷ�%cռ����Դ......\n",pPro[i].proName,pPro[i].proName); 
		}
		
		else
			printf("������Դ���㣬��ʱ����%c����......\n\n",pPro[i].proName);
		
	}
}


//���м��㷨 
void bankerSuanFa(Pro *pPro,int *pAvailable)
{
	int n =0;
	int i = 0;
	while(n  < PRONUM )	//�����н���δִ��ʱ 
	{
		if(pPro[i].finish == 0)	//���ý���δ���ʱ 
		{
			int target = 0;
			for(int j = 0;j < 4 && pPro[i].need[j] <= pAvailable[j];j++)	//��������Դ�����Ƿ��ܹ�����ý��� 
			{
				target++;
			}
			
			if(target == 4) 	//��������Դ���㵱ǰ����ʱ 
			{
				pPro[i].finish = 1;	//�����־Ϊ���״̬ 
				
				printfProgress(i,n,pPro,pAvailable);
								
				//���иý��̺��ջ���ռ����Դ 
				for(int k = 0;k < 4;k++)
				{
					pAvailable[k] +=  pPro[i].allocation[k];
				}
			
				printAvailable(pAvailable);				
				n++;//�����н���������һ 
			}
			else
			{
				printfProgress(i,n,pPro,pAvailable);
			}

		}
		
		i = (i+1)%PRONUM;
	}
	printf("���г���ִ����ɣ�������"); 
}
 
int main()
{
	Pro pro[PRONUM] = {{'A',4,1,1,1,3,0,1,1},{'B',0,2,1,2,0,1,0,0},{'C',4,2,1,0,1,1,1,0},{'D',1,1,1,1,1,1,0,1},{'E',2,1,1,0,0,0,0,0}};	//���н��� 
	int allResouce[4] = {6,3,4,2}; //ϵͳ������Դ 	
	int max[4];	//�������������Դ 
	int allocation[4];	//�����ѷ�����Դ
	 
	getValue(pro);	//���ı��ж�ȡ����
	
	printf("��Դ��������");
	for(int i = 0 ;i < 4;i++)
		printf("%d ",allResouce[i]); 
	printf("\n");
	
	dataPrintf(pro);
	
	int available[4] = {6,3,4,2}; //ϵͳ�ɷ�����Դ 
	getAvailable(available,pro);
	
	printAvailable(available);
	
	bankerSuanFa(pro,available); 
	
	return 0;
}
