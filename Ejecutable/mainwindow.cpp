#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Fondos = new Niveles();
    Fondos->Cargar_PantallaInicial();
    ui->graphicsView->setScene(Fondos->Get_Escena());
}

MainWindow::~MainWindow()
{
    delete ui;
}

