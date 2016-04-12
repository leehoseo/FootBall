#pragma once

#define SAFE_DELETE(ptr) { if (nullptr != ptr) delete ptr; ptr = NULL; }

enum GAME_STATE { INIT, READY, RUNNING, STOP, SUCCESS, FAILED, RESULT };