#include <iostream>
#include <cmath>
#include <time.h>
#include <stdio.h>
using namespace std;
const int MAXN = 50;           //���Լ����n
const double INIT_T =2000;      //��ʼ�¶�
const double RATE = 0.95;        //�¶�˥����
const double FINAL_T = 0;    //��ֹ�¶�
const int IN_LOOP = 13000;      //�ڲ�ѭ������
const int OUT_LOOP = 20000;       //���ѭ������
struct work {                   //���幤���ṹ����
     int p[MAXN];             //�������
     double time;              //ʱ��
 };
int N=4;                          //��������
double D[MAXN][MAXN];        //����ʱ��
int x[MAXN][ MAXN];           //ѡ�����빤��
work bestwork;                   //���ŵı���·��
work minwork; 


void swap(int &a,int &b)         //ע��&a��&b ����Ҫ��p[]��洢������
{
 	int t;
    t=a;a=b;b=t;
}
  
inline double totaldist(work q)        //������ʱ��
{
    int a,b,c,d;
    double cost = 0;
    a=q.p[0];
    b=q.p[1];
    c=q.p[2];
    d=q.p[3];
    cost=D[a][0]+D[b][1]+D[c][2]+D[d][3];
    return cost;
}

void init()                     //�������ݣ�����ʼ��//����ʱ�����D[i][j] ��ʽ������i ����j
{
	minwork.time = 32767;
   	int i=0,j=0;
	for(i=0;i<N;i++)
  		for(j=0;j< N;j++)
  			cin>> D[i][j];


	for (i=0; i<N; i++)    //���Ž�ĳ�ʼ״̬
         bestwork.p[i] = i;
     bestwork.time = totaldist(bestwork);
}
/************** ����ָ�ɷ���*************/
work getnext(work p)   //�½��������
{
     int x, y;
     work ret;
     ret = p;
     do {
         x = rand() % 4;
         y = rand() % 4 ;//x,y����0-3�������
        }while(x == y);
     swap(ret.p[x], ret.p[y]);     //����������λ��˳��
     ret.time = totaldist(ret);
     return ret;
}
/************�˻�ͽ��¹���*********************/
work sa()
{
    double T;               //�¶�
    work curwork,newwork; //��ǰָ�ɺ���ָ��
    int i,A_t=0;
    double delta;
    T = INIT_T;     //��ֵ��ʼ�¶�
    curwork = bestwork;
    if(minwork.time > curwork.time) minwork = curwork;
    while(true)                            //��ѭ��
    {
        for (i=1; i<=IN_LOOP; i++)
        {
            newwork = getnext(curwork);    //��ȡ��·��
            delta = newwork.time - curwork.time;
            if(newwork.time < minwork.time) minwork = newwork;
            if (delta < 0.0)
                curwork = newwork;
            else
             {
                double rnd = rand()%1001/1000;     //�������0-1�ĸ�����
                double p = exp(-delta/T);
                if (p > rnd && p < 1)
                    curwork = newwork;
              }
            A_t++;
        }
        T *= RATE;    //����
		if ( A_t >= OUT_LOOP || T < FINAL_T) break;       //��ѭ��ֹͣ����
    }
    
    newwork = minwork;
    return newwork;
}
/**********************����������****************************/
int main()
{
	
	while(1) {
		init();
    printf("��ʼ����ָ��: %.4f\n", bestwork.time);
	for(int i=0;i<N;i++)
		printf(" %d->", bestwork.p[i]+1);
  	printf("\n");
    bestwork=sa();
    printf("���Ź���ָ��: %.4f\n", bestwork.time);
	for(int j=0;j<N;j++)
		printf(" %d->",bestwork.p[j]+1);
	printf("\n");
	} 
    return 0;
}

