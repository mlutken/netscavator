#include <string>


#include <stdio.h>
#include <php_embedding/php_embedding_utils.h>
#include <interfaces_utils.h>

void testStringCrash()
{
    std::string s1 = " sadsa  ";
    printf("testStringCrash 1('%s')\n", s1.c_str() );
    std::string  s2 = crawl::trimBlanksCopy(s1);
    printf("testStringCrash 2('%s')\n", s2.c_str() );
}

int main(int argc, char* argv[])
{
    testStringCrash();
    printf("robot2\n");
    testPhpNoMiner();

    php_cli_test4( argc, argv );

    testStringCrash();
    return 0;
}


