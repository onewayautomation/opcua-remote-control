#include <boost/process.hpp> 
#include <functional>
#include <atomic>
#include <iostream> 

namespace bp = ::boost::process;

int main(int argc, char *argv[])
{
	bp::pipe inputPipe;
	bp::pstream outputStream;
	std::atomic<bool> exitFlag = false;

	bp::child childProcess(bp::search_path("cmd"), "echo Enter exit to finish\n", bp::std_out > outputStream, bp::std_err > stderr, bp::std_in < inputPipe);

	std::thread writeThread([&]()
	{
		std::cout << "Enter exit to finish ...\n";

		std::string commandString;
		do {

			// Read string from console:
			commandString = "";
			std::getline(std::cin, commandString);

			commandString += "\r\n";

			inputPipe.write(commandString.c_str(), commandString.length());

		} while (!exitFlag);
	});
	
	std::thread readThread([&]()
	{
		do {
			std::string outputString;
			std::getline(outputStream, outputString);
			std::cout << outputString << std::endl;
		} while (!exitFlag);
	});

	childProcess.wait();
	int result = childProcess.exit_code();
	exitFlag = true;

	writeThread.join();
	readThread.join();

	return childProcess;
}