#include "Kernel.hpp"

int	main(int argc, char **argv)
{
	string	str = argv[1];
	Kernel	kernel(str);
	cout << "[cycle #0]" << endl;
	kernel.printState();

	int	cycle = 1;
//	while (!kernel.getallExit())
	while (cycle < 23)
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
