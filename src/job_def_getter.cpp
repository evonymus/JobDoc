#include "asarum/BY/job_def_getter.h"
#include <Poco/ActiveRecord/Query.h>

namespace by=asarum::BY;
namespace pd=Poco::Data;
namespace pa=Poco::ActiveRecord;
using namespace std;

by::JobDefGetter ::JobDefGetter(std::shared_ptr<Poco::Data::Session> session_ptr) {
        m_session_ptr = session_ptr;
}

/// @brief  Gets vector with the Jobs defintion
/// @return vector of Poco::AutoPtr pointers to JobDef objects 
vector<Poco::AutoPtr<by::JobDef>> by::JobDefGetter::getJobDefs() {
    pa::Context::Ptr pContext = new pa::Context(*m_session_ptr);  
    pa::Query<by::JobDef> query{pContext};
    vector<Poco::AutoPtr<by::JobDef>> result = query.execute();
    return result;
}

vector<Poco::AutoPtr<by::JobSelCta>> by::JobDefGetter::getJobSelCtas() {
    pa::Context::Ptr pContext = new pa::Context(*m_session_ptr);  
    pa::Query<by::JobSelCta> query{pContext};
    return query.execute();
}

vector<Poco::AutoPtr<by::EntySelCta>> by::JobDefGetter::getEntySelCtas() {
    pa::Context::Ptr pContext = new pa::Context(*m_session_ptr);  
    pa::Query<by::EntySelCta> query{pContext};
    return query.execute();
}
    
    by::JobDefGetter::~JobDefGetter() { }