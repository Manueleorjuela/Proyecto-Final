#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "niveles.h"
#include "nivel1.h"

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

private slots:
    void on_Iniciar_Partida_clicked();
    void on_Salir_clicked();

private:
    Niveles *Fondos;
    QGraphicsScene *Escena;
    Ui::MainWindow *ui;
    Nivel1 *Primer_Nivel;
};
#endif // MAINWINDOW_H
