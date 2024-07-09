#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <stdexcept>

class INIReader
{
public:
    void parse(const std::string& filename) {
        std::ifstream file(filename);
        if(!file) {
            throw std::runtime_error("Could not open file"); 
        }

        std::string line;
        std::string currentSection;

        while (std::getline(file, line)) {
            line = trim(line.substr(0, line.find(';')));
            if (line.empty()) continue;

            if (line.front() == '[' && line.back() == ']') {
                currentSection = line.substr(1, line.size() - 2);
            } else {
                // Find the delimiter and split the line into key and value
                auto delimiterPos = line.find('=');
                if (delimiterPos != std::string::npos) {
                    std::string key = trim(line.substr(0, delimiterPos));
                    std::string value = trim(line.substr(delimiterPos + 1));
                    data[currentSection + "." + key] = value;
                }
            }
        }
    }

    std::string get(const std::string& section, const std::string& key, const std::string& defaultValue = "") const {
        auto iter = data.find(section + "." + key);
        return iter != data.end() ? iter->second : defaultValue;
    }

private:
    std::unordered_map<std::string, std::string> data;

    std::string trim(const std::string& str) const {
        const char* whitespace = " \t\n\r\f\v";
        size_t start = str.find_first_not_of(whitespace);
        size_t end = str.find_last_not_of(whitespace);
        return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }
};