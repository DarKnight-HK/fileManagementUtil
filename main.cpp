#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>
namespace fs = std::filesystem;
// Function to upload a file using curl
void upload(const std::string& filename)
{
    std::string command = "curl -F file=@" + filename + " 0x0.st";
    system(("\"" + command + "\"").c_str());
    std::cout<<"\n[+] File uploaded successfully\n";
}
// Function to hide files using attrib
void hideFile(const std::string& filename,bool unhide = false)
{
    std::string command = "attrib +h +r +s " + filename;
    //Check if the want to unhide
    if (unhide) {
        command = "attrib -h -r -s " + filename;
    }
    // Write the hidden file names to a text file
    std::ofstream write("hidden_files.txt", std::ios::app);
    write << filename << std::endl;
    write.close();

    system(("\"" + command + "\"").c_str());
    std::cout<<"\n[+] Operation Successful";
}
void encryptFile(const std::string& filename, const std::string& outfile, const std::string& key){
    std::ifstream read(filename, std::ios::binary);
    std::ofstream write(outfile, std::ios::binary);
    if(!read.is_open()){
        std::cerr << "Error while opening the file\n";
    }
    std::size_t keyIndex = 0;
    char byte;
    while (read.get(byte)) {
        byte ^= key[keyIndex];  // XOR with the corresponding byte of the key
        write.put(byte);
        keyIndex = (keyIndex + 1) % key.size();  // Move to the next byte of the key
    }
    read.close();
    write.close();


}
void calculateHash(const std::string& filename, bool sha=false){
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return ;
    }

    std::string command = "CertUtil -hashfile " + filename + " MD5";
    if(sha){
        command = "CertUtil -hashfile " + filename + " SHA256";
    }
    system(("\"" + command + "\"").c_str());
    
}
void searchFile(const std::string& directory, const std::string& targetFileName) {
    bool found = false;
    // regex to match the filename to support iterating
    std::regex backslash("\\\\");
    std::regex quotations("\"");
    // Replace backslashes with forward slashes
    std::string modifiedDirectory = std::regex_replace(directory, backslash, "/");
    // Remove quotations
    modifiedDirectory = std::regex_replace(modifiedDirectory, quotations, "");
    fs::path path(modifiedDirectory);
    // Escape special characters in the targetFileName
    std::string escapedPattern = std::regex_replace(targetFileName, std::regex("([.^$|()\\[\\]{}*+?])"), "\\$1");
    std::regex regexPattern(escapedPattern, std::regex_constants::icase); // Case-insensitive
    for (const auto& entry : fs::directory_iterator(modifiedDirectory)) {
        if (entry.is_regular_file()) {
            //to store matched subexpressions
            std::smatch match;
            std::string filename = entry.path().filename().string();
            if (std::regex_search(filename, match, regexPattern)) {
                std::cout << "File found: " << entry.path() << std::endl;
                found = true;
            }

        }
        else if (entry.is_directory()) {
                searchFile(entry.path().string(), targetFileName);
            }
    }
     if (!found) {
         std::cout << "File not found in: " << modifiedDirectory << std::endl;
    }

}

   

