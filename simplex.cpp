#include <iostream>
#include <algorithm>

using namespace std;

//xx=column ,xy=row
int xx,xy;

//simplex tableau
double x[10][100];

void print_tableau(){
	
	cout << "***start" << endl;
	
	for(int i=0;i<xy;i++){
		for(int j=0;j<xx;j++){
			cout << x[i][j] << " ";
		}
		cout << endl;
	}
	
	cout << "***end" << endl;
	
}

bool check_optimality(){
	
	bool minus = false;
	for(int i=1;i<xx;i++){
		if(x[0][i] > 0){
			minus = true;
			break;
		}
		cout << "check_optimality = " << minus << " " << x[0][i] << endl;
	}
	return minus;
}

int get_pibot_column(){
	
	int pibot_column = 0;
	for(int i=1;i<xx;i++){
		if(x[0][i] > 0){
			pibot_column = i;
			break;
		}
	}
	
	cout << "pibot_column = " << pibot_column << " " << x[0][pibot_column] << endl;
	
	return pibot_column;
}


bool check_unbounded(int pibot_column){
	bool minus = false;
	for(int i=1;i<xy;i++){
		if(-1*x[i][pibot_column]*x[0][pibot_column] > 0){
			minus = true;
			break;
		}
		cout << "check_unbounded = " << minus << " " << -1*x[i][pibot_column]*x[0][pibot_column] << endl;
	}
	return minus;
}

int get_pibot_row(int pibot_column){
	int pibot_row=0;
	int mini = 100000;
	for(int i=1;i<xy;i++){
		if(x[i][pibot_column]*-1>0 && x[i][0]/x[i][pibot_column]*-1 < mini){
			pibot_row = i;
			mini = x[i][0]/x[i][pibot_column]*-1;
		}
	}

	cout << "pibot_row = " << pibot_row << " " << x[pibot_row][0] << endl;

	return pibot_row;
}

int main(){
	
	//load
	cin >> xx >> xy;
	for(int i=0;i<xy;i++){
		for(int j=0;j<xx;j++){
			cin >> x[i][j];
		}
	}
	
	print_tableau();
	
	if(!check_optimality) return 0;
	
	int pibot_column = get_pibot_column();
	
	if(!check_unbounded(pibot_column)) return 0;
	
	int pibot_row = get_pibot_row(pibot_column);
	
	cout << x[pibot_row][0]/x[pibot_row][pibot_column]*-1 << endl;
	
	return 0;
}
