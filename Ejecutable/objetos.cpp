#include "objetos.h"


int Objetos::generarNumeroAleatorio()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(45, 52);
    return dis(gen);
}

double Objetos::Velocidad_X()
{
    return velocidadenX;
}

double Objetos::Velocidad_Y()
{
    return velocidadenY;
}

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
        Objeto_En_La_Pantalla = new QGraphicsPixmapItem(Direccion_Imagen);
        break;
        case Tipo::Granadas:
        Direccion_Imagen = QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Objetos/Bomba-removebg-preview.png");
        velocidadenX = generarNumeroAleatorio();
        velocidadenY = -(generarNumeroAleatorio());
        Objeto_En_La_Pantalla = new QGraphicsPixmapItem(Direccion_Imagen);
        break;
    case Tipo::Balas:
        // Inicializar para Balas
        break;
    case Tipo::Gas_Mostaza:
        // Inicializar para Gas de Mostaza
        break;
    case Tipo::Explosion:
        for (int i = 6; i > 0; i--){
            Direccion_Imagen = QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Efectos/Explosion/Explosion_Momento" + QString::number(i) + "-removebg-preview.png");
            Objeto_En_La_Pantalla = new QGraphicsPixmapItem(Direccion_Imagen);
            Secuencia_Explosiones.push_back(Objeto_En_La_Pantalla);
        }
        break;
    default:
        break;
    }
}

vector<QGraphicsPixmapItem *> Objetos::Get_Secuencia_Explosiones()
{
    return Secuencia_Explosiones;
}


