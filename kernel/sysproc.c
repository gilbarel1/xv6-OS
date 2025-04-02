#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  char msg[32];
  argint(0, &n);
  argstr(1, msg, sizeof(msg));
  exit(n, msg);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  uint64 msg;
  argaddr(0, &p);
  argaddr(1, &msg);
  return wait(p, (char*)msg);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// Return the size of the running process' memory in bytes.
uint64
sys_memsize(void)
{
  return myproc()->sz;
}

uint64
sys_forkn(void)
{
  int n;
  uint64 pids_addr;
  // Get the first argument (number of processes)
  argint(0, &n);
  // Get the second argument (pointer to pids array)
  argaddr(1, &pids_addr); 
  return forkn(n, pids_addr);
}

uint64
sys_waitall(void)
{
  int n;
  uint64 statuses_addr;
  // Get the first argument (number of processes)
  argint(0, &n);
  // Get the second argument (pointer to statuses array)
  argaddr(1, &statuses_addr); 
  return waitall(n, statuses_addr);
}
