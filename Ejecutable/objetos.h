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
    Explosion
};

class Objetos
{
private:

    QGraphicsPixmapItem* Objeto_En_La_Pantalla;
    QPixmap Direccion_Imagen;
    double velocidadenX;
    double velocidadenY;
    Tipo Clasificacion;
    vector <QGraphicsPixmapItem*> Secuencia_Explosiones;

    //Asignacion aleatoria de las velocidades
    int generarNumeroAleatorio();

public:

    double Velocidad_X();
    double Velocidad_Y();
    Tipo Get_Clasificacion();
    QGraphicsPixmapItem* Get_Objeto();
    QPixmap get_Direcccion_Imagen();
    Objetos(Tipo Clasificacion);

    vector <QGraphicsPixmapItem*> Get_Secuencia_Explosiones();


};

#endif // OBJETOS_H
