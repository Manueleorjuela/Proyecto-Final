#include "soldados.h"

Soldados::Soldados(Nacionalidad nacion)
   : nacionalidad(nacion), Orientacion(Direccion::Izquierda)
{
    switch (nacionalidad) {
    case Nacionalidad::Aleman:
        Vida = 100;
        Direccion_Imagen =QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Frances/Soldado_Frances_Parado_Izquierda.png");
        break;
    case Nacionalidad::Frances:
        Vida = 100;
        Direccion_Imagen = QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Aleman/Soldado_Frances_Parado_Izquierda-removebg-preview.png");
    }
    Objeto_En_La_Pantalla = new QGraphicsPixmapItem(Direccion_Imagen);
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

