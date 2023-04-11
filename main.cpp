#include "Kernel.hpp"

int	main(int argc, char **argv)
{
	Kernel	kernel(static_cast<string>(argv[1]));
	cout << "[cycle #0]" << endl;
	kernel.printState();
	cout << endl;

	int	cycle = 1;
	//while (!kernel.getallExit())
	while (cycle < 15)
	{
		kernel.updateState();
		kernel.updateRq();
		kernel.excute();
		cout << "[cycle #" << cycle << "]" << endl;
		kernel.printState();
		cout << endl;
		if (kernel.getSysflag())
			kernel.syscall();
		++cycle;
	}
	return (0);
}
