/*
* Helium Pre-Alpha 0.6.1
*
* Helium is a customizable extension system for Minecraft server which is written in C++.
* This project is inspired by the [Fallen-Breath/MCDReforged](https://github.com/Fallen-Breath/MCDReforged).
* We target to provide a liter, faster, and more customizable choice.
* As a trade-off, we sacrifice its portability and the simplicity of writing extensions.
* (we r sry that we haven't finish the first alpha version yet, if u r interested in our project, we recommend u to use mcdr as a temporary alternative)
* This project is licensed by the GPL-3.0-or-later license.
*
* Very very special thank to contributors of the following projects:
* [Fallen-Breath/MCDReforged](https://github.com/Fallen-Breath/MCDReforged)
* [kpeeters/tree.hh](https://github.com/kpeeters/tree.hh)
* [leethomason/tinyxml2](https://github.com/leethomason/tinyxml2/)
* [jcwangxp/Crossline](https://github.com/jcwangxp/Crossline/)
*
* You can get the lastest source code and releases of Helium at :
* https://github.com/Minecraft1248/Helium
*
* -------------------------------------------------------------------------------------------------------------------------------------------------------
* Helium Pre-Alpha 0.6.1
* Copyright (C) 2021-2022 HeliumDevTeam
* This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
* This is free software, and you are welcome to redistribute it
* under certain conditions; type `show c' for details.
* -------------------------------------------------------------------------------------------------------------------------------------------------------
*/

#pragma once

#ifndef _H_COMMANDS
#define _H_COMMANDS

#include<map>
#include<string>

#include"Crossline/crossline.h"
#include"tree.hh/tree.hh"
namespace Helium {
	using namespace std;
	//fully rewrited command module during the 72th national day xd

	class _BasicHeliumCommand;
	class CommandConstantString;
	class CommandPlaceHolder;

	class _CommandArgument;
	class _ArgumentNumber;
	class CommandArgumentInt;
	class CommandArgumentLongInt;
	class CommandArgumentFloat;
	class CommandArgumentLongFloat;
	class CommandArgumentDouble;
	class CommandArgumentLongDouble;
	class _ArgumentString;
	class CommandArgumentString;
	class CommandArgumentQuotableString;
	class CommandArgumentGreedyString;

	class _CommandEntry;
	class CommandEntry;

	class _CommandRoot;

	class _CommandBinding;
	class SingleFixedCommandBind;
	class SingleVariableCommandBind;
	class MultiFixedCommandBind;
	class MultiVariableCommandBind;


	class _BasicHeliumCommandQueue;

	class ShellCommandQueue;
	class RuntimeCommandQueue;
	class SaveableCommandQueue;

	extern tree<_BasicHeliumCommand*> HeliumCommandTree;

	bool CheckCommandValidance(tree<_BasicHeliumCommand*>::iterator cmdit);

#pragma region CommandClassBase
	class _BasicHeliumCommand {
	protected:
		string commanddesc;
		string commandstr;

		bool listenabled;
		bool execenabled;
		bool hintenabled;
		bool autocompenabled;
	public:
		virtual _BasicHeliumCommand* GetCommandClassType();
	};
	class _CommandRoot : virtual public _BasicHeliumCommand {
	public:
		virtual _CommandRoot* GetCommandClassType();
	};
	class _CommandArgument : virtual public _BasicHeliumCommand {
	protected:
		bool optional;
		bool preprocenable;
	public:
		virtual _CommandArgument* GetCommandClassType();
		virtual bool EnablePreprocessing();
		virtual bool DisablePreprocessing();
	};
	class _CommandEntry : virtual public _BasicHeliumCommand {
	protected:
		int exectype;
		union execinfo {

		};

