#include "connectbar.h"

ConnectBar::ConnectBar(QWidget *parent)
    :QToolBar(parent)
{
    mHostEdit = new QLineEdit;
    mUserEdit = new QLineEdit;
    mPasswordEdit = new QLineEdit;
    mConnectButton = new QPushButton("Connect");

    mHostEdit->setPlaceholderText("Host");
    mUserEdit->setPlaceholderText("Username");
    mPasswordEdit->setPlaceholderText("Password");

    addWidget(mHostEdit);
    addSeparator();
    addWidget(mUserEdit);
    addWidget(mPasswordEdit);

    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    addWidget(empty);

    addWidget(mConnectButton);
}

