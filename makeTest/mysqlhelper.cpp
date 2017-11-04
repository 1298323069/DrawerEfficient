//-----------------
//mysqlhelper.cpp
#include "mysqlhelper.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <cstring>
#include <cppconn/exception.h>
using namespace std;

namespace mysqlhelper{

    MysqlHelper::MysqlHelper(const string& sHost, const string& sUser, const string& sPassword, const string& sDatabase,const string& scharSet, int port, int iFlag):_bConnected(false)
    {

        init(sHost, sUser, sPassword, sDatabase, scharSet, port, iFlag);

        _pstMql = mysql_init(NULL);

    }

    MysqlHelper::MysqlHelper(const DBConf& tcDBConf):_bConnected(false)
    {
        _dbConf = tcDBConf;


        _pstMql = mysql_init(NULL);

    }

    MysqlHelper:: ~MysqlHelper()
    {
        if (_pstMql != NULL)
        {
            mysql_close(_pstMql);
            _pstMql = NULL;
        }
    }

    void MysqlHelper::init(const string& sHost, const string& sUser, const string& sPassword, const string& sDatabase,const string& scharSet, int port, int iFlag)
    {
        _dbConf._host = sHost;
        _dbConf._user = sUser;
        _dbConf._passsword = sPassword;
        _dbConf._database = sDatabase;
        _dbConf._characters = "utf8";
        _dbConf._port = 3306;
        _dbConf._flag = CLIENT_MULTI_STATEMENTS;

        
    }

     void MysqlHelper::connect()
    {

        disConnect();

         if (_dbConf._characters.empty())
        {
           cout << "start mysql_option " << endl;

           unsigned int time = 10000;
           unsigned int * a =  &time;

            if (mysql_options(_pstMql, MYSQL_SET_CHARSET_NAME,_dbConf._characters.c_str() ) && mysql_options(_pstMql, MYSQL_OPT_WRITE_TIMEOUT,a )) {
             cout << "options  has error " << endl;
            throw(MysqlHelper_Exception(string("MysqlHelper::connect: mysql_options MYSQL_SET_CHARSET_NAME") + _dbConf._characters + ":" + string(mysql_error(_pstMql))));
                  
            }
            
        }
      if (mysql_real_connect(_pstMql, _dbConf._host.c_str(), _dbConf._user.c_str(), _dbConf._passsword.c_str(), _dbConf._database.c_str(), _dbConf._port, NULL, _dbConf._flag))
      {
        _bConnected = true;

        cout << "connect success " << endl;
          
      } else
      {
        if (mysql_errno(_pstMql))  
        {  
            fprintf(stderr, "Connection error %d: %s/n", mysql_errno(_pstMql),  
            mysql_error(_pstMql));  
        } 
      }       
                  
    }



    void MysqlHelper::init(const DBConf& tcDBConf)
    {
        _dbConf = tcDBConf;
    }
    
    void MysqlHelper::disConnect()
    {
        if(_pstMql != NULL )
        {
            cout << "disConnect musql " << endl;

            mysql_close(_pstMql);

            _pstMql = mysql_init(NULL);
        }
        
        _bConnected = false;
        
    }
   
    string MysqlHelper::escapeString(const string& sFrom)
    {
        if(!_bConnected){
            
            connect();
        }
        
        string sTo;
        string::size_type  iLen = sFrom.length() * 2 + 1;
        char *pTo = (char *)malloc(iLen);
        memset(pTo, 0x00, iLen);
        mysql_real_escape_string(_pstMql, pTo, sFrom.c_str(),sFrom.length());
        sTo = pTo;
        free(pTo);
        return sTo;
    }
                  
    MYSQL *MysqlHelper::getMysql()
    {
        return _pstMql;
    }
                  
    string MysqlHelper::buildInsertSQL(const string& sTableName, const RECORD_DATA &mapColumns)
    {
    
        ostringstream sColumnNames;
        ostringstream sColumnValues;
        
        map<string, pair<FT, string> >::const_iterator itEnd = mapColumns.end();
        
        for(map<string, pair<FT, string> >::const_iterator it = mapColumns.begin(); it != itEnd; ++it)
        {
            if(it == mapColumns.begin())
            {
               sColumnNames << it->first;
                
                if( it->second.first == DB_INT)
                {
                    sColumnValues << it->second.second;
                    
                } else
                {
                    sColumnValues << "'" << escapeString(it->second.second) << ",";
                }
                
            } else
            {
                sColumnNames << "," << it->first;
                
                if(it->second.first == DB_INT)
                {
                    sColumnValues << ","  + it->second.second;
                    
                } else
                {
                    sColumnValues << ",'" + escapeString(it->second.second) << "'";
                }
            }
        }
        
        ostringstream os;
        
        os << "insert into " << sTableName << "(" << sColumnNames.str() << ") values (" << sColumnValues.str() << ")";
        
        return os.str();
        
    }


