#include "ParserSax.h"
namespace crawl {

void ParserSax::parse(std::string_view html)
{
//	std::cerr << "Parsing string" << std::endl;
//    parse(html.c_str(), html.c_str() + html.length());
    parse(html.begin(), html.end());
}
} // namespace crawl {
