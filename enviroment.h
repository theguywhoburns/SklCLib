#ifndef _SKLC_DATALANG_ENVIROMENT_H_
#define _SKLC_DATALANG_ENVIROMENT_H_

#include <defines.h>
#include <util/string.h>
#include <util/path.h>
#include <util/args.h>
#include <util/array.h>

typedef enum _EnviromentVariableTarget {
    ENV_TARGET_MACHINE = 2,
    ENV_TARGET_PROCESS = 0,
    ENV_TARGET_USER    = 1
} EnviromentVariableTarget;

typedef enum _EnviromentSpecialFolder {
    EnviromentSpecialFolder_AdminTools                = 48,
    EnviromentSpecialFolder_ApplicationData           = 26,
    EnviromentSpecialFolder_CDBurning                 = 59,
    EnviromentSpecialFolder_CommonAdminTools          = 47,
    EnviromentSpecialFolder_CommonApplicationData     = 35,
    EnviromentSpecialFolder_CommonDesktopDirectory    = 25,
    EnviromentSpecialFolder_CommonDocuments           = 46,
    EnviromentSpecialFolder_CommonMusic               = 53,
    EnviromentSpecialFolder_CommonOemLinks            = 58,
    EnviromentSpecialFolder_CommonPictures            = 54,
    EnviromentSpecialFolder_CommonProgramFiles        = 43,
    EnviromentSpecialFolder_CommonProgramFilesX86     = 44,
    EnviromentSpecialFolder_CommonPrograms            = 23,
    EnviromentSpecialFolder_CommonStartMenu           = 22,
    EnviromentSpecialFolder_CommonStartup             = 24,
    EnviromentSpecialFolder_CommonTemplates           = 45,
    EnviromentSpecialFolder_CommonVideos              = 55,
    EnviromentSpecialFolder_Cookies                   = 33,
    EnviromentSpecialFolder_Desktop                   = 0,
    EnviromentSpecialFolder_DesktopDirectory          = 16,
    EnviromentSpecialFolder_Favorites                 = 6,
    EnviromentSpecialFolder_Fonts                     = 20,
    EnviromentSpecialFolder_History                   = 34,
    EnviromentSpecialFolder_InternetCache             = 32,
    EnviromentSpecialFolder_LocalApplicationData      = 28,
    EnviromentSpecialFolder_LocalizedResources        = 57,
    EnviromentSpecialFolder_MyComputer                = 17,
    EnviromentSpecialFolder_MyMusic                   = 5,
    EnviromentSpecialFolder_MyPictures                = 39,
    EnviromentSpecialFolder_MyVideos                  = 14,
    EnviromentSpecialFolder_NetworkShortcuts          = 19,
    EnviromentSpecialFolder_Personal                  = 5,
    EnviromentSpecialFolder_PrinterShortcuts          = 27,
    EnviromentSpecialFolder_ProgramFiles              = 38,
    EnviromentSpecialFolder_ProgramFilesX86           = 42,
    EnviromentSpecialFolder_Programs                  = 2,
    EnviromentSpecialFolder_Recent                    = 8,
    EnviromentSpecialFolder_Resources                 = 56,
    EnviromentSpecialFolder_SendTo                    = 9,
    EnviromentSpecialFolder_StartMenu                 = 11,
    EnviromentSpecialFolder_Startup                   = 7,
    EnviromentSpecialFolder_System                    = 37,
    EnviromentSpecialFolder_SystemX86                 = 41,
    EnviromentSpecialFolder_Templates                 = 21,
    EnviromentSpecialFolder_UserProfile               = 40,
    EnviromentSpecialFolder_Windows                   = 36
} EnviromentSpecialFolder;

typedef enum EnviromentSpecialFolderOption {
    EnviromentSpecialFolderOption_Create        = 32768,
    EnviromentSpecialFolderOption_DoNotVerify   = 16384,
    EnviromentSpecialFolderOption_None          = 0
} EnviromentSpecialFolderOption;

typedef struct _Enviroment {
    // Variables
    string* CommandLine;
    string* CurrentDirectory;
    int CurrentManagedTreadID;
    int exit_code;
    bool HasShutdownStarted;
    bool Is64BitOS;
    bool Is64BitProcess;
    bool IsPrivilegedProcess;
    const char* MachineName;
    const char* NewLine;
    const char* OsVersion;
    int ProcessId;
    int ProcessorCount;
    int ProcessPath;
    string* StackTrace;
    const char* SystemDirectory;
    uint64_t* SystemPageSize;
    int* TickCount;
    long long* TickCount64;
    string* UserDomainName;
    bool UserInteractive;
    string* UserName;
    string* Version;
    uint64_t* WorkingSet;

    // Functions
    void (*Exit)(int ExitCode);
    void (*ExpandEnviromentVariables)(string* out, string* in);
    /// @param message if no message pass NULL
    void (*FailFast)(string* message);
    //TODO: FastFailEx
    void (*FailFastEx)(string* message);
    args (*GetCommandLineArgs)();
    string*(*GetEnviromentVariable)(string variable);
    string*(*GetEnviromentVariableTarget)(string variable, EnviromentVariableTarget target);
    string*(*GetEnviromentVariableCCP)(const char* variable);
    string*(*GetEnviromentVariableTargetCCP)(const char* variable, EnviromentVariableTarget target);
    
    struct Dictionary (*GetEnviromentVariables)();
    struct Dictionary (*GetEnviromentVariablesTarget)(EnviromentVariableTarget target);
    string (*GetFolderPath)(EnviromentSpecialFolder specfolder);
    string (*GetFolderPathEx)(EnviromentSpecialFolder specfolder, EnviromentSpecialFolderOption opt);
    // Returns an array of strings, the strings have to be freed manually
    array (*GetLogicalDrives)();

    void (*SetEnviromentVariable)(string variable, string value);
    void (*SetEnviromentVariableCCP)(const char* variable, const char* value);

    void (*SetEnviromentVariableEx)(string variable, string value, EnviromentVariableTarget target);
    void (*SetEnviromentVariableCCPEx)(const char* variable, const char* value, EnviromentVariableTarget target);
} _Enviroment;

extern _Enviroment Enviroment;
bool Enviroment_Init(_Enviroment* env, int* argc, char*** argv);
void Enviroment_Shutdown(_Enviroment* env);

#endif//_SKLC_DATALANG_ENVIROMENT_H_