#ifndef PRESSED_H
#define PRESSED_H
#include <QPushButton>
#include <QKeyEvent>

class pressed : public QPushButton
{
    Q_OBJECT
public :
    pressed(QWidget* parent);
    void generate(int i,int j);
    void generatenull(int i,int j);
    void keyPressEvent(QKeyEvent *event);
    int i,j;

    void init();
    void tryAns();
    int getNextBlank(int);
    int check(int);
    int check1(int,int,int *);
    void push(int);
    int pop();
    void main();
    void topic();
    void topicanswer(int,int);
    void getnumber(int,int);
    void gettempnumber(int,int);
    void display(int,int);    
public slots:
    void press();
    void dispress();

};

#endif // PRESSED_H
