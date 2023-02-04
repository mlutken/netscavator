#include <zlib.h>
#include "qt_compression.h"

namespace crawl {


/**
 * @brief gUncompress
 * @param data
 * @return
 * @see https://stackoverflow.com/questions/2690328/qt-quncompress-gzip-data#7351507
 */
QByteArray gUncompress(const QByteArray& data)
{
    if (data.size() <= 4) {
        qWarning("gUncompress: Input data is truncated");
        return QByteArray();
    }

    QByteArray result;

    int ret;
    z_stream strm;
    static const int CHUNK_SIZE = 1024;
    char out[CHUNK_SIZE];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = static_cast<unsigned int>(data.size());
    char* non_const_data = const_cast<char*>(data.data());
    strm.next_in = reinterpret_cast<Bytef*>(non_const_data);

    ret = inflateInit2(&strm, 15 +  32); // gzip decoding
    if (ret != Z_OK)
        return QByteArray();

    // run inflate()
    do {
        strm.avail_out = CHUNK_SIZE;
        strm.next_out = reinterpret_cast<Bytef*>(out);

        ret = inflate(&strm, Z_NO_FLUSH);
        Q_ASSERT(ret != Z_STREAM_ERROR);  // state not clobbered

        switch (ret) {
        case Z_NEED_DICT:
            ret = Z_DATA_ERROR;     // and fall through
            [[fallthrough]];

        case Z_DATA_ERROR:
            [[fallthrough]];

        case Z_MEM_ERROR:
            (void)inflateEnd(&strm);
            return QByteArray();
        }

        result.append(out, CHUNK_SIZE - static_cast<int>(strm.avail_out));
    } while (strm.avail_out == 0);

    // clean up and return
    inflateEnd(&strm);
    return result;
}

} // namespace crawl
