#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include "nivel1.h"

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicsView(QWidget *parent = nullptr);

    void setNivel(Nivel1 *nivel);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Nivel1 *nivel;
};

#endif // MYGRAPHICSVIEW_H
