#include "menu_logic.hpp"
#include "main_logic.hpp"
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
            hideFile(filename, false);
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
                calculateHash(filename, false);}
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
            compressFile(filename, outFile, false);
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
