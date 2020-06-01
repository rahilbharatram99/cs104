#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include "gitint.h"

using namespace std;

/*********************** Messages to use for errors ***************************/
const std::string INVALID_COMMAND = "Invalid command";
const std::string INVALID_OPTION = "Invalid option";
const std::string INVALID_COMMIT_NUMBER = "Invalid commit number";
const std::string LOG_COMMIT_STARTER = "Commit: ";

const std::string FILE_EXISTS = "The filename is already in existance";
const std::string INVALID_FILENAME_NUMBER = "Filename or file value not entered";
const std::string FILE_NOT_EXIST = "The filename does not exist";
const std::string INVALID_MESSAGE = "Message is needed to commit";


/********************* To BE WRITTEN ********************/

bool GitInt::process_command(std::string cmd_line)
{
    bool quit = false;
    std::stringstream ss(cmd_line);
    std::string cmd;
    ss >> cmd;
    if (ss.fail()) throw std::runtime_error(INVALID_COMMAND);

    if (cmd == "quit") {
        quit = true;
    }
    // Continue checking/processing commands
    else if(cmd == "create"){
        std::string filename; int val;
        ss >> filename >> val;
        
        //Check no filename or integer are entered
        if(ss.fail()){
            throw std::runtime_error(INVALID_FILENAME_NUMBER);
        }
        //if file already exists
        else if(files.find(filename) != files.end()){
            throw  std::invalid_argument(FILE_EXISTS);
        }
        else{
            create(filename, val);
        }
    }
    else if(cmd == "edit"){
        std::string filename; int val;
        ss >> filename >> val;
        
        //Check if filename and val are valid
        if(ss.fail()) {
            throw std::runtime_error(INVALID_FILENAME_NUMBER);
        }
        //if file does not exists
        else if(files.find(filename) == files.end()) {
            throw std::invalid_argument(FILE_NOT_EXIST);
        }
        else {
            edit(filename, val);
        }
        
    }
    else if(cmd == "display"){
        /*FACTOR IN IF NO FILES EXIST*/
        //****** CHECK DISPLAY COMMIT ****//
        
        std::string filename;
        int args;
        bool varBool = false;
        ss >> filename;
        
        //No specific file name entered
        if (ss.fail()){
            display_all();
        }
        //check if string or int
        else {
            if(isdigit(filename[0])){
                stringstream ss2(filename);
                ss2 >> args;
                varBool = true;
            }
        }
        //If request to display a commit
        if(varBool && !ss.fail()){
            //if commit number does not exist
            if(!valid_commit(args)){
                throw std::invalid_argument(INVALID_COMMIT_NUMBER);
            }
            else{
                display_commit(args);
            }
        }
        //if input is a filename
        else if(!varBool && !ss.fail()){
            //if filename does not exist
            if(files.find(filename) == files.end()){
                throw std::invalid_argument(FILE_NOT_EXIST);
            }
            else{
                display(filename);
            }
        }
    }
    else if(cmd == "add"){
        std::string filename;
        
        //loop to keep adding files
        ss >> filename;
        while(!ss.fail()){
            //error if file does not exist
            if(files.find(filename) == files.end()) {
                throw std::invalid_argument(FILE_NOT_EXIST);
            }
            else {
                add(filename);
            }
            ss >> filename;
        }
    }
    else if (cmd == "commit"){
        /**----------- TRY USING CHARS?  ------------- */
        std::string message;
        std::string temp;
        char quotes;
        ss >> quotes;
        //check if message is provided and in has a starting "
        // and isnt an empty message
        if ( (ss.fail()) || quotes != '"') {
            throw std::runtime_error(INVALID_MESSAGE);
        }
        else{
            while(ss>>temp){
                message += (temp + " ");
            }
            message.pop_back();
            if(message.back() != '"'){
                throw std::runtime_error(INVALID_MESSAGE);
            }
            else{
                message.pop_back();
                commit(message);
            }
        }
    }
    else if(cmd == "tag"){
        std::string tagTemp;
        
        // if no other command is inputted
        if (!(ss >> tagTemp)){
            //display all tags
            tags();
        }
        else {
            // if the command is -a
            if(tagTemp == "-a"){
                // if a tagname follows
                if(ss >> tagTemp){
                    //if tagname does not already exist
                    if(tagNames.find(tagTemp) == tagNames.end()){
                        create_tag(tagTemp, head_);
                    }
                    //if tagname does exist
                    else {
                        throw std::invalid_argument(INVALID_OPTION);
                    }
                }
                // if nothing after -a is provided
                else {
                    throw std::runtime_error(INVALID_COMMAND);
                }
            }
            // if a tagname does not follow
            else{
                throw std::runtime_error(INVALID_COMMAND);
            }
        }
    }
    else if(cmd == "log"){
        log();
    }
    else if(cmd == "checkout"){
        int commit;
        std::string tag;
        bool isDigit = false;
    
        ss >> tag;
        if(ss.fail()){
            throw std::runtime_error(INVALID_COMMAND);
        }
        else {
            //bit messy, not enought time to change :(
            if(isdigit(tag[0])){
                stringstream ss2(tag);
                ss2 >> commit;
                isDigit = true;
            }
            if(isDigit){
                // if commit number
                if(valid_commit(commit)){
                    checkout(commit);
                }
                else{
                    throw std::invalid_argument(INVALID_COMMIT_NUMBER);
                }
            }
            else{
                if(tagNames.find(tag) != tagNames.end()){
                    checkout(tag);
                }
                else {
                    throw std::invalid_argument(INVALID_COMMIT_NUMBER);
                }
            }
        }
    }
    else if(cmd == "diff"){
        int commit1, commit2;
        ss >> commit1;
        
        //if no other args, takes diff from files to head_
        if(ss.fail()){
            diff(head_);
        }
        //if only one args, takes diff from files to commit1
        else if (!(ss >> commit2)){
            //check if commit1 is valid
            if(valid_commit(commit1)){
                diff(commit1);
            }
            else{
                throw std::invalid_argument(INVALID_OPTION);
            }
        }
        //if two commit numbers are inputted
        else{
            //commit no check
            if(commit1 >= commit2 && valid_commit(commit1) && valid_commit(commit2)){
                diff(commit1, commit2);
            }
            else{
                throw std::invalid_argument(INVALID_OPTION);
            }
        }
        
    }
    else {
        throw std::runtime_error(INVALID_COMMAND);
    }
    return quit;
}

