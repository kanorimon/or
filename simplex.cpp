#include <iostream>
#include <algorithm>

using namespace std;

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
	}
	return minus;
}

int get_entering_variable(){
	
	int pibot = 0;
	for(int i=1;i<xx;i++){
		if(x[0][i] > 0){
			pibot = i;
			break;
		}
	}
	
	cout << "pibot = " << pibot << " " << x[0][pibot] << endl;
	
	return pibot;
}

int main(){
	
	//xx=�ϐ��̐� ,xy=�ړI�֐��̐�+��������̐�
	int xx,xy;
	cin >> xx >> xy;
	
	//�ǂݍ���
	for(int i=0;i<xy;i++){
		for(int j=0;j<xx;j++){
			cin >> x[i][j];
		}
	}
	
	//���݂̎�������ʕ\��
	print_tableau();
	
	//�œK������
	if(!check_optimality) return 0;
	
	//�s�{�b�g��I��
	int pibot_row = get_entering_variable();
	
	/*
	minus = false;
	for(int i=1;i<7;i++){
		if(x[4-3][pibot] > 0){
			pibot = i;
			minus = true;
		}
	}
	*/
	
	
	return 0;
}

