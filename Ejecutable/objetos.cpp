#include "objetos.h"

Tipo Objetos::Get_Clasificacion()
{
    return Clasificacion;
}

QGraphicsPixmapItem* Objetos::Get_Objeto()
{
    return Objeto_En_La_Pantalla;
}

QPixmap Objetos::get_Direcccion_Imagen()
{
    return Direccion_Imagen;
}

Objetos::Objetos(Tipo Clasificacion)
{
    switch (Clasificacion) {
    case Tipo::Cañones:
        Direccion_Imagen = QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Objetos/Mortero_Aleman.png");
        break;
        case Tipo::Granadas:
        Direccion_Imagen = QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Objetos/Bomba-removebg-preview.png");
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
    Objeto_En_La_Pantalla = Objeto_En_La_Pantalla = new QGraphicsPixmapItem(Direccion_Imagen);
}