void fileUploadMenu() {
    while (true)
    {
        unsigned int choice;
        std::string filename;
        system("cls");
        // Prompt the user to enter the file path
        std::cout << "Enter the file path: ";

        // Read the entire line, including spaces, into the 'filename' variable
        std::getline(std::cin, filename);

        // Print the entered filename
        std::cout << "Entered filename: " << filename << std::endl;

        // Upload the file using the upload function
        upload(filename);
        std::cout << "1. Upload more files\n";
        std::cout << "2. Return to main menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();
        switch (choice) {
        case 1:
            continue;
        case 2:
            break;
        default:
            std::cout << "Invalid Choice";
            continue;
        }
        break;
    }
}
void hideFilesMenu()
{
    while (true) {
        std::string filename;
        unsigned int choice;
        system("cls");
        std::cout << "1. Hide files\n";
        std::cout << "2. Unhide files\n";
        std::cout << "3. Return to main menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();
        switch (choice) {
        case 1:
 
            system("cls");
            // Prompt the user to enter the file path
            std::cout << "Enter the file path: ";

            // Read the entire line, including spaces, into the 'filename' variable
            std::getline(std::cin, filename);
             hideFile(filename);
            break;
        case 2:
            system("cls");
            // Prompt the user to enter the file path
            std::cout << "Enter the file path: ";

            // Read the entire line, including spaces, into the 'filename' variable
            
            std::getline(std::cin, filename);
            hideFile(filename, true);
            break;
        case 3:
            return;
        default:
            std::cout << "Invalid choice";
            continue;
        }
        break;
    }
}
void encrptionMenu(){
     while (true) {
        std::string filename;
        std::string outFile;
        std::string key;
        unsigned int choice;
        system("cls");
        std::cout << "1. Encrypt file\n";
        std::cout << "2. Decrypt file\n";
        std::cout << "3. Return to main menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();
        switch (choice) {
        case 1 ... 2:
 
            system("cls");
            // Prompt the user to enter the file path
            std::cout << "Enter the input file path: ";

            // Read the entire line, including spaces, into the 'filename' variable
            std::getline(std::cin, filename);
            std::cout<< "Enter the password: ";
            std::getline(std::cin, key);
            std::cout<< "Enter the output file path: ";
            std::getline(std::cin,outFile);
            encryptFile(filename, outFile, key);
            break;
        case 3:
            return;
        default:
            std::cout << "Invalid choice";
            continue;
        }
        break;
    }
}
void hashMenu(){
    
    while (true) {
        std::string filename;
        std::string hash;
        unsigned int choice;
        unsigned int hash_choice;
        system("cls");
        // Prompt the user to enter the file path
            std::cout << "Enter the file path: ";

            // Read the entire line, including spaces, into the 'filename' variable
            std::getline(std::cin, filename);
            std::cin.ignore();
            std::cout << "1. MD5\n2. SHA256\nYour choice: \n";

            std::cin >> hash_choice;
            if(hash_choice==1){
                calculateHash(filename);}
            else if(hash_choice==2){
                calculateHash(filename, true);
            }
            else{
                std::cout << "Invalid Choice\n";
                continue;
            }
            std::cout << "\n\n1. Calculate Hash for another file\n";
            std::cout << "2. Return to main menu\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cin.ignore();
            switch (choice) {
                case 1:
                    continue;
                case 2:
                    break;
                default:
                    std::cout << "Invalid Choice";
                    continue;
            }
        break;
    }
}
void searchMenu(){
    while(true){
    system("cls");
    unsigned int choice;
    std::string directory;
    std::string targetFileName;
    std::cout << "Enter the directory path where you want to search for the file: ";
    std::getline(std::cin, directory);
    std::cout << "Enter the file name: ";
    std::getline(std::cin, targetFileName);
    searchFile(directory, targetFileName);
    std::cout << "\n\n1. Seach for another file\n";
    std::cout << "2. Return to main menu\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    std::cin.ignore();
    switch (choice) {
        case 1:
            continue;
        case 2:
            break;
        default:
            std::cout << "Invalid Choice";
            continue;
        }
        break;
          }
}
int main() 
{
        while (true)
        {
            system("cls");
            std::cout << "Welcome to File Management Utility\n";
            std::cout << "**********************************\n";
            std::cout << "1. File Upload\n";
            std::cout << "2. File hide menu\n";
            std::cout << "3. File encryption menu\n";
            std::cout << "4. File hash calculator\n";\
            std::cout << "5. File Searcher\n";
            std::cout << "8. Exit\n";
            std::cout << "Enter your choice: ";

            unsigned int choice;
            std::cin >> choice;
            std::cin.ignore();

            switch (choice)
            {
            case 1:
                fileUploadMenu();
                break;
            case 2:
                hideFilesMenu();
                break;
            case 3:
                encrptionMenu();
                break;
            case 4:
                hashMenu();
                break;
            case 5:
                searchMenu();
                break;
            case 8:
                system("cls");
                std::cout << "Exiting...";
                return 0;
            default:
                std::cout << "Invalid Choice";
                continue;
            }

        }
    }
