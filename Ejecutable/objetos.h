#ifndef OBJETOS_H
#define OBJETOS_H
#include <QString>
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
    QString Direccion_Imagen;
public:
    QString get_Direcccion_Imagen();
    Objetos(Tipo Clasificacion);
};

#endif // OBJETOS_H
