/*
 * nic.h
 * 
 * this file describes the Q3P network interface card handling
 * 
 * Author: Oliver Maurhart, <oliver.maurhart@ait.ac.at>
 *
 * Copyright (C) 2012-2015 AIT Austrian Institute of Technology
 * AIT Austrian Institute of Technology GmbH
 * Donau-City-Strasse 1 | 1220 Vienna | Austria
 * http://www.ait.ac.at
 *
 * This file is part of the AIT QKD Software Suite.
 *
 * The AIT QKD Software Suite is free software: you can redistribute 
 * it and/or modify it under the terms of the GNU General Public License 
 * as published by the Free Software Foundation, either version 3 of 
 * the License, or (at your option) any later version.
 * 
 * The AIT QKD Software Suite is distributed in the hope that it will 
 * be useful, but WITHOUT ANY WARRANTY; without even the implied warranty 
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with the AIT QKD Software Suite. 
 * If not, see <http://www.gnu.org/licenses/>.
 */

 
#ifndef __QKD_Q3P_NIC_H_
#define __QKD_Q3P_NIC_H_


// ------------------------------------------------------------
// incs

#include <exception>
#include <string>

#include <inttypes.h>

#include <boost/shared_ptr.hpp>

// Qt
#include <QtCore/QObject>
#include <QtDBus/QtDBus>

// ait
#include <qkd/utility/memory.h>


// ------------------------------------------------------------
// decls


namespace qkd {
    
namespace q3p {    

// fwd
class engine_instance;
    
class nic_instance;
typedef boost::shared_ptr<nic_instance> nic;


/**
 * This is the network interface q3p "card" object.
 * 
 * On behalf of the TUN/TAP we create a q3p0 (or q3p1, or q3p2, 
 * or ... you got the picture) interface which is capable of
 * handling IP packets.
 * 
 * =)
 * 
 * 
 * For a process creating a TUN/TAP device on Linux 
 * it needs the CAP_NET_ADMIN capability.
 * 
 * One can set this capability with:
 * 
 *      $ sudo setcap cap_net_admin=ep /PATH/TO/PROCESS
 * 
 * 
 * The offered DBus interface is
 * 
 *      DBus Interface: "at.ac.ait.q3p.nic"
 * 
 * 
 * Properties of at.ac.ait.q3p.nic
 * 
 *      -name-          -read/write-    -description-
 * 
 *      name                R           name of the NIC
 * 
 * Signals emitted by at.ac.ait.q3p.nic
 * 
 *      device_ready(QString)           emitted when created the TUN/TAP device
 * 
 */
class nic_instance : public QObject {
    
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "at.ac.ait.q3p.nic")
    
    Q_PROPERTY(QString name READ name)                      /**< network interface name */
    
public:
    
    
    /**
     * exception type thrown if we don't have an engine
     */
    struct nic_no_engine : virtual std::exception, virtual boost::exception { };
    
    
    /**
     * ctor
     * 
     * @param   cEngine     the parent engine
     * @throws  nic_no_engine
     */
    nic_instance(qkd::q3p::engine_instance * cEngine);
    

    /**
     * dtor
     */
    virtual ~nic_instance();
    
    
    /**
     * return the Q3P engine
     * 
     * @return  the Q3P engine associated
     */
    inline qkd::q3p::engine_instance * engine() { return m_cEngine; };
    
    
    /**
     * return the Q3P engine
     * 
     * @return  the Q3P engine associated
     */
    inline qkd::q3p::engine_instance const * engine() const { return m_cEngine; };
    
    
    /**
     * name of the message queue
     * 
     * @return  the name of the message queue
     */
    inline QString name() const { return QString::fromStdString(m_sName); };
    
    
    /**
     * write data to the device, thus sending it to the kernel
     * 
     * @param   cData       the data to write
     */
    void write(qkd::utility::memory const & cData);

    
signals:    
    
    
    /**
     * emitted when we have a TUN/TAP device created
     * 
     * @param   sDevice     name of the device
     */
    void device_ready(QString sDevice);
    
    
private:
    
    
    /**
     * the reader thread
     */
    void reader();
    
    
    /**
     * the Q3P engine
     */
    qkd::q3p::engine_instance * m_cEngine;
    
    
    /**
     * get up the tun (from tun/tap) device
     */
    void init_tun();
    
    
    /**
     * name of the device
     */
    std::string m_sName;


    // pimpl
    class nic_data;
    boost::shared_ptr<nic_data> d;
};
  

}

}


#endif

