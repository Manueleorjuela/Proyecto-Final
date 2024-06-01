#ifndef OBJETOS_H
#define OBJETOS_H
#include <QString>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <random>
#include <vector>

using namespace std;

enum class Tipo{
    Cañones,
    Granadas,
    Balas,
    Gas_Mostaza,
    Explosion,
    Gas};

class Objetos
{
private:

    QGraphicsPixmapItem* Objeto_En_La_Pantalla;
    QPixmap Direccion_Imagen;
    double velocidadenX;
    double velocidadenY;
    double Velocidad_Angular;
    double Radio;
    double Num_Vueltas;

    int Punto_Explosion;
    Tipo Clasificacion;
    vector <QGraphicsPixmapItem*> Secuencia_Explosiones;

    //Asignacion aleatoria de las velocidades
    int generarNumeroAleatorio(int, int);

    //Para las balas
    QPixmap Bala;


public:

    double Velocidad_X();
    double Velocidad_Y();
    int Get_Punto_Explosion() const ;

    Tipo Get_Clasificacion();
    QGraphicsPixmapItem* Get_Objeto();
    QPixmap get_Direcccion_Imagen();
    Objetos(Tipo Clasificacion);
    double get_Velocidad_Angular();
    double get_Radio();
    double get_NumVueltas();

    void Oricntacion_Imagen(QPixmap Dir_);

    vector <QGraphicsPixmapItem*> Get_Secuencia_Explosiones();


};

#endif // OBJETOS_H
