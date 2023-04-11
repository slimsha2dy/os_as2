#include "Kernel.hpp"

Kernel::Kernel(string pname)
{
	this->headRq = 0;
	this->tailRq = 0;
	this->headWq = 0;
	this->tailWq = 0;
	this->tmp = 0;
	this->newProcess = new Process(pname);
	this->terProcess = 0;

	this->mode = "kernel";
	this->syscallFlag = 0;
	this->kstate = "boot";
	this->last_pid = 1;
	this->allExit = 0;
} 

Kernel::~Kernel(void)
{
}

void	Kernel::changeKstate(const string kstate)
{
	this->kstate = kstate;
}

void	Kernel::updateState(void)
{
	if (this->newProcess)	// change state of new process
		(this->newProcess)->changeState("ready");

	if (this->terProcess)	// delete terminated process
	{
		delete this->terProcess;	// delete terminated process
		this->terProcess = 0;
	}
}

void	Kernel::updateRq(void)
{
	// new process to readyqueue
	if (this->newProcess)
	{
		if (!this->headRq)
			this->headRq = this->newProcess;
		if (!this->tailRq)
			this->tailRq = this->newProcess;
		else
			(this->tailRq)->addNext(this->newProcess);
		this->newProcess = 0;
	}
}

void	Kernel::excute(void)
{
	if (this->syscallFlag)
	{
		this->mode = "system call";
		syscall();
	}
	if (!this->tmp)
	{
		this->scheduleIdle();
		return ;
	}

	this->mode = "user";
	string command = (this->tmp)->readCommand();
	if (command == "exit")
	{
		this->syscallFlag = 1;
		this->syscallCommand = command;
	}
}

void	Kernel::scheduleIdle(void)
{
	if (!this->headRq)	// empty readyqueue: idle
	{
		this->changeKstate("idle");
		return ;
	}

	// scheduler action
	this->changeKstate("schedule");
	this->tmp = this->headRq;
	this->headRq = (this->headRq)->getNext();
	(this->tmp)->changeState("running");
}

void	Kernel::printState(void) const
{
	cout << "1. mode: " << this->mode << endl;
	cout << "2. command: " << this->kstate << endl;
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

void	Kernel::checkSyscall(void)
{
	this->mode = "kernel";
	this->kstate = "syscall";
}

bool	Kernel::getSysflag(void) const
{
	return (this->syscallFlag);
}

void	Kernel::syscall(void)
{
	if (this->syscallCommand == "exit")
	{
		this->terProcess = this->tmp;
		this->tmp = 0;
		this->allExit = 1;
		delete this->terProcess;
	}

	this->syscallFlag = 0;
}

bool	Kernel::getallExit(void) const
{
	return (this->allExit);
}
