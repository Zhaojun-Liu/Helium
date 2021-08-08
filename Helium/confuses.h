#pragma once

#ifndef _H_CONFUSES
#define _H_CONFUSES

#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include"logger.h"
#include"commands.h"
#include"parse.h"
#include"utils.h"
#include<vector>
#include"xmlutils.h"
typedef ServerStartEvent ooOoo00o;
typedef ServerStartedEvent ooOo00o;
typedef tinyxml2::XMLElement awQ;
typedef string ooU;
typedef bool buT;
typedef const char* Oo0;
typedef ostringstream FaQ;
typedef Logger AeX;
typedef int SsS;
typedef string hCr;
typedef FaQ qfa;
#define fra return
#define OOO fra
#define RyN OOO
//GetNodeStringByName
ooU _stdcall DuN(awQ *PQb, ooU eCd) {
	fra GetNodeStringByName(PQb, eCd);
}
//GetNodePointerByName
buT _stdcall TcD(awQ* pRE, Oo0 sNN, awQ*& NhE) {
	fra GetNodePointerByName(pRE, sNN, NhE);
}
//ParseServerStart
ooOoo00o _stdcall oOO(Oo0 OooO) {
	OOO ParseServerStart(OooO);
}
//ParseServerStarted
ooOo00o _stdcall OOo(Oo0 oOOo00) {
	RyN ParseServerStarted(oOOo00);
}

#endif

