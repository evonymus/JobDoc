//
// SchdDetl.h
//
// This file has been generated from jobdoc.xml. Do not edit.
//


#ifndef asarum_BY_SchdDetl_INCLUDED
#define asarum_BY_SchdDetl_INCLUDED


#include "Poco/ActiveRecord/ActiveRecord.h"


namespace asarum {
namespace BY {


class SchdDetl: public Poco::ActiveRecord::ActiveRecord<Poco::Int32>
{
public:
	using Ptr = Poco::AutoPtr<SchdDetl>;

	explicit SchdDetl(ID id);
	SchdDetl() = default;
	SchdDetl(const SchdDetl& other);
	~SchdDetl() = default;

	Poco::Int32 opt_lck() const;
	SchdDetl& opt_lck(Poco::Int32 value);

	Poco::Int32 rcurnce_typ_enu() const;
	SchdDetl& rcurnce_typ_enu(Poco::Int32 value);

	const Poco::Nullable<Poco::Data::Date>& efct_dt() const;
	SchdDetl& efct_dt(const Poco::Nullable<Poco::Data::Date>& value);

	const Poco::Nullable<Poco::Data::Date>& expd_dt() const;
	SchdDetl& expd_dt(const Poco::Nullable<Poco::Data::Date>& value);

	const Poco::Nullable<Poco::Data::Date>& strt_tm() const;
	SchdDetl& strt_tm(const Poco::Nullable<Poco::Data::Date>& value);

	const Poco::Nullable<Poco::Data::Date>& end_tm() const;
	SchdDetl& end_tm(const Poco::Nullable<Poco::Data::Date>& value);

	const Poco::Nullable<Poco::Int32>& day_of_mth() const;
	SchdDetl& day_of_mth(const Poco::Nullable<Poco::Int32>& value);

	Poco::Int32 itvl() const;
	SchdDetl& itvl(Poco::Int32 value);

	Poco::Int32 fxd_itvl_src_enu() const;
	SchdDetl& fxd_itvl_src_enu(Poco::Int32 value);

	const Poco::Nullable<std::string>& bus_days_cd() const;
	SchdDetl& bus_days_cd(const Poco::Nullable<std::string>& value);

	const Poco::Nullable<std::string>& bus_mths_cd() const;
	SchdDetl& bus_mths_cd(const Poco::Nullable<std::string>& value);

	static Ptr find(Poco::ActiveRecord::Context::Ptr pContext, const ID& id);

	void insert();
	void update();
	void remove();

	static const std::vector<std::string>& columns();
	static const std::string& table();

private:
	Poco::Int32 _opt_lck = 0;
	Poco::Int32 _rcurnce_typ_enu = 0;
	Poco::Nullable<Poco::Data::Date> _efct_dt;
	Poco::Nullable<Poco::Data::Date> _expd_dt;
	Poco::Nullable<Poco::Data::Date> _strt_tm;
	Poco::Nullable<Poco::Data::Date> _end_tm;
	Poco::Nullable<Poco::Int32> _day_of_mth;
	Poco::Int32 _itvl = 0;
	Poco::Int32 _fxd_itvl_src_enu = 0;
	Poco::Nullable<std::string> _bus_days_cd;
	Poco::Nullable<std::string> _bus_mths_cd;

	friend class Poco::Data::TypeHandler<SchdDetl>;
};


inline Poco::Int32 SchdDetl::opt_lck() const
{
	return _opt_lck;
}


inline SchdDetl& SchdDetl::opt_lck(Poco::Int32 value)
{
	_opt_lck = value;
	return *this;
}


inline Poco::Int32 SchdDetl::rcurnce_typ_enu() const
{
	return _rcurnce_typ_enu;
}


inline SchdDetl& SchdDetl::rcurnce_typ_enu(Poco::Int32 value)
{
	_rcurnce_typ_enu = value;
	return *this;
}


inline const Poco::Nullable<Poco::Data::Date>& SchdDetl::efct_dt() const
{
	return _efct_dt;
}


inline SchdDetl& SchdDetl::efct_dt(const Poco::Nullable<Poco::Data::Date>& value)
{
	_efct_dt = value;
	return *this;
}


inline const Poco::Nullable<Poco::Data::Date>& SchdDetl::expd_dt() const
{
	return _expd_dt;
}


inline SchdDetl& SchdDetl::expd_dt(const Poco::Nullable<Poco::Data::Date>& value)
{
	_expd_dt = value;
	return *this;
}


inline const Poco::Nullable<Poco::Data::Date>& SchdDetl::strt_tm() const
{
	return _strt_tm;
}


inline SchdDetl& SchdDetl::strt_tm(const Poco::Nullable<Poco::Data::Date>& value)
{
	_strt_tm = value;
	return *this;
}


inline const Poco::Nullable<Poco::Data::Date>& SchdDetl::end_tm() const
{
	return _end_tm;
}


inline SchdDetl& SchdDetl::end_tm(const Poco::Nullable<Poco::Data::Date>& value)
{
	_end_tm = value;
	return *this;
}


inline const Poco::Nullable<Poco::Int32>& SchdDetl::day_of_mth() const
{
	return _day_of_mth;
}


inline SchdDetl& SchdDetl::day_of_mth(const Poco::Nullable<Poco::Int32>& value)
{
	_day_of_mth = value;
	return *this;
}


inline Poco::Int32 SchdDetl::itvl() const
{
	return _itvl;
}


inline SchdDetl& SchdDetl::itvl(Poco::Int32 value)
{
	_itvl = value;
	return *this;
}


inline Poco::Int32 SchdDetl::fxd_itvl_src_enu() const
{
	return _fxd_itvl_src_enu;
}


inline SchdDetl& SchdDetl::fxd_itvl_src_enu(Poco::Int32 value)
{
	_fxd_itvl_src_enu = value;
	return *this;
}


inline const Poco::Nullable<std::string>& SchdDetl::bus_days_cd() const
{
	return _bus_days_cd;
}


inline SchdDetl& SchdDetl::bus_days_cd(const Poco::Nullable<std::string>& value)
{
	_bus_days_cd = value;
	return *this;
}


inline const Poco::Nullable<std::string>& SchdDetl::bus_mths_cd() const
{
	return _bus_mths_cd;
}


inline SchdDetl& SchdDetl::bus_mths_cd(const Poco::Nullable<std::string>& value)
{
	_bus_mths_cd = value;
	return *this;
}


} } // namespace asarum:BY


