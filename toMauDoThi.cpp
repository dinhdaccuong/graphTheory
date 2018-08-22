#include <iostream>
#include <list>
#include <map>
#include <string>
#include <fstream>
using namespace std;

#define MAX 100
#define CO  true
#define KHONG false

int secondDegree(list <int> dsKe[], int soDinh){    // ham tim dinh co bac k - 1
    int nMin = 0;       // bac nho nhat
    int nMax1 = 0;      // nMax2 la bac lon nhat
    int nMax2 = 0;      // Bac lon thu 2
    int iMin = 0;
    nMin = dsKe[0].size();  // bac nho nhat
    for(int i = 1; i < soDinh; i++){    // tim dinh co bac nho nhat
        int s = dsKe[i].size();
        if(nMin > s){
            nMin = s;
            iMin = i;
        }
    }        // dinh co bac nho nhat la iMin

    nMax1 = dsKe[0].size(); // dau tien co bac lon nhat
    nMax2 = nMin;           // bac lon thu 2 bang bac nho nhat

    int iMax1 = 0;          // dinh co bac lon nhat la 0
    int iMax2 = iMin;       // dinh co bac lon thu 2 la iMin

    for(int i = 0; i < soDinh; i++){    // vong lap xac dinh dinh co bac lon thu 2(dinh co bac k - 1)
        int s = dsKe[i].size();
        if(s > nMax1){
            nMax2 = nMax1;
            iMax2 = iMax1;
            nMax1 = s;
            iMax1 = i;
        }
        else if(s > nMax2 && s < nMax1){
            nMax2 = s;
            iMax2 = i;
        }
    }
    return iMax2;           // tra ve dinh co bac k - 1
}

void colorSequence(list <int> dsKe[], int sequence[], int first, int soDinh){     // xac dinh thu tu to mau

    // sequence mang chua thu tu to mau
    // sequence[0] = 1, sequence[1] = 4 <-> dinh 1 duoc to dau tien, dinh 4 duoc to thu 2

    bool check[MAX] = {0};          // luu chi so de kiem tra dinh nao da duoc to mau

    sequence[0] = first;          // diem dau tien duoc to mau la dinh co bac k - 1
    check[first] = CO;            // danh dau diem co bac k - 1 da duoc to mau

    int soPhanTuCuaSequence = 1;    // so phan tu cua do thi da xac dinh duoc vi tri to mau

    for(int v: dsKe[first]){      // lay cac dinh hang xong cua first them vao mang chua thu tu to mau
        sequence[soPhanTuCuaSequence] = v;
        check[v] = CO;            // danh dau dinh da duoc xac dinh thu tu to mau
        soPhanTuCuaSequence++;
    }

    int index = 1;
    while(soPhanTuCuaSequence < soDinh){     /* xac dinh thu tu to mau cac dinh con lai, bat dau tu cac dinh da duoc xac dinh
                                          thu tu to mau */
        for(int v: dsKe[sequence[index]]){  // lay cac dinh hang xong cua dinh da duoc xac dinh thu tu to mau
            if(check[v] == KHONG){      // neu dinh chua duoc xac dinh thu tu
                check[v] = CO;          // danh dau da duoc xac dinh thu tu
                sequence[soPhanTuCuaSequence] = v;  // them vao mang xac dinh thu tu
                soPhanTuCuaSequence++;
            }
        }
        index++;
    }
}

void coloring(list <int> dsKe[], int sequence[], int color[], int soDinh){      // to mau cho cac dinh da duoc xac dinh thu tu
    /* color[]: mang xac dinh dinh nao duoc to mau nao
       color[0] = 3 <-> dinh 0 duoc to mau 3
       color[1] = 2 <-> dinh 1 duoc to mau 2
    */
    /*  sequence[]: mang luu thu tu to mau duoc xac dinh bang ham colorSequence()
        sequence[0] = 1 <-> dinh 1 duoc to dau tien
        sequence[1] = 5 <-> dinh 5 duoc to thu 2
    */

        // dinh dau tien trong thu tu to mau duoc to mau 1

    bool listNotColoring[10];   // danh sach cac mau bi cam to cua dinh dang xet.
     /* listNotColoring[1] = CO <-> mau 1 khong duoc to
        listNotColoring[3] = KHONG <-> mau 3 co the duoc su dung de to
    */
    for(int i = 1; i < soDinh; i++){
        int u = sequence[i];    // dinh u chuan bi duoc to

        for(v: dsKe[u]){        // vong lap xac dinh cac mau dinh u cam to
            if(color[v] != 0)            // neu dinh v da duoc to mau
                listNotColoring[color[v]] = CO; // danh dau mau color[v] dinh u khong duoc su dung
        }

        int k = 1;
        while(listNotColoring[k] == CO){    // vong lap xac dinh mau to cho dinh u
            listNotColoring[k] = KHONG;
            k++;
        }
        color[u] = k;   // to mau cho dinh u la mau k
    }
}

