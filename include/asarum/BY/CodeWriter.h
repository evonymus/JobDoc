#pragma once
#include <string>
#include <memory>
#include <ostream>
#include <Poco/AutoPtr.h>
#include "JobDefGetter.h"
namespace asarum
{
    namespace BY
    {
        /// <summary>
        /// The class used to write (save) the SQL code of the ESC Queries.
        /// </summary>
        class CodeWriter
        {
        public:
            CodeWriter(const std::shared_ptr<Poco::Data::Session> session_ptr);

            /// <summary>
            /// Saves all the queries that have sql code != nullptr to the
            /// directory. The code is save using the original ESC names
            /// </summary>
            /// <param name="r_dir"></param>
            void saveEscQueries(const std::string& r_dir);

        private:
            /// @brief stores pointer to JobDefGetter object, getting information about
            // jobs from daatabase
            std::shared_ptr<asarum::BY::JobDefGetter> m_job_getter_ptr;
            std::shared_ptr<std::ostream> m_out_ptr;

            void saveSingleQuery(const std::string& r_code,
                const std::string& r_file_name);
        };

    } // namespace BY

} // namespace asarum
