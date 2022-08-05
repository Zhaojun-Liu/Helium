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

#include"tree.hh/tree.hh"
#include"replxx/replxx.hxx"
#include<boost/uuid/uuid.hpp>
#include<boost/uuid/uuid_io.hpp>
#include<boost/uuid/uuid_generators.hpp>

#include"tree.hh/tree.hh"
#define REPLXX_STATIC
#include"replxx/replxx.hxx"

export module Helium.Commands;

import <string>;
import <regex>;
import <iostream>;
import <sstream>;
import <any>;
import <map>;
import <list>;
import <iostream>;
import <functional>;

import Helium.Config;
import Helium.Events;
import Helium.Extension;
import Helium.MinecraftServer;
import Helium.Utils;
import Helium.Logger;
import Helium.CommandCallback;
import Helium.CommandQueue;

using namespace std;
using namespace replxx;
using namespace placeholders;
using namespace boost::uuids;

export{
	namespace Helium {
		class _BasicHeliumCommand;
		class _CommandConstantString;
		class _CommandArgument;

		class ConstantString;

		class _ArgumentNumber;
		class CommandArgumentInt;
		class CommandArgumentFloat;
		class _ArgumentString;
		class CommandArgumentString;
		class CommandArgumentQuotableString;
		class CommandArgumentGreedyString;
		class CommandArgumentAny;

		class _CommandEntry;
		class CommandEntry;

		class _CommandBind;
		class CommandBind;

		tree<_BasicHeliumCommand*> HeliumCommandTree;
		Replxx rx;

		int InitShellEnv();
		int InitShell(string prompt);
		int FinShell();
		int InitBuiltinCommandTree();
		Replxx::hints_t HintCallBack(string const& context, int& len, Replxx::Color& color);
		Replxx::completions_t CompletionCallBack(string const& context, int& len);
		Replxx::ACTION_RESULT KeyMessage(Replxx& replxx, std::string s, char32_t);
		
		tree<_BasicHeliumCommand*>::pre_order_iterator 
			AddCommand(_BasicHeliumCommand* cmd, uuid parentuuid);
		tree<_BasicHeliumCommand*>::pre_order_iterator 
			AddCommand(_BasicHeliumCommand* cmd, tree<_BasicHeliumCommand*>::pre_order_iterator parentit = HeliumCommandTree.begin());
		tree<_BasicHeliumCommand*>::pre_order_iterator 
			InsertCommand(_BasicHeliumCommand* cmd, uuid parentuuid);
		tree<_BasicHeliumCommand*>::pre_order_iterator 
			InsertCommand(_BasicHeliumCommand* cmd, tree<_BasicHeliumCommand*>::pre_order_iterator tit = HeliumCommandTree.begin());
		tree<_BasicHeliumCommand*>::pre_order_iterator 
			AddCommandTree(tree<_BasicHeliumCommand*>::pre_order_iterator subtree, uuid parentuuid);
		tree<_BasicHeliumCommand*>::pre_order_iterator 
			AddCommandTree(tree<_BasicHeliumCommand*>::pre_order_iterator subtree, tree<_BasicHeliumCommand*>::pre_order_iterator parentit = HeliumCommandTree.begin());
		tree<_BasicHeliumCommand*>::pre_order_iterator 
			DeleteCommand(uuid uuid);
		tree<_BasicHeliumCommand*>::pre_order_iterator 
			DeleteCommand(tree<_BasicHeliumCommand*>::pre_order_iterator it);
		tree<_BasicHeliumCommand*>::pre_order_iterator 
			DeleteCommandTree(uuid uuid);
		tree<_BasicHeliumCommand*>::pre_order_iterator 
			DeleteCommandTree(tree<_BasicHeliumCommand*>::pre_order_iterator it);
		tree<_BasicHeliumCommand*>::pre_order_iterator 
			QueryCommand(uuid uuid, tree<_BasicHeliumCommand*>::pre_order_iterator = HeliumCommandTree.begin());
		tree<_BasicHeliumCommand*>::pre_order_iterator 
			QueryCommand(string commandstr, tree<_BasicHeliumCommand*>::pre_order_iterator = HeliumCommandTree.begin());
		tree<_BasicHeliumCommand*>::pre_order_iterator 
			ReplaceCommand(uuid uuid, _BasicHeliumCommand* cmd);
		tree<_BasicHeliumCommand*>::pre_order_iterator 
			ReplaceCommand(tree<_BasicHeliumCommand*>::pre_order_iterator it, _BasicHeliumCommand* cmd);
		tree<_BasicHeliumCommand*>::pre_order_iterator 
			ReplaceCommandTree(uuid uuid, tree<_BasicHeliumCommand*>::pre_order_iterator subtree);
		tree<_BasicHeliumCommand*>::pre_order_iterator 
			ReplaceCommandTree(tree<_BasicHeliumCommand*>::pre_order_iterator it, tree<_BasicHeliumCommand*>::pre_order_iterator subtree);

		int ExecuteCommand(string rawcmd, string sender, int permission, string servername = "");
		int PlayerInput(list<any> param);

		typedef int (*HeliumCommandCallback)(string rawcmd, string sender, int permission, list<any> arguments);

#pragma region CommandClassBase
		class _BasicHeliumCommand {
		protected:
			uuid cmduuid;
		public:
			_BasicHeliumCommand() {
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}
			virtual ~_BasicHeliumCommand() {}

			virtual uuid CommandUUID();

			virtual bool IsValid();
		};
		class _CommandArgument : public _BasicHeliumCommand {
		protected:
			bool optional;
			bool preprocenable;
			
			string argudesc;
		public:
			_CommandArgument() {
				this->argudesc = "DefaultArgumentDescription";
				this->optional = false;
				this->preprocenable = false;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}
			_CommandArgument(string desc
				, bool op = false
				, bool preproc = true) {
				this->argudesc = desc;
				this->optional = op;
				this->preprocenable = preproc;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}

			virtual bool IsOptional();
			virtual bool EnableOptional();
			virtual bool DisableOptional();

			virtual bool IsPreproc();
			virtual bool EnablePreproc();
			virtual bool DisablePreproc();

			virtual string GetArgumentDesc();
			virtual string SetArgumentDesc(string desc);
		};
		class _CommandConstantString : public _BasicHeliumCommand {
		public:
			virtual bool IsCallbackable();
			virtual bool EnableCallback();
			virtual bool DisableCallback();

			virtual bool IsListable();
			virtual bool EnableList();
			virtual bool DisableList();

			virtual bool IsExecutable();
			virtual bool EnableExecute();
			virtual bool DisableExecute();

			virtual bool IsHintable();
			virtual bool EnableHint();
			virtual bool DisableHint();

			virtual bool IsCompletable();
			virtual bool EnableCompletion();
			virtual bool DisableCompletion();

			virtual HeliumPermissionLevel GetCommandPermission();
			virtual HeliumPermissionLevel SetCommandPermission(HeliumPermissionLevel perm);

			virtual string GetCommandString();
			virtual string SetCommandString(string cmd);

			virtual string GetCommandDesc();
			virtual string SetCommandDesc(string hint);

			virtual string GetCommandAlias();
			virtual string SetCommandAlias(string alias);

			virtual bool IsValid();

			_CommandConstantString() {
				this->commanddesc = "Default Command Description";
				this->commandstr = "DefaultCMD";
				this->alias = "DCMD";
				this->callback = false;
				this->list = true;
				this->exec = false;
				this->hint = true;
				this->autocomp = true;
				this->level = HeliumPermissionLevel::HELIUMOWNER;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}
			_CommandConstantString(string desc
				, string str
				, string alias
				, HeliumPermissionLevel perm
				, bool callback = true
				, bool list = true
				, bool exec = true
				, bool hint = true
				, bool autocomp = true) {
				this->commanddesc = desc;
				this->commandstr = str;
				this->alias = alias;
				this->callback = callback;
				this->list = list;
				this->exec = exec;
				this->hint = hint;
				this->autocomp = autocomp;
				this->level = perm;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}
			_CommandConstantString(string desc
				, string str
				, string alias = "") {
				this->commanddesc = desc;
				this->commandstr = str;
				this->alias = alias;
				this->callback = false;
				this->list = true;
				this->exec = true;
				this->hint = true;
				this->autocomp = true;
				this->level = HPL::HELIUMOWNER;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}
		protected:
			bool callback;
			bool list;
			bool exec;
			bool hint;
			bool autocomp;

			string commanddesc;
			string commandstr;
			string alias;

			HeliumPermissionLevel level;
		};


		class _CommandBind : public _CommandConstantString {

		};
		class _ArgumentString : public _CommandArgument {
		public:
			_ArgumentString() {
				this->argudesc = "DefaultArgumentDescription";
				this->optional = false;
				this->preprocenable = false;
				this->lengthlim = 0;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}
			_ArgumentString(string desc
				, unsigned long lengthlim = 0
				, bool op = false
				, bool preproc = true) {
				this->argudesc = desc;
				this->optional = op;
				this->preprocenable = preproc;
				this->lengthlim = lengthlim;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}

			virtual unsigned long GetLengthLimit();
			virtual unsigned long SetLengthLimit(unsigned long lim);
		protected:
			unsigned long lengthlim;
		};
#pragma endregion

		class CommandArgumentInt : public _CommandArgument {
		public:
			CommandArgumentInt() {
				this->argudesc = "DefaultArgumentDescription";
				this->optional = false;
				this->preprocenable = false;
				this->upperbound = 0;
				this->lowerbound = 0;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}
			CommandArgumentInt(string desc
				, bool op = false
				, bool preproc = true
				, long upperbound = 0
				, long lowerbound = 0) {
				this->argudesc = desc;
				this->optional = op;
				this->preprocenable = preproc;
				this->upperbound = upperbound;
				this->lowerbound = lowerbound;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}

			virtual long SetUpperbound(long up);
			virtual long SetLowerbound(long down);
			virtual long GetUpperbound();
			virtual long GetLowerbound();
		protected:
			long upperbound;
			long lowerbound;
		};
		class CommandArgumentFloat : public _CommandArgument {
		public:
			CommandArgumentFloat() {
				this->argudesc = "DefaultArgumentDescription";
				this->optional = false;
				this->preprocenable = false;
				this->upperbound = 0;
				this->lowerbound = 0;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}
			CommandArgumentFloat(string desc
				, bool op = false
				, bool preproc = true
				, double upperbound = 0
				, double lowerbound = 0) {
				this->argudesc = desc;
				this->optional = op;
				this->preprocenable = preproc;
				this->upperbound = upperbound;
				this->lowerbound = lowerbound;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}

			virtual double SetUpperbound(double up);
			virtual double SetLowerbound(double down);
			virtual double GetUpperbound();
			virtual double GetLowerbound();
		protected:
			double upperbound;
			double lowerbound;
		};
		class CommandArgumentBool : public _CommandArgument {
			CommandArgumentBool() {
				this->argudesc = "DefaultArgumentDescription";
				this->optional = false;
				this->preprocenable = false;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}
			CommandArgumentBool(string desc
				, bool op = false
				, bool preproc = true) {
				this->argudesc = desc;
				this->optional = op;
				this->preprocenable = preproc;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}
		};
		class CommandArgumentString : public _ArgumentString {
		public:
			CommandArgumentString() {
				this->argudesc = "DefaultArgumentDescription";
				this->optional = false;
				this->preprocenable = false;
				this->lengthlim = 0;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}
			CommandArgumentString(string desc
				, unsigned long lengthlim = 0
				, bool op = false
				, bool preproc = true) {
				this->argudesc = desc;
				this->optional = op;
				this->preprocenable = preproc;
				this->lengthlim = lengthlim;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}
		};
		class CommandArgumentQuotableString : public _ArgumentString {
		public:
			CommandArgumentQuotableString() {
				this->argudesc = "DefaultArgumentDescription";
				this->optional = false;
				this->preprocenable = false;
				this->lengthlim = 0;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}
			CommandArgumentQuotableString(string desc
				, unsigned long lengthlim = 0
				, bool op = false
				, bool preproc = true) {
				this->argudesc = desc;
				this->optional = op;
				this->preprocenable = preproc;
				this->lengthlim = lengthlim;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}
		};
		class CommandBind : public _CommandBind {

		};
		class ConstantString : public _CommandConstantString {
			friend int ExecuteCommand(string rawcmd, string sender, int permission, string servername);
		public:
			ConstantString() {
				this->commanddesc = "Default Command Description";
				this->commandstr = "DefaultCMD";
				this->callback = false;
				this->list = true;
				this->exec = false;
				this->hint = true;
				this->autocomp = true;
				this->level = HeliumPermissionLevel::HELIUMOWNER;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}
			ConstantString(string desc
				, string str
				, string alias
				, HeliumPermissionLevel perm
				, bool callback = true
				, bool list = true
				, bool exec = true
				, bool hint = true
				, bool autocomp = true) {
				this->commanddesc = desc;
				this->commandstr = str;
				this->alias = alias;
				this->callback = callback;
				this->list = list;
				this->exec = exec;
				this->hint = hint;
				this->autocomp = autocomp;
				this->level = perm;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}
			ConstantString(string desc
				, string str
				, string alias = "") {
				this->commanddesc = desc;
				this->commandstr = str;
				this->alias = alias;
				this->callback = false;
				this->list = true;
				this->exec = true;
				this->hint = true;
				this->autocomp = true;
				this->level = HPL::HELIUMOWNER;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}

			virtual void AddCallback(HeliumCommandCallback fnptr);
		protected:
			std::list<HeliumCommandCallback> fnlist;
		};

		void print_tree(const tree<_BasicHeliumCommand*>& tr)
		{
			auto it = tr.begin();
			auto end = tr.end();
			if (!tr.is_valid(it)) return;
			int rootdepth = tr.depth(it);
			while (it != end) {
				if (typeid((**it)) == typeid(_BasicHeliumCommand)) {
					++it;
					continue;
				}
				if (typeid((**it)) == typeid(ConstantString)) {
					for (int i = 0; i < tr.depth(it) - rootdepth; ++i)
						cout << "  ";
					if (!(static_cast<ConstantString*>(*it)->GetCommandAlias().empty()))
						cout << static_cast<ConstantString*>(*it)->GetCommandString() << "/" << static_cast<ConstantString*>(*it)->GetCommandAlias() << endl;
					else
						cout << static_cast<ConstantString*>(*it)->GetCommandString() << endl;
				}
				else {
					for (int i = 0; i < tr.depth(it) - rootdepth; ++i)
						cout << "  ";
					if (static_cast<_CommandArgument*>(*it)->IsOptional())
						cout << '[' << static_cast<_CommandArgument*>(*it)->GetArgumentDesc() << ']' << endl;
					else
						cout << '<' << static_cast<_CommandArgument*>(*it)->GetArgumentDesc() << '>' << endl;
				}
				++it;
			}
		}
		bool IsStringEqual(string l, string r) {
			bool same = true;
			for (int i = 0; same && (i < r.length()); i++) {
				same = (towlower(l[i]) == towlower(r[i]));
			}
			return same;
		}
		Replxx::hints_t HintCallBack(string const& context, int& len, Replxx::Color& color) {
			Replxx::hints_t h;
			vector<string> splited;
			istringstream iss(context);
			string word, beforeword = context.substr(0, context.length() - len);
			tree<_BasicHeliumCommand*>::fixed_depth_iterator pit = HeliumCommandTree.begin();
			tree<_BasicHeliumCommand*>::fixed_depth_iterator tit;
			while (iss >> word) {
				splited.push_back(word);
			}

			if (splited.empty()) return h;
			if (beforeword.length() > 0 && len <= 0)
				if (beforeword[beforeword.length() - 1] == ' ') return h;
			if (splited.back().length() < 2) return h;

			for (auto it = splited.begin(); it < splited.end(); it++) {
				string currword = *it;
				if (it + 1 == splited.end()) {
					for (tit = HeliumCommandTree.begin_fixed(pit, 1);
						HeliumCommandTree.is_valid(tit) && (*(HeliumCommandTree.parent(tit)))->CommandUUID() == (*pit)->CommandUUID();
						tit++) {
						if (typeid((**tit)) != typeid(ConstantString)) continue;
						if (!(static_cast<ConstantString*>(*tit)->IsHintable()))continue;
						string command = static_cast<ConstantString*>(*tit)->GetCommandString();
						if (IsStringEqual(command, currword)) {
							h.emplace_back(command.c_str());
						}
					}
					if (h.size() == 1) {
						color = Replxx::Color::GREEN;
					}
				}
				else {
					bool find = false;
					for (tit = HeliumCommandTree.begin_fixed(pit, 1);
						HeliumCommandTree.is_valid(tit) && (*(HeliumCommandTree.parent(tit)))->CommandUUID() == (*pit)->CommandUUID();
						tit++) {
						if (typeid((**tit)) != typeid(ConstantString)) continue;
						string command = static_cast<ConstantString*>(*tit)->GetCommandString();
						string Alias = static_cast<ConstantString*>(*tit)->GetCommandAlias();
						if (*it == command) {
							pit = tit;
							find = true;
							break;
						}
						if (*it == Alias) {
							pit = tit;
							find = true;
							break;
						}
					}
					if (!find) return h;
				}
			}

			return h;
		}
		Replxx::completions_t CompletionCallBack(string const& context, int& len) {
			Replxx::completions_t c;
			vector<string> splited;
			istringstream iss(context);
			string word, beforeword = context.substr(0, context.length() - len);
			tree<_BasicHeliumCommand*>::fixed_depth_iterator pit = HeliumCommandTree.begin();
			tree<_BasicHeliumCommand*>::fixed_depth_iterator tit;
			while (iss >> word) {
				splited.push_back(word);
			}

			if (splited.empty()) {
				for (tit = HeliumCommandTree.begin_fixed(pit, 1);
					HeliumCommandTree.is_valid(tit) && (*(HeliumCommandTree.parent(tit)))->CommandUUID() == (*pit)->CommandUUID();
					tit++) {
					if (typeid((**tit)) != typeid(ConstantString)) continue;
					if (!(static_cast<ConstantString*>(*tit)->IsCompletable())) continue;
					string command = static_cast<ConstantString*>(*tit)->GetCommandString();
					string alias;
					if (!static_cast<ConstantString*>(*tit)->GetCommandAlias().empty()) {
						alias = static_cast<ConstantString*>(*tit)->GetCommandAlias();
						c.emplace_back(alias.c_str(), Replxx::Color::YELLOW);
					}
					c.emplace_back(command.c_str(), Replxx::Color::YELLOW);
					return c;
				}
			}

			if (!beforeword.empty()) {
				if (beforeword[beforeword.length() - 1] == ' ' && len <= 0) {
					for (auto it = splited.begin(); it < splited.end(); it++) {
						bool find = false;
						for (tit = HeliumCommandTree.begin_fixed(pit, 1);
							HeliumCommandTree.is_valid(tit) && (*(HeliumCommandTree.parent(tit)))->CommandUUID() == (*pit)->CommandUUID();
							tit++) {
							if (typeid((**tit)) != typeid(ConstantString)) continue;
							string command = static_cast<ConstantString*>(*tit)->GetCommandString();
							if (*it == command) {
								pit = tit;
								find = true;
								break;
							}
							string alias;
							if (!static_cast<ConstantString*>(*tit)->GetCommandAlias().empty()) {
								alias = static_cast<ConstantString*>(*tit)->GetCommandAlias();
								if (*it == alias) {
									pit = tit;
									find = true;
									break;
								}
							}
						}
						if (!find) return c;
					}
					for (tit = HeliumCommandTree.begin_fixed(pit, 1);
						HeliumCommandTree.is_valid(tit) && (*(HeliumCommandTree.parent(tit)))->CommandUUID() == (*pit)->CommandUUID();
						tit++) {
						if (typeid((**tit)) != typeid(ConstantString)) continue;
						if (!(static_cast<ConstantString*>(*tit)->IsCompletable())) continue;
						string command = static_cast<ConstantString*>(*tit)->GetCommandString();
						string alias = static_cast<ConstantString*>(*tit)->GetCommandAlias();
						c.emplace_back(command.c_str(), Replxx::Color::YELLOW);
						c.emplace_back(alias.c_str(), Replxx::Color::YELLOW);
						return c;
					}
				}
			}

			for (auto it = splited.begin(); it < splited.end(); it++) {
				string currword = *it;
				if (it + 1 == splited.end()) {
					for (tit = HeliumCommandTree.begin_fixed(pit, 1);
						HeliumCommandTree.is_valid(tit) && (*(HeliumCommandTree.parent(tit)))->CommandUUID() == (*pit)->CommandUUID();
						tit++) {
						if (typeid((**tit)) != typeid(ConstantString)) continue;
						string command = static_cast<ConstantString*>(*tit)->GetCommandString();
						if (IsStringEqual(command, currword)) {
							c.emplace_back(command.c_str(), Replxx::Color::YELLOW);
						}
						string alias;
						if (!static_cast<ConstantString*>(*tit)->GetCommandAlias().empty()) {
							alias = static_cast<ConstantString*>(*tit)->GetCommandAlias();
							if (IsStringEqual(alias, currword)) {
								c.emplace_back(alias.c_str(), Replxx::Color::YELLOW);
							}
						}
					}
				}
				else {
					bool find = false;
					for (tit = HeliumCommandTree.begin_fixed(pit, 1);
						HeliumCommandTree.is_valid(tit) && (*(HeliumCommandTree.parent(tit)))->CommandUUID() == (*pit)->CommandUUID();
						tit++) {
						if (typeid((**tit)) != typeid(ConstantString)) continue;
						string command = static_cast<ConstantString*>(*tit)->GetCommandString();
						if (*it == command) {
							pit = tit;
							find = true;
							break;
						}
						string alias;
						if (!static_cast<ConstantString*>(*tit)->GetCommandAlias().empty()) {
							alias = static_cast<ConstantString*>(*tit)->GetCommandAlias();
							if (*it == alias) {
								pit = tit;
								find = true;
								break;
							}
						}
					}
					if (!find) return c;
				}
			}
			return c;
		}
		int InitBuiltinCommandTree() {
			HeliumEndline hendl;

			log << HLL::LL_INFO << "Initializing Helium built-in command tree." << hendl;

			_BasicHeliumCommand* treeroot = new _BasicHeliumCommand();
			HeliumCommandTree.set_head(treeroot);

			const auto howner = HPL::HELIUMOWNER;
			const auto sowner = HPL::SERVEROWNER;
			const auto admin = HPL::ADMIN;
			const auto user = HPL::USER;
			const auto guest = HPL::GUEST;

			auto root = new ConstantString("Helium Built-in Command \"#helium\"", "#helium", "#hel");
			auto help = new ConstantString("Helium Built-in Command \"#help\"", "#help", "", guest);
			auto rootexit = new ConstantString("Helium Built-in Command \"#exit\"", "#exit", "", guest);

			auto command = new ConstantString("Helium Built-in Command \"command\"", "command", "cmd");
			auto events = new ConstantString("Helium Built-in Command \"event\"", "event", "ent");
			auto extension = new ConstantString("Helium Built-in Command \"extension\"", "extension", "ext");
			auto exit = new ConstantString("Helium Built-in Command \"exit\"", "exit", "");
			auto permission = new ConstantString("Helium Built-in Command\"\"", "permission", "perm");
			auto reload = new ConstantString("Helium Built-in Command \"reload\"", "reload", "rld");
			auto server = new ConstantString("Helium Built-in Command \"server\"", "server", "svr");
			auto show = new ConstantString("Helium Built-in Command \"show\"", "show", "");
			auto status = new ConstantString("Helium Built-in Command \"status\"", "status", "stat", guest);
			auto update = new ConstantString("Helium Built-in Command \"update\"", "update", "upd", admin);
			auto version = new ConstantString("Helium Built-in Command \"version\"", "version", "ver", guest);
			auto document = new ConstantString("Helium Built-in Command \"documentation\"", "documentation", "doc", guest);
			auto manual = new ConstantString("Helium Built-in Command \"manual\"", "manual", "man", guest);

			exit->AddCallback(helium_exit);
			help->AddCallback(helium_command_list);
			status->AddCallback(helium_status);
			update->AddCallback(helium_update);
			version->AddCallback(helium_version);
			document->AddCallback(help_documentation);
			manual->AddCallback(help_manual);

			auto rootit = AddCommand(root);
			auto helpit = AddCommand(help);
			AddCommand(rootexit);

			auto cmdit = AddCommand(command, rootit);
			auto entit = AddCommand(events, rootit);
			auto extit = AddCommand(extension, rootit);
			auto permit = AddCommand(permission, rootit);
			auto rldit = AddCommand(reload, rootit);
			auto svrit = AddCommand(server, rootit);
			auto showit = AddCommand(show, rootit);
			auto manit = AddCommand(manual, helpit);
			AddCommand(exit, rootit);
			AddCommand(status, rootit);
			AddCommand(update, rootit);
			AddCommand(version, rootit);
			AddCommand(document, helpit);

			if (cmdit != HeliumCommandTree.end()) {
				auto bind = new ConstantString("Helium Built-in Command \"bind\"", "bind", "bnd");
				auto detail = new ConstantString("Helium Built-in Command \"detail\"", "detail", "dtl", admin, true);
				auto list = new ConstantString("Helium Built-in Command \"list\"", "list", "lst", user, true);

				detail->AddCallback(helium_command_detail);
				list->AddCallback(helium_command_list);

				auto bindit = AddCommand(bind, cmdit);
				auto detlit = AddCommand(detail, cmdit);
				auto listit = AddCommand(list, cmdit);
				if (bindit != HeliumCommandTree.end()) {
					auto create = new ConstantString("Helium Built-in Command \"create\"", "create", "crt", admin, true);
					auto detail = new ConstantString("Helium Built-in Command \"detail\"", "detail", "dtl", admin, true);
					auto dlt = new ConstantString("Helium Built-in Command \"delete\"", "delete", "dlt", admin, true);
					auto bind_list = new ConstantString("Helium Built-in Command \"list\"", "list", "lst", user, true);

					create->AddCallback(helium_command_bind_create);
					detail->AddCallback(helium_command_bind_detail);
					dlt->AddCallback(helium_command_bind_delete);
					bind_list->AddCallback(helium_command_bind_list);

					auto createit = AddCommand(create, bindit);
					auto detailit = AddCommand(detail, bindit);
					auto deleteit = AddCommand(dlt, bindit);
					AddCommand(bind_list, bindit);

					if (createit != HeliumCommandTree.end()) {
						auto bindedcmd = new CommandArgumentQuotableString("binded_command");
						auto commandtobind = new CommandArgumentQuotableString("command_to_bind");

						auto bindedcmdit = AddCommand(bindedcmd, createit);
						AddCommand(commandtobind, bindedcmdit);
					}
					if (detailit != HeliumCommandTree.end()) {
						auto bindedcmd = new CommandArgumentQuotableString("binded_command");

						AddCommand(bindedcmd, detailit);
					}
					if (deleteit != HeliumCommandTree.end()) {
						auto bindedcmd = new CommandArgumentQuotableString("binded_command");

						AddCommand(bindedcmd, deleteit);
					}
				}
				if (detlit != HeliumCommandTree.end()) {
					auto cmdstr = new CommandArgumentQuotableString("command");

					AddCommand(cmdstr, detlit);
				}
				if (listit != HeliumCommandTree.end()) {
					auto cmdstr = new CommandArgumentQuotableString("command_subtree_parent", 0, true);

					AddCommand(cmdstr, listit);
				}
			}

			if (entit != HeliumCommandTree.end()) {
				auto block = new ConstantString("Helium Built-in Command \"block\"", "block", "blk");
				auto create = new ConstantString("Helium Built-in Command \"create\"", "create", "crt", sowner, true);
				auto detail = new ConstantString("Helium Built-in Command \"detail\"", "detail", "dtl", sowner, true);
				auto list = new ConstantString("Helium Built-in Command \"list\"", "list", "lst", user, true);
				auto trace = new ConstantString("Helium Built-in Command \"trace\"", "trace", "trc", admin, true);

				create->AddCallback(helium_event_create);
				detail->AddCallback(helium_event_detail);
				list->AddCallback(helium_event_list);
				trace->AddCallback(helium_event_trace);

				auto blkit = AddCommand(block, entit);
				auto crtit = AddCommand(create, entit);
				auto detailit = AddCommand(detail, entit);
				auto trcit = AddCommand(trace, entit);
				AddCommand(list, entit);

				if (blkit != HeliumCommandTree.end()) {
					auto blockext = new ConstantString("Helium Built-in Command \"extension\"", "extension", "ext", sowner, true);
					auto blockglobal = new ConstantString("Helium Built-in Command \"global\"", "global", "glb", sowner, true);
					auto blockserver = new ConstantString("Helium Built-in Command \"server\"", "server", "svr", sowner, true);

					blockext->AddCallback(helium_event_block_extension);
					blockglobal->AddCallback(helium_event_block_global);
					blockserver->AddCallback(helium_event_block_server);

					auto beit = AddCommand(blockext, blkit);
					auto bgit = AddCommand(blockglobal, blkit);
					auto bsit = AddCommand(blockserver, blkit);

					if (beit != HeliumCommandTree.end()) {
						auto all = new ConstantString("Helium Built-in Command \"all\"", "all", "", sowner, true);
						auto intarg = new CommandArgumentInt("event_id");

						all->AddCallback(helium_event_block_extension_all);

						AddCommand(all, beit);
						AddCommand(intarg, beit);
					}
					if (bgit != HeliumCommandTree.end()) {
						auto all = new ConstantString("Helium Built-in Command \"all\"", "all", "", sowner, true);
						auto intarg = new CommandArgumentInt("event_id");

						all->AddCallback(helium_event_block_global_all);

						AddCommand(all, bgit);
						AddCommand(intarg, bgit);
					}
					if (bsit != HeliumCommandTree.end()) {
						auto all = new ConstantString("Helium Built-in Command \"all\"", "all", "", sowner, true);
						auto intarg = new CommandArgumentInt("event_id");

						all->AddCallback(helium_event_block_server_all);

						AddCommand(all, bsit);
						AddCommand(intarg, bsit);
					}
				}
				if (crtit != HeliumCommandTree.end()) {
					auto intarg = new CommandArgumentInt("event_id");

					AddCommand(intarg, crtit);
				}
				if (detailit != HeliumCommandTree.end()) {
					auto intarg = new CommandArgumentInt("event_id");

					AddCommand(intarg, detailit);
				}
				if (trcit != HeliumCommandTree.end()) {
					auto intarg = new CommandArgumentInt("event_id");

					AddCommand(intarg, trcit);
				}
			}

			if (extit != HeliumCommandTree.end()) {
				auto detail = new ConstantString("Helium Built-in Command \"detail\"", "detail", "dtl", admin, true);
				auto list = new ConstantString("Helium Built-in Command \"list\"", "list", "lst", user, true);
				auto load = new ConstantString("Helium Built-in Command \"load\"", "load", "ld", admin, true);
				auto lock = new ConstantString("Helium Built-in Command \"lock\"", "lock", "lck", admin, true);
				auto reloadconfig = new ConstantString("Helium Built-in Command \"reloadconfig\"", "reloadconfig", "rldcfg", admin, true);
				auto reloadext = new ConstantString("Helium Built-in Command \"reloadextension\"", "reloadextension", "rldext", admin, true);
				auto unload = new ConstantString("Helium Built-in Command \"unload\"", "unload", "uld", admin, true);
				auto unlock = new ConstantString("Helium Built-in Command \"unlock\"", "unlock", "ulck", admin, true);

				detail->AddCallback(helium_extension_detail);
				list->AddCallback(helium_extension_list);
				load->AddCallback(helium_extension_load);
				lock->AddCallback(helium_extension_lock);
				reloadconfig->AddCallback(helium_reload_extconfig);
				reloadext->AddCallback(helium_reload_extension);
				unload->AddCallback(helium_extension_unload);
				unlock->AddCallback(helium_extension_unlock);

				auto dtlit = AddCommand(detail, extit);
				auto loadit = AddCommand(load, extit);
				auto lockit = AddCommand(lock, extit);
				auto rldcfgit = AddCommand(reloadconfig, extit);
				auto rldextit = AddCommand(reloadext, extit);
				auto unloadit = AddCommand(unload, extit);
				auto unlockit = AddCommand(unlock, extit);
				AddCommand(list, extit);

				if (dtlit != HeliumCommandTree.end()) {
					auto extname = new CommandArgumentString("extension_name");

					AddCommand(extname, dtlit);
				}
				if (loadit != HeliumCommandTree.end()) {
					auto extname = new CommandArgumentString("extension_name");

					AddCommand(extname, loadit);
				}
				if (lockit != HeliumCommandTree.end()) {
					auto extname = new CommandArgumentString("extension_name");

					AddCommand(extname, lockit);
				}
				if (rldcfgit != HeliumCommandTree.end()) {
					auto all = new ConstantString("Helium Built-in Command \"all\"", "all", "", admin, true);
					auto extname = new CommandArgumentString("extension_name");

					all->AddCallback(helium_reload_extconfig_all);

					AddCommand(all, rldcfgit);
					AddCommand(extname, rldcfgit);
				}
				if (rldextit != HeliumCommandTree.end()) {
					auto all = new ConstantString("Helium Built-in Command \"all\"", "all", "", admin, true);
					auto extname = new CommandArgumentString("extension_name");

					all->AddCallback(helium_reload_extension_all);

					AddCommand(all, rldextit);
					AddCommand(extname, rldextit);
				}
				if (unloadit != HeliumCommandTree.end()) {
					auto extname = new CommandArgumentString("extension_name");

					AddCommand(extname, unloadit);
				}
				if (unlockit != HeliumCommandTree.end()) {
					auto extname = new CommandArgumentString("extension_name");

					AddCommand(extname, unlockit);
				}
			}

			if (permit != HeliumCommandTree.end()) {
				auto dft = new ConstantString("Helium Built-in Command \"default\"", "default", "dft", guest, true);
				auto query = new ConstantString("Helium Built-in Command \"query\"", "query", "qry", guest, true);

				dft->AddCallback(helium_permission_default);
				query->AddCallback(helium_permission_query);

				auto dftit = AddCommand(dft, permit);
				auto queryit = AddCommand(query, permit);

				if (dftit != HeliumCommandTree.end()) {
					auto servername = new CommandArgumentString("server_name", true, true);

					AddCommand(servername, dftit);
				}
				if (queryit != HeliumCommandTree.end()) {
					auto servername = new CommandArgumentString("server_name", true, true);
					auto playername = new CommandArgumentString("player_name", true, true);

					auto snit = AddCommand(servername, queryit);
					AddCommand(playername, snit);
				}
			}

			if (rldit != HeliumCommandTree.end()) {
				auto reload_all = new ConstantString("Helium Built-in Command \"all\"", "all", "", admin, true);
				auto reload_config = new ConstantString("Helium Built-in Command \"config\"", "config", "cfg", admin, true);
				auto reload_extconfig = new ConstantString("Helium Built-in Command \"extconfig\"", "extconfig", "extcfg", admin, true);
				auto reload_extension = new ConstantString("Helium Built-in Command \"extension\"", "extension", "ext", admin, true);

				reload_all->AddCallback(helium_reload_all);
				reload_config->AddCallback(helium_reload_config);
				reload_extconfig->AddCallback(helium_reload_extconfig);
				reload_extension->AddCallback(helium_reload_extension);

				AddCommand(reload_all, rldit);
				AddCommand(reload_config, rldit);
				auto ecit = AddCommand(reload_extconfig, rldit);
				auto reit = AddCommand(reload_extension, rldit);

				if (ecit != HeliumCommandTree.end()) {
					auto all = new ConstantString("Helium Built-in Command \"all\"", "all", "", admin, true);
					auto extname = new CommandArgumentString("extension_name");

					all->AddCallback(helium_reload_extconfig_all);

					AddCommand(all, ecit);
					AddCommand(extname, ecit);
				}
				if (reit != HeliumCommandTree.end()) {
					auto all = new ConstantString("Helium Built-in Command \"all\"", "all", "", admin, true);
					auto extname = new CommandArgumentString("extension_name");

					all->AddCallback(helium_reload_extension_all);

					AddCommand(all, reit);
					AddCommand(extname, reit);
				}
			}

			if (svrit != HeliumCommandTree.end()) {
				auto activate = new ConstantString("Helium Built-in Command \"activate\"", "activate", "act");
				auto detail = new ConstantString("Helium Built-in Command \"detail\"", "detail", "dtl", admin, true);
				auto list = new ConstantString("Helium Built-in Command \"list\"", "list", "lst", user, true);
				auto pause = new ConstantString("Helium Built-in Command \"pause\"", "pause", "pse", sowner, true);
				auto resume = new ConstantString("Helium Built-in Command \"resume\"", "resume", "rse", sowner, true);
				auto start = new ConstantString("Helium Built-in Command \"start\"", "start", "srt", sowner, true);
				auto stop = new ConstantString("Helium Built-in Command \"stop\"", "stop", "stp", sowner, true);

				detail->AddCallback(helium_server_detail);
				list->AddCallback(helium_server_list);
				pause->AddCallback(helium_server_pause);
				resume->AddCallback(helium_server_resume);
				start->AddCallback(helium_server_start);
				stop->AddCallback(helium_server_stop);

				auto actit = AddCommand(activate, svrit);
				auto dtlit = AddCommand(detail, svrit);
				auto pauseit = AddCommand(pause, svrit);
				auto resumeit = AddCommand(resume, svrit);
				auto startit = AddCommand(start, svrit);
				auto stopit = AddCommand(stop, svrit);
				AddCommand(list, svrit);

				if (actit != HeliumCommandTree.end()) {
					auto add = new ConstantString("Helium Built-in Command \"add\"", "add", "", admin, true);
					auto remove = new ConstantString("Helium Built-in Command \"remove\"", "remove", "", admin, true);
					auto servername = new CommandArgumentString("server_name");
					auto listact = new ConstantString("Helium Built-in Command \"list\"", "list", "lst", user, true);

					add->AddCallback(helium_server_activate_add);
					remove->AddCallback(helium_server_activate_remove);
					listact->AddCallback(helium_server_activate_list);

					auto addit = AddCommand(add, actit);
					auto removeit = AddCommand(remove, actit);
					AddCommand(listact, actit);

					if (addit != HeliumCommandTree.end()) {
						auto all = new ConstantString("Helium Built-in Command \"all\"", "all", "", admin, true);
						auto servername = new CommandArgumentString("server_name");

						all->AddCallback(helium_server_activate_add_all);

						AddCommand(all, addit);
						AddCommand(servername, addit);
					}
					if (removeit != HeliumCommandTree.end()) {
						auto all = new ConstantString("Helium Built-in Command \"all\"", "all", "", admin, true);
						auto servername = new CommandArgumentString("server_name");

						all->AddCallback(helium_server_activate_remove_all);

						AddCommand(all, removeit);
						AddCommand(servername, removeit);
					}
				}
				if (dtlit != HeliumCommandTree.end()) {
					auto servername = new CommandArgumentString("server_name");

					AddCommand(servername, dtlit);
				}
				if (pauseit != HeliumCommandTree.end()) {
					auto all = new ConstantString("Helium Built-in Command \"all\"", "all", "", admin, true);
					auto servername = new CommandArgumentString("server_name");

					all->AddCallback(helium_server_pause_all);

					AddCommand(all, pauseit);
					AddCommand(servername, pauseit);
				}
				if (resumeit != HeliumCommandTree.end()) {
					auto all = new ConstantString("Helium Built-in Command \"all\"", "all", "", admin, true);
					auto servername = new CommandArgumentString("server_name");

					all->AddCallback(helium_server_resume_all);

					AddCommand(all, resumeit);
					AddCommand(servername, resumeit);
				}
				if (startit != HeliumCommandTree.end()) {
					auto all = new ConstantString("Helium Built-in Command \"all\"", "all", "", admin, true);
					auto servername = new CommandArgumentString("server_name");

					all->AddCallback(helium_server_start_all);

					AddCommand(all, startit);
					AddCommand(servername, startit);
				}
				if (stopit != HeliumCommandTree.end()) {
					auto all = new ConstantString("Helium Built-in Command \"all\"", "all", "", admin, true);
					auto servername = new CommandArgumentString("server_name");

					all->AddCallback(helium_server_stop_all);

					AddCommand(all, stopit);
					AddCommand(servername, stopit);
				}
			}

			if (showit != HeliumCommandTree.end()) {
				auto cond = new ConstantString("Helium Built-in Command \"condition\"", "condition", "cond", guest, true);
				auto warranty = new ConstantString("Helium Built-in Command \"warranty\"", "warranty", "warr", guest, true);

				cond->AddCallback(helium_show_condition);
				warranty->AddCallback(helium_show_warranty);

				AddCommand(cond, showit);
				AddCommand(warranty, showit);
			}

			if (manit != HeliumCommandTree.end()) {
				auto man_cmd = new CommandArgumentQuotableString("command");

				AddCommand(man_cmd, manit);
			}

			log << HLL::LL_INFO << "Helium built-in command tree initialized." << hendl;

			return 0;
		}
		int InitShellEnv() {
			HeliumEndline hendl;

			log << HLL::LL_INFO << "Initializing Helium shell environment." << hendl;

			rx.install_window_change_handler();
			rx.history_load("./commands_history");
			rx.set_max_history_size(256);
			rx.set_max_hint_rows(3);
			rx.set_completion_callback(&CompletionCallBack);
			rx.set_hint_callback(&HintCallBack);
			rx.set_word_break_characters(" ");
			rx.set_completion_count_cutoff(128);
			rx.set_double_tab_completion(false);
			rx.set_complete_on_empty(true);
			rx.set_beep_on_ambiguous_completion(false);
			rx.set_no_color(false);

			rx.bind_key_internal(Replxx::KEY::BACKSPACE, "delete_character_left_of_cursor");
			rx.bind_key_internal(Replxx::KEY::DELETE, "delete_character_under_cursor");
			rx.bind_key_internal(Replxx::KEY::LEFT, "move_cursor_left");
			rx.bind_key_internal(Replxx::KEY::RIGHT, "move_cursor_right");
			rx.bind_key_internal(Replxx::KEY::UP, "history_previous");
			rx.bind_key_internal(Replxx::KEY::DOWN, "history_next");
			rx.bind_key_internal(Replxx::KEY::PAGE_UP, "history_first");
			rx.bind_key_internal(Replxx::KEY::PAGE_DOWN, "history_last");
			rx.bind_key_internal(Replxx::KEY::HOME, "move_cursor_to_begining_of_line");
			rx.bind_key_internal(Replxx::KEY::END, "move_cursor_to_end_of_line");
			rx.bind_key_internal(Replxx::KEY::TAB, "complete_line");
			rx.bind_key_internal(Replxx::KEY::control(Replxx::KEY::LEFT), "move_cursor_one_word_left");
			rx.bind_key_internal(Replxx::KEY::control(Replxx::KEY::RIGHT), "move_cursor_one_word_right");
			rx.bind_key_internal(Replxx::KEY::control(Replxx::KEY::UP), "hint_previous");
			rx.bind_key_internal(Replxx::KEY::control(Replxx::KEY::DOWN), "hint_next");
			rx.bind_key_internal(Replxx::KEY::control(Replxx::KEY::ENTER), "commit_line");
			rx.bind_key_internal(Replxx::KEY::control('R'), "history_incremental_search");
			rx.bind_key_internal(Replxx::KEY::control('W'), "kill_to_begining_of_word");
			rx.bind_key_internal(Replxx::KEY::control('U'), "kill_to_begining_of_line");
			rx.bind_key_internal(Replxx::KEY::control('K'), "kill_to_end_of_line");
			rx.bind_key_internal(Replxx::KEY::control('Y'), "yank");
			rx.bind_key_internal(Replxx::KEY::control('L'), "clear_screen");
			rx.bind_key_internal(Replxx::KEY::control('D'), "send_eof");
			rx.bind_key_internal(Replxx::KEY::control('C'), "abort_line");
			rx.bind_key_internal(Replxx::KEY::control('T'), "transpose_characters");
#ifndef _WIN32
			rx.bind_key_internal(Replxx::KEY::control('V'), "verbatim_insert");
			rx.bind_key_internal(Replxx::KEY::control('Z'), "suspend");
#endif
			rx.bind_key_internal(Replxx::KEY::meta(Replxx::KEY::BACKSPACE), "kill_to_whitespace_on_left");
			rx.bind_key_internal(Replxx::KEY::meta('p'), "history_common_prefix_search");
			rx.bind_key_internal(Replxx::KEY::meta('n'), "history_common_prefix_search");
			rx.bind_key_internal(Replxx::KEY::meta('d'), "kill_to_end_of_word");
			rx.bind_key_internal(Replxx::KEY::meta('y'), "yank_cycle");
			rx.bind_key_internal(Replxx::KEY::meta('u'), "uppercase_word");
			rx.bind_key_internal(Replxx::KEY::meta('l'), "lowercase_word");
			rx.bind_key_internal(Replxx::KEY::meta('c'), "capitalize_word");
			rx.bind_key_internal('a', "insert_character");
			rx.bind_key_internal(Replxx::KEY::INSERT, "toggle_overwrite_mode");
			rx.bind_key(Replxx::KEY::F1, std::bind(&KeyMessage, std::ref(rx), "<F1>", _1));
			rx.bind_key(Replxx::KEY::F2, std::bind(&KeyMessage, std::ref(rx), "<F2>", _1));
			rx.bind_key(Replxx::KEY::F3, std::bind(&KeyMessage, std::ref(rx), "<F3>", _1));
			rx.bind_key(Replxx::KEY::F4, std::bind(&KeyMessage, std::ref(rx), "<F4>", _1));
			rx.bind_key(Replxx::KEY::F5, std::bind(&KeyMessage, std::ref(rx), "<F5>", _1));
			rx.bind_key(Replxx::KEY::F6, std::bind(&KeyMessage, std::ref(rx), "<F6>", _1));
			rx.bind_key(Replxx::KEY::F7, std::bind(&KeyMessage, std::ref(rx), "<F7>", _1));
			rx.bind_key(Replxx::KEY::F8, std::bind(&KeyMessage, std::ref(rx), "<F8>", _1));
			rx.bind_key(Replxx::KEY::F9, std::bind(&KeyMessage, std::ref(rx), "<F9>", _1));
			rx.bind_key(Replxx::KEY::F10, std::bind(&KeyMessage, std::ref(rx), "<F10>", _1));
			rx.bind_key(Replxx::KEY::F11, std::bind(&KeyMessage, std::ref(rx), "<F11>", _1));
			rx.bind_key(Replxx::KEY::F12, std::bind(&KeyMessage, std::ref(rx), "<F12>", _1));
			rx.bind_key(Replxx::KEY::shift(Replxx::KEY::F1), std::bind(&KeyMessage, std::ref(rx), "<S-F1>", _1));
			rx.bind_key(Replxx::KEY::shift(Replxx::KEY::F2), std::bind(&KeyMessage, std::ref(rx), "<S-F2>", _1));
			rx.bind_key(Replxx::KEY::shift(Replxx::KEY::F3), std::bind(&KeyMessage, std::ref(rx), "<S-F3>", _1));
			rx.bind_key(Replxx::KEY::shift(Replxx::KEY::F4), std::bind(&KeyMessage, std::ref(rx), "<S-F4>", _1));
			rx.bind_key(Replxx::KEY::shift(Replxx::KEY::F5), std::bind(&KeyMessage, std::ref(rx), "<S-F5>", _1));
			rx.bind_key(Replxx::KEY::shift(Replxx::KEY::F6), std::bind(&KeyMessage, std::ref(rx), "<S-F6>", _1));
			rx.bind_key(Replxx::KEY::shift(Replxx::KEY::F7), std::bind(&KeyMessage, std::ref(rx), "<S-F7>", _1));
			rx.bind_key(Replxx::KEY::shift(Replxx::KEY::F8), std::bind(&KeyMessage, std::ref(rx), "<S-F8>", _1));
			rx.bind_key(Replxx::KEY::shift(Replxx::KEY::F9), std::bind(&KeyMessage, std::ref(rx), "<S-F9>", _1));
			rx.bind_key(Replxx::KEY::shift(Replxx::KEY::F10), std::bind(&KeyMessage, std::ref(rx), "<S-F10>", _1));
			rx.bind_key(Replxx::KEY::shift(Replxx::KEY::F11), std::bind(&KeyMessage, std::ref(rx), "<S-F11>", _1));
			rx.bind_key(Replxx::KEY::shift(Replxx::KEY::F12), std::bind(&KeyMessage, std::ref(rx), "<S-F12>", _1));
			rx.bind_key(Replxx::KEY::control(Replxx::KEY::F1), std::bind(&KeyMessage, std::ref(rx), "<C-F1>", _1));
			rx.bind_key(Replxx::KEY::control(Replxx::KEY::F2), std::bind(&KeyMessage, std::ref(rx), "<C-F2>", _1));
			rx.bind_key(Replxx::KEY::control(Replxx::KEY::F3), std::bind(&KeyMessage, std::ref(rx), "<C-F3>", _1));
			rx.bind_key(Replxx::KEY::control(Replxx::KEY::F4), std::bind(&KeyMessage, std::ref(rx), "<C-F4>", _1));
			rx.bind_key(Replxx::KEY::control(Replxx::KEY::F5), std::bind(&KeyMessage, std::ref(rx), "<C-F5>", _1));
			rx.bind_key(Replxx::KEY::control(Replxx::KEY::F6), std::bind(&KeyMessage, std::ref(rx), "<C-F6>", _1));
			rx.bind_key(Replxx::KEY::control(Replxx::KEY::F7), std::bind(&KeyMessage, std::ref(rx), "<C-F7>", _1));
			rx.bind_key(Replxx::KEY::control(Replxx::KEY::F8), std::bind(&KeyMessage, std::ref(rx), "<C-F8>", _1));
			rx.bind_key(Replxx::KEY::control(Replxx::KEY::F9), std::bind(&KeyMessage, std::ref(rx), "<C-F9>", _1));
			rx.bind_key(Replxx::KEY::control(Replxx::KEY::F10), std::bind(&KeyMessage, std::ref(rx), "<C-F10>", _1));
			rx.bind_key(Replxx::KEY::control(Replxx::KEY::F11), std::bind(&KeyMessage, std::ref(rx), "<C-F11>", _1));
			rx.bind_key(Replxx::KEY::control(Replxx::KEY::F12), std::bind(&KeyMessage, std::ref(rx), "<C-F12>", _1));
			rx.bind_key(Replxx::KEY::shift(Replxx::KEY::TAB), std::bind(&KeyMessage, std::ref(rx), "<S-Tab>", _1));
			rx.bind_key(Replxx::KEY::control(Replxx::KEY::HOME), std::bind(&KeyMessage, std::ref(rx), "<C-Home>", _1));
			rx.bind_key(Replxx::KEY::shift(Replxx::KEY::HOME), std::bind(&KeyMessage, std::ref(rx), "<S-Home>", _1));
			rx.bind_key(Replxx::KEY::control(Replxx::KEY::END), std::bind(&KeyMessage, std::ref(rx), "<C-End>", _1));
			rx.bind_key(Replxx::KEY::shift(Replxx::KEY::END), std::bind(&KeyMessage, std::ref(rx), "<S-End>", _1));
			rx.bind_key(Replxx::KEY::control(Replxx::KEY::PAGE_UP), std::bind(&KeyMessage, std::ref(rx), "<C-PgUp>", _1));
			rx.bind_key(Replxx::KEY::control(Replxx::KEY::PAGE_DOWN), std::bind(&KeyMessage, std::ref(rx), "<C-PgDn>", _1));
			rx.bind_key(Replxx::KEY::shift(Replxx::KEY::LEFT), std::bind(&KeyMessage, std::ref(rx), "<S-Left>", _1));
			rx.bind_key(Replxx::KEY::shift(Replxx::KEY::RIGHT), std::bind(&KeyMessage, std::ref(rx), "<S-Right>", _1));
			rx.bind_key(Replxx::KEY::shift(Replxx::KEY::UP), std::bind(&KeyMessage, std::ref(rx), "<S-Up>", _1));
			rx.bind_key(Replxx::KEY::shift(Replxx::KEY::DOWN), std::bind(&KeyMessage, std::ref(rx), "<S-Down>", _1));

			log << HLL::LL_INFO << "Helium shell environment initialized." << hendl;

			return 0;
		}
		int InitShell(string prompt) {
			HeliumEndline hendl;

			log << HLL::LL_INFO << "Starting Helium shell." << hendl;

			for (;;) {
				char const* cinput{ nullptr };

				do {
					cinput = rx.input(prompt);
				} while (cinput == nullptr && errno == EAGAIN);

				if (cinput == NULL) continue;
				string input(cinput);
				if (input.empty()) continue;

				list<any> temp_param;
				any temp_any = input;
				temp_param.push_back(temp_any);
				helium_event_manager.DispatchEvent(HeliumEventList::CONSOLE_INPUT, temp_param);
				temp_any = string("console");
				temp_param.push_back(temp_any);
				helium_event_manager.DispatchEvent(HeliumEventList::GENERAL_INPUT, temp_param);

				if (auto ret = ExecuteCommand(input, "console", 4); ret != 0) {
					log << HLL::LL_ERR << "Failed to execute command : " << input << hendl;
				}

				rx.history_add(input);
			}
			return 0;
		}
		int FinShell() {
			HeliumEndline hendl;

			log << HLL::LL_INFO << "Finalizing Helium shell." << hendl;

			rx.history_sync("./command_history");
			for (auto it = HeliumCommandTree.begin(); it != HeliumCommandTree.end(); it++) {
				delete[](*it);
			}
			HeliumCommandTree.clear();

			log << HLL::LL_INFO << "Finalized Helium shell." << hendl;
			return 0;
		}
		Replxx::ACTION_RESULT KeyMessage(Replxx& replxx, std::string s, char32_t) {
			replxx.invoke(Replxx::ACTION::CLEAR_SELF, 0);
			replxx.print("%s\n", s.c_str());
			replxx.invoke(Replxx::ACTION::REPAINT, 0);
			return (Replxx::ACTION_RESULT::CONTINUE);
		}

#pragma region CommandTreeOps
		tree<_BasicHeliumCommand*>::pre_order_iterator
			AddCommand(_BasicHeliumCommand* cmd, uuid parentuuid) {
			for (auto tit = HeliumCommandTree.begin(); tit != HeliumCommandTree.end(); tit++) {
				if (parentuuid == (**tit).CommandUUID()) {
					if (!HeliumCommandTree.is_valid(tit) && cmd->IsValid())
						return HeliumCommandTree.end();
					return HeliumCommandTree.append_child(tit, cmd);;
				}
			}
			return HeliumCommandTree.end();
		}
		tree<_BasicHeliumCommand*>::pre_order_iterator
			AddCommand(_BasicHeliumCommand* cmd, tree<_BasicHeliumCommand*>::pre_order_iterator parentit) {
			if (HeliumCommandTree.is_valid(parentit) && cmd->IsValid())
				return HeliumCommandTree.append_child(parentit, cmd);
			else
				return HeliumCommandTree.end();
		}
		tree<_BasicHeliumCommand*>::pre_order_iterator
			InsertCommand(_BasicHeliumCommand* cmd, uuid parentuuid) {
			for (auto tit = HeliumCommandTree.begin(); tit != HeliumCommandTree.end(); tit++) {
				if (parentuuid == (**tit).CommandUUID()) {
					if (!cmd->IsValid())
						return HeliumCommandTree.end();
					else
						return HeliumCommandTree.insert(tit, cmd);;
				}
			}
			return HeliumCommandTree.end();
		}
		tree<_BasicHeliumCommand*>::pre_order_iterator
			InsertCommand(_BasicHeliumCommand* cmd, tree<_BasicHeliumCommand*>::pre_order_iterator tit) {
			if (cmd->IsValid())
				return HeliumCommandTree.insert(tit, cmd);
			return HeliumCommandTree.end();
		}
		tree<_BasicHeliumCommand*>::pre_order_iterator
			AddCommandTree(tree<_BasicHeliumCommand*>::pre_order_iterator subtree, uuid parentuuid) {
			for (auto tit = HeliumCommandTree.begin(); tit != HeliumCommandTree.end(); tit++) {
				if (parentuuid == (**tit).CommandUUID()) {
					if (!HeliumCommandTree.is_valid(tit))
						return HeliumCommandTree.end();
					return HeliumCommandTree.insert_subtree_after(tit, subtree);;
				}
			}
			return HeliumCommandTree.end();
		}
		tree<_BasicHeliumCommand*>::pre_order_iterator
			AddCommandTree(tree<_BasicHeliumCommand*>::pre_order_iterator subtree, tree<_BasicHeliumCommand*>::pre_order_iterator parentit) {
			if (!HeliumCommandTree.is_valid(parentit))
				return HeliumCommandTree.end();
			else
				return HeliumCommandTree.insert_subtree_after(parentit, subtree);
		}
		tree<_BasicHeliumCommand*>::pre_order_iterator
			DeleteCommand(uuid uuid) {
			for (auto tit = HeliumCommandTree.begin(); tit != HeliumCommandTree.end(); tit++) {
				if ((**tit).CommandUUID() == uuid) {
					delete[] * tit;
					return HeliumCommandTree.erase(tit);
				}
			}
			return HeliumCommandTree.end();
		}
		tree<_BasicHeliumCommand*>::pre_order_iterator
			DeleteCommand(tree<_BasicHeliumCommand*>::pre_order_iterator it) {
			if (HeliumCommandTree.is_valid(it)) {
				delete[] * it;
				return HeliumCommandTree.erase(it);
			}
			return HeliumCommandTree.end();
		}
		tree<_BasicHeliumCommand*>::pre_order_iterator
			DeleteCommandTree(uuid uuid) {
			for (auto tit = HeliumCommandTree.begin(); tit != HeliumCommandTree.end(); tit++) {
				if ((**tit).CommandUUID() == uuid) {
					for (auto subit = tit.begin(); subit != tit.end(); subit++) delete[] * subit;
					HeliumCommandTree.erase_children(tit);
					return HeliumCommandTree.erase(tit);
				}
			}
			return HeliumCommandTree.end();
		}
		tree<_BasicHeliumCommand*>::pre_order_iterator
			DeleteCommandTree(tree<_BasicHeliumCommand*>::pre_order_iterator it) {
			if (HeliumCommandTree.is_valid(it)) {
				for (auto subit = it.begin(); subit != it.end(); subit++) delete[] * subit;
				HeliumCommandTree.erase_children(it);
				return HeliumCommandTree.erase(it);
			}
			return HeliumCommandTree.end();
		}
		tree<_BasicHeliumCommand*>::pre_order_iterator
			QueryCommand(uuid uuid, tree<_BasicHeliumCommand*>::pre_order_iterator it) {
			if (!HeliumCommandTree.is_valid(it)) return it.end();
			for (auto tit = it.begin(); tit != it.end(); tit++) {
				if ((**tit).CommandUUID() == uuid)
					return tit;
			}
			return it.end();
		}
		tree<_BasicHeliumCommand*>::pre_order_iterator
			QueryCommand(string commandstr, tree<_BasicHeliumCommand*>::pre_order_iterator it) {
			if (!HeliumCommandTree.is_valid(it)) return it.end();
			for (auto tit = it.begin(); tit != it.end(); tit++) {
				if (typeid((**it)) != typeid(ConstantString)) continue;
				if (static_cast<ConstantString*>(*tit)->GetCommandString() == commandstr)
					return tit;
			}
			return it.end();
		}
		tree<_BasicHeliumCommand*>::pre_order_iterator
			ReplaceCommand(uuid uuid, _BasicHeliumCommand* cmd) {
			auto tit = QueryCommand(uuid);
			if (HeliumCommandTree.end() != tit) {
				delete[] * tit;
				return HeliumCommandTree.replace(tit, cmd);
			}
			return HeliumCommandTree.end();
		}
		tree<_BasicHeliumCommand*>::pre_order_iterator
			ReplaceCommand(tree<_BasicHeliumCommand*>::pre_order_iterator it, _BasicHeliumCommand* cmd) {
			if (HeliumCommandTree.is_valid(it) && cmd->IsValid()) {
				delete[] * it;
				return HeliumCommandTree.replace(it, cmd);
			}
			return HeliumCommandTree.end();
		}
		tree<_BasicHeliumCommand*>::pre_order_iterator
			ReplaceCommandTree(uuid uuid, tree<_BasicHeliumCommand*>::pre_order_iterator subtree) {
			auto tit = QueryCommand(uuid);
			if (HeliumCommandTree.end() != tit) {
				for (auto subit = tit.begin(); subit != tit.end(); subit++) delete[] * subit;
				return HeliumCommandTree.replace(tit, subtree);
			}
			return HeliumCommandTree.end();
		}
		tree<_BasicHeliumCommand*>::pre_order_iterator
			ReplaceCommandTree(tree<_BasicHeliumCommand*>::pre_order_iterator it, tree<_BasicHeliumCommand*>::pre_order_iterator subtree) {
			if (HeliumCommandTree.is_valid(it)) {
				for (auto subit = it.begin(); subit != it.end(); subit++) delete[] * subit;
				return HeliumCommandTree.replace(it, subtree);
			}
			return HeliumCommandTree.end();
		}
#pragma endregion

#pragma region Attrs
		uuid _BasicHeliumCommand::CommandUUID() {
			return this->cmduuid;
		}

		bool _CommandConstantString::IsCallbackable() {
			return this->callback;
		}
		bool _CommandConstantString::EnableCallback() {
			auto r = this->callback;
			this->callback = true;
			return r;
		}
		bool _CommandConstantString::DisableCallback() {
			auto r = this->callback;
			this->callback = false;
			return r;
		}

		bool _CommandConstantString::IsListable() {
			return this->list;
		}
		bool _CommandConstantString::EnableList() {
			auto r = this->list;
			this->callback = list;
			return r;
		}
		bool _CommandConstantString::DisableList() {
			auto r = this->list;
			this->callback = list;
			return r;
		}

		bool _CommandConstantString::IsExecutable() {
			return this->exec;
		}
		bool _CommandConstantString::EnableExecute() {
			auto r = this->exec;
			this->callback = exec;
			return r;
		}
		bool _CommandConstantString::DisableExecute() {
			auto r = this->exec;
			this->callback = exec;
			return r;
		}

		bool _CommandConstantString::IsHintable() {
			return this->hint;
		}
		bool _CommandConstantString::EnableHint() {
			auto r = this->hint;
			this->callback = hint;
			return r;
		}
		bool _CommandConstantString::DisableHint() {
			auto r = this->hint;
			this->callback = hint;
			return r;
		}

		bool _CommandConstantString::IsCompletable() {
			return this->autocomp;
		}
		bool _CommandConstantString::EnableCompletion() {
			auto r = this->autocomp;
			this->callback = autocomp;
			return r;
		}
		bool _CommandConstantString::DisableCompletion() {
			auto r = this->autocomp;
			this->callback = autocomp;
			return r;
		}

		HeliumPermissionLevel _CommandConstantString::GetCommandPermission() {
			return this->level;
		}
		HeliumPermissionLevel _CommandConstantString::SetCommandPermission(HeliumPermissionLevel perm) {
			auto ol = this->level;
			this->level = perm;
			return ol;
		}

		string _CommandConstantString::GetCommandString() {
			return this->commandstr;
		}
		string _CommandConstantString::SetCommandString(string cmd) {
			string tempstr = this->commandstr;
			this->commandstr = cmd;
			return tempstr;
		}

		string _CommandConstantString::GetCommandDesc() {
			return this->commanddesc;
		}
		string _CommandConstantString::SetCommandDesc(string hint) {
			string tempstr = this->commanddesc;
			this->commanddesc = hint;
			return tempstr;
		}

		string _CommandConstantString::GetCommandAlias() {
			return this->alias;
		}
		string _CommandConstantString::SetCommandAlias(string alias) {
			string tempstr = this->alias;
			this->alias = alias;
			return tempstr;
		}

		unsigned long _ArgumentString::GetLengthLimit() {
			return this->lengthlim;
		}
		unsigned long _ArgumentString::SetLengthLimit(unsigned long lim) {
			auto olim = this->lengthlim;
			this->lengthlim = lim;
			return olim;
		}

		long CommandArgumentInt::SetUpperbound(long up) {
			auto oub = this->upperbound;
			this->upperbound = up;
			return oub;
		}
		long CommandArgumentInt::SetLowerbound(long down) {
			auto olb = this->lowerbound;
			this->lowerbound = down;
			return olb;
		}
		long CommandArgumentInt::GetUpperbound() {
			return this->upperbound;
		}
		long CommandArgumentInt::GetLowerbound() {
			return this->lowerbound;
		}

		double CommandArgumentFloat::SetUpperbound(double up) {
			auto oub = this->upperbound;
			this->upperbound = up;
			return oub;
		}
		double CommandArgumentFloat::SetLowerbound(double down) {
			auto olb = this->lowerbound;
			this->lowerbound = down;
			return olb;
		}
		double CommandArgumentFloat::GetUpperbound() {
			return this->upperbound;
		}
		double CommandArgumentFloat::GetLowerbound() {
			return this->lowerbound;
		}

		bool _CommandArgument::IsOptional() {
			return this->optional;
		}
		bool _CommandArgument::EnableOptional() {
			auto oopt = this->optional;
			this->optional = true;
			return oopt;
		}
		bool _CommandArgument::DisableOptional() {
			auto oopt = this->optional;
			this->optional = false;
			return oopt;
		}

		bool _CommandArgument::IsPreproc() {
			return this->preprocenable;
		}
		bool _CommandArgument::EnablePreproc() {
			auto opreproc = this->preprocenable;
			this->preprocenable = true;
			return opreproc;
		}
		bool _CommandArgument::DisablePreproc() {
			auto opreproc = this->preprocenable;
			this->preprocenable = false;
			return opreproc;
		}

		string _CommandArgument::GetArgumentDesc() {
			return this->argudesc;
		}
		string _CommandArgument::SetArgumentDesc(string desc) {
			auto olddesc = this->argudesc;
			this->argudesc = desc;
			return olddesc;
		}

		void ConstantString::AddCallback(HeliumCommandCallback fnptr) {
			if (this->callback)
				this->fnlist.push_back(fnptr);
		}
#pragma endregion

		bool _BasicHeliumCommand::IsValid() {
			return true;
		}

		bool _CommandConstantString::IsValid() {
			bool ret = true;
			string wordbreakstr = " ";
			if (this->commandstr.empty()) ret = false;
			for (auto i = 0; i < wordbreakstr.length(); i++)
				if (this->commandstr.find(wordbreakstr[i]) != string::npos
					|| this->alias.find(wordbreakstr[i]) != string::npos) {
					ret = false;
					break;
				}
			return ret;
		}
		//string server_name	tm timestamp	string thread	string source	string player_name	string player_input
		int PlayerInput(const list<any> param) {
			auto it = param.begin();
			string server_name = any_cast<string>(*it);
			it++;
			it++;
			it++;
			it++;
			string sender = any_cast<string>(*it);
			it++;
			string rawcmd = any_cast<string>(*it);
			return ExecuteCommand(rawcmd, sender, HPL::HELIUMOWNER, server_name);
		}

		int ExecuteCommand(string rawcmd, string sender, int permission, string servername) {
			istringstream iss(rawcmd);
			list<string> words;
			list<_BasicHeliumCommand*> cmdpath;
			list<string> argus;
			string tempstr;
			tree<_BasicHeliumCommand*>::fixed_depth_iterator pit = HeliumCommandTree.begin();
			tree<_BasicHeliumCommand*>::fixed_depth_iterator tit;

			if (rawcmd == "#exit") {
				list<any> param;
				helium_event_manager.DispatchEvent(HeliumEventList::HELIUM_STOP, param);
				StopAllServer();
				UnloadAllExtension();
				log << HLL::LL_INFO << "Exiting Helium." << hendl;
				::exit(0);
			}

			while (iss >> tempstr) {
				words.push_back(tempstr);
			}

			if (words.empty()) return 0;

			for (auto it = words.begin(); it != words.end(); it++) {

				string currword = *it;
				bool iscstr = false;

				for (tit = HeliumCommandTree.begin_fixed(pit, 1);
					HeliumCommandTree.is_valid(tit) && (*(HeliumCommandTree.parent(tit)))->CommandUUID() == (*pit)->CommandUUID();
					tit++) {
					if (typeid((**tit)) == typeid(ConstantString)) {
						string command = static_cast<ConstantString*>(*tit)->GetCommandString();
						string alias = static_cast<ConstantString*>(*tit)->GetCommandAlias();

						if (currword == command || currword == alias) {
							pit = tit;
							cmdpath.push_back(static_cast<ConstantString*>(*tit));
							iscstr = true;
							break;
						}
					}
				}

				if (!iscstr) {
					bool isargu = false;

					for (tit = HeliumCommandTree.begin_fixed(pit, 1);
						HeliumCommandTree.is_valid(tit) && (*(HeliumCommandTree.parent(tit)))->CommandUUID() == (*pit)->CommandUUID();
						tit++) {
						if (typeid((**tit)) == typeid(CommandArgumentInt)) {
							if (regex_match(currword, regex("^-?[1-9]\\d*$"))) {
								isargu = true;
								pit = tit;
								argus.push_back(currword);
								cmdpath.push_back(static_cast<CommandArgumentInt*>(*tit));
								log << HLL::LL_DBG << "Matched integer : " << currword << hendl;
								break;
							}
						}
						if (typeid((**tit)) == typeid(CommandArgumentFloat)) {
							if (regex_match(currword, regex("^[1-9]\\d*\\.\\d*|0\\.\\d*[1-9]\\d*$"))
								|| regex_match(currword, regex("^-[1-9]\\d*\\.\\d*|-0\\.\\d*[1-9]\\d*$"))) {
								isargu = true;
								pit = tit;
								argus.push_back(currword);
								cmdpath.push_back(static_cast<CommandArgumentFloat*>(*tit));
								log << HLL::LL_DBG << "Matched float : " << currword << hendl;
								break;
							}
						}
						if (typeid((**tit)) == typeid(CommandArgumentQuotableString)) {
							if (currword[0] == '\"' && currword[currword.length() - 1] == '\"') {
								isargu = true;
								pit = tit;
								string strarg = currword;
								strarg.erase(strarg.begin());
								strarg.erase(strarg.end() - 1);
								argus.push_back(strarg);
								cmdpath.push_back(static_cast<CommandArgumentQuotableString*>(*tit));
								break;
							}
							if (currword[0] == '\"' && currword.find_last_of("\"") == 0) {
								bool findend = false;
								string fullword = currword;
								auto innerit = it;
								for (innerit++; innerit != words.end(); innerit++) {
									if ((*innerit)[innerit->length() - 1] == '\"') {
										findend = true;
										it++;
										fullword.append(" ").append(*innerit);
										fullword.erase(fullword.begin());
										fullword.erase(fullword.end() - 1);
										break;
									}
									else {
										fullword.append(" ").append(*innerit);
										it++;
									}
								}
								if (!findend) {
									log << HLL::LL_ERR << "Can't find another \'\"\'!" << hendl;
									return -1;
								}
								isargu = true;
								log << HLL::LL_DBG << "Matched full quotable string : " << fullword << hendl;
								argus.push_back(fullword);
								pit = tit;
								cmdpath.push_back(static_cast<CommandArgumentQuotableString*>(*tit));
								break;
							}
							else {
								log << HLL::LL_ERR << "Unexpected \'\"\'!" << hendl;
								return -1;
							}
						}
						if (typeid((**tit)) == typeid(CommandArgumentString)) {
							if (currword.find("\"") != string::npos) continue;
							log << HLL::LL_DBG << "Matched string : " << currword << hendl;
							pit = tit;
							isargu = true;
							argus.push_back(currword);
							break;
						}
					}

					if (!isargu) {
						log << HLL::LL_ERR << "Bad command." << hendl;
						return -1;
					}
				}
			}

			list<any> argumentlist;
			for (auto it = cmdpath.rbegin(); it != cmdpath.rend(); it++) {
				if (typeid(**it) == typeid(ConstantString)) {
					for (auto fnptr : static_cast<ConstantString*>(*it)->fnlist) {
						if (permission >= static_cast<ConstantString*>(*it)->GetCommandPermission()) {
							fnptr(rawcmd, sender, permission, argumentlist);
							argumentlist.clear();
						}
						else {
							log << HLL::LL_ERR << "You haven't enough permission to execute this command!" << hendl;
							break;
						}
					}
				}
				else {
					if (typeid(**it) == typeid(CommandArgumentInt)) {
						string argu = argus.back();
						long realargu;
						any anyargu;
						argus.pop_back();

						stringstream sstr;
						sstr << argu;
						sstr >> realargu;
						anyargu = realargu;

						argumentlist.push_front(anyargu);
					}
					if (typeid(**it) == typeid(CommandArgumentFloat)) {
						string argu = argus.back();
						float realargu;
						any anyargu;
						argus.pop_back();

						stringstream sstr;
						sstr << argu;
						sstr >> realargu;
						anyargu = realargu;

						argumentlist.push_front(anyargu);
					}
					if (typeid(**it) == typeid(CommandArgumentString)) {
						string argu = argus.back();
						any anyargu = argu;
						argus.pop_back();

						argumentlist.push_front(anyargu);
					}
					if (typeid(**it) == typeid(CommandArgumentQuotableString)) {
						string argu = argus.back();
						any anyargu = argu;
						argus.pop_back();

						argumentlist.push_front(anyargu);
					}
				}
			}

			return 0;
		}
	}
}