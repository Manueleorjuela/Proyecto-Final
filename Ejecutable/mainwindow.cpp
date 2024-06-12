#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Fondos = new Niveles();
    Inicializar_Juego();
    ui->graphicsView->setScene(Escena);
    ui->graphicsView->setFocusPolicy(Qt::StrongFocus);
    ui->graphicsView->setFocus();
    ui->graphicsView->scene()->installEventFilter(this);
    ui->Aviso_Partida_Terminada->hide();
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete Fondos;
    delete Cambio_Nivel;
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
        Jugador.set_Estado_Nivel1(Nivel1_Ganado);
        Cambio_Nivel->stop();
        delete Primer_Nivel;
        if (!Nivel1_Ganado) {
            Jugador.Asignar_Tiempo(0);
            Jugador.set_Estado_Nivel2(false);
            Jugador.Almacenar_NuevaMarca();
            Escena->clear();
            Inicializar_Juego();
        } else {
            Escena->clear();
            Segundo_Nivel_();
        }
    }
}

void MainWindow::Nivel2_Completado_()
{
    Nivel2_Completado = Segundo_Nivel->get_Terminar();
    Nivel2_Ganado = Segundo_Nivel->get_Ganar();

    if(Nivel2_Completado){
        Jugador.set_Estado_Nivel2(Nivel2_Ganado);
        Cambio_Nivel->stop();
        delete Segundo_Nivel;
        if(!Nivel2_Ganado){
            Jugador.Asignar_Tiempo(0);
            Jugador.Almacenar_NuevaMarca();
            Escena->clear();
            Inicializar_Juego();
        }else{
            Jugador.Asignar_Tiempo(0);
            Jugador.Almacenar_NuevaMarca();
            Escena->clear();
            Aviso_Partida_Terminada();
        }
    }
}

void MainWindow::Primer_Nivel_()
{
    Jugador.Asignar_Tiempo(1);
    Fondos->Cargar_Primer_Nivel();
    Ejecucion_PrimerNivel = true;
    Ejecucion_SegundoNivel = false;
    ui->graphicsView->setScene(Escena);
    Primer_Nivel = new Nivel1(Escena);
    Primer_Nivel->Primer_Modulo();
    Primer_Nivel->Segundo_Modulo();
    Inicializar_Cambio_Primer_Nivel();

}

void MainWindow::Segundo_Nivel_()
{
    ui->Volver->hide();
    ui->Intrucciones->hide();
    Fondos->Cargar_Segundo_Nivel();
    Ejecucion_PrimerNivel = false;
    Ejecucion_SegundoNivel = true;
    ui->graphicsView->setScene(Escena);
    Segundo_Nivel = new Nivel2(Escena);
    Segundo_Nivel->Modulo();
    Inicializar_Cambio_Segundo_Nivel();
}

void MainWindow::Inicializar_Cambio_Primer_Nivel()
{

    Cambio_Nivel = new QTimer();
    connect(Cambio_Nivel, &QTimer::timeout, this, &MainWindow::Nivel1_Completado_);
    Cambio_Nivel->start(3000);
}

void MainWindow::Inicializar_Cambio_Segundo_Nivel()
{
    Cambio_Nivel = new QTimer();
    connect(Cambio_Nivel, &QTimer::timeout, this, &MainWindow::Nivel2_Completado_);
    Cambio_Nivel->start(3000);
}

void MainWindow::Inicializar_Juego()
{
    ui->Menu->show();
    ui->Mejor_Registro->hide();
    Fondos->Cargar_PantallaInicial();
    Escena = Fondos->Get_Escena();
    ui->Aviso_Partida_Terminada->hide();
    ui->Menu_2->hide();
    ui->Volver->hide();
    ui->Intrucciones->hide();
    Segundo_Nivel = nullptr;
    Primer_Nivel = nullptr;
    Cambio_Nivel = nullptr;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (Ejecucion_PrimerNivel && !Ejecucion_SegundoNivel) {
        Primer_Nivel->keyPressEvent(event);
    }
    if(Ejecucion_SegundoNivel && !Ejecucion_PrimerNivel){
        Segundo_Nivel->keyPressEvent(event);
    }
}

void MainWindow::on_Volver_clicked()
{
    ui->Volver->hide();
    ui->Mejor_Registro->hide();
    ui->Intrucciones->hide();
    ui->Menu->show();
}

void MainWindow::on_Informacion_clicked()
{
    ui->Aviso_Partida_Terminada->hide();
    ui->Menu->hide();
    ui->Intrucciones->show();
    ui->Volver->show();
}

void MainWindow::Aviso_Partida_Terminada()
{
    Fondos->Cargar_PantallaInicial();
    ui->Aviso_Partida_Terminada->show();
    ui->Volver->show();
}

void MainWindow::on_Registros_clicked()
{
    QString Registros =  QString::fromStdString(Jugador.Mejor_Tiempo_Registrado()) + " minutos";
    ui->Mejor_Registro->show();
    ui->Mejor_Registro->setText(Registros);
    ui->Menu->hide();
    ui->Volver->show();

}

