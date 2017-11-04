//---------
//main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>

using namespace std;

#include "mysqlhelper.hpp"

using namespace mysqlhelper;

void testSqlAbout();


int main(int argc, char const *argv[])
{

    

    
	return 0;
}

void testSqlAbout()
{

//     MysqlHelper mysqlhelper;

//     mysqlhelper.init("localhost","root","123456","CORINFO");

//     try {
        
//         mysqlhelper.connect();
        
//     } catch (MysqlHelper_Exception& excep) {
        
//         cout << "sss" <<endl;
//         cout << excep.errorInfo <<endl;
        
//         return -1;
//     }
// //查询一条记录
//     MysqlHelper::MysqlData dataSet;
//     string querySQL = "select usedid from person where age > 16";
//     try
//     {
//         dataSet = mysqlhelper.queryRecord(querySQL);
//     } catch(MysqlHelper_Exception & excep)
//     {
//         cout << excep.errorInfo;

//         return -1;
//     }

//     for (size_t i = 0; i < dataSet.size() ; ++i)
//     {
//         cout << dataSet[i]["usedid"] << endl;
//     }




//修改一条记录
    // int changeRes;

    // MysqlHelper::RECORD_DATA recordChange;
    // recordChange.insert(make_pair("age",make_pair(MysqlHelper::DB_INT,"16")));
    // try
    // {
    //     changeRes = mysqlhelper.updateRecord("person",recordChange,"where usedid=2");

    // } catch(MysqlHelper_Exception &excep)
    // {
    //     cout << excep.errorInfo;

    //     return -1;
    // }


//增加一条

    // MysqlHelper::RECORD_DATA record;

    // record.insert(make_pair("name",make_pair(MysqlHelper::DB_STR,"xiaoming")));
    // record.insert(make_pair("age",make_pair(MysqlHelper::DB_INT,"18")));
    // record.insert(make_pair("phone",make_pair(MysqlHelper::DB_INT,"18")));
    // record.insert(make_pair("face",make_pair(MysqlHelper::DB_STR,"beauty")));
    // record.insert(make_pair("height",make_pair(MysqlHelper::DB_INT,"118")));

    // int res = 0;

    // try
    // {
    //     res = mysqlhelper.insertRecord("person",record);

    // } catch(MysqlHelper_Exception& excep)
    // {
    //     cout <<excep.errorInfo << endl;

    //     return -1;
    // }

//删除一条记录 ID为2
    // int res = 0;
    // try{

    //     res = mysqlhelper.deleteRecord("person"," where id=2");

    // }catch(MysqlHelper_Exception& excep)
    // {
    //     cout << excep.errorInfo;

    //     return -1;
    // }
 
    // cout << "res:" << res << " insert successfully "<< endl;


}
