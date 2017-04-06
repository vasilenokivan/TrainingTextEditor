#include "mainwindow.h"
#include "ui_mainwindow.h"

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
                    //QString myStr;
                    //myStr= myTextEdit->canPaste();
                    //myLabel1->setText(myStr);

                }


                case BUTTON_INSERT:
                {
                    //if(QTextEdit::canPaste())
                        myTextEdit->paste();
                }

            }
        }

}





