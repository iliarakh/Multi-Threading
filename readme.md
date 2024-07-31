# Multithreading README

## Threads
Multithreading allows you to use the power of multiple CPU threads. While CPUs typically start from a single thread, you can split tasks effectively by creating additional threads. This approach speeds up programs and allows quicker task switching between threads.

## Mutexes
When threads access a shared variable and make changes to it, that moment is called a critical point. Shared variables are important, but improper use can lead to program crashes. This is where Mutexes (short for “mutual exclusions”) come in. They are hardcoded into the software to ensure atomicity—an action that either happens completely or not at all. In other words, mutexes allow you to modify critical points without interruption from other threads. This is very useful in applications where atomic processes are essential.