#include <iostream>
#include <string>
#include <domstate/DomNavigator.h>

void test_DomStateMachine(int argc, char** argv)
{
    using namespace crawl;
    using namespace std;

    printf("test_DomStateMachine();\n");
    DomNavigator nav;
    nav.dropDownSelectCreate("select_genre");
    nav.optionAdd(1, "genre1" );
    nav.optionAdd(1, "genre2" );
    nav.optionAdd(1, "genre3" );

    nav.dropDownSelectCreate("select_media");
    nav.optionAdd(1, "media1" );
    nav.optionAdd(1, "media2" );
    nav.optionAdd(1, "media3" );
    nav.autoInputCreate("search_name", "a,b,c", 2, 4 );
    nav.beginStateSet(" genre1, media2 , b c");
    nav.endStateSet(" genre2, media2,b a");
 //   nav.endStateSet("b c");
    nav.start();
    int i = 0;
    while ( ! nav.navigationDone() ) {
//        cout << "L: " << i << " " << nav.stateString() <<  "  select_genre.attrName1: '" << nav.attributeGet("select_genre", "attrName1") << "'" << endl;
        cout << "L: " << i << " " << nav.stateString() << endl;
        // nav.autoInputIncreaseLength( i == 3 );
//        nav.autoInputIncreaseLength( i == 3 || i == 4 || ( 13 <= i && i <= 38) );
//        if ( i == 60 ) {
//            printf("hmm\n");
//        }

        nav.nextState();

        if ( i++ > 1000 ) {
            printf("Error\n");
            break;
        }
    }
//    cout << "L: E " << nav.stateString() <<  "  select_genre.attrName1: '" << nav.attributeGet("select_genre", "attrName1") << "'" << endl;
    cout << "L: E " << nav.stateString() << endl;


}


void test_DomStateMachine1(int argc, char** argv)
{
    using namespace crawl;
    using namespace std;

    printf("test_DomStateMachine();\n");
    DomNavigator nav;
//    nav.dropDownSelectCreate("select_genre");
//    nav.optionAdd(1, "genre1" );
//    nav.optionAdd(1, "genre2" );

//    nav.dropDownSelectCreate("select_media");
//    nav.optionAdd(1, "media1" );
//    nav.optionAdd(1, "media2" );
//    nav.optionAdd(1, "media3" );
    nav.autoInputCreate("search_name", "aa,bb,cc,dd,ee", 1, 1 );
    nav.beginStateSet   ("bb" );
    nav.endStateSet     ("ee" );
//    nav.autoInputCreate("search_name", "a,b,c,d,e", 1, 1 );
//    nav.beginStateSet   ("b" );
//    nav.endStateSet     ("e" );

    nav.start();
    int i = 0;
    while ( ! nav.navigationDone() ) {
        cout << "L: " << i << " " << nav.stateString() << endl;
        nav.nextState();
        if ( i++ > 1000 ) {
            printf("Error\n");
            break;
        }
    }
    cout << "L: E " << nav.stateString() << endl;


}
