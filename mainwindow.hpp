#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <memory>

#include <QMainWindow>
#include <QSystemTrayIcon>

#include "applicationmodel.hpp"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent*) override;
    void keyReleaseEvent(QKeyEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mousePressEvent(QMouseEvent*) override;

private slots:
    void importData();

private:
    bool isAltKeyPress(QKeyEvent *event);
    void lastnameEdited(const QString&);
    void phoneEdited(const QString&);
    void processAltKeyPress();
    void processEscKeyPress();
    void setupGlobalHotkey();
    void setupTrayIcon();
    void trayActivated(QSystemTrayIcon::ActivationReason);

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *m_tray;

    QPoint m_position;
    bool m_showMenu;

    std::shared_ptr<ApplicationModel> m_model;
};

#endif // MAINWINDOW_HPP
