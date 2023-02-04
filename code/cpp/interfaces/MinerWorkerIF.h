#pragma once

#include <QObject>
#include <QString>
#include <QEventWrapper.h>

class QTimer;

namespace crawl {

DEFINE_QEVENT(StartUpPhpEvent)
DEFINE_QEVENT(ShutDownPhpEvent)
DEFINE_QEVENT(DomReadyEvent)
DEFINE_QEVENT(BeginMiningEvent)
DEFINE_QEVENT(EndMiningEvent)
DEFINE_QEVENT(MatchStepEvent)
DEFINE_QEVENT(MineStepEvent)
DEFINE_QEVENT(NavigateStepEvent)

DEFINE_QEVENT1(RunPhpSnippetEvent, QString, phpCode)
DEFINE_QEVENT1(PostStringEvent, QString, str)
DEFINE_QEVENT2(LoadMinerCodeEvent, QString, scriptCode, QString, scriptAbsPath)

class MinerWorkerIF : public QObject
{
    Q_OBJECT
public:
    enum class TaskDone {startUpPhp, shutDownPhp,
                         domReady,
                         loadMinerScript, runSetupFunctions,
                         beginMining, endMining,
                         matchStep, mineStep, navigateStep,
                         runPhpSnippet

    };
    explicit MinerWorkerIF();


signals:
    void            workDoneSignal(crawl::MinerWorkerIF::TaskDone done);

public slots:
    virtual void    startUpPhpSlot() = 0;
    virtual void    shutDownPhpSlot() = 0;
    virtual void    onTimeoutSlot() = 0;

    virtual void    domReadySlot() = 0;

    virtual void    loadMinerScriptSlot(const QString& phpMinerScript, const QString& scriptAbsPath) = 0;
    virtual void    runSetupFunctionsSlot() = 0;
    virtual void    beginMiningSlot(bool restart) = 0;
    virtual void    endMiningSlot() = 0;

    virtual void    matchStepSlot() = 0;
    virtual void    mineStepSlot() = 0;
    virtual void    navigateStepSlot() = 0;
    virtual void    doOnPageLoadedSlot() = 0;

    virtual void    runPhpSnippetSlot(const QString& phpCode) = 0;
private:
};

} // namespace crawl
