#ifndef BRUSHCOLORWORD_H
#define BRUSHCOLORWORD_H
#include <QBrush>
#include <QPen>
#include <QTextEdit>
#include <QTextCursor>
#include <QTextFormat>

class brushColorWord
{
public:
    brushColorWord();
    brushColorWord(Qt::GlobalColor color, const QStringList & myColorString );

    void setTextBrush(Qt::GlobalColor color);
    void setColorString(const QStringList & myColorString);
    //QBrush getTextBrush();
    //QString getColorString();

    //void searchString();
    void setColorCursor(QTextDocument * myDocument);

private:
    QBrush textBrush(Qt::GlobalColor);
    QStringList colorString;
    QTextEdit::ExtraSelection selection;   // Объявление структуры
};

#endif // BRUSHCOLORWORD_H
