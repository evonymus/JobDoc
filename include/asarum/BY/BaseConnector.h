#pragma once
#include <memory>
#include <Poco/Data/Session.h>

namespace asarum
{
    /// @file include/asarum/BY/BaseConnector.h
    /// @brief parrent class to all connectors. Defines m_session_ptr and getSession()
    /// @author Marek dZiekanski
    /// @version 0.7

    namespace BY
    {
        class BaseConnector
        {
        public:
            /// @brief pointer to Poco::Data::Session object;
            std::shared_ptr<Poco::Data::Session> m_session_ptr;
            /// @brief getter for the Poco::Data::Session
            /// @return Poco::Data::Session object
            std::shared_ptr<Poco::Data::Session> getSession();
            void execSQL(const char* sql);
        };

        inline std::shared_ptr<Poco::Data::Session> asarum::BY::BaseConnector::getSession()
        {
            return m_session_ptr;
        }

    }
}