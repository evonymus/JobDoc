#include<string>

namespace asarum {
	namespace BY {

/**
 * @class Config
 * @brief Manages configuration settings for the application.
 *
 * The Config class provides methods to read and write Data Source Name (DSN) 
 * configurations from a specified file. It handles the file path internally 
 * and provides an interface to interact with DSN settings.
 */
class Config {
public:
  /**
   * @brief Constructs a Config object with the specified file path.
   * @param filePath The path to the configuration file.
   */
  Config(const std::string& filePath);

  /**
   * @brief Reads the DSN configuration from the file.
   * @param dsn Reference to a string where the DSN will be stored.
   * @param uid Reference to a string where the user ID will be stored.
   * @param pwd Reference to a string where the password will be stored.
   * @return True if the DSN was read successfully, false otherwise.
   */
  bool readDSN(std::string& dsn, std::string& uid, std::string& pwd);

  /**
   * @brief Writes the DSN configuration to the file.
   * @param dsn The DSN to be written.
   * @param uid The user ID to be written.
   * @param pwd The password to be written.
   * @return True if the DSN was written successfully, false otherwise.
   */
  bool writeDSN(const std::string& dsn, const std::string& uid, const std::string& pwd);

private:
  std::string m_filePath; ///< The path to the configuration file.
};

}}
