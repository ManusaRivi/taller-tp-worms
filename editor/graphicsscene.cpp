#include "graphicsscene.h"

GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent) {
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
        if (item && item->type() == QGraphicsPixmapItem::Type) {
            offset_ = item->mapFromScene(event->scenePos());
            dragging_ = true;
        }
    }

    QGraphicsScene::mousePressEvent(event);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (dragging_) {
        QPointF newPos = event->scenePos() - offset_;
        QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
        if (item && item->type() == QGraphicsPixmapItem::Type) {
            static_cast<QGraphicsPixmapItem*>(item)->setPos(newPos);
        }
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragging_ = false;
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

