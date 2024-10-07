//
// SchdDetl.cpp
//
// This file has been generated from jobdoc.xml. Do not edit.
//


#include "asarum/BY/SchdDetl.h"


using namespace std::string_literals;
using namespace Poco::Data::Keywords;


namespace asarum {
namespace BY {


SchdDetl::SchdDetl(ID id):
	Poco::ActiveRecord::ActiveRecord<Poco::Int32>(id)
{
}


SchdDetl::SchdDetl(const SchdDetl& other):
	Poco::ActiveRecord::ActiveRecord<Poco::Int32>(other),
	_opt_lck(other._opt_lck),
	_rcurnce_typ_enu(other._rcurnce_typ_enu),
	_efct_dt(other._efct_dt),
	_expd_dt(other._expd_dt),
	_strt_tm(other._strt_tm),
	_end_tm(other._end_tm),
	_day_of_mth(other._day_of_mth),
	_itvl(other._itvl),
	_fxd_itvl_src_enu(other._fxd_itvl_src_enu),
	_bus_days_cd(other._bus_days_cd),
	_bus_mths_cd(other._bus_mths_cd)
{
}


SchdDetl::Ptr SchdDetl::find(Poco::ActiveRecord::Context::Ptr pContext, const ID& id)
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(pContext->statementPlaceholderProvider());
	SchdDetl::Ptr pObject(new SchdDetl);

	pContext->session()
		<< "SELECT schd_detl_id, opt_lck, rcurnce_typ_enu, efct_dt, expd_dt, strt_tm, end_tm, day_of_mth, itvl, fxd_itvl_src_enu, bus_days_cd, bus_mths_cd"
		<< "  FROM SCHD_DETL_T"
		<< "  WHERE schd_detl_id = " << pSPP->next(),
		into(pObject->mutableID()),
		into(*pObject),
		bind(id),
		now;

	return withContext(pObject, pContext);
}


void SchdDetl::insert()
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(context()->statementPlaceholderProvider());

	context()->session()
		<< "INSERT INTO SCHD_DETL_T (schd_detl_id, opt_lck, rcurnce_typ_enu, efct_dt, expd_dt, strt_tm, end_tm, day_of_mth, itvl, fxd_itvl_src_enu, bus_days_cd, bus_mths_cd)"
		<< "  VALUES (" << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ")",
		bind(id()),
		use(*this),
		now;
}


void SchdDetl::update()
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(context()->statementPlaceholderProvider());

	context()->session()
		<< "UPDATE SCHD_DETL_T"
		<< "  SET opt_lck = " << pSPP->next() << ", rcurnce_typ_enu = " << pSPP->next() << ", efct_dt = " << pSPP->next() << ", expd_dt = " << pSPP->next() << ", strt_tm = " << pSPP->next() << ", end_tm = " << pSPP->next() << ", day_of_mth = " << pSPP->next() << ", itvl = " << pSPP->next() << ", fxd_itvl_src_enu = " << pSPP->next() << ", bus_days_cd = " << pSPP->next() << ", bus_mths_cd = " << pSPP->next()
		<< "  WHERE schd_detl_id = " << pSPP->next(),
		use(*this),
		bind(id()),
		now;
}


void SchdDetl::remove()
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(context()->statementPlaceholderProvider());

	context()->session()
		<< "DELETE FROM SCHD_DETL_T"
		<< "  WHERE schd_detl_id = " << pSPP->next(),
		bind(id()),
		now;
}


const std::vector<std::string>& SchdDetl::columns()
{
	static const std::vector<std::string> cols =
	{
		"schd_detl_id"s,
		"opt_lck"s,
		"rcurnce_typ_enu"s,
		"efct_dt"s,
		"expd_dt"s,
		"strt_tm"s,
		"end_tm"s,
		"day_of_mth"s,
		"itvl"s,
		"fxd_itvl_src_enu"s,
		"bus_days_cd"s,
		"bus_mths_cd"s,
	};

	return cols;
}


const std::string& SchdDetl::table()
{
	static const std::string t = "SCHD_DETL_T";
	return t;
}


} } // namespace asarum:BY
