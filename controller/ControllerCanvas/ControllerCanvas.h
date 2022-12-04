#pragma once

#include <QObject>
#include <QQuickImageProvider>
#include <QTimer>

class ControllerCanvas: public QQuickImageProvider {
    Q_OBJECT
private:
    QTimer *_timer = nullptr;
    int _value = 5;
    bool _need_refresh;
public:
    ControllerCanvas();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
    QImage requestImage(const QString &id, QSize *size, const QSize& requestedSize) override;

private slots:
    void timerEnd();
};
