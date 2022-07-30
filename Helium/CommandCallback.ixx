/*
* Helium is a customizable extension system for Minecraft server.
* You can get the lastest source code and releases of Helium at :
* https://github.com/Minecraft1248/Helium
* ----------------------------------------------------------------------------------------
* Helium Copyright (C) 2021-2022 HeliumDevTeam
*
* This file is a part of Helium
*
* Helium is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Helium is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Helium.  If not, see <https://www.gnu.org/licenses/>.
* ----------------------------------------------------------------------------------------
*/

module;

#include<any>
#include<list>

export module Helium.CommandCallback;

import <string>;
import Helium.Logger;

using namespace std;

export {
	namespace Helium {
		int helium_command_bind_create(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_command_bind_detail(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_command_bind_delete(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_command_bind_list(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_command_detail(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_command_list(string rawcmd, string sender, int permission, list<any> arguments);

		int helium_event_block_extension(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_event_block_extension_all(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_event_block_global(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_event_block_global_all(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_event_block_server(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_event_block_server_all(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_event_create(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_event_detail(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_event_list(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_event_trace(string rawcmd, string sender, int permission, list<any> arguments);

		int helium_extension_detail(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_extension_list(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_extension_load(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_extension_lock(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_extension_unload(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_extension_unlock(string rawcmd, string sender, int permission, list<any> arguments);

		int helium_exit(string rawcmd, string sender, int permission, list<any> arguments);
		
		int helium_permission_default(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_permission_query(string rawcmd, string sender, int permission, list<any> arguments);
		
		int helium_reload_all(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_reload_config(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_reload_extconfig(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_reload_extconfig_all(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_reload_extension(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_reload_extension_all(string rawcmd, string sender, int permission, list<any> arguments);

		int helium_server_activate_add(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_server_activate_add_all(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_server_activate_remove(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_server_activate_remove_all(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_server_activate_list(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_server_detail(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_server_list(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_server_pause(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_server_pause_all(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_server_resume(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_server_resume_all(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_server_start(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_server_start_all(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_server_stop(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_server_stop_all(string rawcmd, string sender, int permission, list<any> arguments);

		int helium_show_warranty(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_show_condition(string rawcmd, string sender, int permission, list<any> arguments);
		
		int helium_status(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_update(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_version(string rawcmd, string sender, int permission, list<any> arguments);
		int helium_exit(string rawcmd, string sender, int permission, list<any> arguments);
		
		
		int help_documentation(string rawcmd, string sender, int permission, list<any> arguments);
		int help_manual(string rawcmd, string sender, int permission, list<any> arguments);

		int helium_command_bind_create(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "Get Arguments : " << hendl;
			for (auto str : arguments) {
				log << any_cast<string>(str) << hendl;
			}
			return 0;
		}
		int helium_command_bind_detail(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_command_bind_detail" << hendl;
			return 0;
		}
		int helium_command_bind_delete(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_command_bind_delete" << hendl;
			return 0;
		}
		int helium_command_bind_list(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_command_bind_list" << hendl;
			return 0;
		}
		int helium_command_detail(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_command_detail" << hendl;
			return 0;
		}
		int helium_command_list(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_command_list" << hendl;
			return 0;
		}

		int helium_event_block_extension(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_event_block_extension" << hendl;
			return 0;
		}
		int helium_event_block_extension_all(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_event_block_extension_all" << hendl;
			return 0;
		}
		int helium_event_block_global(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_event_block_global" << hendl;
			return 0;
		}
		int helium_event_block_global_all(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_event_block_global_all" << hendl;
			return 0;
		}
		int helium_event_block_server(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_event_block_server" << hendl;
			return 0;
		}
		int helium_event_block_server_all(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_event_block_server_all" << hendl;
			return 0;
		}
		int helium_event_create(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_event_create" << hendl;
			return 0;
		}
		int helium_event_detail(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_event_detail" << hendl;
			return 0;
		}
		int helium_event_list(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_event_list" << hendl;
			return 0;
		}
		int helium_event_trace(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_event_trace" << hendl;
			return 0;
		}

		int helium_extension_detail(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_extension_detail" << hendl;
			return 0;
		}
		int helium_extension_list(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_extension_list" << hendl;
			return 0;
		}
		int helium_extension_load(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_extension_load" << hendl;
			return 0;
		}
		int helium_extension_lock(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_extension_lock" << hendl;
			return 0;
		}
		int helium_extension_unload(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_extension_unload" << hendl;
			return 0;
		}
		int helium_extension_unlock(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_extension_unlock" << hendl;
			return 0;
		}

		int helium_exit(string rawcmd, string sender, int permission, list<any> arguments) {
			log << HLL::LL_INFO << "Exiting Helium...helium_exit" << hendl;
			exit(0);
			terminate();
		}

		int helium_permission_default(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_permission_default" << hendl;
			return 0;
		}
		int helium_permission_query(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_permission_query" << hendl;
			return 0;
		}

		int helium_reload_all(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_reload_all" << hendl;
			return 0;
		}
		int helium_reload_config(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_reload_config" << hendl;
			return 0;
		}
		int helium_reload_extconfig(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_reload_extconfig" << hendl;
			return 0;
		}
		int helium_reload_extconfig_all(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_reload_extconfig_all" << hendl;
			return 0;
		}
		int helium_reload_extension(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_reload_extension" << hendl;
			return 0;
		}
		int helium_reload_extension_all(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_reload_extension_all" << hendl;
			return 0;
		}

		int helium_server_activate_add(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_activate_add" << hendl;
			return 0;
		}
		int helium_server_activate_add_all(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_activate_add_all" << hendl;
			return 0;
		}
		int helium_server_activate_remove(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_activate_remove" << hendl;
			return 0;
		}
		int helium_server_activate_remove_all(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_activate_remove_all" << hendl;
			return 0;
		}
		int helium_server_activate_list(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_activate_list" << hendl;
			return 0;
		}
		int helium_server_detail(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_detail" << hendl;
			return 0;
		}
		int helium_server_list(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_list" << hendl;
			return 0;
		}
		int helium_server_pause(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_pause" << hendl;
			return 0;
		}
		int helium_server_pause_all(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_pause_all" << hendl;
			return 0;
		}
		int helium_server_resume(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_resume" << hendl;
			return 0;
		}
		int helium_server_resume_all(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_resume_all" << hendl;
			return 0;
		}
		int helium_server_start(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_start" << hendl;
			return 0;
		}
		int helium_server_start_all(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_start_all" << hendl;
			return 0;
		}
		int helium_server_stop(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_stop" << hendl;
			return 0;
		}
		int helium_server_stop_all(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_stop_all" << hendl;
			return 0;
		}

		int helium_show_warranty(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;

			log << HLL::LL_INFO << "Disclaimer of Warranty." << hendl;
			log << HLL::LL_INFO << "THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW." << hendl;
			log << HLL::LL_INFO << "EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER" << hendl;
			log << HLL::LL_INFO << "PARTIES PROVIDE THE PROGRAM ¡°AS IS¡± WITHOUT WARRANTY OF ANY KIND, EITHER" << hendl;
			log << HLL::LL_INFO << "EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF" << hendl;
			log << HLL::LL_INFO << "MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE" << hendl;
			log << HLL::LL_INFO << "QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE" << hendl;
			log << HLL::LL_INFO << "DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION." << hendl;

			return 0;
		}
		int helium_show_condition(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;



			return 0;
		}

		int helium_status(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_status" << hendl;
			return 0;
		}
		int helium_update(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_update" << hendl;
			return 0;
		}
		int helium_version(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_version" << hendl;
			return 0;
		}


		int help_documentation(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "Helium Documentation : https://helium-devteam.github.io/Helium-User-Document/" << hendl;
			return 0;
		}
		int help_manual(string rawcmd, string sender, int permission, list<any> arguments) {
			HeliumEndline hendl;
			log << HLL::LL_INFO << "Argument : " << any_cast<string>(arguments.front()) << hendl;
			return 0;
		}
	}
}