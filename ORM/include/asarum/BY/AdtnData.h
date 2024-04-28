//
// AdtnData.h
//
// This file has been generated from jobdoc.xml. Do not edit.
//


#ifndef asarum_BY_AdtnData_INCLUDED
#define asarum_BY_AdtnData_INCLUDED


#include "Poco/ActiveRecord/ActiveRecord.h"


namespace asarum {
namespace BY {


class AdtnData: public Poco::ActiveRecord::ActiveRecord<Poco::Int32>
{
public:
	using Ptr = Poco::AutoPtr<AdtnData>;

	explicit AdtnData(ID id);
	AdtnData() = default;
	AdtnData(const AdtnData& other);
	~AdtnData() = default;

	const std::string& data() const;
	AdtnData& data(const std::string& value);

	const Poco::DateTime& crdt_dtt() const;
	AdtnData& crdt_dtt(const Poco::DateTime& value);

	const Poco::Nullable<std::string>& adtn_data_cd() const;
	AdtnData& adtn_data_cd(const Poco::Nullable<std::string>& value);

	const Poco::Nullable<Poco::Int16>& adtn_data_enu() const;
	AdtnData& adtn_data_enu(const Poco::Nullable<Poco::Int16>& value);

	const Poco::Nullable<char>& actv_yn() const;
	AdtnData& actv_yn(const Poco::Nullable<char>& value);

	const Poco::Nullable<std::string>& crtd_usr_cd() const;
	AdtnData& crtd_usr_cd(const Poco::Nullable<std::string>& value);

	const Poco::Nullable<std::string>& updt_usr_cd() const;
	AdtnData& updt_usr_cd(const Poco::Nullable<std::string>& value);

	const Poco::Nullable<Poco::DateTime>& updt_dtt() const;
	AdtnData& updt_dtt(const Poco::Nullable<Poco::DateTime>& value);

	const Poco::Nullable<Poco::Int16>& tplt_fmt_typ_enu() const;
	AdtnData& tplt_fmt_typ_enu(const Poco::Nullable<Poco::Int16>& value);

	static Ptr find(Poco::ActiveRecord::Context::Ptr pContext, const ID& id);

	void insert();
	void update();
	void remove();

	static const std::vector<std::string>& columns();
	static const std::string& table();

private:
	std::string _data;
	Poco::DateTime _crdt_dtt;
	Poco::Nullable<std::string> _adtn_data_cd;
	Poco::Nullable<Poco::Int16> _adtn_data_enu;
	Poco::Nullable<char> _actv_yn;
	Poco::Nullable<std::string> _crtd_usr_cd;
	Poco::Nullable<std::string> _updt_usr_cd;
	Poco::Nullable<Poco::DateTime> _updt_dtt;
	Poco::Nullable<Poco::Int16> _tplt_fmt_typ_enu;

	friend class Poco::Data::TypeHandler<AdtnData>;
};


inline const std::string& AdtnData::data() const
{
	return _data;
}


inline AdtnData& AdtnData::data(const std::string& value)
{
	_data = value;
	return *this;
}


inline const Poco::DateTime& AdtnData::crdt_dtt() const
{
	return _crdt_dtt;
}


inline AdtnData& AdtnData::crdt_dtt(const Poco::DateTime& value)
{
	_crdt_dtt = value;
	return *this;
}


inline const Poco::Nullable<std::string>& AdtnData::adtn_data_cd() const
{
	return _adtn_data_cd;
}


inline AdtnData& AdtnData::adtn_data_cd(const Poco::Nullable<std::string>& value)
{
	_adtn_data_cd = value;
	return *this;
}


inline const Poco::Nullable<Poco::Int16>& AdtnData::adtn_data_enu() const
{
	return _adtn_data_enu;
}


inline AdtnData& AdtnData::adtn_data_enu(const Poco::Nullable<Poco::Int16>& value)
{
	_adtn_data_enu = value;
	return *this;
}


inline const Poco::Nullable<char>& AdtnData::actv_yn() const
{
	return _actv_yn;
}


inline AdtnData& AdtnData::actv_yn(const Poco::Nullable<char>& value)
{
	_actv_yn = value;
	return *this;
}


inline const Poco::Nullable<std::string>& AdtnData::crtd_usr_cd() const
{
	return _crtd_usr_cd;
}


inline AdtnData& AdtnData::crtd_usr_cd(const Poco::Nullable<std::string>& value)
{
	_crtd_usr_cd = value;
	return *this;
}


inline const Poco::Nullable<std::string>& AdtnData::updt_usr_cd() const
{
	return _updt_usr_cd;
}


inline AdtnData& AdtnData::updt_usr_cd(const Poco::Nullable<std::string>& value)
{
	_updt_usr_cd = value;
	return *this;
}


inline const Poco::Nullable<Poco::DateTime>& AdtnData::updt_dtt() const
{
	return _updt_dtt;
}


inline AdtnData& AdtnData::updt_dtt(const Poco::Nullable<Poco::DateTime>& value)
{
	_updt_dtt = value;
	return *this;
}


inline const Poco::Nullable<Poco::Int16>& AdtnData::tplt_fmt_typ_enu() const
{
	return _tplt_fmt_typ_enu;
}


inline AdtnData& AdtnData::tplt_fmt_typ_enu(const Poco::Nullable<Poco::Int16>& value)
{
	_tplt_fmt_typ_enu = value;
	return *this;
}


} } // namespace asarum:BY


