#include "runwidget.h"

RunWidget::RunWidget(QWidget *parent) : QWidget(parent)
{

    mFilter = new QLineEdit();
    mPrevButton = new QToolButton();
    mNextButton = new QToolButton();
    mView =new QTableView();
    mModel = new RunModel();

    mView->setModel(mModel);

    mFilter->setPlaceholderText("Filter...");
    QHBoxLayout * hLayout = new QHBoxLayout;
    hLayout->addWidget(mPrevButton);
    hLayout->addWidget(mNextButton);
    hLayout->addWidget(mFilter);
    // hLayout->addStretch();

    hLayout->setContentsMargins(0,0,0,0);

    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addWidget(mView);
    vLayout->setContentsMargins(0,0,0,0);
    vLayout->setSpacing(0);

    setLayout(vLayout);

    mModel->load();

    connect(mPrevButton,SIGNAL(clicked(bool)),mModel,SLOT(prevPage()));
    connect(mNextButton,SIGNAL(clicked(bool)),mModel,SLOT(nextPage()));


}

