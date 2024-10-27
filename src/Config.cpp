#include "asarum/BY/Config.h"
#include <iostream>
#include <fstream>

namespace BY = asarum::BY;

    BY::Config::Config(const std::string& filePath) : m_filePath(filePath) {}

    bool BY::Config::readDSN(std::string& dsn, std::string& uid, std::string& pwd) {
        std::ifstream file(m_filePath);
        if (!file.is_open()) {
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.find("DSN=") == 0) {
                dsn = line.substr(4);
            }
            else if (line.find("UID=") == 0) {
                uid = line.substr(4);
            }
            else if (line.find("PWD=") == 0) {
                pwd = line.substr(4);
            }
        }

        file.close();
        return true;
    }

    bool BY::Config::writeDSN(const std::string& dsn, const std::string& uid, const std::string& pwd) {
        std::ofstream file(m_filePath);
        if (!file.is_open()) {
            return false;
        }

        file << "DSN=" << dsn << std::endl;
        file << "UID=" << uid << std::endl;
        file << "PWD=" << pwd << std::endl;

        file.close();
        return true;
    }
