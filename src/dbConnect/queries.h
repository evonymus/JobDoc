#ifndef __QUERIES__
#define __QUERIES__ 
#include <string>
#include <iostream>
namespace asarum {
namespace db {
const char* JOB_DEFS = R""""(select sd.job_cd as master,  LEVEL, jb.job_cd, jb.next_job_cd_success
, case jb.job_typ_enu
    when 3 -- chain
    then jb.parm_1
    else ''
end as sub_jobs
, jc.enty_sel_cta_cd as ESC
, ad.adtn_data_cd as TEMPL
, nvl(esc.cta_sql, ' ') as sql
, nvl(ad.data, ' ') as xml
, case jb.job_typ_enu
    when 2 then jb.parm_3
    else ''
end as subst
, jb.tplt_file
, jb.job_desc
, case jb.job_typ_enu
    when 2 then jb.parm_1
    else ''
  end as api
, case jb.job_typ_enu
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
from job_defn_t jb
left join job_defn_t sd on jb.job_cd = sd.job_cd and jb.schd_typ_enu = 2
left join adtn_data_t ad on ad.adtn_data_id = jb.tplt_id
left join job_sel_cta_t jc on jc.job_cd = jb.job_cd
left join  enty_sel_cta_t esc on esc.enty_sel_cta_cd = jc.enty_sel_cta_cd
left join adtn_data_t ad on ad.adtn_data_id = jb.tplt_id
connect by   prior jb.next_job_cd_success = jb.job_cd
start with jb.job_cd = sd.job_cd
-- ver.2.1
-- Marek Dziekanski 2023-04-11 14:54
)"""";
}
}
#endif /* ifndef __QUERIES__ */
