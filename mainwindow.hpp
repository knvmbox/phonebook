#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QSystemTrayIcon>

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

private:
    bool isAltKeyPress(QKeyEvent *event);
    void makeTrayIcon();
    void processAltKeyPress();
    void processEscKeyPress();
    void trayActivated(QSystemTrayIcon::ActivationReason);

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *m_tray;

    QPoint m_position;
    bool m_showMenu;
};

#endif // MAINWINDOW_HPP
