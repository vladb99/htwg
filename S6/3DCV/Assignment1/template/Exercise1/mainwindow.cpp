#include "mainwindow.h"

#include <QFileDialog>
#include <QKeyEvent>

#include <iostream>
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
	ui->glwidget->setFocusPolicy(Qt::StrongFocus);
    ui->glwidget->setFocus();

    _camera = QSharedPointer<RenderingCamera>(new RenderingCamera());
    ui->glwidget->attachCamera(_camera);

    QObject::connect(ui->pushButton,&QPushButton::clicked,ui->glwidget, &GLWidget::openFileDialog);
    QObject::connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::updatePointSize);
    QObject::connect(ui->radioButton_1,&QRadioButton::clicked,ui->glwidget,&GLWidget::radioButton1Clicked);
    QObject::connect(ui->radioButton_2,&QRadioButton::clicked,ui->glwidget,&GLWidget::radioButton2Clicked);

    updatePointSize(1);

    _camera->setPosition(QVector3D(0.0f, -0.1f, -0.2f));
    _camera->rotate(0, 50, 0);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::updatePointSize(size_t value)
{
    std::cout << "new pointsize: " << value << std::endl;
    ui->glwidget->setPointSize(value);
}
