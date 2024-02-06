#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "saverecorddialog.h"

#include <QMainWindow>
#include <QListWidgetItem>
#include <QTimer>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void addRecord(const QPair<QString, QString> &newRecord);

private slots:
    void showGameView(QListWidgetItem *item);
    void showTimer();
    void showListWidget();
    void clickSaveButton();
    void clickStartButton();

private:
    Ui::MainWindow *ui;
    SaveRecordDialog *dialog;
    QTimer timer;
    int milliseconds;
};

#endif // MAINWINDOW_H
