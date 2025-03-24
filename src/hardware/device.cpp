
#include "device.h"

namespace Nova {
namespace hardware {

auto Device::registerListener(unsigned char pin, const Listener &handler) -> void
{
    _listerers.emplace(pin, handler);
}

auto Device::updateOutput(unsigned char pin, bool value, bool force) -> void
{
    auto range = _listerers.equal_range(pin);
    for (auto it = range.first; it != range.second; ++it) {
        it->second(value, force);
    }
}

}}