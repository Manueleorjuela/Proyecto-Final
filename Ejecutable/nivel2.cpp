#include "nivel2.h"

Nivel2::Nivel2(QGraphicsScene *&Fondo)
{
    Nivel = Fondo;
    Inicializar_Ametralladoras();
    Adolfo = Nacionalidad::Aleman;
    Agachado = false;
    Ganar = false;
    Terminar = false;
}

//Personaje principal
void Nivel2::Ubicar_PersonajePrincipal()
{
    item = Adolfo.get_Objeto_En_La_Pantalla();
    item->setScale(0.6);
    item->setPos(60,350);
    Nivel->addItem(item);
}

void Nivel2::MoverPersonaje(int deltaX, int deltaY)
{
    QGraphicsPixmapItem *Adolfo_EnEscena = Adolfo.get_Objeto_En_La_Pantalla();
    int Posicion_X = Adolfo_EnEscena->x() + deltaX;
    int Posicion_Y = Adolfo_EnEscena->y() + deltaY;
    Posicion_X = clamp(Posicion_X, LIMITE_IZQUIERDO, LIMITE_DERECHO);
    Posicion_Y = clamp(Posicion_Y, LIMITE_ARRIBA, LIMITE_ABAJO);
    Adolfo_EnEscena->setX(Posicion_X);
    Adolfo_EnEscena->setY(Posicion_Y);
}

void Nivel2::Ubicar_Personaje_Izquierda()
{
    if (!Agachado){
        Adolfo.setIamgen(Adolfo.Get_Imagen_Parado_Izquierda());
    }else{
        Adolfo.setIamgen(Adolfo.Get_Imagen_Agachado_Izquierda());
    }
    Adolfo.get_Objeto_En_La_Pantalla()->setPixmap(Adolfo.Get_Imagen());
}

void Nivel2::Ubicar_Personaje_Derecha()
{
    if (!Agachado){
        Adolfo.setIamgen(Adolfo.Get_Imagen_Parado_Derecha());
    }else{
        Adolfo.setIamgen(Adolfo.Get_Imagen_Agachado_Derecha());
    }
    Adolfo.get_Objeto_En_La_Pantalla()->setPixmap(Adolfo.Get_Imagen());
}

void Nivel2::Agachar_Personaje()
{
    Direccion Orientacion = Adolfo.Get_Direccion();
    QPixmap nuevaImagen;
    if (!Agachado) {
        switch (Orientacion) {
        case Direccion::Izquierda:
        case Direccion::Arriba:
            nuevaImagen = Adolfo.Get_Imagen_Agachado_Derecha();
            break;
        case Direccion::Derecha:
        case Direccion::Abajo:
            nuevaImagen = Adolfo.Get_Imagen_Agachado_Derecha();
            break;
        default:
            break;
        }
    } else {
        switch (Orientacion) {
        case Direccion::Izquierda:
        case Direccion::Arriba:
            nuevaImagen = Adolfo.Get_Imagen_Parado_Derecha();
            break;
        case Direccion::Derecha:
        case Direccion::Abajo:
            nuevaImagen = Adolfo.Get_Imagen_Parado_Derecha();
            break;
        default:
            break;
        }
    }
    Adolfo.setIamgen(nuevaImagen);
    Agachado = !Agachado;
    Adolfo.get_Objeto_En_La_Pantalla()->setPixmap(nuevaImagen);
}

void Nivel2::Colisiones_Personaje_Principal()
{
    QGraphicsPixmapItem* Pantalla = Adolfo.get_Objeto_En_La_Pantalla();
    QList<QGraphicsItem*> itemsColisionados = Pantalla->collidingItems();
    QString tipoObjeto;
    QGraphicsPixmapItem* Imagen_Colision;

    if (!itemsColisionados.isEmpty()) {
        for (QGraphicsItem* item : itemsColisionados) {
            Imagen_Colision = dynamic_cast<QGraphicsPixmapItem*>(item);
            if (Imagen_Colision) {
                tipoObjeto = Imagen_Colision->data(Qt::UserRole).toString();
                if (tipoObjeto == "Bala") {
                    Muerte_Adolfo(100);
                }
                Colisiones_Personaje->stop();
                QTimer::singleShot(500, this, [this]() {
                Colisiones_Personaje->start(100);
                });
                break;
            }
        }
        itemsColisionados.clear();
    }
}

