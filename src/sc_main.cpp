#include <systemc.h>
#include "cpu_initiator.h"
#include "memory_target.h"


class Top : public sc_module
{
public:
	CPU initiator;
	Memory memory;

public:
	SC_HAS_PROCESS(Top);

	Top(sc_module_name name):sc_module(name),initiator("initiator"),memory("memory")
	{
		//bind
		initiator.socket.bind(memory.socket);
	}
};

int sc_main(int argc, char* argv[])
{
	Top top("top");
	sc_start();
	return 0 ;
}
