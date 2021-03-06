#-------------------------------------------------------------------------------
# Copyright (C) 2018 University of Illinois Board of Trustees
# 
# This file is part of uavAP.
# 
# uavAP is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# uavAP is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#-------------------------------------------------------------------------------
set(CORE_SRC "")

add_subdirectory(Scheduler)
add_subdirectory(PropertyMapper)
add_subdirectory(Logging)
add_subdirectory(Runner)
add_subdirectory(IPC)
add_subdirectory(IDC)
add_subdirectory(protobuf)
add_subdirectory(Object)
add_subdirectory(TimeProvider)
add_subdirectory(Framework)
add_subdirectory(DataPresentation)
add_subdirectory(Frames)

set(CORE_SRC 	${CORE_SRC}
				${CMAKE_CURRENT_SOURCE_DIR}/LinearAlgebra.cpp
				${CMAKE_CURRENT_SOURCE_DIR}/SensorData.cpp
				)
				
				
include_directories(${CMAKE_SOURCE_DIR}/uavAP/Core/protobuf/messages)

add_library(uavap_core SHARED ${CORE_SRC})

target_link_libraries(uavap_core 	${BOOST}
									${PROTOBUF}
									pthread
									rt
									dl									
									)
									
									
install(TARGETS uavap_core 
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib)
