#include <iostream>
#include <algorithm>

using namespace std;

//simplex tableau
double x[10][10];
double y[10][10];


//valiable
int nb_cnt;
int N[10];
int b_cnt;
int B[10];

void print_tableau(double a[10][10]){
	
	cout << "***start" << endl;
	
	cout << "     ";
	for(int i=1;i<nb_cnt;i++){
		cout << "x" << N[i] << " ";
	}
	cout << endl;
	
	for(int i=0;i<b_cnt;i++){
		if(i > 0){
			cout << "x" << B[i] << " ";
		}else{
			cout << "   ";
		}
		for(int j=0;j<nb_cnt;j++){
			cout << a[B[i]][N[j]] << " ";
		}
		cout << endl;
	}
	
	cout << "***end" << endl;
	
}

//step1
bool check_optimality(){
	
	bool minus = false;
	for(int i=1;i<nb_cnt;i++){
		if(x[0][N[i]] > 0){
			minus = true;
			break;
		}
		//cout << "check_optimality = " << minus << " " << x[0][N[i]] << endl;
	}
	return minus;
}

//step2
int get_s(){
	
	int s = 0;
	for(int i=1;i<nb_cnt;i++){
		//cout << N[i] << " " << x[0][N[i]]  << endl;
		if(x[0][N[i]] > 0){
			s = N[i];
			break;
		}
	}
	//cout << "s = " << s << " " << x[0][s] << endl;
	return s;
}

//step3
bool check_unbounded(int pibot_column){
	bool minus = false;
	for(int i=1;i<b_cnt;i++){
		if(x[B[i]][pibot_column]*-1 > 0){
			minus = true;
			break;
		}
		//cout << "check_unbounded = " << minus << " " << x[B[i]][pibot_column]*x[0][pibot_column] << endl;
	}
	return minus;
}

//step4
int get_r(int s){
	int r=0;
	int mini = 100000;
	for(int i=1;i<b_cnt;i++){
		if(x[B[i]][s]*-1 > 0 && x[B[i]][0]/x[B[i]][s]*-1 < mini){
				r = B[i];
				mini = x[B[i]][0]/x[B[i]][s]*-1;
		
		}
	}
	//cout << "r = " << r << " " << x[r][0] << endl;
	return r;
}

int main(){
	
	//load
	cin >> nb_cnt >> b_cnt;

	for(int i=0;i<nb_cnt;i++){
		cin >> N[i];
	}
	
	for(int i=0;i<b_cnt;i++){
		cin >> B[i];
	}
	
	for(int i=0;i<b_cnt;i++){
		for(int j=0;j<nb_cnt;j++){
			cin >> x[B[i]][N[j]];
		}
	}
	
	for(int k=0;k<5;k++){
		print_tableau(x);
	
		//step1
		if(!check_optimality()) return 0;
	
		//step2
		int s = get_s();
	
		if(!check_unbounded(s)) return 0;
		
		int r = get_r(s);
	
		//print_tableau(x);
	
	
		double tmpN[10];
		double tmpB[10];
		int tmp_nb_i;
		int tmp_b_i;
		
		for(int i=1;i<nb_cnt;i++){
			if(N[i] == s){
				for(int j=0;j<b_cnt;j++){
					tmpN[j] = x[B[j]][s];
				//	cout << s << " " <<  B[j] << " " << tmpN[j] << endl;
				}
				tmp_nb_i = i;
				break;
			}
		}

		for(int i=1;i<b_cnt;i++){
			if(B[i] == r){
				for(int j=0;j<b_cnt;j++){
					tmpB[j] = x[r][N[j]];
					//	cout << r << " " <<  N[j] << " " << tmpB[j] << endl;
				}
				tmp_b_i = i;
				break;
			}
		}
	
		N[tmp_nb_i] = r;
		B[tmp_b_i] = s;
		
		double val = x[r][s]*-1.0;
		
		for(int i=0;i<b_cnt;i++){
			for(int j=0;j<nb_cnt;j++){
				//cout << B[i] << " " << N[j] << " ";
				
				if(B[i]==s){
					if(j==0){
					//	cout << x[r][0] << "/" << val;
						x[B[i]][N[j]] = x[r][0]/val;
					//	cout << " = " << x[B[i]][N[j]]<< endl;
					}else if(N[j]==r){
					//	cout << "-1*1/" << val;
						x[B[i]][N[j]] =  -1.0*1.0/val;
					//	cout << " = " << x[B[i]][N[j]]<< endl;
						
					}else{
					//	cout << "-1*" << x[r][N[j]] << "/" << val;
						x[B[i]][N[j]] =  -1.0*x[r][N[j]]*-1/val;
					//	cout << " = " << x[B[i]][N[j]]<< endl;
					}
				}else if(N[j]==r){
					if(i==0){
					//	cout << "-1*1/" << val << "*" << x[0][s];
						x[B[i]][N[j]] =  -1.0*1.0/val*x[0][s];
					//	cout << " = " << x[B[i]][N[j]]<< endl;
					}else if(B[i]==s){
					//	cout << "-1*1/" << val;
						x[B[i]][N[j]] =  -1.0*1.0/val;
					//	cout << " = " << x[B[i]][N[j]]<< endl;
						
					}else{
					//	cout << "1/" << val << "/" << x[B[i]][s];
						x[B[i]][N[j]] =  1.0/val*x[B[i]][s]*-1;
					//	cout << " = " << x[B[i]][N[j]]<< endl;
					}
				}else{
					//cout << endl;
				
					if(j==0){
					//cout << x[B[i]][N[j]] << " > " << x[B[i]][N[j]]  << " + " << x[r][N[j]] << " / " << x[r][s]*-1 << " * " << x[B[i]][s] << endl;
						x[B[i]][N[j]] = x[B[i]][N[j]] + x[r][N[j]]/val*x[B[i]][s];
					}else{
					//cout << x[B[i]][N[j]] << " > " << x[B[i]][N[j]]  << " - " << x[r][N[j]]*-1 << " / " << x[r][s]*-1 << " * " << x[B[i]][s] << endl;
						x[B[i]][N[j]] = x[B[i]][N[j]] - x[r][N[j]]*-1.0/val*x[B[i]][s];
					}
				}
					
				
			}
		}
	}
	
	print_tableau(x);
	
	
	return 0;
}
