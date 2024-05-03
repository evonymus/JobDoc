//
// EntySelCta.h
//
// This file has been generated from jobdoc.xml. Do not edit.
//


#ifndef asarum_BY_EntySelCta_INCLUDED
#define asarum_BY_EntySelCta_INCLUDED


#include "Poco/ActiveRecord/ActiveRecord.h"


namespace asarum {
namespace BY {


class EntySelCta: public Poco::ActiveRecord::ActiveRecord<std::string>
{
public:
	using Ptr = Poco::AutoPtr<EntySelCta>;

	explicit EntySelCta(ID id);
	EntySelCta() = default;
	EntySelCta(const EntySelCta& other);
	~EntySelCta() = default;

	Poco::Int32 opt_lck() const;
	EntySelCta& opt_lck(Poco::Int32 value);

	const Poco::Nullable<std::string>& enty_sel_cta_desc() const;
	EntySelCta& enty_sel_cta_desc(const Poco::Nullable<std::string>& value);

	const Poco::Nullable<std::string>& div_cd() const;
	EntySelCta& div_cd(const Poco::Nullable<std::string>& value);

	const Poco::Nullable<std::string>& str_id_yn() const;
	EntySelCta& str_id_yn(const Poco::Nullable<std::string>& value);

	Poco::Int32 enty_typ_enu() const;
	EntySelCta& enty_typ_enu(Poco::Int32 value);

	const Poco::Nullable<std::string>& cta_sql() const;
	EntySelCta& cta_sql(const Poco::Nullable<std::string>& value);

	const Poco::Nullable<std::string>& cta_find_enty() const;
	EntySelCta& cta_find_enty(const Poco::Nullable<std::string>& value);

	const Poco::DateTime& crtd_dtt() const;
	EntySelCta& crtd_dtt(const Poco::DateTime& value);

	const std::string& crtd_usr_cd() const;
	EntySelCta& crtd_usr_cd(const std::string& value);

	const Poco::Nullable<Poco::DateTime>& updt_dtt() const;
	EntySelCta& updt_dtt(const Poco::Nullable<Poco::DateTime>& value);

	const Poco::Nullable<std::string>& updt_usr_cd() const;
	EntySelCta& updt_usr_cd(const Poco::Nullable<std::string>& value);

	const Poco::Nullable<Poco::Int32>& max_entys() const;
	EntySelCta& max_entys(const Poco::Nullable<Poco::Int32>& value);

	static Ptr find(Poco::ActiveRecord::Context::Ptr pContext, const ID& id);

	void insert();
	void update();
	void remove();

	static const std::vector<std::string>& columns();
	static const std::string& table();

private:
	Poco::Int32 _opt_lck = 0;
	Poco::Nullable<std::string> _enty_sel_cta_desc;
	Poco::Nullable<std::string> _div_cd;
	Poco::Nullable<std::string> _str_id_yn;
	Poco::Int32 _enty_typ_enu = 0;
	Poco::Nullable<std::string> _cta_sql;
	Poco::Nullable<std::string> _cta_find_enty;
	Poco::DateTime _crtd_dtt;
	std::string _crtd_usr_cd;
	Poco::Nullable<Poco::DateTime> _updt_dtt;
	Poco::Nullable<std::string> _updt_usr_cd;
	Poco::Nullable<Poco::Int32> _max_entys;

	friend class Poco::Data::TypeHandler<EntySelCta>;
};


inline Poco::Int32 EntySelCta::opt_lck() const
{
	return _opt_lck;
}


inline EntySelCta& EntySelCta::opt_lck(Poco::Int32 value)
{
	_opt_lck = value;
	return *this;
}


inline const Poco::Nullable<std::string>& EntySelCta::enty_sel_cta_desc() const
{
	return _enty_sel_cta_desc;
}


inline EntySelCta& EntySelCta::enty_sel_cta_desc(const Poco::Nullable<std::string>& value)
{
	_enty_sel_cta_desc = value;
	return *this;
}


inline const Poco::Nullable<std::string>& EntySelCta::div_cd() const
{
	return _div_cd;
}


inline EntySelCta& EntySelCta::div_cd(const Poco::Nullable<std::string>& value)
{
	_div_cd = value;
	return *this;
}


inline const Poco::Nullable<std::string>& EntySelCta::str_id_yn() const
{
	return _str_id_yn;
}


inline EntySelCta& EntySelCta::str_id_yn(const Poco::Nullable<std::string>& value)
{
	_str_id_yn = value;
	return *this;
}


inline Poco::Int32 EntySelCta::enty_typ_enu() const
{
	return _enty_typ_enu;
}


inline EntySelCta& EntySelCta::enty_typ_enu(Poco::Int32 value)
{
	_enty_typ_enu = value;
	return *this;
}


inline const Poco::Nullable<std::string>& EntySelCta::cta_sql() const
{
	return _cta_sql;
}


inline EntySelCta& EntySelCta::cta_sql(const Poco::Nullable<std::string>& value)
{
	_cta_sql = value;
	return *this;
}


inline const Poco::Nullable<std::string>& EntySelCta::cta_find_enty() const
{
	return _cta_find_enty;
}


inline EntySelCta& EntySelCta::cta_find_enty(const Poco::Nullable<std::string>& value)
{
	_cta_find_enty = value;
	return *this;
}


inline const Poco::DateTime& EntySelCta::crtd_dtt() const
{
	return _crtd_dtt;
}


inline EntySelCta& EntySelCta::crtd_dtt(const Poco::DateTime& value)
{
	_crtd_dtt = value;
	return *this;
}


inline const std::string& EntySelCta::crtd_usr_cd() const
{
	return _crtd_usr_cd;
}


inline EntySelCta& EntySelCta::crtd_usr_cd(const std::string& value)
{
	_crtd_usr_cd = value;
	return *this;
}


inline const Poco::Nullable<Poco::DateTime>& EntySelCta::updt_dtt() const
{
	return _updt_dtt;
}


inline EntySelCta& EntySelCta::updt_dtt(const Poco::Nullable<Poco::DateTime>& value)
{
	_updt_dtt = value;
	return *this;
}


inline const Poco::Nullable<std::string>& EntySelCta::updt_usr_cd() const
{
	return _updt_usr_cd;
}


inline EntySelCta& EntySelCta::updt_usr_cd(const Poco::Nullable<std::string>& value)
{
	_updt_usr_cd = value;
	return *this;
}


inline const Poco::Nullable<Poco::Int32>& EntySelCta::max_entys() const
{
	return _max_entys;
}


inline EntySelCta& EntySelCta::max_entys(const Poco::Nullable<Poco::Int32>& value)
{
	_max_entys = value;
	return *this;
}


} } // namespace asarum:BY