void exportGraphviz( list <int> dsKe[], int color[], int soDinh){   /* xuat ra file text dong thoi in ra man hinh chuong trinh
                                                                        graphviz */
    map <int, string> mapColor;
    mapColor[1] = "red";    // mau 1 tuong ung mau red
    mapColor[2] = "blue";   // mau 2 tuong ung mau blue
    mapColor[3] = "green";  // mau 3 tuong ung mau green
    mapColor[4] = "yellow"; // ....
    mapColor[5] = "white";
    mapColor[6] = "orange";
    mapColor[7] = "gray";
    mapColor[8] = "pink";

    ofstream fileText("graph.txt"); // tao moi file .txt co ten graph.txt de ghi chuong trinh graphviz

    cout << "graph doThi" << "\n" << "{" << endl;
    fileText << "graph doThi" << "\n" << "{" << endl;

     // ghi ma graphviz vao file .txt va in ra man hinh.

    for(int i = 0; i < soDinh; i++){     // to mau cac dinh va style to mau cac dinh
        cout << "\t" << i << " [fillcolor = " << mapColor.at(color[i]) << ", style = filled];" << endl;
        fileText << "\t" << i << " [fillcolor = " << mapColor.at(color[i]) << ", style = filled];" << endl;
    }
    cout << endl;
    fileText << endl;

    for(int i = 0; i < soDinh; i++){    // cac dinh ke nhau
        for(v: dsKe[i]){
            if(i < v){      // chi in nhung dinh ke lon hon dinh dang xet
                cout << "\t" << i << " -- " << v << endl;
                fileText << "\t" << i << " -- " << v << endl;
            }
        }
    }

    cout << "}" << endl;
    fileText << "}";
    fileText.close();
}

int main(){
    int soDinh = 0;              // so dinh cua do thi
    int soCanh = 0;              // so canh cua do thi

    int dinh_1 = 0, dinh_2 = 0;  // luu cac canh tam thoi

    int sequence[MAX] = {0};     // thu tu to mau
    /*  sequence[]: mang luu thu tu to mau duoc xac dinh bang ham colorSequence()
        sequence[0] = 1 <-> dinh 1 duoc to dau tien
        sequence[1] = 5 <-> dinh 5 duoc to thu 2
    */
    int color[MAX] = {0};        // mau to cua cac dinh
    /* color[]: mang xac dinh dinh nao duoc to mau nao
       color[0] = 3 <-> dinh 0 duoc to mau 3
       color[1] = 2 <-> dinh 1 duoc to mau 2
    */

    list <int> dsKe[MAX];       // danh sach ke
    /*  dsKe[0] = {1, 2, 4, 5} <-> dinh 0 ke voi cac dinh 1, 2, 3, 4
        .......
        */
    cin >> soDinh >> soCanh;

    for(int i = 0; i < soCanh; i++){       // nhap du lieu cho do thi
        cin >> dinh_1 >> dinh_2;
        dsKe[dinh_1].push_back(dinh_2);
        dsKe[dinh_2].push_back(dinh_1);
    }




    int sDegree = secondDegree(dsKe, soDinh);   // tinh dinh co bac k - 1

    colorSequence(dsKe, sequence, sDegree, soDinh);     // tinh thu tu to mau

    coloring(dsKe, sequence, color, soDinh);    //  to mau

    exportGraphviz(dsKe, color, soDinh);    // xuat ra file chua ma graphviz va in ra man hinh ma graphviz.

    return 0;

}

