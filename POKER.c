#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define NUM 5//扑克数 
#define NUMPOINT 13//点数最大值 
#define NUMSITUATION 8//扑克需要被判定情况的总数 
#define END 9//输入用 
#define INTRODUCTION -1//输入用，查看帮助 
#define NUMPROBABILITY 255//概率尝试数
#define NUMPROBABILITYFLOAT 255.0//计算概率用 
#define PROBABILITY -2//输入用，进入计算概率模式
#define SHOWDETAIL 1//展示细节
#define NOTSHOWDETAIL 0//不展示细节 
typedef enum{//花色枚举  相当于const int 
	HEART,//红桃 
	SPADE,//黑桃 
	CLUB,//梅花 
	DIAMOND,//方块
	NUMGRAPH, //花色种类总数 4
}graph;//图形 

typedef struct{//扑克
	graph flower;//花色 
	int point;//点数 
}card; 

card c[NUM];//扑克数组 

void Newcard(void)//分发新牌 
{
	if(c==NULL)
	{
		printf("error\n");
	}
	else
	{
		int i,j;
		//static int used=1; //重置随机数种子用
		//srand((unsigned int)time(0)*(used++));//重复重置随机数种子 
		for(i=0;i<NUM;i++)
		{
			c[i].flower=rand()%NUMGRAPH;//生成随机花色 0~3
			c[i].point=rand()%NUMPOINT+1;//生成随机点数 1~13
			for(j=0;j<i;j++)
				if((c[i].flower==c[j].flower)&&(c[i].point==c[j].point))
				//判断扑克是否重复 
				{
					i--;
					break;
				}
		}
	}
}

int Outputcard(void)//输出扑克样式 
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
									//用空格将花色对齐 
		for(i=0;i<NUM;i++)
		{
			printf("CARD%d:%s%3d\n",
			i+1,graphnames[c[i].flower],c[i].point);
			//输出扑克 
		}
		ret=1;
	}
	return ret;
}

int Judgeflushorstraight(int* poi,int* flo,int flag)//判断连子和同花顺 
{
	int ret; 
	if(c==NULL||poi==NULL||flo==NULL||flag!=-1)//每次Analyze都初始flag为-1 
	{
		printf("error\n");
		ret=-1;
	}
	else
	{
		int i;
		int cou=0;//计数用 
		for(i=0;i<NUMPOINT-1;i++)
		{
			if(poi[i]==1&&poi[i+1]==1)//检查点数是否连续 
			{
				cou++;				
			}
			else
			{
				cou=0;
			}
			if(cou==NUM-1)//NUM为5
			{
				break;
			}
		}
		for(i=0;i<NUMGRAPH;i++)//检查花色是否相同 
		{
			if(flo[i]==NUM) 
			{
				break;//退出时i为相同花色对应下标 
			}
		}										  
		if(i<NUMGRAPH&&cou==NUM-1)//提前退出则五张花色相同，且点数连续 
		{
			ret=2;//同花顺 
		}
		else if(i==NUMGRAPH&&cou==NUM-1)//点数连续但花色不同 
		{
			ret=1;
		}
		else
		{
			ret=0;
		}
	}
	return ret;//单一出口 
}

char *Analyze(int* pflag,char** sit)//分析扑克组合类型 
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
		for(i=0;i<NUM;i++)//分别统计每种点数和花色出现个数 
		{
			poi[c[i].point-1]++;
			flo[c[i].flower]++;		
		}
		int pointmax=0;
		int pointnexmax=0;
		int graphmax=0;
		int graphnexmax=0;//统计出现次数最大和次大的下标
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
		//暂时抹去最大值，方便求次大值位置 
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
		if(poi[pointmax]==4)//四炸four
		{
			*pflag=0;
		}
		else if(poi[pointmax]==3&&poi[pointnexmax]==2)//三拖二full_house
		{
			*pflag=1;
		}
		else if(poi[pointmax]==3&&poi[pointnexmax]==1)//三炸three
		{
			*pflag=2;
		}
		else if(poi[pointmax]==2&&poi[pointnexmax]==2)//两对two_paires
		{
			*pflag=3;
		}
		else if(poi[pointmax]==2&&poi[pointnexmax]==1)//一对pair
		{
			*pflag=4;
		}
		else if(Judgeflushorstraight(poi,flo,*pflag)==2)//同花顺flush
		{
			*pflag=5;
		}
		else if(Judgeflushorstraight(poi,flo,*pflag)==1)//顺子straight
		{
			*pflag=6;
		}
		else//无特殊排列normal 
		{
			*pflag=7;
		}
		return sit[*pflag];
		//按照题目要求返回表示情况判断结论的字符的地址 ，也可以直接返回flag的值 
	}
	
}

long int Gountil(int enter,int* pflag,char** sit,int detail)
//验证扑克直到满足某一情况再输出,返回尝试次数 
{
	long int ret;
	if(c==NULL||enter<INTRODUCTION||enter>END||pflag==NULL||sit==NULL)
	{
		printf("error\n");
		ret=-1;
	}
	else
	{
		long int i=1;//循环次数 
		int power=0;//幂次，方便输出 
		int maxi=0;
		int tempflag=0;
		char* analyzeresult=0;
		while(++power<10)//此处10无特殊意义，较大即可 
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
				if(analyzeresult==sit[enter])//判断是否符合要求 
				{
					tempflag=1;
					break;
				}
			}
			if(tempflag&&detail)//输出的判断 
			{
				printf("Case %ld:\n",i);
				Outputcard();
				printf("Now it is the %s.\n",analyzeresult);
				//printf("\a");//响铃 
			}
			if(tempflag)//判断退出 
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
		printf("Enter %2d to run until find the %s.\n",i,sit[i]);//输出判定部分规则 
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
		int enter=-1;//保证进入下一个while 
		printf("Now it is trying %d times to estimate the probability of a situation.\n",NUMPROBABILITY);
		while((enter<0)||(enter>7))//剔除不符合要求的输入 
		{
		 	printf("Please enter a number between 0 and 7.\n");
			scanf("%d",&enter);
			getchar();//重要 剔除非字母输入 
		}
		long long int sum=0;
		int temp=0;
		int i=0;
		printf("Each result is\n");
		for(i=0;i<NUMPROBABILITY;i++)
		{
			printf("%6lld ",temp=Gountil(enter,pflag,sit,NOTSHOWDETAIL));
			sum+=temp;
			if((i+1)%12==0&&i>0)//每十二次换行 
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
	int enter=-2;//输入 
	int flag=0;
	int i=0;
	char *sit[NUMSITUATION]={"four","full_house",
                             "three","two_paires",
							 "pair","flush",
							 "straight","normal",};
	//二级指针,按题目要求没有设成全局变量 
	srand(time(0));
	printf("Hello!This is a program which can simulate dealing pokers.\n");
	while(enter!=END)
	{
		enter=PROBABILITY-1;
		flag=0; 
		while((enter<PROBABILITY)||(enter>END))
		//剔除不符合要求的输入 
		{
			printf("\nEnter %d to continue,",NUMSITUATION);
			printf("enter %d to end,",END);
			printf("or enter %d to see the introduction.\n",INTRODUCTION);
			scanf("%d",&enter);
			getchar();//重要 剔除非数字输入 
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

/*mydddyh*/
