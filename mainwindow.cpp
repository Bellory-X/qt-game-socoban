#include "mainwindow.h"
#include "saverecorddialog.h"
#include "ui_mainwindow.h"

#include "gamescene.h"
#include "tablerecordsmodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), dialog(new SaveRecordDialog(this))
{
    ui->setupUi(this);
    auto scene = new GameScene(&timer);
    auto records = new TableRecordsModel(scene);
    for (auto &title : records->titles())
    {
        auto item = new QListWidgetItem(title);
        item->setTextAlignment(Qt::AlignCenter);
        ui->listWidget->addItem(item);
    }
    ui->gameView->setScene(scene);
    ui->recordView->setModel(records);
    ui->recordView->horizontalHeader()->setFixedHeight(50);
    ui->recordView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->recordView->setStyleSheet("QHeaderView::section { background-color:gray; color:white; }");
    connect(this, &MainWindow::addRecord, records, &TableRecordsModel::add);
    connect(ui->listWidget, &QListWidget::itemClicked, records, &TableRecordsModel::fill);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::showGameView);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::clickStartButton);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::clickSaveButton);
    connect(ui->menuButton, &QPushButton::clicked, this, &MainWindow::showListWidget);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::close);
    connect(&timer, &QTimer::timeout, this, &MainWindow::showTimer);
    timer.setInterval(1);
    showListWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dialog;
}

void MainWindow::showListWidget()
{
    timer.stop();
    ui->listWidget->setFocus();
    ui->timeLabel->setText("00:00:000");
    ui->splitter->setSizes({width(), 0});
    auto rowCount = ui->recordView->model()->rowCount();
    for (int i = 0; i < rowCount; ++i)
    {
        ui->recordView->hideRow(i);
    }
}

void MainWindow::showGameView(QListWidgetItem *item)
{
    milliseconds = 0;
    ui->gameView->setFocus();
    ui->splitter->setSizes({0, width()});
    auto rowCount = ui->recordView->model()->rowCount();
    for (int i = 0; i < rowCount; ++i)
    {
        ui->recordView->showRow(i);
    }
}

void MainWindow::showTimer()
{
    milliseconds++;
    auto time = QString("%1:%2:%3")
            .arg(milliseconds / 60000, 2, 10, QChar('0'))
            .arg((milliseconds / 1000) % 60, 2, 10, QChar('0'))
            .arg(milliseconds % 1000, 3, 10, QChar('0'));
    ui->timeLabel->setText(time);
}

void MainWindow::clickStartButton()
{
    emit ui->listWidget->itemClicked(ui->listWidget->currentItem());
}

void MainWindow::clickSaveButton()
{
    if (!timer.isActive() && dialog->exec() == QDialog::Accepted)
    {
        emit addRecord({dialog->getName(), ui->timeLabel->text()});
    }
}
