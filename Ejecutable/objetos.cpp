#include "objetos.h"

QString Objetos::get_Direcccion_Imagen()
{
    return Direccion_Imagen;
}

Objetos::Objetos(Tipo Clasificacion)
{
    switch (Clasificacion) {
    case Tipo::Cañones:
        Direccion_Imagen = "C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Objetos/Mortero_Aleman.png";
        break;
        case Tipo::Granadas:
        // Inicializar para Granadas
        break;
    case Tipo::Balas:
        // Inicializar para Balas
        break;
    case Tipo::Gas_Mostaza:
        // Inicializar para Gas de Mostaza
        break;
    case Tipo::Explosion:
        // Inicializar para Explosión
        break;
    default:
        break;
    }
}
