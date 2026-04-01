#include<iostream>
#include<fstream>
#include<filesystem>

using namespace std;
namespace fs = std :: filesystem;

int main()
{
    while (true)
{
    int choice;

    cout << "\n1. Create File";
    cout << "\n2. Read File";
    cout << "\n3. Delete File";
    cout << "\n4. Rename File";
    cout << "\n5. List Directory";
     cout << "\n6. Move file";
    cout << "\n7. Exit";
    cout << "\nEnter choice: ";

    cin >> choice;
    cin.ignore();
    if (choice == 7)
        break;

    switch(choice)
    {
        case 1:
            {    char rewriteFlag='Y';

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
                ;
            break;
            }
        case 2:
            {
                string file;
                cout << "Enter a file path: ";
                getline(cin, file);

                fs::path ps = fs::path(file);

                ifstream filen(ps);

                if(!filen.is_open()){
                    cout << "Error opening the file";
                    break;
                }

                string line;

                while(getline(filen, line)){
                    cout << line << endl;
                }

                filen.close();
            }
            break;
        case 3:
            {
                string file;

                cout << "Enter file path to delete:";
                getline(cin, file);

                fs::path ps(file);

                if(!fs::exists(ps)){
                    cout<<"file does not exist";
                    break;
                }

                char cnfrm;
                cout << "Do you want to delete this file " <<ps.filename()<<"(Y/N)";
                cin >> cnfrm;
                cin.ignore();

                if(cnfrm == 'Y'|| cnfrm =='y')
                {
                    if(fs::remove(ps))
                    {
                        cout<< ps.filename()<<"File deleted successfully.";

                    }
                    else
                    {
                        cout<< "Error deleting the file.";
                    }
                }
                else
                {
                    cout<< "Deletion cancelled.";
                }

            
            }
           
            break;

        case 4:
            {
                string file;

                cout << "Enter full file path: ";
                getline(cin, file);

                fs::path oldPath(file); 

                if(!fs::exists(oldPath))
                {
                    cout<<"File does not exist";
                    break;
                }

                string newName;

                cout<< "Enter a new file name:";
                getline(cin, newName);

                fs::path newPath = oldPath.parent_path() / (newName + oldPath.extension().string());;
                fs::rename(oldPath, newPath);

                cout<<"File renamed successfully to "<< newName;
            }
            break;

        case 5:
            {
                string dir;

                cout<< "Enter directory path: ";
                getline(cin, dir);

                fs::path p(dir);

                if(!fs::exists(p) || !fs::is_directory(p))
                {
                    cout<< "Invalid Directory";
                    break;

                }

                cout << "\nContents of directory:\n";
                
                for(const auto &entry : fs::directory_iterator(p)){
                    cout<< entry.path().filename()<<endl;
                }

                
            }
            
            break;
        case 6:
            {
                string sourcePath;
                string destDir;

                cout << "Enter source file/folder path: ";
                getline(cin, sourcePath);

                fs::path source(sourcePath);

                if(!fs::exists(source))
                {
                    cout << "Source does not exist.";
                    break;
                }

                cout << "Enter destination directory: ";
                getline(cin, destDir);

                fs::path destinationFolder(destDir);

                if(!fs::exists(destinationFolder) || !fs::is_directory(destinationFolder))
                {
                    cout << "Invalid destination directory.";
                    break;
                }

                fs::path newLoc = destinationFolder / source.filename();

                fs::rename(source, newLoc);

                cout << "Moved Successfully";
                
 
            }

        default:
            cout << "Invalid choice!";
    }
}
    
}
