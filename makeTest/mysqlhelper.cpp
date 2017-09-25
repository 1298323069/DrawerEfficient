//-----------------
//mysqlhelper.cpp
#include "mysqlhelper.hpp"
#include <string>
#include <sstream>
using namespace std;
namespace mysqlhelper{

	MysqlHelper::MysqlHelper():__bConnected(false)
	{
		_pstMql = mysql_init(NULL):

	}

	MysqlHelper::MysqlHelper(const string& sHost, const string& sUser, const string& sPassword, const string& sDatabase,const string& scharSet, int port, int iFlag):__bConnected(false)
	{

		init(sHost, sUser, sPassword, sDatabase, scharSet, port, iFlag);

		_pstMql = mysql_init(NULL):

	}

	MysqlHelper::MysqlHelper(const DBConf& tcDBConf):__bConnected(false)
	{
		_dbConf = tcDBConf;


		_pstMql = mysql_init(NULL):

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
    
    void MysqlHelper::connect()
    {
        disConnect();
        
        if (_pstMql == NULL) {
            
            _pstMql = mysql_init(NULL);
            
        }
        //建立连接以后，自动调用设置字符集的语句
        
        if (mysql_options(_pstMql, MYSQL_SET_CHARSET_NAME,_dbConf._characters.c_str() )) {
            
            throw(MysqlHelper_Exception(string("MysqlHelper::connect: mysql_options MYSQL_SET_CHARSET_NAME") + _dbConf._characters + ":" + string(mysql_error(_pstMql)));
                  
        }
        if(mysql_real_connect(_pstMql, _dbConf._host.c_str(), _dbConf._user.c_str(), _dbConf._passsword.c_str(), _dbConf._database.c_str(), _dbConf._port, NULL, _dbConf._flag)){
                  
            throw(MysqlHelper_Exception("[MysqlHelper::connect]: mysql_real_connect: " + mysql_error(_pstMql)));
            
                  
        }
                  
        _bConnected = true;
                  
                  
    }
    string escapeString(const string& sFrom)
    {
        if(!_bConnected){
            connect();
        }
        
        string sTo;
        string::size_type  iLen = sFrom.length() * 2 + 1;
        char *pTo = (char *)malloc(iLen);
        memset(sTo, 0x00, iLen);
        mysql_real_escape_string(_pstMql, pTo, sFrom.c_str(),sFrom.length());
        sTo = pTo;
        free(pTo);
        return sTo;
    }
                  
    MYSQL *getMysql()
    {
        return _pstMql;
    }
                  
    string buildInsertSQL(const string& sTableName, const RECORD_DATA &mapColumns){
    
        ostringstream sColumnNames;
        ostringstream sColumnValues;
        
        map<string, pair<FT, string>>::const_iterator itEnd = mapColumns.end();
        
        for(map<string, pair<FT, string>>::const_iterator it = mapColumns.begin(), it != itEnd, ++it)
        {
            if(it == mapColumns.begin())
            {
                sColumnNames << "'" << it->frist << "'";
                if( it->second.frist == DB_INT)
                {
                    sColumnNames << it->second.second;
                } else
                {
                    sColumnValues << "'" << escapeString(it->second.second) << ",";
                }
                
            } else
            {
                sColumnNames << ",'" << it->frist << "'";
                
                if(it->second.frist == DB_INT)
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
}



















