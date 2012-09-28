#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

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
    createImageView();
    this->show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions(){
    fileOpenAct = new QAction(tr("&Open"), this);
    fileOpenAct->setShortcut(QKeySequence::Open);
    fileOpenAct->setStatusTip(tr("Open an image to process"));
    connect(fileOpenAct, SIGNAL(triggered()), this, SLOT(openFile()));

    fileSaveAct = new QAction(tr("&Save"), this);
    fileSaveAct->setShortcut(QKeySequence::Save);
    fileSaveAct->setStatusTip(tr("Save changes to the file"));
    connect(fileSaveAct, SIGNAL(triggered()), this, SLOT(saveFile()));

    fileSaveAsAct = new QAction(tr("S&ave as"), this);
    fileSaveAsAct->setShortcut(QKeySequence::SaveAs);
    fileSaveAsAct->setStatusTip(tr("Save changes to another file"));
    connect(fileSaveAsAct, SIGNAL(triggered()), this, SLOT(saveFileAs()));

    fileCloseAct = new QAction(tr("&Close"), this);
    fileCloseAct->setShortcut(QKeySequence::Close);
    fileCloseAct->setStatusTip(tr("Close current file"));
    connect(fileCloseAct, SIGNAL(triggered()), this, SLOT(closeFile()));

    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcut(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit the software"));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(quit()));

}

void MainWindow::createMenus(){
    fileMenu = this->menuBar->addMenu(tr("&File"));
    fileMenu->addAction(fileOpenAct);
    fileMenu->addAction(fileSaveAct);
    fileMenu->addAction(fileSaveAsAct);
    fileMenu->addAction(fileCloseAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

}
void MainWindow::createImageView(){
    imageView = new ImageView(this);
    imageView->setObjectName(QString::fromUtf8("ImageView"));
    imageView->setGeometry(QRect(this->width()/5,
                                 this->mainToolBar->height(),
                                 this->width()*4/5,
                                 this->height() - this->mainToolBar->height() - this->statusBar->height()));
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

void MainWindow::openFile(){
    QString fileName = QFileDialog::getOpenFileName(this);
    if (this->imageView->openImage(fileName)){
        QMessageBox::warning(this, tr("Application"), tr("Can't open file %1:\n").arg(fileName));
        return;
    }

}

void MainWindow::saveFile(){

}

void MainWindow::saveFileAs(){

}

void MainWindow::closeFile(){

}

void MainWindow::quit(){

}
