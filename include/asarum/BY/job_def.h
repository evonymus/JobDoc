//
// JobDef.h
//
// This file has been generated from jobdoc.xml. Do not edit.
//


#ifndef asarum_BY_JobDef_INCLUDED
#define asarum_BY_JobDef_INCLUDED


#include "Poco/ActiveRecord/ActiveRecord.h"


namespace asarum {
namespace BY {


class JobDef: public Poco::ActiveRecord::KeylessActiveRecord
{
public:
	using Ptr = Poco::AutoPtr<JobDef>;

	JobDef() = default;
	JobDef(const JobDef& other);
	~JobDef() = default;

	const std::string& job_cd() const;
	JobDef& job_cd(const std::string& value);

	Poco::Int16 opt_lck() const;
	JobDef& opt_lck(Poco::Int16 value);

	const std::string& job_desc() const;
	JobDef& job_desc(const std::string& value);

	Poco::Int16 schd_typ_enu() const;
	JobDef& schd_typ_enu(Poco::Int16 value);

	Poco::Int16 job_typ_enu() const;
	JobDef& job_typ_enu(Poco::Int16 value);

	const std::string& div_cd() const;
	JobDef& div_cd(const std::string& value);

	const std::string& parm_1() const;
	JobDef& parm_1(const std::string& value);

	const std::string& parm_2() const;
	JobDef& parm_2(const std::string& value);

	const std::string& parm_3() const;
	JobDef& parm_3(const std::string& value);

	const std::string& parm_4() const;
	JobDef& parm_4(const std::string& value);

	const std::string& parm_5() const;
	JobDef& parm_5(const std::string& value);

	const Poco::DateTime& crt_dtt() const;
	JobDef& crt_dtt(const Poco::DateTime& value);

	const std::string& crtd_usr_cd() const;
	JobDef& crtd_usr_cd(const std::string& value);

	const Poco::DateTime& updt_dtt() const;
	JobDef& updt_dtt(const Poco::DateTime& value);

	const std::string& updt_usr_cd() const;
	JobDef& updt_usr_cd(const std::string& value);

	const std::string& tplt_file() const;
	JobDef& tplt_file(const std::string& value);

	const std::string& output_file() const;
	JobDef& output_file(const std::string& value);

	Poco::Int32 schd_detl_id() const;
	JobDef& schd_detl_id(Poco::Int32 value);

	Poco::Int16 prty() const;
	JobDef& prty(Poco::Int16 value);

	char acty_yn() const;
	JobDef& acty_yn(char value);

	const std::string& next_job_cd_success() const;
	JobDef& next_job_cd_success(const std::string& value);

	const std::string& next_job_cd_failure() const;
	JobDef& next_job_cd_failure(const std::string& value);

	const std::string& alrt_grp_cd_success() const;
	JobDef& alrt_grp_cd_success(const std::string& value);

	const std::string& alrt_grp_cd_failure() const;
	JobDef& alrt_grp_cd_failure(const std::string& value);

	char gen_enty_output_yn() const;
	JobDef& gen_enty_output_yn(char value);

	Poco::Int32 tplt_id() const;
	JobDef& tplt_id(Poco::Int32 value);

	void insert();
	void update();
	void remove();

	static const std::vector<std::string>& columns();
	static const std::string& table();

private:
	std::string _job_cd;
	Poco::Int16 _opt_lck = 0;
	std::string _job_desc;
	Poco::Int16 _schd_typ_enu = 0;
	Poco::Int16 _job_typ_enu = 0;
	std::string _div_cd;
	std::string _parm_1;
	std::string _parm_2;
	std::string _parm_3;
	std::string _parm_4;
	std::string _parm_5;
	Poco::DateTime _crt_dtt;
	std::string _crtd_usr_cd;
	Poco::DateTime _updt_dtt;
	std::string _updt_usr_cd;
	std::string _tplt_file;
	std::string _output_file;
	Poco::Int32 _schd_detl_id = 0;
	Poco::Int16 _prty = 0;
	char _acty_yn = 0;
	std::string _next_job_cd_success;
	std::string _next_job_cd_failure;
	std::string _alrt_grp_cd_success;
	std::string _alrt_grp_cd_failure;
	char _gen_enty_output_yn = 0;
	Poco::Int32 _tplt_id = 0;

