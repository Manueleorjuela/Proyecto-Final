#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Fondos = new Niveles();
    Fondos->Cargar_PantallaInicial();
    Escena = Fondos->Get_Escena();
    ui->graphicsView->setScene(Escena);
    Primer_Nivel = new Nivel1(Escena, 5,5);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete Fondos;
    delete Escena;
    delete Primer_Nivel;
}

void MainWindow::on_Iniciar_Partida_clicked()
{
    ui->Menu->hide();
    Fondos->Cargar_Primer_Nivel();
    ui->graphicsView->setScene(Escena);
    Primer_Nivel->Primer_Modulo();
}


void MainWindow::on_Salir_clicked()
{
    close();
}



