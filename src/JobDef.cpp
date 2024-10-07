//
// JobDef.cpp
//
// This file has been generated from jobdoc.xml. Do not edit.
//


#include "asarum/BY/JobDef.h"


using namespace std::string_literals;
using namespace Poco::Data::Keywords;


namespace asarum {
namespace BY {


JobDef::JobDef(ID id):
	Poco::ActiveRecord::ActiveRecord<std::string>(id)
{
}


JobDef::JobDef(const JobDef& other):
	Poco::ActiveRecord::ActiveRecord<std::string>(other),
	_opt_lck(other._opt_lck),
	_job_desc(other._job_desc),
	_schd_typ_enu(other._schd_typ_enu),
	_job_typ_enu(other._job_typ_enu),
	_div_cd(other._div_cd),
	_parm_1(other._parm_1),
	_parm_2(other._parm_2),
	_parm_3(other._parm_3),
	_parm_4(other._parm_4),
	_parm_5(other._parm_5),
	_crtd_dtt(other._crtd_dtt),
	_crtd_usr_cd(other._crtd_usr_cd),
	_updt_dtt(other._updt_dtt),
	_updt_usr_cd(other._updt_usr_cd),
	_tplt_file(other._tplt_file),
	_outpt_file(other._outpt_file),
	_schd_detl_id(other._schd_detl_id),
	_prty(other._prty),
	_actv_yn(other._actv_yn),
	_next_job_cd_success(other._next_job_cd_success),
	_next_job_cd_failure(other._next_job_cd_failure),
	_alrt_grp_cd_success(other._alrt_grp_cd_success),
	_alrt_grp_cd_failure(other._alrt_grp_cd_failure),
	_gen_enty_output_yn(other._gen_enty_output_yn),
	_tplt_id(other._tplt_id)
{
}


SchdDetl::Ptr JobDef::schd_detl_id() const
{
	if (!_schd_detl_id.isNull())
		return SchdDetl::find(context(), _schd_detl_id.value());
	else
		return nullptr;
}


JobDef& JobDef::schd_detl_id(SchdDetl::Ptr pObject)
{
	if (pObject)
		_schd_detl_id = pObject->id();
	else
		_schd_detl_id = SchdDetl::INVALID_ID;
	return *this;
}


JobDef::Ptr JobDef::next_job_cd_success() const
{
	if (!_next_job_cd_success.isNull())
		return JobDef::find(context(), _next_job_cd_success.value());
	else
		return nullptr;
}


JobDef& JobDef::next_job_cd_success(JobDef::Ptr pObject)
{
	if (pObject)
		_next_job_cd_success = pObject->id();
	else
		_next_job_cd_success = JobDef::INVALID_ID;
	return *this;
}


JobDef::Ptr JobDef::next_job_cd_failure() const
{
	if (!_next_job_cd_failure.isNull())
		return JobDef::find(context(), _next_job_cd_failure.value());
	else
		return nullptr;
}


JobDef& JobDef::next_job_cd_failure(JobDef::Ptr pObject)
{
	if (pObject)
		_next_job_cd_failure = pObject->id();
	else
		_next_job_cd_failure = JobDef::INVALID_ID;
	return *this;
}


AdtnData::Ptr JobDef::tplt_id() const
{
	if (!_tplt_id.isNull())
		return AdtnData::find(context(), _tplt_id.value());
	else
		return nullptr;
}


JobDef& JobDef::tplt_id(AdtnData::Ptr pObject)
{
	if (pObject)
		_tplt_id = pObject->id();
	else
		_tplt_id = AdtnData::INVALID_ID;
	return *this;
}


JobDef::Ptr JobDef::find(Poco::ActiveRecord::Context::Ptr pContext, const ID& id)
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(pContext->statementPlaceholderProvider());
	JobDef::Ptr pObject(new JobDef);

