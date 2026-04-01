#include<iostream>
#include<fstream>
#include<filesystem>

using namespace std;
namespace fs = std :: filesystem;

int main()
{
    
    char rewriteFlag='Y';

    string file;
    std::cout << "Enter a file path: ";
    
    getline(cin, file);
    fs:: path ps=fs::path(file);
    if (fs::exists(ps)) {
        std::cout << "File '" << ps.filename() << "' exists in this directory!" << std::endl;
        std::cout << "Do you want to rewrite (Y/n): ";
        std::cin >> rewriteFlag;

    } 
    if (rewriteFlag=='Y') {
       fs::path parentDir = ps.parent_path();


        if (!parentDir.empty() && !fs::exists(parentDir)) {
            fs::create_directories(parentDir);
        }

        ofstream myfile(ps);


        if(myfile.is_open())
        {
        myfile<< "2nd file";
       
        cout<<"Done";
        myfile.close();
        }
        else
            cout<<"Error in opening file!";
        }
}
