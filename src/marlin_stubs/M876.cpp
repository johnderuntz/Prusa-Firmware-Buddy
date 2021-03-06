/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include "../../lib/Marlin/Marlin/src/inc/MarlinConfig.h"

#if ENABLED(HOST_PROMPT_SUPPORT) && DISABLED(EMERGENCY_PARSER)

    #include "../../lib/Marlin/Marlin/src/feature/host_actions.h"
    #include "../../lib/Marlin/Marlin/src/feature/safety_timer.h"
    #include "../../lib/Marlin/Marlin/src/gcode/gcode.h"
    #include "../../lib/Marlin/Marlin/src/Marlin.h"
    #include "marlin_server.hpp"

/**
 * M876: Handle Prompt Response
 */
void GcodeSuite::M876() {
    if (parser.seenval('P')) {
        if (parser.value_int()) {
            fsm_create(ClientFSM::Serial_printing, 0);
        } else {
            fsm_destroy(ClientFSM::Serial_printing);
            safety_timer_set_interval(1800000); //in miliseconds
        }
    }
    if (parser.seenval('S'))
        host_response_handler((uint8_t)parser.value_int());
}

#endif // HOST_PROMPT_SUPPORT && !EMERGENCY_PARSER
