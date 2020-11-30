// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#ifndef ROCKSDB_LITE
#include<iostream>
#include "rocksdb/db.h"
#include "rocksdb/options.h"
#include "rocksdb/slice.h"
#include "rocksdb/utilities/transaction.h"
#include "rocksdb/utilities/transaction_db.h"
#include<thread>
using namespace rocksdb;
const std::string db_path = "./rocks_data/";
const std::string wal_path = "./rocks_data/wal";
std::string kDBPath = "/tmp/rocksdb_transaction_example";
int count1=0;
int count2=0;
int count3=0;
int count4=0;

clock_t start,end; 

static struct {
	int keys = 10000;
	int threads = 1;
	int reads = 25;
	int writes = 5;
	bool sync = false;
	bool has_conflict = true;
	int ratio_2pl = 1;
	int ratio_occ = 0;
} opt;



 












void do_run(TransactionDB *db) {
     ReadOptions read_options;
     WriteOptions write_options;
     std::string value;
    
     Status s; 
   

     for (int j=0 ;j<1000;j++){

     Transaction* txn = db->BeginTransaction(write_options);
     int k;
     k =rand()%10000;
     //std::cout<<"k ="<<k<<std::endl;
     for(int i=0;i<100;i++){
     //s = txn->Get(std::to_string(i), std::to_string(i)); 
      s = txn->DoGet(read_options, std::to_string(i+k), &value, 1);
    //  txn->Get(read_options, std::to_string(i+k), &value);
    //  std::cout<<i<<"    =    "<<value<<std::endl;
     }
     //txn->Get(read_options, "2", &value);
   //  s=txn->Put(std::to_string(rand()%10000), "deasdsaf"); 
     s = txn->DoPut(std::to_string(rand()%10000), "deasdsaf", 1);
     s = txn->Commit();
     if(s.ok())  {
       count1++;

     }
     else{  std::cout<<"error"<<std::endl;
    }
   }

     
}






void do_run2(TransactionDB *db) {
     ReadOptions read_options;
     WriteOptions write_options;
     std::string value;
    
     Status s; 
   

     for (int j=0 ;j<100000;j++){

     Transaction* txn = db->BeginTransaction(write_options);
     int k;
     k =rand()%10000;
     //std::cout<<"k ="<<k<<std::endl;


     if(0){
     for(int i=0;i<1;i++){
     //s = txn->Get(std::to_string(i), std::to_string(i)); 
      s = txn->DoGet(read_options, std::to_string(i+k), &value, 1);
      //s = txn->DoGet(read_options, "1", &value, 1);
    //  txn->Get(read_options, std::to_string(i+k), &value);
    //  std::cout<<i<<"    =    "<<value<<std::endl;
     }
     }
     //txn->Get(read_options, "2", &value);
    else{
   //  s=txn->Put(std::to_string(rand()%10000), "deasdsaf"); 
     s = txn->DoPut(std::to_string(rand()%10000), "1", 1);
    // s = txn->DoPut("1", "1", 1);
     }
     s = txn->Commit();
     if(s.ok())  {
       count1++;

     }
     else{  std::cout<<"error"<<std::endl;
    }
   }

     
}


void do_run3(TransactionDB *db) {
     ReadOptions read_options;
     WriteOptions write_options;
     std::string value;

    // WriteOptions write_options;
    
     Status s; 
   

     for (int j=0 ;j<100000;j++){

     Transaction* txn = db->BeginTransaction(write_options);
     int k;
     //k =rand()%10000;
     //std::cout<<"k ="<<k<<std::endl;


     if(1){
     for(int i=0;i<1;i++){
     //s = txn->Get(std::to_string(i), std::to_string(i)); 
      s = txn->DoGet(read_options, std::to_string(i+k), &value, 1);
    //  txn->Get(read_options, std::to_string(i+k), &value);
    //  std::cout<<i<<"    =    "<<value<<std::endl;
     //     s = txn->DoGet(read_options, "1", &value, 1);
     }
     }
     //txn->Get(read_options, "2", &value);
    else{
   //  s=txn->Put(std::to_string(rand()%10000), "deasdsaf"); 
     s = txn->DoPut(std::to_string(rand()%10000), "deasdsaf", 1);
     }
     s = txn->Commit();
     if(s.ok())  {
       count2++;

     }
     else{  std::cout<<"error"<<std::endl;
    }
   }

     
}














