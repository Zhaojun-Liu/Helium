#pragma once
#define NULL 0

typedef struct {
	int pid = NULL;
} ServerStartEvent;

typedef struct {
	int port = NULL;
} ServerStartedEvent;

typedef struct {

} ServerStopEvent;

typedef struct {
	char* lpRawOutput = NULL;
} ServerInfoEvent;

typedef struct {
	char* lpRawOutput = NULL;
	char* lpPlayer = NULL;
} PlayerInfoEvent;




