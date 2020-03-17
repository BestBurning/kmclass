// common.h
#pragma once
#include <ntddk.h>
#include "kmclass.h"



//----------------------------------------------------
// 回调函数声明
typedef VOID(*MY_KEYBOARDCALLBACK) (PDEVICE_OBJECT  DeviceObject,
	PKEYBOARD_INPUT_DATA  InputDataStart,
	PKEYBOARD_INPUT_DATA  InputDataEnd,
	PULONG  InputDataConsumed);

typedef VOID(*MY_MOUSECALLBACK) (PDEVICE_OBJECT  DeviceObject,
	PMOUSE_INPUT_DATA  InputDataStart,
	PMOUSE_INPUT_DATA  InputDataEnd,
	PULONG  InputDataConsumed);


typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemBasicInformation = 0,
	SystemCpuInformation = 1,
	SystemPerformanceInformation = 2,
	SystemTimeOfDayInformation = 3, /* was SystemTimeInformation */
	Unknown4,
	SystemProcessInformation = 5,
	Unknown6,
	Unknown7,
	SystemProcessorPerformanceInformation = 8,
	Unknown9,
	Unknown10,
	SystemModuleInformation = 11,
	Unknown12,
	Unknown13,
	Unknown14,
	Unknown15,
	SystemHandleInformation = 16,
	Unknown17,
	SystemPageFileInformation = 18,
	Unknown19,
	Unknown20,
	SystemCacheInformation = 21,
	Unknown22,
	SystemInterruptInformation = 23,
	SystemDpcBehaviourInformation = 24,
	SystemFullMemoryInformation = 25,
	SystemNotImplemented6 = 25,
	SystemLoadImage = 26,
	SystemUnloadImage = 27,
	SystemTimeAdjustmentInformation = 28,
	SystemTimeAdjustment = 28,
	SystemSummaryMemoryInformation = 29,
	SystemNotImplemented7 = 29,
	SystemNextEventIdInformation = 30,
	SystemNotImplemented8 = 30,
	SystemEventIdsInformation = 31,
	SystemCrashDumpInformation = 32,
	SystemExceptionInformation = 33,
	SystemCrashDumpStateInformation = 34,
	SystemKernelDebuggerInformation = 35,
	SystemContextSwitchInformation = 36,
	SystemRegistryQuotaInformation = 37,
	SystemCurrentTimeZoneInformation = 44,
	SystemTimeZoneInformation = 44,
	SystemLookasideInformation = 45,
	SystemSetTimeSlipEvent = 46,
	SystemCreateSession = 47,
	SystemDeleteSession = 48,
	SystemInvalidInfoClass4 = 49,
	SystemRangeStartInformation = 50,
	SystemVerifierInformation = 51,
	SystemAddVerifier = 52,
	SystemSessionProcessesInformation = 53,
	SystemInformationClassMax
} SYSTEM_INFORMATION_CLASS, * PSYSTEM_INFORMATION_CLASS;



typedef struct _SYSTEM_MODULE_INFORMATION {//Information Class 11

	ULONG     Reserved[2];
	PVOID     Base;
	ULONG     Size;
	ULONG     Flags;
	USHORT    Index;
	USHORT    Unknown;
	USHORT    LoadCount;
	USHORT    ModuleNameOffset;
	CHAR      ImageName[256];

}SYSTEM_MODULE_INFORMATION, * PSYSTEM_MODULE_INFORMATION;


typedef struct _SYSMODULE_LIST {

	ULONG                        dwNumberOfModules;
	SYSTEM_MODULE_INFORMATION    SysModuleInfo[1];

} SYSMODULE_LIST, * PSYSMODULE_LIST;


typedef struct _SYSTEM_SERVICE_TABLE {

	PULONG ServiceTableBase;                //这个指向系统服务函数地址表
	PULONG ServiceCounterTableBase;
	ULONG NumberOfService;                  //服务函数的个数
	ULONG ParamTableBase;

}SYSTEM_SERVICE_TABLE, * PSYSTEM_SERVICE_TABLE;


typedef struct _SERVICE_DESCRIPTOR_TABLE {

	SYSTEM_SERVICE_TABLE ntoskrnel;         //ntoskrnl.exe的服务函数
	SYSTEM_SERVICE_TABLE win32k;            //win32k.sys的服务函数,(gdi.dll/user.dll的内核支持)
	SYSTEM_SERVICE_TABLE NotUsed1;
	SYSTEM_SERVICE_TABLE NotUsed2;

}SYSTEM_DESCRIPTOR_TABLE, * PSYSTEM_DESCRIPTOR_TABLE;



// 声明为导出变量

#ifdef __cplusplus
extern "C"
{
#endif


	NTSTATUS
		ObReferenceObjectByName(
			IN PUNICODE_STRING ObjectName,
			IN ULONG Attributes,
			IN PACCESS_STATE PassedAccessState OPTIONAL,
			IN ACCESS_MASK DesiredAccess OPTIONAL,
			IN POBJECT_TYPE ObjectType,
			IN KPROCESSOR_MODE AccessMode,
			IN OUT PVOID ParseContext OPTIONAL,
			OUT PVOID* Object
			);


	extern POBJECT_TYPE* IoDriverObjectType;
	extern PSYSTEM_DESCRIPTOR_TABLE KeServiceDescriptorTable;


#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////