namespace Poco {
namespace Data {


template <>
class TypeHandler<asarum::BY::EntySelCta>
{
public:
	static std::size_t size()
	{
		return 12;
	}

	static void bind(std::size_t pos, const asarum::BY::EntySelCta& ar, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir)
	{
		TypeHandler<Poco::Int32>::bind(pos++, ar._opt_lck, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._enty_sel_cta_desc, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._div_cd, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._str_id_yn, pBinder, dir);
		TypeHandler<Poco::Int32>::bind(pos++, ar._enty_typ_enu, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._cta_sql, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._cta_find_enty, pBinder, dir);
		TypeHandler<Poco::DateTime>::bind(pos++, ar._crtd_dtt, pBinder, dir);
		TypeHandler<std::string>::bind(pos++, ar._crtd_usr_cd, pBinder, dir);
		TypeHandler<Poco::Nullable<Poco::DateTime>>::bind(pos++, ar._updt_dtt, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._updt_usr_cd, pBinder, dir);
		TypeHandler<Poco::Nullable<Poco::Int32>>::bind(pos++, ar._max_entys, pBinder, dir);
}

	static void extract(std::size_t pos, asarum::BY::EntySelCta& ar, const asarum::BY::EntySelCta& deflt, AbstractExtractor::Ptr pExtr)
	{
		TypeHandler<Poco::Int32>::extract(pos++, ar._opt_lck, deflt._opt_lck, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._enty_sel_cta_desc, deflt._enty_sel_cta_desc, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._div_cd, deflt._div_cd, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._str_id_yn, deflt._str_id_yn, pExtr);
		TypeHandler<Poco::Int32>::extract(pos++, ar._enty_typ_enu, deflt._enty_typ_enu, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._cta_sql, deflt._cta_sql, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._cta_find_enty, deflt._cta_find_enty, pExtr);
		TypeHandler<Poco::DateTime>::extract(pos++, ar._crtd_dtt, deflt._crtd_dtt, pExtr);
		TypeHandler<std::string>::extract(pos++, ar._crtd_usr_cd, deflt._crtd_usr_cd, pExtr);
		TypeHandler<Poco::Nullable<Poco::DateTime>>::extract(pos++, ar._updt_dtt, deflt._updt_dtt, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._updt_usr_cd, deflt._updt_usr_cd, pExtr);
		TypeHandler<Poco::Nullable<Poco::Int32>>::extract(pos++, ar._max_entys, deflt._max_entys, pExtr);
}

	static void prepare(std::size_t pos, const asarum::BY::EntySelCta& ar, AbstractPreparator::Ptr pPrep)
	{
		TypeHandler<Poco::Int32>::prepare(pos++, ar._opt_lck, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._enty_sel_cta_desc, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._div_cd, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._str_id_yn, pPrep);
		TypeHandler<Poco::Int32>::prepare(pos++, ar._enty_typ_enu, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._cta_sql, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._cta_find_enty, pPrep);
		TypeHandler<Poco::DateTime>::prepare(pos++, ar._crtd_dtt, pPrep);
		TypeHandler<std::string>::prepare(pos++, ar._crtd_usr_cd, pPrep);
		TypeHandler<Poco::Nullable<Poco::DateTime>>::prepare(pos++, ar._updt_dtt, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._updt_usr_cd, pPrep);
		TypeHandler<Poco::Nullable<Poco::Int32>>::prepare(pos++, ar._max_entys, pPrep);
	}
};


} } // namespace Poco::Data


#endif // asarum_BY_EntySelCta_INCLUDED
