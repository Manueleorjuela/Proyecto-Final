#include "objetos.h"


int Objetos::generarNumeroAleatorio(int a, int b)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(a,b);
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

int Objetos::Get_Punto_Explosion() const
{
    return Punto_Explosion;
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
        velocidadenX = generarNumeroAleatorio(45,52);
        velocidadenY = -(generarNumeroAleatorio(45,52));
        Punto_Explosion = generarNumeroAleatorio(0,10);
        Objeto_En_La_Pantalla = new QGraphicsPixmapItem(Direccion_Imagen);
        break;
    case Tipo::Balas:
        velocidadenX = 1200;
        Direccion_Imagen = QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Objetos/Bala.png");
        Objeto_En_La_Pantalla = new QGraphicsPixmapItem(Direccion_Imagen);
        break;
    case Tipo::Gas_Mostaza:
        for (int i = 5; i > 0; i--){
            Direccion_Imagen = QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Efectos/Gas_Mostaza/Gas_Momento" + QString::number(i) + ".png");
            Objeto_En_La_Pantalla = new QGraphicsPixmapItem(Direccion_Imagen);
            Secuencia_Explosiones.push_back(Objeto_En_La_Pantalla);
        }
        break;
    case Tipo::Explosion:
        for (int i = 5; i > 0; i--){
            Direccion_Imagen = QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Efectos/Explosion/Explosion_Momento" + QString::number(i) + "-removebg-preview.png");
            Objeto_En_La_Pantalla = new QGraphicsPixmapItem(Direccion_Imagen);
            Secuencia_Explosiones.push_back(Objeto_En_La_Pantalla);
        }
        break;
    case Tipo:: Gas:
        Direccion_Imagen = QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Objetos/Gas.png");
        velocidadenX = generarNumeroAleatorio(45,52);
        velocidadenY = -(generarNumeroAleatorio(45,52));
        Punto_Explosion = generarNumeroAleatorio(0,10);
        //Para el movimiento circular
        Velocidad_Angular = generarNumeroAleatorio(10,10);
        Radio = generarNumeroAleatorio(2,4);
        Num_Vueltas = generarNumeroAleatorio(3,5);
        Objeto_En_La_Pantalla = new QGraphicsPixmapItem(Direccion_Imagen);
        break;
    case Tipo::Ametralladoras:
        Direccion_Imagen = QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Objetos/Ametralladora_Francesa.png");
        Objeto_En_La_Pantalla = new QGraphicsPixmapItem(Direccion_Imagen);
        break;
    case Tipo::Bengala:
        Direccion_Imagen = QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Objetos/Bengala.png");
        velocidadenX = generarNumeroAleatorio(30,52);
        velocidadenY = -(generarNumeroAleatorio(30,52));
        Objeto_En_La_Pantalla = new QGraphicsPixmapItem(Direccion_Imagen);
        break;
    case Tipo::Señal_Humo:
        for (int i = 5; i > 0; i--){
            Direccion_Imagen = QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Efectos/Humo/Señal_Humo_Momento" + QString::number(i) + ".png");
            Objeto_En_La_Pantalla = new QGraphicsPixmapItem(Direccion_Imagen);
            Secuencia_Explosiones.push_back(Objeto_En_La_Pantalla);
        }
        break;
    default:
        break;
    }
}

double Objetos::get_Velocidad_Angular()
{
    return Velocidad_Angular;
}

double Objetos::get_Radio()
{
    return Radio;
}

double Objetos::get_NumVueltas()
{
    return Num_Vueltas;
}

void Objetos::Oricntacion_Imagen(QPixmap Dir_)
{
    Direccion_Imagen = Dir_;
}

vector<QGraphicsPixmapItem *> Objetos::Get_Secuencia_Explosiones()
{
    return Secuencia_Explosiones;
}

void Objetos::Set_Durabilidad_Ametralladoras(int Nueva_Durabilidad)
{
    Durabilidad = Nueva_Durabilidad;
}

int Objetos::Get_Durabilidad_Ametralladoras()
{
    return Durabilidad;
}


