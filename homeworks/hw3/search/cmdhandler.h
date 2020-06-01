#ifndef CMDHANDLER_H
#define CMDHANDLER_H
#include "handler.h"
#include "searcheng.h"

/*********** OTHER CLASSES WILL NEED TO BE COMPLETED IN cmdhandler.cpp *******/
/***********  You will also need to declare the classes for handling   *******/
/***********          the AND, OR, and DIFF command handlers           *******/

/**
 * Handles the INCOMING command
 */
class IncomingHandler : public Handler
{
public:
    IncomingHandler()
    {
        
    };
    IncomingHandler(Handler* next) : Handler(next)
    {
        
    };

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
};

/**
 * Handles the OUTGOING command
 */
class OutgoingHandler : public Handler
{
public:
    OutgoingHandler()
    {
        
    };
    OutgoingHandler(Handler* next) : Handler(next)
    {
        
    };

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
};

/****************************************************************************/
/* Declare the handler classes for AND, OR, and DIFF here                   */
/****************************************************************************/

class ANDHandler : public Handler
{
public:
    ANDHandler()
    {
        and_ = new AND;
    };
    ANDHandler(Handler* next) : Handler(next)
    {
        
    };
    ~ANDHandler(){
        delete and_;
    }

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
    
private:
    WebPageSetCombiner* and_;
};

class ORHandler : public Handler
{
public:
    ORHandler()
    {
        or_ = new OR;
    };
    ORHandler(Handler* next) : Handler(next)
    {
       
    };
    ~ORHandler(){
        delete or_;
    }

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
    
private:
    WebPageSetCombiner* or_;
};

class DIFFHandler : public Handler
{
public:
    DIFFHandler()
    {
        diff_ = new DIFF;
        
    };
    DIFFHandler(Handler* next) : Handler(next)
    {
        
    };
    ~DIFFHandler(){
        delete diff_;
    }

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
    
private:
    WebPageSetCombiner* diff_;
};

/****************************************************************************/

/****************************************************************************/
/**
 * Handles the QUIT command - COMPLETED in cmdhandler.cpp
 */
class QuitHandler : public Handler
{
public:
    QuitHandler();
    QuitHandler(Handler* next);

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
};

/**
 * Handles the PRINT command
 */
class PrintHandler : public Handler
{
public:
    PrintHandler();
    PrintHandler(Handler* next);

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
};


#endif
