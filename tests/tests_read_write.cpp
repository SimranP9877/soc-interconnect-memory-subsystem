#include "cpu_initiator.h"
#include <iostream>

void CPU::run_read_write_test()
{
	transaction_for_write();
	transaction_for_read();
}

void CPU::transaction_for_write()
{
	data =1234;
 	tlm::tlm_generic_payload trans;
 	sc_time delay = SC_ZERO_TIME;

 	//write
 	trans.set_command(tlm::TLM_WRITE_COMMAND);
 	trans.set_address(address);
 	trans.set_data_ptr(reinterpret_cast<unsigned char*>(&data));
 	trans.set_data_length(sizeof(data));

 	std::cout<<sc_time_stamp()<<"CPU: Starting transaction"<<"\n";
    std::cout<<sc_time_stamp()<<"CPU: Writing value "<< data <<" to address "<<address <<"\n";

    socket->b_transport(trans,delay);

    if(trans.is_response_error())
    {
    	SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
    }

}


void CPU::transaction_for_read()
{
	//read
    data = 0;

    tlm::tlm_generic_payload trans;
 	sc_time delay = SC_ZERO_TIME;

    trans.set_command(tlm::TLM_READ_COMMAND);
    trans.set_address(address);
    trans.set_data_ptr(reinterpret_cast<unsigned char*> (&data));
    trans.set_data_length(sizeof(data));

    std::cout<<sc_time_stamp()<<"CPU: Reading address "<< address <<"\n";
    
    socket->b_transport(trans,delay);

    if(trans.is_response_error())
    {
    	SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
        return;
    }

    std::cout<<sc_time_stamp()<<"CPU: Read value = "<< data <<"\n";
    
    if(data == 1234)
    {
    	std::cout<<"CPU : Verification successful"<<"\n";
    }

    else
    {
    	SC_REPORT_ERROR("TLM-2", "Data verification failed");
    }


}