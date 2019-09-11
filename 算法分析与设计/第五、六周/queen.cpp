 #include <iostream>  
#include <list>  
using namespace std;  
int count = 0;
list<int> sol;  
int n;  
int uplimit;  
  
void print()  
{  
	count++;
	cout << "µÚ" << count << "¸ö½â£º" ;
    list<int>::iterator i;  
    int c = 1;
    for(i = sol.begin(); i != sol.end(); i++)  
    {  
        int tmp = *i, cnt = 0;  
        while(tmp != 1)  
        {  
            cnt++;  
            tmp = tmp >> 1;  
        }  
        cout << "("  << c << "," << cnt+1 << ")" << " ";  
 		c++;
    }   
    cout << endl;
}  
  
void doans(int r, int ld, int rd)  
{  
    if(r != uplimit)  
    {  
  
        int pos = uplimit & ~(r | ld | rd);  
        while(pos)  
        {    
            int p = pos & -pos;  
            pos -= p;  
            sol.push_back(p);  
            doans(r + p, (ld + p) << 1, (rd + p) >> 1);  
            sol.pop_back();  
        }  
    }  
    else print();
	  
}  
  
int main()  
{  
    cin >> n;
    uplimit = (1 << n) - 1;  
    doans(0, 0, 0); 
    return 0;  
}  

