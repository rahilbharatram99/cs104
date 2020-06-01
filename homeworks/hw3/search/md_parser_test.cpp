#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include <string>
#include "md_parser.h"
#include "util.h"

using namespace std;

int main (){
    MDParser test;
    string filename = "test-small/page3.md";
    std::set<std::string> allSearchableTerms;
    std::set<std::string> allOutgoingLinks;
    
    test.parse(filename, allSearchableTerms, allOutgoingLinks);
    cout << test.display_text(filename) << endl;
    
    cout << "searchable terms" << endl;
    set<string>::iterator it ;
    for(it = allSearchableTerms.begin(); it != allSearchableTerms.end(); it++){
        cout << *it << " ";
    }
    cout << endl;
    
    cout << "outgoinglinks" << endl;
    set<string>::iterator it2;
    for(it2 = allOutgoingLinks.begin(); it2 != allOutgoingLinks.end(); it2++){
        cout << *it2 << " ";
    }
    cout << endl;
    return 0;
}

