#include "cpu_initiator.h"

CPU::CPU(sc_module_name name):sc_module(name),cpu_init_sckt("cpu_init_sckt")
{
	SC_THREAD(run_read_write_test);
}

