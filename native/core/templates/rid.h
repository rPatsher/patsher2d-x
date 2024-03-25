#ifndef RID_H
#define RID_H



#include <cstdio>
#include <cstdint>

class ResourceID {
public:
    ResourceID() : typeID(-1), instanceID(-1) {}

    ResourceID(int typeID, int instanceID) : typeID(typeID), instanceID(instanceID) {}

    static ResourceID from_uint64(uint64_t value) {
        ResourceID result;
        result.typeID = static_cast<int>(value >> 32);
        result.instanceID = static_cast<int>(value & 0xFFFFFFFF);
        return result;
    }

    uint64_t get_id() const {
        return (static_cast<uint64_t>(typeID) << 32) | static_cast<uint64_t>(instanceID);
    }

    bool operator==(const ResourceID& other) const {
        return typeID == other.typeID && instanceID == other.instanceID;
    }

    bool operator!=(const ResourceID& other) const {
        return !(*this == other);
    }

    bool operator>(const ResourceID& other) const {
        return typeID > other.typeID || (typeID == other.typeID && instanceID > other.instanceID);
    }

    bool operator<(const ResourceID& other) const {
        return typeID < other.typeID || (typeID == other.typeID && instanceID < other.instanceID);
    }

    bool is_valid() const {
        return typeID >= 0 && instanceID >= 0;
    }

    bool is_null() const {
        return typeID == -1 && instanceID == -1;
    }

    int get_local_index() const {
        return instanceID % 100;
    }

private:
    int typeID;
    int instanceID;
};


#endif // RID_H