#include "aboutdlg.hpp"
#include "ui_aboutdlg.h"


//-----------------------------------------------------------------------------
AboutDlg::AboutDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDlg)
{
    ui->setupUi(this);
    setModal(true);
}

//-----------------------------------------------------------------------------
AboutDlg::~AboutDlg()
{
    delete ui;
}
