#pragma once

#include <qqml.h>
#include <QDebug>
#include <QObject>
#include <QList>
#include <QObjectList>
#include <QAbstractListModel>

// TODO: implement
struct PreviewData {
    PreviewData();
    PreviewData( const QString& name, const QString& flag, double population );
};

// preview list
class PreviewPageController : public QAbstractListModel
{
    Q_OBJECT
private:
    bool _isVisible;

public:
    enum Roles {
        Nome = Qt::UserRole,
        Cognome,
        Eta
    };

    explicit PreviewPageController(QObject *parent = nullptr);

    auto rowCount(const QModelIndex& parent) const -> int override;
    auto data( const QModelIndex& index, int role = Qt::DisplayRole ) const -> QVariant override;
    auto roleNames() const -> QHash<int, QByteArray> override;

    Q_PROPERTY(bool isVisible READ isVisible WRITE setVisible NOTIFY isVisibleChanged);
    auto isVisible() const -> bool;
    void setVisible(bool visible);
    Q_SIGNAL void isVisibleChanged();

public slots:
    void duplicateData(int row);
    void removeData(int row);
    void modifiedPages(int page);
    void modifiedPages(const std::vector<int> &page);

private slots:
    void growPopulation();

private: //members

    friend class WQMLItemListComponent;

    auto getImg(int index) -> const QImage &;

    QVector< PreviewData > m_data;

    static auto instance() -> PreviewPageController *;
    static void registerItem(class WQMLItemListComponent *item);
};
