#ifndef NIVEL1_H
#define NIVEL1_H

#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "soldados.h"
#include "objetos.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>
#include <QKeyEvent>
#include <algorithm>

class Nivel1 : public QGraphicsScene
{
    Q_OBJECT
private:
    QGraphicsScene *Nivel;
    QTimer *Timer;
    QTimer *Colisiones;
    QTimer *Colisiones_Aliados;
    QTimer *Llegada_Alemanes;
    QTimer *DisparosEnemigos;

    // Personaje principal
    vector<Soldados> Soldados_Franceses_EnEscena;
    vector <Soldados> Soldados_Alemanes_EnEscena;

    Soldados* Pierre_De_Gaulle;

    //Enemigos
    vector<Objetos> Cañones_Alemanes_EnEscena;

    //PARA AÑADIR OBJETOS
    QGraphicsPixmapItem *item;

    //Cantidad Objetos
    int Cantidad_Soldados_Franceses;
    int Cantidad_Soldados_Alemanes;
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

    //Moverse Izquierda - Derecha
    void Ubicar_Personaje_Izquierda();
    void Ubicar_Personaje_Derecha();

    //Agacharse
    void Agachar_Personaje();
    bool Agachado;

    void Lanzamiento_Proyectiles();
    vector<Objetos> Proyectiles_Ronda;
    void Ubicar_Proyectiles();
    void Ejecutar_Movimiento_Parabolico_Bombas();
    int  Numero_Bomba;
    //int Numero_Ronda;
    //QTimer *Timer_Ronda;
    void Inicializar_Proyectiles();

    //Ejecucion explosion
    vector <Objetos> Explosiones;
    void Inicializar_Explosiones();

    //Colisiones
    void Colisiones_PersonajePrincipal();
    void Muerte_Pierre(int Daño);
    void Inicializar_Colisiones();

    //Eliminar_Aliados
    void Muerte_Soldado_Frances(int indice, int Daño);
    void Colisiones_SoldadosFranceses();

    //Segundo Modulo
    void Inicializar_Soldados_Alemanes();
    void Añadir_SoldadosAlemanes_EnEscena();
    void Ubicar_Soldados_Alemanes();

    //Inicializar Gas_Mostaza
    vector<Objetos> Fumigacion_Gas;
    vector<Objetos> Efecto_Gas_Mostaza;
    void Inicializar_Efecto_Gas();
    void Inicializar_Barrido_De_Gas();
    void Lanzamiento_Gas();
    void Ubicar_Gas();
    void Ejecutar_Movimiento_Parabolico_Gas();

    //Iniciar_Tiroteo
    void Disparo_Personaje_Principal();

    //Avance_Enemigo
    void Disparos_Enemigos();
    void Inicializar_Disparos_Enemigos();
    bool Probabilidadi_Para_Disparos_Enemigos();

private slots:

    void Ejecutar_Movimiento_Circular();
    void Posicionar_Enemigos(int Repeticiones, int Posicion_Final, QTimer* Timer);
    void Secuencia_Animaciones(QGraphicsPixmapItem* Explosion, int Frame, vector<QGraphicsPixmapItem*> Secuencia_Explosiones, int Timer);
    void Movimiento_Parabolico(QGraphicsPixmapItem* Proyectil, QTimer* timer, double x0, double y0, double vx, double vy, double t, int Limite, QGraphicsPixmapItem* Explosion, int Case, double Escala);
    void Movimiento_Rectilineo_Disparos(QGraphicsPixmapItem* Bala, QTimer* timer, double v0, double x0, double t0);

public:
    //Constructor
    Nivel1(QGraphicsScene *&Fondo, int Cant_Franceses, int Cant_Cañones_Alemanes, int Cant_Soldados_Alemanes);
    //Movimiento
    void keyPressEvent(QKeyEvent *event) override;
    void Primer_Modulo();
    void Segundo_Modulo();

    ~Nivel1();
};

#endif // NIVEL1_H
