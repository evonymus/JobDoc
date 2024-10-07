#include "asarum/BY/Meter.h"
#include "asarum/BY/JobDefGetter.h"
#include <boost/algorithm/string/replace.hpp>

using namespace std;
namespace by = asarum::BY;
namespace pd = Poco::Data;

const string HEAD = R"( <?xml version="1.0" encoding="UTF-8"?>
<jmeterTestPlan version="1.2" properties="5.0" jmeter="5.4.1">
  <hashTree>
    <TestPlan guiclass="TestPlanGui" testclass="TestPlan" testname="ESC Queries Test" enabled="true">
      <stringProp name="TestPlan.comments"></stringProp>
      <boolProp name="TestPlan.functional_mode">false</boolProp>
      <boolProp name="TestPlan.serialize_threadgroups">false</boolProp>
      <elementProp name="TestPlan.user_defined_variables" elementType="Arguments" guiclass="ArgumentsPanel" testclass="Arguments" testname="User Defined Variables" enabled="true">
        <collectionProp name="Arguments.arguments"/>
      </elementProp>
      <stringProp name="TestPlan.user_define_classpath">C:\Users\j1013871\Downloads\ojdbc8.jar</stringProp>
    </TestPlan>
    <hashTree>
      <JDBCDataSource guiclass="TestBeanGUI" testclass="JDBCDataSource" testname="MS SQL QA" enabled="true">
        <stringProp name="dataSource">SQL_QA</stringProp>
        <stringProp name="poolMax">0</stringProp>
        <stringProp name="timeout">10000</stringProp>
        <stringProp name="trimInterval">60000</stringProp>
        <boolProp name="autocommit">true</boolProp>
        <stringProp name="transactionIsolation">DEFAULT</stringProp>
        <boolProp name="preinit">false</boolProp>
        <stringProp name="initQuery"></stringProp>
        <boolProp name="keepAlive">true</boolProp>
        <stringProp name="connectionAge">5000</stringProp>
        <stringProp name="checkQuery">select current_timestamp</stringProp>
        <stringProp name="dbUrl">jdbc:sqlserver://tsbd350203001;DatabaseName=tmdb</stringProp>
        <stringProp name="driver">com.microsoft.sqlserver.jdbc.SQLServerDriver</stringProp>
        <stringProp name="username">hu_tmdb</stringProp>
        <stringProp name="password">zwZmncUycYCDsmaU</stringProp>
        <stringProp name="connectionProperties">encrypt=false</stringProp>
      </JDBCDataSource>
      <hashTree/>
      <ThreadGroup guiclass="ThreadGroupGui" testclass="ThreadGroup" testname="ESC Queries" enabled="true">
        <stringProp name="ThreadGroup.on_sample_error">continue</stringProp>
        <elementProp name="ThreadGroup.main_controller" elementType="LoopController" guiclass="LoopControlPanel" testclass="LoopController" testname="Loop Controller" enabled="true">
          <boolProp name="LoopController.continue_forever">false</boolProp>
          <stringProp name="LoopController.loops">1</stringProp>
        </elementProp>
        <stringProp name="ThreadGroup.num_threads">1</stringProp>
        <stringProp name="ThreadGroup.ramp_time">1</stringProp>
        <boolProp name="ThreadGroup.scheduler">false</boolProp>
        <stringProp name="ThreadGroup.duration"></stringProp>
        <stringProp name="ThreadGroup.delay"></stringProp>
        <boolProp name="ThreadGroup.same_user_on_next_iteration">true</boolProp>
      </ThreadGroup>
      <hashTree>
        <JDBCSampler guiclass="TestBeanGUI" testclass="JDBCSampler" testname="Connection Test" enabled="true">
          <stringProp name="dataSource">${connection}</stringProp>
          <stringProp name="queryType">Select Statement</stringProp>
          <stringProp name="query">select current_timestamp</stringProp>
          <stringProp name="queryArguments"></stringProp>
          <stringProp name="queryArgumentsTypes"></stringProp>
          <stringProp name="variableNames"></stringProp>
          <stringProp name="resultVariable"></stringProp>
          <stringProp name="queryTimeout">${timeout}</stringProp>
          <stringProp name="resultSetMaxRows">${rec_count}</stringProp>
          <stringProp name="resultSetHandler">Store as String</stringProp>
        </JDBCSampler> )";

