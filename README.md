# Quark
Hobby OS, multiboot-compliant

## What is quark?
A quark is an elemental fermion described in the... Oh, the OS?

Quark is a work-in-progress open-source OS designed to be easily scalable. It has been my main project since June 16th.

## But what does it do for now?
As I said, it's a WIP, so it's gonna be growing. But I have some planned milestones. Here they are:

### Milestone 1: Basic kernel
 - [x] x86-specific things
   - [x] Interrupts (IDT, IRQ, ISR, PIC)
   - [x] GDT
   - [x] PIT timer
 - [x] Basic VGA text mode output
 - [x] PS/2 keyboard
 - [x] UART drivers
 - [x] Physical memory manager
 - [x] Virtual memory manager
 - [ ] Virtual file system (mount and unmount capabilities)
 - [ ] QROFS file system

### Milestone 2: Users, welcome
 - [ ] User space
 - [ ] Process management
 - [ ] ELF parser
 - [ ] Shell now is a user space program
 - [ ] Some drivers are now in user space

### Milestone 3: Graphics
 - [ ] Basically everything about GUI and stuff

### Milestone 4: Connections and security
 - [ ] Ethernet driver
 - [ ] IPv4 (or maybe v6?) stack
 - [ ] TCP/IP stack
 - [ ] Network application layer
   - [ ] HTTP
 - [ ] Criptography (with hardware acceleration)

### Milestone 5: There you go! Free way!
 - [ ] Some WiFi drivers
 - [ ] USB drivers
 - [ ] Applications!
   - [ ] File manager
   - [ ] Web browser
   - [ ] Terminal
 - [ ] Package manager
 - [ ] Some outside-of-the-box stuff
   - [ ] A web page
     - [ ] Wiki
     - [ ] Downloads
     - [ ] Forums
   - [ ] Matrix community server

And more! (when we get there)

## Are contributions accepted?
Yes, of course! Feel free to create an issue reporting a bug or requesting some feature. Or even do a pull request!

You can even fork this project, if you want to, and continue by your way (just make sure to keep GPLv3!)
