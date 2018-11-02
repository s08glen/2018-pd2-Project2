#include "pressed.h"
#include <QDebug>
#include<iostream>
#include<cstdlib>
#include<QString>

using namespace std;

int sudoku[81] ={0};                                //數獨題目陣列
int shownumber[81]={0},numbercolor[81];
int tempNum[81] ;                               // 上一次填數位置
int tempSp= 0 ;                                 // 上一次填數位置指標
int startH[81] ;                                // 列位置的起點
int startV[81] ;                                // 行位置的起點
int startB[81] ;                                // 九宮格位置的起點
int addH[9] ;                                   // 列位置的加值
int addV[9] ;                                   // 行位置的加值
int addB[9] ;


void pressed::main() {
    init() ;                                     // 參數設定
    tryAns() ;                                   // 測試求解
 }
void pressed::init() {
       // 參數設定
       int i ;
       for(i=0; i<81; i++) {
          startH[i]= i/9* 9 ;                       // 列位置的起點
          startV[i]= i% 9 ;                         // 行位置的起點
          startB[i]= ((i/9)/3)*27+ ((i%9)/3)*3 ;    // 九宮格位置的起點
       }
       for(i=0; i<9; i++) {
          addH[i]= i ;                              // 列位置的加值
          addV[i]= i*9 ;                            // 行位置的加值
          addB[i]= (i/3)*9+ (i%3) ;                 // 九宮格位置的加值
       }
    }
void pressed::tryAns() {
       // 測試求解
       int sp=getNextBlank(-1) ;                    // 取得第一個空白的位置開始填入數字
       do {
          sudoku[sp]++ ;                            // 將本位置數字加 1
          if(sudoku[sp]>9) {                        // 如果本位置的數字已大於 9 時則回到上一個位置繼續測試
             sudoku[sp]= 0 ;
             sp= pop() ;
          } else {
             if(check(sp)==0) {                     // 如果同行、列、九宮格都沒有相同的數字，則到下一個空白處繼續
                push(sp) ;                          // 當然，如果發現有相同的數字時，就需把原位置的數字加 1(所以本處什麼都不做)
                sp= getNextBlank(sp) ;
             }
          }
       } while(sp>=0 && sp<81) ;
    }
int pressed::getNextBlank(int sp) {
       // 取得下一個空白的位置
       do {
          sp++ ;
       } while(sp<81 && sudoku[sp]>0) ;
       return(sp) ;
    }
int pressed::check(int sp) {
       // 檢查同行、列、九宮格有沒有相同的數字，若有傳回 1
       int fg= 0 ;
       if(!fg) fg= check1(sp, startH[sp], addH) ;   // 檢查同列有沒有相同的數字
       if(!fg) fg= check1(sp, startV[sp], addV) ;   // 檢查同行有沒有相同的數字
       if(!fg) fg= check1(sp, startB[sp], addB) ;   // 檢查同九宮格有沒有相同的數字
       return(fg) ;
    }
int pressed::check1(int sp, int start, int *addnum) {
       // 檢查指定的行、列、九宮格有沒有相同的數字，若有傳回 1
       int fg= 0, i, sp1  ;
       for(i=0; i<9; i++) {
          sp1= start+ addnum[i] ;
          if(sp!=sp1 && sudoku[sp]==sudoku[sp1]) fg++ ;
       }
       return(fg) ;
    }
void pressed::push(int sp) {
       // 將指定的位置放入堆疊中
       tempNum[tempSp++]= sp ;
    }
int pressed::pop() {
    // 取出堆疊中的上一個位置
    if(tempSp<=0) return(-1) ;
    else return(tempNum[--tempSp]) ;
 }

pressed::pressed(QWidget* parent) : QPushButton (parent){
    show();
    connect(this,SIGNAL(clicked()),this ,SLOT(press()));
    setFont(QFont("Ubuntu",16));
}
void pressed::generate(int ii, int jj){
    if(((ii<6&&ii>2)||(jj<6&&jj>2)) && (!((ii<6&&ii>2)&&(jj<6&&jj>2))))
            setStyleSheet("background-color:#E6E6FA;");
    else
        setStyleSheet("background-color:#FFEBCD;");    
    setText(" ");
    setGeometry(QRect(QPoint(66.6*ii, 66.6*jj), QSize(66.6,66.6)));

    i = ii;
    j = jj;
}
void pressed::generatenull(int ii, int jj){
    if(((ii<6&&ii>2)||(jj<6&&jj>2)) && (!((ii<6&&ii>2)&&(jj<6&&jj>2))))
            setStyleSheet("background-color:#E6E6FA;");
    else
        setStyleSheet("background-color:#FFEBCD;");
    setText(" ");
    setGeometry(QRect(QPoint(66.6*ii, 66.6*jj), QSize(66.6,66.6)));

    i = ii;
    j = jj;
}

