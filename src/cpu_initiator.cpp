#include "cpu_initiator.h"

CPU::CPU(sc_module_name name):sc_module(name),socket("socket")
{
	SC_THREAD(run_read_write_test);
}

