// ACT.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
	vector<double> time_t;
	vector<double> time_g;
	/*for (int N = 15; N <= 120; N += 15) {
		vector<Act> testData = getTestData(N);

		//for (Act buffer : testData)
		//	cout << buffer.begin << " " << buffer.end << endl;

		double t;
		cout << "SUM:" << N << endl;
		t = test("trace", testData);
		time_t.push_back(t);
		cout << "Trace :" << t << endl;
		t = test("greedy", testData);	
		time_g.push_back(t);
		cout << "Greedy:" << t << endl;
		cout << endl;


   }*/

	//draw(time_t, time_g);
	vector<Act> testData = getTestData(10000000);
	double t = test("greedy", testData);
	cout << "N = 10000000 , Time used: " << t << endl;
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