	friend class Poco::Data::TypeHandler<JobDef>;
};


inline const std::string& JobDef::job_cd() const
{
	return _job_cd;
}


inline JobDef& JobDef::job_cd(const std::string& value)
{
	_job_cd = value;
	return *this;
}


inline Poco::Int16 JobDef::opt_lck() const
{
	return _opt_lck;
}


inline JobDef& JobDef::opt_lck(Poco::Int16 value)
{
	_opt_lck = value;
	return *this;
}


inline const std::string& JobDef::job_desc() const
{
	return _job_desc;
}


inline JobDef& JobDef::job_desc(const std::string& value)
{
	_job_desc = value;
	return *this;
}


inline Poco::Int16 JobDef::schd_typ_enu() const
{
	return _schd_typ_enu;
}


inline JobDef& JobDef::schd_typ_enu(Poco::Int16 value)
{
	_schd_typ_enu = value;
	return *this;
}


inline Poco::Int16 JobDef::job_typ_enu() const
{
	return _job_typ_enu;
}


inline JobDef& JobDef::job_typ_enu(Poco::Int16 value)
{
	_job_typ_enu = value;
	return *this;
}


inline const std::string& JobDef::div_cd() const
{
	return _div_cd;
}


inline JobDef& JobDef::div_cd(const std::string& value)
{
	_div_cd = value;
	return *this;
}


inline const std::string& JobDef::parm_1() const
{
	return _parm_1;
}


inline JobDef& JobDef::parm_1(const std::string& value)
{
	_parm_1 = value;
	return *this;
}


inline const std::string& JobDef::parm_2() const
{
	return _parm_2;
}


inline JobDef& JobDef::parm_2(const std::string& value)
{
	_parm_2 = value;
	return *this;
}


inline const std::string& JobDef::parm_3() const
{
	return _parm_3;
}


inline JobDef& JobDef::parm_3(const std::string& value)
{
	_parm_3 = value;
	return *this;
}


inline const std::string& JobDef::parm_4() const
{
	return _parm_4;
}


inline JobDef& JobDef::parm_4(const std::string& value)
{
	_parm_4 = value;
	return *this;
}


inline const std::string& JobDef::parm_5() const
{
	return _parm_5;
}


inline JobDef& JobDef::parm_5(const std::string& value)
{
	_parm_5 = value;
	return *this;
}


inline const Poco::DateTime& JobDef::crt_dtt() const
{
	return _crt_dtt;
}


inline JobDef& JobDef::crt_dtt(const Poco::DateTime& value)
{
	_crt_dtt = value;
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


inline const Poco::DateTime& JobDef::updt_dtt() const
{
	return _updt_dtt;
}


inline JobDef& JobDef::updt_dtt(const Poco::DateTime& value)
{
	_updt_dtt = value;
	return *this;
}


inline const std::string& JobDef::updt_usr_cd() const
{
	return _updt_usr_cd;
}


inline JobDef& JobDef::updt_usr_cd(const std::string& value)
{
	_updt_usr_cd = value;
	return *this;
}


inline const std::string& JobDef::tplt_file() const
{
	return _tplt_file;
}


inline JobDef& JobDef::tplt_file(const std::string& value)
{
	_tplt_file = value;
	return *this;
}


inline const std::string& JobDef::output_file() const
{
	return _output_file;
}


inline JobDef& JobDef::output_file(const std::string& value)
{
	_output_file = value;
	return *this;
}


inline Poco::Int32 JobDef::schd_detl_id() const
{
	return _schd_detl_id;
}


inline JobDef& JobDef::schd_detl_id(Poco::Int32 value)
{
	_schd_detl_id = value;
	return *this;
}


inline Poco::Int16 JobDef::prty() const
{
	return _prty;
}


inline JobDef& JobDef::prty(Poco::Int16 value)
{
	_prty = value;
	return *this;
}


inline char JobDef::acty_yn() const
{
	return _acty_yn;
}


inline JobDef& JobDef::acty_yn(char value)
{
	_acty_yn = value;
	return *this;
}


inline const std::string& JobDef::next_job_cd_success() const
{
	return _next_job_cd_success;
}


inline JobDef& JobDef::next_job_cd_success(const std::string& value)
{
	_next_job_cd_success = value;
	return *this;
}


inline const std::string& JobDef::next_job_cd_failure() const
{
	return _next_job_cd_failure;
}


inline JobDef& JobDef::next_job_cd_failure(const std::string& value)
{
	_next_job_cd_failure = value;
	return *this;
}


inline const std::string& JobDef::alrt_grp_cd_success() const
{
	return _alrt_grp_cd_success;
}


inline JobDef& JobDef::alrt_grp_cd_success(const std::string& value)
{
	_alrt_grp_cd_success = value;
	return *this;
}


inline const std::string& JobDef::alrt_grp_cd_failure() const
{
	return _alrt_grp_cd_failure;
}


inline JobDef& JobDef::alrt_grp_cd_failure(const std::string& value)
{
	_alrt_grp_cd_failure = value;
	return *this;
}


inline char JobDef::gen_enty_output_yn() const
{
	return _gen_enty_output_yn;
}


inline JobDef& JobDef::gen_enty_output_yn(char value)
{
	_gen_enty_output_yn = value;
	return *this;
}


inline Poco::Int32 JobDef::tplt_id() const
{
	return _tplt_id;
}


inline JobDef& JobDef::tplt_id(Poco::Int32 value)
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
		return 26;
	}

