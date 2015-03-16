#include "asio-zmq/error.hpp"
#include "asio-zmq/frame.hpp"

namespace boost {
namespace asio {
namespace error {

const system::error_category& zmq_category()
{
    static zmq_error_category_impl instance;
    return instance;
}

system::error_code make_error_code(zmq_error e)
{
    return system::error_code(static_cast<int>(e), zmq_category());
}

}
}
}

namespace std {

std::string to_string(boost::asio::zmq::frame const& frame)
{
    return std::string(static_cast<char const*>(frame.data()), frame.size());
}

}
