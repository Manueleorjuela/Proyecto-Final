#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView(QWidget *parent)
    : QGraphicsView(parent), nivel(nullptr)
{
}

void MyGraphicsView::setNivel(Nivel1 *nivel)
{
    this->nivel = nivel;
}

void MyGraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (nivel) {
        nivel->keyPressEvent(event);
    } else {
        QGraphicsView::keyPressEvent(event);
    }
}
