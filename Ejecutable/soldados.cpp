#include "soldados.h"

Soldados::Soldados(Nacionalidad nacion)
    : nacionalidad(nacion)
{
    switch (nacionalidad) {
    case Nacionalidad::Aleman:
        Vida = 100;
        Direccion_Imagen = "C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Frances/Soldado_Frances_Parado_Izquierda.png";
        break;
    case Nacionalidad::Frances:
        Vida = 100;
        Direccion_Imagen = "C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Aleman/Soldado_Frances_Parado_Izquierda-removebg-preview.png";
    }
}

void Soldados::Movimiento_Soldado()
{

}

QString Soldados::Get_Direccion_Imagen()
{
    return Direccion_Imagen;
}
