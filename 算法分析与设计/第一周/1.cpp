#include <bits/stdc++.h>
#include <Windows.h>
#include "m_Algorithm.h"
using namespace std;

double start_t, end_t;
void start ()
{
	start_t = clock();
}
double end ()
{
	end_t = clock();
	return ((end_t - start_t)/CLOCKS_PER_SEC);
}

void test_1()
{
	int i = 0;
	while(i++ < 10000001 );
}
void output(vector<int>& testvec,ofstream& result)
{
	vector<int> :: iterator iter = testvec.begin();
	while(iter != testvec.end()) {
		result << *iter << " ";
		iter++;
	}
	result << endl;
}
void test_2(vector<int> testvec)
{
	m_qsort(testvec,0,(int)testvec.size() - 1);
	return;
}

void test_3(vector<int> testvec) 
{
	m_MergeSort(testvec,0,(int)testvec.size() - 1);
	return;
}

void test_4(vector<int> testvec)
{
	bubble(testvec,0,(int)testvec.size() - 1);
	return;
}

void test_5(ifstream& in,ofstream& testresults) 
{
	int buffer;
	vector<int> testvec;
	while( in >> buffer) 
		testvec.push_back(buffer);
	in.close();
	start();
	test_2(testvec);
	double time = end();
	testresults << "qsort test : " << time << " Sec(s)" << endl;
	start();
	test_3(testvec);
	time = end();
	testresults << "merge sort test : " << time << " Sec(s)" << endl;
	start();
	test_4(testvec);
	time = end();
	testresults << "bubble sort test : " << time << " Sec(s)" << endl;
	testresults << endl;
}

void test_6(ifstream& in,ofstream& testresults)
{
	int buffer;
	vector<int> testvec1;
	while( in >> buffer) 
		testvec1.push_back(buffer);
	in.close();
	vector<int> testvec2(testvec1);
	double t;
	start();
	Kth_frag(testvec1,0,(int)testvec1.size()-1,1); // 1 means smallest
	t = end();
	testresults << "Kth_frag Smallest test :" << t << "Sec(s)" << endl;
	
	start();
	Kth_frag_Separate(testvec2,0,(int)testvec2.size()-1,1);
	t = end();
	testresults << "Kth_frag_Separate Smallest test :" << t << "Sec(s)" << endl;
	
	start();
	Kth_frag(testvec1,0,(int)testvec1.size()-1,(int)testvec1.size()); 
	t = end();
	testresults << "Kth_frag Biggest test :" << t << "Sec(s)" << endl;
	
	start();
	Kth_frag_Separate(testvec2,0,(int)testvec2.size()-1,(int)testvec2.size());
	t = end();
	testresults << "Kth_frag_Separate Biggest test :" << t << "Sec(s)" << endl;
	
	default_random_engine e(time(0));
	uniform_int_distribution<unsigned> u(1,(int)testvec1.size());
	int k = u(e);
	start();
	Kth_frag(testvec1,0,(int)testvec1.size()-1,k);
	t = end();
	testresults << k << "th_frag test :" << t << "Sec(s)" << endl;
	
	start();
	Kth_frag_Separate(testvec2,0,(int)testvec2.size()-1,k);
	t = end();
	testresults << k << "th_frag_Separate test :" << t << "Sec(s)" << endl;
}

int main()
{
	ofstream testresults("Test1Results.txt");
	
	int i = 1;
	while( i <= 20) {
		start();
		test_1();
		double time = end();
		testresults << "The " << i << " Times : " << time << " Sec(s)" << endl;
		i++;
	}
	
	
	testresults.close();
	testresults.open("Test_qsort_Result.txt");
	ifstream in("test_q.txt");
	
	vector<int> testvec;

	int buffer;
	while( in >> buffer) 
		testvec.push_back(buffer);
	in.close();
	
	i=1;
	while(i <= 20) {
		start();
		test_2(testvec);
		double time = end();
		testresults << "qsort test : " << time << " Sec(s)" << endl;
		i++;
	}
	testresults.close();
	ofstream q_result("qsort result.txt");
	output(testvec,q_result);
	cout << "Qsort result is showed in qsort result.txt'." << endl;
	q_result.close();
	
	testresults.open("Test_Merge_Sort_Result.txt");
	in.open("test_m.txt");
	while( in >> buffer) 
		testvec.push_back(buffer);
	in.close();
	
	i=1;
	while(i <= 20) {
		start();
		test_3(testvec);
		double time = end();
		testresults << "merge sort test : " << time << " Sec(s)" << endl;
		i++;
	}
	testresults.close();
	ofstream m_result("merge result.txt");
	output(testvec,m_result);
	cout <<"Mergesort result is showed in msort result.txt'." << endl;
	m_result.close();
	
	i=1;
	while(i<=10) {
	
		string name_in;string name_out;
		char DstBuf[3];
		itoa(i,DstBuf,10);
		name_in += DstBuf;
		name_in += ".sortin";
		name_out += DstBuf;
		name_out += ".sortout";
		in.open(name_in);
		testresults.open(name_out);
		test_5(in,testresults);
		in.close();
		testresults.close();
		i++;
	}
	
	i=1;
	while(i<=10) {
		
		string name_in;string name_out;
		char DstBuf[3];
		itoa(i,DstBuf,10);
		name_in += DstBuf;
		name_in += ".findin";
		name_out += DstBuf;
		name_out += ".findout";
		in.open(name_in);
		testresults.open(name_out);
		test_6(in,testresults);
		in.close();
		testresults.close();
		i++;
	}
	return 0 ;
 
}