    string MysqlHelper::buildReplaceSQL(const string& sTableName, const RECORD_DATA &mapColumns)
    {
        ostringstream sColumnNames;
        ostringstream sColumnValues;

        map<string,pair<FT, string> >::const_iterator itEnd = mapColumns.end();

        for (map<string, pair<FT, string> >:: const_iterator it = mapColumns.begin(); it != itEnd; ++it)
        {
            if (it == mapColumns.begin()) 
            {
                sColumnNames << "`" << it->first << "`";
                if (it->second.first == DB_INT)
                {
                    sColumnValues << it->second.second;

                } else
                {
                    sColumnValues << "'" << escapeString(it->second.second) << "'";
                }
            } else
            {
                sColumnNames << ",`" << it->first << "`";
                if (it->second.first == DB_INT)
                {
                    sColumnValues << "," + it->second.second;

                } else
                {
                    sColumnValues << ",'" << escapeString(it->second.second) << "'";
                }
            }

        }

        ostringstream os;
        os << "replace into " << sTableName << " (" << sColumnNames.str() << ") values (" << sColumnValues.str() << ")";
        return os.str();
    }

    string MysqlHelper::buidUpdateSQL(const string& sTableName, const RECORD_DATA &mapColumns, const string& sCondition)
    {
        ostringstream sColumnNameValueSet;

        map<string, pair<FT, string> >::const_iterator itEnd = mapColumns.end();

        for (map<string, pair<FT, string> >::const_iterator it = mapColumns.begin(); it != itEnd; ++it)
        {
            if (it == mapColumns.begin())
            {
                sColumnNameValueSet << "`" << it->first << "`";

            } else
            {
                sColumnNameValueSet << ",`" << it->first << "`";
            }

            if (it->second.first == DB_INT)
            {
                sColumnNameValueSet << "= " << it ->second.second;
            } else
            {
                sColumnNameValueSet << "= '" << escapeString(it->second.second) << "'";
            }
        }

        ostringstream os;

        os << "update " << sTableName << " set " << sColumnNameValueSet.str() << " " << sCondition;

        return os.str();
    }
    
    string MysqlHelper::getVariables(const string& sName)
    {
        string sql = "SHOW VARIABLES LIKE '" + sName + "'";

        MysqlData data = queryRecord(sql);
        if (data.size() == 0)
        {
            return "";
        }

        if (sName == data[0]["Variable_name"])
        {
            return data[0]["Value"];
        }
        return "";
    }

    void MysqlHelper::execute(const string& sSql)
    {
        cout << sSql << endl;

        if (!_bConnected)
        {

            cout << "connect again" << endl;

            connect();
        }

        _sLastSql = sSql;

        int iRet = mysql_real_query(_pstMql, sSql.c_str(), sSql.length());

        cout << string(mysql_error(_pstMql)) << endl;


        if (_bConnected)
        {
            cout << "has connect" << endl;

        } else
        {

            cout << "not connect" << endl;

        }
        if (iRet == 0)
        {
            cout << "queryOK" << endl;
        } else
        {
            cout << "queryfail" << endl;
        }

        if (iRet != 0)
        {
            int iError = mysql_errno(_pstMql);
            if (iError == 2013 || iError == 2006)
            {
                connect();
                
                cout << "connet again" << endl;

                iRet = mysql_real_query(_pstMql, sSql.c_str(), sSql.length());
            }
        }
        if (iRet != 0)
        {
            throw MysqlHelper_Exception("[MysqlHelper::execute]: mysql_query: [ " + sSql + " ] :" + string(mysql_error(_pstMql)));
        }

    }