void Nivel2::Muerte_Adolfo(int Daño)
{
    int Vida_Actual = Adolfo.Get_Vida();
    int Nueva_Vida = Vida_Actual - Daño;
    if (!Agachado){
        Adolfo.Set_Vida(Vida_Actual-Daño);
            if (Nueva_Vida <= 0){
            Secuencia_Animaciones(Adolfo.get_Objeto_En_La_Pantalla(), 3, Adolfo.get_Secuencia_Muerte(), 300,0);
            Adolfo.Set_Vivo(false);
        }
    }
}

void Nivel2::Lanzar_Bengalas()
{
    Objetos Bengala(Tipo::Bengala);
    QTimer *Timer_ = new QTimer(this);
    QGraphicsPixmapItem *item;
    item = Bengala.Get_Objeto();
    item->setScale(0.05);
    item->setPos(Adolfo.get_Objeto_En_La_Pantalla()->x()+20, Adolfo.get_Objeto_En_La_Pantalla()->y()+10);
    Nivel->addItem(item);

    double vx = Bengala.Velocidad_X();
    double vy = Bengala.Velocidad_Y();
    double x0 = item->x();
    double y0 = item->y();
    double t = 0;
    connect(Timer_, &QTimer::timeout, this, [=]() mutable {
        Movimiento_Parabolico(item, Timer_, x0, y0, vx, vy, t);
        t += 0.15;
    });
    Timer_->start(1);
}

void Nivel2::Movimiento_Parabolico(QGraphicsPixmapItem *Objeto, QTimer *timer, double x0, double y0, double vx, double vy, double t)
{

    double g = 9.8;
    double newX = x0 + vx * t;
    double newY = y0 + vy * t + 0.5 * g * t * t;
    Objeto->setPos(newX, newY);
    if (newY > y0 ) {
        Objetos Señal (Tipo::Señal_Humo);
        QGraphicsPixmapItem* Efecto = Señal.Get_Objeto();
        Efecto->setPos(newX, newY);
        Secuencia_Animaciones(Efecto, 4, Señal.Get_Secuencia_Explosiones(), 400, 1);
        Objeto->scene()->removeItem(Objeto);
        timer->stop();
        timer->deleteLater();
    }
}

void Nivel2::Lanzar_Bombardeo(double Posicion_X, double Posicion_Y)
{
    QGraphicsPixmapItem* item;
    QTimer *Timer_MAS = new QTimer(this);
    Objetos Bomba(Tipo::Granadas);
    item = Bomba.Get_Objeto();
    item->setScale(0.05);
    item->setPos(Posicion_X+40, 0);
    Nivel->addItem(item);
    double t = 0;
    double amplitud_x = 20;
    double frecuencia_x = 1;
    double velocidad_y = 300;
    double x0 = item->x();
    double y0 = item->y();
    connect(Timer_MAS, &QTimer::timeout, this, [=]() mutable {
        Movimiento_Armonico_Simple(item, Timer_MAS, x0, y0, amplitud_x, frecuencia_x, velocidad_y, t, Posicion_Y);
        t += 0.05;
    });
    Timer_MAS->start(20);
}


void Nivel2::Movimiento_Armonico_Simple(QGraphicsPixmapItem *Objeto, QTimer *timer, double x0, double y0, double amplitud_x, double frecuencia_x, double velocidad_y, double t, double Limite)
{
    double omega_x = 2 * M_PI * frecuencia_x;

    double newX = x0 + amplitud_x * sin(omega_x * t);
    double newY = y0 + velocidad_y * t;
    Objeto->setPos(newX, newY);
    if (newY > Limite+0) {
        Objetos Explosion(Tipo::Explosion);
        QGraphicsPixmapItem* item = Explosion.Get_Objeto();
        item->setPos(newX, newY);
        item->setScale(0.4);
        Nivel->removeItem(Objeto);
        item->setData(Qt::UserRole, "Explosion");
        timer->stop();
        timer->deleteLater();
        Secuencia_Animaciones(item, 4, Explosion.Get_Secuencia_Explosiones(), 100, 0);
    }
}

