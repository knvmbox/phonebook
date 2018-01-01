#include <QDebug>
#include <QKeyEvent>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"


//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_showMenu(false)
{
    ui->setupUi(this);
    ui->menubar->hide();

    makeTrayIcon();
}

//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//-----------------------------------------------------------------------------
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Alt && event->modifiers() == Qt::AltModifier) {
        if(m_showMenu) {
            ui->menubar->hide();
        }
        m_showMenu = !m_showMenu;
    }
    else {
        m_showMenu = false;
    }

    if(event->key() == Qt::Key_Escape) {
        if(ui->menubar->isVisible()) {
            ui->menubar->hide();
        } else {
            this->hide();
        }
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
void MainWindow::makeTrayIcon()
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
