#ifndef NIVEL2_H
#define NIVEL2_H
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

class Nivel2:  public QGraphicsScene
{
    Q_OBJECT
public:
    Nivel2(QGraphicsScene *&Fondo);
    void keyPressEvent(QKeyEvent *event) override;
    void Modulo();

private slots:

    void Movimiento_Parabolico(QGraphicsPixmapItem *Objeto, QTimer *timer, double x0, double y0, double vx, double vy, double t);
    void Movimiento_Armonico_Simple(QGraphicsPixmapItem *Objeto, QTimer *timer, double x0, double y0, double amplitud_x, double frecuencia_x, double velocidad_y, double t, double Limite);
    void Secuencia_Animaciones(QGraphicsPixmapItem* Explosion, int Frame, vector<QGraphicsPixmapItem*> Secuencia_Explosiones, int Timer, int Case);

private:
    //Escenas
    QGraphicsScene *Nivel;
    //Limites del mapa
    const int LIMITE_IZQUIERDO = 40;
    const int LIMITE_DERECHO = 370;
    const int LIMITE_ARRIBA = 80;
    const int LIMITE_ABAJO= 500;

    //Para manejar objetos de la escena
    QGraphicsPixmapItem *item;

    //Personaje principal
    Soldados Adolfo;
    void Ubicar_PersonajePrincipal();
    bool Agachado;
    void MoverPersonaje(int deltaX, int deltaY);
    void Ubicar_Personaje_Izquierda();
    void Ubicar_Personaje_Derecha();
    void Agachar_Personaje();

    //Para las bengalas y bombas
    void Lanzar_Bengalas();
    void Lanzar_Bombardeo(double Posicion_X, double Posicion_Y);

    //Ametralladoras
    vector<Objetos> Ametralladoras_EnEscena;
    void Inicializar_Ametralladoras();
    void Ubicar_Ametralladoras();

    ~Nivel2();
};

#endif // NIVEL2_H
