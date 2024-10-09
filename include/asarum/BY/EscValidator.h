#ifndef __ESC_VALIDATOR__
#define __ESC_VALIDATOR__
#include <string>
#include <ostream>
#include <vector>
#include "asarum/BY/EntySelCta.h"

namespace asarum {
	namespace BY {

	class EscValidator {
	public:
		EscValidator(const std::vector<Poco::AutoPtr<EntySelCta>> vec_esc_ptr_, std::ostream &r_out);
		void validate();

	private:
		bool magicNumbersPresent(const std::string &r_sql);
		bool obsoleteJoinsPresent(const std::string &r_sql);
		bool isCommentMissing(const std::string & r_sql);

		std::vector<Poco::AutoPtr<EntySelCta>> vec_esc_ptr_;
		std::ostream& r_out_;
	};
	}
}
#endif // !__ESC_VALIDATOR__
