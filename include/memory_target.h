#ifndef  MEMORY_TARGET_H
#define  MEMORY_TARGET_H

//socket namespace for modules
#include <systemc>
#include <tlm.h>
#include <tlm_utils/simple_target_socket.h>
#include <cstring>


using namespace sc_core;
using namespace sc_dt;
using namespace std;

#define SIZE 256


class Memory : public sc_module
{
private:
	unsigned char mem[SIZE]{};

public:
	tlm_utils::simple_target_socket<Memory>socket;

public:
	SC_HAS_PROCESS(Memory);

	Memory(sc_module_name name);
	void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay);
};



#endif
