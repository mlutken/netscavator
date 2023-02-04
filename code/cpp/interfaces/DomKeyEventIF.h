#ifndef _CRAWL_DOM_KEY_EVENT_IF_H_
#define _CRAWL_DOM_KEY_EVENT_IF_H_


#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>
#include "DomEventIF.h"

namespace crawl {


    class DomKeyEventIF : public DomEventIF
    {
    public:
        enum { DOM_VK_CANCEL = 3U };

        enum { DOM_VK_HELP = 6U };

        enum { DOM_VK_BACK_SPACE = 8U };

        enum { DOM_VK_TAB = 9U };

        enum { DOM_VK_CLEAR = 12U };

        enum { DOM_VK_RETURN = 13U };

        enum { DOM_VK_ENTER = 14U };

        enum { DOM_VK_SHIFT = 16U };

        enum { DOM_VK_CONTROL = 17U };

        enum { DOM_VK_ALT = 18U };

        enum { DOM_VK_PAUSE = 19U };

        enum { DOM_VK_CAPS_LOCK = 20U };

        enum { DOM_VK_KANA = 21U };

        enum { DOM_VK_HANGUL = 21U };

        enum { DOM_VK_JUNJA = 23U };

        enum { DOM_VK_FINAL = 24U };

        enum { DOM_VK_HANJA = 25U };

        enum { DOM_VK_KANJI = 25U };

        enum { DOM_VK_ESCAPE = 27U };

        enum { DOM_VK_CONVERT = 28U };

        enum { DOM_VK_NONCONVERT = 29U };

        enum { DOM_VK_ACCEPT = 30U };

        enum { DOM_VK_MODECHANGE = 31U };

        enum { DOM_VK_SPACE = 32U };

        enum { DOM_VK_PAGE_UP = 33U };

        enum { DOM_VK_PAGE_DOWN = 34U };

        enum { DOM_VK_END = 35U };

        enum { DOM_VK_HOME = 36U };

        enum { DOM_VK_LEFT = 37U };

        enum { DOM_VK_UP = 38U };

        enum { DOM_VK_RIGHT = 39U };

        enum { DOM_VK_DOWN = 40U };

        enum { DOM_VK_SELECT = 41U };

        enum { DOM_VK_PRINT = 42U };

        enum { DOM_VK_EXECUTE = 43U };

        enum { DOM_VK_PRINTSCREEN = 44U };

        enum { DOM_VK_INSERT = 45U };

        enum { DOM_VK_DELETE = 46U };

        enum { DOM_VK_0 = 48U };

        enum { DOM_VK_1 = 49U };

        enum { DOM_VK_2 = 50U };

        enum { DOM_VK_3 = 51U };

        enum { DOM_VK_4 = 52U };

        enum { DOM_VK_5 = 53U };

        enum { DOM_VK_6 = 54U };

        enum { DOM_VK_7 = 55U };

        enum { DOM_VK_8 = 56U };

        enum { DOM_VK_9 = 57U };

        enum { DOM_VK_SEMICOLON = 59U };

        enum { DOM_VK_EQUALS = 61U };

        enum { DOM_VK_A = 65U };

        enum { DOM_VK_B = 66U };

        enum { DOM_VK_C = 67U };

        enum { DOM_VK_D = 68U };

        enum { DOM_VK_E = 69U };

        enum { DOM_VK_F = 70U };

        enum { DOM_VK_G = 71U };

        enum { DOM_VK_H = 72U };

        enum { DOM_VK_I = 73U };

        enum { DOM_VK_J = 74U };

        enum { DOM_VK_K = 75U };

        enum { DOM_VK_L = 76U };

        enum { DOM_VK_M = 77U };

        enum { DOM_VK_N = 78U };

        enum { DOM_VK_O = 79U };

        enum { DOM_VK_P = 80U };

        enum { DOM_VK_Q = 81U };

        enum { DOM_VK_R = 82U };

        enum { DOM_VK_S = 83U };

        enum { DOM_VK_T = 84U };

        enum { DOM_VK_U = 85U };

        enum { DOM_VK_V = 86U };

        enum { DOM_VK_W = 87U };

        enum { DOM_VK_X = 88U };

        enum { DOM_VK_Y = 89U };

        enum { DOM_VK_Z = 90U };

        enum { DOM_VK_CONTEXT_MENU = 93U };

        enum { DOM_VK_SLEEP = 95U };

        enum { DOM_VK_NUMPAD0 = 96U };

