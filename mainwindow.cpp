#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>

#include "dialog/aboutdlg.hpp"
#include "mainwindow.hpp"
#include "personviewmodel.hpp"
#include "ui_mainwindow.h"


//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_showMenu(false),
    m_model(new ApplicationModel)
{
    ui->setupUi(this);
    ui->menubar->hide();

    setupTrayIcon();

    ui->peopleView->setModel(new PersonViewModel(m_model.get(), ui->peopleView));

    connect(ui->hideAction, SIGNAL(triggered(bool)), this, SLOT(hide()));
    connect(ui->quitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(ui->importDataAction, SIGNAL(triggered(bool)), this, SLOT(importData()));
    connect(ui->aboutAction, SIGNAL(triggered(bool)), this, SLOT(showAbout()));
    connect(ui->aboutQtAction, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));

    connect(ui->lastnameEdit, &QLineEdit::textEdited, this, &MainWindow::lastnameEdited);
    connect(ui->phoneEdit, &QLineEdit::textEdited, this, &MainWindow::phoneEdited);
}

//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//-----------------------------------------------------------------------------
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(isAltKeyPress(event)) {
        processAltKeyPress();
    }
    else {
        m_showMenu = false;
    }

    if(event->key() == Qt::Key_Escape) {
        processEscKeyPress();
    }

    QMainWindow::keyPressEvent(event);
}

//-----------------------------------------------------------------------------
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Alt) {
        if(m_showMenu) {
            ui->menubar->show();
        }
    } else {
        m_showMenu = false;
    }

    QMainWindow::keyReleaseEvent(event);
}

//-----------------------------------------------------------------------------
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton) {
        QPoint pos = event->globalPos();
        QPoint diff = pos - m_position;

        this->move(this->pos() + diff);
        m_position = pos;
    }

    QMainWindow::mouseMoveEvent(event);
}

//-----------------------------------------------------------------------------
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
        m_position = event->globalPos();

    QMainWindow::mousePressEvent(event);
}

//-----------------------------------------------------------------------------
void MainWindow::importData()
{
    QString filename = QFileDialog::getOpenFileName(
        this, tr("Импорт данных"),
        ".",
        tr("Данные (*.csv)")
    );
    if(filename.isEmpty())
        return;

    try {
        m_model->importData(filename);
        QMessageBox::information(this, tr("Импорт данных"), "Импорт данных завершен");
    } catch (std::runtime_error &e) {
        QMessageBox::critical(this, tr("Импорт данных"), e.what());
    }
}

//-----------------------------------------------------------------------------
void MainWindow::showAbout()
{
    AboutDlg about;
    about.exec();
}

//-----------------------------------------------------------------------------
bool MainWindow::isAltKeyPress(QKeyEvent *event)
{
    return event->key() == Qt::Key_Alt && event->modifiers() == Qt::AltModifier;
}

//-----------------------------------------------------------------------------
void MainWindow::lastnameEdited(const QString &text)
{
    m_model->findPerson(text, ui->phoneEdit->text());
}

//-----------------------------------------------------------------------------
void MainWindow::phoneEdited(const QString &text)
{
    m_model->findPerson(ui->lastnameEdit->text(), text);
}

//-----------------------------------------------------------------------------
void MainWindow::processAltKeyPress()
{
    if(m_showMenu) {
        ui->menubar->hide();
    }
    m_showMenu = !m_showMenu;
}

//-----------------------------------------------------------------------------
void MainWindow::processEscKeyPress()
{
    if(ui->menubar->isVisible()) {
        ui->menubar->hide();
    } else {
        this->hide();
    }
}

//-----------------------------------------------------------------------------
void MainWindow::setupTrayIcon()
{
    m_tray = new QSystemTrayIcon(this);
    m_tray->setIcon(QIcon(":/icons/image/phonebook.png"));
    m_tray->setToolTip("PhoneBook" "\n" "Телефонная книга");
    m_tray->show();

    connect(m_tray, &QSystemTrayIcon::activated, this, &MainWindow::trayActivated);
}

//-----------------------------------------------------------------------------
void MainWindow::trayActivated(QSystemTrayIcon::ActivationReason reason)
{
    if(reason != QSystemTrayIcon::Trigger)
        return;

    if(this->isVisible()) {
        this->hide();
    } else {
        this->show();
    }
}
