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

#include<map>
#include<iostream>
#include<functional>
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/multiprecision/cpp_dec_float.hpp>
#include<boost/uuid/uuid.hpp>
#include<boost/uuid/uuid_io.hpp>
#include<boost/uuid/uuid_generators.hpp>

#include"tree.hh/tree.hh"
#define REPLXX_STATIC
#include"replxx/replxx.hxx"

export module Helium.Commands;

import <string>;
import Helium.Config;

using namespace std;
using namespace replxx;
using namespace placeholders;
using namespace boost::uuids;
using namespace boost::multiprecision;         

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

		class _CommandEntry;
		class CommandEntry;

		class _CommandBind;
		class CommandBind;

		extern tree<_BasicHeliumCommand*> HeliumCommandTree;

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

		int ExecuteCommand(string rawcmd);

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
		public:
			virtual bool IsOptional();
			virtual bool EnableOptional();
			virtual bool DisableOptional();

			virtual bool IsPreproc();
			virtual bool EnablePreproc();
			virtual bool DisablePreproc();
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

			virtual string GetCommandString();
			virtual string SetCommandString(string cmd);

			virtual string GetCommandDesc();
			virtual string SetCommandDesc(string hint);

			virtual string GetCommandAtlas();
			virtual string SetCommandAtlas(string atlas);

			virtual bool IsValid();

			_CommandConstantString() {
				this->commanddesc = "Default Command Description";
				this->commandstr = "DefaultCMD";
				this->atlas = "DCMD";
				this->callback = false;
				this->list = true;
				this->exec = false;
				this->hint = true;
				this->autocomp = true;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}
			_CommandConstantString(string desc, string str, string atlas = "", bool callback = true, bool list = true, bool exec = true, bool hint = true, bool autocomp = true) {
				this->commanddesc = desc;
				this->commandstr = str;
				this->atlas = atlas;
				this->callback = callback;
				this->list = list;
				this->exec = exec;
				this->hint = hint;
				this->autocomp = autocomp;
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
			string atlas;

			HeliumPermissionLevel level;
		};


		class _CommandBind : public _CommandConstantString {

		};
		class _ArgumentString : public _CommandArgument {
		public:
			virtual unsigned long GetLengthLimit();
			virtual unsigned long SetLengthLimit(unsigned long lim);
			virtual string GetValue();
			virtual string SetValue(string v);
		protected:
			unsigned long lengthlim;
			string value;
		};
#pragma endregion

		class CommandArgumentInt : public _CommandArgument {
		public:
			virtual long SetUpperbound(long up);
			virtual long SetLowerbound(long down);
			virtual long GetUpperbound();
			virtual long GetLowerbound();
			virtual long GetValue();
			virtual long SetValue(long v);
		protected:
			long upperbound;
			long lowerbound;
			long value;
		};
		class CommandArgumentFloat : public _CommandArgument {
		public:
			virtual double SetUpperbound(double up);
			virtual double SetLowerbound(double down);
			virtual double GetUpperbound();
			virtual double GetLowerbound();
			virtual double GetValue();
			virtual double SetValue(double v);
		protected:
			double upperbound;
			double lowerbound;
			double value;
		};
		class CommandArgumentBool : public _CommandArgument {
		public:
			virtual bool GetValue();
			virtual bool SetValue(bool v);
		protected:
			bool value;
		};
		class CommandArgumentString : public _ArgumentString {

		};
		class CommandArgumentQuotableString : public _ArgumentString {

		};
		class CommandArgumentGreedyString : public _ArgumentString {

		};
		class CommandBind : public _CommandBind {

		};
		class ConstantString : public _CommandConstantString {
		public:
			ConstantString() {
				this->commanddesc = "Default Command Description";
				this->commandstr = "DefaultCMD";
				this->callback = false;
				this->list = true;
				this->exec = false;
				this->hint = true;
				this->autocomp = true;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}
			ConstantString(string desc, string str, string atlas = "", bool callback = true, bool list = true, bool exec = true, bool hint = true, bool autocomp = true) {
				this->commanddesc = desc;
				this->commandstr = str;
				this->atlas = atlas;
				this->callback = callback;
				this->list = list;
				this->exec = exec;
				this->hint = hint;
				this->autocomp = autocomp;
				uuid cmduuid = random_generator()();
				this->cmduuid = cmduuid;
			}
		};
	}
}