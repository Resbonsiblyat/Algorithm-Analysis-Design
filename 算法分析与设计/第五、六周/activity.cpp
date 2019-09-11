#include <bits/stdc++.h>
using namespace std;

struct activity {
	int begin,end;
};

bool cmp (activity a, activity b) {
	return a.end < b.end;
}

int main() {
	int n;
	int last_t = 0 , sum = 0;
	vector<activity> activities;
	cout << "输入任务个数： " << endl;
	cin >> n;
	cout << "输入每项任务的开始时间和结束时间: " << endl;
	while(n--) {
		activity buffer;
		cin >> buffer.begin >> buffer.end;
		activities.push_back(buffer);
	}
	sort(activities.begin(),activities.end(),cmp);
	
	vector<activity>:: iterator it = activities.begin();
	cout << "任务顺序：";
	while( it != activities.end()) {
		if((*it).begin >= last_t) {
			sum=-~sum;
			last_t = (*it).end;
			cout << (int)(it - activities.begin()) + 1 << " ";
		}
		it++;
	}
	cout << endl << "兼容任务总数： " << sum << endl; 
	return 0; 
} 
