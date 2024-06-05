#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "niveles.h"
#include "nivel2.h"
#include "Nivel1.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_Iniciar_Partida_clicked();
    void on_Salir_clicked();

    void Nivel1_Completado_();
    void Nivel2_Completado_();

    void on_Reiniciar_Nivel_clicked();
    void on_Salir_2_clicked();
    void on_Volver_clicked();
    void on_Informacion_clicked();

private:
    Niveles *Fondos;
    QGraphicsScene *Escena;
    QTimer* Cambio_Nivel;
    Ui::MainWindow *ui;
    Nivel1 *Primer_Nivel;
    Nivel2 *Segundo_Nivel;

    bool Ejecucion_PrimerNivel;
    bool Ejecucion_SegundoNivel;

    void Primer_Nivel_();
    void Segundo_Nivel_();

    void Inicializar_Cambio_Primer_Nivel();
    void Inicializar_Cambio_Segundo_Nivel();
    void Inicializar_Juego();

    bool Nivel2_Completado;
    bool Nivel2_Ganado;

    bool Nivel1_Completado;
    bool Nivel1_Ganado;

    void Volver_A_Intentar_Nivel1();
};

#endif // MAINWINDOW_H
