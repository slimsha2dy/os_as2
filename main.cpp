#include "Kernel.hpp"

int	main(int argc, char **argv)
{
	Kernel	kernel(argv[1]);
	cout << "[cycle #0]" << endl;
	kernel.printState();

	int	cycle = 1;
	while (!kernel.getallExit())
	{		
		if (kernel.getSysflag())
			kernel.checkSyscall();
		kernel.updateSleep();
		kernel.updateState();
		kernel.updateRq();
		kernel.excute();
		cout << "[cycle #" << cycle << "]" << endl;
		kernel.printState();
		++cycle;
	}
	return (0);
}
