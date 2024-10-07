//
// JobSelCta.h
//
// This file has been generated from jobdoc.xml. Do not edit.
//


#ifndef asarum_BY_JobSelCta_INCLUDED
#define asarum_BY_JobSelCta_INCLUDED


#include "Poco/ActiveRecord/ActiveRecord.h"
#include "asarum/BY/JobDef.h"
#include "asarum/BY/EntySelCta.h"


namespace asarum {
namespace BY {

/// <summary>
/// The class is used to store a record of a JOB_SEL_CTA, the table
///  that connects JOB_T with ENTY_SEL_CTA_T 
/// </summary>
class JobSelCta: public Poco::ActiveRecord::ActiveRecord<Poco::Int32>
{
public:
	using Ptr = Poco::AutoPtr<JobSelCta>;

	explicit JobSelCta(ID id);
	JobSelCta() = default;
	JobSelCta(const JobSelCta& other);
	~JobSelCta() = default;

	Poco::Int32 opt_lck() const;
	JobSelCta& opt_lck(Poco::Int32 value);

	JobDef::Ptr job_cd() const;
	const std::string& job_cdID() const;
	JobSelCta& job_cd(JobDef::Ptr pObject);
	JobSelCta& job_cdID(const std::string& id);

	EntySelCta::Ptr enty_sel_cta_cd() const;
	const std::string& enty_sel_cta_cdID() const;
	JobSelCta& enty_sel_cta_cd(EntySelCta::Ptr pObject);
	JobSelCta& enty_sel_cta_cdID(const std::string& id);

	static Ptr find(Poco::ActiveRecord::Context::Ptr pContext, const ID& id);

	void insert();
	void update();
	void remove();

	static const std::vector<std::string>& columns();
	static const std::string& table();

private:
	Poco::Int32 _opt_lck = 0;
	std::string _job_cd;
	std::string _enty_sel_cta_cd;

	friend class Poco::Data::TypeHandler<JobSelCta>;
};


inline Poco::Int32 JobSelCta::opt_lck() const
{
	return _opt_lck;
}


inline JobSelCta& JobSelCta::opt_lck(Poco::Int32 value)
{
	_opt_lck = value;
	return *this;
}


inline const std::string& JobSelCta::job_cdID() const
{
	return _job_cd;
}


inline JobSelCta& JobSelCta::job_cdID(const std::string& value)
{
	_job_cd = value;
	return *this;
}


inline const std::string& JobSelCta::enty_sel_cta_cdID() const
{
	return _enty_sel_cta_cd;
}


inline JobSelCta& JobSelCta::enty_sel_cta_cdID(const std::string& value)
{
	_enty_sel_cta_cd = value;
	return *this;
}


} } // namespace asarum:BY


namespace Poco {
namespace Data {


template <>
class TypeHandler<asarum::BY::JobSelCta>
{
public:
	static std::size_t size()
	{
		return 3;
	}

	static void bind(std::size_t pos, const asarum::BY::JobSelCta& ar, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir)
	{
		TypeHandler<Poco::Int32>::bind(pos++, ar._opt_lck, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._job_cd, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._enty_sel_cta_cd, pBinder, dir);
}

	static void extract(std::size_t pos, asarum::BY::JobSelCta& ar, const asarum::BY::JobSelCta& deflt, AbstractExtractor::Ptr pExtr)
	{
		TypeHandler<Poco::Int32>::extract(pos++, ar._opt_lck, deflt._opt_lck, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._job_cd, deflt._job_cd, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._enty_sel_cta_cd, deflt._enty_sel_cta_cd, pExtr);
}

	static void prepare(std::size_t pos, const asarum::BY::JobSelCta& ar, AbstractPreparator::Ptr pPrep)
	{
		TypeHandler<Poco::Int32>::prepare(pos++, ar._opt_lck, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._job_cd, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._enty_sel_cta_cd, pPrep);
	}
};


} } // namespace Poco::Data


#endif // asarum_BY_JobSelCta_INCLUDED
