#ifndef NIVEL1_H
#define NIVEL1_H

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "soldados.h"
#include "objetos.h"
#include <vector>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>
#include <QKeyEvent>

class Nivel1: public QObject
{
    Q_OBJECT
private:
    QGraphicsScene *Nivel;
    QTimer *Timer;
    vector<Soldados> Soldados_Franceses;
    vector<Objetos> Cañones;

    //Personaje principal
    Soldados *Pierre_De_Gaulle;
     QGraphicsPixmapItem *Pierre_De_Gaulle_EnEscena;


    QGraphicsPixmapItem *item;

    int Cantidad_Soldados_Franceses;
    int Cantidad_Cañones_Alemanes;
    void Inicializar_Franceses();
    void Inicializar_Cañones();

    vector<QGraphicsPixmapItem*> Cañones_EnEscena;
    vector<QGraphicsPixmapItem*> SoldadosFranceses_EnEscena;

    //PrimerModulo
    void Añadir_Soldados_FrancesesEscena();
    void Añadir_Cañones();
    void Ubicar_Cañones();


private slots:
    void Posicion_Canon();

public:
    Nivel1(QGraphicsScene *&Fondo, int Cant_Franceses, int Cant_Cañones_Alemanes);
    void Primer_Modulo();
    void keyPressEvent(QKeyEvent *Tecla_Presionada);

    ~Nivel1();
};

#endif // NIVEL1_H
