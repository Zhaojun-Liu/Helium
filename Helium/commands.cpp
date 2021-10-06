#include"commands.h"

tree<_BasicHeliumCommand*> HeliumCommandTree;

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