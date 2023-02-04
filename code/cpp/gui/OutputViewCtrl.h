#ifndef CRAWL_OUTPUT_VIEW_CTRL_H
#define CRAWL_OUTPUT_VIEW_CTRL_H

#include <QObject>
#include <QString>
#include <DataWriterIF.h>

class OutputViewUi;

namespace crawl {

class OutputViewCtrl : public QObject, public DataWriterIF
{
Q_OBJECT

public:
    OutputViewCtrl(const std::string& sBaseOutputName, OutputViewUi* ui = nullptr );
    int     phpStdOutputWrite   ( const char* str, unsigned int strLength );
    void    phpLogMessage       ( char* str );
    void	phpFlushStdOut		( void* server_context );

signals:
    void clearSignal();
    void appendHtmlSignal(const QString& html);
//signals:
//    void    phpStdOutputWriteSignal (const QString& str);
//    void    phpLogMessageSignal     (const QString& str);
//    void    phpFlushStdOutSignal    (void* server_context);

private:
    // ---------------------------------
    // --- PRIVATE: Helper functions ---
    // ---------------------------------
    void            outputLineToWindow  (const QString& line );
    QString getIndention( int iIndentLevel ) const;

    // ------------------------------------
    // --- PRIVATE: Writer do_functions ---
    // ------------------------------------
    virtual void    do_close                    () override;
    virtual void    do_restart                  () override;
    virtual void    do_configOutputEncloseCDATA ( bool bDoEncloseInCDATA ) override;
    virtual void    do_beginMining              () override;
    virtual void    do_endMining                () override;
    virtual void    do_pushContext              ( const std::string& context, const std::string& prevContext,
                                                  int iIndentLevel, size_t contextCount ) override;
    virtual void    do_popContext               ( const std::string& context,
                                                  int iIndentLevel, size_t contextCount ) override;
    virtual void    do_outputValueDirect        ( const std::string& sFieldName, const std::string& sValue, int iIndentLevel
                                                , size_t valuesCount ) override;
    virtual void    do_outputList               ( const std::string& fieldName, const std::vector<std::string> &list
                                                , int indentLevel, size_t valuesCount ) override;

    // ----------------------------
    // --- PRIVATE: Member data ---
    // ----------------------------
    OutputViewUi*   m_ui;
    int             m_iIndentLevel;
    bool            m_bDoWriteOutput;
    std::string     m_prevContext;
};

} // END namespace crawl

#endif // CRAWL_OUTPUT_VIEW_CTRL_H
