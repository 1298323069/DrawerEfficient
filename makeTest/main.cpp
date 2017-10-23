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
    mysqlhelper.init("192.168.3.132","root","123456","CORINFO");
    try {
        
        mysqlhelper.connect();
        
    } catch (MysqlHelper_Exception& excep) {
        
        cout << excep.errorInfo;
        return -1;
    }

    
	return 0;
}
