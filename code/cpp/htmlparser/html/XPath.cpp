#include "XPath.h"
#include <vector>
#include <cpaf_libs/unicode/cpaf_u8string_split.h>
#include <cpaf_libs/unicode/cpaf_u8string_utils.h>
#include <cpaf_libs/unicode/cpaf_u8string_parse_numbers.h>

using namespace std;
namespace cu = cpaf::unicode;

namespace crawl {


XPath::XPath(std::string_view path)
{
    fromString(path);
}

void XPath::fromString(std::string_view path)
{
    const auto parts = cu::split_trim(path, "/");
    for (const auto part : parts) {
        const auto tag = tagFromPathPart(part);
        if (tag.empty()) {
            continue;
        }
        const auto index = indexFromPathPart(part);
        emplace_back(tag, index);
    }
}

std::string XPath::toString() const
{
    string p{"/"};
    const auto it = elems_.begin();

    auto i = 0;
    for (const auto& e: elems_) {
        if (i > 0) { p.append(1, '/'); }
        p.append(e.tagName);
        if (e.index > 0) {
            p.append(1, '[').append(to_string(e.index)).append(1, ']');
        }

        ++i;
    }
    return p;
}

string XPath::tagFromPathPart(const std::string& path_part)
{
    auto tag = cu::substring_between(path_part, "", "[");
    if (!tag.empty()) {
        return tag;
    }
    return path_part;
}

int32_t XPath::indexFromPathPart(const std::string& path_part)
{
    return static_cast<int32_t>(cu::parse_long(cu::substring_between(path_part, "[", "]"), 0));
}


} // namespace htmlcxx
