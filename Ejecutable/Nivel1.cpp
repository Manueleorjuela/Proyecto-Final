#include "nivel1.h"
#include <algorithm>
#include <thread>
#include <chrono>

void Nivel1::Inicializar_Franceses()
{
    for (int i = 0; i < Cantidad_Soldados_Franceses; i++){
        Soldados_Franceses_EnEscena.push_back(Soldados(Nacionalidad::Frances));
    }
    Pierre_De_Gaulle = nullptr;
}

void Nivel1::Inicializar_Cañones()
{
    for (int i = 0; i < Cantidad_Cañones_Alemanes; i++){
        Cañones_Alemanes_EnEscena.push_back(Objetos(Tipo::Cañones));
    }
}

Nivel1::Nivel1(QGraphicsScene *&Fondo, int Cant_Franceses, int Cant_Cañones_Alemanes)
{
    Nivel = Fondo;
    Cantidad_Soldados_Franceses = Cant_Franceses;
    Cantidad_Cañones_Alemanes = Cant_Cañones_Alemanes;
    Inicializar_Franceses();
    Inicializar_Cañones();
    Inicializar_Explosiones();
    Inicializar_Proyectiles();
    Timer = new QTimer(this);
    Agachado = false;
    Numero_Bomba = 0;
    Numero_Ronda = 0;
}

void Nivel1::Primer_Modulo()
{
    Añadir_Soldados_FrancesesEscena();
    Añadir_Cañones();
    Ubicar_Cañones();
}

void Nivel1::Añadir_Soldados_FrancesesEscena()
{
    double factor_escala = 0.5;
    for (int i = 0; i < Cantidad_Soldados_Franceses; i++){
        item = Soldados_Franceses_EnEscena[i].get_Objeto_En_La_Pantalla();
        item->setScale(factor_escala);
        item->setPos(670, i * 130);
        Nivel->addItem(item);
    }
    Pierre_De_Gaulle = &Soldados_Franceses_EnEscena[2];
}

void Nivel1::Añadir_Cañones()
{
    double factor_escala = 0.5;

    for (int i = 0; i < Cantidad_Cañones_Alemanes; i++){
        item = Cañones_Alemanes_EnEscena[i].Get_Objeto();
        item->setScale(factor_escala);
        item->setPos(20/*-100*/, (i + 1) * 100);
        Nivel->addItem(item);
    }
}

void Nivel1::Ubicar_Cañones()
{
    connect(Timer, &QTimer::timeout, this, &Nivel1::Posicion_Canon);
    Timer->start(100);
}

void Nivel1::Lanzamiento_Proyectiles()
{
    Numero_Ronda++;
    Ubicar_Proyectiles();
    Ejecutar_Movimiento_Parabolico();
    Proyectiles_Ronda.clear();
}

void Nivel1::Ubicar_Proyectiles()
{
    for (int k = 0; k < int(Proyectiles_Ronda.size()); k++){
    item = Proyectiles_Ronda[k].Get_Objeto();
    item->setScale(0.05);
    item->setPos(Cañones_Alemanes_EnEscena[k].Get_Objeto()->x()+40, Cañones_Alemanes_EnEscena[k].Get_Objeto()->y()-10);
    Nivel->addItem(item);
    }
}

void Nivel1::Ejecutar_Movimiento_Parabolico()
{
    QTimer* timer;
    QGraphicsPixmapItem* item;
    QGraphicsPixmapItem* Explosion;
    int Limite_;
    double x0;
    double y0;
    double vx;
    double vy;

    for (int i = 0; i < int(Proyectiles_Ronda.size()); ++i) {
        timer = new QTimer(this);
        item = Proyectiles_Ronda[i].Get_Objeto();
        Explosion = Explosiones[i].Get_Objeto();
        Limite_ = Limite();
        x0 = item->x();
        y0 = item->y();
        vx = Proyectiles_Ronda[i].Velocidad_X();
        vy = Proyectiles_Ronda[i].Velocidad_Y();

        connect(timer, &QTimer::timeout, this, [=]() mutable {
        static double t = 0;
        Movimiento_Parabolico(item, timer, x0, y0, vx, vy, t, Limite_, Explosion);
        t += 0.05; });
        timer->start(20);
    }
}

