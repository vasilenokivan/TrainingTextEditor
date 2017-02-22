#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QLineEdit>


namespace Ui {
class InputDialog;
}

class InputDialog : public QDialog
{
    Q_OBJECT
private:
    QLineEdit* m_ptxtFirstName;
    QLineEdit* m_ptxtLastName;

public:
    InputDialog(QWidget* pwgt=0);

    QString firstName () const;
    QString lastName () const;


public:
    explicit InputDialog(QWidget *parent = 0);
    ~InputDialog();

private:
    Ui::InputDialog *ui;











};
#endif //_InputDialog_h_

#endif // MAINWINDOW_H










};

#endif // INPUTDIALOG_H
