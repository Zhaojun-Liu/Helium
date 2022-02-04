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

#include<functional>
#include<iostream>
#include<sstream>
#include<boost/uuid/uuid.hpp>
#include<boost/uuid/uuid_io.hpp>
#include<boost/uuid/uuid_generators.hpp>
#include"tree.hh/tree.hh"
#define REPLXX_STATIC
#include"replxx/replxx.hxx"

module Helium.Commands;

import Helium.Utils;

using namespace std;
using namespace replxx;
using namespace placeholders;
using namespace boost::uuids;

namespace Helium {
	tree<_BasicHeliumCommand*> HeliumCommandTree;
	Replxx rx;

	void print_tree(const tree<_BasicHeliumCommand*>& tr)
	{
		auto it = tr.begin();
		auto end = tr.end();
		if (!tr.is_valid(it)) return;
		int rootdepth = tr.depth(it);
		while (it != end) {
			for (int i = 0; i < tr.depth(it) - rootdepth; ++i)
				cout << "  ";
			if (!((*it)->GetCommandAtlas().empty()))
				cout << (*it)->GetCommandString() << "/" << (*it)->GetCommandAtlas() << endl;
			else
				cout << (*it)->GetCommandString() << endl;
			++it;
		}
	}
	bool IsStringEqual(string l, string r) {
		bool same = true;
		for (int i = 0; same && (i < r.length()); i ++ ) {
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
		if (splited.back().length() < 2) return h;

		for (auto it = splited.begin(); it < splited.end(); it++) {
			string currword = *it;
			if (it + 1 == splited.end() && beforeword.find(" ") == string::npos) {
				for (tit = HeliumCommandTree.begin_fixed(pit, 1);
					HeliumCommandTree.is_valid(tit) && HeliumCommandTree.parent(tit) == pit;
					tit++) {
					string command = (*tit)->GetCommandString();
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
					HeliumCommandTree.is_valid(tit) && HeliumCommandTree.parent(tit) == pit;
					tit++) {
					string command = (*tit)->GetCommandString();
					if(*it == (*tit)->GetCommandString()){
						pit = tit;
						find = true;
						break;
					}
					if (*it == (*tit)->GetCommandAtlas()) {
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
		cout << "\tCompletion : " << context << "(" << len << ")" << endl;
		return c;
	}
	void ColorCallBack(string const& str, Replxx::colors_t& colors) {
		return;
	}
	int InitBuiltinCommandTree() {
		ConstantString* treeroot = new ConstantString("Helium Command Tree Root.", "HeliumCommandTreeRoot", "HCTR", false, false, false, false, false);
		HeliumCommandTree.set_head(treeroot);

		ConstantString* root = new ConstantString("Helium Built-in Command \"#Helium\" command root.", "#Helium", "#Hel", false);
		ConstantString* help = new ConstantString("Helium Built-in Command \"#Help\" command root.", "#Help", "");
		auto rit = AddCommand(root);
		auto hit = AddCommand(help);

		ConstantString* show = new ConstantString("Helium Built-in Command : \"show\" command.", "show", "sh");
		ConstantString* conditions = new ConstantString("Helium Built-in Command : \"conditions\" command.", "conditions", "c");
		ConstantString* warranty = new ConstantString("Helium Built-in Command : \"warranty\" command", "warranty", "w");

		auto showit = AddCommand(show, rit);
		AddCommand(conditions, showit);
		AddCommand(warranty, showit);

		ConstantString* command = new ConstantString("Helium Built-in Command : \"Command\" command", "command", "cmd");
		ConstantString* cmdlist = new ConstantString("Helium Built-in Command : \"list\" command", "list", "lst");

		auto cmdit = AddCommand(command, rit);
		AddCommand(cmdlist, cmdit);

		ConstantString* server = new ConstantString("Helium Built-in Command : \"server\" command", "server", "svr");

		auto serverit = AddCommand(server, rit);

		ConstantString* ext = new ConstantString("Helium Built-in Command : \"extension\" command", "extension", "ext");

		auto extit = AddCommand(ext, rit);

		ConstantString* ent = new ConstantString("Helium Built-in Command : \"event\" command", "event", "ent");

		auto entit = AddCommand(ent, rit);

		print_tree(HeliumCommandTree);
		return 0;
	}
	int InitShellEnv() {
		rx.install_window_change_handler();
		rx.history_load("./commands_history");
		rx.set_max_history_size(256);
		rx.set_max_hint_rows(3);
		rx.set_completion_callback(&CompletionCallBack);
		rx.set_hint_callback(&HintCallBack);
		rx.set_highlighter_callback(&ColorCallBack);
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
		return 0;
	}
	int InitShell(string prompt) {
		print_tree(HeliumCommandTree);
		for (;;) {
			char const* cinput{ nullptr };

			do {
				cinput = rx.input(prompt);
			} while (cinput == nullptr && errno == EAGAIN);

			if (cinput == NULL) continue;
			string input(cinput);
			if (input.empty()) continue;

			//add input function call here

			rx.history_add(input);
		}
		return 0;
	}
	int FinShell() {
		rx.history_sync("./command_history");
		for (auto it = HeliumCommandTree.begin(); it != HeliumCommandTree.end(); it++) {
			delete[] (*it);
		}
		HeliumCommandTree.clear();
		return 0;
	}
	Replxx::ACTION_RESULT KeyMessage(Replxx& replxx, std::string s, char32_t) {
		replxx.invoke(Replxx::ACTION::CLEAR_SELF, 0);
		replxx.print("%s\n", s.c_str());
		replxx.invoke(Replxx::ACTION::REPAINT, 0);
		return (Replxx::ACTION_RESULT::CONTINUE);
	}

#pragma region GetCommandClassType
	_BasicHeliumCommand* _BasicHeliumCommand::GetCommandClassType() {
		return this;
	}
	_CommandArgument* _CommandArgument::GetCommandClassType() {
		return this;
	}
	_CommandBind* _CommandBind::GetCommandClassType() {
		return this;
	}
	_CommandConstantString* _CommandConstantString::GetCommandClassType() {
		return this;
	}
	_ArgumentNumber* _ArgumentNumber::GetCommandClassType() {
		return this;
	}
	_ArgumentString* _ArgumentString::GetCommandClassType() {
		return this;
	}
	CommandBind* CommandBind::GetCommandClassType() {
		return this;
	}
	CommandArgumentInt* CommandArgumentInt::GetCommandClassType() {
		return this;
	}
	CommandArgumentFloat* CommandArgumentFloat::GetCommandClassType() {
		return this;
	}
	CommandArgumentString* CommandArgumentString::GetCommandClassType() {
		return this;
	}
	CommandArgumentQuotableString* CommandArgumentQuotableString::GetCommandClassType() {
		return this;
	}
	CommandArgumentGreedyString* CommandArgumentGreedyString::GetCommandClassType() {
		return this;
	}
	ConstantString* ConstantString::GetCommandClassType() {
		return this;
	}
#pragma endregion

#pragma region CommandTreeOps
	tree<_BasicHeliumCommand*>::pre_order_iterator 
		AddCommand(_BasicHeliumCommand* cmd, uuid parentuuid) {
		for (auto tit = HeliumCommandTree.begin(); tit != HeliumCommandTree.end(); tit++) {
			if (parentuuid == (**tit).CommandUUID()) {
				if (!HeliumCommandTree.is_valid(tit) && cmd->IsVaild())
					return HeliumCommandTree.end();
				return HeliumCommandTree.append_child(tit, cmd);;
			}
		}
	}
	tree<_BasicHeliumCommand*>::pre_order_iterator 
		AddCommand(_BasicHeliumCommand* cmd, tree<_BasicHeliumCommand*>::pre_order_iterator parentit) {
		if (HeliumCommandTree.is_valid(parentit) && cmd->IsVaild())
			return HeliumCommandTree.append_child(parentit, cmd);
		return HeliumCommandTree.end();
	}
	tree<_BasicHeliumCommand*>::pre_order_iterator 
		InsertCommand(_BasicHeliumCommand* cmd, uuid parentuuid) {
		for (auto tit = HeliumCommandTree.begin(); tit != HeliumCommandTree.end(); tit++) {
			if (parentuuid == (**tit).CommandUUID()) {
				if (!cmd->IsVaild())
					return HeliumCommandTree.end();
				return HeliumCommandTree.insert(tit, cmd);;
			}
		}
	}
	tree<_BasicHeliumCommand*>::pre_order_iterator 
		InsertCommand(_BasicHeliumCommand* cmd, tree<_BasicHeliumCommand*>::pre_order_iterator tit) {
		if (cmd->IsVaild())
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
	}
	tree<_BasicHeliumCommand*>::pre_order_iterator 
		AddCommandTree(tree<_BasicHeliumCommand*>::pre_order_iterator subtree, tree<_BasicHeliumCommand*>::pre_order_iterator parentit) {
		if (!HeliumCommandTree.is_valid(parentit))
			return HeliumCommandTree.end();
		return HeliumCommandTree.insert_subtree_after(parentit, subtree);
	}
	tree<_BasicHeliumCommand*>::pre_order_iterator 
		DeleteCommand(uuid uuid) {
		for (auto tit = HeliumCommandTree.begin(); tit != HeliumCommandTree.end(); tit++) {
			if ((**tit).CommandUUID() == uuid) {
				return HeliumCommandTree.erase(tit);
			}
		}
	}
	tree<_BasicHeliumCommand*>::pre_order_iterator 
		DeleteCommand(tree<_BasicHeliumCommand*>::pre_order_iterator it) {
		if (HeliumCommandTree.is_valid(it)) {
			return HeliumCommandTree.erase(it);
		}
		return HeliumCommandTree.end();
	}
	tree<_BasicHeliumCommand*>::pre_order_iterator 
		DeleteCommandTree(uuid uuid) {
		for (auto tit = HeliumCommandTree.begin(); tit != HeliumCommandTree.end(); tit++) {
			if ((**tit).CommandUUID() == uuid) {
				HeliumCommandTree.erase_children(tit);
				return HeliumCommandTree.erase(tit);
			}
		}
	}
	tree<_BasicHeliumCommand*>::pre_order_iterator 
		DeleteCommandTree(tree<_BasicHeliumCommand*>::pre_order_iterator it) {
		if (HeliumCommandTree.is_valid(it)) {
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
				if ((**tit).GetCommandString() == commandstr)
					return tit;
			}
			return it.end();
	}
	tree<_BasicHeliumCommand*>::pre_order_iterator 
		ReplaceCommand(uuid uuid, _BasicHeliumCommand* cmd) {
		auto tit = QueryCommand(uuid);
		if (HeliumCommandTree.end() != tit) {
			return HeliumCommandTree.replace(tit, cmd);
		}
		return HeliumCommandTree.end();
	}
	tree<_BasicHeliumCommand*>::pre_order_iterator 
		ReplaceCommand(tree<_BasicHeliumCommand*>::pre_order_iterator it, _BasicHeliumCommand* cmd) {
		if (HeliumCommandTree.is_valid(it) && cmd->IsVaild()) {
			return HeliumCommandTree.replace(it, cmd);
		}
	}
	tree<_BasicHeliumCommand*>::pre_order_iterator 
		ReplaceCommandTree(uuid uuid, tree<_BasicHeliumCommand*>::pre_order_iterator subtree) {
		auto tit = QueryCommand(uuid);
		if (HeliumCommandTree.end() != tit) {
			return HeliumCommandTree.replace(tit, subtree);
		}
		return HeliumCommandTree.end();
	}
	tree<_BasicHeliumCommand*>::pre_order_iterator 
		ReplaceCommandTree(tree<_BasicHeliumCommand*>::pre_order_iterator it, tree<_BasicHeliumCommand*>::pre_order_iterator subtree) {
		if (HeliumCommandTree.is_valid(it)) {
			return HeliumCommandTree.replace(it, subtree);
		}
		return HeliumCommandTree.end();
	}
#pragma endregion

#pragma region Attrs
	bool _BasicHeliumCommand::IsCallbackable() {
		return this->callback;
	}
	bool _BasicHeliumCommand::EnableCallback() {
		auto r = this->callback;
		this->callback = true;
		return r;
	}
	bool _BasicHeliumCommand::DisableCallback() {
		auto r = this->callback;
		this->callback = false;
		return r;
	}

	bool _BasicHeliumCommand::IsListable() {
		return this->list;
	}
	bool _BasicHeliumCommand::EnableList() {
		auto r = this->list;
		this->callback = list;
		return r;
	}
	bool _BasicHeliumCommand::DisableList() {
		auto r = this->list;
		this->callback = list;
		return r;
	}

	bool _BasicHeliumCommand::IsExecutable() {
		return this->exec;
	}
	bool _BasicHeliumCommand::EnableExecute() {
		auto r = this->exec;
		this->callback = exec;
		return r;
	}
	bool _BasicHeliumCommand::DisableExecute() {
		auto r = this->exec;
		this->callback = exec;
		return r;
	}

	bool _BasicHeliumCommand::IsHintable() {
		return this->hint;
	}
	bool _BasicHeliumCommand::EnableHint() {
		auto r = this->hint;
		this->callback = hint;
		return r;
	}
	bool _BasicHeliumCommand::DisableHint() {
		auto r = this->hint;
		this->callback = hint;
		return r;
	}

	bool _BasicHeliumCommand::IsCompletable() {
		return this->autocomp;
	}
	bool _BasicHeliumCommand::EnableCompletion() {
		auto r = this->autocomp;
		this->callback = autocomp;
		return r;
	}
	bool _BasicHeliumCommand::DisableCompletion() {
		auto r = this->autocomp;
		this->callback = autocomp;
		return r;
	}

	uuid _BasicHeliumCommand::CommandUUID() {
		return this->cmduuid;
	}

	string _BasicHeliumCommand::GetCommandString() {
		return this->commandstr;
	}
	string _BasicHeliumCommand::SetCommandString(string cmd) {
		string tempstr = this->commandstr;
		this->commandstr = cmd;
		return tempstr;
	}

	string _BasicHeliumCommand::GetCommandDesc() {
		return this->commanddesc;
	}
	string _BasicHeliumCommand::SetCommandDesc(string hint) {
		string tempstr = this->commanddesc;
		this->commanddesc = hint;
		return tempstr;
	}

	string _BasicHeliumCommand::GetCommandAtlas() {
		return this->atlas;
	}
	string _BasicHeliumCommand::SetCommandAtlas(string atlas) {
		string tempstr = this->atlas;
		this->atlas = atlas;
		return tempstr;
	}
#pragma endregion

	bool _BasicHeliumCommand::IsVaild() {
		bool ret = true;
		string wordbreakstr = " ";
		if (this->commandstr.empty()) ret = false;
		for(auto i = 0; i < wordbreakstr.length(); i ++)
			if (this->commandstr.find(wordbreakstr[i]) != string::npos
				|| this->atlas.find(wordbreakstr[i]) != string::npos) {
				ret = false;
				break;
			}
		return ret;
	}

	int ExecuteCommand(tree<_BasicHeliumCommand*>::pre_order_iterator cmdit) {
		return 0;
	}
}