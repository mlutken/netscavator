#pragma once

#include <string>
#include <deque>
#include <cstdint>

namespace crawl {


class XPath
{
public:
    struct Elem {
        std::string tagName;
        int32_t     index;
    };
    using ElemsList = std::deque<Elem>;
    using const_iterator = ElemsList::const_iterator;

    XPath  () = default;
    explicit XPath  (std::string_view path);

    void            fromString      (std::string_view path);

    void            push_front      (Elem e)                                { elems_.push_front(std::move(e));  }
    void            emplace_front   (const std::string& tag, int32_t i)     { elems_.emplace_front(tag, i);     }
    void            push_back       (Elem e)                                { elems_.push_back(std::move(e));   }
    void            emplace_back    (const std::string& tag, int32_t i)     { elems_.emplace_back(tag, i);      }
    size_t          size            () const                                { return elems_.size();             }
    bool            empty           () const                                { return elems_.empty();            }
    std::string     toString        () const;

    const_iterator  begin           () const    { return elems_.begin();    }
    const_iterator  end             () const    { return elems_.end();      }

private:
    static std::string  tagFromPathPart      (const std::string& path_part);
    static int32_t      indexFromPathPart    (const std::string& path_part);

    ElemsList    elems_;
};

} // namespace htmlcxx

