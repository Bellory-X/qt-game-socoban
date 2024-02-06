#include "saverecorddialog.h"
#include "ui_saverecorddialog.h"

SaveRecordDialog::SaveRecordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveRecordDialog)
{
    ui->setupUi(this);
    connect(ui->saveButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

SaveRecordDialog::~SaveRecordDialog()
{
    delete ui;
}

QString SaveRecordDialog::getName()
{
    return ui->lineEdit->text();
}
