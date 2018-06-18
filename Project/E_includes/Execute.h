#pragma once
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <process.h>
#include <windows.h> 

/*
*	function that run an executable file
*/
void RunProcess(const char* name)
{
	const char* a[1];			// string for arguments
	a[0] = name;
	// -------------------- CreateProcces -----------------------------------//
	PROCESS_INFORMATION pif;
	STARTUPINFOA si;				//Defines how to start the program
	ZeroMemory(&si, sizeof(si));	//Zero the STARTUPINFO struct
	si.cb = sizeof(si);				//Must set size of structure
	BOOL _bRet = CreateProcessA(a[0],
		NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pif);
	if (!_bRet)
		puts("create process failed");

	WaitForSingleObject(pif.hProcess, INFINITE);	//Wait for process to end
	CloseHandle(pif.hProcess);
	CloseHandle(pif.hThread);
}