#pragma once

#include <map>
#include <vector>
#include <string>
#include <utility>
#include <optional>

namespace crawl {
    class Node {

        public:
        struct Attribute {
            std::string name;
            std::string value;
        };

            Node() {}
            //Node(const Node &rhs); //uses default
            ~Node() {}

            void                text            (const std::string& text)   { this->m_Text = text; }
            const std::string&  text            () const                    { return this->m_Text; }

            void                closingText     (const std::string &text)   { this->m_ClosingText = text; }
            const std::string&  closingText     () const                    { return m_ClosingText; }

            void                offset          (unsigned int offset)       { this->m_Offset = offset; }
            unsigned int        offset          () const                    { return this->m_Offset; }

            void                length          (unsigned int length)       { this->m_Length = length; }
            unsigned int        length          () const                    { return this->m_Length; }

            void                tagName         (const std::string& tagname){ this->m_TagName = tagname; }
            const std::string&  tagName         () const                    { return this->m_TagName; }

            bool                isTag           () const                    { return this->m_IsHtmlTag; }
            void                isTag           (bool is_html_tag)          { this->m_IsHtmlTag = is_html_tag; }

            bool                isEndTag        () const                    { return m_IsEndTag; }
            void                isEndTag        (bool is_end_tag)           { m_IsEndTag = is_end_tag;}

            bool                isComment       () const                    { return this->m_Comment; }
            void                isComment       (bool comment)              { this->m_Comment = comment; }

            int                 linearDomPos    () const                    { return m_LinearDomPos; }
            void                linearDomPosSet (int linearDomPos)          { m_LinearDomPos = linearDomPos;}

            std::optional<std::string> attribute_value(const std::string& attr_name) const
            {
                auto fn = [&](const Attribute& attr) -> bool { return attr.name == attr_name; };
                const auto it = std::find_if(m_Attributes.begin(), m_Attributes.end(), fn);
                if (it != m_Attributes.end()) {
                    return it->value;
                } else {
                    return std::nullopt;
                }
            }

            operator std::string() const;
            std::ostream &operator<<(std::ostream &stream) const;

            const std::vector<Attribute>& attributes() const { return m_Attributes; }
            void parseAttributes();
            void sortAttributes();

            bool operator==(const Node &rhs) const;
    private:

            void attributeAppend    (const std::string& key, const std::string& val) {
                m_Attributes.emplace_back(key, val);
            }

            std::string                         m_Text;
            std::string                         m_ClosingText;
            unsigned int                        m_Offset;
            unsigned int                        m_Length;
            int                                 m_LinearDomPos;
            std::string                         m_TagName;
            std::vector<Attribute>              m_Attributes;
            bool                                m_IsHtmlTag;
            bool                                m_IsEndTag = false;
            bool                                m_Comment;
    };
} // namespace crawl

