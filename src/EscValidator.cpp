#include "asarum/BY/EscValidator.h"
#include <regex>


using namespace std;
namespace by = asarum::BY;
namespace pc = Poco::Data;

const string MAGIC_NUM_MSG = "probably, 'magic numbers' present";
const string OBS_JOINS_MSG = "probably, there are used obsolete, SQL89 joins syntax";
const string COMMENT_MISSING = "there is /** comment missing";
const string CORRECT = "no error found";

by::EscValidator::EscValidator(const vector<Poco::AutoPtr<by::EntySelCta>> vec_esc_ptr, ostream& r_out)
	: vec_esc_ptr_(vec_esc_ptr), r_out_(r_out) { }

/// <summary>
/// Functions iterates all ESC queries, checks if either magic numbers or
/// obsolete joins are present and saves the results to the output string
/// given as the constructor parameter
/// </summary>
void by::EscValidator::validate() {
	for (const Poco::AutoPtr<by::EntySelCta> esc_ptr : vec_esc_ptr_) {

		if (esc_ptr->cta_sql().isNull() == false) {
			bool test = true;
			r_out_ << '\n' << esc_ptr->id() << " :\n";

			if (magicNumbersPresent(esc_ptr->cta_sql())) {
				test = false;
				r_out_ << '\t' << MAGIC_NUM_MSG << '\n';
			}
			if (obsoleteJoinsPresent(esc_ptr->cta_sql())) {
				test = false;
				r_out_ << '\t' << OBS_JOINS_MSG << '\n';
			}

			if (isCommentMissing(esc_ptr->cta_sql())) {
				test = false;
				r_out_ << '\t' << COMMENT_MISSING << '\n';
			}

			if (test) {
				r_out_ << '\t' << CORRECT << '\n';
			}
		}
	}
}

/// <summary>
/// Chcecks if the string contains digits and does not contain comments '--'
/// </summary>
/// <returns>True, if the the numbers are present and comment not</returns>
bool by::EscValidator::magicNumbersPresent(const string& r_sql) {
	const std::regex magic_number{ "^(?=.*\\d)(?!.*--).+$" };
	return regex_match(r_sql, magic_number);
}

/// <summary>
/// returns True if the string contains a list separated by comas after the FROM
/// </summary>
/// <param name="r_sql"></param>
/// <returns></returns>
bool by::EscValidator::obsoleteJoinsPresent(const string& r_sql) {
	//const std::regex pattern{ "(?i)^FROM\\s+([\\w]+(,\\s*[\\w]+)*)?$" };
	const std::regex pattern{ "bFROM\s+[\w]+(?:\s*,\s*[\w]+)+\b", std::regex_constants::icase };
	return regex_match(r_sql, pattern);
}

/// <summary>
/// The functon checks if the string contains /** - the beginning of a comment
/// </summary>
/// <param name="r_sql"></param>
/// <returns></returns>
bool by::EscValidator::isCommentMissing(const string& r_sql) {
	const std::regex pattern("\\/\\*\\*"); // Escaped regex pattern
	return !std::regex_search(r_sql, pattern);
}
