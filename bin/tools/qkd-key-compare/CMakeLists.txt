# ------------------------------------------------------------
# CMakeLists.txt 
# 
# make: qkd/bin/tools/qkd-key-compare
#
# Author: Oliver Maurhart, <oliver.maurhart@ait.ac.at>
#
# Copyright (C) 2016 AIT Austrian Institute of Technology
# AIT Austrian Institute of Technology GmbH
# Donau-City-Strasse 1 | 1220 Vienna | Austria
# http://www.ait.ac.at
#
# This file is part of the AIT QKD Software Suite.
#
# The AIT QKD Software Suite is free software: you can redistribute 
# it and/or modify it under the terms of the GNU General Public License 
# as published by the Free Software Foundation, either version 3 of 
# the License, or (at your option) any later version.
# 
# The AIT QKD Software Suite is distributed in the hope that it will 
# be useful, but WITHOUT ANY WARRANTY; without even the implied warranty 
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with the AIT QKD Software Suite. 
# If not, see <http://www.gnu.org/licenses/>.
# ------------------------------------------------------------


# ------------------------------------------------------------
# tools/qkd-key-compare

# sources
set(QKD_KEY_COMPARE_SRC
    main.cpp
)

# bin definition
add_executable(qkd-key-compare ${QKD_KEY_COMPARE_SRC})

# linkage
target_link_libraries(qkd-key-compare ${CMAKE_REQUIRED_LIBRARIES})

# install
install(TARGETS qkd-key-compare RUNTIME DESTINATION bin COMPONENT tools)

