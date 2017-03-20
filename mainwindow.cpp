#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QToolTip>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    verticalLayout = new QVBoxLayout();
    centralWidget()-> setLayout(verticalLayout);

    myFrame=new QFrame ();
    verticalLayout->addWidget(myFrame);
    myFrame->setFrameShape(QFrame::Panel);

    horizontalLayout = new QHBoxLayout();
    myFrame->setLayout(horizontalLayout);


    myTextEdit= new QTextEdit ();
    verticalLayout->addWidget(myTextEdit);    

    myLabel= new QLabel("Buffer:");
    verticalLayout->addWidget(myLabel);
    myLabel1= new QLabel ();

//Создание указателей на кнопки**************************************************************************************************************************

    for (int i=0; i<6; i++)                 // Создание указателей для 6 кнопок
    {
        QToolButton *btn = new QToolButton; //Создание указателя на кнопку
        toolButton.append(btn);             // Сохранение указателей в контейнер

    }

//Создание подсказок для кнопок*******************************************************************************************************************

    stringToolTip << "Создать новый файл." << "Открыть файл." << "Закрыть файл без сохранения."<< "Сохранить." << "Вырезать выделенный фрагмент в бефер."
                  <<"Вставить из буфера." << "Закрыть файл без сохранения.";

// Закрепелние подсказок за кнопками ****************************************************************************************************

    for (int k=0; k<toolButton.length(); k++)
    {
        //toolButton[k]->setToolButtonStyle(Qt::ToolButtonIconOnly);
        toolButton[k]->setToolTip(stringToolTip[k]);
    }

//Создание контейнера с картинками из файла поддержки**************************************************************************************************

    QString icons[7] = {":/myImages/open_new.jpeg",":/myImages/open_file.jpeg",":/myImages/close_file.jpeg",":/myImages/save_file.png",
                        ":/myImages/сut_text.png",":/myImages/insert_text.jpeg"};

// Присвоение кнопкам иконок из контейнера *************************************************************************************************************

    for (int k=0; k<toolButton.length(); k++)
    {
        toolButton[k]->setToolButtonStyle(Qt::ToolButtonIconOnly);
        toolButton[k]->setIcon(QIcon(icons[k]));
    }

// Размещение кнопок на горизонтальном виджете *************************************************************************************************************

    for(int k=0; k<toolButton.length(); k++)
    {
            horizontalLayout->addWidget(toolButton.at(k));
    }

// Соединение сигнала каждой кнопки с слотом ****************************************************************************************************************

    for(int i=0; i < toolButton.length();i++ ) //В зависимости от количества кнопок в контейнере
        connect (toolButton.at(i), SIGNAL(clicked()),this, SLOT(button_clicked())); // Соединение со слотом
}

// Декремент***************************************************************************************************************

MainWindow::~MainWindow()
{
    delete ui;
}

// Слот *********************************************************************************************************************

void MainWindow :: button_clicked()
{
// Преобразование типа QObject к QToolButton, конект возвращает указатель на QObject нажатой кнопки **************************************************************************

    QToolButton *btn= dynamic_cast<QToolButton*>(sender());

// Условие сравнивает указатель полученный от QObject с указателем из контейнера с казателями на кнопки *********************************************

    for (int i=0; i < toolButton.length();i++ )
        if (btn == toolButton[i])
        {
            switch(i)
            {
                case BUTTON_NEW: //Нужно еще реализовать проверку одинаковых имен для файлов.
                {
                    if(!myTextEdit->toPlainText().isEmpty())
                    {
                        fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                   "/newDoc.txt", tr("myDoc (*.txt)"));

                        if(!fileName.isEmpty()) // Если нажата кнопка отмена файл не будет созадн, переданная строка будет пустая.
                        {
                        QFile myFile(fileName);

                        if(myFile.exists())
                        {
                            //Файл уже существует. Перезаписать?
                        }

                        if (!myFile.open(QIODevice::WriteOnly | QIODevice::Text))
                                return;
                        QByteArray strByteArray = myTextEdit->toPlainText().toUtf8();
                        myFile.write(strByteArray);
                        myFile.close();
                        }
                        myTextEdit->clear();
                    }
                    break;
                }
                case BUTTON_OPEN:
                {
                    fileName =QFileDialog::getOpenFileName(0, "Open dialog", "", "*.txt");
                    QFile myFile(fileName);
                    if (!myFile.open(QIODevice::ReadOnly | QIODevice::Text))
                            return;
                    QByteArray a;
                    a=myFile.readAll();
                    myTextEdit->setText(QString(a));
                    myFile.close();
                    break;
                }

                case BUTTON_SAVE:
                {
                    if(!myTextEdit->toPlainText().isEmpty())
                    {
                        if(!fileName.isEmpty()) // Если нажата кнопка отмена файл не будет созадн, переданная строка будет пустая.
                        {
                        QFile myFile(fileName);

                        if (!myFile.open(QIODevice::WriteOnly | QIODevice::Text))
                                return;
                        QByteArray strByteArray = myTextEdit->toPlainText().toUtf8(); //Преобразование текста в QByteArray
                        myFile.write(strByteArray);
                        myFile.close();
                        }
                        else
                        {
                            fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                       "/newDoc.txt", tr("myDoc (*.txt)"));
                            if(!fileName.isEmpty()) // Если нажата кнопка отмена файл не будет созадн, переданная строка будет пустая.
                            {
                            QFile myFile(fileName);
                            if (!myFile.open(QIODevice::WriteOnly | QIODevice::Text))
                                    return;
                            QByteArray strByteArray = myTextEdit->toPlainText().toUtf8();
                            myFile.write(strByteArray);
                            myFile.close();
                            }
                        }
                    }
                    break;
                }

                case BUTTON_CLOSE:
                {
                    fileName.clear();
                    myTextEdit->clear();
                   break;
                }

                case BUTTON_CUT:
                {
                    myTextEdit->cut();
                    break;
                }

                case BUTTON_INSERT:
                {
                    myTextEdit->paste();
                    break;
                }
            }
        }
}

