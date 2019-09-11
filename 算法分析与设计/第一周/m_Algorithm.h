#ifndef m_Algorithm_h
#define m_Algorithm_h

// change type here
typedef  int type;

#include <bits/stdc++.h>
using namespace std;


void m_qsort(vector<type> & ,int ,int);
void m_MergeSort(vector<type>& ,int , int);
void merge(vector<type>& , int , int , int , int);
void bubble(vector<type>& , int , int);

type Kth_frag(vector<type>& ,int ,int ,int);
type Kth_frag_Separate(vector<type>& , int , int , int);



#endif
