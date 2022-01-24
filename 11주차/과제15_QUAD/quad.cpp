#include <iostream>
#include <string>
#include <cmath>

using namespace std;

#define MAX 64
void quad_input();
void QTS2IMG(int,int,int);
void IMG2QTS(int,int,int);
void quad_output();

int K;
int LENGTH;
int IMG[MAX][MAX];
string TYPE;
string QTS;

int main(){
    quad_input();

    if (TYPE == "QTS") QTS2IMG(0,0,LENGTH);

    else if (TYPE == "IMG") IMG2QTS(0,0,LENGTH);

    quad_output();

    return 0;
} // end of main()

void quad_input(){

    cin >> K;
    LENGTH = pow(2,K);

    cin >> TYPE;

    string tmp;
    if (TYPE == "QTS") cin >> QTS;

    else if (TYPE == "IMG"){
        for (int i = 0; i < LENGTH; i++){
            cin >> tmp;
            for (int j = 0; j < LENGTH; j++){
                IMG[i][j] = tmp[j]-'0';
            }
        }
    }
} // end of quad_input()

void QTS2IMG(int myX, int myY, int myL){
    if (QTS.back()==')'){
            QTS.pop_back();
            QTS2IMG(myX+myL/2,myY+myL/2,myL/2);
            QTS2IMG(myX,myY+myL/2,myL/2);
            QTS2IMG(myX,myY,myL/2);
            QTS2IMG(myX+myL/2,myY,myL/2);
    }
    else {
        for (int i = myY; i < myY+myL; i++){
            for (int j = myX; j < myX+myL; j++){
                IMG[i][j] = QTS.back()-'0';
            }
        }
    }
    QTS.pop_back();
} // end of QTS2IMG()

void IMG2QTS(int myX, int myY, int myL){
    bool isCloud = false;
    int firstNum = IMG[myY][myX];
    for (int i = myY; i < myY+myL; i++)
        for (int j = myX; j < myX+myL; j++)
            if (IMG[i][j] != firstNum) {isCloud = true; break;}

    if (isCloud){
        QTS += '(';
        IMG2QTS(myX+myL/2,myY,myL/2);
        IMG2QTS(myX,myY,myL/2);
        IMG2QTS(myX,myY+myL/2,myL/2);
        IMG2QTS(myX+myL/2,myY+myL/2,myL/2);
        QTS += ')';
    }
    else QTS += firstNum + '0';
} // end of IMG2QTS()

void quad_output(){
    if (TYPE=="QTS"){
        for (int i = 0; i < LENGTH; i++){
            for (int j = 0; j < LENGTH; j++){
                cout << IMG[i][j];
            }
            cout << endl;
        }
    }
    else if (TYPE=="IMG"){
            cout << QTS << endl;
    }
} // end of quad_output()
