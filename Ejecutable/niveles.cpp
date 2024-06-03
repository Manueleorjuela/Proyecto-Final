#include "niveles.h"


Niveles::Niveles()
{
    Escena = new QGraphicsScene;
}

void Niveles::Cargar_PantallaInicial()
{
    Direccion_Fondo = ":/Escenas/Imagenes_Proyecto/Fondos/Menu_Inicio.png";
    Pixmap = new QPixmap(Direccion_Fondo);
    PixmapAjustado = Pixmap->scaled(798, 598, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    Escena->addPixmap(PixmapAjustado);
    Pixmap = nullptr;
}

void Niveles::Cargar_Primer_Nivel()
{
    Remover_Fondo();
    Direccion_Fondo = ":/Escenas/Imagenes_Proyecto/Fondos/Primer nivel_.png";
    Pixmap = new QPixmap(Direccion_Fondo);
    PixmapAjustado = Pixmap->scaled(798, 598, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    Escena->addPixmap(PixmapAjustado);
    Pixmap = nullptr;
}

void Niveles::Cargar_Segundo_Nivel()
{

    Direccion_Fondo = "C:/Users/UsuarioCS/OneDrive/Documentos/ProyectoFinal/Imagenes_Proyecto/Fondos/Segundo nivel.png";
    Pixmap = new QPixmap(Direccion_Fondo);
    Escena->addPixmap(*Pixmap);
    PixmapAjustado = Pixmap->scaled(798, 598, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    Escena->addPixmap(PixmapAjustado);
    Pixmap = nullptr;
}

void Niveles::Remover_Fondo()
{
    QList<QGraphicsItem*> Items = Escena->items();
    for (QGraphicsItem* item : Items) {
        Escena->removeItem(item);
        delete item;
    }
}

QGraphicsScene *Niveles::Get_Escena()
{
    return Escena;
}

Niveles::~Niveles()
{
    delete Escena;
    delete Pixmap;
}
