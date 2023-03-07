#pragma once

#include <QObject>
#include <QAbstractListModel>
#include "Files.h"

class ControllerListFiles: public QAbstractListModel
{
    Q_OBJECT
public:
    ControllerListFiles(QObject *parent = nullptr);
    ControllerListFiles(QObject *parent, std::function<QList<File> *()> getFiles);
    ~ControllerListFiles() = default;

    enum Roles {
        Path = Qt::UserRole, /* QByteArray */
        LastModification /*  */
    };

    [[nodiscard]] int rowCount(const QModelIndex& parent) const override;
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

public slots:
    void duplicateData(int row);
    void removeData(int row);

private:
    std::function<QList<File> *()> _getFile;
public:
    void updateList();
};