namespace Poco {
namespace Data {


template <>
class TypeHandler<asarum::BY::SchdDetl>
{
public:
	static std::size_t size()
	{
		return 11;
	}

	static void bind(std::size_t pos, const asarum::BY::SchdDetl& ar, AbstractBinder::Ptr pBinder, AbstractBinder::Direction dir)
	{
		TypeHandler<Poco::Int32>::bind(pos++, ar._opt_lck, pBinder, dir);
		TypeHandler<Poco::Int32>::bind(pos++, ar._rcurnce_typ_enu, pBinder, dir);
		TypeHandler<Poco::Nullable<Poco::Data::Date>>::bind(pos++, ar._efct_dt, pBinder, dir);
		TypeHandler<Poco::Nullable<Poco::Data::Date>>::bind(pos++, ar._expd_dt, pBinder, dir);
		TypeHandler<Poco::Nullable<Poco::Data::Date>>::bind(pos++, ar._strt_tm, pBinder, dir);
		TypeHandler<Poco::Nullable<Poco::Data::Date>>::bind(pos++, ar._end_tm, pBinder, dir);
		TypeHandler<Poco::Nullable<Poco::Int32>>::bind(pos++, ar._day_of_mth, pBinder, dir);
		TypeHandler<Poco::Int32>::bind(pos++, ar._itvl, pBinder, dir);
		TypeHandler<Poco::Int32>::bind(pos++, ar._fxd_itvl_src_enu, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._bus_days_cd, pBinder, dir);
		TypeHandler<Poco::Nullable<std::string>>::bind(pos++, ar._bus_mths_cd, pBinder, dir);
}

	static void extract(std::size_t pos, asarum::BY::SchdDetl& ar, const asarum::BY::SchdDetl& deflt, AbstractExtractor::Ptr pExtr)
	{
		TypeHandler<Poco::Int32>::extract(pos++, ar._opt_lck, deflt._opt_lck, pExtr);
		TypeHandler<Poco::Int32>::extract(pos++, ar._rcurnce_typ_enu, deflt._rcurnce_typ_enu, pExtr);
		TypeHandler<Poco::Nullable<Poco::Data::Date>>::extract(pos++, ar._efct_dt, deflt._efct_dt, pExtr);
		TypeHandler<Poco::Nullable<Poco::Data::Date>>::extract(pos++, ar._expd_dt, deflt._expd_dt, pExtr);
		TypeHandler<Poco::Nullable<Poco::Data::Date>>::extract(pos++, ar._strt_tm, deflt._strt_tm, pExtr);
		TypeHandler<Poco::Nullable<Poco::Data::Date>>::extract(pos++, ar._end_tm, deflt._end_tm, pExtr);
		TypeHandler<Poco::Nullable<Poco::Int32>>::extract(pos++, ar._day_of_mth, deflt._day_of_mth, pExtr);
		TypeHandler<Poco::Int32>::extract(pos++, ar._itvl, deflt._itvl, pExtr);
		TypeHandler<Poco::Int32>::extract(pos++, ar._fxd_itvl_src_enu, deflt._fxd_itvl_src_enu, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._bus_days_cd, deflt._bus_days_cd, pExtr);
		TypeHandler<Poco::Nullable<std::string>>::extract(pos++, ar._bus_mths_cd, deflt._bus_mths_cd, pExtr);
}

	static void prepare(std::size_t pos, const asarum::BY::SchdDetl& ar, AbstractPreparator::Ptr pPrep)
	{
		TypeHandler<Poco::Int32>::prepare(pos++, ar._opt_lck, pPrep);
		TypeHandler<Poco::Int32>::prepare(pos++, ar._rcurnce_typ_enu, pPrep);
		TypeHandler<Poco::Nullable<Poco::Data::Date>>::prepare(pos++, ar._efct_dt, pPrep);
		TypeHandler<Poco::Nullable<Poco::Data::Date>>::prepare(pos++, ar._expd_dt, pPrep);
		TypeHandler<Poco::Nullable<Poco::Data::Date>>::prepare(pos++, ar._strt_tm, pPrep);
		TypeHandler<Poco::Nullable<Poco::Data::Date>>::prepare(pos++, ar._end_tm, pPrep);
		TypeHandler<Poco::Nullable<Poco::Int32>>::prepare(pos++, ar._day_of_mth, pPrep);
		TypeHandler<Poco::Int32>::prepare(pos++, ar._itvl, pPrep);
		TypeHandler<Poco::Int32>::prepare(pos++, ar._fxd_itvl_src_enu, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._bus_days_cd, pPrep);
		TypeHandler<Poco::Nullable<std::string>>::prepare(pos++, ar._bus_mths_cd, pPrep);
	}
};


} } // namespace Poco::Data


#endif // asarum_BY_SchdDetl_INCLUDED
