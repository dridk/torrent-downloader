#include "connectbar.h"

ConnectBar::ConnectBar(QWidget *parent)
    :QToolBar(parent)
{
    mHostEdit = new QLineEdit;
    mUserEdit = new QLineEdit;
    mPasswordEdit = new QLineEdit;
    mConnectButton = new QPushButton(QIcon(":/icons/connect.png"),"Connect");

    mHostEdit->setPlaceholderText("Host");
    mUserEdit->setPlaceholderText("Username");
    mPasswordEdit->setPlaceholderText("Password");

    mHostEdit->setText("10.67.70.16");
    mUserEdit->setText("ionadmin");
    mPasswordEdit->setText("ionadmin");


    addWidget(mHostEdit);
    addSeparator();
    addWidget(mUserEdit);
    addSeparator();
    addWidget(mPasswordEdit);

    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    addWidget(empty);

    addWidget(mConnectButton);

    connect(mConnectButton,SIGNAL(clicked()),this,SIGNAL(connectClicked()));
}

 QString ConnectBar::host() const
{
    return mHostEdit->text();
}

 QString ConnectBar::user() const
{
    return mUserEdit->text();
}

 QString ConnectBar::pass() const
{
return mPasswordEdit->text();
}

