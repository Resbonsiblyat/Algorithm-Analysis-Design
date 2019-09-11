#include <bits/stdc++.h>
using namespace std;
int main()
{
	int k = 1;
	while(k <= 10){
	string name;
	char *dstbuf;
	itoa(k,dstbuf,10);
	name += dstbuf;
	name += ".sortin";
	ofstream out;
	out.open(name);
	int i = 1 , j = 1;
	default_random_engine e(time(0));
	while(i < 1500*k)
	{
	out << e() << " ";i++;
	}
		
	
	out << endl;
	out.close();
	k++;
	}
	return 0;
}
