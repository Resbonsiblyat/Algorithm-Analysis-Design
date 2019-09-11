#include "merge.h"

double start_t,end_t;
void start () {
	start_t = clock();
}

double end () {
	end_t = clock();
	return ((end_t - start_t)/CLOCKS_PER_SEC);
}


float Median(vector<type>& v) {
	return (int)v.size()%2?v[v.size()/2]:(v[v.size()/2]+v[v.size()/2-1])/2;
}

float findMedian(vector<type>& v1, vector<type>& v2) {
	int size = v1.size();
	if(size == 1) return (v1[0]+v2[0])/2.0;
	float m_v1 = Median(v1);
	float m_v2 = Median(v2);
	if(m_v1 == m_v2) return m_v1;
	vector<type>:: iterator it;
	if(m_v1 > m_v2)
		if(size%2) {
			v1.resize(size/2+1);
			v2.erase(v2.begin(),v2.begin() + size/2);
		}
		else {
			v1.resize(size/2);
			v2.erase(v2.begin(),v2.begin() + size/2);
		}
	else
		if(size%2) {
			v2.resize(size/2+1);
			v1.erase(v1.begin(),v1.begin() + size/2);
		}
		else {
			v2.resize(size/2);
			v1.erase(v1.begin(),v1.begin() + size/2);
		}
	return findMedian(v1,v2);	
}

int findSumofSubseq_m(vector<type>& vec, int l, int r) {
	//终止条件 
	if(l==r)return vec[l];
	
	int mid = l + r >> 1;
	int ans_l = findSumofSubseq_m(vec,l,mid);
	int ans_r = findSumofSubseq_m(vec,mid+1,r);
	
	int sum = 0, max_l = vec[mid], max_r = vec[mid + 1];
	for(int i = mid; i >= l; i--) {
        sum += vec[i];
        if(sum > max_l) max_l = sum;
    }
    sum = 0;
    for(int i = mid + 1; i <= r; i++) {
        sum += vec[i];
        if(sum > max_r) max_r = sum;
    }
    int ans = max_l + max_r;
    if(ans < ans_l) ans = ans_l;
    if(ans < ans_r) ans = ans_r;
    return ans;
}

int merge_count(int a[],int p,int q,int r) // a[p..q] ?a[q+1..r]
{
	int t=0;
	int len = r-p+1;
	int *b = (int*)malloc(len*sizeof(int));
	int i,j,k;
	for (i=p,j=q+1,k=0;i<=q&&j<=r;)
	{
	if (a[i]<=a[j]) b[k++]= a[i++];
	else
	 {
	 b[k++]= a[j++];
	 t += q-i+1;//第一个数组余下的长度
	 }
		 }
 
 
	 while (i<=q) b[k++]= a[i++];
	
	 while (j<=r) b[k++]= a[j++];
 
 
	 for (k=0;k<len;k++) a[k+p]=b[k];
 
 
	free(b);
	return t;
}
 
 
int count(int a[],int p,int r)
{
	if(p==r) return 0;
	int q=(p+r)/2;
	return count(a,p,q)+count(a,q+1,r)+merge_count(a,p,q,r);
}