	pContext->session()
		<< "SELECT job_cd, opt_lck, job_desc, schd_typ_enu, job_typ_enu, div_cd, parm_1, parm_2, parm_3, parm_4, parm_5, crtd_dtt, crtd_usr_cd, updt_dtt, updt_usr_cd, tplt_file, outpt_file, schd_detl_id, prty, actv_yn, next_job_cd_success, next_job_cd_failure, alrt_grp_cd_success, alrt_grp_cd_failure, gen_enty_output_yn, tplt_id"
		<< "  FROM JOB_DEFN_T"
		<< "  WHERE job_cd = " << pSPP->next(),
		into(pObject->mutableID()),
		into(*pObject),
		bind(id),
		now;

	return withContext(pObject, pContext);
}


void JobDef::insert()
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(context()->statementPlaceholderProvider());

	context()->session()
		<< "INSERT INTO JOB_DEFN_T (job_cd, opt_lck, job_desc, schd_typ_enu, job_typ_enu, div_cd, parm_1, parm_2, parm_3, parm_4, parm_5, crtd_dtt, crtd_usr_cd, updt_dtt, updt_usr_cd, tplt_file, outpt_file, schd_detl_id, prty, actv_yn, next_job_cd_success, next_job_cd_failure, alrt_grp_cd_success, alrt_grp_cd_failure, gen_enty_output_yn, tplt_id)"
		<< "  VALUES (" << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ")",
		bind(id()),
		use(*this),
		now;
}


void JobDef::update()
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(context()->statementPlaceholderProvider());

	context()->session()
		<< "UPDATE JOB_DEFN_T"
		<< "  SET opt_lck = " << pSPP->next() << ", job_desc = " << pSPP->next() << ", schd_typ_enu = " << pSPP->next() << ", job_typ_enu = " << pSPP->next() << ", div_cd = " << pSPP->next() << ", parm_1 = " << pSPP->next() << ", parm_2 = " << pSPP->next() << ", parm_3 = " << pSPP->next() << ", parm_4 = " << pSPP->next() << ", parm_5 = " << pSPP->next() << ", crtd_dtt = " << pSPP->next() << ", crtd_usr_cd = " << pSPP->next() << ", updt_dtt = " << pSPP->next() << ", updt_usr_cd = " << pSPP->next() << ", tplt_file = " << pSPP->next() << ", outpt_file = " << pSPP->next() << ", schd_detl_id = " << pSPP->next() << ", prty = " << pSPP->next() << ", actv_yn = " << pSPP->next() << ", next_job_cd_success = " << pSPP->next() << ", next_job_cd_failure = " << pSPP->next() << ", alrt_grp_cd_success = " << pSPP->next() << ", alrt_grp_cd_failure = " << pSPP->next() << ", gen_enty_output_yn = " << pSPP->next() << ", tplt_id = " << pSPP->next()
		<< "  WHERE job_cd = " << pSPP->next(),
		use(*this),
		bind(id()),
		now;
}


void JobDef::remove()
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(context()->statementPlaceholderProvider());

	context()->session()
		<< "DELETE FROM JOB_DEFN_T"
		<< "  WHERE job_cd = " << pSPP->next(),
		bind(id()),
		now;
}


const std::vector<std::string>& JobDef::columns()
{
	static const std::vector<std::string> cols =
	{
		"job_cd"s,
		"opt_lck"s,
		"job_desc"s,
		"schd_typ_enu"s,
		"job_typ_enu"s,
		"div_cd"s,
		"parm_1"s,
		"parm_2"s,
		"parm_3"s,
		"parm_4"s,
		"parm_5"s,
		"crtd_dtt"s,
		"crtd_usr_cd"s,
		"updt_dtt"s,
		"updt_usr_cd"s,
		"tplt_file"s,
		"outpt_file"s,
		"schd_detl_id"s,
		"prty"s,
		"actv_yn"s,
		"next_job_cd_success"s,
		"next_job_cd_failure"s,
		"alrt_grp_cd_success"s,
		"alrt_grp_cd_failure"s,
		"gen_enty_output_yn"s,
		"tplt_id"s,
	};

	return cols;
}


const std::string& JobDef::table()
{
	static const std::string t = "JOB_DEFN_T";
	return t;
}


} } // namespace asarum:BY
