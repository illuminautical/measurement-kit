// Part of measurement-kit <https://measurement-kit.github.io/>.
// Measurement-kit is free software. See AUTHORS and LICENSE for more
// information on the copying conditions.
#ifndef SRC_NET_SOCKS5_HPP
#define SRC_NET_SOCKS5_HPP

#include <measurement_kit/common.hpp>
#include <measurement_kit/net.hpp>
#include "src/net/connection.hpp"
#include "src/net/emitter.hpp"

namespace mk {
namespace net {

class Socks5 : public Emitter {
  public:
    Socks5(Settings, Logger * = Logger::global(), Poller * = Poller::global());

    void set_timeout(double timeout) override { conn.set_timeout(timeout); }

    void clear_timeout() override { conn.clear_timeout(); }

    void do_send(Buffer data) override { conn.write(data); }

    void close() override {
        isclosed = true;
        conn.close();
    }

    std::string socks5_address() override { return proxy_address; }

    std::string socks5_port() override { return proxy_port; }

  protected:
    void socks5_connect_();

    Settings settings;
    Connection conn;
    Buffer buffer;
    bool isclosed = false;
    std::string proxy_address;
    std::string proxy_port;
};

namespace socks5 {

Buffer format_auth_request(Logger * = Logger::global());
ErrorOr<bool> parse_auth_response(Buffer &, Logger * = Logger::global());
ErrorOr<Buffer> format_connect_request(Settings, Logger * = Logger::global());
ErrorOr<bool> parse_connect_response(Buffer &, Logger * = Logger::global());

} // namespace socks5
} // namespace net
} // namespace mk
#endif
