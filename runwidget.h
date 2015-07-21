#ifndef RUNWIDGET_H
#define RUNWIDGET_H
#include <QtWidgets>
#include "runmodel.h"
class RunWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RunWidget(QWidget *parent = 0);


public slots:
    void load();
signals:
    void clicked(int runId);


protected slots:
    void viewClicked(const QModelIndex& index);



private:
    QLineEdit * mFilter;
    QToolButton * mPrevButton;
    QToolButton * mNextButton;
    QTableView * mView;
    RunModel * mModel;

};

#endif // RUNWIDGET_H
