#ifndef CRAWL_CRAWLERCOMMANDQUEUE_H
#define CRAWL_CRAWLERCOMMANDQUEUE_H

#include <functional>
#include <QObject>
#include <SingleWriterSingleReaderLocklessFifo.h>

namespace crawl {

class CrawlerCommandQueue : public QObject
{
    Q_OBJECT
public:
    using Cmd = std::function<bool ()>;
private:
    using Fifo = cpaf::concurrent::SingleWriterSingleReaderLocklessFifo<Cmd>;
public:
    using size_type = Fifo::size_type;

    explicit CrawlerCommandQueue(QObject *parent = 0);

    bool        push    ( Cmd&& v )             { return m_fifo.push(std::move(v));    }
    bool        push    ( const Cmd& v )        { return m_fifo.push(v);    }
    bool        pop     ()                      { return m_fifo.pop();      }
    Cmd&        front   ()                      { return m_fifo.front();    }
    bool        full    () const                { return m_fifo.full();     }
    bool        empty   () const                { return m_fifo.empty();    }
    size_type   size    () const                { return m_fifo.size();     }

signals:

public slots:

private:

    Fifo m_fifo;
};

} // namespace crawl

#endif // CRAWL_CRAWLERCOMMANDQUEUE_H
