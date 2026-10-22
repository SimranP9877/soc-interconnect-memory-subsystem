#include "memory_target.h"

Memory::Memory(sc_module_name name) :sc_module (name),socket("socket")
{
	socket.register_b_transport(this, &Memory::b_transport);
}

void Memory::b_transport(tlm::tlm_generic_payload& trans, sc_time& delay)
{
	tlm::tlm_command cmd = trans.get_command();
	unsigned int     adr = trans.get_address();
	unsigned char* ptr   = trans.get_data_ptr();
	unsigned int   len   = trans.get_data_length();

	if(ptr == nullptr || adr >= SIZE || len > SIZE- adr)
	{
		trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
		return ;
	}

	if(cmd == tlm::TLM_WRITE_COMMAND)
	{
		memcpy(&mem[adr],ptr,len);
		std::cout<<sc_time_stamp()<<"Memory : Write  transaction received at address "<<adr;
		std::cout<<"\n";
	}

	else if(cmd == tlm::TLM_READ_COMMAND)
	{
		memcpy(ptr, &mem[adr], len);
		std::cout<<sc_time_stamp()<<"Memory "<<"Read transcation received"<<"\n";
		//std::cout<< sc_time_stamp()<< " Memory: Read address" << adr <<" = " << mem[adr] <<"received";
		//std::cout<<"\n";
	}
	else
	{
		trans.set_response_status(tlm::TLM_COMMAND_ERROR_RESPONSE);
		return;
	}

	trans.set_response_status(tlm::TLM_OK_RESPONSE);
}