#ifndef RUNITEM_H
#define RUNITEM_H
#include <QtCore>

class RunItem
{
public:
    RunItem();


  QString name;
  QDateTime date;
  QString reportName;
  QUrl reportLink;
  int id;



};

#endif // RUNITEM_H