const string TAIL = R"( <hashTree/>
      </hashTree>
      <ResultCollector guiclass="ViewResultsFullVisualizer" testclass="ResultCollector" testname="View Results Tree" enabled="true">
        <boolProp name="ResultCollector.error_logging">false</boolProp>
        <objProp>
          <name>saveConfig</name>
          <value class="SampleSaveConfiguration">
            <time>true</time>
            <latency>true</latency>
            <timestamp>true</timestamp>
            <success>true</success>
            <label>true</label>
            <code>true</code>
            <message>true</message>
            <threadName>true</threadName>
            <dataType>false</dataType>
            <encoding>false</encoding>
            <assertions>true</assertions>
            <subresults>false</subresults>
            <responseData>false</responseData>
            <samplerData>false</samplerData>
            <xml>false</xml>
            <fieldNames>true</fieldNames>
            <responseHeaders>false</responseHeaders>
            <requestHeaders>false</requestHeaders>
            <responseDataOnError>true</responseDataOnError>
            <saveAssertionResultsFailureMessage>true</saveAssertionResultsFailureMessage>
            <assertionsResultsToSave>0</assertionsResultsToSave>
            <bytes>true</bytes>
            <hostname>true</hostname>
            <threadCounts>true</threadCounts>
            <sampleCount>true</sampleCount>
          </value>
        </objProp>
        <stringProp name="filename"></stringProp>
      </ResultCollector>
      <hashTree/>
      <ResultCollector guiclass="TableVisualizer" testclass="ResultCollector" testname="Summary Results in Table" enabled="true">
        <boolProp name="ResultCollector.error_logging">false</boolProp>
        <objProp>
          <name>saveConfig</name>
          <value class="SampleSaveConfiguration">
            <time>true</time>
            <latency>true</latency>
            <timestamp>true</timestamp>
            <success>true</success>
            <label>true</label>
            <code>true</code>
            <message>true</message>
            <threadName>true</threadName>
            <dataType>true</dataType>
            <encoding>false</encoding>
            <assertions>true</assertions>
            <subresults>true</subresults>
            <responseData>false</responseData>
            <samplerData>false</samplerData>
            <xml>false</xml>
            <fieldNames>true</fieldNames>
            <responseHeaders>false</responseHeaders>
            <requestHeaders>false</requestHeaders>
            <responseDataOnError>false</responseDataOnError>
            <saveAssertionResultsFailureMessage>true</saveAssertionResultsFailureMessage>
            <assertionsResultsToSave>0</assertionsResultsToSave>
            <bytes>true</bytes>
            <sentBytes>true</sentBytes>
            <url>true</url>
            <threadCounts>true</threadCounts>
            <idleTime>true</idleTime>
            <connectTime>true</connectTime>
          </value>
        </objProp>
        <stringProp name="filename"></stringProp>
      </ResultCollector>
      <hashTree/>
      <Arguments guiclass="ArgumentsPanel" testclass="Arguments" testname="User Defined Variables" enabled="true">
        <collectionProp name="Arguments.arguments">
          <elementProp name="connection" elementType="Argument">
            <stringProp name="Argument.name">ms_sql</stringProp>
            <stringProp name="Argument.value">SQL_QA</stringProp>
            <stringProp name="Argument.metadata">=</stringProp>
          </elementProp>
          <elementProp name="rec_count" elementType="Argument">
            <stringProp name="Argument.name">rec_count</stringProp>
            <stringProp name="Argument.value">10000</stringProp>
            <stringProp name="Argument.metadata">=</stringProp>
          </elementProp>
          <elementProp name="timeout" elementType="Argument">
            <stringProp name="Argument.name">timeout</stringProp>
            <stringProp name="Argument.value">12000</stringProp>
            <stringProp name="Argument.desc">query timeout in s</stringProp>
            <stringProp name="Argument.metadata">=</stringProp>
          </elementProp>
          <elementProp name="oracle" elementType="Argument">
            <stringProp name="Argument.name">oracle</stringProp>
            <stringProp name="Argument.value">ORCL_GB_QA</stringProp>
            <stringProp name="Argument.metadata">=</stringProp>
          </elementProp>
        </collectionProp>
      </Arguments>
      <hashTree/>
    </hashTree>
  </hashTree>
</jmeterTestPlan>
)";

by::Meter::Meter(shared_ptr<pd::Session> session_ptr)
{
    m_session_ptr = session_ptr;

}

/// <summary>
/// The function generates the content of JMeter JDBC test and sends it to the steam
/// given as the parameter
/// </summary>
/// <param name="out_stream">stream where the JMeter test defintion is to be written</param>
void by::Meter::generateJdbcTestFile(ostream& out_stream) {
    out_stream << getHead();

    by::JobDefGetter jobGetter{ m_session_ptr };
    auto sel_cta = jobGetter.getAllEntySelCtas();
    for (Poco::AutoPtr<by::EntySelCta> i : sel_cta) {
        out_stream << getJDBCSampler(i);
    }
        
    out_stream << getTail();
}

string by::Meter::getHead() {
    return HEAD;
}

string by::Meter::getTail() {
    return TAIL;
}

//-------------------------------------------------------------------

string by::Meter::getJDBCSampler(const Poco::AutoPtr<by::EntySelCta> esc_ptr) {
    stringstream ss{};
    if (esc_ptr->cta_sql().isNull() == false)
    {
        ss << "\n<hashTree/>";
        ss << "\n<JDBCSampler guiclass = \"TestBeanGUI\" testclass=\"JDBCSampler\" testname=\""
           << esc_ptr->id() << "\" enabled=\"true\">";
       
        ss << "\n\t<stringProp name = \"dataSource\">${connection}</stringProp>"
           << "\n\t<stringProp name = \"queryType\">Select Statement</stringProp>"
           << "\n\t<stringProp name=\"query\">";

        string sql{ esc_ptr->cta_sql() };
        
       // the result is written as xml so som characters need to be replaced 
        boost::replace_all(sql, ">", "&gt;");
        boost::replace_all(sql, "<", "&lt;");
        boost::replace_all(sql, "'", "&apos;");

        ss << '\n' << sql << "\n</stringProp>"
            << "\n\t<stringProp name=\"queryArguments\"></stringProp>"
            << "\n\t<stringProp name=\"queryArgumentsTypes\"></stringProp>"
            << "\n\t<stringProp name=\"variableNames\"></stringProp>"
            << "\n\t<stringProp name=\"resultVariable\"></stringProp>"
            << "\n\t<stringProp name=\"queryTimeout\">${timeout}</stringProp>"
            << "\n\t<stringProp name=\"resultSetMaxRows\">${rec_count}</stringProp>"
            << "\n\t<stringProp name=\"resultSetHandler\">Store as String</stringProp>"
            << "\n</JDBCSampler>";
    }
    return ss.str();
}