		bool hasargument;
	public:
		virtual _CommandEntry* GetCommandClassType();
	};
	class _CommandBinding : virtual public _BasicHeliumCommand {
	public:
		virtual _CommandBinding* GetCommandClassType();
	};
	class _ArgumentNumber : public _CommandArgument {
	public:
		virtual _ArgumentNumber* GetCommandClassType();
		virtual void SetUpperbound() = 0;
		virtual void SetLowerbound() = 0;
		virtual void GetUpperbound() = 0;
		virtual void GetLowerbound() = 0;
	protected:
		bool precheckenable;
	};
	class _ArgumentString : public _CommandArgument {
	public:
		virtual _ArgumentString* GetCommandClassType();
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
	class CommandArgumentLongInt : public _ArgumentNumber {
	public:
		virtual CommandArgumentLongInt* GetCommandClassType();
		virtual long int SetUpperbound(long int up);
		virtual long int SetLowerbound(long int down);
		virtual long int GetUpperbound(long int up);
		virtual long int GetLowerbound(long int down);
	protected:
		long int upperbound;
		long int lowerbound;
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
	class CommandArgumentLongFloat : public _ArgumentNumber {
	public:
		virtual CommandArgumentLongFloat* GetCommandClassType();
		virtual long float SetUpperbound(long float up);
		virtual long float SetLowerbound(long float down);
		virtual long float GetUpperbound(long float up);
		virtual long float GetLowerbound(long float down);
	protected:
		long float upperbound;
		long float lowerbound;
	};
	class CommandArgumentDouble : public _ArgumentNumber {
	public:
		virtual CommandArgumentDouble* GetCommandClassType();
		virtual double SetUpperbound(double up);
		virtual double SetLowerbound(double down);
		virtual double GetUpperbound(double up);
		virtual double GetLowerbound(double down);
	protected:
		double upperbound;
		double lowerbound;
	};
	class CommandArgumentLongDouble : public _ArgumentNumber {
	public:
		virtual CommandArgumentLongDouble* GetCommandClassType();
		virtual long double SetUpperbound(long double up);
		virtual long double SetLowerbound(long double down);
		virtual long double GetUpperbound(long double up);
		virtual long double GetLowerbound(long double down);
	protected:
		long double upperbound;
		long double lowerbound;
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
	class CommandConstantString : virtual public _BasicHeliumCommand {
	public:
		virtual CommandConstantString* GetCommandClassType();
	};
	class CommandPlaceHolder : virtual public _BasicHeliumCommand {
	public:
		virtual CommandPlaceHolder* GetCommandClassType();
	};
	class CommandEntry : virtual public _CommandEntry {
	public:
		virtual CommandEntry* GetCommandClassType();
	};
	class SingleFixedCommandBind : virtual public _CommandBinding {
	public:
		virtual SingleFixedCommandBind* GetCommandClassType();
	};
	class SingleVariableCommandBind : virtual public _CommandBinding {
	public:
		virtual SingleVariableCommandBind* GetCommandClassType();
	};
	class MultiFixedCommandBind : virtual public _CommandBinding {
	public:
		virtual MultiFixedCommandBind* GetCommandClassType();
	};
	class MultiVariableCommandBind : virtual public _CommandBinding {
	public:
		virtual MultiVariableCommandBind* GetCommandClassType();
	};


	class _BasicHeliumCommandQueue {
	protected:
		int queuetype;
		int queuestate;
		vector<string>::iterator execit;

		vector<string> originalcommands;
	public:
		virtual _BasicHeliumCommandQueue* GetCommandQueueClassType();
	};
	class ShellCommandQueue : virtual public _BasicHeliumCommandQueue {
	public:
		virtual ShellCommandQueue* GetCommandQueueClassType();
	};
	class RuntimeCommandQueue : virtual public _BasicHeliumCommandQueue {
	public:
		virtual RuntimeCommandQueue* GetCommandQueueClassType();
	};
	class SaveableCommandQueue : virtual public _BasicHeliumCommandQueue {
	public:
		virtual SaveableCommandQueue* GetCommandQueueClassType();
	};
#endif // !_H_COMMANDS
}