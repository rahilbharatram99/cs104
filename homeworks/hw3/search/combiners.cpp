#include "searcheng.h"

// Place your function implementations for your derived
using namespace std;
// WebPageSetCombiner classes here
WebPageSet AND::combine(const WebPageSet& setA, const WebPageSet& setB)
{
    set<WebPage*> combined;
    
    //iterates through set A
    set<WebPage*>::iterator itSetA;
    for(itSetA = setA.begin(); itSetA != setA.end(); itSetA++)
    {
        //if webpage is in set B
        set<WebPage*>::iterator find = setB.find(*itSetA);
        //places webpage in combined
        if(find != setB.end())
        {
            combined.insert(*find);
        }
    }
    
    return combined;
}

WebPageSet OR::combine(const WebPageSet& setA, const WebPageSet& setB)
{
    set<WebPage*> combined;
    
    //iterates through set A
    set<WebPage*>::iterator itSetA;
    for(itSetA = setA.begin(); itSetA != setA.end(); itSetA++)
    {
        //inserts webpages into or
        combined.insert(*itSetA);
    
    }
    
    //iterates through set B
    set<WebPage*>::iterator itSetB;
    for(itSetB = setB.begin(); itSetB != setB.end(); itSetB++)
    {
        //if webpage is not already in combined
        set<WebPage*>::iterator find = combined.find(*itSetB);
        if(find == combined.end())
        {
            combined.insert(*itSetB);
        }
    }
    
    return combined;
}
   
WebPageSet DIFF::combine(const WebPageSet& setA, const WebPageSet& setB)
{
    set<WebPage*> combined;

    //iterates through set A
    set<WebPage*>::iterator itSetA;
    for(itSetA = setA.begin(); itSetA != setA.end(); itSetA++)
    {
        //check if webpage is in set B
        set<WebPage*>::iterator find = setB.find(*itSetA);
        //if not found in B, inserts into diff
        if(find == setB.end())
        {
            combined.insert(*itSetA);
        }
    }
    return combined;

}
