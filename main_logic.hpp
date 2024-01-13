#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>
#include <map>
namespace fs = std::filesystem;
fs::path fix_name(const std::string& name);
void upload(const std::string& filename);
void hideFile(const std::string& filename,bool unhide);
void encryptFile(const std::string& filename, const std::string& outfile, const std::string& key);
void calculateHash(const std::string& filename, bool sha);
void searchFile(const std::string& directory, const std::string& targetFileName);
void moveFile(const fs::path& filePath, const std::map<std::string, std::string>& folders);
void sortFiles(const std::string& directory);
void compressFile(const std::string& inFile, const std::string& outFile, bool decompress=false);
