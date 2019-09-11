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
		//�й�Լ
		for(int i = 0;i < N;i ++){
			double min = 2147483647;
			for(int j = 0;j < N;j ++){
				if(m[i][j] < min)
					min = m[i][j];
			}
			for(int j = 0;j < N;j ++)
				m[i][j] -= min;
		}
		//�й�Լ
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
		
		//�����Է���
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
			//�ж��Ƿ�ﵽ���ŷ���
			if(isOptimal())
				break;
			
			//�任����
			updataM();
			
			//��0Ԫ�ػָ�
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
		//��¼�С����Ƿ��
		bool rowIsChecked[N];
		bool colIsChecked[N];
		//��û�б�Ȧ���д�
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
			
			//�����д��е�0Ԫ�������д�
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
			//�Դ����ϵĶ�����Ԫ���д�
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
 
		//Ѱ�Ҹ�����������С����
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
		
		//�򹳸��м�ȥmin
		for(int i=0;i < N;i ++){
			if(rowIsChecked[i]){
				for(int j = 0;j < N;j ++){
					if(m[i][j] > 0)
						m[i][j] -= min;
				}
			}
		}
		
		//�򹳸��м���min
		for(int j=0;j < N;j ++){
			if(colIsChecked[j]){
				for(int i = 0;i < N;i ++){
					if(m[i][j] > 0)
						m[i][j] += min;
				}
			}
		}		
				
	}
	
	//ͳ�Ʊ�Ȧ������0����,�ж��Ƿ��ҵ����Ž�
	bool isOptimal(){
		int count = 0;
		for(int i = 0;i < length;i ++){
			for(int j = 0;j < length;j ++)
				if(m[i][j] == -1)
					count ++;
		}
		return count==length;
	}
	
	//Ѱ��ֻ��һ��0Ԫ�ص��У�������Ϊ����0Ԫ�أ�-1�������������е�0Ԫ�ػ��棨-2��
	//�����ڶ���0Ԫ�ط���true
	bool rowAppoint(){
		bool zeroExist = false; 
		int N = length;
		//Ѱ��ֻ��һ��0Ԫ�ص��У��У�
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
			//������0Ԫ�ر��Ϊ-1(��Ȧ����)����Ӧ�����ϵ�����Ϊ-2(����ȥ)
			if(zeroCount == 1){
				m[i][colIndex] = -1;
				for(int k = 0;k < N;k ++){
					if(k == i)
						continue;
					else if(m[k][colIndex] == 0)
						m[k][colIndex] = -2;
				}
			}else if(zeroCount == 2){//�������2��⣬���ѡ����һ��ǣ�����������
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
	//Ѱ��ֻ��һ��0Ԫ�ص��У�������Ϊ����0Ԫ�أ�-1�������������е�0Ԫ�ػ��棨-2��
	//�����ڶ���0Ԫ�ط���true
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


