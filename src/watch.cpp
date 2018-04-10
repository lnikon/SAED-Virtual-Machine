#include"watch.h"

Watch::Watch()
{
	dock = new QDockWidget("Watch");
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
	list = new QListWidget(dock);
	dock->setWidget(list);
}

QDockWidget* Watch::getDockWidget() 
{
	return dock;
}

void Watch::setVarables(QVector<QPair<QString, int>> variables) 
{
	QString str;
	list->clear();
	for (int i = 0; i < variables.size(); ++i) 
	{
		str.setNum(variables[i].second);
		str = variables[i].first + " = " + str;
		list->addItems(QStringList() << str);
	}
}

void Watch::clear()
{
	list->clear();
}

