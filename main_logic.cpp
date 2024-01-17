#include "main_logic.hpp"
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
void hideFile(const std::string& filename,bool unhide)
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
void calculateHash(const std::string& filename, bool sha){
    
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
        {".ppt", "MS PowerPoint files"},
        {".jpg", "Photos"},
        {".jpeg", "Photos"},
        {".png", "Photos"}
    };
    for(const auto& entry: fs::directory_iterator(modifiedDirectory)){
        if(entry.is_regular_file()){
            //pass the file to the move file function
             moveFile(entry.path(), folders);
        }
    }
    std::cout << "[+] Operation successful";
}
void compressFile(const std::string& inFile, const std::string& outFile, bool decompress){
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
