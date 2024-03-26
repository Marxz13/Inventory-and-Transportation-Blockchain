#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

// Necessary for using std::vector and std::string
#include <vector>
#include <string>

// If Block is defined in another file, include its header to ensure Block type is known
#include "Block.h"

// Forward declare the Block class if its full definition is not required here
// class Block;

// Declares a function that lists .txt files in a directory (implementation specifics needed)
std::vector<std::string> listTxtFiles();

// Takes a Block object and a filename, and writes the Block's data to a file
void writeBlockToFile(const Block& block, const std::string& filename);

// Displays the content of a Block from a given file (implementation specifics needed)
void displayBlockFromFile(const std::string& selectedFile);

// Searches for a Block by a hash pattern within files (implementation specifics needed)
void searchForBlockByHashPattern(const std::string& hashPattern);

#endif // FILE_OPERATIONS_H
