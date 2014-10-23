/*  This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. 
	
	Created by Adam Kramer [2014] - Email: adamkramer at hotmail dot com */

#include "stdafx.h"
#include "Windows.h"

using namespace System;

int main(int argc, char* argv[])
{

	/* Intro line */
	Console::WriteLine(L"Handle Inheritor - Created by Adam Kramer [2014]");
	
	/* Check that we have received the required arguments */
	if (argc != 3)
	{
		Console::WriteLine(L"Usage: handleinheritor.exe <executable to launch> <file we want to include a handle to>");
		return 1;
	}

	/* Setup the security structure for the CreateFile call, to allow handle inheritence */
	SECURITY_ATTRIBUTES sa;
	sa.nLength=sizeof(sa);
	sa.lpSecurityDescriptor=NULL; 
	sa.bInheritHandle=TRUE; 
	
	/* Convert argument 2 to wide char pointer */
	wchar_t w[MAX_PATH];
	mbstowcs(w, argv[2], MAX_PATH);
	LPWSTR pFile = w;

	/* Create handle to requested file */
	HANDLE hFile = CreateFile (pFile, GENERIC_READ, FILE_SHARE_READ, &sa, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	/* Error catching for handle creation */
	if (hFile == INVALID_HANDLE_VALUE)
	{
		Console::WriteLine(L"Error: Unable to create handle to file - check path to file");
		return 1;
	}

	/* Create variables required for CreateProcess */
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

	/* Convert argument 1 to wide char pointer */
	wchar_t x[MAX_PATH];
	mbstowcs(x, argv[1], MAX_PATH);
	LPWSTR pProcess = x;

	/* Launch process with error catching */
	if (!CreateProcess(pProcess, NULL, &sa, &sa, TRUE, 0, NULL, NULL, &si, &pi))
	{
		Console::WriteLine(L"Error: Unable to launch process - check path to file");
		return 1;
	}

	/* Inform user everything has worked */
	Console::WriteLine(L"Process successfully spawned with specified handle inherited");

    return 0;
}
