#pragma once

#include <QObject>
#include <QQuickImageProvider>
#include <QTimer>
#include <QAbstractListModel>

#include "WQMLCanvasHandler.h"
#include "WQMLCanvasComponentStroke.h"
#include "WQMLCanvasComponentPage.h"
#include "touch/UpdateEvent.h"
#include "ControllerPopupCanvas.h"

class ControllerCanvas final: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(double positionX READ positionX WRITE setPositionX NOTIFY positionXChanged);
    Q_PROPERTY(double positionY READ positionY WRITE setPositionY NOTIFY positionYChanged);
    Q_PROPERTY(int heightObject READ getHeightObject NOTIFY onHeightObjectChanged);
    Q_PROPERTY(int widthObject READ getWidthObject NOTIFY onWidthObjectChanged);
private:
    int _width;
    int _height;

    void wSetWidth(int newWidth);
    void wSetHeight(int newHeight);

    ControllerPopupCanvas* _controllerPopupCanvas;

#ifdef DEBUGINFO
    enum waitingFor {
        begin,
        update
    };

    /**
     * indicates the last function call
    */
    enum waitingFor _status;

#endif // DEBUGINFO

public:
    explicit ControllerCanvas(QObject *parent = nullptr);
    ~ControllerCanvas() = default;

    auto getHeightObject() const -> int;
    auto getWidthObject() const -> int;

    auto positionX() const -> double;
    auto positionY() const -> double;

    void setPositionX(double newPosition);
    void setPositionY(double newPosition);

    void setFunc(std::function<void (QPainter &, double, WFlags<UpdateEvent::UpdateEventType>)> getImg);

    auto rowCount(const QModelIndex& parent) const -> int override;
    auto data( const QModelIndex& index, int role = Qt::DisplayRole ) const -> QVariant override;
    auto roleNames() const -> QHash<int, QByteArray> override;

    static void registerDrawerPage(WQMLCanvasComponentPage* object);
    static void unregisterDrawerPage(WQMLCanvasComponentPage* object);

    static void registerDrawerStroke(WQMLCanvasComponentStroke* object);
    static void unregisterDrawerStroke(WQMLCanvasComponentStroke* object);

    static void registerHandler(WQMLCanvasHandler* object);
    static void unregisterHandler(WQMLCanvasHandler* object);

private:
    double _positionX;
    double _positionY;

    /**
     * If true it means that we are waiting for the scheduler
     * to call the update function in the page object
     * */
    bool _isWaitingForDrawInPage = false;
    UpdateEvent eventWaiting = {UpdateEvent::stroke};

    std::function<void (QPainter &painter, double width, WFlags<UpdateEvent::UpdateEventType> updateFlag)> _getImg;

    /**
     * @brief Call this method to update the canvas on the screen
     * */
    static void callUpdate(const UpdateEvent& event);

    /**
     * @brief Call this method to update a specific page
     * @param page -1 if you want to update all pages, otherwise pass the index of the page you want to refresh
     * */
    static void callUpdatePage(int page);

public slots:
    void refresh(const UpdateEvent& event);
    void sizeHasChanged(const QSizeF &size);
    void touchBegin(const QPointF &point, double pressure);
    void touchUpdate(const QPointF &point, double pressure);
    void touchEnd(const QPointF &point, double pressure);

    void duplicateData(int row);
    void removeData(int row);

protected:
    bool event(QEvent *event) override;

signals:
    void onTouchBegin(const QPointF &point, double pressure);
    void onTouchUpdate(const QPointF &point, double pressure);
    void onTouchEnd(const QPointF &point, double pressure);
    void positionXChanged();
    void positionYChanged();
    /**
     * Il parametro newPosition indica la nuova posizione in pixel
    */
    void positionChanged(const QPointF &newPosition);

    void onWidthObjectChanged();
    void onHeightObjectChanged();
};
