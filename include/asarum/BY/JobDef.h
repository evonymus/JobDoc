//
// JobDef.h
//
// This file has been generated from jobdoc.xml. Do not edit.
//


#ifndef asarum_BY_JobDef_INCLUDED
#define asarum_BY_JobDef_INCLUDED


#include "Poco/ActiveRecord/ActiveRecord.h"
#include "asarum/BY/SchdDetl.h"
#include "asarum/BY/AdtnData.h"


namespace asarum {
namespace BY {

/// <summary>
/// The class is used to store a record of JOB_T table.
/// </summary>
class JobDef: public Poco::ActiveRecord::ActiveRecord<std::string>
{
public:
	using Ptr = Poco::AutoPtr<JobDef>;

	explicit JobDef(ID id);
	JobDef() = default;
	JobDef(const JobDef& other);
	~JobDef() = default;

	Poco::Int32 opt_lck() const;
	JobDef& opt_lck(Poco::Int32 value);

	const Poco::Nullable<std::string>& job_desc() const;
	JobDef& job_desc(const Poco::Nullable<std::string>& value);

	Poco::Int32 schd_typ_enu() const;
	JobDef& schd_typ_enu(Poco::Int32 value);

	Poco::Int32 job_typ_enu() const;
	JobDef& job_typ_enu(Poco::Int32 value);

	const Poco::Nullable<std::string>& div_cd() const;
	JobDef& div_cd(const Poco::Nullable<std::string>& value);

	const Poco::Nullable<std::string>& parm_1() const;
	JobDef& parm_1(const Poco::Nullable<std::string>& value);

	const Poco::Nullable<std::string>& parm_2() const;
	JobDef& parm_2(const Poco::Nullable<std::string>& value);

	const Poco::Nullable<std::string>& parm_3() const;
	JobDef& parm_3(const Poco::Nullable<std::string>& value);

	const Poco::Nullable<std::string>& parm_4() const;
	JobDef& parm_4(const Poco::Nullable<std::string>& value);

	const Poco::Nullable<std::string>& parm_5() const;
	JobDef& parm_5(const Poco::Nullable<std::string>& value);

	const Poco::DateTime& crtd_dtt() const;
	JobDef& crtd_dtt(const Poco::DateTime& value);

	const std::string& crtd_usr_cd() const;
	JobDef& crtd_usr_cd(const std::string& value);

	const Poco::Nullable<Poco::DateTime>& updt_dtt() const;
	JobDef& updt_dtt(const Poco::Nullable<Poco::DateTime>& value);

	const Poco::Nullable<std::string>& updt_usr_cd() const;
	JobDef& updt_usr_cd(const Poco::Nullable<std::string>& value);

	const Poco::Nullable<std::string>& tplt_file() const;
	JobDef& tplt_file(const Poco::Nullable<std::string>& value);

	const Poco::Nullable<std::string>& outpt_file() const;
	JobDef& outpt_file(const Poco::Nullable<std::string>& value);

	const Poco::Nullable<Poco::Int32>& prty() const;
	JobDef& prty(const Poco::Nullable<Poco::Int32>& value);

	const std::string& actv_yn() const;
	JobDef& actv_yn(const std::string& value);

	const Poco::Nullable<std::string>& alrt_grp_cd_success() const;
	JobDef& alrt_grp_cd_success(const Poco::Nullable<std::string>& value);

	const Poco::Nullable<std::string>& alrt_grp_cd_failure() const;
	JobDef& alrt_grp_cd_failure(const Poco::Nullable<std::string>& value);

	const std::string& gen_enty_output_yn() const;
	JobDef& gen_enty_output_yn(const std::string& value);

	SchdDetl::Ptr schd_detl_id() const;
	const Poco::Nullable<Poco::Int32>& schd_detl_idID() const;
	JobDef& schd_detl_id(SchdDetl::Ptr pObject);
	JobDef& schd_detl_idID(const Poco::Nullable<Poco::Int32>& id);

	JobDef::Ptr next_job_cd_success() const;
	const Poco::Nullable<std::string>& next_job_cd_successID() const;
	JobDef& next_job_cd_success(JobDef::Ptr pObject);
	JobDef& next_job_cd_successID(const Poco::Nullable<std::string>& id);

	JobDef::Ptr next_job_cd_failure() const;
	const Poco::Nullable<std::string>& next_job_cd_failureID() const;
	JobDef& next_job_cd_failure(JobDef::Ptr pObject);
	JobDef& next_job_cd_failureID(const Poco::Nullable<std::string>& id);

