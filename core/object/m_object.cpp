#include "m_object.h"
#include <cstdlib>

// Static pointer initialization
MObject* MObject::staticPointer = nullptr;

// Constructor
MObject::MObject() {
    // Initialization if needed
}

// Destructor
MObject::~MObject() {
    // Cleanup if needed
}

// Const version: Get the value for a given key
int MObject::get(const std::string& key) const {
    // If the key is not found, return a default value (0 in this case)
    auto it = dataMap.find(key);
    return (it != dataMap.end()) ? it->second : 0;
}

// Const version: Set the value for a given key
void MObject::set(const std::string& key, int value) const {
    // Using const_cast to allow modification in a const function
    const_cast<std::map<std::string, int>&>(dataMap)[key] = value;
}

// Get the property for a given key
std::string MObject::get_property(const std::string& key) const {
    auto it = propertyMap.find(key);
    return (it != propertyMap.end()) ? it->second : "";
}

MObject::zero_fill_memory(size_t size) {
    if (dynamicMemory) {
        std::memset(dynamicMemory.get(), 0, size);
    }
}

// Memory-related function: Set a value at a specific offset in dynamic memory
void MObject::set_memory_value(size_t offset, int value) {
    if (dynamicMemory) {
        int* memoryInt = reinterpret_cast<int*>(dynamicMemory.get() + offset);
        *memoryInt = value;
    }
}

// Memory-related function: Get a value from a specific offset in dynamic memory
int MObject::get_memory_value(size_t offset) const {
    if (dynamicMemory) {
        const int* memoryInt = reinterpret_cast<const int*>(dynamicMemory.get() + offset);
        return *memoryInt;
    }
    return 0; // Default value if dynamic memory is not allocated
}

// Get the property array for a given key
std::vector<std::string> MObject::get_property_array(const std::string& key) const {
    auto it = propertyArrayMap.find(key);
    return (it != propertyArrayMap.end()) ? it->second : std::vector<std::string>();
}

// Get and set properties with a single function call
std::string MObject::getset(const std::string& key, const std::string& value) {
    if (!value.empty()) {
        // If value is provided, set the property and return the previous value
        auto it = propertyMap.find(key);
        std::string previousValue = (it != propertyMap.end()) ? it->second : "";
        propertyMap[key] = value;
        return previousValue;
    } else {
        // If no value is provided, get the current property value
        return get_property(key);
    }
}

void MObject::setget(const std::string& key, const std::string& value) {
    // Set the property value
    propertyMap[key] = value;
}

// Get the class name from the property map
std::string MObject::get_class_name() const {
    return get_property("class_name");
}

// Get a copy of the property map
std::map<std::string, std::string> MObject::get_from_property_map() const {
    return propertyMap;
}

// Insert an object into the object map
void MObject::get_obj_insert(const std::string& objKey, const MObject& objToInsert) {
    objectMap[objKey] = objToInsert;
}

// Get a map of objects associated with a key
std::map<std::string, MObject> MObject::get_obj_map(const std::string& objKey) const {
    auto it = objectMap.find(objKey);
    return (it != objectMap.end()) ? std::map<std::string, MObject>{{objKey, it->second}} : std::map<std::string, MObject>();
}




MObject::allocate_memory(size_t size) {
    dynamicMemory = std::make_unique<char[]>(size);
    return dynamicMemory.get();
}

// Memory-related function: Deallocate dynamic memory
void MObject::deallocate_memory(void* ptr) {
    // Check if the provided pointer matches the dynamic memory pointer
    if (ptr == dynamicMemory.get()) {
        dynamicMemory.reset(); // Deallocate memory by resetting the unique pointer
    }
}

// Memory-related function: Copy data from another MObject
void MObject::copy_data_from(const MObject& other) {
    // Check if both objects have allocated dynamic memory
    if (dynamicMemory && other.dynamicMemory) {
        // Copy data from 'other' to the current object
        std::memcpy(dynamicMemory.get(), other.dynamicMemory.get(), sizeof(char));
    }
}

MObject::get_obj_max_property(const std::string& objKey, const std::string& propertyKey) const {
    auto it = objectMap.find(objKey);
    if (it != objectMap.end()) {
        const MObject& obj = it->second;
        auto objIt = obj.dataMap.find(propertyKey);
        if (objIt != obj.dataMap.end()) {
            return objIt->second;
        }
    }
    return 0; // Default value if the object or property is not found
}

// New function to get the minimum property value in the object map
int MObject::get_obj_min_property(const std::string& objKey, const std::string& propertyKey) const {
    auto it = objectMap.find(objKey);
    if (it != objectMap.end()) {
        const MObject& obj = it->second;
        auto objIt = obj.dataMap.find(propertyKey);
        if (objIt != obj.dataMap.end()) {
            return objIt->second;
        }
    }
    return 0; // Default value if the object or property is not found
}


// String manipulation functions
size_t MObject::find(const std::string& substring) const {
    // Example implementation, you might need to customize based on your requirements
    std::string concatenatedData;
    for (const auto& entry : dataMap) {
        concatenatedData += std::to_string(entry.second);
    }
    return concatenatedData.find(substring);
}

size_t MObject::rfind(const std::string& substring) const {
    // Example implementation, you might need to customize based on your requirements
    std::string concatenatedData;
    for (const auto& entry : dataMap) {
        concatenatedData += std::to_string(entry.second);
    }
    return concatenatedData.rfind(substring);
}

// Null and validity checks
bool MObject::is_null() const {
    return dataMap.empty() && propertyMap.empty() && propertyArrayMap.empty() && objectMap.empty();
}

bool MObject::is_valid() const {
    // Example implementation, you might need to customize based on your requirements
    return !is_null();
