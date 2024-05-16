#pragma once


constexpr char* JOB_DEFN_T_CREATE = R"SQL(
CREATE TABLE 'JOB_DEFN_T' ('JOB_CD' TEXT primary key,'OPT_LCK' NUMERIC
,'JOB_DESC' TEXT,'SCHD_TYP_ENU' NUMERIC,'JOB_TYP_ENU' NUMERIC,
'DIV_CD' TEXT,'PARM_1' TEXT,'PARM_2' TEXT,'PARM_3' TEXT,
'PARM_4' TEXT,'PARM_5' TEXT,'CRTD_DTT' TEXT,'CRTD_USR_CD' TEXT,
'UPDT_DTT' TEXT,'UPDT_USR_CD' TEXT,'TPLT_FILE' TEXT,
'OUTPT_FILE' TEXT,'SCHD_DETL_ID' NUMERIC,'PRTY' NUMERIC,
'ACTV_YN' TEXT,'NEXT_JOB_CD_SUCCESS' TEXT,'NEXT_JOB_CD_FAILURE' TEXT,
'ALRT_GRP_CD_SUCCESS' TEXT,'ALRT_GRP_CD_FAILURE' TEXT,
'GEN_ENTY_OUTPUT_YN' TEXT,'TPLT_ID' NUMERIC);                          
)SQL";

//**************************************************************
constexpr char* ENTY_SEL_CTA_T_CREATE = R"SQL(
CREATE TABLE 'ENTY_SEL_CTA_T' ('ENTY_SEL_CTA_CD' TEXT primary key,'OPT_LCK' NUMERIC
,'ENTY_SEL_CTA_DESC' TEXT,'DIV_CD' TEXT,'STR_ID_YN' TEXT,
'ENTY_TYP_ENU' NUMERIC,'CTA_SQL' TEXT,'CTA_FIND_ENTY' TEXT,
'CRTD_DTT' TEXT,'CRTD_USR_CD' TEXT,'UPDT_DTT' TEXT,'UPDT_USR_CD' TEXT,'MAX_ENTYS' NUMERIC);
)SQL";

//**************************************************************

constexpr char* JOB_SEL_CTA_T_CREATE = R"SQL(
CREATE TABLE 'JOB_SEL_CTA_T' ('JOB_SEL_CTA_ID' NUMERIC,'OPT_LCK' NUMERIC,
'JOB_CD' TEXT,'ENTY_SEL_CTA_CD' TEXT);          
)SQL";

//**************************************************************
constexpr char* SCHD_DETL_T_CREATE = R"SQL(
CREATE TABLE 'SCHD_DETL_T' ('SCHD_DETL_ID' NUMERIC primary key,'OPT_LCK' NUMERIC,
'RCURNCE_TYP_ENU' NUMERIC,'EFCT_DT' TEXT,'EXPD_DT' TEXT
,'STRT_TM' TEXT,'END_TM' TEXT,'DAY_OF_MTH' NUMERIC,
'ITVL' NUMERIC,'FXD_ITVL_SRC_ENU' NUMERIC,'BUS_DAYS_CD' TEXT,'BUS_MTHS_CD' TEXT);
)SQL";

constexpr char* ADTN_DATA_T_CREATE = R"SQL(
CREATE TABLE 'ADTN_DATA_T' ('ADTN_DATA_ID' NUMERIC primary key,'DATA' TEXT,'CRTD_DTT' TEXT,'ADTN_DATA_CD' TEXT,'ADTN_DATA_TYP_ENU' NUMERIC,'ACTV_YN' TEXT,'CRTD_USR_CD' TEXT,'UPDT_USR_CD' TEXT,'UPDT_DTT' TEXT,'TPLT_FMT_TYP_ENU' NUMERIC);
)SQL";

//**************************************************************
constexpr char *JOB_DEFS_QRY = R"SQL(
with RECURSIVE jobs(
  master,level , job_cd, child, sub_jobs 
  , ESC, TEMPL , sql, xml, subst 
  , tpl_file, job_desc , api, job_typ
) 
as (
select jdef.job_cd as master
, 1 as level 
, jdef.job_cd as job_cd
, jdef.next_job_cd_success as child
-- if Chain JOB then specify sub_jobs
, case jdef.job_typ_enu 
    when 3 then jdef.parm_1 
    else null 
  end as sub_jobs
, jc.enty_sel_cta_cd as ESC
, ad.adtn_data_cd as TEMPL
, case when esc.cta_sql is null then '' else esc.cta_sql end as sql
, case when ad.data is null then '' else ad.data end as xml
, case jdef.job_typ_enu
    when 2 then jdef.parm_3
    else ''
end as subst
, jdef.tplt_file
, jdef.job_desc
, case jdef.job_typ_enu
    when 2 then jdef.parm_1
    else ''
  end as api
, case jdef.job_typ_enu
    when 1 then 'RRS'
    when 2 then 'API'
    when 3 then 'Chain'
    when 4 then 'Decision'
    when 6 then 'MMSI'
    when 7 then 'Trans Voyant Ocean'
    when 8 then 'Intra Ocean Schedule'
    when 17 then 'Intra Send'
    when 18 then 'Intra Receive'
    when 19 then 'Directory Watch'
    when 20 then 'Transp.Order Consol.'
    when 22 then 'Dispatch'
    when 23 then 'Tracking'
    when 25 then 'Reoptymalization'
    when 26 then 'Notification'
    else 'Other'
  end as job_typ

from job_defn_t jdef
left join job_sel_cta_t jc on jc.job_cd = jdef.job_cd
left join  enty_sel_cta_t esc on esc.enty_sel_cta_cd = jc.enty_sel_cta_cd
left join adtn_data_t ad on ad.adtn_data_id = jdef.tplt_id
where schd_detl_id is not null 

union 

select jb.master
, jb.level + 1
,  aa.job_cd
, aa.next_job_cd_success
, case aa.job_typ_enu 
    when 3 then aa.parm_1 
    else null 
  end as sub_jobs
, jc.enty_sel_cta_cd as ESC
, ad.adtn_data_cd as TEMPL
, case when esc.cta_sql is null then '' else esc.cta_sql end as sql
, case when ad.data is null then '' else ad.data end as xml
, case aa.job_typ_enu
    when 2 then aa.parm_3
    else ''
end as subst
, aa.tplt_file
, aa.job_desc
, case aa.job_typ_enu
    when 2 then aa.parm_1
    else ''
  end as api
, case aa.job_typ_enu
    when 1 then 'RRS'
    when 2 then 'API'
    when 3 then 'Chain'
    when 4 then 'Decision'
    when 6 then 'MMSI'
    when 7 then 'Trans Voyant Ocean'
    when 8 then 'Intra Ocean Schedule'
    when 17 then 'Intra Send'
    when 18 then 'Intra Receive'
    when 19 then 'Directory Watch'
    when 20 then 'Transp.Order Consol.'
    when 22 then 'Dispatch'
    when 23 then 'Tracking'
    when 25 then 'Reoptymalization'
    when 26 then 'Notification'
    else 'Other'
  end as job_typ

from job_defn_t aa 
inner join jobs jb on aa.job_cd = jb.child
left join job_sel_cta_t jc on jc.job_cd = aa.job_cd
left join  enty_sel_cta_t esc on esc.enty_sel_cta_cd = jc.enty_sel_cta_cd
left join adtn_data_t ad on ad.adtn_data_id = aa.tplt_id
)
select * from jobs order by master, level;
  )SQL";
