//
// EntySelCta.cpp
//
// This file has been generated from jobdoc.xml. Do not edit.
//


#include "asarum/BY/EntySelCta.h"


using namespace std::string_literals;
using namespace Poco::Data::Keywords;


namespace asarum {
namespace BY {


EntySelCta::EntySelCta(ID id):
	Poco::ActiveRecord::ActiveRecord<std::string>(id)
{
}


EntySelCta::EntySelCta(const EntySelCta& other):
	Poco::ActiveRecord::ActiveRecord<std::string>(other),
	_opt_lck(other._opt_lck),
	_enty_sel_cta_desc(other._enty_sel_cta_desc),
	_div_cd(other._div_cd),
	_str_id_yn(other._str_id_yn),
	_enty_typ_enu(other._enty_typ_enu),
	_cta_sql(other._cta_sql),
	_cta_find_enty(other._cta_find_enty),
	_crtd_dtt(other._crtd_dtt),
	_crtd_usr_cd(other._crtd_usr_cd),
	_updt_dtt(other._updt_dtt),
	_updt_usr_cd(other._updt_usr_cd),
	_max_entys(other._max_entys)
{
}


EntySelCta::Ptr EntySelCta::find(Poco::ActiveRecord::Context::Ptr pContext, const ID& id)
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(pContext->statementPlaceholderProvider());
	EntySelCta::Ptr pObject(new EntySelCta);

	pContext->session()
		<< "SELECT enty_sel_cta_cd, opt_lck, enty_sel_cta_desc, div_cd, str_id_yn, enty_typ_enu, cta_sql, cta_find_enty, crtd_dtt, crtd_usr_cd, updt_dtt, updt_usr_cd, max_entys"
		<< "  FROM ENTY_SEL_CTA_T"
		<< "  WHERE enty_sel_cta_cd = " << pSPP->next(),
		into(pObject->mutableID()),
		into(*pObject),
		bind(id),
		now;

	return withContext(pObject, pContext);
}


void EntySelCta::insert()
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(context()->statementPlaceholderProvider());

	context()->session()
		<< "INSERT INTO ENTY_SEL_CTA_T (enty_sel_cta_cd, opt_lck, enty_sel_cta_desc, div_cd, str_id_yn, enty_typ_enu, cta_sql, cta_find_enty, crtd_dtt, crtd_usr_cd, updt_dtt, updt_usr_cd, max_entys)"
		<< "  VALUES (" << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ", " << pSPP->next() << ")",
		bind(id()),
		use(*this),
		now;
}


void EntySelCta::update()
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(context()->statementPlaceholderProvider());

	context()->session()
		<< "UPDATE ENTY_SEL_CTA_T"
		<< "  SET opt_lck = " << pSPP->next() << ", enty_sel_cta_desc = " << pSPP->next() << ", div_cd = " << pSPP->next() << ", str_id_yn = " << pSPP->next() << ", enty_typ_enu = " << pSPP->next() << ", cta_sql = " << pSPP->next() << ", cta_find_enty = " << pSPP->next() << ", crtd_dtt = " << pSPP->next() << ", crtd_usr_cd = " << pSPP->next() << ", updt_dtt = " << pSPP->next() << ", updt_usr_cd = " << pSPP->next() << ", max_entys = " << pSPP->next()
		<< "  WHERE enty_sel_cta_cd = " << pSPP->next(),
		use(*this),
		bind(id()),
		now;
}


void EntySelCta::remove()
{
	Poco::ActiveRecord::StatementPlaceholderProvider::Ptr pSPP(context()->statementPlaceholderProvider());

	context()->session()
		<< "DELETE FROM ENTY_SEL_CTA_T"
		<< "  WHERE enty_sel_cta_cd = " << pSPP->next(),
		bind(id()),
		now;
}


const std::vector<std::string>& EntySelCta::columns()
{
	static const std::vector<std::string> cols =
	{
		"enty_sel_cta_cd"s,
		"opt_lck"s,
		"enty_sel_cta_desc"s,
		"div_cd"s,
		"str_id_yn"s,
		"enty_typ_enu"s,
		"cta_sql"s,
		"cta_find_enty"s,
		"crtd_dtt"s,
		"crtd_usr_cd"s,
		"updt_dtt"s,
		"updt_usr_cd"s,
		"max_entys"s,
	};

	return cols;
}


const std::string& EntySelCta::table()
{
	static const std::string t = "ENTY_SEL_CTA_T";
	return t;
}


} } // namespace asarum:BY