	AdtnData::Ptr tplt_id() const;
	const Poco::Nullable<Poco::Int32>& tplt_idID() const;
	JobDef& tplt_id(AdtnData::Ptr pObject);
	JobDef& tplt_idID(const Poco::Nullable<Poco::Int32>& id);

	static Ptr find(Poco::ActiveRecord::Context::Ptr pContext, const ID& id);

	void insert();
	void update();
	void remove();

	static const std::vector<std::string>& columns();
	static const std::string& table();

private:
	Poco::Int32 _opt_lck = 0;
	Poco::Nullable<std::string> _job_desc;
	Poco::Int32 _schd_typ_enu = 0;
	Poco::Int32 _job_typ_enu = 0;
	Poco::Nullable<std::string> _div_cd;
	Poco::Nullable<std::string> _parm_1;
	Poco::Nullable<std::string> _parm_2;
	Poco::Nullable<std::string> _parm_3;
	Poco::Nullable<std::string> _parm_4;
	Poco::Nullable<std::string> _parm_5;
	Poco::DateTime _crtd_dtt;
	std::string _crtd_usr_cd;
	Poco::Nullable<Poco::DateTime> _updt_dtt;
	Poco::Nullable<std::string> _updt_usr_cd;
	Poco::Nullable<std::string> _tplt_file;
	Poco::Nullable<std::string> _outpt_file;
	Poco::Nullable<Poco::Int32> _schd_detl_id;
	Poco::Nullable<Poco::Int32> _prty;
	std::string _actv_yn;
	Poco::Nullable<std::string> _next_job_cd_success;
	Poco::Nullable<std::string> _next_job_cd_failure;
	Poco::Nullable<std::string> _alrt_grp_cd_success;
	Poco::Nullable<std::string> _alrt_grp_cd_failure;
	std::string _gen_enty_output_yn;
	Poco::Nullable<Poco::Int32> _tplt_id;

