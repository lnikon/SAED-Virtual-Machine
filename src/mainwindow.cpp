#include <QtWidgets>

#include "mainwindow.h"
#include "watch.h"

MainWindow::MainWindow()
{
	setWindowTitle(tr("SAED"));

	cpu = new Cpu();
	this->addDockWidget(Qt::RightDockWidgetArea, cpu->getDockWidget());
	viewMenu->addAction(cpu->getDockWidget()->toggleViewAction());

	Watch* watch = new Watch();
	this->addDockWidget(Qt::RightDockWidgetArea, watch->getDockWidget());
	viewMenu->addAction(watch->getDockWidget()->toggleViewAction());

	textEdit = new QTextEdit;
	setCentralWidget(textEdit);

	createActions();
	createStatusBar();

	newLetter();

	// ============== testing
	cpu->setIP(50);
	cpu->setSP(60);

	cpu->setAX(1);
	cpu->setBX(2);
	cpu->setCX(3);
	cpu->setDX(4);
	
	CProcessor::CFlags flags;
	
	flags.setCarry(1);
	flags.setOverflow(1);
	flags.setParity(1);
	flags.setSign(1);
	flags.setTrap(1);
	flags.setZero(1);

	cpu->setFlags(flags);
	
	QVector<QPair<QString, int>> a;
	a.push_back(QPair<QString, int>("A", 5));
	a.push_back(QPair<QString, int>("B", 4));
	a.push_back(QPair<QString, int>("C", 3));	
	watch->setVarables(a);
	
	//tabifyDockWidget(cpu->getDockWidget(), something->getDockWidget());
}

void MainWindow::newLetter()
{
	textEdit->clear();

	QTextCursor cursor(textEdit->textCursor());
	cursor.movePosition(QTextCursor::Start);
	QTextFrame *topFrame = cursor.currentFrame();
	QTextFrameFormat topFrameFormat = topFrame->frameFormat();
	topFrameFormat.setPadding(5);
	topFrame->setFrameFormat(topFrameFormat);

	QTextTableFormat tableFormat;
	tableFormat.setBorder(1);
	tableFormat.setCellPadding(16);
	tableFormat.setAlignment(Qt::AlignRight);
	//cursor.insertText("ADDRESS", italicFormat);
}

void MainWindow::save()
{
	QMimeDatabase mimeDatabase;
	QString fileName = QFileDialog::getSaveFileName(this, tr("Choose a file name"), ".", mimeDatabase.mimeTypeForName("text").filterString());
	if (fileName.isEmpty())
	{
		return;
	}
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		QMessageBox::warning(this, tr("Dock Widgets"), tr("Cannot write file %1:\n%2.").arg(QDir::toNativeSeparators(fileName), file.errorString()));
		return;
	}

	QTextStream out(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	out << textEdit->toPlainText();
	QApplication::restoreOverrideCursor();

	statusBar()->showMessage(tr("Saved '%1'").arg(fileName), 2000);
}

void MainWindow::createActions()
{
	QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
	QToolBar *fileToolBar = addToolBar(tr("File"));

	const QIcon openIcon = QIcon::fromTheme("open-document", QIcon(":/images/open.png"));
	QAction *openAct = new QAction(openIcon, tr("&Open"), this);
	openAct->setShortcuts(QKeySequence::New);
	openAct->setStatusTip(tr("open a file"));
	fileMenu->addAction(openAct);
	fileToolBar->addAction(openAct);

	const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/images/new.png"));
	QAction *newLetterAct = new QAction(newIcon, tr("&New Letter"), this);
	newLetterAct->setShortcuts(QKeySequence::New);
	newLetterAct->setStatusTip(tr("Create a new form letter"));
	connect(newLetterAct, &QAction::triggered, this, &MainWindow::newLetter);
	fileMenu->addAction(newLetterAct);
	fileToolBar->addAction(newLetterAct);

	const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/images/save.png"));
	QAction *saveAct = new QAction(saveIcon, tr("&Save"), this);
	saveAct->setShortcuts(QKeySequence::Save);
	saveAct->setStatusTip(tr("Save the current form letter"));
	connect(saveAct, &QAction::triggered, this, &MainWindow::save);
	fileMenu->addAction(saveAct);
	fileToolBar->addAction(saveAct);

	fileMenu->addSeparator();
	QAction *quitAct = fileMenu->addAction(tr("&Quit"), this, &QWidget::close);
	quitAct->setShortcuts(QKeySequence::Quit);
	quitAct->setStatusTip(tr("Quit the application"));

// =============================================================================================== run
	QMenu *toolMenu = menuBar()->addMenu(tr("&Tools"));
	QToolBar *toolBar = addToolBar(tr("Tools"));
  
	const QIcon buildIcon = QIcon::fromTheme("build", QIcon(":/images/build.png"));
	QAction *buildAct = new QAction(buildIcon, tr("&Build"), this);
	buildAct->setStatusTip(tr("build"));
	toolMenu->addAction(buildAct);
	toolBar->addAction(buildAct);
	
	const QIcon runIcon = QIcon::fromTheme("play", QIcon(":/images/play.png"));
	QAction *runAct = new QAction(runIcon, tr("&Run"), this);
	runAct->setStatusTip(tr("run"));
	toolMenu->addAction(runAct);
	toolBar->addAction(runAct);

	const QIcon debugIcon = QIcon::fromTheme("debug", QIcon(":/images/debug.png"));
	QAction *debugAct = new QAction(debugIcon, tr("&Debug"), this);
	debugAct->setStatusTip(tr("debug"));
	toolMenu->addAction(debugAct);
	toolBar->addAction(debugAct);
	toolMenu->addSeparator();

// ================================================================================================ debug

	QToolBar *debugBar = addToolBar(tr("Debug"));

	const QIcon nextIcon = QIcon::fromTheme("next", QIcon(":/images/next.png"));
	QAction *nextAct = new QAction(nextIcon, tr("&Next"), this);
	nextAct->setStatusTip(tr("next"));
	toolMenu->addAction(nextAct);
	debugBar->addAction(nextAct);

	const QIcon scipIcon = QIcon::fromTheme("scip", QIcon(":/images/scip.png"));
	QAction *scipAct = new QAction(scipIcon, tr("&Scip"), this);
	nextAct->setStatusTip(tr("scip"));
	toolMenu->addAction(scipAct);
	debugBar->addAction(scipAct);

	const QIcon stopIcon = QIcon::fromTheme("stop", QIcon(":/images/stop.png"));
	QAction *stopAct = new QAction(stopIcon, tr("&Stop"), this);
	stopAct->setStatusTip(tr("stop"));
	toolMenu->addAction(stopAct);
	debugBar->addAction(stopAct);
	
	viewMenu = menuBar()->addMenu(tr("&View"));
	menuBar()->addSeparator();
}

void MainWindow::createStatusBar()
{
	statusBar()->showMessage(tr("Ready"));
}

