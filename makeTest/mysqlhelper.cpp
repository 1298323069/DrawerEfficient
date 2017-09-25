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
        
    }

}
