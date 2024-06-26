#ifndef ETWP_I_ETW_BASED_PROFILER_HPP
#define ETWP_I_ETW_BASED_PROFILER_HPP

#include <windows.h>

#include "IProfiler.hpp"

#include "Utility/Macros.hpp"

namespace ETWP {

// Interface for thread-safe ETW-based profiler objects
class IETWBasedProfiler : public IProfiler {
public:
    ETWP_DISABLE_COPY_AND_MOVE (IETWBasedProfiler);

    struct ProviderInfo {
        GUID      providerID;
        bool      stack;
        UCHAR     level;
        ULONGLONG flags;
    };

    using Flags = uint8_t;

    enum Options : Flags {
        Default         = 0b00000,     
        RecordCSwitches = 0b00001,     // Record context switch information
        Compress        = 0b00010,     // Compress result ETL with ETW's built-in compression
        Debug           = 0b00100,     // Preserve intermediate ETL files (if any)
        StackCache      = 0b01000,     // Use ETW's stack caching feature
        ProfileChildren = 0b10000      // Profile child processes
    };

    IETWBasedProfiler () = default;
    virtual ~IETWBasedProfiler () = default;

    virtual bool EnableProvider (const ProviderInfo& providerInfo) = 0;

    virtual uint32_t GetNumberOfProfiledProcesses () = 0;
};

bool operator== (const IETWBasedProfiler::ProviderInfo& lhs, const IETWBasedProfiler::ProviderInfo& rhs);

}   // namespace ETWP

#endif  // #ifndef ETWP_I_ETW_BASED_PROFILER_HPP