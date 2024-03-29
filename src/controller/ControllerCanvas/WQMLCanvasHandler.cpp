#include "WQMLCanvasHandler.h"
#include <QPainter>
#include <QBrush>
#include "ControllerCanvas.h"
#include "touch/dataTouch/page/Page.h"
#include "utils/WCommonScript.h"

WQMLCanvasHandler::WQMLCanvasHandler(QQuickItem *parent)
    : QQuickItem(parent)
    , _h(0)
    , _w(0)
    , _waitingForEnd(false)
    , _targetTouchArea(nullptr)
{
    this->update();

    ControllerCanvas::registerHandler(this);

    qDebug() << "WQMLCanvasComponentStroke constructor call";
}

WQMLCanvasHandler::~WQMLCanvasHandler()
{
    ControllerCanvas::unregisterHandler(this);
}

void WQMLCanvasHandler::touchEventPrivate(QTouchEvent *event)
{
    qDebug() << "WQMLCanvasComponentStroke::touchEvent " << event->type();
    //return QQuickPaintedItem::touchEvent(event);
}

QQuickItem *WQMLCanvasHandler::targetTouchArea() const
{
    return this->_targetTouchArea;
}

void WQMLCanvasHandler::setTargetTouchArea(QQuickItem *targetTouchArea)
{
    if (targetTouchArea == _targetTouchArea)
        return;

    if (_targetTouchArea)
        _targetTouchArea->removeEventFilter(this);

    _targetTouchArea = targetTouchArea;

    if (_targetTouchArea)
        _targetTouchArea->installEventFilter(this);

    emit targetTouchAreaChanged();
}

bool WQMLCanvasHandler::eventFilter(QObject *, QEvent *event)
{
    if (auto *e = dynamic_cast<QMouseEvent*>(event)) {
        if (!_h or !_w)
            return false;

        const double pressure = 0.3;

        // TODO: ri enable the real value of pressure
        //const double pressure = e->points().at(0).pressure() * 5.;

        const double dw1 = 1.;
        const double dh1 = 1.; //Page::getHeight()  /  this->_h;

        auto point = QPointF (
            (e->position().x() - this->_xOrigin)   *  dw1,
            (e->position().y() - this->_yOrigin )  *  dh1// * (Page::getProportion()) * 1.17
        );

        if (e->isBeginEvent()) {
            emit touchBegin(point, pressure);
        } else if (e->isUpdateEvent()) {
            emit touchUpdate(point, pressure);
        } else {
            W_ASSERT(e->isEndEvent());
            emit touchEnd(point, pressure);
        }
        return true;
    }

    if (event->type() == QEvent::TouchUpdate || event->type() == QEvent::TouchBegin || event->type() == QEvent::TouchEnd) {
        //this->touchEventPrivate(dynamic_cast<QTouchEvent *>(event));
        //return true;
    }

    return false;
}
