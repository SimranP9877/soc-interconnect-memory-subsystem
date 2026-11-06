#ifndef  BUS_INTERCONNECT_H
#define  BUS_INTERCONNECT_H

//socket namespace for modules
#include <systemc>
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace sc_core;
using namespace sc_dt;
using namespace std;

#define SIZE 256

class BusInterconnect : public sc_module
{
 

  public:
  //socket target to receive payload from CPU(initiator)
  //socket initiator to forward payload to Memory(target)
  tlm_utils::simple_initiator_socket<BusInterconnect> m_bus_init_sckt0;
  tlm_utils::simple_initiator_socket<BusInterconnect> m_bus_init_sckt1;
  tlm_utils::simple_target_socket<BusInterconnect> m_bus_target_sckt;

  public: 
  	SC_HAS_PROCESS(BusInterconnect);
  	BusInterconnect(sc_module_name name);
    void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay);

};

#endif
  