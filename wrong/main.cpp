#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <iostream>

namespace beast = boost::beast;
namespace net = boost::asio;
using tcp = net::ip::tcp;

const char* host = "127.0.0.1";
const uint16_t port = 8080;

void doRead(tcp::socket socket)
{
    beast::websocket::stream<tcp::socket&> stream(socket);
    boost::system::error_code error;
    beast::flat_buffer buffer;
    stream.read(buffer, error);

    std::cout << "Error: " << error << " Message: " << error.message() << std::endl;
}

void doAccept(net::io_context& context, tcp::endpoint endpoint)
{
    tcp::acceptor acceptor(context, endpoint);
    tcp::socket socket(context);

    std::cout << "Waiting for connection.." << std::endl;
    acceptor.accept(socket);

    beast::websocket::stream<tcp::socket&> stream(socket);
    stream.accept();

    doRead(std::move(socket));
}

int main()
{
    tcp::endpoint endpoint(net::ip::make_address(host), port);
    net::io_context context;
    doAccept(context, endpoint);
}