void Nivel2::Secuencia_Animaciones(QGraphicsPixmapItem* Imagen, int frame, vector<QGraphicsPixmapItem*> Secuencia_Animacion, int Timer, int Case)
{
    Nivel->addItem(Imagen);
    QTimer* animTimer = new QTimer(this);
    connect(animTimer, &QTimer::timeout, this, [=]() mutable {
        if (frame > -1) {
            Imagen->setPixmap(Secuencia_Animacion[frame]->pixmap());
            frame--;
        } else {
            animTimer->stop();
            animTimer->deleteLater();
            Nivel->removeItem(Imagen);
            if(Case == 1){
                Lanzar_Bombardeo(Imagen->x(), Imagen->y());
            }
        }
    });
    animTimer->start(Timer);
}

void Nivel2::Movimiento_Rectilineo_Disparos(QGraphicsPixmapItem *Objeto, QTimer *timer, double v0, double x0, double t)
{
    double newX = x0 + v0 * t;
    Objeto->setPos(newX, Objeto->y());
    if (newX > Nivel->width() || newX < 0) {
        timer->stop();
        Nivel->removeItem(Objeto);
        delete Objeto;
        timer->deleteLater();
    }
}

void Nivel2::Inicializar_TodasLas_Colisiones()
{
    Colisiones_Personaje = new QTimer(this);
    connect(Colisiones_Personaje, &QTimer::timeout, this, &Nivel2::Colisiones_Personaje_Principal);
    Colisiones_Ametralladoras_ = new QTimer(this);
    connect(Colisiones_Ametralladoras_, &QTimer::timeout, this, &Nivel2::Colisiones_Ametralladoras);
    Colisiones_Personaje->start(50);
    Colisiones_Ametralladoras_->start(50);

}
void Nivel2::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A:
        MoverPersonaje(-2,0);
        Ubicar_Personaje_Izquierda();
        Adolfo.Set_Direccion(Direccion::Izquierda);
        break;
    case Qt::Key_D:
        MoverPersonaje(2, 0);
        Ubicar_Personaje_Derecha();
        Adolfo.Set_Direccion(Direccion::Derecha);
        break;
    case Qt::Key_W:
        Adolfo.Set_Direccion(Direccion::Arriba);
        MoverPersonaje(0, -2);
        break;
    case Qt::Key_S:
        Adolfo.Set_Direccion(Direccion::Abajo);
        MoverPersonaje(0, 2);
        break;
    case Qt::Key_C:
        Agachar_Personaje();
        break;
    case Qt::Key_L:
        if(!Agachado) Lanzar_Bengalas();
        break;
    }
}

//Ametralladoras
void Nivel2::Inicializar_Ametralladoras()
{
    for (int i = 0; i < 3; i++){
        Ametralladoras_EnEscena.push_back(Objetos(Tipo::Ametralladoras));
    }
}

void Nivel2::Ubicar_Ametralladoras()
{
    for (int i = 0; i < int(Ametralladoras_EnEscena.size()); i++){
        item = Ametralladoras_EnEscena[i].Get_Objeto();
        item->setScale(0.15);
        if (i < 2){
            item->setPos(710, (i+1)*120);
        }else{
            item->setPos(710, (i+2)*120);
        }
        Nivel->addItem(item);
    }
}

bool Nivel2::Probabilidad_Disparos()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0.0, 1.0);
    double probabilityTrue = 0.8;
    return dis(gen) < probabilityTrue;
}

