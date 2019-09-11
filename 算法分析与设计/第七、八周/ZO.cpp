#include<iostream>
#include<algorithm>
using namespace std;
#define N 100 //������������
struct goods  //��Ʒ�ṹ��
{
    int sign;  //��Ʒ���
    int w; //��Ʒ����
    int p; //��Ʒ��ֵ
}a[N];

bool m(goods a,goods b)
{
    return (a.p/a.w)>(b.p/b.w);
}

int max(int a,int b)
{
    return a<b?b:a;
}

int n,C,bestP=0,cp=0,cw=0;

int X[N],cx[N];

struct KNAPNODE   //״̬�ṹ��
{
    bool s1[N]; //��ǰ��������
    int k;     //�������
    int b; //��ֵ�Ͻ�
    int w; //��������
    int p; //�����ֵ
};

struct HEAP   //��Ԫ�ؽṹ��
{
    KNAPNODE *p;//�������
    int b;        //��ָ�����Ͻ�
};

//����������Ԫ��
void swap(HEAP &a, HEAP&b)
{
    HEAP temp = a;
    a = b;
    b = temp;
}

//����Ԫ������
void mov_up(HEAP H[], int i)
{
    bool done = false;
    if(i!=1){
       while(!done && i!=1){
           if(H[i].b>H[i/2].b){
              swap(H[i], H[i/2]);
           }else{
              done = true;
           }
           i = i/2;
       }
    }
}

//����Ԫ������
void mov_down(HEAP H[], int n, int i)
{
    bool done = false;
    if((2*i)<=n){
       while(!done && ((i = 2*i) <= n)){
           if(i+1<=n && H[i+1].b > H[i].b){
              i++;
           }

           if(H[i/2].b<H[i].b){
              swap(H[i/2], H[i]);
           }else{
              done = true;
           }
       }
    }
}

//�����в�����
void insert(HEAP H[], HEAP x, int &n)
{
    n++;
    H[n] = x;
    mov_up(H,n);
}

//ɾ�����н��
void del(HEAP H[], int &n, int i)
{
    HEAP x, y;
    x = H[i]; y = H[n];
    n --;
    if(i<=n){
       H[i] = y;
       if(y.b>=x.b){
           mov_up(H,i);
       }else{
           mov_down(H, n, i);
       }
    }
}

//��öѶ�Ԫ�ز�ɾ��
HEAP del_top(HEAP H[], int&n)
{
    HEAP x = H[1];
    del(H, n, 1);
    return x;
}

//�����֧�ڵ���Ͻ�
void bound( KNAPNODE* node,int M, goods a[], int n)
{
    int i = node->k;
    float w = node->w;
    float p = node->p;
    if(node->w>M){   //  ����������������������
       node->b = 0;   //  �Ͻ���Ϊ0
    }else{
       while((w+a[i].w<=M)&&(i<n)){  
           w += a[i].w;   // ���㱳����װ������
           p += a[i++].p; //    ���㱳����װ���ֵ
       }
       if(i<n){
           node->b = p + (M - w)*a[i].p/a[i].w;
       }else{
           node -> b = p;
       }
    }
}

//�÷�֧�޽編ʵ��0/1��������
int KnapSack4(int n,goods a[],int C, int X[])
{
    int i, k = 0;      // ����Ԫ�ظ����ļ�������ʼ��Ϊ0
    int v;
    KNAPNODE *xnode, *ynode, *znode;
    HEAP x, y, z, *heap;
    heap = new HEAP[n*n];        // ����ѵĴ洢�ռ�
    for( i=0; i<n; i++){
       a[i].sign=i;        //��¼����ĳ�ʼ���
    }
    sort(a,a+n,m);             // �����尴�ռ�ֵ����������
    xnode = new KNAPNODE;        // �������׽��
    for( i=0; i<n; i++){           //  ��ʼ�����
       xnode->s1[i] = false;
    }
    xnode->k = xnode->w = xnode->p = 0;
    while(xnode->k<n) {
       ynode = new KNAPNODE;     // �������y
       *ynode = *xnode;         //���x�����ݸ��Ƶ����y
       ynode->s1[ynode->k] = true;     //  װ���k������
       ynode->w += a[ynode->k].w;     //  ���������������ۼ�
       ynode->p += a[ynode->k].p;     //  �����������ֵ�ۼ�
       ynode->k ++;               //  �������++
       bound(ynode, C, a, n); //       ������y���Ͻ�
       y.b = ynode->b;
       y.p = ynode;
        insert(heap, y, k);        //���y���Ͻ��ֵ�������
       znode = new KNAPNODE;     // �������z
       *znode = *xnode;          //���x�����ݸ��Ƶ����z
       znode->k++;                         //   �������++
       bound(znode, C, a, n); //����ڵ�z���Ͻ�
       z.b = znode->b;
       z.p = znode;
       insert(heap, z, k);     //���z���Ͻ��ֵ�������
       delete xnode;
       x = del_top(heap, k);   //��öѶ�Ԫ����Ϊ�µĸ��׽��
       xnode = x.p;
    }
    v = xnode->p;
    for( i=0; i<n; i++){     //ȡװ�뱳��������������ǰ�����
       if(xnode->s1[i]){
           X[a[i].sign] =1 ;
       }else{
           X[a[i].sign] = 0;
       }
    }
    delete xnode;
    delete heap;
    return v;              //���ر���������ļ�ֵ
}

/*���������㷨��������*/
int main()
{
    goods b[N];
    printf("��Ʒ����n: ");
    scanf("%d",&n);   //������Ʒ����
    printf("��������C: ");
    scanf("%d",&C);   //���뱳������
    for (int i=0;i<n;i++)    //������Ʒi������w�����ֵv
    {
       printf("��Ʒ%d������w[%d]�����ֵv[%d]:  ",i+1,i+1,i+1);
       scanf("%d%d",&a[i].w,&a[i].p);
       b[i]=a[i];
    }

int sum4=KnapSack4(n,a,C,X);//���÷�֧�޽編��0/1��������
    printf("��֧�޽編���0/1��������:\nX=[ ");
    for(int i=0;i<n;i++)
       cout<<X[i]<<" ";//�������X[n]����
    printf("]  װ���ܼ�ֵ%d\n",sum4);
    return 0;
}
