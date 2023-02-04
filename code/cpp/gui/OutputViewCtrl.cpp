#include "OutputViewCtrl.h"

#include <stdio.h>
#include <iostream>
#include <boost/algorithm/string.hpp>

#include <QCoreApplication>
#include "OutputViewUi.h"

using namespace std;

namespace crawl {


OutputViewCtrl::OutputViewCtrl(
    const std::string& sBaseOutputName,
    OutputViewUi* ui )
    : QObject(nullptr)
    , DataWriterIF          ( sBaseOutputName       )
    , m_ui                  ( ui                    )
    , m_iIndentLevel        ( 0                     )
    , m_bDoWriteOutput      ( true                  )
{
    if (m_ui) {
        connect( this, SIGNAL( clearSignal()), m_ui, SLOT (clearSlot()) );
        connect( this, SIGNAL( appendHtmlSignal(const QString&)), m_ui, SLOT (appendHtmlSlot(const QString&)) );
    }
}

int OutputViewCtrl::phpStdOutputWrite( const char* str, unsigned int strLength )
{
    const int strLen = static_cast<int>(strLength);
    QString s("<div style='color:DarkGreen;font-weight:normal;float:left' >");
    s.append( QString::fromUtf8( str, strLen) );
    s.append("</div>");

    emit appendHtmlSignal(s);
    return strLen;
}

void OutputViewCtrl::phpLogMessage( char* str )
{
    QString s("<div style='color:DarkRed;font-weight:normal;float:left' >");
    s.append( QString::fromUtf8( str ) );
    s.append("</div>");

    emit appendHtmlSignal(s);
}

void OutputViewCtrl::phpFlushStdOut( void* /*server_context*/ )
{
}

// ---------------------------------
// --- PRIVATE: Helper functions ---
// ---------------------------------

void OutputViewCtrl::outputLineToWindow(
    const QString& line
)
{
    QString finalLine = getIndention(m_iIndentLevel);
    finalLine += line;
    emit appendHtmlSignal(finalLine);
}


QString OutputViewCtrl::getIndention(
    int iIndentLevel
) const
{
    QString s;
    if ( iIndentLevel < 1	)	return "";
    if ( iIndentLevel > 100 )	return "";	// Sanity check !!
    iIndentLevel--; // We skip the first level of indention here!
    while ( iIndentLevel-- ) {
        s += "&nbsp;&nbsp;&nbsp;&nbsp;";
    }
    return s;
}

// ------------------------------------
// --- PRIVATE: Writer do_functions ---
// ------------------------------------
void OutputViewCtrl::do_close ()
{
    m_iIndentLevel = 0;
}

void OutputViewCtrl::do_restart ()
{
    m_iIndentLevel = 0;
    m_prevContext = "";
    emit clearSignal();
}

void OutputViewCtrl::do_configOutputEncloseCDATA  ( bool /*bDoEncloseInCDATA */)
{
}

void OutputViewCtrl::do_beginMining ()
{
    restart();
}

void OutputViewCtrl::do_endMining ()
{

}

void OutputViewCtrl::do_pushContext (
        const std::string& context,
        const string& prevContext,
        int iIndentLevel,
        size_t /*contextCount*/ )
{
    m_prevContext = prevContext;
    m_iIndentLevel = iIndentLevel;
    const bool curContextIsList = contextIsList(context);
    QString color = "DarkBlue";
    QString listMarker = "";
    if (curContextIsList) {
        listMarker = QString("&nbsp;[");
        color = "Blue";
    }

    QString s = "<span style='color:";
    s += color + ";font-weight:bold;float:left' >";
    s += QString::fromUtf8(context.c_str());
    s += listMarker;
    s += "</span>";
    outputLineToWindow(s);
}

void OutputViewCtrl::do_popContext (const std::string& context,
                                    int iIndentLevel, size_t /*contextCount*/)
{
    m_iIndentLevel = iIndentLevel;
    const bool curContextIsList = contextIsList(context);
    if (curContextIsList) {
        outputLineToWindow("<span style='color:Blue;font-weight:bold;float:left' >]</span>");
    }
}

void OutputViewCtrl::do_outputValueDirect(
        const std::string& sFieldName
        , const std::string& sValue
        , int iIndentLevel , size_t /*valuesCount*/)
{
    m_iIndentLevel = iIndentLevel;
    const bool prevContextIsList = contextIsList(m_prevContext);
    if (prevContextIsList && m_prevContext == sValue)
        return; // To avoid printing the extra 'field_name' : 'parent_listname' - line!
    QString s = QString("<b>") + QString::fromUtf8(sFieldName.c_str()) + "</b>&nbsp;:&nbsp;" + QString::fromUtf8(sValue.c_str());
    outputLineToWindow(s);
}

void OutputViewCtrl::do_outputList(
        const std::string &fieldName,
        const std::vector<std::string> &list,
        int indentLevel, size_t /*valuesCount*/)
{

    m_iIndentLevel = indentLevel;

    string value = boost::algorithm::join(list, ",");
    boost::algorithm::replace_all(value, ";", ","); // We support that a list element can itself contains elements separated by ';' which we split up here and add to the list.

    QString s = QString("<b>") + QString::fromUtf8(fieldName.c_str()) + "</b>&nbsp;:&nbsp;" + QString::fromUtf8(value.c_str());
    outputLineToWindow(s);
}

} // END namespace crawl
