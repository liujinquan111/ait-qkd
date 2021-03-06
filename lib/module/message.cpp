/* 
 * message.cpp
 * 
 * QKD module message implementation
 *
 * Author: Oliver Maurhart, <oliver.maurhart@ait.ac.at>
 *
 * Copyright (C) 2012-2016 AIT Austrian Institute of Technology
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


// ------------------------------------------------------------
// incs

#include <boost/format.hpp>

// ait
#include <qkd/module/message.h>


using namespace qkd::module;


// ------------------------------------------------------------
// vars


/**
 * message id counter
 */
uint32_t qkd::module::message::m_nLastId = 0;


// ------------------------------------------------------------
// code


/**
 * ctor
 * 
 * @param   nKeyId      the key id the message is bound to
 * @param   eType       type of message
 */
message::message(qkd::key::key_id nKeyId, qkd::module::message_type eType) {
    m_cHeader.nId = 0;
    m_cHeader.nKeyId = nKeyId;
    m_cHeader.eType = eType;
}


/**
 * give a debug string
 * 
 * @param   sIndent     indent of message canonical dump
 * @return  a debug string describing the message
 */
std::string message::string(std::string const & sIndent) const {
    
    boost::format cLineFormatter = boost::format("<%10u><%10u><%-8s><%10u><%08x>\n%s");

    cLineFormatter % id();
    cLineFormatter % m_cHeader.nKeyId;
    
    switch (type()) {
        
    case qkd::module::message_type::MESSAGE_TYPE_DATA:
        cLineFormatter % "DATA";
        break;
    
    case qkd::module::message_type::MESSAGE_TYPE_KEY_SYNC:
        cLineFormatter % "KEY_SYNC";
        break;
        
    default:
        cLineFormatter % "UNKNOWN";
        break;
    }

    cLineFormatter % data().size();
    cLineFormatter % data().crc32();
    cLineFormatter % data().canonical(sIndent);
    
    return cLineFormatter.str();
}



