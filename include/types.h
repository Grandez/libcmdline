#pragma once

#ifndef __CMDLINE_CTYPES__
#define __CMDLINE_CTYPES__


typedef enum _Type {
	STRING=0, CHAR, BOOL,
	NUMBER, DECIMAL, LONGNUMBER, LONGDECIMAL,
	DATE, TIME, DATETIME, TMS,
	DIR, DIR_EXISTS, FILES, FILE_EXISTS,
	FLAG
} Type;
typedef enum _logical { TRUE=-1, FALSE = 0, MISSING=1 } logical;

typedef enum { DEFAULT, ENV, CMDLINE, CODE, AUTO } Source;


typedef struct _ParmDef {
	const char* name;
	Type type;
	char* value;
	logical multiple;
} ParmDef;

typedef struct _Parameter {
	const char* name;
	const char** values;
	int          size;
} Parameter;
typedef struct _Flag {
	const char* name;
	logical value;
} Flag;

//JGG Ajustar a diferentes sistemas
/*
typedef struct _Path {
	char path_buffer[_MAX_PATH];
	char drive[MAX_DRIVE];
	char dir[MAX_DIR];
	char fname[MAX_FNAME];
	char ext[MAX_EXT];
	char dir; // -1 if dir, 0 if file
} Path;
*/
#endif
