#pragma once

#include <QObject>
#include <QQmlApplicationEngine>

#include "ControllerList/ControllerList.h"
#include "ControllerCanvas/ControllerCanvas.h"
#include "ControllerToolBar/ControllerToolBar.h"
#include "ControllerPageCounter/ControllerPageCounter.h"
#include "ControllerColor/ControllerColor.h"
#include "ControllerAudio/ControllerAudioRecorder.h"
#include "ControllerAudio/ControllerAudioPlayer.h"
#include "QtQml/qqmlcontext.h"
#include "ControllerSettings/ControllerSettings.h"
#include "ControllerListFiles/ControllerListFiles.h"

/* writernote include */
#include "touch/TabletController.h"

class Controller: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString uiSelected READ getUiSelected WRITE setCurrentPage NOTIFY onUiSelectedChanged);

private:
    Fn<WPath()> _getPath = [this] { return _tabletController->getCurrentPathSaving(); };
    Fn<int()>   _currentPositionRecording = [this] { return _audioRecorder->getSecondRecording(); };
    Fn<bool()>  _isPlaying = [this] { return this->_audioPlayer->isPlaying(); };
    Fn<int()>   _getPositionAudioPlaying = [this] { return this->_audioPlayer->getPositionInSeconds(); };
    Fn<void(const WString&)> _showGenericError = [] (const WString& error) { WDebug(true, "Error: " << error); };

    TabletController *_tabletController;

    QQmlApplicationEngine *_engine;

    PreviewPageController              *_listPreview;
    ControllerAudioRecorder     *_audioRecorder;
    ControllerAudioPlayer       *_audioPlayer;
    ControllerToolBar           *_toolBar;
    ControllerCanvas            *_canvas;
    ControllerPageCounter       *_pageCounter;
    ControllerColor             *_color;
    ControllerSettings          *_settings;
    ControllerListFiles         *_listOfFiles;

    void registerPrivateType();

    static QQmlContext *getContent();

    enum uiSelected {
        Main,
        Settings,
        ListFiles
    };

    enum uiSelected _uiSelected;

public:
    explicit Controller(QObject *parent, QQmlContext* content, QQmlApplicationEngine* engine);
    ~Controller() override;

    static void registerType(const QString &name, QObject *object);

    nd auto getUiSelected() const -> QString;

    void setCurrentPage(QString currentPage);

    static auto instance() -> Controller *;
    static void registerControllerCanvas(ControllerCanvas *controllerCanvas);

    static auto tabletController() -> TabletController *;

signals:
    void onPathSavingChanged();
    void onUiSelectedChanged();

public slots:
    void dropView();
    void newFile();
    void clickSetting();
    void clickBack();
    void showMain();
    void openFile (QString name);

    void stopRecording() noexcept;

    void startRecording() noexcept;
};

inline void Controller::registerType(const QString &name, QObject *object)
{
    QQmlContext *content = Controller::getContent();
    content->setContextProperty(name, object);
};

inline auto Controller::tabletController() -> TabletController *
{
    return Controller::instance()->_tabletController;
}