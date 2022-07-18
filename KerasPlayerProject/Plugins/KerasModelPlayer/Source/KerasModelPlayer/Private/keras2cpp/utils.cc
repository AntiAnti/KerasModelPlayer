#include "utils.h"
//#include "CoreMinimal.h"

namespace keras2cpp {
    Stream::Stream(const std::string& filename)
    : stream_(filename, std::ios::binary)
    {
        /*
        if (!stream_.is_open())
            UE_LOG(LogTemp, Warning, TEXT("Cannot open file"));
        */
    }

    Stream& Stream::reads(char* ptr, size_t count)
    {
        stream_.read(ptr, static_cast<ptrdiff_t>(count));
        /*
        if (!stream_)
            UE_LOG(LogTemp, Warning, TEXT("File read failure"));
        */
        return *this;
    }
}