GitInt::GitInt(){
    std::map<std::string, int> dummyMap;
    CommitObj dummy("", dummyMap, 0);
    commits.push_back(dummy);
    
    head_ = 0;
    
}

void GitInt::create(const std::string& filename, int value){
    files.insert(make_pair(filename, value));
}

void GitInt::edit(const std::string& filename, int value){
    files[filename] = value;
}

void GitInt::display(const std::string& filename) const{
    std::map<std::string, int>::const_iterator it = files.find(filename);
    cout << it->first << " : " << it->second << endl;
}

void GitInt::display_all() const{
    display_helper(files);
}

void GitInt::add(std::string filename){
    staged.insert(filename);
}

void GitInt::commit(std::string message){ //******** CHECK ******////
    std::map<std::string, int> prevBuild = buildState(head_);
    std::map<std::string, int> diffs;
    
    //input all the file names into diff
    std::map<std::string, int>::iterator it_map;
    for(it_map = prevBuild.begin(); it_map != prevBuild.end(); it_map++){
        diffs[it_map->first] = 0;
    }
    //Loop through staged files
    std::set<std::string>::iterator it_set;
    for(it_set = staged.begin(); it_set != staged.end(); it_set++){
        //Check if staged file is not in prevBuild
        std::map<std::string, int>::iterator it_map = prevBuild.find(*it_set);
        if(it_map == prevBuild.end()){
            diffs[*it_set] = files.find(*it_set)->second;
        } 
        //Check if staged file is in prevBuild
        else{
            diffs[*it_set] = files.find(*it_set)->second - it_map->second;
        }
    }
    staged.clear();
    commits.push_back(CommitObj(message, diffs, head_));
    
    // change the files to current commit?
    head_ = commits.size() - 1;
    
}

void GitInt::create_tag(const std::string& tagname, CommitIdx commit){
    tagNames.insert(make_pair(tagname, commit));
    tagOrder.push_back(tagname);
}

void GitInt::tags() const{
    for(int i = (int) tagOrder.size() -1 ; i >= 0; i--){
        cout << tagOrder[i] << endl;
    }
}

bool GitInt::checkout(CommitIdx commitIndex){
    staged.clear();
    files = buildState(commitIndex);
    head_ = commitIndex;
    return true;
    
}

bool GitInt::checkout(std::string tag){
    std::map<std::string, int>::const_iterator it;
    files = buildState(tagNames.find(tag)->second);
    return true;
    
}

void GitInt::log() const{
    CommitIdx temp = head_;
    
    cout << "Commit: " << head_ << endl;
    cout << commits[head_].msg_ << endl;
    cout << endl;
    
    //Loop through the commits vector
    for(CommitIdx i = head_-1; i > 0; i--){
        //Only executes if commit is the parent
        if(commits[temp].parent_ == i){
            cout << "Commit: " << i << endl;
            cout << commits[i].msg_ << endl;
            cout << endl;
            temp = i;
        }
    }
}

