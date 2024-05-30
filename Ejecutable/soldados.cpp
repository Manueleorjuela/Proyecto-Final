#include "soldados.h"

void Soldados::Inicializar_Muerte_Franceses()
{
    for (int i = 4; i > 0; i--){
        Direccion_Imagen = QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Frances/Soldado_Frances_Mueriendo_Momento" + QString::number(i) + "-removebg-preview.png");
        Objeto_En_La_Pantalla = new QGraphicsPixmapItem(Direccion_Imagen);
        Secuencia_Muerte.push_back(Objeto_En_La_Pantalla);
    }
}

Soldados::Soldados(Nacionalidad nacion)
   : nacionalidad(nacion), Orientacion(Direccion::Izquierda)
{
    switch (nacionalidad) {
    case Nacionalidad::Aleman:
        Vida = 100;
        //Direccion_Imagen = QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Frances/Soldado_Frances_Parado_Izquierda.png");
        break;
    case Nacionalidad::Frances:
        Inicializar_Muerte_Franceses();
        Vida = 100;
        Agachado_Derecha = QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Frances/Soldado_Frances_Agachado_Derecha-removebg-preview.png");
        Agachado_Izquierda = QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Frances/Soldado_Frances_Agachado_Izquierda-removebg-preview.png");
        Parado_Izquierda = QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Aleman/Soldado_Frances_Parado_Izquierda-removebg-preview.png");
        Parado_Derecha = QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Aleman/Soldado_Frances_Parado_Derecha-removebg-preview.png");
    }

    Objeto_En_La_Pantalla = new QGraphicsPixmapItem(Parado_Izquierda);
}

Soldados::Soldados()
{

}

void Soldados::setIamgen(QPixmap NuevaImagen)
{
    Direccion_Imagen = NuevaImagen;
}

QGraphicsPixmapItem *Soldados::get_Objeto_En_La_Pantalla()
{
    return Objeto_En_La_Pantalla;
}

QPixmap Soldados::Get_Imagen()
{
    return Direccion_Imagen;
}

vector<QGraphicsPixmapItem *> Soldados::get_Secuencia_Muerte()
{
    return Secuencia_Muerte;
}

int Soldados::Get_Vida()
{
    return Vida;
}

void Soldados::Set_Vida(int Nueva_vida)
{
    Vida = Nueva_vida;
}

QPixmap Soldados::Get_Imagen_Agachado_Derecha()
{
    return Agachado_Derecha;
}

QPixmap Soldados::Get_Imagen_Agachado_Izquierda()
{
    return Agachado_Izquierda;
}

QPixmap Soldados::Get_Imagen_Parado_Izquierda()
{
    return Parado_Izquierda;
}

QPixmap Soldados::Get_Imagen_Parado_Derecha()
{
    return Parado_Derecha;
}

void Soldados::Set_Direccion(Direccion Pos)
{
    Orientacion  = Pos;
}

Direccion Soldados::Get_Direccion()
{
    return Orientacion;
}

Soldados::~Soldados()
{
    //delete Objeto_En_La_Pantalla;
}

