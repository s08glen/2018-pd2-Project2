#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>

extern int sudoku[81],show[81];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this ,SLOT(button_pressed()));
    ui->progressBar->hide();
    ui->pushButton->hide();
    ui->test->hide();
    srand(time(NULL));

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){

           square[i][j] = new pressed(ui->frame);
           square[i][j]->generate(i,j);
        }
    }

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
           for(int k=0;k<9;k++){
               for(int m=0;m<9;m++){
                     if(k!=i || m!=j){
                         connect(square[i][j],SIGNAL(clicked()),square[k][m] ,SLOT(dispress()));
                     }
               }
           }
        }
    }

    connect(ui->user,SIGNAL(clicked()),this ,SLOT(generatenull()));
    connect(ui->newgame,SIGNAL(clicked()),this ,SLOT(newgame()));
    connect(ui->answer,SIGNAL(clicked()),this ,SLOT(answer()));
    connect(ui->hide,SIGNAL(clicked()),this ,SLOT(hide()));
    connect(ui->answernew,SIGNAL(clicked()),this ,SLOT(answernew()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->progressBar->setValue(ui->progressBar->value()+2);
}
void MainWindow::on_test_clicked()
{
    ui->progressBar->setValue(ui->progressBar->value()+4);
}

void MainWindow::button_pressed(){
    //qDebug()<<ui->progressBar->value();
}

void MainWindow::generatenull(){

    ui->solvetext->setText("  ");
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
           square[i][j]->setText(" ");
        }
    }
    ui->answer->hide();
    ui->hide->show();
    ui->answernew->show();

}
void MainWindow::newgame(){
    ui->answer->show();
    ui->hide->hide();
    ui->answernew->hide();
    //generatenull();
    srand(time(NULL));
    int a[9];
    for(int i=0;i<9;i++){
         a[i]=(rand() % 9) +1;
         for(int j=0;j<i;j++){
             if(a[i]== a[j])i--;
         }
    }
    for(int i=0;i<9;i++){
        sudoku[i]=a[i];
        //qDebug()<<sudoku[i*10];
    }
    for(int i=9;i<81;i++){
        sudoku[i]=0;
        //qDebug()<<sudoku[i*10];
    }
   // for(int i=0;i<9;i++){qDebug()<<sudoku[i];}
    square[0][0]->main();

    for(int i=0;i<81;i++){
        if(sudoku[i]==0){
            square[0][0]->main();
        }
    }
    square[0][0]->topic();
    //for(int i=0;i<81;i++){qDebug()<<sudoku[i];}
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){               
               square[i][j]->display(i,j);
            }
        }
    //for(int i=0;i<81;i++){qDebug()<<sudoku[i];}qDebug()<<endl<<endl;
}
void MainWindow::answer(){
    ui->solvetext->setStyleSheet("color:red");
    ui->solvetext->setText("This is Answer~");
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            square[i][j]->gettempnumber(i,j);
            square[i][j]->topicanswer(i,j);
        }
    }
    ui->answer->hide();
    ui->hide->show();
}
void MainWindow::answernew(){
    ui->answer->hide();
    ui->hide->show();
    ui->solvetext->setStyleSheet("color:red");
    ui->solvetext->setText("  ");
//for(int i=0;i<81;i++){qDebug()<<sudoku[i];}qDebug()<<endl;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
          square[i][j]->getnumber(i,j);
          square[i][j]->gettempnumber(i,j);
        }
    }
    for(int i=0;i<81;i++){
        //qDebug()<<sudoku[i];
    }
    int cp1=0,cp2=0,wrong=0,okay=0,wrong1=0,okay1=0,wrong2=0,okay2=0;
    for(int a=0;a<9;a++){
        for(int k=9*a;k<9*a+8;k++){
             cp1=sudoku[k];
             for(int m=k+1;m<9*a+9;m++){
                 cp2=sudoku[m];
                 if(cp1!=0 && cp2!=0){
                     if(cp1==cp2){
                          wrong++;
                     }
                     else{
                         okay++;
                     }
                 }
            }
        }
    }
   // for(int i=0;i<9;i++){qDebug()<<sudoku[9*i];}
    int compare[9],b[9]={0,9,18,27,36,45,54,63,72},bb=0,cm1=0,cm2=0;
    for(int kk=0;kk<9;kk++){
        for(int i=0;i<9;i++){
            bb=b[i];
            compare[i]=sudoku[bb];
        }
        for(int k=0;k<8;k++){
            cm1=compare[k];
            for(int m=k+1;m<9;m++){
                cm2=compare[m];
                if(cm1!=0 && cm2!=0){
                    //qDebug()<<cm1<<cm2;
                    if(cm1==cm2){
                        wrong1++;
                    }
                    else{
                        okay1++;
                    }
                }
            }
        }
        for(int i=0;i<9;i++){
            b[i]+=1;
        }
     }

    int a[9]={0,1,2,9,10,11,18,19,20},aa=0;
    for(int y=0;y<3;y++){
        for(int kk=0;kk<3;kk++){
            for(int k=0;k<9;k++){
                aa=a[k];
                compare[k]=sudoku[aa];
            }
            for(int k=0;k<8;k++){
                cm1=compare[k];
                for(int m=k+1;m<9;m++){
                    cm2=compare[m];
                    if(cm1!=0 && cm2!=0){
                        //qDebug()<<cm1<<cm2;
                        if(cm1==cm2){
                            wrong2++;
                        }
                        else{
                            okay2++;
                        }
                    }
                }
            }
            for(int k=0;k<9;k++){
                a[k]=a[k]+3;
            }
        }
        for(int x=0;x<9;x++){
            a[x]=a[x]+18;
        }

    }

    //qDebug()<<wrong<<wrong1<<wrong2;
    if(wrong==0 && wrong1==0 &&wrong2==0){
        square[8][8]->main();
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
             square[i][j]->topicanswer(i,j);
            }
        }
        ui->solvetext->setText("This is Answer~");
    }
    else{
        ui->solvetext->setStyleSheet("color:red");
        ui->solvetext->setText("Some of your inputs are Wrong!!");
    }


}

void MainWindow::hide(){    
    ui->solvetext->setText(" ");
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
           square[i][j]->display(i,j);
        }
    }
    ui->answer->show();
    ui->hide->hide();
}
