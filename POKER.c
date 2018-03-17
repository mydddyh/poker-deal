#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define NUM 5//�˿��� 
#define NUMPOINT 13//�������ֵ 
#define NUMSITUATION 8//�˿���Ҫ���ж���������� 
#define END 9//������ 
#define INTRODUCTION -1//�����ã��鿴���� 
#define NUMPROBABILITY 255//���ʳ�����
#define NUMPROBABILITYFLOAT 255.0//��������� 
#define PROBABILITY -2//�����ã�����������ģʽ
#define SHOWDETAIL 1//չʾϸ��
#define NOTSHOWDETAIL 0//��չʾϸ�� 
typedef enum{//��ɫö��  �൱��const int 
	HEART,//���� 
	SPADE,//���� 
	CLUB,//÷�� 
	DIAMOND,//����
	NUMGRAPH, //��ɫ�������� 4
}graph;//ͼ�� 

typedef struct{//�˿�
	graph flower;//��ɫ 
	int point;//���� 
}card; 

card c[NUM];//�˿����� 

void Newcard(void)//�ַ����� 
{
	if(c==NULL)
	{
		printf("error\n");
	}
	else
	{
		int i,j;
		//static int used=1; //���������������
		//srand((unsigned int)time(0)*(used++));//�ظ�������������� 
		for(i=0;i<NUM;i++)
		{
			c[i].flower=rand()%NUMGRAPH;//���������ɫ 0~3
			c[i].point=rand()%NUMPOINT+1;//����������� 1~13
			for(j=0;j<i;j++)
				if((c[i].flower==c[j].flower)&&(c[i].point==c[j].point))
				//�ж��˿��Ƿ��ظ� 
				{
					i--;
					break;
				}
		}
	}
}

int Outputcard(void)//����˿���ʽ 
{
	int ret; 
	if(c==NULL)
	{
		printf("error\n");
		ret=0;
	}
	else
	{
		int i;
		char *graphnames[NUMGRAPH]={"  heart",
		                            "  spade",
									"   club",
									"diamond",};
									//�ÿո񽫻�ɫ���� 
		for(i=0;i<NUM;i++)
		{
			printf("CARD%d:%s%3d\n",
			i+1,graphnames[c[i].flower],c[i].point);
			//����˿� 
		}
		ret=1;
	}
	return ret;
}

int Judgeflushorstraight(int* poi,int* flo,int flag)//�ж����Ӻ�ͬ��˳ 
{
	int ret; 
	if(c==NULL||poi==NULL||flo==NULL||flag!=-1)//ÿ��Analyze����ʼflagΪ-1 
	{
		printf("error\n");
		ret=-1;
	}
	else
	{
		int i;
		int cou=0;//������ 
		for(i=0;i<NUMPOINT-1;i++)
		{
			if(poi[i]==1&&poi[i+1]==1)//�������Ƿ����� 
			{
				cou++;				
			}
			else
			{
				cou=0;
			}
			if(cou==NUM-1)//NUMΪ5
			{
				break;
			}
		}
		for(i=0;i<NUMGRAPH;i++)//��黨ɫ�Ƿ���ͬ 
		{
			if(flo[i]==NUM) 
			{
				break;//�˳�ʱiΪ��ͬ��ɫ��Ӧ�±� 
			}
		}										  
		if(i<NUMGRAPH&&cou==NUM-1)//��ǰ�˳������Ż�ɫ��ͬ���ҵ������� 
		{
			ret=2;//ͬ��˳ 
		}
		else if(i==NUMGRAPH&&cou==NUM-1)//������������ɫ��ͬ 
		{
			ret=1;
		}
		else
		{
			ret=0;
		}
	}
	return ret;//��һ���� 
}

char *Analyze(int* pflag,char** sit)//�����˿�������� 
{
	if(c==NULL||pflag==NULL||sit==NULL)
	{
		printf("error\n");
		return 0; 
	}
	else
	{
		*pflag=-1;
		int i=0;
		int poi[NUMPOINT]={0};
		int flo[NUMGRAPH]={0};
		for(i=0;i<NUM;i++)//�ֱ�ͳ��ÿ�ֵ����ͻ�ɫ���ָ��� 
		{
			poi[c[i].point-1]++;
			flo[c[i].flower]++;		
		}
		int pointmax=0;
		int pointnexmax=0;
		int graphmax=0;
		int graphnexmax=0;//ͳ�Ƴ��ִ������ʹδ���±�
		int tem1;
		int tem2;	
		for(i=1;i<NUMPOINT;i++)
		{
			if(poi[i]>poi[pointmax])
			pointmax=i;
		}
		for(i=1;i<NUMGRAPH;i++)
		{
			if(flo[i]>flo[graphmax])
			graphmax=i;
		}
		tem1=poi[pointmax];
		tem2=flo[graphmax];
		poi[pointmax]=0;
		flo[graphmax]=0;
		//��ʱĨȥ���ֵ��������δ�ֵλ�� 
		for(i=1;i<NUMPOINT;i++)
		{
			if(poi[i]>poi[pointnexmax])
			pointnexmax=i;
		}
		for(i=1;i<NUMGRAPH;i++)
		{
			if(flo[i]>flo[graphnexmax])
			graphnexmax=i;
		}
		poi[pointmax]=tem1;
		flo[graphmax]=tem2;
		//printf("pointnexmax=%d\npointmax=%d\ngraphnexmax=%d\ngraphmax=%d\n",pointnexmax,pointmax,graphnexmax,graphmax);	
		if(poi[pointmax]==4)//��ըfour
		{
			*pflag=0;
		}
		else if(poi[pointmax]==3&&poi[pointnexmax]==2)//���϶�full_house
		{
			*pflag=1;
		}
		else if(poi[pointmax]==3&&poi[pointnexmax]==1)//��ըthree
		{
			*pflag=2;
		}
		else if(poi[pointmax]==2&&poi[pointnexmax]==2)//����two_paires
		{
			*pflag=3;
		}
		else if(poi[pointmax]==2&&poi[pointnexmax]==1)//һ��pair
		{
			*pflag=4;
		}
		else if(Judgeflushorstraight(poi,flo,*pflag)==2)//ͬ��˳flush
		{
			*pflag=5;
		}
		else if(Judgeflushorstraight(poi,flo,*pflag)==1)//˳��straight
		{
			*pflag=6;
		}
		else//����������normal 
		{
			*pflag=7;
		}
		return sit[*pflag];
		//������ĿҪ�󷵻ر�ʾ����жϽ��۵��ַ��ĵ�ַ ��Ҳ����ֱ�ӷ���flag��ֵ 
	}
	
}

