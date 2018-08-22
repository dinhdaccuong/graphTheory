#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <map>

using namespace std;

#define soDong 5757
#define soDinh 5757
#define voCung 6000

bool visited[soDinh];       // danh dau cac dinh da duo tham
list <int> dsKeA[soDong];    // danh sach ke cua do thi
list <int> dsKeB[soDong];
list <string> data;         // luu du lieu doc tu file duLieuMau.txt
map <int, int> mapDFS;
set <int> tpLienThong[soDinh];

int  num = -1;
int prevw[soDinh];
int post[soDinh];

int clock = 1;

struct cmp{
    bool operator() (int a,int b){
        return a > b;
    }
};
set <int, cmp> sequenceDFS;

void previsit(int v){
   clock = clock + 1;
}
void postvist(int v){
    sequenceDFS.insert(clock);
    mapDFS[clock] = v;
    clock = clock + 1;
}

void explore(list <int> dsKe[], int d, int vertex){ // d = 0, tinh so thanh phan lien thong cua do thi vo huong
                                                    // d = 1, duyet DFS do thi co huong
                                                    // d = 2, tinh so thanh phan lien thong cua do thi co huong
    visited[vertex] = true;     // dinh vertex da duoc tham
    if(d == 1)
        previsit(vertex);

    for(int v: dsKe[vertex]){
        if(!visited[v]){
            explore(dsKe, d, v);
        }
    }

    if(d == 1)
        postvist(vertex);

    else if(d == 2)
            tpLienThong[num].insert(vertex);
}

void loadData(string nameDI){
    fstream f;
    f.open(nameDI, ios :: in);
    string line;                // luu tung dong cua file duLieuMau.txt

    while(!f.eof()){
        getline(f, line);
        if(line.length() > 5)
            cout << "dinh dac cuong" << endl;
        data.push_back(line);
    }

    f.close();
}

int convertWordToVertex(string word){
    int index = 0;
    for(string s: data){
        if(word == s){
            return index;
        }
    index++;
    }
    if(index == soDinh)
        return -1;
}

void path(list <int> dsKe[], string word1, string word2){
    queue <int> Q;
    int paths[soDinh];
    int parents[soDinh];

    for(int i = 0; i < soDinh; i++){
        paths[i] = voCung;
    }

    /* di tu w1 den w2*/
    int w1 = convertWordToVertex(word1);
    int w2 = convertWordToVertex(word2);

    paths[w1] = 0;  // di tu w1 den w1 co quang duong bang 0;
    parents[w1] = w1; // cha cua w1 la chinh no
    Q.push(w1);
    if(w1 == -1 || w2 == -1){
        cout << endl;
        cout << "Khong ton tai u hoac v !" << endl;
        return;
    }
    bool exit = true;
    while(exit && !Q.empty()){
        int u = Q.front();  Q.pop();
        for(int v: dsKe[u]){
            if(paths[v] == voCung){         // neu quang duong tu v den w1 bang vo cung
                paths[v] = paths[u] + 1;    // tang quang duong tu v den w1 len 1
                Q.push(v);                   // them v vao hang doi
                parents[v] = u;
            }
            if(v == w2){
                exit = false;
                break;
            }
        }
    }

    if(paths[w2] == voCung)
        cout << "Khong co duong di tu " << word1 << " den " << word2 << endl;
    else{
        stack <int> S;
        list <string> :: iterator iter;
        S.push(w2);
        int p = parents[w2];
        while(p != parents[p]){
            S.push(p);
            p = parents[p];
        }
        S.push(p);
        int k = 0;
        while(!S.empty()){
            int index = S.top(); S.pop();
            int i = 0;
            iter = data.begin();
            while(i < index){
                iter++;
                i++;
            }
            k++;
            if(k == 1)
                cout << *iter;
            else
                cout << " -> " << *iter;
        }
    }
}

bool compareA(string s1, string s2){       // kiem tra chuoi s1 va s2 co khac nhau 1 vi tri hay khong
    int countc = 0;

    for(int i = 0; i < s1.length(); i++){
        if(s1[i] != s2[i])
            countc++;
    }
    if(countc == 1)
        return true;
    else return false;
}

bool compareB(string word1, string word2){
    bool check[5];
    int i = 0;
    int countn = 0;
    for(char c1: word1.substr(1, 5)){
        int i = 0;
        for(char c2: word2){
            if(!check[i] && c1 == c2){
                countn++;
                check[i] = true;
                break;
            }
            i++;
        }
    }
    if(countn == 4)
        return true;
    else
        return false;
}

