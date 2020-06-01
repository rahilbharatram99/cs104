#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "searcheng.h"

using namespace std;

std::string extract_extension(const std::string& filename);

//DONE
WebPageSet SearchEng::search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const
{
    //set to empty
    set<WebPage*> searchResult;
    set<WebPage*> emptyset;
    if(terms.begin() == terms.end()) // edge case if terms is empty
    {
        return searchResult;
    }
    
    map<string, set<WebPage*>>::const_iterator itSearch;
    
    //set intial set (diff edge case)
    vector<string>::const_iterator itVec = terms.begin();
    if(itVec != terms.end())
    {
        //only sets if term is in the map
        itSearch = mapSearchTerms_.find(*itVec);
        if(itSearch != mapSearchTerms_.end())
        {
            searchResult = itSearch->second;
        }
    }

    for(itVec++; itVec != terms.end(); itVec++)
    {
        itSearch = mapSearchTerms_.find(*itVec);
        //If term is in mapSearchTerms
        if(itSearch != mapSearchTerms_.end())
        {
            searchResult = combiner->combine(searchResult, itSearch->second);
        }
        else{
            searchResult = combiner->combine(searchResult, emptyset);
        }
    }
    return searchResult;
}

//DONE
WebPage* SearchEng::retrieve_page(const std::string& page_name) const
{
    map<string, WebPage*>::const_iterator itPage = mapWebPages_.find(page_name);
    
    //if page_name is in map, returns WebPage
    if(itPage != mapWebPages_.end())
    {
        return itPage->second;
    }
    else
    {
        return NULL;
    }
}

//DONE
void SearchEng::display_page(std::ostream& ostr, const std::string& page_name) const
{
    string temp;
    string ext = extract_extension(page_name);
    
    PageParser* parser;
    
    //checks pagename is in the map
    if(mapWebPages_.find(page_name) == mapWebPages_.end())
    {
        throw std::invalid_argument("Page name does not exist");
    }
    else
    {
        map<string, PageParser*>::const_iterator itParser = mapParsers_.find(ext);
        //if the parser for the ext does not exist
        if(itParser == mapParsers_.end())
        {
            throw std::logic_error("file extention is invalid");
        }
        else
        {
            //helper function to display file
            parser = itParser->second;
            ostr << parser->display_text(page_name);
        }
    }
}

//DONE
void SearchEng::read_page(const std::string& filename)
{
    set<string> terms;
    set<string> links;
    //find parser for given ext
    string ext_;
    ext_ = extract_extension(filename);
    map<string, PageParser*>::iterator itParser = mapParsers_.find(ext_);
    
    //if parser for the file does not exist
    PageParser* parser = itParser->second;
    try
    {
        //parse
        parser->parse(filename, terms, links);
    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
        return;
    }
    
    //iterators
    set<string>::iterator itTerm;
    set<string>::iterator itLink;
    map<string, set<WebPage*>>::iterator itSearchTerms;
    
    //Pointer to this page
    WebPage* page;
    
    map<string, WebPage*>::iterator itPage = mapWebPages_.find(filename);
    //if WebPage already exists
    if(itPage != mapWebPages_.end())
    {
        //insert into WebPage terms
        page = itPage->second;
        itPage->second->all_terms(terms);
        
        //loop through links
        for(itLink = links.begin(); itLink != links.end(); itLink++)
        {
            map<string, WebPage*>::iterator itPage2 = mapWebPages_.find(*itLink);
            //if the link webpage does not exist
            if(itPage2 == mapWebPages_.end())
            {
                //create blank webpage, and add to outgoinglink and mapWebPages
                WebPage* pageLink = new WebPage(*itLink);
                mapWebPages_[*itLink] = pageLink;
                itPage->second->add_outgoing_link(pageLink);
            }
            else
            {
                itPage->second->add_outgoing_link(itPage2->second);
            }
            //Add incoming link from page to link
            itPage2->second->add_incoming_link(page);
        }
    }
    else
    {
        //Creates new webpage
        page = new WebPage(filename);
        //add page to mapWebPages_
        mapWebPages_.insert(make_pair(filename, page));
        
        //insert into WebPage terms
        page->all_terms(terms);
        
        //loop through links
        for(itLink = links.begin(); itLink != links.end(); itLink++)
        {
            map<string, WebPage*>::iterator itPage2 = mapWebPages_.find(*itLink);
            //if the link webpage does not exist
            if(itPage2 == mapWebPages_.end())
            {
                //create blank webpage, and add to outgoinglink, and mapWebPages
                WebPage* pageLink = new WebPage(*itLink);
                mapWebPages_[*itLink] = pageLink;
                page->add_outgoing_link(pageLink);
                //add incoming link from page to link
                mapWebPages_[*itLink]->add_incoming_link(page);
            }
            else
            {
                page->add_outgoing_link(itPage2->second);
                //add incoming link from page to link
                itPage2->second->add_incoming_link(page);
            }
        }
        //add page to mapWebPages_
        mapWebPages_[filename] = page;
    }
    
    //iterate through terms
    for(itTerm = terms.begin(); itTerm != terms.end(); itTerm++)
    {
        itSearchTerms = mapSearchTerms_.find(*itTerm);
        if(itSearchTerms == mapSearchTerms_.end()) //term not in current search term lib
        {
            mapSearchTerms_[*itTerm].insert(page);
        }
        else
        {
            mapSearchTerms_[*itTerm].insert(page);
        }
    }
}


//COMPELTED
void SearchEng::register_parser(const std::string& extension, PageParser* parser)
{
    mapParsers_[extension] = parser;
}

SearchEng::~SearchEng(){
    map<string, WebPage*>::iterator itWeb;
    
    for(itWeb = mapWebPages_.begin(); itWeb != mapWebPages_.end(); itWeb++)
    {
        delete itWeb->second;
    }
    
    map<string, PageParser*>::iterator itParser;
    for(itParser = mapParsers_.begin(); itParser != mapParsers_.end(); itParser++)
    {
        delete itParser->second;
    }
}

/* --------------------------*//* --------------------------*/
/* --------------------------*//* --------------------------*/
/* --------------------------*//* --------------------------*/
/* --------------------------*//* --------------------------*/


SearchEng::SearchEng(PageParser* noExtensionParser)
{
    if (NULL == noExtensionParser)
    {
        throw std::invalid_argument("default parser cannot be NULL");
    }
    this->noExtensionParser_ = noExtensionParser;

    register_parser("", noExtensionParser_);
}


void SearchEng::read_pages_from_index(const std::string& index_file)
{
    ifstream ifile(index_file.c_str());
    if(ifile.fail()) {
        cerr << "Unable to open index file: " << index_file << endl;
    }

    // Parse all the files
    string filename;
    while(ifile >> filename) {
#ifdef DEBUG
        cout << "Reading " << filename << endl;
#endif
        read_page(filename);
    }
    ifile.close();
}

std::string extract_extension(const std::string& filename)
{
    size_t idx = filename.rfind(".");
    if (idx == std::string::npos) {
        return std::string();
    }
    return filename.substr(idx + 1);
}
