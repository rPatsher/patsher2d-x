/**
 * MIT License

Copyright (c) 2024/2025 rPatsher

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef SIGNALS_H
#define SIGNALS_H


#include <functional>

#include "core/templates/list.h"
#include "core/templates/map.h"  
#include "core/templates/vector.h" 
#include "core/object/m_object.h"


/**
	*@class Signal 
	*@brief Signal class for communication between objects
*/
template <typename... Args>
class Signal {
public:
    struct CallError {
    int errorCode;
    String errorMessage;

    // Constructor
    CallError(int code, const String& message) : errorCode(code), errorMessage(message) {}
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

    void connect(const String& key, Object* obj, const Slot& slot) {
        // Connect the slot to the signal associated with the provided key
        connections[key].emplace_back(obj, slot);
    }

    void disconnect(const String& key, Object* obj) {
        auto it = connections.find(key);
        if (it != connections.end()) {
            auto& slots = it->second;
            slots.erase(std::remove_if(slots.begin(), slots.end(), [obj](const auto& pair) {
                return pair.first == obj;
            }), slots.end());
        }
    }

    void emit_signal(Args... args) {
        for (const auto& connection : connections) {
            for (const auto& pair : connection.second) {
                pair.second(args...);
            }
        }
    }

// New functions to get and set connections
    const Vector<std::pair<Object*, Slot>>& get(const String& key) const {
        auto it = connections.find(key);
        return (it != connections.end()) ? it->second : emptyVector;
    }

    void set(const String& key, const Vector<std::pair<Object*, Slot>>& newConnections) {
        connections[key] = newConnections;
    }
private:
    // Map to store connections for each key
    Map<String, Vector<std::pair<Object*, Slot>>> connections;
    const Vector<Connection> emptyVector;
};



#endif // SIGNALS_H
