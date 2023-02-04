#include <iostream>
#include <interfaces/utils/StringFinder.h>
using namespace std;
using namespace crawl;


int main()
{
    cerr << "--- string_finder playground ---\n";
    StringFinder sf("Here is a string that we want to cut a piece from");
//    StringFinder sf(s);

    cerr << "sf before: " << sf.currentValue() << "\n";

    auto val1 = sf.findBetween("cut ", "from");
    cerr << "sf val 1: '" << val1 << "'\n";
    cerr << "sf cut 1: '" << sf.currentValue() << "'\n";
    auto val2 = sf.findBetween("Here ", "from");
    cerr << "sf val 2: '" << val2 << "'\n";
    cerr << "sf cut 2: '" << sf.currentValue() << "'\n";

    auto val3 = sf.findBetween("Here ", "not there");
    cerr << "sf val 3: '" << val3 << "'\n";
    cerr << "sf cut 3: '" << sf.currentValue() << "'\n";

    return 0;
}



