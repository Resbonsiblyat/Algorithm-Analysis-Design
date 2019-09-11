#include "pch.h"

bool cmp(Act a, Act b) {
	return a.end < b.end;
}


int greedy(std::vector<Act>& acts) {
	int N = (int)acts.size();
	int last_t = 0, sum = 0;
	sort(acts.begin(), acts.end(), cmp);

	std::vector<Act>::iterator it = acts.begin();
	while (it != acts.end()) {
		if ((*it).begin >= last_t) {
			sum = -~sum;
			last_t = (*it).end;
		}
		it++;
	}

	return sum;
}

int sum_max; std::vector<int> act_list;
void dfs(int last_t, int sum, std::vector<Act>& acts, int i, int N) {
	if (i >= N-1 && sum > sum_max)
			sum_max = sum;
	else {
		
		for (int j = i; j < N; j++) {
			if (last_t <= acts[j].begin) {
				dfs(acts[j].end, sum + 1, acts, i + 1, N);
			}
				
			//std::cout << "i: " << i << " j: " << j << std::endl;
		}
		if (sum > sum_max) sum_max = sum;
	}
		
}

int trace(std::vector<Act>& acts) {
	sum_max = 0; std::vector<int> buffer;
	act_list.swap(buffer);
	int N = (int)acts.size();
	dfs(0, 0, acts, 0, N);
	return sum_max;
}