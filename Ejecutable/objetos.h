#ifndef OBJETOS_H
#define OBJETOS_H
#include <QString>
#include <QGraphicsPixmapItem>
#include <QPixmap>

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
    Tipo Clasificacion;
public:
    Tipo Get_Clasificacion();
    QGraphicsPixmapItem* Get_Objeto();
    QPixmap get_Direcccion_Imagen();
    Objetos(Tipo Clasificacion);
};

#endif // OBJETOS_H