void setDSKe(){     // thiet lap danh sach ke cua do thi
    string s1, s2;
    int vertex1 = 0, vertex2 = 0;     // dinh cua do thi
    for(list <string> :: iterator iter1 = data.begin(); iter1 != data.end();){
        s1 = *iter1;
        vertex2 = vertex1 + 1;
        for(list <string> :: iterator iter2 = ++iter1; iter2 != data.end(); iter2++){
            s2 = *iter2;
            if(compareA(s1, s2)){
                dsKeA[vertex1].push_back(vertex2);
                dsKeA[vertex2].push_back(vertex1);
            }
            if(compareB(s1, s2))
                dsKeB[vertex1].push_back(vertex2);
            if(compareB(s2, s1))
                dsKeB[vertex2].push_back(vertex1);

            vertex2++;
        }
        vertex1++;
    }
}

int countTPLienThongA(){         // tinh so thanh phan lien thong cua do thi
    int cc = 0;
    for(int i = 0; i < soDinh; i++){
        if(!visited[i]){
            cc = cc + 1;
            explore(dsKeA, 0, i);
        }
    }
    return cc;
}

void DFS(){
    clock = 1;
    list <int> dsKeNguoc[soDong];
    for(int i = 0; i < soDinh; i++){
        for(int v: dsKeB[i])
            dsKeNguoc[v].push_back(i);
    }
    for(int i = 0; i < soDinh; i++){
        visited[i] = false;
    }

    for(int i = 0; i < soDinh; i++){
        if(!visited[i])
            explore(dsKeNguoc, 1, i);
    }
}

int countTPLienThongB(){
    for(int i = 0; i < soDinh; i++)
        visited[i] = false;

    num = -1;
    for(int s: sequenceDFS){
        int v = mapDFS[s];
        if(!visited[v]){
            num = num + 1;
            explore(dsKeB, 2, v);
        }
    }
    return num + 1;

}

void tpLT(string word){
    int v = convertWordToVertex(word);
    if(v == -1){
        cout << endl;
        cout << "Khont ton tai v !" << endl;
        return;
    }
    bool exit = true;
    int i = 0;
    list <string> :: iterator iter;
    while(exit && i++ < num + 1){
        if(tpLienThong[i].find(v) != tpLienThong[i].end()){
            int pre = 0;
            int iMax = 0;
            iter = data.begin();
            for(int next: tpLienThong[i]){
                int index = 0;
                iMax = next - pre;
                while(index++ < iMax){
                    iter++;
                }
                cout << *iter << " ";
                pre = next;
            }
            exit = false;
        }
    }

}
int main(){

    cout << "Wait..." << endl;
    loadData("duLieuMau.txt");
    setDSKe();

    cout << "A. So thanh phan lien thong cua do thi vo huong: " << countTPLienThongA() << endl;
    DFS();
    cout << "B. So thanh phan lien thong cua do thi co huong: " << countTPLienThongB() << endl;

    cout << "A. Duong di tu u den v tren do thi vo huong: " << endl;
    char s;
    string u, v;
    do{
        cout << "\t" << "Nhap u: ";
        getline(cin, u);
        cout << "\t" << "Nhap v: ";
        getline(cin, v);
        path(dsKeA, u, v);
        cout << endl;
        cout << "Chon y de thuc hien voi tu khac, tiep tuc chon phim bat ki: ";
        cin >> s;
        fflush(stdin);
    }
    while(s == 'y' || s == 'Y');

    string str;
    cout << endl;
    cout << "B. Cac tu cung thanh phan lien thong voi dinh s." << endl;
    do{
        cout << "\t" << "Nhap s: ";
        fflush(stdin);
        getline(cin, str);
        tpLT(str);
        cout << endl;
        cout << "Chon y de thuc hien voi tu khac, tiep tuc chon phim bat ki: ";
        cin >> s;
      }
    while(s == 'y' || s == 'Y');

    fflush(stdin);
    cout << endl;
    cout << "B. Duong di tu u den v tren do thi co huong: " << endl;
    do{
        cout << "\t" << "Nhap u: ";
        getline(cin, u);
        cout << "\t" << "Nhap v: ";
        getline(cin, v);
        path(dsKeB, u, v);
        cout << endl;
        cout << "Chon y de thuc hien voi tu khac, tiep tuc chon phim bat ki: ";
        cin >> s;
        fflush(stdin);
    }
    while(s == 'y' || s == 'Y');

    return 0;
}
