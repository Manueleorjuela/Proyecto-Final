#ifndef SOLDADOS_H
#define SOLDADOS_H
#include <QString>
using namespace std;

enum class Nacionalidad{
    Aleman,
    Frances
};

class Soldados
{
    int Vida;
    QString Direccion_Imagen;
    Nacionalidad nacionalidad;

public:
    Soldados(Nacionalidad nacion);
    void Movimiento_Soldado();


    int Get_Vida() const;
    void Set_Vida(int Nueva_vida);
    QString Get_Direccion_Imagen();
};


#endif // SOLDADOS_H
