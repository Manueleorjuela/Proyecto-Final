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

class Nivel1 : public QGraphicsScene
{
    Q_OBJECT
private:
    QGraphicsScene *Nivel;
    QTimer *Timer;
    QTimer *parabolicTimer;



    // Personaje principal
    vector<Soldados> Soldados_Franceses_EnEscena;
    Soldados *Pierre_De_Gaulle;

    //Enemigos
    vector<Objetos> Cañones_Alemanes_EnEscena;

    //PARA AÑADIR OBJETOS
    QGraphicsPixmapItem *item;

    //Cantidad Objetos
    int Cantidad_Soldados_Franceses;
    int Cantidad_Cañones_Alemanes;

    //Limites Soldados Franceses
    const int LIMITE_IZQUIERDO = 636;
    const int LIMITE_DERECHO = 682;
    const int LIMITE_ARRIBA =2;
    const int LIMITE_ABAJO=560;


    void Inicializar_Franceses();
    void Inicializar_Cañones();

    // Primer Modulo
    void Añadir_Soldados_FrancesesEscena();
    void Añadir_Cañones();
    void Ubicar_Cañones();


    //Para las animaciones
    void MoverPersonaje(int DeltX, int DeltY);
    Direccion Orientacion;

    //Moverse Izquierda - Derecha
    void Ubicar_Personaje_Izquierda();
    void Ubicar_Personaje_Derecha();

    //Agacharse
    void Agachar_Personaje();
    bool Agachado;


    void Lanzamiento_Proyectiles();
    vector<Objetos> Proyectiles_Ronda;
    void Ubicar_Proyectiles();
    void Ejecutar_Movimiento_Parabolico();
    int  Numero_Bomba;
    int Numero_Ronda;
    QTimer *Timer_Ronda;
    void Inicializar_Proyectiles();
    void Movimiento_Parabolico(QGraphicsPixmapItem* Proyectil, QTimer* timer, double x0, double y0, double vx, double vy, double t, int Limite, QGraphicsPixmapItem* Explosion);
    int Limite();

    //Ejecucion explosion
    void Secuencia_Explosion(QGraphicsPixmapItem* Explosion);
    vector <Objetos> Explosiones;
    void Inicializar_Explosiones();

private slots:
    void Posicion_Canon();

public:
    //Constructor
    Nivel1(QGraphicsScene *&Fondo, int Cant_Franceses, int Cant_Cañones_Alemanes);
    //Movimiento
    void keyPressEvent(QKeyEvent *event) override;
    void Primer_Modulo();

    ~Nivel1();
};

#endif // NIVEL1_H