void Nivel1::Movimiento_Parabolico(QGraphicsPixmapItem* Proyectil, QTimer* timer, double x0, double y0, double vx, double vy, double t, int Limite, QGraphicsPixmapItem* Explosion)
{
    double g = 9.8; // Aceleración debida a la gravedad
    double newX = x0 + vx * t;
    double newY = y0 + vy * t + 0.5 * g * t * t;
    Proyectil->setPos(newX, newY);

    if (newY > y0 + Limite) { // Suponiendo que y0 es el suelo
        Explosion->setPos(newX, newY);
        Secuencia_Explosion(Explosion);
        Proyectil->scene()->removeItem(Proyectil); // Eliminar el proyectil de la escena
        timer->stop(); // Detener el QTimer
        timer->deleteLater();// Eliminar el QTimer después de detenerlo
    }
}

void Nivel1::Secuencia_Explosion(QGraphicsPixmapItem* Explosion)
{
    vector<QGraphicsPixmapItem*> Secuencia_Explosiones = Explosiones[0].Get_Secuencia_Explosiones();
    Explosion->setScale(0.8);
    Nivel->addItem(Explosion);
    QTimer* animTimer = new QTimer(this);
    int frame = 5;

    connect(animTimer, &QTimer::timeout, this, [=]() mutable {
        if (frame > -1) {
            Explosion->setPixmap(Secuencia_Explosiones[frame]->pixmap());
            frame--;
        } else {
            animTimer->stop();
            animTimer->deleteLater();
            Nivel->removeItem(Explosion); // Eliminar la explosión de la escena después de la animación
            delete Explosion; // Liberar la memoria de la explosión
        }
    });
    animTimer->start(100); // Cambiar la imagen cada 100 ms
}

int Nivel1::Limite()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0,10);
    return dis(gen);
}

void Nivel1::Inicializar_Explosiones()
{
    for (int i = 0; i < Cantidad_Cañones_Alemanes; i++){
        Explosiones.push_back(Objetos(Tipo::Explosion));
    }
}

void Nivel1::Posicion_Canon()
{
    bool todosAlcanzaronPosicionFinal = true;
    int Posicion_X = 0;

    for (int i = 0; i < Cantidad_Cañones_Alemanes; i++){
        item = Cañones_Alemanes_EnEscena[i].Get_Objeto();
        Posicion_X = item->x();
        if (Posicion_X < 50) {
            item->setX(Posicion_X + 1);
            todosAlcanzaronPosicionFinal = false;
        }
    }
    if (todosAlcanzaronPosicionFinal) {
        Timer->stop();
        Lanzamiento_Proyectiles();
    }
}

void Nivel1::Inicializar_Proyectiles()
{
    for (int k = 0; k < Cantidad_Cañones_Alemanes; k++){
        Proyectiles_Ronda.push_back(Objetos(Tipo::Granadas));
    }
}

Nivel1::~Nivel1()
{
    delete item;
    delete Timer;
}

void Nivel1::keyPressEvent(QKeyEvent *event)
{

        switch (event->key()) {
        case Qt::Key_A:
            MoverPersonaje(-2,0);
            Ubicar_Personaje_Izquierda();
            Pierre_De_Gaulle->Set_Direccion(Direccion::Izquierda);
            break;
        case Qt::Key_D:
            MoverPersonaje(2, 0);
            Ubicar_Personaje_Derecha();
            Pierre_De_Gaulle->Set_Direccion(Direccion::Derecha);
            break;
        case Qt::Key_W:
            Pierre_De_Gaulle->Set_Direccion(Direccion::Arriba);
            MoverPersonaje(0, -2);
            break;
        case Qt::Key_S:
            Pierre_De_Gaulle->Set_Direccion(Direccion::Abajo);
            MoverPersonaje(0, 2);
            break;
        case Qt::Key_C:
            Agachar_Personaje();
            break;
        }
}