namespace Poco {
namespace Data {


template <>
class TypeHandler<asarum::BY::AdtnData>
{
public:
	static std::size_t size()
	{
		return 9;
	}

	static void bind(std::size_t pos, const asarum::BY::AdtnData& ar, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir)
	{
		TypeHandler<std::string>::bind(pos++, ar._data, pBinder, dir);
		TypeHandler<Poco::DateTime>::bind(pos++, ar._crdt_dtt, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._adtn_data_cd, pBinder, dir);
		TypeHandler<Poco::Nullable<Poco::Int16>>::bind(pos++, ar._adtn_data_enu, pBinder, dir);
		TypeHandler<Poco::Nullable<char>>::bind(pos++, ar._actv_yn, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._crtd_usr_cd, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._updt_usr_cd, pBinder, dir);
		TypeHandler<Poco::Nullable<Poco::DateTime>>::bind(pos++, ar._updt_dtt, pBinder, dir);
		TypeHandler<Poco::Nullable<Poco::Int16>>::bind(pos++, ar._tplt_fmt_typ_enu, pBinder, dir);
}

	static void extract(std::size_t pos, asarum::BY::AdtnData& ar, const asarum::BY::AdtnData& deflt, AbstractExtractor::Ptr pExtr)
	{
		TypeHandler<std::string>::extract(pos++, ar._data, deflt._data, pExtr);
		TypeHandler<Poco::DateTime>::extract(pos++, ar._crdt_dtt, deflt._crdt_dtt, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._adtn_data_cd, deflt._adtn_data_cd, pExtr);
		TypeHandler<Poco::Nullable<Poco::Int16>>::extract(pos++, ar._adtn_data_enu, deflt._adtn_data_enu, pExtr);
		TypeHandler<Poco::Nullable<char>>::extract(pos++, ar._actv_yn, deflt._actv_yn, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._crtd_usr_cd, deflt._crtd_usr_cd, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._updt_usr_cd, deflt._updt_usr_cd, pExtr);
		TypeHandler<Poco::Nullable<Poco::DateTime>>::extract(pos++, ar._updt_dtt, deflt._updt_dtt, pExtr);
		TypeHandler<Poco::Nullable<Poco::Int16>>::extract(pos++, ar._tplt_fmt_typ_enu, deflt._tplt_fmt_typ_enu, pExtr);
}

	static void prepare(std::size_t pos, const asarum::BY::AdtnData& ar, AbstractPreparator::Ptr pPrep)
	{
		TypeHandler<std::string>::prepare(pos++, ar._data, pPrep);
		TypeHandler<Poco::DateTime>::prepare(pos++, ar._crdt_dtt, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._adtn_data_cd, pPrep);
		TypeHandler<Poco::Nullable<Poco::Int16>>::prepare(pos++, ar._adtn_data_enu, pPrep);
		TypeHandler<Poco::Nullable<char>>::prepare(pos++, ar._actv_yn, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._crtd_usr_cd, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._updt_usr_cd, pPrep);
		TypeHandler<Poco::Nullable<Poco::DateTime>>::prepare(pos++, ar._updt_dtt, pPrep);
		TypeHandler<Poco::Nullable<Poco::Int16>>::prepare(pos++, ar._tplt_fmt_typ_enu, pPrep);
	}
};


} } // namespace Poco::Data


#endif // asarum_BY_AdtnData_INCLUDED
