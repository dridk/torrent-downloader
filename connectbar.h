#ifndef CONNECTBAR_H
#define CONNECTBAR_H
#include <QtWidgets>

class ConnectBar : public QToolBar
{
    Q_OBJECT
public:
    ConnectBar(QWidget * parent = 0);

     QString host() const;
     QString user() const;
     QString pass() const;

signals:
void connectClicked();

private:
    QLineEdit *mHostEdit;
    QLineEdit *mUserEdit;
    QLineEdit *mPasswordEdit;
    QPushButton * mConnectButton;


};

#endif // CONNECTBAR_H
