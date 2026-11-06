#include <systemc.h>
#include "cpu_initiator.h"
#include "memory_target.h"
#include "bus_interconnect.h"


class Top : public sc_module
{
public:
	CPU initiator;
	BusInterconnect interconnect;
	Memory target_0;
   	Memory target_1;

public:
	SC_HAS_PROCESS(Top);

	Top(sc_module_name name)
	    : sc_module(name)
		, initiator("initiator")
		, interconnect("interconnect")
		, target_0("target_0")
		, target_1("target_1")
   	{
	   	//bind
	   	initiator.cpu_init_sckt.bind(interconnect.m_bus_target_sckt);
	   	interconnect.m_bus_init_sckt0.bind(target_0.mem_target_sckt);
	   	interconnect.m_bus_init_sckt1.bind(target_1.mem_target_sckt);
	}
};

int sc_main(int argc, char* argv[])
{
	Top top("top");
	sc_start();
	return 0 ;
}
