/*
 * Licensed under the MIT License (MIT)
 *
 * Copyright (c) 2013 AudioScience Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * net_interface_imp.h
 *
 * Network interface implementation class
 */

#pragma once

#define HAVE_REMOTE

#include <iostream>
#include <vector>
#include <string>

#include "avdecc-lib_build.h"
#include "net_interface.h"

namespace avdecc_lib
{
struct ipheader;
struct udpheade;

class net_interface_imp : public net_interface
{
private:
    enum econsts
    {
        SIZEOF_BUFFER = 2048
    };

    std::vector<std::string> ifnames;

    uint32_t total_devs;
    struct ipheader * ip_hdr_store;
    struct udpheader * udp_hdr_store;
    int rawsock;
    int ifindex;
    uint16_t ethertype;
    uint64_t mac;
    uint64_t selected_dev_eui;
    uint8_t buf[SIZEOF_BUFFER];
    uint8_t rx_buf[SIZEOF_BUFFER];

    int getifindex(int rawsock, const char * iface);
    int setpromiscuous(int rawsock, int ifindex);

public:
    ///
    /// An empty constructor for net_interface_imp
    ///
    net_interface_imp();

    ///
    /// Destructor for net_interface_imp used for destroying objects
    ///
    virtual ~net_interface_imp();

    void STDCALL destroy();

    ///
    /// Count the number of devices.
    ///
    uint32_t STDCALL devs_count();
    
    ///
    /// Count the number of IP addresses for a device.
    ///
    size_t STDCALL device_ip_address_count(size_t dev_index);

    ///
    /// Get the MAC address of the network interface.
    ///
    uint64_t mac_addr();

    ///
    /// Get the EUI of the selected network interface.
    ///
    uint64_t get_dev_eui();
    
    ///
    /// Set the EUI of the selected network interface.
    ///
    void set_dev_eui(uint64_t dev_eui);

    ///
    /// Get the MAC address of a network interface.
    ///
    uint64_t STDCALL get_dev_mac_addr_by_index(size_t dev_index);

    ///
    /// Get network interface description by index.
    ///
    char * STDCALL get_dev_desc_by_index(size_t dev_index);

    ///
    /// Get the corresponding network interface IP address by index.
    ///
    const char * STDCALL get_dev_ip_address_by_index(size_t dev_index, size_t ip_index);
    
    ///
    /// Check whether ip_addr_str is a valid IP Address for a device.
    ///
    bool STDCALL does_interface_have_ip_address(size_t dev_index, char * ip_addr_str);
    
    ///
    /// Check whether mac_addr is the MAC Address for a device.
    ///
    bool STDCALL does_interface_have_mac_address(size_t dev_index, uint64_t mac_addr);

    ///
    /// Get the corresponding network interface name by index.
    ///
    char * STDCALL get_dev_name_by_index(size_t dev_index);

    ///
    /// Select network interface by number.
    ///
    int STDCALL select_interface_by_num(uint32_t interface_num);

    ///
    /// Update the Ethernet type for the network interface.
    ///
    int set_capture_ether_type(uint16_t * ether_type, uint32_t count);

    ///
    /// Capture a network packet.
    ///
    int STDCALL capture_frame(const uint8_t ** frame, uint16_t * mem_buf_len);

    ///
    /// Send a network packet.
    ///
    int send_frame(uint8_t * frame, uint16_t mem_buf_len);

    int get_fd();

    bool is_pcap() { return true; }
    bool is_Mac_Native_end_station_connected(uint64_t entity_id) { return false; }
};

extern net_interface_imp * net_interface_ref;
}
