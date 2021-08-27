#include <stdio.h>
#include <shlwapi.h>

void test(char* path, char* args) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    char path_[MAX_PATH];
    char args_[MAX_PATH];

    sprintf(path_, path ? "\"%s\"" : "%d", path ? path : 0);
    sprintf(args_, args ? "\"%s\"" : "%d", args ? args : 0);

    char res[MAX_PATH];

    if(!CreateProcessA(path, args, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) ) {
        sprintf(res, "fail %d", GetLastError());
    } else {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        sprintf(res, "pass");
    }

    printf("lpApplicationName = %s lpCommandLine = %s %s\n", path_, args_, res);
}

void get_app_dirname(char* buf, int buf_size) {
	GetModuleFileNameA(0, buf, buf_size);
	PathRemoveFileSpecA(buf);
}

void test1() {
    printf("\nname tests\n");
    
    test("callee1", 0);
    test(0, "callee1");
    test("callee1", "foo bar");
    test("callee1", " foo bar");
    test("callee1 foo bar", 0);
    test(0, "callee1 foo bar");

    char path[MAX_PATH];
    get_app_dirname(path, MAX_PATH);
    strcat(path, "\\callee1.exe");
    char path_args[MAX_PATH];
    strcpy(path_args, path);
    strcat(path_args, " foo bar");

    printf("\nfull path tests\n");

    test(path, 0);
    test(0, path);
    test(path, "foo bar");
    test(path, " foo bar");
    test(path_args, 0);
    test(0, path_args);
}

void test2() {
    char path[MAX_PATH];
    get_app_dirname(path, MAX_PATH);
    strcat(path, "\\callee2.exe");
    char path_args[MAX_PATH];
    strcpy(path_args, path);
    strcat(path_args, " foo bar");

    test(0, "callee2 foo bar");


    test(path, "foo bar");
 

    test(0, path_args);
 
}




int main(int argc, char** argv) {

    if (argc > 1 && strcmp(argv[1], "test1") == 0) {
        test1();
    } else if (argc > 1 && strcmp(argv[1], "test2") == 0) {
        test2();
    } else {
        printf("usage: %s test1 | test2\n", argv[0]);
        return 1;
    }

    return 0;
}