#include "inputdialog.h"
#include "ui_inputdialog.h"

InputDialog::InputDialog(QWidget *parent) :
    : QDialog(pwgt, Qt::WindowTitleHint |Qt::WindowSystemMenuHint),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);



        m_ptxtFirstName= new QLineEdit();
        m_ptxtLastName= new QLineEdit();

        QLabel* plblFirstName= new QLabel("&Firet Name");
        QLabel* plblLastName= new QLabel("&Last Name");

        plblFirstName->setBuddy(m_ptxtFirstName);
        plblLastName->setBuddy(m_ptxtLastName);

        QPushButton* pcmdOk= new  QPushButton ("Ok");
        QPushButton* pcmdCancel= new  QPushButton ("Cancel");

        connect(pcmdOk, SIGNAL(clicked()), SLOT(accept()));
        connect(pcmdCancel, SIGNAL(clicked()), SLOT(reject()));

        QGridLayout* ptopLayout= new QGridLayout;
        ptopLayout->addWidget(plblFirstName, 0, 1);
        ptopLayout->addWidget(plblLastName, 1, 0);
        ptopLayout->addWidget(m_ptxtFirstName, 0, 1);
        ptopLayout->addWidget(m_ptxtLastName, 1, 1);
        ptopLayout->addWidget(pcmdOk, 2, 0);
        ptopLayout->addWidget(pcmdCancel, 2, 1);
        centralWidget()-> setLayout(ptopLayout);

}

InputDialog::~InputDialog()
{
    delete ui;
}
