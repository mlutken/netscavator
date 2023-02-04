#include <algorithm>
#include <cctype>
#include <cstring>
#include <sstream>
#include <iostream>
#include <regex>
#include <boost/algorithm/string.hpp>
#include "Uri.h"

#include "utils.h"

using namespace std;
namespace crawl {

// DETECT charset regex: (<META|<meta)\s+.*charset=?('|")([^ '"]+)
string detect_charset(const std::string& html)
{
    string charset = "";
    const std::regex charset_regex1(R"(<meta\s+.*charset=?('|")([^ '"]+))", std::regex::icase);
    const std::regex charset_regex2(R"(<meta\s+.*charset=([^ '"]+))", std::regex::icase);
    const std::regex charset_regex3(R"(\?xml\s+.*encoding=?('|")([^ \s'"]+))", std::regex::icase);
    const std::regex charset_regex4(R"(\?xml\s+.*encoding=([^ \s'"]+))", std::regex::icase);
    if (std::smatch charset_match; std::regex_search(html, charset_match, charset_regex1)) {
        charset = charset_match[2];
    }
    else if (std::smatch charset_match; std::regex_search(html, charset_match, charset_regex2)) {
        charset = charset_match[1];
    }
    else if (std::smatch charset_match; std::regex_search(html, charset_match, charset_regex3)) {
        charset = charset_match[2]; //<?xml version="1.0" encoding="iso-8859-1"?>
    }
    else if (std::smatch charset_match; std::regex_search(html, charset_match, charset_regex4)) {
        charset = charset_match[1]; //<?xml version="1.0" encoding=iso-8859-1 ?>
    }
    return boost::algorithm::to_lower_copy(charset);
}

// DETECT charset regex: (<META|<meta)\s+.*charset=?('|")([^ '"]+)
// <meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
// @todo Make a better function somewhere and for example use an improved QStringFinder for the task.
string detect_charset(const QByteArray& html)
{
    string charset = "";
    const std::regex charset_regex1(R"(<meta\s+.*charset=?('|")([^ '"]+))", std::regex::icase);
    const std::regex charset_regex2(R"(<meta\s+.*charset=([^ '"]+))", std::regex::icase);
    const std::regex charset_regex3(R"(\?xml\s+.*encoding=?('|")([^ \s'"]+))", std::regex::icase);
    const std::regex charset_regex4(R"(\?xml\s+.*encoding=([^ \s'"]+))", std::regex::icase);

    if (std::cmatch charset_match; std::regex_search(html.constData(), charset_match, charset_regex1)) {
        charset = charset_match[2];
    }
    else if (std::cmatch charset_match; std::regex_search(html.constData(), charset_match, charset_regex2)) {
        charset = charset_match[1];
    }
    else if (std::cmatch charset_match; std::regex_search(html.constData(), charset_match, charset_regex3)) {
        charset = charset_match[2]; //<?xml version="1.0" encoding="iso-8859-1"?>
    }
    else if (std::cmatch charset_match; std::regex_search(html.constData(), charset_match, charset_regex4)) {
        charset = charset_match[1]; //<?xml version="1.0" encoding=iso-8859-1 ?>
    }
    return boost::algorithm::to_lower_copy(charset);
}

bool detect_utf8(const char *begin, int size)
{
    const char *ptr;
    const char *end = begin+size;
    const char *signature = "﻿";
    char previous_byte = 0;
    unsigned count_bad_utf = 0;
    unsigned count_good_utf = 0;

    if (!strncmp(begin, signature, 3)) return true;

    for (ptr = begin; ptr != end; ++ptr)
    {
        if ((*ptr & 0xC0) == 0x80)
        {
            if ((previous_byte & 0xC0) == 0xC0)
            {
                count_good_utf ++;
            }
            else if ((previous_byte & 0x80) == 0x00)
            {
                count_bad_utf ++;
            }
        }
        else if ((previous_byte & 0xC0) == 0xC0)
        {
            count_bad_utf ++;
        }

        previous_byte = *ptr;
    }

    return count_good_utf > count_bad_utf;
}

string single_blank(const string &str) {

    unsigned int count = 0;
    bool first_space = true;
    const char *ptr = str.c_str();

    string ret(str.length(), ' ');

    // Skip space at beginning
    while (isspace(*ptr)) ++ptr;

    while (*ptr)
    {
        if (isspace(*ptr))
        {
            if (first_space)
            {
                first_space = false;
                ret[count++] = ' ';
            }
        }
        else
        {
            first_space = true;
            ret[count++] = *ptr;
        }

        ++ptr;
    }

    // Trim space at the end
    string::size_type a;
    a = ret.find_last_not_of(' ', count);
    if (a != string::npos)
        ret.erase(a+1);
    else
    {
        a = 0;
        ret.erase(a);
    }

    return ret;
}

string strip_comments(const string &str) {

    string ret;
    ret.reserve(str.size());

    const char *ptr = str.c_str();
    const char *end = ptr + str.length();

    bool inside_comment = false;
    while(1) {
        if(!inside_comment) {
            if(ptr  + 4 < end) {
                if(*ptr == '<' && *(ptr+1) == '!' && *(ptr+2) =='-' && *(ptr + 3) == '-' && isspace(*(ptr + 4))) {
                    inside_comment = true;
                }
            }
        } else {
            if(ptr + 2 < end) {
                if(*ptr == '-' && *(ptr+1) == '-' && *(ptr+2) == '>' ) {
                    inside_comment = false;
                    ptr += 3;
                }
            }
        }
        if(ptr == end) break;
        if(!inside_comment) ret += *ptr;
        ptr++;
    }

    ret.resize(ret.size());

    return ret;

}

static struct {
    const char *str;
    unsigned char chr;
} entities[] = {
    /* 00 */
{ "quot", 34 },
{ "amp", 38 },
{ "lt", 60 },
{ "gt", 62 },
{ "nbsp", ' ' },
{ "iexcl", 161 },
{ "cent", 162 },
{ "pound", 163 },
{ "curren", 164 },
{ "yen", 165 },
/* 10 */
{ "brvbar", 166 },
{ "sect", 167 },
{ "uml", 168 },
{ "copy", 169 },
{ "ordf", 170 },
{ "laquo", 171 },
{ "not", 172 },
{ "shy", 173 },
{ "reg", 174 },
{ "macr", 175 },
/* 20 */
{ "deg", 176 },
{ "plusmn", 177 },
{ "sup2", 178 },
{ "sup3", 179 },
{ "acute", 180 },
{ "micro", 181 },
{ "para", 182 },
{ "middot", 183 },
{ "cedil", 184 },
{ "sup1", 185 },
/* 30 */
{ "ordm", 186 },
{ "raquo", 187 },
{ "frac14", 188 },
{ "frac12", 189 },
{ "frac34", 190 },
{ "iquest", 191 },
{ "Agrave", 192 },
{ "Aacute", 193 },
{ "Acirc", 194 },
{ "Atilde", 195 },
/* 40 */
{ "Auml", 196 },
{ "ring", 197 },
{ "AElig", 198 },
{ "Ccedil", 199 },
{ "Egrave", 200 },
{ "Eacute", 201 },
{ "Ecirc", 202 },
{ "Euml", 203 },
{ "Igrave", 204 },
{ "Iacute", 205 },
/* 50 */
{ "Icirc", 206 },
{ "Iuml", 207 },
{ "ETH", 208 },
{ "Ntilde", 209 },
{ "Ograve", 210 },
{ "Oacute", 211 },
{ "Ocirc", 212 },
{ "Otilde", 213 },
{ "Ouml", 214 },
{ "times", 215 },
/* 60 */
{ "Oslash", 216 },
{ "Ugrave", 217 },
{ "Uacute", 218 },
{ "Ucirc", 219 },
{ "Uuml", 220 },
{ "Yacute", 221 },
{ "THORN", 222 },
{ "szlig", 223 },
{ "agrave", 224 },
{ "aacute", 225 },
/* 70 */
{ "acirc", 226 },
{ "atilde", 227 },
{ "auml", 228 },
{ "aring", 229 },
{ "aelig", 230 },
{ "ccedil", 231 },
{ "egrave", 232 },
{ "eacute", 233 },
{ "ecirc", 234 },
{ "euml", 235 },
/* 80 */
{ "igrave", 236 },
{ "iacute", 237 },
{ "icirc", 238 },
{ "iuml", 239 },
{ "ieth", 240 },
{ "ntilde", 241 },
{ "ograve", 242 },
{ "oacute", 243 },
{ "ocirc", 244 },
{ "otilde", 245 },
/* 90 */
{ "ouml", 246 },
{ "divide", 247 },
{ "oslash", 248 },
{ "ugrave", 249 },
{ "uacute", 250 },
{ "ucirc", 251 },
{ "uuml", 252 },
{ "yacute", 253 },
{ "thorn", 254 },
{ "yuml", 255 },
/* 100 */
{ NULL, 0 },
};

string decode_entities(const string &str)
{
    unsigned int count = 0;
    const char *ptr = str.c_str();
    const char *end;

    string ret(str);
    string entity;

    ptr = strchr(ptr, '&');
    if (ptr == NULL) return ret;

    count += static_cast<unsigned int>(ptr - str.c_str());

    //			printf("url_init: %s\n", str.c_str());
    while (*ptr)
    {
        if (*ptr == '&' && ((end = strchr(ptr, ';')) != NULL))
        {
            entity.assign(ptr + 1, end);
            //					printf("Entity: %d %s\n", entity.length(), entity.c_str());
            if (!entity.empty() && entity[0] == '#')
            {
                entity.erase(0, 1);
                int chr = atoi(entity.c_str());
                if (chr > 0 && chr <= UCHAR_MAX)
                {
                    ret[count++] = chr;
                }
                ptr = end + 1;
            }
            else
            {
                bool found = false;
                for (int i = 0; entities[i].str != NULL; i++)
                {
                    if (entity == entities[i].str)
                    {
                        found = true;
                        ret[count++] = static_cast<char>(entities[i].chr);
                        ptr = end + 1;
                        break;
                    }
                }

                if (!found)
                {
                    ret[count++] = *ptr++;
                }
            }
        }
        else
        {
            ret[count++] = *ptr++;
        }
    }

    ret.erase(count);

    //			printf("url_end: %s\n", ret.c_str());
    return ret;
}

string get_attribute(const string& tag, const string& attr) {
    string val;
    string low_tag(tag);
    string low_attr(attr);

    transform(low_attr.begin(), low_attr.end(), low_attr.begin(), ::tolower);
    transform(low_tag.begin(), low_tag.end(), low_tag.begin(), ::tolower);

    string::size_type a;
    a = low_tag.find(low_attr);
    if (a == string::npos)
        return val;

    a += attr.length();
    while (a < tag.length() && isspace(tag[a])) a++;
    if (a == tag.length() || tag[a] != '=')
        return val;
    a++;
    while (a < tag.length() && isspace(tag[a])) a++;
    if (a == tag.length())
        return val;

    if (tag[a] == '"') {
        string::size_type b = tag.find('"', a+1);
        if (b == string::npos) return val;
        val = tag.substr(a+1, b-a-1);
    } else if (tag[a] == '\'') {
        string::size_type b = tag.find('\'', a+1);
        if (b == string::npos) return val;
        val = tag.substr(a+1, b-a-1);
    } else {
        while (a < tag.length() && !isspace(tag[a]) && tag[a] != '>') {
            val += tag[a++];
        }
    }

    return val;
}

string normalize_slashs(const string &url)
{
    const int NONE = 0;
    const int LASTSLASH = 1;
    const int LASTDOTSLASH = 2;
    const int LASTDOTDOTSLASH = 3;
    int state = NONE;
    const char *question_dash;
    const char *question;
    const char *dash;
    unsigned int count = 0;
    const char *ptr = url.c_str();
    string ret(url);

    question = strchr(ptr, '?');
    dash = strchr(ptr, '#');
    if (question &&(!dash || question < dash)) question_dash = question;
    else question_dash = dash;
    if (question_dash == 0) question_dash = url.c_str() + url.length();

    const char *problem;
    const char *problem1 = strstr(ptr, "//");
    const char *problem2 = strstr(ptr, "/.");

    if (problem1 && (!problem2 || problem1 < problem2)) problem = problem1;
    else problem = problem2;

    if (problem && problem < question_dash)
    {
        ptr = problem;
        count = static_cast<unsigned int>(ptr - url.c_str());
        while (*ptr && ptr < question_dash)
        {
            switch (state)
            {
            case LASTSLASH:
                if (*ptr == '/')
                {
                    ++ptr;
                    state = LASTSLASH;
                }
                else if (*ptr == '.')
                {
                    ++ptr;
                    state = LASTDOTSLASH;
                }
                else
                {
                    ret[count++] = *ptr;
                    ++ptr;
                    state = NONE;
                }
                break;
            case LASTDOTSLASH:
                if (*ptr == '/')
                {
                    ++ptr;
                    state = LASTSLASH;
                }
                else if (*ptr == '.')
                {
                    ++ptr;
                    state = LASTDOTDOTSLASH;
                }
                else
                {
                    ret[count++] = '.';
                    ret[count++] = *ptr;
                    ++ptr;
                    state = NONE;
                }
                break;
            case LASTDOTDOTSLASH:
                if (*ptr == '/')
                {
                    const char *last_slash = ret.c_str() + count - 2;
                    while (last_slash >= ret.c_str() && *last_slash != '/')
                        --last_slash;
                    if (last_slash >= ret.c_str())
                        count = static_cast<unsigned int>(last_slash - ret.c_str() + 1);
                    ++ptr;
                    state = LASTSLASH;
                }
                else
                {
                    ret[count++] = '.';
                    ret[count++] = '.';
                    ret[count++] = *ptr;
                    ++ptr;
                    state = NONE;
                }
                break;
            default:
                if (*ptr == '/')
                {
                    ret[count++] = *ptr;
                    ++ptr;
                    state = LASTSLASH;
                }
                else
                {
                    ret[count++] = *ptr;
                    ++ptr;
                    state = NONE;
                }
            }
        }

        if (question_dash)
        {
            while (*ptr)
            {
                ret[count++] = *ptr;
                ++ptr;
            }
        }

        ret.erase(count);
    }

    return ret;
}

string convert_link(const string& relative, const Uri& root)
{
    string url(relative);

    url = crawl::decode_entities(url);

    string::size_type a;
    a = 0;
    while ((a = url.find_first_of(" \r\n", a)) != string::npos)
    {
        switch (url[a])
        {
        case ' ':
            url.replace(a, 1, "%20");
            break;
        case '\r':
            url.erase(a, 1);
            break;
        case '\n':
            url.erase(a, 1);
            break;
        }
    }

    Uri uri;
    try
    {
        Uri rel(url);
        uri = rel.absolute(root);
        uri.path(normalize_slashs(uri.path()));
    }
    catch (Uri::Exception)
    {
        return string();
    }

    return uri.unparse(Uri::REMOVE_FRAGMENT);
}

string __serialize_gml(const tree<crawl::Node> &tr, tree<crawl::Node>::iterator it, tree<crawl::Node>::iterator end, unsigned int parent_id, unsigned int& label) {

    using namespace std;
    ostringstream ret;
    tree<crawl::Node>::sibling_iterator sib = tr.begin(it);
    while(sib != tr.end(it)) {
        ++label;
        ret << "node [ id " << label << "\n label \"" << label << "\"\n]\n";
        ret << "edge [ \n source " << parent_id << "\n target " << label << "\n]" << endl;
        ret << __serialize_gml(tr, sib, end, label, label);
        ++sib;
    }
    ret << ends;
    string str = ret.str();
    return str;
}


string serialize_gml(const tree<crawl::Node> &tr) {

    using namespace std;

    tree<crawl::Node>::pre_order_iterator it = tr.begin();
    tree<crawl::Node>::pre_order_iterator end = tr.end();

    string ret;
    ret += "graph [";
    ret += "directed 1\n";
    ret += "node [ id 0\n label \"0\"\n ]\n";
    unsigned int label = 0;
    ret += __serialize_gml(tr, it, end, 0, label);
    ret += "]";
    return ret;
}

const std::map<string, string>& stdAsciiHtmlEntitiesMap()
{
    // see:
    // https://www.ascii.cl/htmlcodes.htm
    // https://www.freeformatter.com/html-entities.html
    // https://www.w3.org/wiki/Common_HTML_entities_used_for_typography
    // https://www.freeformatter.com/html-entities.html
    // Unik &#8220;Klik on/off&#8221;
    // https://en.wikipedia.org/wiki/%C3%98
    static const std::map<std::string,std::string> m = {
        {"&#32;", " "}, {"&#x20;", " "},
        {"&#33;", "!"}, {"&#x21;", "!"},
        {"&#34;","\""}, {"&#x22;","\""}, {"&quot;", "\""},
        {"&#35;", "#"}, {"&#x23;", "#"},
        {"&#36;", "$"}, {"&#x24;", "$"},
        {"&#37;", "%"}, {"&#x25;", "%"},
        {"&#38;", "&"}, {"&#x26;", "&"}, {"&amp;", "&"},
        {"&#39;", "'"}, {"&#x27;", "'"}, {"&#039;", "'"},
        {"&#40;", "("}, {"&#x28;", "("},
        {"&#41;", ")"}, {"&#x29;", ")"},

        {"&#42;", "*"}, {"&#x2A;", "*"},
        {"&#43;", "+"}, {"&#x2B;", "+"},
        {"&#44;", ","}, {"&#x2C;", ","},
        {"&#45;", "-"}, {"&#x2D;", "-"},
        {"&#46;", "."}, {"&#x2E;", "."},
        {"&#47;", "/"}, {"&#x2F;", "/"}, {"&sol;", "/"},

        {"&#58;", ":"}, {"&#x3A;", ":"},
        {"&#59;", ";"}, {"&#x3B;", ";"},
        {"&#60;", "<"}, {"&#x3C;", "<"}, {"&lt;", "<"},
        {"&#61;", "="}, {"&#x3D;", "="},
        {"&#62;", ">"}, {"&#x3E;", ">"}, {"&gt;", ">"},
        {"&#63;", "?"}, {"&#x3F;", "?"},
        {"&#64;", "@"}, {"&#x40;", "@"},

        {"&#96;", "`"}, {"&#x60;", "`"},

        {"&#123;","{"}, {"&#x7B;","{"},
        {"&#124;","|"}, {"&#x7C;","|"},
        {"&#125;","}"}, {"&#x7D;","}"},
        {"&#126;","~"}, {"&#x7E;","~"},

        {"&#160;"," "}, {"&#xA0;"," "}, {"&nbsp;", " "},
        {"&#162;","¢"}, {"&#xA2;","¢"}, {"&cent;", "¢"},
        {"&#163;","£"}, {"&#xA3;","£"}, {"&pound;", "£"},
        {"&#164;","¤"}, {"&#xA4;","¤"}, {"&curren;", "¤"},
        {"&#165;","¥"}, {"&#xA5;","¥"}, {"&yen;", "¥"},
        {"&#166;","¦"}, {"&#xA6;","¦"}, {"&brvbar;", "¦"},
        {"&#167;","§"}, {"&#xA7;","§"}, {"&sect;", "§"},
        {"&#168;","¨"}, {"&#xA8;","¨"}, {"&uml;", "¨"},
        {"&#169;","©"}, {"&#xA9;","©"}, {"&copy;", "©"},
        {"&#174;","®"}, {"&#xAE;","®"}, {"&reg;", "®"},
        {"&#180", "´"}, {"&#xB7;","´"}, {"&acute;","´"}, {"\u00B4","´"},

        {"&#196;","Ä"}, {"&#xC4;","Ä"}, {"&Auml;", "Ä"},
        {"&#197;","Å"}, {"&#xC5;","Å"}, {"&Aring;", "Å"},
        {"&#198;","Æ"}, {"&#xC6;","Æ"}, {"&AElig;", "Æ"},
        {"&#199;","Ç"}, {"&#xC7;","Ç"}, {"&Ccedil;","Ç"},
        {"&#200;","È"}, {"&#xC8;","È"}, {"&Egrave;","È"},
        {"&#201;","É"}, {"&#xC9;","É"}, {"&Eacute;","É"},
        {"&#202;","Ê"}, {"&#xCA;","Ê"}, {"&Ecirc;","Ê"},
        {"&#203;","Ë"}, {"&#xCB;","Ë"}, {"&Euml;","Ë"},
        {"&#204;","Ì"}, {"&#xCC;","Ì"}, {"&Igrave;","Ì"},

        {"&#212;","Ô"}, {"&#xD4;","Ô"}, {"&Ocirc;","Ô"},
        {"&#213;","Õ"}, {"&#xD5;","Õ"}, {"&Otilde;","Õ"},
        {"&#214;","Ö"}, {"&#xD6;","Ö"}, {"&Ouml;","Ö"},
        {"&#215;","×"}, {"&#xD7;","×"}, {"&times;","×"},
        {"&#247;","÷"}, {"&#xF7;","÷"}, {"&divide;","÷"},
        {"&#216;","Ø"}, {"&#xD8;","Ø"}, {"&Oslash;", "Ø"},
        {"&#217;","Ù"}, {"&#xD9;","Ù"}, {"&Ugrave;","Ù"},
        {"&#218;","Ú"}, {"&#xDA;","Ú"}, {"&Uacute;","Ú"},
        {"&#219;","Û"}, {"&#xDB;","Û"}, {"&Ucirc;","Û"},
        {"&#220;","Ü"}, {"&#xDC;","Ü"}, {"&Uuml;","Ü"},

        {"&#228;","ä"}, {"&#xE4;","ä"}, {"&auml;","ä"},
        {"&#229;","å"}, {"&#xE5;","å"}, {"&aring;", "å"},
        {"&#230;","æ"}, {"&#xE6;","æ"}, {"&aelig;", "æ"},
        {"&#231;","ç"}, {"&#xE7;","ç"}, {"&ccedil;","ç"},
        {"&#232;","è"}, {"&#xE8;","è"}, {"&egrave;","è"},
        {"&#233;","é"}, {"&#xE9;","é"}, {"&eacute;","é"},
        {"&#234;","ê"}, {"&#xEA;","ê"}, {"&ecirc;","ê"},
        {"&#235;","ë"}, {"&#xEB;","ë"}, {"&euml;","ë"},
        {"&#236;","ì"}, {"&#xEC;","ì"}, {"&igrave;","ì"},

        {"&#244;","ô"}, {"&#xF4;","ô"}, {"&ocirc;","ô"},
        {"&#245;","õ"}, {"&#xF5;","õ"}, {"&otilde;","õ"},
        {"&#246;","ö"}, {"&#xF6;","ö"}, {"&ouml;","ö"},
        {"&#248;","ø"}, {"&#xF8;","ø"}, {"&oslash;", "ø"},
        {"&#249;","ù"}, {"&#xF9;","ù"}, {"&ugrave;","ù"},
        {"&#250;","ú"}, {"&#xFA;","ú"}, {"&uacute;","ú"},
        {"&#251;","û"}, {"&#xFB;","û"}, {"&ucirc;","û"},
        {"&#252;","ü"}, {"&#xFC;","ü"}, {"&uuml;","ü"},
        {"&#253;","ý"}, {"&#xFD;","ý"}, {"&yacute;","ý"},
        {"&#254;","þ"}, {"&#xFE;","þ"}, {"&thorn;","þ"},
        {"&#255;","ÿ"}, {"&#xFF;","ÿ"}, {"&yuml;","ÿ"},

        {"&#8203;",""}, {"&#x200b;", ""},
        {"&#8211;","–"}, {"&#x2013;","–"}, {"&ndash;","–"},
        {"&#8217;","’"}, {"&#x2019;","’"}, {"&rsquo;","’"},
        {"&#8220;","“"},
        {"&#8221;","”"},
        {"&#8249;","‹"},
        {"&#8250;","›"},
        {"&#9654;","▶"}, {"&#x25b6;","▶"},
        {"&#65533;", ""}, {"&#xFFFD", ""}, {"&xfffd;", ""}
    };

    return m;
}

}//namespace crawl