void pressed::press(){
    //qDebug()<<i<<"   "<<j;
    if(((i<6&&i>2)||(j<6&&j>2)) && (!((i<6&&i>2)&&(j<6&&j>2))))
            setStyleSheet("background-color:#7B68EE	;");
    else
        setStyleSheet("background-color:#FF9900;");
    disconnect(this,SIGNAL(clicked()),this ,SLOT(dispress()));
    disconnect(this,SIGNAL(clicked()),this ,SLOT(press()));
    connect(this,SIGNAL(clicked()),this ,SLOT(dispress()));

}

void pressed::dispress(){
    if(((i<6&&i>2)||(j<6&&j>2)) && (!((i<6&&i>2)&&(j<6&&j>2))))
            setStyleSheet("background-color:#E6E6FA;");
    else
        setStyleSheet("background-color:#FFEBCD;");

    disconnect(this,SIGNAL(clicked()),this ,SLOT(dispress()));
    disconnect(this,SIGNAL(clicked()),this ,SLOT(press()));
    connect(this,SIGNAL(clicked()),this ,SLOT(press()));
}
void pressed::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_0){
        setText(" ");
    }
    if(event->key()==Qt::Key_Space){
        setText(" ");
    }
    else if(event->key()==Qt::Key_1){
        setText("1");
    }
    else if(event->key()==Qt::Key_2){
        setText("2");
    }
    else if(event->key()==Qt::Key_3){
        setText("3");
    }
    else if(event->key()==Qt::Key_4){
        setText("4");
    }
    else if(event->key()==Qt::Key_5){
        setText("5");
    }
    else if(event->key()==Qt::Key_6){
        setText("6");
    }
    else if(event->key()==Qt::Key_7){
        setText("7");
    }
    else if(event->key()==Qt::Key_8){
        setText("8");
    }
    else if(event->key()==Qt::Key_9){
        setText("9");
    }
    if(((i<6&&i>2)||(j<6&&j>2)) && (!((i<6&&i>2)&&(j<6&&j>2))))
            setStyleSheet("background-color:#E6E6FA;color:#0000EF");
    else
        setStyleSheet("background-color:#FFEBCD;color:#0000EF");
}
/*if(((i<6&&i>2)||(j<6&&j>2)) && (!((i<6&&i>2)&&(j<6&&j>2))))
        setStyleSheet("background-color:#E6E6FA;color:#0000EF;");
else
    setStyleSheet("background-color:#FFEBCD;color:#0000EF;");*/
void pressed::getnumber(int i,int j){
    QString numberstr = text();
    sudoku[j*9+i]=numberstr.toInt();
}
void pressed::gettempnumber(int i,int j){
    QString numberstr = text();
    shownumber[j*9+i]=numberstr.toInt();
}

void pressed::topicanswer(int i,int j){
    int val=sudoku[j*9+i];
    //qDebug()<<val;
    if(val!=0){
        QString str;
        str.setNum(val);
        setText(str);}
    else{
        setText(" ");
    }
}
void pressed::topic(){
    int a;
    for(int ii=0;ii<81;ii++){
        shownumber[ii]=sudoku[ii];        
    }
    //for(int i=0;i<81;i++){qDebug()<<shownumber[i];}
    srand(time(NULL));
    for(int ii=0;ii<50;ii++){
        a=(rand() % 81)+0;
        shownumber[a]=0;
    }
    for(int ii=0;ii<81;ii++){
        //numbercolor[ii]==shownumber[ii];
    }
}
void pressed::display(int i,int j){
    int val=shownumber[j*9+i];

        if(shownumber[9*j+i]==0){
            if(((i<6&&i>2)||(j<6&&j>2)) && (!((i<6&&i>2)&&(j<6&&j>2))))
                    setStyleSheet("background-color:#E6E6FA;color:#0000EF");
            else
                setStyleSheet("background-color:#FFEBCD;color:#0000EF");
        }
        else{
            if(((i<6&&i>2)||(j<6&&j>2)) && (!((i<6&&i>2)&&(j<6&&j>2))))
                    setStyleSheet("background-color:#E6E6FA;color:black");
            else
                setStyleSheet("background-color:#FFEBCD;color:black");
        }

    if(val!=0){
        QString str;
        str.setNum(val);
        setText(str);
    }
    else{
        setText(" ");
    }
}
