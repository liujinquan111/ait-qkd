/*
 * fiber_sync.cpp
 * 
 * Implementation of a synchronization impulse transmission fiber
 *
 * Author: Philipp Grabenweger
 *         Oliver Maurhart, <oliver.maurhart@ait.ac.at>
 *
 * Copyright (C) 2013-2016 AIT Austrian Institute of Technology
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

#include <fstream>

// ait
#include "fiber_sync.h"
#include "../channel_event_manager.h"


using namespace qkd::simulate;


// -----------------------------------------------------------------
// code


/**
 * handle a channel event. 
 * 
 * @param   cEvent      the channel event to be handled
 */
void fiber_sync::handle(event const & cEvent) {
    
    switch (cEvent.eType) {
        
    case event::type::SYNC_PULSE: 
        { 
            // incoming sync pulse
            event cEventNew;
                
            cEventNew.ePriority = event::priority::NORMAL;
            cEventNew.eType = event::type::SYNC_PULSE;
            cEventNew.cDestination = parent();
            cEventNew.cSource = this;
            cEventNew.nTime = manager()->get_time();
            
            // forward sync pulse to fiber
            manager()->add_event(cEventNew); 
        }
        break;
    
    default:
        break;
    }
}


/**
 * write out all parameters of this event handler and its child event handlers
 * 
 * @param   cStream     the stream to write to
 */
void fiber_sync::write_parameters(std::ofstream & cStream) {

    cStream << "NAME: " << get_name() << std::endl;
    cStream << std::endl;
}
