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
private:

    int Vida;
    QPixmap Direccion_Imagen;
    Nacionalidad nacionalidad;
    Direccion Orientacion;
    QGraphicsPixmapItem* Objeto_En_La_Pantalla;
    vector <QGraphicsPixmapItem*> Secuencia_Muerte;

    //Imagenes_
    QPixmap Agachado_Derecha;
    QPixmap Agachado_Izquierda;
    QPixmap Parado_Derecha;
    QPixmap Parado_Izquierda;
    //Estado
    bool Vivo;
    void Inicializar_Muerte_Franceses();
    void Inicializar_Muerte_Alemanes();

public:
    Soldados(Nacionalidad nacion);
    Soldados();

    void setIamgen(QPixmap NuevaImagen);
    QGraphicsPixmapItem *get_Objeto_En_La_Pantalla();
    QPixmap Get_Imagen();
    vector <QGraphicsPixmapItem*> get_Secuencia_Muerte();

    int Get_Vida();
    void Set_Vida(int Nueva_vida);

    QPixmap Get_Imagen_Agachado_Derecha();
    QPixmap Get_Imagen_Agachado_Izquierda();
    QPixmap Get_Imagen_Parado_Izquierda();
    QPixmap Get_Imagen_Parado_Derecha();

    void Set_Direccion(Direccion Pos);
    Direccion Get_Direccion();

    bool Get_Vivo();
    void Set_Vivo(bool Estado);

    ~Soldados();

};


#endif // SOLDADOS_H
