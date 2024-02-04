#include "FileManager.h"

#include <fstream>
#include <iostream>

bool FileManager::Save(const std::string& text, const std::string& address)
{
    // String to be saved to a file
    std::string content = text;

    // File path
    std::string filePath = address;

    // Open a file for writing
    std::ofstream outputFile(filePath);

    // Check if the file is opened successfully
    if (outputFile.is_open())
    {
        // Write the content to the file
        outputFile << content;

        // Close the file
        outputFile.close();

        return true;
    }
    else
    {
        return false;
    }
}
