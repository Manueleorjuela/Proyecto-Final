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
    vector <QGraphicsPixmapItem*> Secuencia_Muerte;

    void Inicializar_Muerte_Franceses();

public:
    Soldados(Nacionalidad nacion);
    Soldados();

    void setIamgen(QPixmap NuevaImagen);
    QGraphicsPixmapItem *get_Objeto_En_La_Pantalla();
    QPixmap Get_Imagen();
    vector <QGraphicsPixmapItem*> get_Secuencia_Muerte();

    int Get_Vida();
    void Set_Vida(int Nueva_vida);

    void Set_Direccion(Direccion Pos);
    Direccion Get_Direccion();

    ~Soldados();

};


#endif // SOLDADOS_H
