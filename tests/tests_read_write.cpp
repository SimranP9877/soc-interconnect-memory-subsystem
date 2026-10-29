#include "cpu_initiator.h"
#include <iostream>

void CPU::run_read_write_test()
{
	unsigned char value1[]= {2};
    unsigned char value2[]= {2,3};
    unsigned char value3[]= {2,3,4,5};

    transaction_for_write(0x05,1,tlm::TLM_WRITE_COMMAND);
    transaction_for_read(0x05,1,value1);

    transaction_for_write(0x20,2,tlm::TLM_WRITE_COMMAND);
    transaction_for_read(0x20,2,value2);


    transaction_for_write(0x40,4,tlm::TLM_WRITE_COMMAND);
    transaction_for_read(0x40,4,value3);

    transaction_for_write(0xFE,4,tlm::TLM_WRITE_COMMAND);  //invalid as we have 256bytes and 4byte needs to be allocated from 254.
    
    transaction_for_read(0x10,0,value3);

    transaction_for_write(0xFA,1,tlm::TLM_IGNORE_COMMAND);
	      
}

void CPU::transaction_for_write(int address, int d_len ,tlm::tlm_command cmd)
{
	unsigned char data[d_len];

    for(int i=0; i<d_len ; i++)
    {
        data[i] = i+2;
    }

    tlm::tlm_generic_payload trans;
    sc_time delay = SC_ZERO_TIME;	

    //write
    trans.set_command(cmd);
    trans.set_address(address);
    trans.set_data_ptr(data);
    trans.set_data_length(sizeof(data));

    std::cout<<sc_time_stamp()<<"CPU:  write "<< sizeof(data) << "byte at "<< address <<"\n";

    socket->b_transport(trans,delay);

    if(trans.is_response_error()) 
    {
        std::string error_msg = "Transaction failed with status: " + std::string(trans.get_response_string());
        std::cout<<"CPU :" << error_msg.c_str()<<"\n";
    }

}


void CPU::transaction_for_read(int address, int d_len ,unsigned char* value)
{
	unsigned char data[d_len]{};

    tlm::tlm_generic_payload trans;
    sc_time delay = SC_ZERO_TIME;

    trans.set_command(tlm::TLM_READ_COMMAND);
    trans.set_address(address);
    trans.set_data_ptr(data);
    trans.set_data_length(sizeof(data));

    std::cout<<sc_time_stamp()<<"CPU:  Read  "<<sizeof(data) <<"byte at "<< address<<"\n";
    socket->b_transport(trans,delay);

    if (trans.is_response_error())
    {
        std::string error_msg = "Transaction failed with status: " + std::string(trans.get_response_string());
        std::cout<<"CPU :" << error_msg.c_str()<<"\n";
    } 
    else if (std::memcmp(data, value, d_len) == 0)
    {
        std::cout<<"CPU : Verification successful"<<"\n";
    } 
    else
    {
        SC_REPORT_ERROR("TLM-2", "data verification failed");
    }

}