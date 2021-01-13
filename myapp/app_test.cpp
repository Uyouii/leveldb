#include "leveldb/db.h"
#include "leveldb/write_batch.h"
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

    std::string const & strKey1 = "TestKey1";
    std::string const & strKey2 = "TestKey2";
    
    leveldb::WriteBatch oWriteBatch;
    {
        oWriteBatch.Put(strKey1, "TestValue1");
        oWriteBatch.Put(strKey2, "TestValue2");
    }
    
    tStatus = pDb->Write(leveldb::WriteOptions(), &oWriteBatch);

    std::string strValue1, strValue2;
    tStatus = pDb->Get(leveldb::ReadOptions(), strKey1, &strValue1);
    tStatus = pDb->Get(leveldb::ReadOptions(), strKey2, &strValue2);

    // iterator all key
    leveldb::Iterator* it = pDb->NewIterator(leveldb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next()) 
    {
        std::cout << it->key().ToString() << ": "  << it->value().ToString() << std::endl;
    }
    assert(it->status().ok());  // Check for any errors found during the scan
    delete it;

    delete pDb;
    return 0;
}