     MysqlHelper::MysqlData MysqlHelper::queryRecord(const string& sSql)
     {
        MysqlData data;

        if (!_bConnected)
        {
            connect();
        }

        _sLastSql = sSql;

        int iRet = mysql_real_query(_pstMql, sSql.c_str(), sSql.length());
        if (iRet != 0)
        {
            int iError = mysql_errno(_pstMql);
            if (iError == 2013 || iError == 2006)
            {
                connect();
                iRet = mysql_real_query(_pstMql, sSql.c_str(), sSql.length());
            }
        }

        if (iRet != 0)
        {
            throw MysqlHelper_Exception("MysqlHelper::execute]: mysql_query :[ " + sSql + " ] :" + string(mysql_error(_pstMql)));
        }
        MYSQL_RES *pstRes = mysql_store_result(_pstMql);
        if (pstRes == NULL)
        {
            throw MysqlHelper_Exception("[MysqlHelper::queryRecord]: mysql_store_result: " + sSql + " : " + string(mysql_error(_pstMql)));
        }

        std::vector<string> vtFields;
        MYSQL_FIELD *field;
        while((field = mysql_fetch_field(pstRes)))
        {
            vtFields.push_back(field->name);
        }
        std::map<string, string> mpRow;
        MYSQL_ROW stRow;
        while((stRow = mysql_fetch_row(pstRes)) != (MYSQL_ROW) NULL)
        {
            mpRow.clear();
            unsigned long * lengths = mysql_fetch_lengths(pstRes);
            for (size_t i = 0; i < vtFields.size(); ++i)
            {
                if (stRow[i])
                {
                    mpRow[vtFields[i]] = string(stRow[i], lengths[i]);
                }else
                {
                    mpRow[vtFields[i]] = "";
                }
            }

            data.data().push_back(mpRow);
        }

        mysql_free_result(pstRes);
        return data;

     }


     size_t MysqlHelper::updateRecord(const string& sTableName, const RECORD_DATA &mapColumns, const string &sCondition)
     {
        string sSql = buidUpdateSQL(sTableName, mapColumns, sCondition);
        execute(sSql);
        return mysql_affected_rows(_pstMql);
     }


     size_t MysqlHelper::insertRecord(const string& sTableName, const RECORD_DATA &mapColumns)
     {

        string sSql = buildInsertSQL(sTableName, mapColumns);

        if (_bConnected)
        {
            cout << "has connect" << endl;

        } else
        {

            cout << "not connect" << endl;

        }
        
       
        execute(sSql);

        return mysql_affected_rows(_pstMql);
     }

     size_t MysqlHelper::replaceRecord(const string &sTableName, const RECORD_DATA &mapColumns)
     {
        string sSql = buildReplaceSQL(sTableName, mapColumns);
        execute(sSql);
        return mysql_affected_rows(_pstMql);
     }

     size_t MysqlHelper::deleteRecord(const string& sTableName, const string& sCondition)
     {
        ostringstream sSql;
        sSql << "delete from " << sTableName << " " << sCondition;

        cout << sSql << endl;

        execute(sSql.str());
        return mysql_affected_rows(_pstMql);
     }


     size_t MysqlHelper::getRecordCount(const string& sTableName, const string& sCondition)
     {
        ostringstream sSql;
        sSql << "select count(*) as num from " << sTableName << " " << sCondition;
        MysqlData data = queryRecord(sSql.str());
        long n = atol(data[0]["num"].c_str());
        return n;
     }
    
    size_t MysqlHelper::getSqlCount(const string &sCondition)
    {
        ostringstream sSql;
        sSql << "select count(*) as num " << sCondition;
        MysqlData data = queryRecord(sSql.str());
        long n = atol(data[0]["num"].c_str());
        return n;
    }

    int MysqlHelper::getMaxValue(const string& sTableName, const string& sfiledName, const string& sCondition)
    {
        ostringstream sSql;
        sSql << "select " << sfiledName << " as f from " << sTableName << " " << sCondition << " order by f desc limit 1";
        MysqlData data = queryRecord(sSql.str());
        int n = 0;
        if (data.size() == 0)
        {
            n = 0;
        } else
        {
            n = atol(data[0]["f"].c_str());
        }

        return n;
    }

    bool MysqlHelper::existRecord(const string &sql)
    {
        return queryRecord(sql).size() > 0;

    }

    long MysqlHelper::lastInserID()
    {
        return mysql_insert_id(_pstMql);
    }

     size_t MysqlHelper::getEffectedRows()
     {
        return mysql_affected_rows(_pstMql);

     }


     MysqlHelper::MysqlRecord::MysqlRecord(const map<string, string> &record):_record(record){}

     const string &MysqlHelper::MysqlRecord::operator[](const string &s)
     {
        std::map<string, string>::const_iterator it = _record.find(s);
        if (it == _record.end())
        {
            throw MysqlHelper_Exception("field '" + s + "' not exists.");
        }

        return it->second;
     }

     std::vector<std::map<string, string> > & MysqlHelper::MysqlData::data()
     {
        return _data;
     }

     size_t  MysqlHelper::MysqlData::size()
     {
        return _data.size();
     }

     MysqlHelper::MysqlRecord MysqlHelper::MysqlData::operator[](size_t i)
     {
        return MysqlRecord(_data[i]);
     }

} //end namespace



















