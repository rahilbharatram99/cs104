#ifndef SEARCHENG_H
#define SEARCHENG_H

#include <map>
#include <vector>
#include <string>
#include "pageparser.h"
#include "webpage.h"




class WebPageSetCombiner
{
public:
    /**
     * Destructor
     */
    virtual ~WebPageSetCombiner() {}

    /**
     * Combines two sets of webpages into a resulting set based on some strategy
     *
     * @param[in] setA
     *   first set of webpages
     * @param[in] setB
     *   second set of webpages
     * @return set of webpages that results from the combination strategy
     */
    virtual
    WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB) = 0;
};

/*** Define Derived WebPageSetCombiners (for AND, OR, DIFF) classes below ***/

class AND : public WebPageSetCombiner
{
private:
    WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB);

};

class OR : public WebPageSetCombiner
{
private:
    WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB);

};

class DIFF : public WebPageSetCombiner
{
private:
    WebPageSet combine(const WebPageSet& setA, const WebPageSet& setB);

};

/**
 * Provides parsing and indexing of search terms as well as search operations.
 * Provides webpage display and retrieval.
 */
class SearchEng {
public:
    /**
    * Default constructor
    *
    * @param[in] parser
    *  A parser for files that have no extension.
    *  SearchEng will now be responsible for this parser and its deallocation.
    *
    */
    SearchEng(PageParser* noExtensionParser);

    /**
     * Destructor
     * [WRITTEN BY RAHIL]
     */
    ~SearchEng();

    /**
     * Register a parser for a particular file extension
     * [WRITTEN BY RAHIL]
     *
     * @param[in] extension
     *   File type/extension that should use this parser
     * @param[in] parser
     *   Pointer to the parser
      *  SearchEng will now be responsible for this parser and its deallocation.
     */
    void register_parser(const std::string& extension, PageParser* parser);
    //Do we create a new parser for each webpage, and store that.
    // OR could we have 2 parsers, and then rotate between file types
    //What do we register it to? Data Structure?

    /**
     * Reads and parses files specified in the given index file
     * [COMPLETED]
     *
     * @param[in] index_file
     *   Name of the index file containing the list of files to read/parse
     *
     * @throws std::logic_error
     *   If the file has an extension but no parser is registered for
     *   that extension
     */

    void read_pages_from_index(const std::string& index_file);
    
    /**
     * Retrieves the WebPage object for a given page/file
     * [COMPLETED BY RAHIL]
     *
     * @param[in] page_name
     *   Name of page/file to retrieve
     *
     * @return Pointer to the corresponding WebPage object.  Should not be used
     *   to alter or deallocate the object.
     *   Return NULL if page_name does not exist.
     */
    WebPage* retrieve_page(const std::string& page_name) const;
    
    /**
     * Displays the contents of the page/file
     * [COMPLETED BY RAHIL]
     *
     * @param[inout] ostr
     *   Output stream to display the contnents
     * @param[in] page_name
     *   Name of page/file to display
     *
     * @throw std::invalid_argument if the page_name does not exist
     * @throws std::logic_error
     *   If the file has an extension but no parser is registered for
     *   that extension
     */
    void display_page(std::ostream& ostr, const std::string& page_name) const;
    // DO WE NEED TO STORE THE WEBPAGES, OR COULD WE JUST OPEN THE FILE
    
    
    /**
     * Uses the given search terms and combiner to find the set of webpages
     *  that match the query
     * [COMEPLTED BY RAHIL]
     *
     * @param[in] terms
     *   words/terms to search for
     * @param[in] combiner
     *   Combiner object that implements the strategy for combining the
     *   pages that contain each term (i.e. AND, OR, DIFF, etc.)
     *
     * @return Set of webpages matching the query
     */
    WebPageSet search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const;

private:
    // Helper function to read/parse a single page
    void read_page(const std::string& filename); // COMPLETED BY RAHIL
    // Add other private helpers and data members as needed
    //  Consider how you will store
    //    - the webpages that match a particular search term
    //    - the parsers for particular extensions as well as
    //       the parser for files without an extension
    //    - Webpage objects and ability to look them up via
    //       their page/filename
    
    //Default parser
    PageParser* noExtensionParser_;
    //Stores the webapges to be looked up by filename
    std::map<std::string, WebPage*> mapWebPages_;
    //stores webpages associated with a specific search term
    std::map<std::string, std::set<WebPage*> > mapSearchTerms_;
    //stores the parsers associated
    std::map<std::string, PageParser*> mapParsers_;
    
    
    


};

#endif
