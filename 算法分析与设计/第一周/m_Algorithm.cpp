#include "m_Algorithm.h"
void m_qsort(vector<type> &vec, int l, int r) {
	if( l >= r ) return;
	
	int i = l , j = r, x = vec[l];
	while (i < j) {
		while ( i < j && vec[j] >= x) j--;
		if( i < j) vec[i++] = vec[j];
		while ( i < j && vec[i] <= x) i++;
		if( i < j) vec[j--] = vec[i];
	} 
	vec[i] = x;
	m_qsort(vec,l, i - 1);
	m_qsort(vec,l + 1, r);
}


void merge(vector<type>& vec, int l1, int r1, int l2, int r2 ) {
	int i = l1;                                               
	int j = l2;                                               
	int n = (r1 - l1 + 1) + (r2 - l2 + 1);                    
	vector<int> temp(n);                                     
	int k = 0;	                                          
	while (i <= r1&&j <= r2) {                                
		if (vec[i] < vec[j])
			temp[k++] = vec[i++];
		else
			temp[k++] = vec[j++];
	}

	while (i <= r1)
		temp[k++] = vec[i++];
	while (j <= r2)
		temp[k++] = vec[j++];

	for (int i = 0; i < n;i++)
	{
		vec[l1 + i] = temp[i];
	}
}

void m_MergeSort(vector<type>& vec,int start, int end) {
	if (start < end) {
		int mid = (start + end) >> 1;		
		m_MergeSort(vec, start, mid);		
		m_MergeSort(vec, mid + 1, end);			
		merge(vec, start, mid, mid + 1, end);             
	}
}

void bubble(vector<type>& vec,int l,int r) {
	int temp;
	for (int i = l; i < r; ++ i) {
		for (int j = l; j < r - i; ++ j) {
			if(vec[j] > vec[j+1]) {
				temp = vec[j];
				vec[j] = vec[j+1];
				vec[j+1] = temp;
			}
		}
	}
}


type Kth_frag(vector<type>& vec, int l,int r,int k) {
	m_qsort(vec,l,r);
	return vec[k-1];
}

type Kth_frag_Separate(vector<type>& vec, int l,int r, int k) {
	int i = l , j = r + 1;
	int tag = vec[l];
	while(1) {
		do {
			i++;
		}while(vec[i] < tag);
		do {
			j--;
		}while(vec[j] > tag);
		if(i >= j) break;
		int buffer = vec[i];
		vec[i] = vec[j];
		vec[j] = buffer;
	}
	if(j - l + 1 == k) // NOT j - l + 2 ---- 'cause vec[l] is tag, we count 1 more time here. So j - l + 2 - 1.
		return tag;
	vec[l] = vec[j];
	vec[j] = tag;
	if(j - l + 1 < k)
	 	return Kth_frag_Separate(vec,j+1,r,k-j-1+l); // k should cut down j-l+1 (lenth of left interval)
	else
		return Kth_frag_Separate(vec,j-1,r,k) ;
}

