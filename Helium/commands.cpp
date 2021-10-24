#include"commands.h"
namespace Helium {
	tree<_BasicHeliumCommand*> HeliumCommandTree;
	Replxx rx;

	bool CheckCommandValidance(tree<_BasicHeliumCommand*>::iterator cmdit)
	{
		return false;
	}
	int InitReplxx()
	{
		rx.install_window_change_handler();
		rx.set_word_break_characters(" ");
		rx.set_completion_callback(hook_completion);
		rx.set_hint_callback(hook_hint);
		rx.set_highlighter_callback(hook_color);
		rx.set_completion_count_cutoff(128);
		rx.set_max_hint_rows(4);
		rx.set_complete_on_empty(true);
		rx.set_double_tab_completion(false);
		rx.set_no_color(false);
		rx.set_immediate_completion(true);

		rx.history_load("heliumcommandhistory.txt");
		rx.set_max_history_size(256);

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
		return 0;
	}
	/*
	while (true) {
            string inputcmd = rx.input(str.str().c_str());
            cout << inputcmd << endl;
            rx.history_add(inputcmd);
        }

        rx.history_sync("heliumcommandhistory.txt");
        rx.history_save("heliumcommandhistory.txt");
	*/

#pragma region GetCommandClassType
	_BasicHeliumCommand* _BasicHeliumCommand::GetCommandClassType()
	{
		return this;
	}

	_CommandArgument* _CommandArgument::GetCommandClassType()
	{
		return this;
	}

	_CommandEntry* _CommandEntry::GetCommandClassType()
	{
		return this;
	}

	_CommandRoot* _CommandRoot::GetCommandClassType()
	{
		return this;
	}
	_CommandBinding* _CommandBinding::GetCommandClassType()
	{
		return this;
	}
	CommandConstantString* CommandConstantString::GetCommandClassType()
	{
		return this;
	}
	CommandPlaceHolder* CommandPlaceHolder::GetCommandClassType()
	{
		return this;
	}
	CommandEntry* CommandEntry::GetCommandClassType()
	{
		return this;
	}
	SingleFixedCommandBind* SingleFixedCommandBind::GetCommandClassType()
	{
		return this;
	}
	SingleVariableCommandBind* SingleVariableCommandBind::GetCommandClassType()
	{
		return this;
	}
	MultiFixedCommandBind* MultiFixedCommandBind::GetCommandClassType()
	{
		return this;
	}
	MultiVariableCommandBind* MultiVariableCommandBind::GetCommandClassType()
	{
		return this;
	}
#pragma endregion

#pragma region GetCommandQueueClassType
	_BasicHeliumCommandQueue* _BasicHeliumCommandQueue::GetCommandQueueClassType()
	{
		return this;
	}
	ShellCommandQueue* ShellCommandQueue::GetCommandQueueClassType()
	{
		return this;
	}
	RuntimeCommandQueue* RuntimeCommandQueue::GetCommandQueueClassType()
	{
		return this;
	}
	SaveableCommandQueue* SaveableCommandQueue::GetCommandQueueClassType()
	{
		return this;
	}
#pragma endregion

#pragma region ReplxxCallback
	Replxx::completions_t hook_completion(std::string const& context, int& contextLen) {
		Replxx::completions_t completions;
		return completions;
	}
	Replxx::hints_t hook_hint(std::string const& context, int& contextLen, Replxx::Color& color) {
		Replxx::hints_t hints;
		return hints;
	}
	void hook_color(std::string const& context, Replxx::colors_t& colors) {
		return;
	}
#pragma endregion
}