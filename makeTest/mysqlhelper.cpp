//-----------------
//mysqlhelper.cpp
#include "mysqlhelper.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <cstring>

using namespace std;

namespace mysqlhelper{

    MysqlHelper::MysqlHelper()
    {
        
    }

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
        _dbConf._characters = scharSet;
        _dbConf._port = port;
        _dbConf._port = iFlag;
        
    }

    void MysqlHelper::init(const DBConf& tcDBConf)
    {
        _dbConf = tcDBConf;
    }
    
    void MysqlHelper::disConnect()
    {
        if(_pstMql != NULL )
        {
            mysql_close(_pstMql);
            _pstMql = mysql_init(NULL);
        }
        
        _bConnected = false;
        
    }
    void MysqlHelper::connect()
    {
        disConnect();
        
        if (_pstMql == NULL) {
            
            _pstMql = mysql_init(NULL);
            
        }
        //建立连接以后，自动调用设置字符集的语句
        
        if (mysql_options(_pstMql, MYSQL_SET_CHARSET_NAME,_dbConf._characters.c_str() )) {
            
            throw(MysqlHelper_Exception(string("MysqlHelper::connect: mysql_options MYSQL_SET_CHARSET_NAME") + _dbConf._characters + ":" + string(mysql_error(_pstMql))));
                  
        }
        if(mysql_real_connect(_pstMql, _dbConf._host.c_str(), _dbConf._user.c_str(), _dbConf._passsword.c_str(), _dbConf._database.c_str(), _dbConf._port, NULL, _dbConf._flag)){
                  
            throw(MysqlHelper_Exception("[MysqlHelper::connect]: mysql_real_connect: " + string(mysql_error(_pstMql))));
            
                  
        }
                  
        _bConnected = true;
                  
                  
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
                sColumnNames << "'" << it->first << "'";
                
                if( it->second.first == DB_INT)
                {
                    sColumnNames << it->second.second;
                    
                } else
                {
                    sColumnValues << "'" << escapeString(it->second.second) << ",";
                }
                
            } else
            {
                sColumnNames << ",'" << it->first << "'";
                
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
        
        os << "insert into" << sTableName << "(" << sColumnNames.str() << ") values (" << sColumnValues.str() << ")";
        
        return os.str();
        
    }


    string MysqlHelper::buildReplaceSQL(const string& sTableName, const RECORD_DATA &mapColumns)
    {
        ostringstream sColumnNames;
        ostringstream sColumnValues;

        map<string,pair<FT, string>>::const_iterator itEnd = mapColumns.end();

        for (map<string, pair<FT, string>>:: const_iterator it = mapColumns.begin(); it < itEnd; ++it)
        {
            if (it == mapColumns.begin()) 
            {
                sColumnNames << "'" << it->first << "'";
                if (it->second.first == DB_INT)
                {
                    sColumnValues << it->second.second;

                } else
                {
                    sColumnValues << "'" << escapeString(it->second) << "'";
                }
            } else
            {
                sColumnNames << ",'" << it->first << "'";
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

        map<string, pair<FT, string>>::const_iterator itEnd = mapColumns.end();
        for (map<string, pair<FT, string>>::const_iterator it = mapColumns.begin(); it != itEnd; ++it)
        {
            if (it == mapColumns.begin())
            {
                sColumnNameValueSet << "'" << it->first << "'";

            } else
            {
                sColumnNameValueSet << ",'" << it->first << "'";
            }

            if (it->second.first == DB_INT)
            {
                sColumnNameValueSet << "= " << it ->second.second;
            } else
            {
                sColumnNameValueSet << "= '" << escapeString(it->second.second) << "'"''
            }
        }

        ostringstream os;

        os << "update " << sTableName << " set" << sColumnNameValueSet.str() << " " << sWhereFilter;

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
        //没有连上， 连接数据库
        if (!_bConnected)
        {
            connect();
        }
        _sLastSql = sql;

        int iRet = mysql_real_query(_pstMql, sSql.c_str(), sSql.length());
        if (iRet != 0)
        {
            //自动重新连接
            int iError = mysql_error(_pstMql);
            if (iError == 1013 || iError == 2006)
            {
                connect();
                iRet = mysql_real_query(_pstMql, sSql.c_str(), sSql.length();
            }
        }

        if (iRet != 0)
        {
            throw MysqlHelper_Exception
        }
    }
    
}



