long int Gountil(int enter,int* pflag,char** sit,int detail)
//��֤�˿�ֱ������ĳһ��������,���س��Դ��� 
{
	long int ret;
	if(c==NULL||enter<INTRODUCTION||enter>END||pflag==NULL||sit==NULL)
	{
		printf("error\n");
		ret=-1;
	}
	else
	{
		long int i=1;//ѭ������ 
		int power=0;//�ݴΣ�������� 
		int maxi=0;
		int tempflag=0;
		char* analyzeresult=0;
		while(++power<10)//�˴�10���������壬�ϴ󼴿� 
		{
			maxi=pow(10,power);
			for(;i<=10*maxi;i++)
			{
				if(!(i%maxi)&&detail)
				{
					printf("Case %ld begins.\n",i);
				}
				Newcard();
				//Outputcard();
				analyzeresult=Analyze(pflag,sit);
				if(analyzeresult==sit[enter])//�ж��Ƿ����Ҫ�� 
				{
					tempflag=1;
					break;
				}
			}
			if(tempflag&&detail)//������ж� 
			{
				printf("Case %ld:\n",i);
				Outputcard();
				printf("Now it is the %s.\n",analyzeresult);
				//printf("\a");//���� 
			}
			if(tempflag)//�ж��˳� 
			{
				break;
			}			
		}
		ret=i;			
	}
	return ret;
}

void Printintroduction(char** sit)
{
	int i=0;
	printf("Enter %d to try %d times to estimate the probability of a situation.\n",
	PROBABILITY,NUMPROBABILITY);
	printf("Enter %d to see the introduction again.\n",INTRODUCTION);
	for(i=0;i<NUMSITUATION;i++)
	{
		printf("Enter %2d to run until find the %s.\n",i,sit[i]);//����ж����ֹ��� 
	}
	printf("Enter %2d to continue.\n",NUMSITUATION);			
	printf("Enter %2d to end.\n",END);
}

void Probability(int* pflag,char** sit)
{
	if(sit==NULL)
	{
		printf("error\n");
	}
	else
	{
		int enter=-1;//��֤������һ��while 
		printf("Now it is trying %d times to estimate the probability of a situation.\n",NUMPROBABILITY);
		while((enter<0)||(enter>7))//�޳�������Ҫ������� 
		{
		 	printf("Please enter a number between 0 and 7.\n");
			scanf("%d",&enter);
			getchar();//��Ҫ �޳�����ĸ���� 
		}
		long long int sum=0;
		int temp=0;
		int i=0;
		printf("Each result is\n");
		for(i=0;i<NUMPROBABILITY;i++)
		{
			printf("%6lld ",temp=Gountil(enter,pflag,sit,NOTSHOWDETAIL));
			sum+=temp;
			if((i+1)%12==0&&i>0)//ÿʮ���λ��� 
			{
				printf("\n");
			} 
		}
		printf("\n");
		//printf("The summry is %lld.\n",sum);
		printf("The average of a %s is %.2f.\n",sit[enter],sum/NUMPROBABILITYFLOAT);
		printf("The probability of a %s is %f.\n",sit[enter],NUMPROBABILITYFLOAT/sum);
	}
}

int main(void)
{
	extern card c[];
	int enter=-2;//���� 
	int flag=0;
	int i=0;
	char *sit[NUMSITUATION]={"four","full_house",
                             "three","two_paires",
							 "pair","flush",
							 "straight","normal",};
	//����ָ��,����ĿҪ��û�����ȫ�ֱ��� 
	srand(time(0));
	printf("Hello!This is a program which can simulate dealing pokers.\n");
	while(enter!=END)
	{
		enter=PROBABILITY-1;
		flag=0; 
		while((enter<PROBABILITY)||(enter>END))
		//�޳�������Ҫ������� 
		{
			printf("\nEnter %d to continue,",NUMSITUATION);
			printf("enter %d to end,",END);
			printf("or enter %d to see the introduction.\n",INTRODUCTION);
			scanf("%d",&enter);
			getchar();//��Ҫ �޳����������� 
		}
		switch(enter)
		{
			case PROBABILITY://-2
				 Probability(&flag,sit);
				 break;
			case INTRODUCTION://-1 
				 Printintroduction(sit);
				 break; 
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
				Gountil(enter,&flag,sit,SHOWDETAIL);
				break;
			case 8:
				Newcard();
				Outputcard();
				char* analyzeresult=Analyze(&flag,sit);
				printf("This is a %s.\n",analyzeresult);
				break;	
		}		
	}	
	return 0;
}
