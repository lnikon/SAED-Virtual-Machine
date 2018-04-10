#include "cpu.h"

Cpu::Cpu() 
{
	dock = new QDockWidget("CPU");
	dock->setFixedHeight(180);
	dock->setMinimumWidth(200);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	list = new QListWidget(dock);
	ip = "IP = 0";
	sp = "SP = 0";
	ax = "AX = 0";
	bx = "BX = 0";
	cx = "CX = 0";
	dx = "DX = 0";
	
	cf = "CF 0";
	pf = "PF 0";
	tf = "TF 0";
	zf = "ZF 0";
	sf = "SF 0";
	of = "OF 0";

	update();
	dock->setWidget(list);
}

QDockWidget* Cpu::getDockWidget()
{
	return dock;
}

void Cpu::update()
{
	list->clear();
	list->addItems(QStringList()
		<< ip
		<< sp
		<< ""
		<< ax
		<< bx
		<< cx
		<< dx
		<< ""
		<< cf + ",  " + pf + ",  " + tf + ",  " + zf + ",  " + sf + ",  " + of
	);
}

void Cpu::setIP(int newIP)
{
	ip.setNum(newIP);
	ip = "IP = " + ip;
	update();
}

void Cpu::setSP(int newSP)
{
	sp.setNum(newSP);
	sp = "SP = " + sp;
	update();
}

void Cpu::setAX(int newAX)
{
	ax.setNum(newAX);
	ax = "AX = " + ax;
	update();
}

void Cpu::setBX(int newBX)
{
	bx.setNum(newBX);
	bx = "BX = " + bx;
	update();
}

void Cpu::setCX(int newCX)
{
	cx.setNum(newCX);
	cx = "CX = " + cx;
	update();
}

void Cpu::setDX(int newDX)
{
	dx.setNum(newDX);
	dx = "DX = " + dx;
	update();
}

void Cpu::setFlags(CProcessor::CFlags flags)
{
	cf.setNum(flags.getCarry());
	pf.setNum(flags.getParity());
	tf.setNum(flags.getTrap());
	zf.setNum(flags.getZero());
	sf.setNum(flags.getSign());
	of.setNum(flags.getOverflow());
	
	cf = "CF " + cf;
	pf = "PF " + pf;
	tf = "TF " + tf;
	zf = "ZF " + zf;
	sf = "SF " + sf;
	of = "OF " + of;
	
	this->update();	
}