void Nivel1::MoverPersonaje(int deltaX, int deltaY)
{
    QGraphicsPixmapItem *Pierre_De_Gaulle_EnEscena = Pierre_De_Gaulle->get_Objeto_En_La_Pantalla();


    int Posicion_X = Pierre_De_Gaulle_EnEscena->x() + deltaX;
    int Posicion_Y = Pierre_De_Gaulle_EnEscena->y() + deltaY;

    // Limitar las posiciones a los límites definidos
    Posicion_X = clamp(Posicion_X, LIMITE_IZQUIERDO, LIMITE_DERECHO);
    Posicion_Y = clamp(Posicion_Y, LIMITE_ARRIBA, LIMITE_ABAJO);

    // Actualizar las posiciones del personaje
    Pierre_De_Gaulle_EnEscena->setX(Posicion_X);
    Pierre_De_Gaulle_EnEscena->setY(Posicion_Y);
}

void Nivel1::Ubicar_Personaje_Izquierda()
{

    if (!Agachado){
            Pierre_De_Gaulle->setIamgen(QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Frances/Soldado_Frances_Parado_Izquierda-removebg-preview.png"));
    }else{
            Pierre_De_Gaulle->setIamgen(QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Frances/Soldado_Frances_Agachado_Izquierda-removebg-preview.png"));
    }
    Pierre_De_Gaulle->get_Objeto_En_La_Pantalla()->setPixmap(Pierre_De_Gaulle->Get_Imagen());
}

void Nivel1::Ubicar_Personaje_Derecha()
{

    if (!Agachado){
        Pierre_De_Gaulle->setIamgen(QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Frances/Soldado_Frances_Parado_Derecha-removebg-preview.png"));
    }else{
        Pierre_De_Gaulle->setIamgen(QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Frances/Soldado_Frances_Agachado_Derecha-removebg-preview.png"));
    }
    Pierre_De_Gaulle->get_Objeto_En_La_Pantalla()->setPixmap(Pierre_De_Gaulle->Get_Imagen());
}

void Nivel1::Agachar_Personaje()
{

    Orientacion = Pierre_De_Gaulle->Get_Direccion();

    if(!Agachado){
        switch(Orientacion){
        case Direccion::Izquierda:
            Pierre_De_Gaulle->setIamgen(QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Frances/Soldado_Frances_Agachado_Izquierda-removebg-preview.png"));
            break;
        case Direccion::Derecha:
            Pierre_De_Gaulle->setIamgen(QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Frances/Soldado_Frances_Agachado_Derecha-removebg-preview.png"));
            break;
        case Direccion:: Arriba:
            Pierre_De_Gaulle->setIamgen(QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Frances/Soldado_Frances_Agachado_Izquierda-removebg-preview.png"));
            break;
        case Direccion::Abajo:
            Pierre_De_Gaulle->setIamgen(QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Frances/Soldado_Frances_Agachado_Derecha-removebg-preview.png"));
            break;
        default:
            break;
        }
    }
    else{
        switch(Orientacion){
        case Direccion::Izquierda:
            Pierre_De_Gaulle->setIamgen(QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Frances/Soldado_Frances_Parado_Izquierda-removebg-preview.png"));
            break;
        case Direccion::Derecha:
            Pierre_De_Gaulle->setIamgen(QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Frances/Soldado_Frances_Parado_Derecha-removebg-preview.png"));
            break;
        case Direccion::Arriba:
            Pierre_De_Gaulle->setIamgen(QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Frances/Soldado_Frances_Parado_Izquierda-removebg-preview.png"));
            break;
        case Direccion::Abajo:
            Pierre_De_Gaulle->setIamgen(QPixmap("C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Soldados/Frances/Soldado_Frances_Parado_Izquierda-removebg-preview.png"));
            break;
        default:
            break;
        }
    }
    Agachado = !Agachado;
    Pierre_De_Gaulle->get_Objeto_En_La_Pantalla()->setPixmap(Pierre_De_Gaulle->Get_Imagen());
}
