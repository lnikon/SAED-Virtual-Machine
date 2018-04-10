#ifndef CPU_H
#define CPU_H

#include <QDockWidget>
#include <QListWidget>
#include <QStringList>

#include "processor.h"

class Cpu
{
public:
	Cpu();
	QDockWidget* getDockWidget();
	
	void setIP(int newIP);
	void setSP(int newSP);
	
	void setAX(int newAX);
	void setBX(int newBX);
	void setCX(int newCX);
	void setDX(int newDX);
	
	void setFlags(CProcessor::CFlags flags);
	
private:
	QDockWidget* dock;
	QListWidget* list;
	
	QString ip;
	QString sp;
	
	QString ax;
	QString bx;
	QString cx;
	QString dx;
	
	QString cf;
	QString pf;
	QString tf;
	QString zf;
	QString sf;
	QString of;
	
	void update();
};
#endif // CPU_H
