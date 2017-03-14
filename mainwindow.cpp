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

    QTextCursor newCursor(document);                             //Создает курсор указывающий на начало документа


    QBrush textBrush( Qt::red );
    QPen outlinePen( Qt::gray, 1 );

    QTextEdit::ExtraSelection selection;
    //selection.newCursor = QTextCursor(document());

    //selection.format.setBackground( backBrush );
    selection.format.setForeground( textBrush );
    selection.format.setProperty( QTextFormat::OutlinePen, outlinePen );



    QString searchString="MainWindow::MainWindow(QWidget *parent) :"; //Искомая подстрока

     while (!newCursor.isNull() && !newCursor.atEnd()) {         //Возвращает истину если курсор равен нулу, возвращает истину если курсор находится в конце документа
         newCursor = document->find(searchString, newCursor);    //Находит следующее вхождение подстроки в строке документа. Превый аргум. искомая подстрока

         if (!newCursor.isNull()) {
             newCursor.movePosition(QTextCursor::WordRight,    //Перемещение в право на одно слово
                                    QTextCursor::KeepAnchor);  //Оставить флаг там, где он находится


         if(newCursor.hasSelection())
         {

             newCursor.mergeCharFormat(selection.format);
            //newCursor.mergeCharFormat(colorformat);  //Обьединяет текущий формат символов со свойствами модификатора формата. Если курсор выделил текст, эта функция прменяет все свойства установленные в модификаторе  для всех форматов символов в выделении.
            //newCursor.mergeCharFormat(myModifier.setUnderlineColor(QColor(0, 255, 0)));

         }

         }
     }







    //return str;
}




/*
 *class FixedQPlainTextEdit : public QPlainTextEdit // I guess the name tells you everything :)
{
public:
    FixedQPlainTextEdit( QWidget* parent = 0 ) : QPlainTextEdit( parent ) {}

protected:
    void    paintEvent( QPaintEvent* e )
    {
        QPaintEvent* fixed_event = new QPaintEvent( e->rect().adjusted( -1, -1, 0, 0 ) ); // left and top edge need to be adjusted by -1
        QPlainTextEdit::paintEvent( fixed_event );
        delete fixed_event;
    }
};

// below is your example code using the FixedQPlainTextEdit class
MainWindow::MainWindow( QWidget* p )
    :
    QMainWindow( p )
{
    QPlainTextEdit* e = new FixedQPlainTextEdit();
    e->appendPlainText( "#include <QtGui/QApplication>" );
    e->appendPlainText( "#include \"mainwindow.h\"" );
    e->appendPlainText( "" );
    e->appendPlainText( "int main(int argc, char *argv[])" );
    e->appendPlainText( "{" );
    e->appendPlainText( "    QApplication a(argc, argv);" );
    e->appendPlainText( "    MainWindow w;" );
    e->appendPlainText( "    w.show();" );
    e->appendPlainText( "" );
    e->appendPlainText( "    return a.exec();" );
    e->appendPlainText( "}" );

    this->setCentralWidget( e );

    QList<QTextEdit::ExtraSelection> extraSelections;

    QBrush backBrush( Qt::yellow );
    QBrush textBrush( Qt::black );
    QPen outlinePen( Qt::gray, 1 );
    QString highlighText = "QApplication";

    for( int i=0; i<e->document()->blockCount(); i++ )
    {
        QTextBlock block = e->document()->findBlockByNumber( i );
        if( block.isValid() )
        {
            QString text = block.text();
            int p;

            if( (p=text.indexOf(highlighText)) != -1 )
            {
                int pos = block.position() + p;

                QTextEdit::ExtraSelection selection;
                selection.cursor = QTextCursor(e->document());
                selection.cursor.setPosition( pos );
                selection.cursor.setPosition( pos+highlighText.length(), QTextCursor::KeepAnchor );
                selection.format.setBackground( backBrush );
                selection.format.setForeground( textBrush );
                selection.format.setProperty( QTextFormat::OutlinePen, outlinePen );

                extraSelections.append( selection );
            }
        }
    }

    e->setExtraSelections( extraSelections );
}

 */

