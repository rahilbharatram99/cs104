#include <iostream>
#include "gitint.h"
// Add any necessary headers
using namespace std;

void print_exception_message(const std::string& what_msg);

int main()
{

    GitInt g;
    string cmd_line;
    bool quit = false;
    const string PROMPT_STARTER = "$ ";
    
    do{
        g.print_menu();
        cout << PROMPT_STARTER;
        getline(cin, cmd_line);
        try {
            quit = g.process_command(cmd_line);
        }
        catch(runtime_error &e){
            print_exception_message(e.what());
        }
        catch(invalid_argument &e){
            print_exception_message(e.what());
        }
        cmd_line.clear();
    }while(!quit);
    
    return 0;

}

void print_exception_message(const std::string& what_msg)
{
  cout << "Error - " << what_msg << endl;
}