void do_run4(TransactionDB *db) {
     int count10=0;
     ReadOptions read_options;
     WriteOptions write_options;
     std::string value;

    // WriteOptions write_options;
    
     Status s; 
    clock_t start3,end3; 
 start3 = clock();
     for (int j=0 ;j<100000;j++){

   Transaction* txn = db->BeginTransaction(write_options);

    if(rand()%2==0){

     
  
     int k;
     k =rand()%4;
     //std::cout<<"k ="<<k<<std::endl;


  //   s = txn->DoGet(read_options, std::to_string(k), &value, 1);
     s = txn->DoGet(read_options, std::to_string(k) ,&value, 1);
  //   s = txn->DoPut(std::to_string(rand()%10000), "deasdsaf", 1);
     s = txn->DoPut("1", "deasdsaf", 1);
     s = txn->Commit();
    }

    else{


     int k;
     k =rand()%10000;
     //std::cout<<"k ="<<k<<std::endl;


  // s = txn->DoGet(read_options, std::to_string(k), &value, 1);
  //   s = txn->DoGet(read_options, std::to_string(k), &value, 1);
  // s = txn->DoPut(std::to_string(rand()%10000), "deasdsaf", 1);



    
     s = txn->DoPut("1", "deasdsaf", 1);
     s = txn->DoPut("2", "deasdsaf", 1);
     s = txn->DoPut("3", "deasdsaf", 1);
     s = txn->DoPut("4", "deasdsaf", 1);
     s = txn->Commit();


    }


     if(s.ok())  {
       count10++;

     }
     else{ // std::cout<<"error"<<std::endl;
      s = txn->Rollback();
       if(s.ok())  {
       count10++;

    }
   
     }
   }


       end3 =clock();
     double duration =(double)(end3-start3)/CLOCKS_PER_SEC;
     printf("Duratuion 4  : %f\n",duration);
     std::cout<<"Count 10:"<<count10   <<std::endl; // 4.015
}


void do_run6(TransactionDB *db) {
     ReadOptions read_options;
     WriteOptions write_options;
     std::string value;

    // WriteOptions write_options;
    
     Status s; 
   

     for (int j=0 ;j<100000;j++){

     Transaction* txn = db->BeginTransaction(write_options);
     int k;
     k =rand()%4;
     //std::cout<<"k ="<<k<<std::endl;


  //   s = txn->DoGet(read_options, std::to_string(k), &value, 1);
  //   s = txn->DoGet(read_options, "3" ,&value, 1);
  //   s = txn->DoPut(std::to_string(rand()%10000), "deasdsaf", 1);
     s = txn->DoPut("1", "deasdsaf", 1);
     s = txn->Commit();
     if(s.ok())  {
       count3++;

     }
     else{  std::cout<<"error"<<std::endl;
    }
   

     }

}

void do_run5(TransactionDB *db) {
     ReadOptions read_options;
     WriteOptions write_options;
     std::string value;

    // WriteOptions write_options;
    
     Status s; 
       clock_t start3,end3; 
 start3 = clock();

     for (int j=0 ;j<1000000;j++){
 Transaction* txn = db->BeginTransaction(write_options);
    if(rand()%2==0){

     
    
     int k;
     k =rand()%4;
     //std::cout<<"k ="<<k<<std::endl;


  //   s = txn->DoGet(read_options, std::to_string(k), &value, 1);
     s = txn->DoGet(read_options, std::to_string(k) ,&value, 1);
  //   s = txn->DoPut(std::to_string(rand()%10000), "deasdsaf", 1);
     s = txn->DoPut("1", "deasdsaf", 1);
     s = txn->Commit();
    }

    else{

 
     int k;
     k =rand()%10000;
     //std::cout<<"k ="<<k<<std::endl;


  // s = txn->DoGet(read_options, std::to_string(k), &value, 1);
  //   s = txn->DoGet(read_options, std::to_string(k), &value, 1);
  // s = txn->DoPut(std::to_string(rand()%10000), "deasdsaf", 1);



    
     s = txn->DoPut("1", "deasdsaf", 1);
     s = txn->DoPut("2", "deasdsaf", 1);
     s = txn->DoPut("3", "deasdsaf", 1);
     s = txn->DoPut("4", "deasdsaf", 1);
     s = txn->Commit();


    }
     if(s.ok())  {
       count2++;

     }
     else{
       s = txn->Rollback();
       if(s.ok())  {
       count2++;
    }
      }
     }   
     end3 =clock();
     double duration =(double)(end3-start3)/CLOCKS_PER_SEC;
     printf("Duratuion 4  : %f\n",duration); // 4.015

}



void do_run7(TransactionDB *db) {
     ReadOptions read_options;
     WriteOptions write_options;
     std::string value;

    // WriteOptions write_options;
    
     Status s; 
       clock_t start3,end3; 
 start3 = clock();

     for (int j=0 ;j<1000000;j++){
 Transaction* txn = db->BeginTransaction(write_options);
    if(rand()%2==0){

     
    
     int k;
     k =rand()%4;
     //std::cout<<"k ="<<k<<std::endl;


  //   s = txn->DoGet(read_options, std::to_string(k), &value, 1);
     s = txn->DoGet(read_options, std::to_string(k) ,&value, 1);
  //   s = txn->DoPut(std::to_string(rand()%10000), "deasdsaf", 1);
     s = txn->DoPut("1", "deasdsaf", 1);
     s = txn->Commit();
    }

    else{

 
     int k;
     k =rand()%10000;
     //std::cout<<"k ="<<k<<std::endl;


  // s = txn->DoGet(read_options, std::to_string(k), &value, 1);
  //   s = txn->DoGet(read_options, std::to_string(k), &value, 1);
  // s = txn->DoPut(std::to_string(rand()%10000), "deasdsaf", 1);



    
     s = txn->DoPut("1", "deasdsaf", 1);
     s = txn->DoPut("2", "deasdsaf", 1);
     s = txn->DoPut("3", "deasdsaf", 1);
     s = txn->DoPut("4", "deasdsaf", 1);
     s = txn->Commit();


    }
     if(s.ok())  {
       count3++;

     }
     else{
       s = txn->Rollback();
       if(s.ok())  {
       count3++;
    }
      }
     }   
     end3 =clock();
     double duration =(double)(end3-start3)/CLOCKS_PER_SEC;
     printf("Duratuion 4  : %f\n",duration); // 4.015

}



