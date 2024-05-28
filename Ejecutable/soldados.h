#ifndef SOLDADOS_H
#define SOLDADOS_H
#include <QString>
#include <QGraphicsPixmapItem>
#include <QPixmap>

using namespace std;

enum class Nacionalidad{
    Aleman,
    Frances
};

enum class Direccion{
    Derecha,
    Izquierda,
    Arriba,
    Abajo
};

class Soldados
{

    int Vida;
    QPixmap Direccion_Imagen;
    Direccion Orientacion;
    Nacionalidad nacionalidad;
    QGraphicsPixmapItem* Objeto_En_La_Pantalla;

public:
    Soldados(Nacionalidad nacion);


    void setIamgen(QPixmap NuevaImagen);

    QGraphicsPixmapItem *get_Objeto_En_La_Pantalla();
    QPixmap Get_Imagen();

    int Get_Vida() const;
    void Set_Vida(int Nueva_vida);

    void Set_Direccion(Direccion Pos);
    Direccion Get_Direccion();

    ~Soldados();

};


#endif // SOLDADOS_H