//Открытие файла по умолчанию ***********************************************************************************************************************

void MainWindow::myOpenFile(QString myArgv)
{    
    if(myArgv != 0)
    {
        QFile myFile(myArgv);
        if (!myFile.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
        QByteArray a;
        //QColor b;
        a=myFile.readAll(); //Прочитать все из файла
        //myTextEdit->setTextColor(Qt::red);                //Установить красный цвет текста
        //myTextEdit->setTextBackgroundColor(Qt::green);    //Установить зеленый цвет фона текста
        myTextEdit->setText(QString(a));                  //Установить строку в textEditor, преобразование из QByteArray в QString
        myTextColor();

        myFile.close();

    }
}

void MainWindow::myTextColor()
{
    QTextDocument *document = myTextEdit->document();            //Получаем текстовый документ из текстового редактора
    QTextCharFormat colorformat = myTextEdit->currentCharFormat();
    //colorformat.setFontUnderline(true);                        //Подчеркивает шрифт
    //colorformat.setFontWeight(100);                            //Выделяет шрифт жирным
    //colorformat.setToolTip("Ссылка");                          //Создает ссылку на указанную строку
    //colorformat.setFontPointSize(30);                          //Устанавливает размер шрифта
    //colorformat.setFontOverline(true);                         //Подчеркивание сверух
    //colorformat.setFontItalic(true);                           //Курсив
    QFont myFont;
    myFont.setBold(true);
    colorformat.setFont(myFont);                                 //Выделяет шрифт жирным

    //QTextCursor newCursor(document);                             //Создает курсор указывающий на начало документа

//*******************************************************************************
                                        //  Класс QBrush определяет шаблон заполнения фигур, нарисованных QPainter

    QBrush textBrush( Qt::magenta );        // Qt::red - enum Qt::GlobalColor ((Перечисление глобальных цветов)Предопределенные объекты QColor Qt:)
                                        // Конструктор создает черную кисть по умолчанию со стилем Qt :: NoBrush (то есть эта кисть не будет заполнять фигуры).

    QVector <QBrush> multiColor(10);
    //multiColor[0]= ( Qt::magenta );
    //multiColor[1]= ( Qt::green );

// ******************************************************************************
                                                                //  Класс QPen определяет, как QPainter должен рисовать линии и контуры фигур.
                                                                // Ручка имеет стиль (), width (), brush (), capStyle () и joinStyle ().
                                                                // Различные настройки могут быть легко изменены с помощью соответствующих функций setStyle (), setWidth (), setBrush (), setCapStyle () и setJoinStyle ()

    QPen outlinePen(Qt::gray, 1);                               //Можно выкинуть весь аргумент и результат не поменяется!

//**********************************QVector <QStringList> stringColor(10);************************************************

    QTextEdit::ExtraSelection selection;    // Объявление структуры

//QVector <QStringList> stringColor(10);
    //selection.format.setForeground( multiColor[0] );
    selection.format.setForeground( textBrush );                 //Формат, используемый для указания переднего плана или фона кисти, цвета для выделения.
    selection.format.setProperty( QTextFormat::OutlinePen, outlinePen );

//**********************************************************************************
                                                                 // Структура QTextEdit :: ExtraSelection предоставляет способ указания формата символа для данного выделения в документе.


    QStringList searchString;                                    //Искомая подстрока
    searchString << "QWidget" <<"QString" << "QApplication" << "Qt" << "QLatin1String" << "MainWindow" << "Qt" << "QTextCursor" << "QFont" << "QTextEdit" << "ExtraSelection" << "OutlinePen"
                 << "QBrush" << "QTextCursor" << "QTextCharFormat" << "QPen" << "ExtraSelection" << "WordRight" << "KeepAnchor"
                 << "QByteArray" << "QFile";







//***********************************************************************************

    for(int i=0; i != searchString.length(); ++i){
        QTextCursor newCursor(document);
     while (!newCursor.isNull() && !newCursor.atEnd()) {            //Возвращает истину если курсор равен нулу, возвращает истину если курсор находится в конце документа

         newCursor = document->find(searchString[i], newCursor);    //Находит следующее вхождение подстроки в строке документа. Превый аргум. искомая подстрока

         if (!newCursor.isNull()) {
             newCursor.movePosition(QTextCursor::WordRight,      //Перемещение в право на одно слово
                                    QTextCursor::KeepAnchor);    //Оставить флаг там, где он находится


         if(newCursor.hasSelection())                            //Возвращает true, если курсор содержит выделение; В противном случае возвращает false.

         {
             newCursor.mergeCharFormat(selection.format);        //Объединяет текущий формат символа курсора со свойствами, описанными модификатором формата.

         }

         }
     }
    }







    return;
}




