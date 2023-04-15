#include "Process.hpp"

int	Process::getPid(void) const
{
	return (this->pid);
}

void	Process::changeState(const string state)
{
	this->pstate = state;
}

void	Process::addNext(Process *next)
{
	this->next = next;
}

Process	*Process::getNext(void) const
{
	return (this->next);
}

void	Process::printInfo(void) const
{
	cout << this->pid << "(" << this->pname << ", " << this->ppid \
		<< ")" << endl;
}

string	Process::getPstate(void) const
{
	return (this->pstate);
}

string	Process::getCommand(void) const
{
	return (this->tmpCode);
}