void do_run8(TransactionDB *db) {
     ReadOptions read_options;
     WriteOptions write_options;
     std::string value;

    // WriteOptions write_options;
    
     Status s; 
       clock_t start3,end3; 
 start3 = clock();

     for (int j=0 ;j<1000000;j++){
 Transaction* txn = db->BeginTransaction(write_options);
    if(rand()%2==0){

     
    
     int k;
     k =rand()%4;
     //std::cout<<"k ="<<k<<std::endl;


  //   s = txn->DoGet(read_options, std::to_string(k), &value, 1);
     s = txn->DoGet(read_options, std::to_string(k) ,&value, 1);
  //   s = txn->DoPut(std::to_string(rand()%10000), "deasdsaf", 1);
     s = txn->DoPut("1", "deasdsaf", 1);
     s = txn->Commit();
    }

    else{

 
     int k;
     k =rand()%10000;
     //std::cout<<"k ="<<k<<std::endl;


  // s = txn->DoGet(read_options, std::to_string(k), &value, 1);
  //   s = txn->DoGet(read_options, std::to_string(k), &value, 1);
  // s = txn->DoPut(std::to_string(rand()%10000), "deasdsaf", 1);



    
     s = txn->DoPut("1", "deasdsaf", 1);
     s = txn->DoPut("2", "deasdsaf", 1);
     s = txn->DoPut("3", "deasdsaf", 1);
     s = txn->DoPut("4", "deasdsaf", 1);
     s = txn->Commit();


    }
     if(s.ok())  {
       count4++;

     }
     else{
       s = txn->Rollback();
       if(s.ok())  {
       count4++;
    }
      }
     }   
     end3 =clock();
     double duration =(double)(end3-start3)/CLOCKS_PER_SEC;
     printf("Duratuion 4  : %f\n",duration); // 4.015

}
int main() {
    std::string value;
         ReadOptions read_options;
        TransactionDB* txn_db;
  Options options;   WriteOptions write_options;
	options.IncreaseParallelism();
	options.wal_dir = wal_path;
	options.manual_wal_flush = false;
	options.create_if_missing = true;
	options.write_buffer_size = 512 << 20;
	options.max_write_buffer_number = 10;

	TransactionDBOptions txn_db_options;
	txn_db_options.write_policy = TxnDBWritePolicy::WRITE_COMMITTED;

	Status status = TransactionDB::Open(options, txn_db_options, db_path, &txn_db);
  Transaction* txn2 = txn_db->BeginTransaction(write_options);
 Transaction* txn = txn_db->BeginTransaction(write_options);
 start = clock();
  for(int i=0;i<1000000;i++){
      txn2->DoPut(std::to_string(i), std::to_string(i),1); 
      // start = clock();
     //  txn2->DoGet(read_options, std::to_string(i), &value, 1);
     //  end = clock();
  // Commit transaction
     // double duration =(double)(end-start)/CLOCKS_PER_SEC;("%f\n",duration); // 4.015
    //  printf("get%f\n",duration); // 4.015
  }

 txn2->Commit();

start = clock();


std::thread t1(do_run4,txn_db);
std::thread t2(do_run4,txn_db);
std::thread t3(do_run4,txn_db);
std::thread t4(do_run4,txn_db);
std::thread t5(do_run4,txn_db);
std::thread t6(do_run4,txn_db);
std::thread t7(do_run4,txn_db);
std::thread t8(do_run4,txn_db);
t1.join();
t2.join();
t3.join();
t4.join();
t5.join();
t6.join();
t7.join();
t8.join();

end = clock();

  // Commit transaction
double duration =(double)(end-start)/CLOCKS_PER_SEC;("%f\n",duration); // 4.015
 printf("%f\n",duration); // 4.015
  //txn1->Get(read_options, "1", &value);
  //std::cout<<"value"<<value<<std::endl;

//std::cout<<value<<std::endl;// s = txn_db->Get(read_options, "abc", &value);
 // delete txn;
std::cout<<"total :"<<count1+count2<<std::endl;
std::cout<<"count1 :"<<count1<<std::endl;
std::cout<<"count2 :"<<count2<<std::endl;
std::cout<<"count3 :"<<count3<<std::endl;
std::cout<<"count4 :"<<count3<<std::endl;
  // Cleanup
  delete txn_db;
  DestroyDB(db_path , options);
  return 0;
}

#endif  // ROCKSDB_LITE
