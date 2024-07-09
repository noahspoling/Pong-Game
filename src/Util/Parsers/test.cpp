#include <iostream>
#include <string>
#include <stdexcept>

#include "INIReader.hpp"

//int main() { // This is the main function leave commented to avoid build error
int loadTestINIConfig(const std::string& iniFilePath) {
    try {
        INIReader reader;
        reader.parse("test.ini");

        std::string server = reader.get("network", "server", "UNKNOWN");
        int port = std::stoi(reader.get("network", "port", "-1"));
        std::string db_user = reader.get("database", "user", "UNKNOWN");
        std::string db_password = reader.get("database", "password", "UNKNOWN");
        std::string db_host = reader.get("database", "host", "UNKNOWN");
        std::string db_name = reader.get("database", "dbname", "UNKNOWN");

        std::cout << "Network server: " << server << "\n";
        std::cout << "Network port: " << port << "\n";
        std::cout << "Database user: " << db_user << "\n";
        std::cout << "Database password: " << db_password << "\n";
        std::cout << "Database host: " << db_host << "\n";
        std::cout << "Database name: " << db_name << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}