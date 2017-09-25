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
		



	}

}