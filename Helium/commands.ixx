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
#include<string>
#include<functional>
//#include<boost/multiprecision/cpp_int.hpp>
//#include<boost/multiprecision/cpp_dec_float.hpp>
//#include<boost/multiprecision/gmp.hpp>
#include<boost/uuid/uuid.hpp>

#include"tree.hh/tree.hh"
#define REPLXX_STATIC
#include"replxx/replxx.hxx"

export module Helium.Commands;

using namespace std;
using namespace replxx;
using namespace placeholders;
using namespace boost::uuids;

export{
	namespace Helium {
		class _BasicHeliumCommand;
		class _CommandConstantString;
		class _CommandArgument;

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
		void ColorCallBack(string const& str, Replxx::colors_t& colors);
		Replxx::ACTION_RESULT KeyMessage(Replxx& replxx, std::string s, char32_t);

		tree<_BasicHeliumCommand*>::pre_order_iterator AddCommand(_BasicHeliumCommand* cmd, uuid parentuuid);
		tree<_BasicHeliumCommand*>::pre_order_iterator AddCommand(_BasicHeliumCommand* cmd, tree<_BasicHeliumCommand*>::pre_order_iterator parentit);
		tree<_BasicHeliumCommand*>::pre_order_iterator AddCommandTree(tree<_BasicHeliumCommand*>::pre_order_iterator subtree, uuid parentuuid);
		tree<_BasicHeliumCommand*>::pre_order_iterator AddCommandTree(tree<_BasicHeliumCommand*>::pre_order_iterator subtree, tree<_BasicHeliumCommand*>::pre_order_iterator parentit);
		tree<_BasicHeliumCommand*>::pre_order_iterator DeleteCommand(uuid uuid);
		tree<_BasicHeliumCommand*>::pre_order_iterator DeleteCommand(tree<_BasicHeliumCommand*>::pre_order_iterator it);
		tree<_BasicHeliumCommand*>::pre_order_iterator DeleteCommandTree(uuid uuid);
		tree<_BasicHeliumCommand*>::pre_order_iterator DeleteCommandTree(tree<_BasicHeliumCommand*>::pre_order_iterator it);
		tree<_BasicHeliumCommand*>::pre_order_iterator QueryCommand(uuid uuid, tree<_BasicHeliumCommand*>::pre_order_iterator = HeliumCommandTree.begin());
		tree<_BasicHeliumCommand*>::pre_order_iterator QueryCommand(string commandstr, tree<_BasicHeliumCommand*>::pre_order_iterator = HeliumCommandTree.begin());
		tree<_BasicHeliumCommand*>::pre_order_iterator ReplaceCommand(uuid uuid, _BasicHeliumCommand* cmd);
		tree<_BasicHeliumCommand*>::pre_order_iterator ReplaceCommand(tree<_BasicHeliumCommand*>::pre_order_iterator it, _BasicHeliumCommand* cmd);
		tree<_BasicHeliumCommand*>::pre_order_iterator ReplaceCommandTree(uuid uuid, tree<_BasicHeliumCommand*>::pre_order_iterator subtree);
		tree<_BasicHeliumCommand*>::pre_order_iterator ReplaceCommandTree(tree<_BasicHeliumCommand*>::pre_order_iterator it, tree<_BasicHeliumCommand*>::pre_order_iterator subtree);

		int ExecuteCommand(string rawcmd);

#pragma region CommandClassBase
		class _BasicHeliumCommand {
		protected:
			string commanddesc;
			string commandstr;

			bool callback;
			bool list;
			bool exec;
			bool hint;
			bool autocomp;

			uuid cmduuid;
		public:
			virtual _BasicHeliumCommand operator()(string desc, string str, bool callback = true, bool list = true, bool exec = true, bool hint = true, bool autocomp = true);

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

			virtual uuid CommandUUID();

			virtual string GetCommandString();
			virtual string SetCommandString(string cmd);

			virtual string GetCommandHint();
			virtual string SetCommandHint(string hint);

			virtual _BasicHeliumCommand* GetCommandClassType();
			virtual bool IsVaild();
		};
		class _CommandArgument : virtual public _BasicHeliumCommand {
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

			virtual _CommandArgument* GetCommandClassType();
			virtual bool EnablePreprocessing();
			virtual bool DisablePreprocessing();
		};
		class _CommandConstantString : virtual public _BasicHeliumCommand {
		public:
			virtual _CommandConstantString* GetCommandClassType();
		};


		class _CommandBind : virtual public _CommandConstantString {
		public:
			virtual _CommandBind* GetCommandClassType();
		};
		class _ArgumentNumber : public _CommandArgument {
		public:
			virtual _ArgumentNumber* GetCommandClassType();
			virtual void SetUpperbound() = 0;
			virtual void SetLowerbound() = 0;
			virtual void GetUpperbound() = 0;
			virtual void GetLowerbound() = 0;
		protected:
		};
		class _ArgumentString : public _CommandArgument {
		public:
			virtual _ArgumentString* GetCommandClassType();

			virtual unsigned long GetLengthLimit();
			virtual unsigned long SetLengthLimit();
		protected:
			unsigned long lengthlim;
		};
#pragma endregion



		class CommandArgumentInt : public _ArgumentNumber {
		public:
			virtual CommandArgumentInt* GetCommandClassType();
			virtual int SetUpperbound(int up);
			virtual int SetLowerbound(int down);
			virtual int GetUpperbound(int up);
			virtual int GetLowerbound(int down);
		protected:
			int upperbound;
			int lowerbound;
		};
		class CommandArgumentFloat : public _ArgumentNumber {
		public:
			virtual CommandArgumentFloat* GetCommandClassType();
			virtual float SetUpperbound(float up);
			virtual float SetLowerbound(float down);
			virtual float GetUpperbound(float up);
			virtual float GetLowerbound(float down);
		protected:
			float upperbound;
			float lowerbound;
		};
		class CommandArgumentString : public _ArgumentString {
		public:
			virtual CommandArgumentString* GetCommandClassType();
		};
		class CommandArgumentQuotableString : public _ArgumentString {
		public:
			virtual CommandArgumentQuotableString* GetCommandClassType();
		};
		class CommandArgumentGreedyString : public _ArgumentString {
		public:
			virtual CommandArgumentGreedyString* GetCommandClassType();
		};
		class CommandBind : virtual public _CommandBind {
		public:
			virtual CommandBind* GetCommandClassType();
		};
	}
}