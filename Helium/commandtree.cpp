#include"commandtree.h"

tree<HeliumCommandRegisterInstance> commandtree;

int _stdcall HeliumCommandRegisterInstance::operator=(HeliumCommandRegisterInstance* ins)
{
	this->callbackfn = ins->callbackfn;
	this->cmddesc = ins->cmddesc;
	this->cmd = ins->cmd;
	return 0;
}

int _stdcall RegisterCommand(tree<HeliumCommandRegisterInstance>::iterator root, HeliumCommandRegisterInstance ins) {
	commandtree.append_child(root, ins);
	return 0;
}
int _stdcall DeleteCommand(tree<HeliumCommandRegisterInstance>::iterator root) {
	commandtree.erase_children(root);
	commandtree.erase(root);
	return 0;
}
int _stdcall SetupBuiltinCommand() {
	return 0;
}