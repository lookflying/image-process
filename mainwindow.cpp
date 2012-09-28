#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    if (this->objectName().isEmpty())
    this->setObjectName(QString::fromUtf8("MainWindow"));
    this->resize(793, 488);
    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
    this->setCentralWidget(centralWidget);
    createActions();
    createMenuBar();
    createMenus();
    createToolBar();
    createStatusBar();
    this->show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions(){
    fileOpenAct = new QAction(tr("&Open"), this);
    fileOpenAct->setShortcut(QKeySequence::Open);
    fileOpenAct->setStatusTip(tr("Open an image to process"));

    fileSaveAct = new QAction(tr("&Save"), this);
    fileSaveAct->setShortcut(QKeySequence::Save);
    fileSaveAct->setStatusTip(tr("Save changes to the file"));

    fileSaveAsAct = new QAction(tr("S&ave as"), this);
    fileSaveAsAct->setShortcut(QKeySequence::SaveAs);
    fileSaveAsAct->setStatusTip(tr("Save changes to another file"));

    fileCloseAct = new QAction(tr("&Close"), this);
    fileCloseAct->setShortcut(QKeySequence::Close);
    fileCloseAct->setStatusTip(tr("Close current file"));

    fileQuitAct = new QAction(tr("&Quit"), this);
    fileQuitAct->setShortcut(QKeySequence::Quit);
    fileQuitAct->setStatusTip(tr("Quit the software"));

}

void MainWindow::createMenus(){
    fileMenu = this->menuBar->addMenu(tr("&File"));
    fileMenu->addAction(fileOpenAct);
    fileMenu->addAction(fileSaveAct);
    fileMenu->addAction(fileSaveAsAct);
    fileMenu->addAction(fileCloseAct);
    fileMenu->addSeparator();
    fileMenu->addAction(fileQuitAct);

}
void MainWindow::createImageView(){
    imageView = new ImageView(this);
    imageView->setObjectName(QString::fromUtf8("ImageView"));
    imageView->setGeometry(QRect(this->width()/5, 0, this->width()*4/5, this->height()));
}

void MainWindow::createStatusBar(){
    statusBar = new QStatusBar(this);
    statusBar->setObjectName(QString::fromUtf8("statusBar"));
    this->setStatusBar(statusBar);
}

void MainWindow::createToolBar(){
    mainToolBar = new QToolBar(this);
    mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
    this->addToolBar(Qt::TopToolBarArea, mainToolBar);
}

void MainWindow::createMenuBar(){
    menuBar = new QMenuBar(this);
    menuBar->setObjectName(QString::fromUtf8("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 793, 25));
}
