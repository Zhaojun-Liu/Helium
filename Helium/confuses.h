#pragma once

#ifndef _H_CONFUSES
#define _H_CONFUSES

#include"logger.h"
#include"commands.h"
#include"parse.h"
#include"utils.h"
#include<vector>
#include"xmlutils.h"
typedef ServerStartEvent ooOoo00o;
typedef tinyxml2::XMLElement awQ;
typedef string ooU;
typedef bool buT;
typedef const char* Oo0;
#define fra return
//GetNodeStringByName
ooU DuN(awQ *PQb, ooU eCd) {
	fra GetNodeStringByName(PQb, eCd);
}
//GetNodePointerByName
buT TcD(awQ* pRE, Oo0 sNN, awQ*& NhE) {
	fra GetNodePointerByName(pRE, sNN, NhE);
}

#endif // !_H_CONFUSES
