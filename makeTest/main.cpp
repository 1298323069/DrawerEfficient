//---------
//main.c
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

using namespace std;

#include "mysqlhelper.hpp"

using namespace mysqlhelper;

int main(int argc, char const *argv[])
{
    
    MysqlHelper mysqlhelper;

    mysqlhelper.init("192.168.2.199","root","123456","CORINFO");
    try {
        
        mysqlhelper.connect();
        
    } catch (MysqlHelper_Exception& excep) {
        
        cout << "sss" <<endl;
        cout << excep.errorInfo <<endl;
        
        return -1;
    }

    MysqlHelper::RECORD_DATA record;

    record.insert(make_pair("id",make_pair(MysqlHelper::DB_INT,"6")));
    record.insert(make_pair("name",make_pair(MysqlHelper::DB_STR,"xiaoming")));
    record.insert(make_pair("age",make_pair(MysqlHelper::DB_INT,"18")));
    record.insert(make_pair("phone",make_pair(MysqlHelper::DB_INT,"18")));
    int res = 0;
    try
    {

        res = mysqlhelper.insertRecord("person",record);

    } catch(MysqlHelper_Exception& excep)
    {
        cout <<excep.errorInfo << endl;

        return -1;
    }
    cout << "res:" << res << " insert successfully "<< endl;

    
	return 0;
}
