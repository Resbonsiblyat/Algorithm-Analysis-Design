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
	cout << "������������� " << endl;
	cin >> n;
	cout << "����ÿ������Ŀ�ʼʱ��ͽ���ʱ��: " << endl;
	while(n--) {
		activity buffer;
		cin >> buffer.begin >> buffer.end;
		activities.push_back(buffer);
	}
	sort(activities.begin(),activities.end(),cmp);
	
	vector<activity>:: iterator it = activities.begin();
	cout << "����˳��";
	while( it != activities.end()) {
		if((*it).begin >= last_t) {
			sum=-~sum;
			last_t = (*it).end;
			cout << (int)(it - activities.begin()) + 1 << " ";
		}
		it++;
	}
	cout << endl << "�������������� " << sum << endl; 
	return 0; 
} 