	friend class Poco::Data::TypeHandler<JobDef>;
};


inline Poco::Int32 JobDef::opt_lck() const
{
	return _opt_lck;
}


inline JobDef& JobDef::opt_lck(Poco::Int32 value)
{
	_opt_lck = value;
	return *this;
}


inline const Poco::Nullable<std::string>& JobDef::job_desc() const
{
	return _job_desc;
}


inline JobDef& JobDef::job_desc(const Poco::Nullable<std::string>& value)
{
	_job_desc = value;
	return *this;
}


inline Poco::Int32 JobDef::schd_typ_enu() const
{
	return _schd_typ_enu;
}


inline JobDef& JobDef::schd_typ_enu(Poco::Int32 value)
{
	_schd_typ_enu = value;
	return *this;
}


inline Poco::Int32 JobDef::job_typ_enu() const
{
	return _job_typ_enu;
}


inline JobDef& JobDef::job_typ_enu(Poco::Int32 value)
{
	_job_typ_enu = value;
	return *this;
}


inline const Poco::Nullable<std::string>& JobDef::div_cd() const
{
	return _div_cd;
}


inline JobDef& JobDef::div_cd(const Poco::Nullable<std::string>& value)
{
	_div_cd = value;
	return *this;
}


inline const Poco::Nullable<std::string>& JobDef::parm_1() const
{
	return _parm_1;
}


inline JobDef& JobDef::parm_1(const Poco::Nullable<std::string>& value)
{
	_parm_1 = value;
	return *this;
}


inline const Poco::Nullable<std::string>& JobDef::parm_2() const
{
	return _parm_2;
}


inline JobDef& JobDef::parm_2(const Poco::Nullable<std::string>& value)
{
	_parm_2 = value;
	return *this;
}


inline const Poco::Nullable<std::string>& JobDef::parm_3() const
{
	return _parm_3;
}


inline JobDef& JobDef::parm_3(const Poco::Nullable<std::string>& value)
{
	_parm_3 = value;
	return *this;
}


inline const Poco::Nullable<std::string>& JobDef::parm_4() const
{
	return _parm_4;
}


inline JobDef& JobDef::parm_4(const Poco::Nullable<std::string>& value)
{
	_parm_4 = value;
	return *this;
}


inline const Poco::Nullable<std::string>& JobDef::parm_5() const
{
	return _parm_5;
}


inline JobDef& JobDef::parm_5(const Poco::Nullable<std::string>& value)
{
	_parm_5 = value;
	return *this;
}


inline const Poco::DateTime& JobDef::crtd_dtt() const
{
	return _crtd_dtt;
}


inline JobDef& JobDef::crtd_dtt(const Poco::DateTime& value)
{
	_crtd_dtt = value;
	return *this;
}


inline const std::string& JobDef::crtd_usr_cd() const
{
	return _crtd_usr_cd;
}


inline JobDef& JobDef::crtd_usr_cd(const std::string& value)
{
	_crtd_usr_cd = value;
	return *this;
}


inline const Poco::Nullable<Poco::DateTime>& JobDef::updt_dtt() const
{
	return _updt_dtt;
}


inline JobDef& JobDef::updt_dtt(const Poco::Nullable<Poco::DateTime>& value)
{
	_updt_dtt = value;
	return *this;
}


inline const Poco::Nullable<std::string>& JobDef::updt_usr_cd() const
{
	return _updt_usr_cd;
}


inline JobDef& JobDef::updt_usr_cd(const Poco::Nullable<std::string>& value)
{
	_updt_usr_cd = value;
	return *this;
}


inline const Poco::Nullable<std::string>& JobDef::tplt_file() const
{
	return _tplt_file;
}


inline JobDef& JobDef::tplt_file(const Poco::Nullable<std::string>& value)
{
	_tplt_file = value;
	return *this;
}


inline const Poco::Nullable<std::string>& JobDef::outpt_file() const
{
	return _outpt_file;
}


inline JobDef& JobDef::outpt_file(const Poco::Nullable<std::string>& value)
{
	_outpt_file = value;
	return *this;
}


inline const Poco::Nullable<Poco::Int32>& JobDef::prty() const
{
	return _prty;
}


inline JobDef& JobDef::prty(const Poco::Nullable<Poco::Int32>& value)
{
	_prty = value;
	return *this;
}


inline const std::string& JobDef::actv_yn() const
{
	return _actv_yn;
}


inline JobDef& JobDef::actv_yn(const std::string& value)
{
	_actv_yn = value;
	return *this;
}


inline const Poco::Nullable<std::string>& JobDef::alrt_grp_cd_success() const
{
	return _alrt_grp_cd_success;
}


inline JobDef& JobDef::alrt_grp_cd_success(const Poco::Nullable<std::string>& value)
{
	_alrt_grp_cd_success = value;
	return *this;
}


inline const Poco::Nullable<std::string>& JobDef::alrt_grp_cd_failure() const
{
	return _alrt_grp_cd_failure;
}


inline JobDef& JobDef::alrt_grp_cd_failure(const Poco::Nullable<std::string>& value)
{
	_alrt_grp_cd_failure = value;
	return *this;
}


inline const std::string& JobDef::gen_enty_output_yn() const
{
	return _gen_enty_output_yn;
}


inline JobDef& JobDef::gen_enty_output_yn(const std::string& value)
{
	_gen_enty_output_yn = value;
	return *this;
}


inline const Poco::Nullable<Poco::Int32>& JobDef::schd_detl_idID() const
{
	return _schd_detl_id;
}


inline JobDef& JobDef::schd_detl_idID(const Poco::Nullable<Poco::Int32>& value)
{
	_schd_detl_id = value;
	return *this;
}


inline const Poco::Nullable<std::string>& JobDef::next_job_cd_successID() const
{
	return _next_job_cd_success;
}


inline JobDef& JobDef::next_job_cd_successID(const Poco::Nullable<std::string>& value)
{
	_next_job_cd_success = value;
	return *this;
}


inline const Poco::Nullable<std::string>& JobDef::next_job_cd_failureID() const
{
	return _next_job_cd_failure;
}


inline JobDef& JobDef::next_job_cd_failureID(const Poco::Nullable<std::string>& value)
{
	_next_job_cd_failure = value;
	return *this;
}


inline const Poco::Nullable<Poco::Int32>& JobDef::tplt_idID() const
{
	return _tplt_id;
}


inline JobDef& JobDef::tplt_idID(const Poco::Nullable<Poco::Int32>& value)
{
	_tplt_id = value;
	return *this;
}


} } // namespace asarum:BY


namespace Poco {
namespace Data {


template <>
class TypeHandler<asarum::BY::JobDef>
{
public:
	static std::size_t size()
	{
		return 25;
	}

