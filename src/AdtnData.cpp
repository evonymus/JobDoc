//
// AdtnData.cpp
//
// This file has been generated from jobdoc.xml. Do not edit.
//


#include "asarum/BY/AdtnData.h"


using namespace std::string_literals;
using namespace Poco::Data::Keywords;


namespace asarum {
namespace BY {


AdtnData::AdtnData(ID id):
	Poco::ActiveRecord::ActiveRecord<Poco::Int32>(id)
{
}


AdtnData::AdtnData(const AdtnData& other):
	Poco::ActiveRecord::ActiveRecord<Poco::Int32>(other),
	_data(other._data),
	_crtd_dtt(other._crtd_dtt),
	_adtn_data_cd(other._adtn_data_cd),
	_adtn_data_typ_enu(other._adtn_data_typ_enu),
	_actv_yn(other._actv_yn),
	_crtd_usr_cd(other._crtd_usr_cd),
	_updt_usr_cd(other._updt_usr_cd),
	_updt_dtt(other._updt_dtt),
	_tplt_fmt_typ_enu(other._tplt_fmt_typ_enu)
{
}


AdtnData::Ptr AdtnData::find(Poco::ActiveRecord::Context::Ptr pContext, const ID& id)
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(pContext->statementPlaceholderProvider());
	AdtnData::Ptr pObject(new AdtnData);

	pContext->session()
		<< "SELECT adtn_data_id, data, crtd_dtt, adtn_data_cd, adtn_data_typ_enu, actv_yn, crtd_usr_cd, updt_usr_cd, updt_dtt, tplt_fmt_typ_enu"
		<< "  FROM ADTN_DATA_T"
		<< "  WHERE adtn_data_id = " << pSPP->next(),
		into(pObject->mutableID()),
		into(*pObject),
		bind(id),
		now;

	return withContext(pObject, pContext);
}


void AdtnData::insert()
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(context()->statementPlaceholderProvider());

	context()->session()
		<< "INSERT INTO ADTN_DATA_T (adtn_data_id, data, crtd_dtt, adtn_data_cd, adtn_data_typ_enu, actv_yn, crtd_usr_cd, updt_usr_cd, updt_dtt, tplt_fmt_typ_enu)"
		<< "  VALUES (" << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ")",
		bind(id()),
		use(*this),
		now;
}


void AdtnData::update()
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(context()->statementPlaceholderProvider());

	context()->session()
		<< "UPDATE ADTN_DATA_T"
		<< "  SET data = " << pSPP->next() << ", crtd_dtt = " << pSPP->next() << ", adtn_data_cd = " << pSPP->next() << ", adtn_data_typ_enu = " << pSPP->next() << ", actv_yn = " << pSPP->next() << ", crtd_usr_cd = " << pSPP->next() << ", updt_usr_cd = " << pSPP->next() << ", updt_dtt = " << pSPP->next() << ", tplt_fmt_typ_enu = " << pSPP->next()
		<< "  WHERE adtn_data_id = " << pSPP->next(),
		use(*this),
		bind(id()),
		now;
}


void AdtnData::remove()
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(context()->statementPlaceholderProvider());

	context()->session()
		<< "DELETE FROM ADTN_DATA_T"
		<< "  WHERE adtn_data_id = " << pSPP->next(),
		bind(id()),
		now;
}


const std::vector<std::string>& AdtnData::columns()
{
	static const std::vector<std::string> cols =
	{
		"adtn_data_id"s,
		"data"s,
		"crtd_dtt"s,
		"adtn_data_cd"s,
		"adtn_data_typ_enu"s,
		"actv_yn"s,
		"crtd_usr_cd"s,
		"updt_usr_cd"s,
		"updt_dtt"s,
		"tplt_fmt_typ_enu"s,
	};

	return cols;
}


const std::string& AdtnData::table()
{
	static const std::string t = "ADTN_DATA_T";
	return t;
}


} } // namespace asarum:BY
