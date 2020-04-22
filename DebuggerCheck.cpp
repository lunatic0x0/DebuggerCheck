#include <iostream>
#include <tchar.h>
#include <Windows.h>

#pragma comment(lib,"ntdll.lib")

EXTERN_C NTSTATUS NTAPI NtQueryInformationProcess(HANDLE hProcess, ULONG InfoClass, PVOID Buffer, ULONG Length, PULONG ReturnLength);

#define NtCurrentProcess() (HANDLE)-1

void WINAPI tls_callback(PVOID Dllhandle, DWORD Reason, PVOID Reserved) {

	HANDLE DebugPort = NULL;

	if (!NtQueryInformationProcess(NtCurrentProcess(), 7, &DebugPort, sizeof(HANDLE), NULL))
	{
		if (DebugPort)
		{
			MessageBox(NULL, _T("Debugger detected"), _T("TLS callback"), MB_ICONSTOP);
		}

		else
		{
			MessageBox(NULL, _T("No debugger detected"), _T("TLS callback"), MB_ICONINFORMATION);
		}
	}
}

#pragma comment(linker, "/INCLUDE:_tls_used")
#pragma comment(linker, "/INCLUDE:p_tls_callback")
#pragma const_seg(push)
#pragma const_seg(".CRT$XLA")

EXTERN_C const PIMAGE_TLS_CALLBACK p_tls_callback = tls_callback;
#pragma const_seg(pop)

int main()
{
	printf("Hello World");
}