void Nivel2::Disparos_Ametralladora()
{
    Objetos *Ametralladora_Actual;
    for (int i = 0; i < int(Ametralladoras_EnEscena.size()); i++){
        Ametralladora_Actual = &Ametralladoras_EnEscena[i];
        if (Ametralladora_Actual->Get_Durabilidad_Ametralladoras() != 0){
            if(Probabilidad_Disparos()){
                Objetos Bala(Tipo::Balas);
                QTimer *Timer_Disparo = new QTimer();
                QGraphicsPixmapItem *item;
                item = Bala.Get_Objeto();
                item->setScale(0.2);
                item->setPos(Ametralladora_Actual->Get_Objeto()->x()-20, Ametralladora_Actual->Get_Objeto()->y()+12);
                item->setData(Qt::UserRole, "Bala");
                Nivel->addItem(item);
                double vx = -180;
                double x0 = item->x();
                double t = 0;
                connect(Timer_Disparo, &QTimer::timeout, this, [=]() mutable {
                    Movimiento_Rectilineo_Disparos(item, Timer_Disparo, vx, x0, t);
                    t += 0.05;
                });
                Timer_Disparo->start(10);
            }
        }
    }
}

void Nivel2::Inicializar_Disparos()
{
    Disparos = new QTimer(this);
    connect(Disparos, &QTimer::timeout, this, &Nivel2::Disparos_Ametralladora);
    Disparos->start(1000);
}

void Nivel2::Colisiones_Ametralladoras()
{
    for (int i = 0; i < int(Ametralladoras_EnEscena.size()); i++){
        if (Ametralladoras_EnEscena[i].Get_Durabilidad_Ametralladoras() != 0){
            Objetos *Actual = &Ametralladoras_EnEscena[i];
            QGraphicsPixmapItem* Pantalla = Ametralladoras_EnEscena[i].Get_Objeto();
            QList<QGraphicsItem*> itemsColisionados = Pantalla->collidingItems();
            QString tipoObjeto;
            QGraphicsPixmapItem* Imagen_Colision;
            if (!itemsColisionados.isEmpty()) {
                for (QGraphicsItem* item : itemsColisionados) {
                    Imagen_Colision = dynamic_cast<QGraphicsPixmapItem*>(item);
                    if (Imagen_Colision) {
                        tipoObjeto = Imagen_Colision->data(Qt::UserRole).toString();
                        if (tipoObjeto == "Explosion") {
                            Daño_Ametralladoras(25, Actual);
                        }
                        Colisiones_Ametralladoras_->stop();
                        QTimer::singleShot(500, this, [this]() {
                        Colisiones_Ametralladoras_->start(100);
                        });
                        break;
                    }
                }
                itemsColisionados.clear();
            }
        }
    }
}

void Nivel2::Daño_Ametralladoras(int Daño, Objetos *Ametralladoras)
{
    int Nueva_Durabilidad = Ametralladoras->Get_Durabilidad_Ametralladoras() - Daño;
    Ametralladoras->Set_Durabilidad_Ametralladoras(Nueva_Durabilidad);
    if(Nueva_Durabilidad == 0){
        Nivel->removeItem(Ametralladoras->Get_Objeto());
    }
}

void Nivel2::Inicializar_Ejecucion()
{
    Ejecucion_Nivel = new QTimer();
    connect(Ejecucion_Nivel, &QTimer::timeout, this, &Nivel2::Validar_Estados);
    Ejecucion_Nivel->start(100);

}

void Nivel2::Validar_Estados()
{
    int Ametralladoras_Destruidas = 0;
    for (int i = 0; i < int(Ametralladoras_EnEscena.size()); i++){
        if (Ametralladoras_EnEscena[i].Get_Durabilidad_Ametralladoras() == 0){
            Ametralladoras_Destruidas++;
        }
        if(Adolfo.Get_Vivo() == false){
            Terminar = true;
        }
    }
    if (Ametralladoras_Destruidas == int(Ametralladoras_EnEscena.size())){
        Ganar = true;
        Terminar = true;
    }
}

bool Nivel2::get_Ganar()
{
    return Ganar;
}

bool Nivel2::get_Terminar()
{
    return Terminar;
}

void Nivel2::Modulo()
{
    Ubicar_Ametralladoras();
    Ubicar_PersonajePrincipal();
    Inicializar_Disparos();
    Inicializar_TodasLas_Colisiones();
    Inicializar_Ejecucion();
}

Nivel2::~Nivel2()
{
    delete item;
    delete Colisiones_Ametralladoras_;
    delete Colisiones_Personaje;
    delete Disparos;
    delete Ejecucion_Nivel;
}

