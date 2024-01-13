#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>
#include <map>
namespace fs = std::filesystem;
//function to convert string path to fs::path
fs::path fix_name(const std::string& name){
    // regex to match the filename to support iterating
    std::regex backslash("\\\\");
    std::regex quotations("\"");
    // Replace backslashes with forward slashes
    std::string modifiedDirectory = std::regex_replace(name, backslash, "/");
    // Remove quotations
    modifiedDirectory = std::regex_replace(modifiedDirectory, quotations, "");
    fs::path path(modifiedDirectory);
    return path;
}
// Function to upload a file using curl
void upload(const std::string& filename)
{
    fs::path m_filename = fix_name(filename);
    // Quote paths to handle spaces
    std::string quotedInFile = "\"" + m_filename.string() + "\"";
    std::string command = "curl -F file=@" + quotedInFile + " 0x0.st";
    system(command.c_str());
    std::cout<<"\n[+] File uploaded successfully\n";
}
// Function to hide files using attrib
void hideFile(const std::string& filename,bool unhide = false)
{
    
    fs::path m_filename = fix_name(filename);
    // Quote paths to handle spaces
    std::string quotedInFile = "\"" + m_filename.string() + "\"";
    std::string command = "attrib +h +r +s " + quotedInFile;
    //Check if the want to unhide
    if (unhide) {
        command = "attrib -h -r -s " + quotedInFile;
    }
    // Write the hidden file names to a text file
    std::ofstream write("hidden_files.txt", std::ios::app);
    write << filename << std::endl;
    write.close();

    system(command.c_str());
    std::cout<<"\n[+] Operation Successful";
}
void encryptFile(const std::string& filename, const std::string& outfile, const std::string& key){
    fs::path in = fix_name(filename);
    fs::path out = fix_name(outfile);
    out = in.parent_path() / out;
    std::ifstream read(in.string(), std::ios::binary);
    std::ofstream write(out.string(), std::ios::binary);
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
    
    fs::path m_filename = fix_name(filename);
    // Quote paths to handle spaces
    std::string quotedInFile = "\"" + m_filename.string() + "\"";
    std::string command = "CertUtil -hashfile " +quotedInFile + " MD5";
    if(sha){
        command = "CertUtil -hashfile " + quotedInFile + " SHA256";
    }
    system(command.c_str());
    
}
void searchFile(const std::string& directory, const std::string& targetFileName) {
    bool found = false;
    fs::path modifiedDirectory = fix_name(directory);
    // Escape special characters in the targetFileName
    std::string escapedPattern = std::regex_replace(targetFileName, std::regex("([.^$|()\\[\\]{}*+?])"), "\\$1");
    std::regex regexPattern(escapedPattern, std::regex_constants::icase); // Case-insensitive
    for (const auto& entry : fs::recursive_directory_iterator(modifiedDirectory)) {
        if (entry.is_regular_file()) {
            //to store matched subexpressions
            std::smatch match;
            std::string filename = entry.path().filename().string();
            if (std::regex_search(filename, match, regexPattern)) {
                std::cout << "File found: " << entry.path() << std::endl;
                found = true;
            }

        }
    }
     if (!found) {
         std::cout << "File not found in: " << modifiedDirectory << std::endl;
    }
}
void moveFile(const fs::path& filePath, const std::map<std::string, std::string>& folders) {
 // Get the file extension
    std::string fileExtension = filePath.extension().string();

    // Find the destination folder based on the file extension
    auto it = folders.find(fileExtension);
    if (it != folders.end()) {
        // Construct the destination path
        fs::path destinationFolderPath = filePath.parent_path() / it->second;
        fs::path destinationPath = destinationFolderPath / filePath.filename();

        // Create the destination folder if it doesn't exist
        if (!fs::exists(destinationFolderPath)) {
            fs::create_directories(destinationFolderPath);
            std::cout << "Created folder: " << destinationFolderPath << std::endl;
        }

        // Rename or move the file
        fs::rename(filePath, destinationPath);

        std::cout << "Moved: " << filePath << " to " << destinationPath << std::endl;
    } else {
        std::cout << "No folder defined for the extension: " << fileExtension << std::endl;
    }
}
void sortFiles(const std::string& directory){
    // regex to match the filename to support iterating
    std::regex backslash("\\\\");
    std::regex quotations("\"");
    // Replace backslashes with forward slashes
    std::string modifiedDirectory = std::regex_replace(directory, backslash, "/");
    // Remove quotations
    modifiedDirectory = std::regex_replace(modifiedDirectory, quotations, "");
    fs::path path(modifiedDirectory);
    //create a map to store the folder names
    std::map<std::string, std::string> folders = {
        {".zip", "Compressed Files"},
        {".rar", "Compressed Files"},
        {".mp4", "Videos"},
        {".exe", "Executable Programs"},
        {".txt", "Text Files"},
        {".cpp", "C++ Source Files"},
        {".pdf", "PDF Files"},
        {".docx", "MS Word files"},
        {".pptx", "MS PowerPoint files"},
        {".xlsx", "MS Excel Files"},
        {".mp3", "Audio Files"},
        {".py", "Python Source Files"},
        {".ppt", "MS PowerPoint files"}
    };
    for(const auto& entry: fs::directory_iterator(modifiedDirectory)){
        if(entry.is_regular_file()){
            //pass the file to the move file function
             moveFile(entry.path(), folders);
        }
    }
    std::cout << "[+] Operation successful";
}
void compressFile(const std::string& inFile, const std::string& outFile, bool decompress=false){
    fs::path m_inFile = fix_name(inFile);
    fs::path m_outFile = fix_name(outFile);
    m_outFile = m_inFile.parent_path() / m_outFile;
    // Quote paths to handle spaces
    std::string quotedInFile = "\"" + m_inFile.string() + "\"";
    std::string quotedOutFile = "\"" + m_outFile.string() + "\"";
    std::string command;
    // Construct the 7-Zip command with proper quoting
    if(!decompress)
        command = "7z a " + quotedOutFile + " " + quotedInFile;
    else{
        command = "7z x " + quotedInFile  + " -o" + quotedOutFile;
    }
    system(command.c_str());
    system("pause");


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
            std::cout<< "Enter the output file name: ";
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
void sortMenu(){
    while(true){
    system("cls");
    unsigned int choice;
    std::string directory;
    std::cout << "Enter the directory path where you want to sort the files: ";
    std::getline(std::cin, directory);
    sortFiles(directory);
    std::cout << "\n\n1. Sort another folder\n";
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
void zipMenu(){
 while (true) {
        std::string filename;
        std::string outFile;
        unsigned int choice;
        system("cls");
        std::cout << "1. File Zipper\n";
        std::cout << "2. Unzip a file\n";
        std::cout << "3. Return to main menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();
        switch (choice) {
        case 1:
 
            system("cls");
            // Prompt the user to enter the file path
            std::cout << "Enter the file or folder path: ";

            // Read the entire line, including spaces, into the 'filename' variable
            std::getline(std::cin, filename);
            std::cout<< "Enter the output archive name: ";
            std::getline(std::cin, outFile);
            compressFile(filename, outFile);
            break;
        case 2:
            // Prompt the user to enter the file path
            std::cout << "Enter the zip file path: ";

            // Read the entire line, including spaces, into the 'filename' variable
            std::getline(std::cin, filename);
            std::cout<< "Enter the output folder name: ";
            std::getline(std::cin, outFile);
            compressFile(filename, outFile, true);
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
            std::cout << "6. Folder Sort\n";
            std::cout << "7. Zipping menu\n";
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
            case 6:
                sortMenu();
                break;
            case 7:
                zipMenu();
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
