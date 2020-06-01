#include <iostream>
#include <fstream>
#include "searcheng.h"
#include "md_parser.h"
#include "txt_parser.h"


using namespace std;

int main() {
    SearchEng e1(new TXTParser);
    PageParser* txt = new TXTParser;
    PageParser* md = new MDParser;
    e1.register_parser("txt", txt);
    e1.register_parser("md", md);
    //READ FROM INDEX CHECK
    
    cout << " ---- READ FROM INDEX CHECK ---- " << endl;
    e1.read_pages_from_index("test-small/index.in");
    
    //DISPLAY PAGE
    cout << " ---- DISPLAY PAGE CHECK ---- " << endl;
    cout << "---Page 1:" << endl;
    e1.display_page(cout, "test-small/page1.md");
    cout << endl << "---Page 2:" << endl;
    e1.display_page(cout, "test-small/page2.txt");
    cout << endl << "---Page 3:" << endl;
    e1.display_page(cout, "test-small/page3.md");
    cout << endl << "---Page 4" << endl;
    e1.display_page(cout, "test-small/page4.txt");
    cout << endl << endl;
    
    cout << " ---- RUNNING COMBINERS TEST ---- " << endl;
    WebPageSetCombiner* diff_ = new DIFF;
    WebPageSetCombiner* or_ = new OR;
    WebPageSetCombiner* and_ = new AND;
    WebPageSet::iterator it;
    WebPageSet a;
    
    
    cout << " -- TERMS1 -- " << endl;
    vector<string> terms1 = {"one", "four", "two", "test"};
    //AND page4
    //OR page1 page2 page3 page4
    //DIFF page1
    
    cout << " - AND (page4) - " << endl;
    a = e1.search(terms1, and_);
    for(it = a.begin(); it != a.end(); it++)
    {
        cout << (*it)->filename() << endl;
    }
    cout << endl;
    
    cout << " - OR (page1 page2 page3 page4) - " << endl;
    a = e1.search(terms1, or_);
    for(it = a.begin(); it != a.end(); it++)
    {
        cout << (*it)->filename() << endl;
    }
    cout << endl;
    
    cout << " - DIFF (page1) - " << endl;
    a = e1.search(terms1, diff_);
    for(it = a.begin(); it != a.end(); it++)
    {
        cout << (*it)->filename() << endl;
    }
    cout << endl << endl;
    
    cout << " -- TERMS2 -- " << endl;
    vector<string> terms2 = {};
    //AND
    //OR
    //DIFF
    
    cout << " - AND () - " << endl;
    a = e1.search(terms2, and_);
    for(it = a.begin(); it != a.end(); it++)
    {
        cout << (*it)->filename() << endl;
    }
    cout << endl;
    
    cout << " - OR () - " << endl;
    a = e1.search(terms2, or_);
    for(it = a.begin(); it != a.end(); it++)
    {
        cout << (*it)->filename() << endl;
    }
    cout << endl;
    
    cout << " - DIFF () - " << endl;
    a = e1.search(terms2, diff_);
    for(it = a.begin(); it != a.end(); it++)
    {
        cout << (*it)->filename() << endl;
    }
    cout << endl;
    
    cout << " -- TERMS3-- " << endl;
    vector<string> terms3 = {"one"};
    //AND page1 page3 page4
    //OR page1 page3 page4
    //DIFF page1 page3 page4
    
    cout << " - AND (page1 page3 page4) - " << endl;
    a = e1.search(terms3, and_);
    for(it = a.begin(); it != a.end(); it++)
    {
        cout << (*it)->filename() << endl;
    }
    cout << endl;
    
    cout << " - OR (page1 page3 page4) - " << endl;
    a = e1.search(terms3, or_);
    for(it = a.begin(); it != a.end(); it++)
    {
        cout << (*it)->filename() << endl;
    }
    cout << endl;
    
    cout << " - DIFF (page1 page3 page4) - " << endl;
    a = e1.search(terms3, diff_);
    for(it = a.begin(); it != a.end(); it++)
    {
        cout << (*it)->filename() << endl;
    }
    cout << endl;
    
    cout << " -- TERMS4 -- " << endl;
    vector<string> terms4 = {"one" , "person", "ligma", "tommy", "text", "sandra"};
    //AND
    //OR page1 page2 page3 page4
    //DIFF page4
    
    cout << " - AND () - " << endl;
    a = e1.search(terms4, and_);
    for(it = a.begin(); it != a.end(); it++)
    {
        cout << (*it)->filename() << endl;
    }
    cout << endl;
    
    cout << " - OR (page1 page2 page3 page4) - " << endl;
    a = e1.search(terms4, or_);
    for(it = a.begin(); it != a.end(); it++)
    {
        cout << (*it)->filename() << endl;
    }
    cout << endl;
    
    cout << " - DIFF (page4) - " << endl;
    a = e1.search(terms4, diff_);
    for(it = a.begin(); it != a.end(); it++)
    {
        cout << (*it)->filename() << endl;
    }
    cout << endl;
    
    
    
    
    return 0;
}