        enum { DOM_VK_NUMPAD1 = 97U };

        enum { DOM_VK_NUMPAD2 = 98U };

        enum { DOM_VK_NUMPAD3 = 99U };

        enum { DOM_VK_NUMPAD4 = 100U };

        enum { DOM_VK_NUMPAD5 = 101U };

        enum { DOM_VK_NUMPAD6 = 102U };

        enum { DOM_VK_NUMPAD7 = 103U };

        enum { DOM_VK_NUMPAD8 = 104U };

        enum { DOM_VK_NUMPAD9 = 105U };

        enum { DOM_VK_MULTIPLY = 106U };

        enum { DOM_VK_ADD = 107U };

        enum { DOM_VK_SEPARATOR = 108U };

        enum { DOM_VK_SUBTRACT = 109U };

        enum { DOM_VK_DECIMAL = 110U };

        enum { DOM_VK_DIVIDE = 111U };

        enum { DOM_VK_F1 = 112U };

        enum { DOM_VK_F2 = 113U };

        enum { DOM_VK_F3 = 114U };

        enum { DOM_VK_F4 = 115U };

        enum { DOM_VK_F5 = 116U };

        enum { DOM_VK_F6 = 117U };

        enum { DOM_VK_F7 = 118U };

        enum { DOM_VK_F8 = 119U };

        enum { DOM_VK_F9 = 120U };

        enum { DOM_VK_F10 = 121U };

        enum { DOM_VK_F11 = 122U };

        enum { DOM_VK_F12 = 123U };

        enum { DOM_VK_F13 = 124U };

        enum { DOM_VK_F14 = 125U };

        enum { DOM_VK_F15 = 126U };

        enum { DOM_VK_F16 = 127U };

        enum { DOM_VK_F17 = 128U };

        enum { DOM_VK_F18 = 129U };

        enum { DOM_VK_F19 = 130U };

        enum { DOM_VK_F20 = 131U };

        enum { DOM_VK_F21 = 132U };

        enum { DOM_VK_F22 = 133U };

        enum { DOM_VK_F23 = 134U };

        enum { DOM_VK_F24 = 135U };

        enum { DOM_VK_NUM_LOCK = 144U };

        enum { DOM_VK_SCROLL_LOCK = 145U };

        enum { DOM_VK_COMMA = 188U };

        enum { DOM_VK_PERIOD = 190U };

        enum { DOM_VK_SLASH = 191U };

        enum { DOM_VK_BACK_QUOTE = 192U };

        enum { DOM_VK_OPEN_BRACKET = 219U };

        enum { DOM_VK_BACK_SLASH = 220U };

        enum { DOM_VK_CLOSE_BRACKET = 221U };

        enum { DOM_VK_QUOTE = 222U };

        enum { DOM_VK_META = 224U };


        DomKeyEventIF(    boost::uint32_t chCode, boost::uint32_t kCode );
        DomKeyEventIF(    boost::uint32_t chCode, boost::uint32_t kCode
                        ,   bool alt, bool ctrl, bool shift, bool meta );
        virtual ~DomKeyEventIF() {}

        boost::uint32_t     charCode() const    {	return do_charCode();   }
        boost::uint32_t     keyCode () const    {	return do_keyCode();    }

        bool                altKey  () const    {	return do_altKey();     }
        bool                ctrlKey () const    {	return do_ctrlKey();    }
        bool                shiftKey() const    {	return do_shiftKey();   }
        bool                metaKey () const    {	return do_metaKey();    }

    private:
        // --- PRIVATE: Virtual Implementation functions ---
        virtual boost::uint32_t     do_charCode () const    {	return m_charCode;  }
        virtual boost::uint32_t     do_keyCode  () const    {	return m_keyCode;   }

        virtual bool                do_altKey   () const    {	return m_altKey;    }
        virtual bool                do_ctrlKey  () const    {	return m_ctrlKey;   }
        virtual bool                do_shiftKey () const    {	return m_shiftKey;  }
        virtual bool                do_metaKey  () const    {	return m_metaKey;   }

        // --- PRIVATE: Data ---
        boost::uint32_t         m_charCode;
        boost::uint32_t         m_keyCode;

        bool                    m_altKey;
        bool                    m_ctrlKey;
        bool                    m_shiftKey;
        bool                    m_metaKey;

    };

} // END namespace crawl


#endif //_CRAWL_DOM_KEY_EVENT_IF_H_

