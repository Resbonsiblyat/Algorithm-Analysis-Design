#include "pch.h"
std::vector<Act> getTestData(int N) {
	std::vector<Act> testData;
	cv::RNG rng;
		for (int i = 1; i <= N; i++) {
			int begin = rng.uniform(0, 5000);
			int end = rng.uniform(0, 5000);
			Act  buffer_act;
			buffer_act.begin = end > begin ? begin : end;
			buffer_act.end = end > begin ? end : begin;
			testData.push_back(buffer_act);
		}
		return testData;
}


double test(std::string testFunction, std::vector<Act>& testData) {
	if (testFunction == "trace") {
		double time0 = cv::getTickCount();
		std::cout << "Trace :" << trace(testData) << std::endl;
		return (cv::getTickCount() - time0)/ cv::getTickFrequency();
	}
		

	else if (testFunction == "greedy") {
		double time0 = cv::getTickCount();
		std::cout<< "Greedy:" << greedy(testData) << std::endl;
		return (cv::getTickCount() - time0) / cv::getTickFrequency();
	}

	else return -1;
}

void drawLine(cv::Mat img, cv::Point start, cv::Point end, int B, int G, int R, std::string coordinate) {
	int thickness = 1;
	int linetype = 8;
	cv::line(img, start, end, cv::Scalar(B, G, R), thickness, linetype);
	cv::circle(img, end, 2, cv::Scalar(B, G, R), thickness+1, linetype);
	cv::putText(img, coordinate, end, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(B, G, R), 0.02);
}

void drawLine(cv::Mat img, cv::Point start, cv::Point end, int B, int G, int R) {
	int thickness = 1;
	int linetype = 8;
	cv::line(img, start, end, cv::Scalar(B, G, R), thickness, linetype);
	cv::circle(img, end, 2, cv::Scalar(B, G, R), thickness + 1, linetype);
}

void draw(std::vector<double>& time_t, std::vector<double>& time_g) {
	cv::Mat img1(800, 1200, CV_8UC3, cv::Scalar::all(0));
	double x0 , y0;

	//Draw Axis

	std::vector<double>::iterator it = time_t.begin();
	x0 = 10; y0 = *it; it++; //Initialize
	cv::Point buf1(x0, -y0 * 10 + 500);
	cv::circle(img1, buf1, 5, cv::Scalar(255, 255, 0), 2, 8);
	int count = 15;
	std:: string buffer1 = "(";
	buffer1 += std::to_string(count) + "," + std::to_string(y0);
	buffer1.resize(buffer1.size()-4);
	buffer1 += ")";
	cv::putText(img1, buffer1, buf1, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 0), 0.02);
	cv::putText(img1, "TRACE", cv::Point(x0 + 100, -y0 * 50 + 550), cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(255, 255, 0), 1);
	for (;it!=time_t.end();it++) {
		count += 15;
		buffer1 = "(";
		double x = 130 + x0 , y = *it;
		cv::Point S(x0, -y0*10+500);
		cv::Point E(x, -y*10+500);
		buffer1 += std::to_string(count) + "," + std::to_string(y);
		buffer1.resize(buffer1.size() - 4);
		buffer1 += ")";
		if (y != 0)
			drawLine(img1, S, E, 255, 255, 0, buffer1);
		else
			drawLine(img1, S, E, 255, 255, 0);
		x0 = x; y0 = y;
	}
	count = 15;
	it = time_g.begin();
	x0 = 10; y0 = *it; it++;
	cv::Point buf2(x0, -y0 * 10 + 500);
	cv::circle(img1, buf2, 5, cv::Scalar(255, 0, 255), 2, 8);
	std::string buffer2 = "(";
	buffer2 += std::to_string(count) + "," + std::to_string(y0);
	buffer2.resize(buffer2.size() - 4);
	buffer2 += ")"; 
	cv::putText(img1, buffer2, buf2, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 0, 255), 0.02);
	cv::putText(img1, "GREEDY", cv::Point(x0+100, -y0*50 + 450), cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(255, 0, 255), 1);
	for (; it != time_g.end(); it++) {
		count += 15;
		double x = 130 + x0, y = *it;
		cv::Point S(x0, -y0*10+500);
		cv::Point E(x, -y*10+500);
		buffer2 = "(";
		buffer2 += std::to_string(count) + "," + std::to_string(y);
		buffer2.resize(buffer2.size() - 4);
		buffer2 += ")";
		if (y != 0)
			drawLine(img1, S, E, 255, 0, 255, buffer2);
		else
			drawLine(img1, S, E, 255, 0, 255);
		x0 = x; y0 = y;
	}

	cv::imshow("时间复杂度对比图", img1);
	cv::waitKey();
	return;
}