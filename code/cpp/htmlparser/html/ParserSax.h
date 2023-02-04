#pragma once

#include <string>

#include "Node.h"

namespace crawl {
    class ParserSax
    {
        public:
            ParserSax() : mpLiteral(0), mCdata(false) {}
            virtual ~ParserSax() {}

            /** Parse the html code */
            void parse(std::string_view html);

            template <typename _Iterator>
            void parse(_Iterator begin, _Iterator end);

        protected:
            // Redefine this if you want to do some initialization before
            // the parsing
            virtual void beginParsing() {}

            virtual void foundTag(Node /*node*/, bool /*isEnd*/) {}
            virtual void foundText(Node /*node*/) {}
            virtual void foundComment(Node /*node*/) {}

            virtual void endParsing() {}


            template <typename _Iterator>
            void parse(_Iterator &begin, _Iterator &end,
                    std::forward_iterator_tag);

            template <typename _Iterator>
            void parseHtmlTag(_Iterator b, _Iterator c);

            template <typename _Iterator>
            void parseContent(_Iterator b, _Iterator c);

            template <typename _Iterator>
            void parseComment(_Iterator b, _Iterator c);

            template <typename _Iterator>
            _Iterator skipHtmlTag(_Iterator ptr, _Iterator end);

            template <typename _Iterator>
            _Iterator skipHtmlComment(_Iterator ptr, _Iterator end);

            unsigned long mCurrentOffset;
            const char *mpLiteral;
            bool mCdata;
    };

}//namespace crawl

#include "ParserSax.tcc"

