#include<bits/stdc++.h>
#include "merge.h"
#include "usual_solve.h"
using namespace std;

vector<vector<int>> test;
void readnum() {
	ifstream input;
	for(int i=1;i<=10;i++){
		char DstBuf[3];
		itoa(i,DstBuf,10);
		
		string name;
		name += DstBuf;
		name += ".in";
		input.open(name);

		int buffer;
		vector<int> buf;
		while(input >> buffer) buf.push_back(buffer);
		test.push_back(buf);
		input.close();
	}
	input.close();
}

void test1() {
	ofstream out("merge subseq.out");
	for(int i = 0; i < 10; i++) {
		vector<int> vec (test[i]);
		double time;
		start();
		findSumofSubseq_m(vec,0,vec.size()-1);
		time = end();
		out << time << "sec(s)" << endl;
	}
	out.close();
}

void test2() {
	ofstream out("usual subseq.out");
	for(int i = 0; i < 10; i++) {
		vector<int> vec = test[i];
		double time;
		start();
		findSumofSubseq_u(vec);
		time = end();
		out << time << "sec(s)" << endl;
	}
	out.close();
}

void test3() {
	ofstream out("merge reversOrder.out");
	for(int i = 0; i < 10; i++) {
		vector<int> buf = test[i];
		int vec[buf.size()];
		for(int j=0;j<buf.size();j++) vec[j] = buf[j];
		double time;
		start();
		count(vec,0,buf.size()-1);
		time = end();
		out << time << "sec(s)" << endl;
	}
	out.close();
}

void test4() {
	ofstream out("usual reversOrder.out");
	for(int i = 0; i < 10; i++) {
		vector<int> vec = test[i];
		double time;
		start();
		reverseOrder_u(vec);
		time = end();
		out << time << "sec(s)" << endl;
	}
	out.close();
}

int main() 
{
	int a[] = {4,6,8,10,12,14};
	vector<int> v1(a,a+6);
	int b[] = {2,5,7,9,11,15};
	vector<int> v2(b,b+6);
	int c[] = {-2,6,-1,5,4,-7,2,3};
	vector<int> v3(c,c+8);
	int d[] = {3,7,5,6,4,1,2};
	vector<int> v4(d,d+7);
	double time;
	start();
	float result = findMedian(v1,v2);
	time = end();
	cout << "result: " << result << endl;
	cout << "Time using :" << time << endl;
	
	cout << "Sum of subseq(merge) : " << findSumofSubseq_m(v3,0,v3.size()-1) << endl;
	cout << "Sum of subseq(usual) : " << findSumofSubseq_u(v3) << endl;
	cout << "reverse order of seq : " << reverseOrder_u(v4) << endl;
	cout << "reverse order of seq(merge) : " << count(d,0,6) << endl;
	readnum();
	cout << test.size() << endl;
	test1(); 
	cout << "done" << endl;
	test2();
	cout << "done" << endl;
	test3();
	cout << "done" << endl;
	test4();
	cout << "done" << endl;
	return 0;
}
