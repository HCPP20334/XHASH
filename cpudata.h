// -- file: fCPUData.h --- 
// -- CPU Information by HCPP -- 
// -- For DevC++ join libgdi32.a and libpsapi.a --
// -- for Visual Studio  use #pragma comment(gdi32.lib); and #pragma comment(psapi.lib);--
// -- Writtein C++11 , Compiled MinGW GCC 4.9.2 64-bit --
//------------------------------------------------------------------------------------// 

#include <windows.h>
#include <malloc.h>    
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <vector>
#include <intrin.h>

#pragma intrinsic(__rdtsc)
class CPUInfo {public: float dCPUSpeedMHz; };
CPUInfo* pInfo = new CPUInfo;
int64_t ClearMemoryAddress() {
    delete pInfo;
    return 0;
}
int64_t GetProcessorSpeed()
{
    LARGE_INTEGER qwWait, qwStart, qwCurrent;
    QueryPerformanceCounter(&qwStart);
    QueryPerformanceFrequency(&qwWait);
    qwWait.QuadPart >>= 5;
    unsigned __int64 Start = __rdtsc();
    do
    {
        QueryPerformanceCounter(&qwCurrent);
    } while (qwCurrent.QuadPart - qwStart.QuadPart < qwWait.QuadPart);
    pInfo->dCPUSpeedMHz = ((__rdtsc() - Start) << 5) / 1000000.0;
    return pInfo->dCPUSpeedMHz;
}
char fDataVRAMUses()// Not Correct Work Function !!! Check Sym VRAM to Current Program //
{
    char* Address = (char*)((void*)0xB800);
    return *Address;
}
typedef BOOL(WINAPI* LPFN_GLPI)(
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
    PDWORD);


// Helper function to count set bits in the processor mask.
DWORD CountSetBits(ULONG_PTR bitMask) //  Work Function !!! Set count Bits //
{
    DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;
    DWORD bitSetCount = 0;
    ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
    DWORD i;

    for (i = 0; i <= LSHIFT; ++i)
    {
        bitSetCount += ((bitMask & bitTest) ? 1 : 0);
        bitTest /= 2;
    }

    return bitSetCount;
}
int64_t dDataCPU(int64_t fCode)
{
    LPFN_GLPI glpi;
    BOOL done = FALSE;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION buffer = NULL;
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = NULL;
    DWORD returnLength = 0;
    DWORD logicalProcessorCount = 0;
    DWORD numaNodeCount = 0;
    DWORD processorCoreCount = 0;
    DWORD processorL1CacheCount = 0;
    DWORD processorL2CacheCount = 0;
    DWORD processorL3CacheCount = 0;
    DWORD processorPackageCount = 0;
    DWORD processorL4CacheCount = 0;
    DWORD byteOffset = 0;
    PCACHE_DESCRIPTOR Cache;

    glpi = (LPFN_GLPI)GetProcAddress(
        GetModuleHandle(TEXT("kernel32")),
        "GetLogicalProcessorInformation");
    if (NULL == glpi)
    {
        _tprintf(TEXT("\n[CPU]GetLogicalProcessorInformation is not supported.\n"));
        return (1);
    }

    while (!done)
    {
        DWORD rc = glpi(buffer, &returnLength);

        if (FALSE == rc)
        {
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
                if (buffer)
                    free(buffer);

                buffer = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(
                    returnLength);

                if (NULL == buffer)
                {
                    _tprintf(TEXT("\nError: Allocation failure\n"));
                    return (2);
                }
            }
            else
            {
                _tprintf(TEXT("\nError %d\n"), GetLastError());
                return (3);
            }
        }
        else
        {
            done = TRUE;
        }
    }

    ptr = buffer;
    uint64_t l1offset = 0;
    while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLength)
    {
        switch (ptr->Relationship)
        {
        case RelationNumaNode:
            // Non-NUMA systems report a single record of this type.
            numaNodeCount++;
            break;

        case RelationProcessorCore:
            processorCoreCount++;

            // A hyperthreaded core supplies more than one logical processor.
            logicalProcessorCount += CountSetBits(ptr->ProcessorMask);
            break;

        case RelationCache:
            // Cache data is in ptr->Cache, one CACHE_DESCRIPTOR structure for each cache. 
            Cache = &ptr->Cache;
          
            if (Cache->Level == 1)
            {
              // std::cout << "test size:" << Cache->Size << std::endl;
                processorL1CacheCount++;
            }
            else if (Cache->Level == 2)
            {
                processorL2CacheCount++;
            }
            else if (Cache->Level == 3)
            {
                processorL3CacheCount++;
            }
            else if (Cache->Level == 4)
            {
                processorL4CacheCount++;
            }
            break;

        case RelationProcessorPackage:
            // Logical processors share a physical package.
            processorPackageCount++;
            break;

        default:
            _tprintf(TEXT("\nError: Unsupported LOGICAL_PROCESSOR_RELATIONSHIP value.\n"));
            break;
        }
        byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
        ptr++;
    }

    //    _tprintf(TEXT("\nGetLogicalProcessorInformation results:\n"));
    //    _tprintf(TEXT("Number of NUMA nodes: %d\n"), 
    //             numaNodeCount);
    //    _tprintf(TEXT("Number of physical processor packages: %d\n"), 
    //             processorPackageCount);
    //    _tprintf(TEXT("Number of processor cores: %d\n"), 
    //             processorCoreCount);
    //    _tprintf(TEXT("Number of logical processors: %d\n"), 
    //             logicalProcessorCount);
    //    _tprintf(TEXT("Number of processor L1/L2/L3 caches: %d/%d/%d\n"), 
    //             processorL1CacheCount,
    //             processorL2CacheCount,
    //             processorL3CacheCount);
    if (fCode == 1)
    {
        return numaNodeCount;
    }
    if (fCode == 2)
    {
        return processorPackageCount;
    }
    if (fCode == 3)
    {
        return processorCoreCount;
    }
    if (fCode == 4)
    {
        return logicalProcessorCount;
    }
    if (fCode == 5)
    {
        return processorL1CacheCount;
    }
    if (fCode == 6)
    {
        return processorL2CacheCount;
    }
    if (fCode == 7)
    {
        return processorL3CacheCount;
    }
    if (fCode == 8) {
        return processorL4CacheCount;
    }
    free(buffer);

    return 0;
}
