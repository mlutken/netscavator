#ifndef CRAWL_MINERWORKER_H
#define CRAWL_MINERWORKER_H

#include <boost/shared_ptr.hpp>
#include <MinerWorkerIF.h>
class QTimer;
class ScriptMiner;

namespace crawl {

class ScriptExecutor;


class MinerWorker : public MinerWorkerIF
{
    Q_OBJECT
public:
    explicit MinerWorker();
    virtual ~MinerWorker() override;
    virtual bool	event(QEvent * e) override;

    ScriptExecutor *scriptExecutor() const;

    boost::shared_ptr<ScriptMiner> miner() const;
    void minerSet(const boost::shared_ptr<ScriptMiner>& miner);

    bool isExecutingPhp() const;

signals:

public slots:
    void startUpPhpSlot         () override;
    void shutDownPhpSlot        () override;
    void onTimeoutSlot          () override;

    void domReadySlot           () override;

    void loadMinerScriptSlot    (const QString& phpMinerScript, const QString& scriptAbsPath) override;
    void runSetupFunctionsSlot  () override;
    void beginMiningSlot        (bool restart) override;
    void endMiningSlot          () override;

    void matchStepSlot          () override;
    void mineStepSlot           () override;
    void navigateStepSlot       () override;
    void doOnPageLoadedSlot     () override;
    void runPhpSnippetSlot      (const QString& phpCode) override;
private:
    QTimer*                         m_minerWorkerTimer;
    ScriptExecutor*                 m_scriptExecutor;
    boost::shared_ptr<ScriptMiner>  m_miner;
    volatile bool                   m_isExecutingPhp = false;

};

} // namespace crawl

#endif // CRAWL_MINERWORKER_H