	static void bind(std::size_t pos, const asarum::BY::JobDef& ar, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir)
	{
		TypeHandler<std::string>::bind(pos++, ar._job_cd, pBinder, dir);
		TypeHandler<Poco::Int16>::bind(pos++, ar._opt_lck, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._job_desc, pBinder, dir);
		TypeHandler<Poco::Int16>::bind(pos++, ar._schd_typ_enu, pBinder, dir);
		TypeHandler<Poco::Int16>::bind(pos++, ar._job_typ_enu, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._div_cd, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._parm_1, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._parm_2, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._parm_3, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._parm_4, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._parm_5, pBinder, dir);
		TypeHandler<Poco::DateTime>::bind(pos++, ar._crt_dtt, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._crtd_usr_cd, pBinder, dir);
		TypeHandler<Poco::DateTime>::bind(pos++, ar._updt_dtt, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._updt_usr_cd, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._tplt_file, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._output_file, pBinder, dir);
		TypeHandler<Poco::Int32>::bind(pos++, ar._schd_detl_id, pBinder, dir);
		TypeHandler<Poco::Int16>::bind(pos++, ar._prty, pBinder, dir);
		TypeHandler<char>::bind(pos++, ar._acty_yn, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._next_job_cd_success, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._next_job_cd_failure, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._alrt_grp_cd_success, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._alrt_grp_cd_failure, pBinder, dir);
		TypeHandler<char>::bind(pos++, ar._gen_enty_output_yn, pBinder, dir);
		TypeHandler<Poco::Int32>::bind(pos++, ar._tplt_id, pBinder, dir);
}

	static void extract(std::size_t pos, asarum::BY::JobDef& ar, const asarum::BY::JobDef& deflt, AbstractExtractor::Ptr pExtr)
	{
		TypeHandler<std::string>::extract(pos++, ar._job_cd, deflt._job_cd, pExtr);
		TypeHandler<Poco::Int16>::extract(pos++, ar._opt_lck, deflt._opt_lck, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._job_desc, deflt._job_desc, pExtr);
		TypeHandler<Poco::Int16>::extract(pos++, ar._schd_typ_enu, deflt._schd_typ_enu, pExtr);
		TypeHandler<Poco::Int16>::extract(pos++, ar._job_typ_enu, deflt._job_typ_enu, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._div_cd, deflt._div_cd, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._parm_1, deflt._parm_1, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._parm_2, deflt._parm_2, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._parm_3, deflt._parm_3, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._parm_4, deflt._parm_4, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._parm_5, deflt._parm_5, pExtr);
		TypeHandler<Poco::DateTime>::extract(pos++, ar._crt_dtt, deflt._crt_dtt, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._crtd_usr_cd, deflt._crtd_usr_cd, pExtr);
		TypeHandler<Poco::DateTime>::extract(pos++, ar._updt_dtt, deflt._updt_dtt, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._updt_usr_cd, deflt._updt_usr_cd, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._tplt_file, deflt._tplt_file, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._output_file, deflt._output_file, pExtr);
		TypeHandler<Poco::Int32>::extract(pos++, ar._schd_detl_id, deflt._schd_detl_id, pExtr);
		TypeHandler<Poco::Int16>::extract(pos++, ar._prty, deflt._prty, pExtr);
		TypeHandler<char>::extract(pos++, ar._acty_yn, deflt._acty_yn, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._next_job_cd_success, deflt._next_job_cd_success, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._next_job_cd_failure, deflt._next_job_cd_failure, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._alrt_grp_cd_success, deflt._alrt_grp_cd_success, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._alrt_grp_cd_failure, deflt._alrt_grp_cd_failure, pExtr);
		TypeHandler<char>::extract(pos++, ar._gen_enty_output_yn, deflt._gen_enty_output_yn, pExtr);
		TypeHandler<Poco::Int32>::extract(pos++, ar._tplt_id, deflt._tplt_id, pExtr);
}

	static void prepare(std::size_t pos, const asarum::BY::JobDef& ar, AbstractPreparator::Ptr pPrep)
	{
		TypeHandler<std::string>::prepare(pos++, ar._job_cd, pPrep);
		TypeHandler<Poco::Int16>::prepare(pos++, ar._opt_lck, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._job_desc, pPrep);
		TypeHandler<Poco::Int16>::prepare(pos++, ar._schd_typ_enu, pPrep);
		TypeHandler<Poco::Int16>::prepare(pos++, ar._job_typ_enu, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._div_cd, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._parm_1, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._parm_2, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._parm_3, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._parm_4, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._parm_5, pPrep);
		TypeHandler<Poco::DateTime>::prepare(pos++, ar._crt_dtt, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._crtd_usr_cd, pPrep);
		TypeHandler<Poco::DateTime>::prepare(pos++, ar._updt_dtt, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._updt_usr_cd, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._tplt_file, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._output_file, pPrep);
		TypeHandler<Poco::Int32>::prepare(pos++, ar._schd_detl_id, pPrep);
		TypeHandler<Poco::Int16>::prepare(pos++, ar._prty, pPrep);
		TypeHandler<char>::prepare(pos++, ar._acty_yn, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._next_job_cd_success, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._next_job_cd_failure, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._alrt_grp_cd_success, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._alrt_grp_cd_failure, pPrep);
		TypeHandler<char>::prepare(pos++, ar._gen_enty_output_yn, pPrep);
		TypeHandler<Poco::Int32>::prepare(pos++, ar._tplt_id, pPrep);
	}
};


} } // namespace Poco::Data


#endif // asarum_BY_JobDef_INCLUDED
