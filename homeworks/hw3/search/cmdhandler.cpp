#include "cmdhandler.h"
#include "util.h"
using namespace std;

bool IncomingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "INCOMING";
}

Handler::HANDLER_STATUS_T IncomingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    WebPage* page;
    set<WebPage*> inLinks;
    
    //check if filename is inputted
    string name;
    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    
    //check if webpage does exist
    page = eng->retrieve_page(name);
    if(page == NULL)
    {
        return HANDLER_ERROR;
    }
    
    inLinks = page->incoming_links();
    display_hits(inLinks, ostr);
    
    return HANDLER_OK;
    
}

bool OutgoingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OUTGOING";
}

Handler::HANDLER_STATUS_T OutgoingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    WebPage* page;
    set<WebPage*> outLinks;
    
    //check if filename is inputted
    string name;
    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    
    //check if webpage does exist
    page = eng->retrieve_page(name);
    if(page == NULL)
    {
        return HANDLER_ERROR;
    }
    
    outLinks = page->outgoing_links();
    display_hits(outLinks, ostr);
   return HANDLER_OK;
    
}

bool ANDHandler::canHandle(const std::string& cmd) const
{
    return cmd == "AND";
}

Handler::HANDLER_STATUS_T ANDHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    vector<string> terms;
    
    string temp;
    
    instr >> temp;
    while(!instr.fail())
    {
        temp = conv_to_lower(temp);
        terms.push_back(temp);
        instr >> temp;
    }
    
    display_hits(eng->search(terms, and_), ostr);
    return HANDLER_OK;
}

bool ORHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OR";
}
Handler::HANDLER_STATUS_T ORHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    vector<string> terms;
    
    string temp;
    
    instr >> temp;
    while(!instr.fail())
    {
        temp = conv_to_lower(temp);
        terms.push_back(temp);
        instr >> temp;
    }
    
    display_hits(eng->search(terms, or_), ostr);
    return HANDLER_OK;
}

bool DIFFHandler::canHandle(const std::string& cmd) const
{
    return cmd == "DIFF";
}

Handler::HANDLER_STATUS_T DIFFHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    vector<string> terms;
    
    string temp;
    
    instr >> temp;
    while(!instr.fail())
    {
        temp = conv_to_lower(temp);
        terms.push_back(temp);
        instr >> temp;
    }
    
    display_hits(eng->search(terms, diff_), ostr);
    return HANDLER_OK;
}

/****************************************************************************/

/****************************************************************************/

QuitHandler::QuitHandler()
{

}

QuitHandler::QuitHandler(Handler* next)
    : Handler(next)
{

}

bool QuitHandler::canHandle(const std::string& cmd) const
{
    return cmd == "QUIT";

}

Handler::HANDLER_STATUS_T QuitHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    return HANDLER_QUIT;
}

PrintHandler::PrintHandler()
{

}

PrintHandler::PrintHandler(Handler* next)
    : Handler(next)
{

}

bool PrintHandler::canHandle(const std::string& cmd) const
{
    return cmd == "PRINT";

}

Handler::HANDLER_STATUS_T PrintHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    try {
        eng->display_page(ostr, name);
    }
    catch (std::exception& e) {
        return HANDLER_ERROR;
    }
    return HANDLER_OK;
}
