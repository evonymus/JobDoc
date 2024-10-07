#ifndef __METER__
#define __METER__
#include <string>
#include <memory>
#include <Poco/Data/Session.h>
#include <Poco/AutoPtr.h>
#include "EntySelCta.h"
namespace asarum {
	namespace BY {
		class Meter {
		public:
			Meter(std::shared_ptr<Poco::Data::Session> session_ptr);
			void generateJdbcTestFile(std::ostream &out_stream);
		private:
        /// @brief session to the datbase
			std::shared_ptr<Poco::Data::Session> m_session_ptr;
			std::string getHead();
			std::string getTail();
			/// <summary>
			/// Returns string with definitions of queries for JMeter JDBC test
			/// </summary>
			/// <returns></returns>
			std::string getJDBCSampler(const Poco::AutoPtr<EntySelCta> esc_ptr);
		};
	}
}
#endif
