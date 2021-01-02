#include "leveldb/db.h"
#include <cassert>
#include <iostream>


int main() {
    leveldb::DB * pDb;
    leveldb::Options tOptions;
    {
        tOptions.create_if_missing = true;
    }
    leveldb::Status tStatus = leveldb::DB::Open(tOptions, "testdb", &pDb);
    assert(tStatus.ok());

    std::string const & strKey = "TestKey";

    tStatus = pDb->Put(leveldb::WriteOptions(), strKey, "TestValue");
    if(!tStatus.ok())
    {
        std::cerr << tStatus.ToString() << std::endl;
    }
    std::string strRes;
    tStatus = pDb->Get(leveldb::ReadOptions(), strKey, &strRes);
    if(!tStatus.ok())
    {
        std::cerr << tStatus.ToString() << std::endl;
    }
    std::cout << strRes << std::endl;

    tStatus = pDb->Delete(leveldb::WriteOptions(), strKey);

    delete pDb;
    return 0;
}
