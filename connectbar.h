#ifndef CONNECTBAR_H
#define CONNECTBAR_H
#include <QtWidgets>
class ConnectBar : public QToolBar
{
public:
    ConnectBar(QWidget * parent = 0);


private:
    QLineEdit *mHostEdit;
    QLineEdit *mUserEdit;
    QLineEdit *mPasswordEdit;

    QPushButton * mConnectButton;


};

#endif // CONNECTBAR_H