void GitInt::diff(CommitIdx to) const{
    std::map<std::string, int> diffs;
    std::map<std::string, int> prevBuild = buildState(to);
    
    //places all files in prevBuild into diffs with 0 as second
    std::map<std::string, int>::iterator it_build;
    for(it_build = prevBuild.begin(); it_build != prevBuild.end(); it_build++){
        diffs[it_build->first] = 0;
    }
    //Loop through files
    std::map<std::string, int>::const_iterator it_files;
    for(it_files = files.begin(); it_files != files.end(); it_files++){
        //Check if file in files is not in prevBuild
        std::map<std::string, int>::iterator it_check = prevBuild.find(it_files->first);
        if(it_check == prevBuild.end()){
            diffs[it_files->first] = files.find(it_files->first)->second;
        } 
        //Check if file is in prevBuild
        else{
            diffs[it_files->first] = files.find(it_files->first)->second - it_check->second;
        }
    }
    display_helper(diffs);
}

void GitInt::diff(CommitIdx from, CommitIdx to) const{
    std::map<std::string, int> diffs;
    std::map<std::string, int> prevBuild = buildState(to);
    std::map<std::string, int> currBuild = buildState(from);
    
    
    //places all files in prevBuild into diffs with 0 as second
    std::map<std::string, int>::iterator it_build;
    for(it_build = prevBuild.begin(); it_build != prevBuild.end(); it_build++){
        diffs[it_build->first] = 0;
    }
    //Loop through currBuild files
    std::map<std::string, int>::const_iterator it_curr;
    for(it_curr = currBuild.begin(); it_curr != currBuild.end(); it_curr++){
        //Check if file in files is not in prevBuild
        std::map<std::string, int>::iterator it_check = prevBuild.find(it_curr->first);
        if(it_check == prevBuild.end()){
            diffs[it_curr->first] = it_curr->second;
        } 
        //Check if file is in prevBuild
        else{
            diffs[it_curr->first] = it_curr->second - it_check->second;
        }
    }
    display_helper(diffs);    
}

bool GitInt::valid_commit(CommitIdx commit) const{
    return ((size_t)commit < commits.size());
    
}

std::map<std::string, int> GitInt::buildState(CommitIdx from, CommitIdx to) const{
    std::map<std::string, int> currBuild;
    CommitIdx temp = from;
    
    //insert all items from child class into diffs
    std::map<std::string, int>::const_iterator it_child;
    for(it_child = commits[temp].diffs_.begin(); it_child != commits[temp].diffs_.end(); it_child++){
        currBuild[it_child->first] = it_child->second;
    }
    
    //Loop through the commits vector
    for(CommitIdx i = from-1; i >= to; i--){
        //Only executes if commit is the parent
        if(commits[temp].parent_ == i){
            
            std::map<std::string, int>::const_iterator it_diffs;
            for(it_diffs = commits[i].diffs_.begin(); it_diffs != commits[i].diffs_.end(); it_diffs++){
                //If filename is in currBuild
                std::map<std::string, int>::iterator it_curr = currBuild.find(it_diffs->first);
                if(it_curr != currBuild.end()){
                    it_curr->second += it_diffs->second;
                }
                //Insert filename into currBuild
                else{
                    currBuild.insert(make_pair(it_diffs->first, it_diffs->second));
                }
            }
            temp = i;
        }
    }
    return currBuild;
}

// Class implementation

void GitInt::print_menu() const
{
    cout << "Menu:                          " << endl;
    cout << "===============================" << endl;
    cout << "create   filename int-value    " << endl;
    cout << "edit     filename int-value    " << endl;
    cout << "display  (filename)            " << endl;
    cout << "display  commit-num            " << endl;
    cout << "add      file1 (file2 ...)     " << endl;
    cout << "commit   \"log-message\"       " << endl;
    cout << "tag      (-a tag-name)         " << endl;
    cout << "log                            " << endl;
    cout << "checkout commit-num/tag-name   " << endl;
    cout << "diff                           " << endl;
    cout << "diff     commit                " << endl;
    cout << "diff     commit-n commit-m     " << endl;
}


void GitInt::display_commit(CommitIdx commit) const
{
    if ( false == valid_commit(commit) ) {
        throw std::invalid_argument(INVALID_COMMIT_NUMBER);
    }
    display_helper(commits[commit].diffs_);
}


void GitInt::display_helper(const std::map<std::string, int>& dat) const
{
    for (std::map<std::string, int>::const_iterator cit = dat.begin();
            cit != dat.end();
            ++cit) {
        std::cout << cit->first << " : " << cit->second << std::endl;
    }
}


void GitInt::log_helper(CommitIdx commit_num, const std::string& log_message) const
{
    std::cout << LOG_COMMIT_STARTER << commit_num << std::endl;
    std::cout << log_message << std::endl << std::endl;

}

