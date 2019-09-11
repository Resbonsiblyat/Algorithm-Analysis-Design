#include "usual_solve.h"

int findSumofSubseq_u(vector<type>& vec) {
	int i = 1;
	int min = 0;
	
	int sum = vec[0];
	int ans = sum;
	
	for (i = 1; i < vec.size(); i++) {
		min = sum < min ? sum : min;
		sum += vec[i];
		ans = sum - min > ans? sum - min : ans;
	}
	
	return ans;
}

struct node {
	type value;
	int index;
};

node a[20001];
type aa[20001];
int c[20001];
int size;
bool cmp(node a, node b) {
	return a.value < b.value;
} 

vector<type> disorve(vector<type>& vec) {
	memset(aa,0,sizeof(aa));
	memset(a,0,sizeof(a));
	for(int i = 0 ; i < size ; i++) {
		a[i].index = i + 1;
		a[i].value = vec[i];
	}
	sort(a,a+size,cmp);
	for(int i = 1 ; i <= size ; i++) 
		aa[a[i-1].index] = i ;
	
	vector<type> dis(aa+1,aa+size+1);
	return dis;
}

int lowbit(int x) {
	return x&(-x);
}

void update(int t) {
	for(int i = t; i <= size; i += lowbit(i)) 
		c[i]++;
}

int getsum(int x) {
    int i;
    int temp=0;
    for(i=x;i>=1;i-=lowbit(i))
    {
        temp+=c[i];
    }
    return temp;
}


int reverseOrder_u(vector<type>& vec) {
	memset(c,0,sizeof(c));
	size = vec.size();
	vec = disorve(vec);
	
	int ans = 0;
	for(int i = 0 ; i < size ; i++) {
		update(vec[i]);
		ans += i - getsum(vec[i]) + 1;
	}
	return ans;
}