	static void bind(std::size_t pos, const asarum::BY::JobDef& ar, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir)
	{
		TypeHandler<Poco::Int32>::bind(pos++, ar._opt_lck, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._job_desc, pBinder, dir);
		TypeHandler<Poco::Int32>::bind(pos++, ar._schd_typ_enu, pBinder, dir);
		TypeHandler<Poco::Int32>::bind(pos++, ar._job_typ_enu, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._div_cd, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._parm_1, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._parm_2, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._parm_3, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._parm_4, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._parm_5, pBinder, dir);
		TypeHandler<Poco::DateTime>::bind(pos++, ar._crtd_dtt, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._crtd_usr_cd, pBinder, dir);
		TypeHandler<Poco::Nullable<Poco::DateTime>>::bind(pos++, ar._updt_dtt, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._updt_usr_cd, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._tplt_file, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._outpt_file, pBinder, dir);
		TypeHandler<Poco::Nullable<Poco::Int32>>::bind(pos++, ar._schd_detl_id, pBinder, dir);
		TypeHandler<Poco::Nullable<Poco::Int32>>::bind(pos++, ar._prty, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._actv_yn, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._next_job_cd_success, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._next_job_cd_failure, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._alrt_grp_cd_success, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._alrt_grp_cd_failure, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._gen_enty_output_yn, pBinder, dir);
		TypeHandler<Poco::Nullable<Poco::Int32>>::bind(pos++, ar._tplt_id, pBinder, dir);
}

	static void extract(std::size_t pos, asarum::BY::JobDef& ar, const asarum::BY::JobDef& deflt, AbstractExtractor::Ptr pExtr)
	{
		TypeHandler<Poco::Int32>::extract(pos++, ar._opt_lck, deflt._opt_lck, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._job_desc, deflt._job_desc, pExtr);
		TypeHandler<Poco::Int32>::extract(pos++, ar._schd_typ_enu, deflt._schd_typ_enu, pExtr);
		TypeHandler<Poco::Int32>::extract(pos++, ar._job_typ_enu, deflt._job_typ_enu, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._div_cd, deflt._div_cd, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._parm_1, deflt._parm_1, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._parm_2, deflt._parm_2, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._parm_3, deflt._parm_3, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._parm_4, deflt._parm_4, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._parm_5, deflt._parm_5, pExtr);
		TypeHandler<Poco::DateTime>::extract(pos++, ar._crtd_dtt, deflt._crtd_dtt, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._crtd_usr_cd, deflt._crtd_usr_cd, pExtr);
		TypeHandler<Poco::Nullable<Poco::DateTime>>::extract(pos++, ar._updt_dtt, deflt._updt_dtt, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._updt_usr_cd, deflt._updt_usr_cd, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._tplt_file, deflt._tplt_file, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._outpt_file, deflt._outpt_file, pExtr);
		TypeHandler<Poco::Nullable<Poco::Int32>>::extract(pos++, ar._schd_detl_id, deflt._schd_detl_id, pExtr);
		TypeHandler<Poco::Nullable<Poco::Int32>>::extract(pos++, ar._prty, deflt._prty, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._actv_yn, deflt._actv_yn, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._next_job_cd_success, deflt._next_job_cd_success, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._next_job_cd_failure, deflt._next_job_cd_failure, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._alrt_grp_cd_success, deflt._alrt_grp_cd_success, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._alrt_grp_cd_failure, deflt._alrt_grp_cd_failure, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._gen_enty_output_yn, deflt._gen_enty_output_yn, pExtr);
		TypeHandler<Poco::Nullable<Poco::Int32>>::extract(pos++, ar._tplt_id, deflt._tplt_id, pExtr);
}

	static void prepare(std::size_t pos, const asarum::BY::JobDef& ar, AbstractPreparator::Ptr pPrep)
	{
		TypeHandler<Poco::Int32>::prepare(pos++, ar._opt_lck, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._job_desc, pPrep);
		TypeHandler<Poco::Int32>::prepare(pos++, ar._schd_typ_enu, pPrep);
		TypeHandler<Poco::Int32>::prepare(pos++, ar._job_typ_enu, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._div_cd, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._parm_1, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._parm_2, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._parm_3, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._parm_4, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._parm_5, pPrep);
		TypeHandler<Poco::DateTime>::prepare(pos++, ar._crtd_dtt, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._crtd_usr_cd, pPrep);
		TypeHandler<Poco::Nullable<Poco::DateTime>>::prepare(pos++, ar._updt_dtt, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._updt_usr_cd, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._tplt_file, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._outpt_file, pPrep);
		TypeHandler<Poco::Nullable<Poco::Int32>>::prepare(pos++, ar._schd_detl_id, pPrep);
		TypeHandler<Poco::Nullable<Poco::Int32>>::prepare(pos++, ar._prty, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._actv_yn, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._next_job_cd_success, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._next_job_cd_failure, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._alrt_grp_cd_success, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._alrt_grp_cd_failure, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._gen_enty_output_yn, pPrep);
		TypeHandler<Poco::Nullable<Poco::Int32>>::prepare(pos++, ar._tplt_id, pPrep);
	}
};


} } // namespace Poco::Data


#endif // asarum_BY_JobDef_INCLUDED
