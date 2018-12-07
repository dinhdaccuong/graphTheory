#include <iostream>
#include <set>
using namespace std;
#define MAX 100
/*Dinh Dac Cuong CNTT 1.1 - K60 Dai hoc Bach Khoa Ha Noi*/
void compressTree(int tree[], int n, int pruferCode[]){			// ham thuc hien nen cay
	int degree[MAX];	// mang luu tru bac cua moi nhan degree[1] = 2 <-> nhan 1 co bac 2

	
	set <int> labelDegree_1;	// mang luu cac nhan bac co bac 1
	set <int> :: iterator it;
	
	degree[0] = 0;				// 0 la goc.
	for(int i = 1; i < n; i++){	// cac nhan con lai cua cay co bac it nhat bang 1
		degree[i] = 1;			
	}
	
	for(int i = 1; i < n; i++){		// tinh bac cua tung nhan luu vao mang degree
		degree[tree[i]]++; 
	}
	
	for(int i = 0; i < n; i++){		// luu cac nhan bac 1 vao labelDegree_1
		if(degree[i] == 1)
			labelDegree_1.insert(i);
	}
	int currentLable;			// nhan dang xet
	for(int i = 0; i < n - 2; i++){			
		it = labelDegree_1.begin();				// iterator tro vao phan tu dau tien nho nhat trong cac nhan bac 1
		currentLable = *it;						// gan gia tri cua iterator vao currentLabel
		labelDegree_1.erase(it);				// xoa phan tu vua lay ra trong labelDegree
		pruferCode[i] = tree[currentLable];		// luu cha cua currentLabel vao pruferCode
		degree[tree[currentLable]]--;			// giam bac nut cha cua currentLabel di 1 sau khi currentLabel bi xoa.
		if(degree[tree[currentLable]] == 1 && tree[currentLable] != 0)	labelDegree_1.insert(tree[currentLable]);	// neu nut cha cua currentLabel co bac bang 1 
																													// thi no la la
	}
}

void printPruferCode(int pruferCode[], int n){		// in pruferCode.
	int n2 = n - 2;
	for(int i = 0; i < n2; i++)
		cout << pruferCode[i] << " ";
}

int main(){
	int tree[MAX];		// mang luu du lieu cua cay
						
	int pruferCode[MAX];	// mang luu pruferCode
					
	int n;					// so phan tu cua cay
	int dinh_1, dinh_2;		// bien trung gian de nhap du lieu cho cay.
	
	cin >> n;				// nhap so dinh cua cay		

	for(int i = 1; i < n; i++){		// nhap danh sach canh
		cin >> dinh_1 >> dinh_2;
		tree[dinh_2] = dinh_1;		// dinh_1 la cha dinh_1
	}
	cout << endl;
	
	compressTree(tree, n, pruferCode);		// thuc hien nen cay
	printPruferCode(pruferCode, n);		// in cay
	cout << endl;
}
