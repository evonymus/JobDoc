#ifndef __ESC_VALIDATOR__
#define __ESC_VALIDATOR__
#include <string>
#include <ostream>
#include <vector>
#include "asarum/BY/EntySelCta.h"

namespace asarum {
	namespace BY {

	/**
  * @class EscValidator
  * @brief Validates SQL queries for specific conditions.
  *
  * The EscValidator class is responsible for validating SQL queries
  * to ensure they meet certain criteria, such as the absence of magic numbers,
  * obsolete joins, and the presence of comments.
  */
	class EscValidator {
	public:
		/**
   * @brief Constructor for EscValidator.
   * @param vec_esc_ptr_ A vector of pointers to EntySelCta objects.
   * @param r_out The output stream to write validation results to.
   */
		EscValidator(const std::vector<Poco::AutoPtr<EntySelCta>> vec_esc_ptr_, std::ostream &r_out);

		/**
   * @brief Validates the SQL queries.
   *
   * This method iterates through the provided SQL queries and checks for
   * specific conditions such as magic numbers, obsolete joins, and missing comments.
   */
		void validate();

	private:
		/**
   * @brief Checks if magic numbers are present in the SQL query.
   * @param r_sql The SQL query to check.
   * @return True if magic numbers are present, false otherwise.
   */
		bool magicNumbersPresent(const std::string &r_sql);

		/**
   * @brief Checks if obsolete joins are present in the SQL query.
   * @param r_sql The SQL query to check.
   * @return True if obsolete joins are present, false otherwise.
   */
		bool obsoleteJoinsPresent(const std::string &r_sql);

		/**
   * @brief Checks if comments are missing in the SQL query.
   * @param r_sql The SQL query to check.
   * @return True if comments are missing, false otherwise.
   */
		bool isCommentMissing(const std::string & r_sql);

		std::vector<Poco::AutoPtr<EntySelCta>> vec_esc_ptr_; ///< Vector of pointers to EntySelCta objects.
		std::ostream& r_out_; ///< Output stream to write validation results to.
	};
	}
}
#endif // !__ESC_VALIDATOR__
