#include "CrawlerCommandQueue.h"

namespace crawl {

CrawlerCommandQueue::CrawlerCommandQueue(QObject *parent)
    : QObject(parent),
      m_fifo(100)
{

}

} // namespace crawl

