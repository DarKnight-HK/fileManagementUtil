#include "main_logic.hpp"
#include "menu_logic.hpp"
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
