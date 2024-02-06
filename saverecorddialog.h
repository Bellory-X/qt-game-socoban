#ifndef SAVERECORDDIALOG_H
#define SAVERECORDDIALOG_H

#include <QDialog>

namespace Ui {
class SaveRecordDialog;
}

class SaveRecordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveRecordDialog(QWidget *parent = nullptr);
    ~SaveRecordDialog();

    QString getName();

private:
    Ui::SaveRecordDialog *ui;
};

#endif // SAVERECORDDIALOG_H
