#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

void print(const boost::system::error_code& /*e*/)
{
  std::cout << "Hello, world!" << std::endl;
}

int main()
{
  io_context io;

  steady_timer t(io, chrono::seconds(5));

  t.async_wait(&print);

  io.run();
  return 0;
}