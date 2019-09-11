#include <bits/stdc++.h>
using namespace std;
 
int N,M;
int sum=0;  //可行解数量
int x[10001];  //记录可行解
int a[10001][10001];//邻接矩阵 
 
bool limit(int k)  //边界条件
{
    for(int i = 0; i < N; i++)
        if(a[k][i] == 1 && x[k] == x[i] && x[i] != -1 )return false;
    return true;
}
 
void dfs(int t)
{
    if(t==N)   //N个结点全部染色，可行解+1 
    //{
        sum++;
    //    for(int i=0;i<N;i++)
    //        cout<<x[i]+1<<" ";
    //    cout<<endl;
    //}
    else
    {
        for(int i = 0; i < M;i++)
        {
            x[t] = i;
            if( limit(t) )dfs(t + 1);
            x[t] = -1; //回溯 
        }
    }
}
 
 
 
int main()
{
	int k;
	memset(x,-1,sizeof(x));
	cin >> N >> k >> M;
	while(k--) {
		int i,j;
		cin >> i >> j;
		a[i-1][j-1] = 1;
		a[j-1][i-1] = 1;
	}
    dfs(0);
    if(sum) cout<<sum<<endl;
    else cout << "-1" << endl;
    return 0;
}

