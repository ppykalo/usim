#include "sysbus.h"

#include <iostream>
#include <iomanip>

SystemBus::SystemBus()
{
  /* empty */
}

void SystemBus::register_device(uint32_t base_addr, DeviceIf *dev)
{
  SysDevice sys_device = {base_addr, dev};
  m_devs.push_back(sys_device);
}

uint32_t SystemBus::read32(uint32_t addr)
{
  std::cout << ">>> Memory read on address 0x" << std::hex << std::setw(8) << std::setfill('0') << addr << std::endl;
  for (auto it = m_devs.begin(); it != m_devs.end(); it++) {
    auto& sysdev = *it;
    uint32_t base_addr = sysdev.base_addr;
    uint32_t size = sysdev.device->get_size();
    
    if (addr >= base_addr && addr < (base_addr + size)) {
      return sysdev.device->read32(addr - base_addr);
    }
  }
}

void SystemBus::write32(uint32_t addr, uint32_t data)
{
  std::cout 
    << ">>> Memory write on address 0x" 
    << std::hex << std::setw(8) << std::setfill('0') << addr 
    << " with value " << data << std::endl;
  for (auto it = m_devs.begin(); it != m_devs.end(); it++) {
    auto& sysdev = *it;
    uint32_t base_addr = sysdev.base_addr;
    uint32_t size = sysdev.device->get_size();

    if (addr >= base_addr && addr < (base_addr + size)) {
      sysdev.device->write32(addr - base_addr, data);
      return;
    }
  }
}

uint32_t SystemBus::get_size()
{
  throw "Not Implemented Error";
}
