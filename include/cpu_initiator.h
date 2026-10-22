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
private:
    unsigned int address {0x10};
    unsigned int data;

public:
    tlm_utils::simple_initiator_socket<CPU> socket;

public:
    SC_HAS_PROCESS(CPU);

    CPU(sc_module_name name);

    void run_read_write_test(); 

    void transaction_for_write();
    void transaction_for_read();
};


#endif
