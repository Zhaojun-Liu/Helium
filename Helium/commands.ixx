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
#include<map>
#include<list>
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

		int ExecuteCommand(string rawcmd, string sender, int permission);

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
			friend int ExecuteCommand(string rawcmd, string sender, int permission);
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
	}
}