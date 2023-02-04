#ifndef _CRAWL_DATA_WRITER_IF_H_
#define _CRAWL_DATA_WRITER_IF_H_

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <QObject>
#include <QString>

namespace crawl {
class StringSearch;

    /** Base browser class. */
    class DataWriterIF  {
    public:
        // ---------------------
        // --- PUBLIC: Types ---
        // ---------------------
        typedef std::vector< boost::shared_ptr<DataWriterIF> >  DataWriterVecT;



        // ---------------------------------------------
        // --- PUBLIC: Constructors / Init functions ---
        // ---------------------------------------------
        DataWriterIF ( const std::string& sBaseOutputName );
        virtual 	~DataWriterIF();

        void                baseOutputNameSet   ( const std::string& sBaseOutputName ){ m_sBaseOutputName = sBaseOutputName;    }
        const std::string&  baseOutputName      () const                              { return m_sBaseOutputName; }
        void                doContinueModeSet   ( bool bDoContinue, int iContinueCounter );
        bool                doContinueMode      () const    { return m_bDoContinueMode;     }
        int                 continueCounter     () const    { return m_iContinueCounter;    }

        // -------------------------------------------
        // --- Writer slots for cross thread usage ---
        // -------------------------------------------

        // ------------------------
        // --- Writer functions ---
        // ------------------------
        void            close                       ()                                { do_close() ;  }
        void            restart                     ( const std::string& sBaseOutputName = "" );
        void            configOutputEncloseCDATA    ( bool bDoEncloseInCDATA )        { do_configOutputEncloseCDATA(bDoEncloseInCDATA); }
        void            beginMining                 ()                                { do_beginMining(); }
        void            endMining                   ();
        void            pushContext                 ( const std::string& sContext, const std::string& prevContext,
                                                      int iIndentLevel, size_t contextCount )
                                                    { do_pushContext(sContext, prevContext, iIndentLevel, contextCount); }
        void            popContext                  ( const std::string& sContext, int iIndentLevel, size_t contextCount )
                                                    { do_popContext(sContext, iIndentLevel, contextCount);  }
        void            outputValueDirect           ( const std::string& sFieldName, const std::string& sValue, int iIndentLevel, size_t valuesCount )
                                                    { do_outputValueDirect(sFieldName, sValue, iIndentLevel, valuesCount ); }
        void            outputList                  ( const std::string& fieldName, const std::vector<std::string> &list, int indentLevel, size_t valuesCount )
                                                    { do_outputList ( fieldName, list, indentLevel, valuesCount ) ; }
        StringSearch*   stringSearch                () const { return m_stringSearch; }
        void            stringSearchSet             ( StringSearch* stringSearch ) { m_stringSearch = stringSearch; }
        bool            contextIsList                  ( const std::string& fieldName) const;

        bool            doWriteOutputToFile() const;
        void            doWriteOutputToFileSet(bool doWriteOutputToFile);

    private:
        // ------------------------------------
        // --- PRIVATE: Writer do_functions ---
        // ------------------------------------
        virtual void    do_close                    () = 0;
        virtual void    do_restart                  () = 0;
        virtual void    do_configOutputEncloseCDATA ( bool bDoEncloseInCDATA ) = 0;
        virtual void    do_beginMining              () = 0;
        virtual void    do_endMining                () = 0;
        virtual void    do_pushContext              ( const std::string& sContext, const std::string& prevContext, int iIndentLevel, size_t contextCount ) = 0;
        virtual void    do_popContext               ( const std::string& sContext, int iIndentLevel, size_t contextCount ) = 0;
        virtual void    do_outputValueDirect        ( const std::string& sFieldName, const std::string& sValue, int iIndentLevel, size_t valuesCount  ) = 0;
        virtual void    do_outputList               ( const std::string& fieldName, const std::vector<std::string> &list, int indentLevel, size_t valuesCount ) = 0;


        // ----------------------------
        // --- PRIVATE: Member data ---
        // ----------------------------
        std::string     m_sBaseOutputName;
        bool            m_bDoContinueMode;  // True if continue scanning has been requested from the command line (-c). Only used in crawler, never in creator
        int             m_iContinueCounter;
        StringSearch*   m_stringSearch;
        bool            m_doWriteOutputToFile = true;

    };

} // END namespace crawl

#endif // _CRAWL_DATA_WRITER_IF_H_



