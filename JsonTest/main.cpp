//---------
//main.c

#include <iostream>
#include <cmath>
#include "jsonwrite.hpp"

using namespace std;

int main(int argc, char const *argv[])
{

    JsonWrite * write = new JsonWrite;

    write->StartArray();
    write->StartShortObject();
    write->KeyValue("name", "shiyanlou1");
    write->KeyValue("age", 3);
    write->EndObject();

     write->StartObject();
     write->KeyValue("skills", "c++");
     write->KeyValue("skills", "python");
     write->KeyValue("skills", "php");
     write->KeyValue("skills", "java");
     write->KeyValue("url", "http://shiyanlou.com");

     write->Key("path");
     write->StartArray();
     write->Value("web");
     write->Value("algorithm");
     write->Value("linux");
     write->EndArray();

     write->Key("short-array");
     write->StartShortArray();
     write->Value(1);
     write->Value((uint64_t)0xabcdef123456);
     write->Value(M_PI);
     write->EndContainer();

     write->EndObject();
     write->Value(false);
     write->EndArray();

	return 0;
}

