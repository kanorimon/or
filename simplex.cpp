#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

/* �萔 */
const int MAX_NO = 10;

/* ����ϐ� */
int n_cnt;
int N[MAX_NO];

/* ���ϐ� */
int b_cnt;
int B[MAX_NO];

/* �V���v���b�N�X�\ */
double xf;
double c[MAX_NO];
double b[MAX_NO];
double a[MAX_NO][MAX_NO];


/*
 * �V���v���b�N�X�\�̏o��
 * 
 * <����>
 * �����ԍ�
 */
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

/* ��i�K�ڂ̕K�v���`�F�b�N */
bool check_first_simplex(){
	for(int i=0;i<b_cnt;i++){
		if(b[B[i]] < 0){
			return true;
		}
	}
	return false;
}

/* 
 * Step1:�œK������
 *
 * <����>
 * �i�K,���[�v��
 */
bool check_optimality(int level,int cnt){
	
	if(level < 2 && cnt < 2){
		return true;
	}
	for(int i=0;i<n_cnt;i++){
		if(c[N[i]] > 0){
			return true;
		}
		//cout << "check_optimality = " << c[N[i]] << endl;
	}
	return false;
}

/* Step2:�s�{�b�g��I�� */
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

/* 
 * Step3:��L�E������ 
 *
 * <����>
 * �s�{�b�g��̓Y����,�i�K,���[�v��
 */
bool check_unbounded(int s,int level,int cnt){
	if(level <2 && cnt < 2){
		return true;
	}
	for(int i=0;i<b_cnt;i++){
		if(a[B[i]][s]*-1 > 0){
			return true;
		}
		//cout << "check_unbounded = " << a[B[i]][s]*c[s] << endl;
	}
	cout << "unbounded" << endl;
	return false;
}

/* 
 * Step4:�s�{�b�g�s�I�� 
 *
 * <����>
 * �s�{�b�g��̓Y����,�i�K,���[�v��
 */
int get_r(int s,int level,int cnt){
	int r=0;
	int mini = 100000;
	if(level < 2 && cnt < 2){
		for(int i=0;i<b_cnt;i++){
			if(b[B[i]]/a[B[i]][s] < mini){
				r = B[i];
				mini = b[B[i]]/a[B[i]][s];
			}
		}
	}else{
		for(int i=0;i<b_cnt;i++){
			if(a[B[i]][s]*-1 > 0 && b[B[i]]/a[B[i]][s]*-1 < mini){
				r = B[i];
				mini = b[B[i]]/a[B[i]][s]*-1;
			}
		}
	}
	
	//cout << "r = " << r << " " << b[r] << endl;
	return r;
}

/* 
 * Step5:�s�{�b�g���Z 
 *
 * <����>
 * �s�{�b�g�s,�s�{�b�g��
 */
void pibot(int r,int s){
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

/* 
 * �V���v���b�N�X�@ 
 *
 * <����>
 * �i�K
 */
bool simplex_method(int level){
	for(int i=1;;i++){
		
		/* �V���v���b�N�X�\�o�� */
		print_tableau(i);
		
		/* Step1:�œK������ */
		if(!check_optimality(level,i)) return false;
	
		/* Step2:�s�{�b�g��I�� */
		int s = get_s();
	
		/* Step3:��L�E������ */
		if(!check_unbounded(s,level,i)) return false;
		
		/* Step4:�s�{�b�g�s�I�� */
		int r = get_r(s,level,i);
		
		/* Step5:�s�{�b�g���Z */
		pibot(r,s);
	}
	return true;
}

int main(){
	
	/* 
	 * �����W���`�̃V���v���b�N�X�\��ǂݍ���
	 * 
	 * <���̓t�@�C���t�H�[�}�b�g>
	 * ����ϐ��̐� ���ϐ��̐�
	 * ����ϐ��̓Y����(1,2,...,n)
	 * �K��ϐ��̓Y����(n+1,n+2,...,n+m)
	 * �V���v���b�N�X�\
	 */
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
	
	/*
	 * �V���v���b�N�X�@�i��i�K�ځj
	 */
	if(check_first_simplex()){
		
		int tmpN[n_cnt];
		double tmpc[n_cnt];
		for(int i=0;i<n_cnt;i++){
			tmpN[i] = N[i];
			tmpc[N[i]] = c[N[i]];
		}
		
		N[n_cnt] = 0;
		n_cnt++;
		
		for(int i=0;i<n_cnt;i++){
			if(N[i] == 0){
				c[N[i]] = -1;
			}else{
				c[N[i]] = 0;
			}
		}
		
		for(int i=0;i<b_cnt;i++){
			a[B[i]][0] = 1;
		}
		
		simplex_method(1);
		
		if(xf < 0){
			cout << "non-executable" << endl;
			return 0;
		}
		
		for(int i=0;i<b_cnt;i++){
			if(B[i] == 0){
				for(int j=0;j<n_cnt;j++){
					if(a[B[i]][N[j]] != 0){
						pibot(B[i],N[j]);
						break;
					}
				}
				break;
			}
		}
		
		n_cnt--;
		bool minus = false;
		for(int i=0;i<n_cnt;i++){
			if(N[i] == 0 && !minus){
				N[i] = N[i+1];
				minus = true;
			}else if(minus){
				N[i] = N[i+1];
			}
		}
		
		for(int i=0;i<n_cnt;i++){
			for(int j=0;j<n_cnt;j++){
				if(N[i] == tmpN[j]){
					c[N[i]] = tmpc[tmpN[j]];
					tmpc[tmpN[j]] = 0;
					break;
				}
			}
		}
		
		for(int i=0;i<n_cnt;i++){
			if(tmpc[tmpN[i]] > 0){
				xf = b[tmpN[i]];
				for(int j=0;j<n_cnt;j++){
					c[N[j]] = c[N[j]] + a[tmpN[i]][N[j]];
				}
			}
		}
		
	}
	
	/*
	 * �V���v���b�N�X�@�i��i�K�ځj
	 */
	simplex_method(2);
	
	return 0;
}
