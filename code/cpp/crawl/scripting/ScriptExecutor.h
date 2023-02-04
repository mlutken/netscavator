#pragma once

#include <boost/shared_ptr.hpp>
#include <QObject>

namespace crawl {

class ScriptingClassIF;
class ScriptMinerIF;

class ScriptExecutor : public QObject
{
    Q_OBJECT
public:
    explicit ScriptExecutor(QObject *parent = nullptr);
    ~ScriptExecutor() override;

    boost::shared_ptr<ScriptingClassIF>         scriptingClass();
    const boost::shared_ptr<ScriptingClassIF>   scriptingClass() const;

    void startup        (const boost::shared_ptr<ScriptMinerIF>& scriptMiner) ;
    void shutdown       ();
    void loadMinerCode  (const boost::shared_ptr<ScriptMinerIF>& scriptMiner, const QString& scriptCode,
                         const QString& scriptAbsPath);
    void loadMinerCode  (boost::shared_ptr<ScriptMinerIF> scriptMiner, const QString& scriptAbsPath);
    void loadMinerCode  (const QString& scriptAbsPath);

private:
    boost::shared_ptr<ScriptingClassIF> m_scriptingClassIF;
};

} // namespace crawl
