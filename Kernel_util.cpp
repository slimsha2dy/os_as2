#include "Kernel.hpp"

void    Kernel::changeKstate(const string kstate)
{
    this->kstate = kstate;
}

bool	Kernel::getSysflag(void) const
{
	return (this->syscallFlag);
}

bool	Kernel::getallExit(void) const
{
	return (this->allExit);
}

void	Kernel::printState(void) const
{
	cout << "1. mode: " << this->mode << endl;

	cout << "2. command: " ;
	if (this->mode == "kernel")
		cout << this->kstate << endl;
	else
		cout << (this->tmp)->getPstate() << endl;

	cout << "3. running: ";
	if (this->tmp)
		(this->tmp)->printInfo();
	else
		cout << "none" << endl;

	cout << "4. ready: none" << endl;
	cout << "5. wating : none" << endl;
	cout << "6. new: ";
	if (this->newProcess)	// if there is new process
		(this->newProcess)->printInfo();
	else
		cout << "none" << endl;

	cout << "7. terminated: ";
	if (this->terProcess)	// if there is terminated process
		(this->terProcess)->printInfo();
	else
		cout << "none" << endl;
}