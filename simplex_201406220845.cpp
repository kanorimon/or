#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

//constant
const int MAX_NO = 10;

//valiable
int n_cnt;
int N[MAX_NO];
int b_cnt;
int B[MAX_NO];

//simplex tableau
double xf;
double c[MAX_NO];
double b[MAX_NO];
double a[MAX_NO][MAX_NO];

void print_tableau(int no){
	
	cout << "(D_" << no << ")" << endl;
	
	cout << "                 ";
	for(int i=0;i<n_cnt;i++){
		cout << setw(7) << right << "x" << N[i];
	}
	cout << endl;
	
	cout << "         ";
	cout << setw(8) << right << xf;
	
	for(int i=0;i<n_cnt;i++){
		cout << setw(8) << right << c[N[i]];
	}

	cout << endl;
	for(int i=0;i<b_cnt;i++){
		cout <<  setw(8) << right << "x" << B[i];
		cout <<  setw(8) << right << b[B[i]];
		for(int j=0;j<n_cnt;j++){
			cout <<  setw(8) << right << a[B[i]][N[j]];
		}
		cout << endl;
	}
	
	cout << endl;
}

//step1
bool check_optimality(){
	
	bool minus = false;
	for(int i=0;i<n_cnt;i++){
		if(c[N[i]] > 0){
			minus = true;
			break;
		}
	//	cout << "check_optimality = " << minus << " " << c[N[i]] << endl;
	}
	return minus;
}

//step2
int get_s(){
	
	int s = 0;
	for(int i=0;i<n_cnt;i++){
		//cout << N[i] << " " << x[0][N[i]]  << endl;
		if(c[N[i]] > 0){
			s = N[i];
			break;
		}
	}
	//cout << "s = " << s << " " << c[s] << endl;
	return s;
}

//step3
bool check_unbounded(int pibot_column){
	bool minus = false;
	for(int i=0;i<b_cnt;i++){
		if(a[B[i]][pibot_column]*-1 > 0){
			minus = true;
			break;
		}
	//	cout << "check_unbounded = " << minus << " " << a[B[i]][pibot_column]*c[pibot_column] << endl;
	}
	return minus;
}

//step4
int get_r(int s){
	int r=0;
	int mini = 100000;
	for(int i=0;i<b_cnt;i++){
		if(a[B[i]][s]*-1 > 0 && b[B[i]]/a[B[i]][s]*-1 < mini){
				r = B[i];
				mini = b[B[i]]/a[B[i]][s]*-1;
		}
	}
	//cout << "r = " << r << " " << b[r] << endl;
	return r;
}

int main(){
	
	/* load */
	cin >> n_cnt >> b_cnt;
	
	for(int i=0;i<n_cnt;i++){
		cin >> N[i];
	}
	
	for(int i=0;i<b_cnt;i++){
		cin >> B[i];
	}
	
	cin >> xf;
	
	for(int i=0;i<n_cnt;i++){
		cin >> c[N[i]];
	}
	
	for(int i=0;i<b_cnt;i++){
		cin >> b[B[i]];
		for(int j=0;j<n_cnt;j++){
			cin >> a[B[i]][N[j]];
		}
	}
	
	/* simplex method */
	int no = 0;
	while(true){
		
		/* print tableau */
		print_tableau(++no);
		
		/* step1 */
		if(!check_optimality()) return 0;
	
		/* step2 */
		int s = get_s();
	
		/* step3 */
		if(!check_unbounded(s)) return 0;
		
		/* step4 */
		int r = get_r(s);
		
		/* step5 */
		
		for(int i=0;i<n_cnt;i++){
			if(N[i] == s){
				N[i] = r;
				break;
			}
		}

		for(int i=0;i<b_cnt;i++){
			if(B[i] == r){
				B[i] = s;
				break;
			}
		}
		
		double ars = a[r][s] * -1.0;
		
		xf = xf + b[r] / ars * c[s];
		
		for(int j=0;j<n_cnt;j++){
			if(N[j]==r){
				c[N[j]] = -1.0 * 1.0 / ars * c[s];
			}else{
				c[N[j]] = c[N[j]] - (a[r][N[j]] * -1.0 / ars * c[s]);
			}
		}
		
		for(int i=0;i<b_cnt;i++){
			if(B[i]==s){
				b[B[i]] = b[r] / ars;
			}else{
				b[B[i]] = b[B[i]] - (b[r] / ars * a[B[i]][s] * -1.0);
			}

			for(int j=0;j<n_cnt;j++){
				if(B[i]==s){
					if(N[j]==r){
						a[B[i]][N[j]] = -1.0 * 1.0 / ars;
					}else{
						a[B[i]][N[j]] = -1.0 * a[r][N[j]] * -1.0 / ars;
					}
				}else if(N[j]==r){
					if(B[i]==s){
						a[B[i]][N[j]] = -1.0 * 1.0 / ars;
					}else{
						a[B[i]][N[j]] = 1.0 / ars * a[B[i]][s] * -1.0;
					}
				}else{
					a[B[i]][N[j]] = -1.0 * ( a[B[i]][N[j]] * -1.0 - (a[r][N[j]] * -1.0 / ars * a[B[i]][s] * -1.0));
				}
			}
		}
	}
	
	print_tableau(no);
	
	
	return 0;
}
