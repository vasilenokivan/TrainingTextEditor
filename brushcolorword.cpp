#include "brushcolorword.h"

brushColorWord::brushColorWord()
{
    selection.format.setForeground(Qt::black);                 //Формат, используемый для указания переднего плана или фона кисти, цвета для выделения.
    //selection.format.setProperty( QTextFormat::OutlinePen, outlinePen );
    colorString[0] = "#include";
}


brushColorWord::brushColorWord(Qt::GlobalColor color, const QStringList & myColorString )
{
    //textBrush(color);
    colorString = myColorString;
    QPen outlinePen(Qt::gray, 1);                               //Можно выкинуть весь аргумент и результат не поменяется!
    selection.format.setForeground(color);                 //Формат, используемый для указания переднего плана или фона кисти, цвета для выделения.
    selection.format.setProperty( QTextFormat::OutlinePen, outlinePen );
}

/*
void brushColorWord::setTextBrush(Qt::GlobalColor color)
{
   textBrush(color);
}
*/

void brushColorWord::setColorCursor(QTextDocument * myDocument)
{



        for(int i=0; i != colorString.length(); ++i){

            QTextCursor newCursor(myDocument);
            while (!newCursor.isNull() && !newCursor.atEnd()) {            //Возвращает истину если курсор равен нулу, возвращает истину если курсор находится в конце документа

             newCursor = myDocument->find(colorString[i], newCursor);    //Находит следующее вхождение подстроки в строке документа. Превый аргум. искомая подстрока

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





/*
QBrush brushColorWord::getTextBrush()
{
    return (textBrush());
}

QString brushColorWord::getColorString()
{
    return(colorString);
}
*/


