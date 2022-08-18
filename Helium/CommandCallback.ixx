/*
* Helium is a customizable extension system for Minecraft server.
* You can get the lastest source code and releases of Helium at :
* https://github.com/Helium-DevTeam/Helium
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

export module Helium.CommandCallback;

import <any>;
import <list>;
import <string>;
import Helium.Logger;
import Helium.Events;
import Helium.Extension;
import Helium.Version;
import Helium.MinecraftServer;

using namespace std;

export {
	namespace Helium {
		int helium_command_bind_create(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_command_bind_detail(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_command_bind_delete(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_command_bind_list(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_command_detail(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_command_list(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);

		int helium_event_block_extension(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_event_block_extension_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_event_block_global(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_event_block_global_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_event_block_server(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_event_block_server_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_event_create(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_event_detail(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_event_list(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_event_trace(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);

		int helium_extension_detail(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_extension_list(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_extension_load(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_extension_lock(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_extension_unload(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_extension_unlock(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_extension_install(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_extension_update(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_extension_uninstall(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);

		int helium_permission_default(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_permission_query(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);

		int helium_reload_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_reload_config(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_reload_extconfig(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_reload_extconfig_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_reload_extension(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_reload_extension_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);

		int helium_server_activate_add(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_server_activate_add_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_server_activate_remove(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_server_activate_remove_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_server_activate_list(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_server_detail(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_server_list(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_server_pause(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_server_pause_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_server_resume(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_server_resume_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_server_start(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_server_start_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_server_stop(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_server_stop_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);

		int helium_show_warranty(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_show_condition(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);

		int helium_status(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_update(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_version(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int helium_exit(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);

		int help_documentation(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int help_manual(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
		int root_exit(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments);
	}
}

namespace Helium {
	int helium_command_bind_create(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "Get Arguments : " << hendl;
		for (auto str : arguments) {
			log << any_cast<const string&>(str) << hendl;
		}
		return 0;
	}
	int helium_command_bind_detail(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_command_bind_detail" << hendl;
		return 0;
	}
	int helium_command_bind_delete(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_command_bind_delete" << hendl;
		return 0;
	}
	int helium_command_bind_list(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_command_bind_list" << hendl;
		return 0;
	}
	int helium_command_detail(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_command_detail" << hendl;
		return 0;
	}
	int helium_command_list(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_command_list" << hendl;
		return 0;
	}

	int helium_event_block_extension(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_event_block_extension" << hendl;
		return 0;
	}
	int helium_event_block_extension_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_event_block_extension_all" << hendl;
		return 0;
	}
	int helium_event_block_global(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_event_block_global" << hendl;
		return 0;
	}
	int helium_event_block_global_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_event_block_global_all" << hendl;
		return 0;
	}
	int helium_event_block_server(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_event_block_server" << hendl;
		return 0;
	}
	int helium_event_block_server_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_event_block_server_all" << hendl;
		return 0;
	}
	int helium_event_create(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		long event_id;
		try {
			event_id = any_cast<long>(arguments.front());
		}
		catch (exception& e) {
			log << HLL::LL_ERR << "Unable to cast the arguments : "
				<< e.what() << hendl;
			return -1;
		}
		log << HLL::LL_INFO << "Creating event " << EventIDToDesc(event_id)
			<< "(" << event_id << ")" << hendl;
		list<any> temp_param;
		helium_event_manager.DispatchEvent(event_id, temp_param);
		return 0;
	}
	int helium_event_detail(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_event_detail" << hendl;
		return 0;
	}
	int helium_event_list(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_event_list" << hendl;
		return 0;
	}
	int helium_event_trace(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		long event_id = any_cast<long>(arguments.front());
		if (helium_event_manager.IsEventTraced(event_id)) {
			helium_event_manager.UntraceEvent(event_id);
			log << HLL::LL_INFO << "Untracing event " << EventIDToDesc(event_id)
				<< "(" << event_id << ")" << hendl;
		}
		else {
			helium_event_manager.TraceEvent(event_id);
			log << HLL::LL_INFO << "Tracing event " << EventIDToDesc(event_id)
				<< "(" << event_id << ")" << hendl;
		}
		return 0;
	}

	int helium_extension_detail(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_extension_detail" << hendl;
		return 0;
	}
	int helium_extension_list(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_extension_list" << hendl;
		return 0;
	}
	int helium_extension_load(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_extension_load" << hendl;
		return 0;
	}
	int helium_extension_lock(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_extension_lock" << hendl;
		return 0;
	}
	int helium_extension_unload(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_extension_unload" << hendl;
		return 0;
	}
	int helium_extension_unlock(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_extension_unlock" << hendl;
		return 0;
	}
	int helium_extension_install(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_extension_unlock" << hendl;
		return 0;
	}
	int helium_extension_update(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_extension_unlock" << hendl;
		return 0;
	}
	int helium_extension_uninstall(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_extension_unlock" << hendl;
		return 0;
	}

	int helium_permission_default(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_permission_default" << hendl;
		return 0;
	}
	int helium_permission_query(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_permission_query" << hendl;
		return 0;
	}

	int helium_reload_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_reload_all" << hendl;
		return 0;
	}
	int helium_reload_config(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_reload_config" << hendl;
		return 0;
	}
	int helium_reload_extconfig(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_reload_extconfig" << hendl;
		return 0;
	}
	int helium_reload_extconfig_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_reload_extconfig_all" << hendl;
		return 0;
	}
	int helium_reload_extension(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_reload_extension" << hendl;
		return 0;
	}
	int helium_reload_extension_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_reload_extension_all" << hendl;
		return 0;
	}

	int helium_server_activate_add(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_activate_add" << hendl;
		return 0;
	}
	int helium_server_activate_add_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_activate_add_all" << hendl;
		return 0;
	}
	int helium_server_activate_remove(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_activate_remove" << hendl;
		return 0;
	}
	int helium_server_activate_remove_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_activate_remove_all" << hendl;
		return 0;
	}
	int helium_server_activate_list(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_activate_list" << hendl;
		return 0;
	}
	int helium_server_detail(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_detail" << hendl;
		return 0;
	}
	int helium_server_list(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_list" << hendl;
		return 0;
	}
	int helium_server_pause(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_pause" << hendl;
		return 0;
	}
	int helium_server_pause_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_pause_all" << hendl;
		return 0;
	}
	int helium_server_resume(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_resume" << hendl;
		return 0;
	}
	int helium_server_resume_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_resume_all" << hendl;
		return 0;
	}
	int helium_server_start(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_start" << hendl;
		return 0;
	}
	int helium_server_start_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_start_all" << hendl;
		return 0;
	}
	int helium_server_stop(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_stop" << hendl;
		return 0;
	}
	int helium_server_stop_all(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_server_stop_all" << hendl;
		return 0;
	}

	int helium_show_warranty(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
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
	int helium_show_condition(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING WILL ANY" << hendl;
		log << HLL::LL_INFO << "COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MODIFIES AND/OR CONVEYS THE PROGRAM" << hendl;
		log << HLL::LL_INFO << "AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES, INCLUDING ANY GENERAL, SPECIAL," << hendl;
		log << HLL::LL_INFO << "INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OR INABILITY TO USE THE" << hendl;
		log << HLL::LL_INFO << "PROGRAM (INCLUDING BUT NOT LIMITED TO LOSS OF DATA OR DATA BEING RENDERED" << hendl;
		log << HLL::LL_INFO << "INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM" << hendl;
		log << HLL::LL_INFO << "TO OPERATE WITH ANY OTHER PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN" << hendl;
		log << HLL::LL_INFO << "ADVISED OF THE POSSIBILITY OF SUCH DAMAGES." << hendl;
		return 0;
	}

	int helium_status(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_status" << hendl;
		return 0;
	}
	int helium_update(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_update" << hendl;
		return 0;
	}
	int helium_version(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "This command hasn't been implemented yet :(helium_version" << hendl;
		return 0;
	}

	int help_documentation(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "Helium Documentation : https://helium-devteam.github.io/Helium-User-Document/" << hendl;
		return 0;
	}
	int help_manual(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		log << HLL::LL_INFO << "Argument : " << any_cast<const string&>(arguments.front()) << hendl;
		return 0;
	}

	int root_exit(const string& rawcmd, const string& sender, const int& permission, const list<any>& arguments) {
		list<any> param;
		any temp_any;
		temp_any = GetHeliumVersion();
		param.push_back(temp_any);
		helium_event_manager.DispatchEvent(HeliumEventList::HELIUM_STOP, param);
		StopAllServer();
		UnloadAllExtension();
		log << HLL::LL_INFO << "Exiting Helium." << hendl;
		::exit(0);
		return 0;
	}
}