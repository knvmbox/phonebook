#ifndef ABOUTDLG_HPP
#define ABOUTDLG_HPP

#include <string>

#include <QDialog>


namespace Ui {
class AboutDlg;
}


class AboutDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit AboutDlg(QWidget *parent = 0);
    ~AboutDlg();

private:
    Ui::AboutDlg *ui;
};

#endif // ABOUTDLG_HPP
