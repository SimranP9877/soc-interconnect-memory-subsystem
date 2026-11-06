#include "bus_interconnect.h"

BusInterconnect::BusInterconnect(sc_module_name name)
: sc_module(name)
, m_bus_init_sckt0("m_bus_init_sckt0")
, m_bus_init_sckt1("m_bus_init_sckt1")
, m_bus_target_sckt("m_bus_target_sckt")
{
  m_bus_target_sckt.register_b_transport(this,&BusInterconnect::b_transport);
}

//Bus target
void BusInterconnect::b_transport(tlm::tlm_generic_payload& trans, sc_time& delay)
{
  
  unsigned int adr = trans.get_address();

  std::cout<<"BUS:  Transaction received"<<"\n";

  if( adr >= 0x0000  && adr <= 0x00FF )
  {
    std::cout<<"BUS: Address mapped to memory 0"<<"\n";
    m_bus_init_sckt0->b_transport(trans,delay);
  }
  else if(adr >= 0x0100  && adr <= 0x01FF )
  {
    std::cout<<"BUS: Address mapped to memory 1"<<"\n";
    trans.set_address(adr - 0x0100);
    m_bus_init_sckt1->b_transport(trans,delay);
    trans.set_address(adr + 0x0100);
  }
  else
  {
    std::cout<<"BUS: Address unmapped"<<"\n";
    trans.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
    return;
  }
}

