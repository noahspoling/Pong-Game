#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class INIWriter
{
    public:
        void set(const std::string& section, const std::string& key, const std::string& value) {
            data[section + "." + key] = value;
        }
    
        void save(const std::string& filename) const {
            std::ofstream file(filename);
            if (!file) {
                throw std::runtime_error("Could not open file");
            }

            std::string currentSection;
            for (const auto& [key, value] : data) {
                std::string section = key.substr(0, key.find('.'));
                std::string actualKey = key.substr(key.find('.') + 1);

                if (section != currentSection) {
                    file << "[" << section << "]\n";
                    currentSection = section;
                }
            }

        }

    private:
        std::unordered_map<std::string, std::string> data;
};