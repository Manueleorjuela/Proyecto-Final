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
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setFocus();
    ui->graphicsView->scene()->installEventFilter(this);
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();
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
    Ejecucion_PrimerNivel = true;
    ui->graphicsView->setScene(Escena);
    Primer_Nivel = new Nivel1(Escena, 4, 5, 10);
    Primer_Nivel->Primer_Modulo();
    Primer_Nivel->Segundo_Modulo();
}

void MainWindow::on_Salir_clicked()
{
    close();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (Ejecucion_PrimerNivel){
        Primer_Nivel->keyPressEvent(event);
    }
}



