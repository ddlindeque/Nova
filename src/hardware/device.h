#ifndef _DEVICE_H
#define _DEVICE_H

#include <functional>
#include <unordered_map>

namespace Nova {
namespace hardware {

class Device
{
public:
    typedef std::function<void(bool value, bool force)> Listener;
public:
    Device() = default;
    Device(const Device&) = default;
    Device(Device &&) = default;

    virtual ~Device() = default;

    Device& operator=(const Device&) = default;
    Device& operator=(Device&&) = default;

    virtual auto setInput(unsigned char pin, bool value, bool force = false) -> void = 0;
    virtual auto registerListener(unsigned char pin, const Listener &handler) -> void;
protected:
    auto updateOutput(unsigned char pin, bool value, bool force) -> void;
private:
    std::unordered_multimap<unsigned char, Listener> _listerers;
};

}}

#endif // _DEVICE_H