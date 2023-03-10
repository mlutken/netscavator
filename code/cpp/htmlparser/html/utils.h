#pragma once
#include <string>
#include <map>
#include <QByteArray>

#include "tree.h"
#include "Node.h"

namespace crawl {

class Uri;


/** Tries to look for <META charset="charset-claimed-by-page" */
std::string detect_charset(const std::string& html);

/** Tries to look for <META charset="charset-claimed-by-page" */
std::string detect_charset(const QByteArray& html);

/** Tries to detect if the buffer is encoded as utf8 */
bool detect_utf8(const char *buf, int size);

/** Trim the argument string at both end and convert sibling blanks
         * into a single space */
std::string single_blank(const std::string& str);

/** Remove html comments from the string */
std::string strip_comments(const std::string& str);

/** Convert html entities into their ISO8859-1 equivalents */
std::string decode_entities(const std::string& str);

/** Get the value of an attribute inside the text of a tag
          * @return empty string if the attribute is not found, or the value of
          * the attribute
          */
std::string get_attribute(const std::string& tag, const std::string& attr);

/** Create absolute url for a link */
std::string convert_link(const std::string &relative, const Uri &root);

/** Create a gml representation of the tree for input of tools like graphviz */
std::string serialize_gml(const tree<crawl::Node> &tr);

/** Map of standard html ASCII entities to replace if the site has
            this messed up. See for example bike24.com.
            See here:
            https://www.ascii.cl/htmlcodes.htm
            https://www.freeformatter.com/html-entities.html
            https://www.w3.org/wiki/Common_HTML_entities_used_for_typography
            :		&#58; (&#3A;)	Colon
            /		&#47; (&#2F;)	Slash
            ?		&#63; (&#3F;)	Question mark
            ... etc.
        */
const std::map<std::string, std::string>& stdAsciiHtmlEntitiesMap();
} // namespace crawl {


