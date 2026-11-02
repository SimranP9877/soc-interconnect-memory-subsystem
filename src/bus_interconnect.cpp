#include "bus_interconnect.h"

BusInterconnect::BusInterconnect(sc_module_name name)
:sc_module(name),m_bus_init_sckt("m_bus_init_sckt"),m_bus_target_sckt("m_bus_target_sckt")
{
  m_bus_target_sckt.register_b_transport(this,&BusInterconnect::b_transport);
}

//Bus target
void BusInterconnect::b_transport(tlm::tlm_generic_payload& trans, sc_time& delay)
{
  
  unsigned int adr = trans.get_address();

  std::cout<<"BUS:  Transaction received"<<"\n";

  if( adr >= SIZE )
  {
    std::cout<<"BUS: Address unmapped"<<"\n";
    trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
    return;
  }

  std::cout<<"BUS: Address mapped to memory"<<"\n"; 
    
  m_bus_init_sckt->b_transport(trans,delay);
}

