#pragma once

#include <string>
#include <system_error>
#include <type_traits>
#include <boost/asio/error.hpp>
#include <boost/system/error_code.hpp>
#include <zmq.h>

namespace boost {
namespace asio {
namespace error {

enum class zmq_error {};

struct zmq_error_category_impl : public system::error_category {
    virtual const char* name() const noexcept { return "zeromq"; }

    virtual std::string message(int ev) const noexcept { return ::zmq_strerror(ev); }
};

#if 1
extern const system::error_category& zmq_category();
#else
const system::error_category& zmq_category()
{
    static zmq_error_category_impl instance;
    return instance;
}
#endif

#if 1
extern system::error_code make_error_code(zmq_error e);
#else
system::error_code make_error_code(zmq_error e)
{
    return system::error_code(static_cast<int>(e), zmq_category());
}
#endif

}  // namespace error
}  // namespace asio
}  // namespace boost

namespace std {

template <> struct is_error_code_enum<boost::asio::error::zmq_error> : std::true_type {
};

}  // namespace std
