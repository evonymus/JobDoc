//
// JobSelCta.cpp
//
// This file has been generated from jobdoc.xml. Do not edit.
//


#include "asarum/BY/JobSelCta.h"


using namespace std::string_literals;
using namespace Poco::Data::Keywords;


namespace asarum {
namespace BY {


JobSelCta::JobSelCta(ID id):
	Poco::ActiveRecord::ActiveRecord<Poco::Int32>(id)
{
}


JobSelCta::JobSelCta(const JobSelCta& other):
	Poco::ActiveRecord::ActiveRecord<Poco::Int32>(other),
	_opt_lck(other._opt_lck),
	_job_cd(other._job_cd),
	_enty_sel_cta_cd(other._enty_sel_cta_cd)
{
}


JobDef::Ptr JobSelCta::job_cd() const
{
	return JobDef::find(context(), _job_cd);
}


JobSelCta& JobSelCta::job_cd(JobDef::Ptr pObject)
{
	if (pObject)
		_job_cd = pObject->id();
	else
		_job_cd = JobDef::INVALID_ID;
	return *this;
}


EntySelCta::Ptr JobSelCta::enty_sel_cta_cd() const
{
	return EntySelCta::find(context(), _enty_sel_cta_cd);
}


JobSelCta& JobSelCta::enty_sel_cta_cd(EntySelCta::Ptr pObject)
{
	if (pObject)
		_enty_sel_cta_cd = pObject->id();
	else
		_enty_sel_cta_cd = EntySelCta::INVALID_ID;
	return *this;
}


JobSelCta::Ptr JobSelCta::find(Poco::ActiveRecord::Context::Ptr pContext, const ID& id)
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(pContext->statementPlaceholderProvider());
	JobSelCta::Ptr pObject(new JobSelCta);

	pContext->session()
		<< "SELECT job_sel_cta_id, opt_lck, job_cd, enty_sel_cta_cd"
		<< "  FROM JOB_SEL_CTA_T"
		<< "  WHERE job_sel_cta_id = " << pSPP->next(),
		into(pObject->mutableID()),
		into(*pObject),
		bind(id),
		now;

	return withContext(pObject, pContext);
}


void JobSelCta::insert()
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(context()->statementPlaceholderProvider());

	context()->session()
		<< "INSERT INTO JOB_SEL_CTA_T (job_sel_cta_id, opt_lck, job_cd, enty_sel_cta_cd)"
		<< "  VALUES (" << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ")",
		bind(id()),
		use(*this),
		now;
}


void JobSelCta::update()
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(context()->statementPlaceholderProvider());

	context()->session()
		<< "UPDATE JOB_SEL_CTA_T"
		<< "  SET opt_lck = " << pSPP->next() << ", job_cd = " << pSPP->next() << ", enty_sel_cta_cd = " << pSPP->next()
		<< "  WHERE job_sel_cta_id = " << pSPP->next(),
		use(*this),
		bind(id()),
		now;
}


void JobSelCta::remove()
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(context()->statementPlaceholderProvider());

	context()->session()
		<< "DELETE FROM JOB_SEL_CTA_T"
		<< "  WHERE job_sel_cta_id = " << pSPP->next(),
		bind(id()),
		now;
}


const std::vector<std::string>& JobSelCta::columns()
{
	static const std::vector<std::string> cols =
	{
		"job_sel_cta_id"s,
		"opt_lck"s,
		"job_cd"s,
		"enty_sel_cta_cd"s,
	};

	return cols;
}


const std::string& JobSelCta::table()
{
	static const std::string t = "JOB_SEL_CTA_T";
	return t;
}


} } // namespace asarum:BY
