#ifndef SIGNALS_H
#define SIGNALS_H


#include <map>
#include <string>
#include <vector>
#include <functional>

class Object;

// Signal class for communication between objects
template <typename... Args>
class Signal {
public:
    struct CallError {
    int errorCode;
    std::string errorMessage;

    // Constructor
    CallError(int code, const std::string& message) : errorCode(code), errorMessage(message) {}
};
public:
   struct Connection {
    Object* connectedObject;
    Signal<Args...>::Slot connectedSlot;

    // Constructor
    Connection(Object* obj, const Signal<Args...>::Slot& slot)
        : connectedObject(obj), connectedSlot(slot) {}
};

public:
    using Slot = std::function<void(Args...)>;

    void connect(const std::string& key, MObject* obj, const Slot& slot) {
        // Connect the slot to the signal associated with the provided key
        connections[key].emplace_back(obj, slot);
    }

    void disconnect(const std::string& key, MObject* obj) {
        auto it = connections.find(key);
        if (it != connections.end()) {
            auto& slots = it->second;
            slots.erase(std::remove_if(slots.begin(), slots.end(), [obj](const auto& pair) {
                return pair.first == obj;
            }), slots.end());
        }
    }

    void emit(Args... args) {
        for (const auto& connection : connections) {
            for (const auto& pair : connection.second) {
                pair.second(args...);
            }
        }
    }

// New functions to get and set connections
    const std::vector<std::pair<Object*, Slot>>& get(const std::string& key) const {
        auto it = connections.find(key);
        return (it != connections.end()) ? it->second : emptyVector;
    }

    void set(const std::string& key, const std::vector<std::pair<MObject*, Slot>>& newConnections) {
        connections[key] = newConnections;
    }
private:
    // Map to store connections for each key
    std::map<std::string, std::vector<std::pair<Object*, Slot>>> connections;
    const std::vector<Connection> emptyVector;
};



#endif // SIGNALS_H
