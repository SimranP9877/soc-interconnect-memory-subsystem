#ifndef  CPU_INITIATOR_H
#define  CPU_INITIATOR_H

//socket namespace for modules
#include <systemc>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

class CPU : public sc_module
{
public:
    tlm_utils::simple_initiator_socket<CPU> socket;

public:
    SC_HAS_PROCESS(CPU);

    CPU(sc_module_name name);

    void run_read_write_test(); 

    void transaction_for_write(int address, int d_len ,tlm::tlm_command cmd);
    void transaction_for_read(int address,int d_len ,unsigned char* value);
};


#endif
