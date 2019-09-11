	#include <bits/stdc++.h>
	using namespace std;
	#define length 4
	// length here
	double m[length][length] = {{9,2,7,8},
					{6,4,3,7},
					{5,8,1,8},
					{7,6,9,4}};
	double source[length][length]; 
	bool rowAppoint();	bool colAppoint();	bool isOptimal(); void updataM();
	void printM(){
		cout << "---------------" << endl;
		for(int i = 0;i < length;i ++){
			for(int j = 0;j < length;j ++)
				cout << m[i][j] << " ";
			cout << endl;
		}
	}
	
	void printResult(){
		double time = 0;
		cout<< "-----Result------" << endl;
		for(int i = 0;i < length;i ++)
			for(int j = 0;j < length;j ++)
				if(m[i][j] == -1){
					cout << i+1 << "--" << j+1 << ", ";
					
					time += source[i][j];
				}
		cout << endl;		
		cout << "time : " << time << endl;
	}
					
	 void appoint(){
		int N = length;
		//行规约
		for(int i = 0;i < N;i ++){
			double min = 2147483647;
			for(int j = 0;j < N;j ++){
				if(m[i][j] < min)
					min = m[i][j];
			}
			for(int j = 0;j < N;j ++)
				m[i][j] -= min;
		}
		//列规约
		for(int j = 0;j < N;j ++){
			double min = 2147483647;
			for(int i = 0;i < N;i ++){
				if(m[i][j] < min)
					min = m[i][j];
			}
			if(min == 0)
				continue;
			for(int i = 0;i < N;i ++)
				m[i][j] -=min;
		}
		
		printM();
		
		//进行试分配
		while(true){
			bool zeroExist = true;
			while(zeroExist){
				zeroExist = false;
				if(rowAppoint())
					zeroExist = true;
				if(colAppoint())
					zeroExist = true;
				printM();
			}
			//判断是否达到最优分配
			if(isOptimal())
				break;
			
			//变换矩阵
			updataM();
			
			//将0元素恢复
			for(int i = 0;i < N;i ++){
				for(int j = 0;j < N;j ++)
					if(m[i][j]<0)
						m[i][j] = 0;
			}
			
			printM();
		}
	}
	
	void updataM(){
		int N = length;
		//记录行、列是否打钩
		bool rowIsChecked[N];
		bool colIsChecked[N];
		//给没有被圈的行打钩
		for(int i = 0;i < N;i ++){
			for(int j = 0;j < N;j ++){
				if(m[i][j] == -1){
					rowIsChecked[i] = false;
					break;
				}else{
					rowIsChecked[i] = true;
				}
			}
		}
		
		bool isChecked = true;
		
		while(isChecked){
			isChecked = false;
			
			//对所有打钩行的0元素所在列打钩
			for(int i = 0;i < N;i ++){
				if(rowIsChecked[i]){
					for(int j = 0;j < N;j ++){
						if(m[i][j]==-2 && !colIsChecked[j]){
							colIsChecked[j] = true;
							isChecked = true;
						}
					}
				}
			}
			//对打钩列上的独立零元素行打钩
			for(int j = 0;j < N;j ++){
				if(colIsChecked[j]){
					for(int i = 0;i < N;i ++){
						if(m[i][j] == -1 && !rowIsChecked[i]){
							rowIsChecked[i] = true;
							isChecked = true;
						}
					}
				}
			}
		}
 
		//寻找盖零线以外最小的数
		double min = 2147483647;
		for(int i = 0;i < N;i ++){
			if(rowIsChecked[i]){
				for(int j = 0;j < N;j ++){
					if(!colIsChecked[j]){
						if(m[i][j] < min)
							min = m[i][j];
					}
				}			
			}
		}
		
		//打钩各行减去min
		for(int i=0;i < N;i ++){
			if(rowIsChecked[i]){
				for(int j = 0;j < N;j ++){
					if(m[i][j] > 0)
						m[i][j] -= min;
				}
			}
		}
		
		//打钩各列加上min
		for(int j=0;j < N;j ++){
			if(colIsChecked[j]){
				for(int i = 0;i < N;i ++){
					if(m[i][j] > 0)
						m[i][j] += min;
				}
			}
		}		
				
	}
	
	//统计被圈起来的0数量,判断是否找到最优解
	bool isOptimal(){
		int count = 0;
		for(int i = 0;i < length;i ++){
			for(int j = 0;j < length;j ++)
				if(m[i][j] == -1)
					count ++;
		}
		return count==length;
	}
	
	//寻找只有一个0元素的行，将其标记为独立0元素（-1），对其所在列的0元素画叉（-2）
	//若存在独立0元素返回true
	bool rowAppoint(){
		bool zeroExist = false; 
		int N = length;
		//寻找只有一个0元素的行（列）
		for(int i = 0;i < N;i ++){
			int zeroCount = 0;
			int colIndex = -1;
			for(int j = 0;j < N;j ++){
				if(m[i][j]==0){
					zeroCount ++;
					colIndex = j;
					zeroExist = true;
				}
			}
			//将独立0元素标记为-1(被圈起来)，对应的列上的零标记为-2(被划去)
			if(zeroCount == 1){
				m[i][colIndex] = -1;
				for(int k = 0;k < N;k ++){
					if(k == i)
						continue;
					else if(m[k][colIndex] == 0)
						m[k][colIndex] = -2;
				}
			}else if(zeroCount == 2){//如果存在2组解，随机选择其一标记，解决多解问题
				if(rand()%1001/1000 > 0.95){
					m[i][colIndex] = -1;
					for(int k = 0;k < N;k ++){
						if(k == i)
							continue;
						else if(m[k][colIndex] == 0)
							m[k][colIndex] = -2;
					}
					for(int j = 0;j < N;j ++){
						if(j == colIndex)
							continue;
						else if(m[i][j] == 0)
							m[i][j] = -2;
					}
				}
			}
		}
		return zeroExist;
	}
	//寻找只有一个0元素的列，将其标记为独立0元素（-1），对其所在行的0元素画叉（-2）
	//若存在独立0元素返回true
	bool colAppoint(){
		bool zeroExist = false; 
		int N = length;
		for(int j = 0;j < N;j ++){
			int zeroCount = 0;
			int rowIndex = -1;
			for(int i = 0;i < N;i ++){
				if(m[i][j]==0){
					zeroCount ++;
					rowIndex = i;
					zeroExist = true;
				}
			}
			if(zeroCount == 1){
				m[rowIndex][j] = -1;
				for(int k = 0;k < N;k ++){
					if(k == j)
						continue;
					else if(m[rowIndex][k] == 0)
						m[rowIndex][k] = -2;
				}
			}
		}
		return zeroExist;
	}
		


	int main() {
		
		memcpy(*source , *m , sizeof(m));
		appoint();
		
		printResult();
	}


