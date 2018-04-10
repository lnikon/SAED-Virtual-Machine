#ifndef SOMETHING_H
#define SOMETHING_H

#include <QDockWidget>
#include <QListWidget>
#include <QStringList>
#include <QVector>
#include <QPair>

class Watch
{
public:
	Watch();
	
	QDockWidget* getDockWidget() ;
	
	void setVarables(QVector<QPair<QString, int>> variables);
	void clear();
	
private:
	QDockWidget* dock;
	QListWidget* list;
};
#endif // SOMETHING_H
