#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Menu_2->hide();
    ui->Aviso_Muerte->hide();
    Fondos = new Niveles();
    Fondos->Cargar_PantallaInicial();
    Escena = Fondos->Get_Escena();
    ui->graphicsView->setScene(Escena);
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setFocus();
    ui->graphicsView->scene()->installEventFilter(this);
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();

    Primer_Nivel = nullptr;
    Cambio_Nivel = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete Fondos;
    delete Escena;
}

void MainWindow::on_Iniciar_Partida_clicked()
{
    ui->Menu->hide();
    Primer_Nivel_();
}

void MainWindow::on_Salir_clicked()
{
    close();
}

void MainWindow::Nivel1_Completado_()
{
    Nivel1_Completado = Primer_Nivel->get_TerminoNivel();
    Nivel1_Ganado = Primer_Nivel->get_Ganar();
    if (Nivel1_Completado) {
        Cambio_Nivel->stop();
        delete Primer_Nivel;
        Primer_Nivel = nullptr;
        if (!Nivel1_Ganado) {
            Volver_A_Intentar_Nivel();
        } else {
            Segundo_Nivel();
        }
    }
}

void MainWindow::Primer_Nivel_()
{
    Fondos->Cargar_Primer_Nivel();
    Ejecucion_PrimerNivel = true;
    Ejecucion_SegundoNivel = false;
    ui->graphicsView->setScene(Escena);
    Primer_Nivel = new Nivel1(Escena);
    Primer_Nivel->Primer_Modulo();
    Primer_Nivel->Segundo_Modulo();
    Inicializar_Cambio_Nivel();
}

void MainWindow::Segundo_Nivel()
{
    Fondos->Cargar_Segundo_Nivel();
    Ejecucion_PrimerNivel = false;
    Ejecucion_SegundoNivel = true;
    ui->graphicsView->setScene(Escena);

}

void MainWindow::Inicializar_Cambio_Nivel()
{

    Cambio_Nivel = new QTimer();
    connect(Cambio_Nivel, &QTimer::timeout, this, &MainWindow::Nivel1_Completado_);
    Cambio_Nivel->start(2000);
}

void MainWindow::Volver_A_Intentar_Nivel()
{
    ui->Aviso_Muerte->show();
    Fondos->Cargar_PantallaInicial();
    ui->Menu_2->show();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (Ejecucion_PrimerNivel && Primer_Nivel) {
        Primer_Nivel->keyPressEvent(event);
    }
}

void MainWindow::on_Reiniciar_Nivel_clicked()
{
    if (Ejecucion_PrimerNivel) {
        ui->Menu_2->hide();
        ui->Aviso_Muerte->hide();
        Primer_Nivel_();
    }
    if (Ejecucion_SegundoNivel) {
        // Lógica para el segundo nivel si es necesario
    }
}

void MainWindow::on_Salir_2_clicked()
{
    close();
}

