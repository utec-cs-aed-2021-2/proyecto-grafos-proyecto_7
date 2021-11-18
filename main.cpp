#include "Tester/tester.h"
#include "Parser/parser.h"

int main(int argc, char *argv[]) {
#ifndef TEST
    freopen("output.txt", "w", stdout);
#endif
    Tester::runMenu();
    //Tester::executeExamples();
    //Tester::executeParser();
    
    return EXIT_SUCCESS;
}