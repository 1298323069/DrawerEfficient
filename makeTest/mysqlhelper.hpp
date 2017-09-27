//-------------------
//mysqlhelper.hpp
#ifndef mysqlhelper_hpp
#define mysqlhelper_hpp 
#include <stdlib.h>
#include <map>
#include <vector>
#include <string>
#include "mysql.h"

using namespace std;
namespace mysqlhelper
{

	/* DB exception */

	struct  MysqlHelper_Exception
	{
		MysqlHelper_Exception(const string &sBuffer):errorInfo(sBuffer){};


		~MysqlHelper_Exception() throw(){};


		string errorInfo;
		
	};


	/* DBConfig */
	struct  DBConf
	{
		string _host;        /* 主机地址 */
		string _user;        /* 用户名 */
		string _passsword;   /* 用户密码 */
		string _database;    /* 数据库 */
		string _characters;  /* 字符集 */
		int _port;           /* 端口 */
		int _flag;           /* 客户短标示 */


		DBConf():_port(0),_flag(0){}

		void loadFromMap(const map<string, string> &mpParam)
		{

			map<string, string> mpTmp = mpParam;

			_host = mpTmp["dbhost"];
			_user = mpTmp["dbuser"];
			_passsword = mpTmp["dbpass"];
			_database = mpTmp["dbname"];
			_characters = mpTmp["charset"];
			_port = atoi(mpTmp["dbport"].c_str());
			_flag = 0;
			if (mpTmp["dbport"] == "")
			{
				_port = 3306;
			}


		}
		
	};

	class MysqlHelper
	{
	public:
		MysqlHelper(const string& sHost, const string& sUser = "", const string& sPassword = "", const string& sDatabase = "",const string& scharSet = "", int port = 0, int iFlag = 0);

		MysqlHelper(const DBConf& tcDBConf);

        MysqlHelper();
        
		~MysqlHelper();
        
        void test();
        
		void init(const string& sHost, const string& sUser = "", const string& sPassword = "", const string& sDatabase = "",const string& scharSet = "", int port = 0, int iFlag = 0);

		void init(const DBConf& tcDBConf);

		void connect();

		void disConnect();

		string getVariables(const string& sName);

		MYSQL *getMysql();

		string escapeString(const string& sFrom);

		void execute(const string& sSql);

		class MysqlRecord
		{
		public:
			MysqlRecord(const map<string, string> &record);

		const string& operator [](const string &s);

		protected:
			const map<string, string>& _record;
			
		};

		class MysqlData
		{
		public:

			vector<map<string, string> >& data();


			size_t size();


			MysqlRecord operator [](size_t i);
			
		protected:
			vector<map<string, string> > _data;
		};

		MysqlData queryRecord(const string& sSql);

		enum FT
		{
			DB_INT,
			DB_STR,
			
		};

		typedef map<string, pair<FT, string> > RECORD_DATA;

		size_t updateRecord(const string& stableName, const RECORD_DATA &mapColumns, const string &sCondition);

		size_t insertRecord(const string& stableName, const RECORD_DATA &mapColumns);

		size_t replaceRecord(const string& stableName, const RECORD_DATA &mapColumns);

		size_t deleteRecord(const string& sTableName, const string& sCondition = "");

		size_t getRecordCount(const string& sTableName, const string& sCondition = "");

		size_t getSqlCount(const string &sCondition = "");

		bool existRecord(const string &sql);

		int getMaxValue(const string& sTableName, const string& sfiledName, const string& sCondition = "");

		long lastInserId();

		string buildInsertSQL(const string& sTableName, const RECORD_DATA &mapColumns);

		string buildReplaceSQL(const string& sTableName, const RECORD_DATA &mapColumns);

		string buidUpdateSQL(const string& sTableName, const RECORD_DATA &mapColumns, const string& sCondition);

		string getLastSQL(){ return _sLastSql;}

		size_t getEffectedRows();

	protected:

		MysqlHelper(const MysqlHelper& tcMysql);

		MysqlHelper& operator = (const MysqlHelper& tcMysql);

	private:

		MYSQL *_pstMql;

		DBConf _dbConf;

		bool _bConnected;

		string _sLastSql;
		
	};
}

#endif
