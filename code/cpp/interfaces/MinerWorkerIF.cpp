#include "MinerWorkerIF.h"
#include <QThread>
#include <QTimer>
#include <iostream>

#include <Configuration.h>
#include <Globals.h>


using namespace std;
namespace crawl {


MinerWorkerIF::MinerWorkerIF()
    : QObject()
{
    static bool registeredMetaTypes = false;
    if (!registeredMetaTypes) {
        registeredMetaTypes = true;
        qRegisterMetaType<crawl::MinerWorkerIF::TaskDone>("crawl::MinerWorkerIF::TaskDone");
        qRegisterMetaType<crawl::MinerWorkerIF::TaskDone*>("crawl::MinerWorkerIF::TaskDone*");
    }
}


} // namespace crawl

