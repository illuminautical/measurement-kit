// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software under the BSD license. See AUTHORS
// and LICENSE for more information on the copying conditions.
#ifndef MEASUREMENT_KIT_COMMON_DETAIL_EVERY_HPP
#define MEASUREMENT_KIT_COMMON_DETAIL_EVERY_HPP

#include <measurement_kit/common/detail/maybe.hpp>
#include <measurement_kit/common/reactor.hpp>

namespace mk {

template <typename Callable, typename StopPredicate, typename Callback>
void every(double delay, SharedPtr<Reactor> reactor, Callback callback,
           StopPredicate stop_predicate, Callable callable) {
    reactor->call_soon([=]() {
        if (delay <= 0.0) {
            callback(ValueError());
            return;
        }
        if (stop_predicate()) {
            callback(NoError());
            return;
        }
        callable();
        reactor->call_later(delay, [=]() {
            every(delay, reactor, callback, stop_predicate, callable);
        });
    });
}

} // namespace mk
#endif
