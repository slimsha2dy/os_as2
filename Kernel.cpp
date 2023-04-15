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
	if (this->terProcess)
		delete this->terProcess;
}

void	Kernel::checkSyscall(void)
{
	this->mode = "kernel";
	this->kstate = "syscall";
}

void	Kernel::updateState(void)
{
	// change state of new process
	if (this->newProcess)
		(this->newProcess)->changeState("ready");

	// delete terminated process
	if (this->terProcess)
	{
		delete this->terProcess;
		this->terProcess = 0;
	}
}

void	Kernel::updateRq(void)
{
	// new process to readyqueue
	if (this->newProcess)
	{
		this->pushRq(this->newProcess);
		this->newProcess = 0;
	}
}

void	Kernel::excute(void)
{
	if (this->syscallFlag)	// system call command
	{
		this->mode = "kernel";
		syscall();
		return ;
	}

	else if (!this->tmp)	// schedule or idle
	{
		this->mode = "kernel";
		this->scheduleIdle();
		return ;
	}

	// running process command
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
	this->tmp = this->popRq();
	(this->tmp)->changeState("running");
}

void	Kernel::syscall(void)
{
	if (this->syscallCommand == "exit")
	{
		this->terProcess = this->tmp;
		this->tmp = 0;
		this->allExit = 1;
	}

	this->syscallFlag = 0;
}
