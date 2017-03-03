#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QFrame>
#include <QList>
#include <QtWidgets>
#include <QToolTip>
#include <QFileDialog>
#include <QTextEdit>
#include <QClipboard>
#include <iostream>
#include <QIODevice>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QColor>
using namespace std;



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    typedef enum {
        BUTTON_NEW = 0,
        BUTTON_OPEN,
        BUTTON_CLOSE,
        BUTTON_SAVE,
        BUTTON_CUT,
        BUTTON_INSERT
    }BUTTON_T;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QFrame *myFrame;
    QList<QToolButton*> toolButton;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QTextEdit *myTextEdit;
    QList<QString> s, stringToolTip;
    QLabel *myLabel;
    QLabel *myLabel1;
    QToolButton *btn;
    QFileDialog *newFileDialog;
    QFile *myNewFile;
    QString str;
    QString fileName;                 // В строке хранится путь к файлу с которым сейчас работаю
    QStringList strListFileName;
    QString icons[6];
    //QString myArgument;
    void myOpenFile (QString myArgv);
    void myTextColor();



private:
    Ui::MainWindow *ui;


public slots:
    void button_clicked();

};

#endif // MAINWINDOW_H
