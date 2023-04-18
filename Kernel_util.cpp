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
	return (this->exitCount == this->last_pid);
}

void	Kernel::printState(void) const
{
	// 1. mode
	cout << "1. mode: " << this->mode << endl;

	// 2. command
	cout << "2. command: " ;
	if (this->mode == "kernel")
		cout << this->kstate << endl;
	else
	{
		cout << (this->tmp)->getCommand()[0];
		if ((this->tmp)->getCommand()[0] != "exit" && (this->tmp)->getCommand()[0] != "wait")
			cout << " " << (this->tmp)->getCommand()[1];
		cout << endl;
	}

	// 3. running
	cout << "3. running: ";
	if (this->tmp)
		(this->tmp)->printInfo();
	else
		cout << "none" << endl;

	// 4. ready
	cout << "4. ready:";
	if (this->headRq)
	{
		Process *tmp = this->headRq;
		while (tmp)
		{
			cout << " " << tmp->getPid();
			tmp = tmp->getNext();
		}
		cout << endl;
	}
	else
		cout << " none" << endl;

	// 5. waiting
	cout << "5. waiting:";
	if (this->headWq)		// if there is wating process
	{
		Process	*tmp = this->headWq;
		while (tmp)
		{
			tmp->printWait();
			tmp = tmp->getNext();
		}
		cout << endl;
	}
	else
		cout << " none" << endl;

	// 6. new
	cout << "6. new: ";
	if (this->newProcess)	// if there is new process
		(this->newProcess)->printInfo();
	else
		cout << "none" << endl;

	// 7. terminated
	cout << "7. terminated: ";
	if (this->terProcess)	// if there is terminated process
		(this->terProcess)->printInfo();
	else
		cout << "none" << endl;
	cout << endl;
}

void	Kernel::pushRq(Process *p)
{
	if (!this->headRq)
		this->headRq = p;
	if (!this->tailRq)
		this->tailRq = p;
	else
		(this->tailRq)->addNext(p);
}

Process	*Kernel::popRq(void)
{
	Process	*tmp = this->headRq;
	if (this->headRq == this->tailRq)
		this->tailRq = 0;
	this->headRq = (this->headRq)->getNext();
	tmp->addNext(0);
	return (tmp);
}

void	Kernel::pushWq(Process *p)
{
	if (!this->headWq)
		this->headWq = p;
	if (!this->tailWq)
		this->tailWq = p;
	else
		(this->tailWq)->addNext(p);
}

Process	*Kernel::popWq(void)
{
	Process	*tmp = this->headWq;
	if (this->headWq == this->tailWq)
		this->tailWq = 0;
	this->headWq = (this->headWq)->getNext();
	tmp->addNext(0);
	return (tmp);
}

Process	*Kernel::popWq(Process *p)
{
	Process	*tmp = this->headWq;
	Process	*ret;
	if (tmp == p)
		return (this->popWq());
	while (tmp->getNext() == p)		// tmp is before p
		tmp = tmp->getNext();
	ret = tmp->getNext();			// ret = p
	tmp->addNext(ret->getNext());	// a-(p)-b -> a-b
	ret->addNext(0);
	return (ret);
}
