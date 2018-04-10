#pragma once
#include <iostream>
#include <vector>
#include <cstdint>


// This is the Interface Header file for the SLSV CNC Servcleaer

/*
	This file essentially provides a bunnch of methods to the parent Device and test instance sets 
	the methds being provided as wrappers to the entire library of the access versions for V0 - V5
*/

// This provides the most crude access interface 
// Access policies will have to be defined inside each of the 
// Version files
class Interface{
public:
	// Constructors
	Interface();
	// Destructor
	virtual ~Interface();
	// Initialise 
	virtual bool Initialise() = 0;
	// Syncronise
	// Get it to the defined sync point
	// Different policy for multi core
	virtual bool Synchronise() = 0;
	// Update State
	virtual std::pair<std::vector<std::pair<uint32_t,uint64_t>>,std::vector<std::pair<uint64_t,uint64_t>>> Single_Step() = 0;
	// return a vector of updates pair of Registers and memory
	// Access HART & NHSV
	virtual std::pair<uint64_t,std::vector<uint32_t>> GetVariable() = 0;
	virtual bool SetVariable() = 0;
	// Access Memory
	virtual std::pair<uint64_t,std::vector<uint32_t>> GetMemory() = 0;
	virtual bool SetMemory() = 0;
	// Load Memory w/ Use Fastest method available to load the program memory 
	virtual std::pair<uint64_t,std::vector<uint32_t>> DumpMemory() = 0;
	virtual bool LoadBinary(uint64_t address) = 0;
	// Checkpoint
	// Record the entire accessable state from all reachable DUV`s
	virtual bool Checkpoint(std::string File) = 0;
	virtual bool Checkpoint() = 0; // to the already defined checkpoint file :/
	// Restore
	virtual bool Restore(std::string File) = 0;
	// Restore the checkpoint state to the core and set/reset state variables as defined by user.
	// Utility Methods -- Should be defined in derived interface classes
	// bool set_ocd_port(uint32_t port);
	// bool set_ocd_ip(char* ip);
private:
	//this is the Function Vector;
	std::string CheckpointFile;
	bool initialised = 0;
};

typedef std::pair<uint32_t,uint64_t> p1;
typedef std::pair<uint64_t,uint64_t> p2;
typedef std::vector<p1> RegUpdate;
typedef std::vector<p2> MemUpdate;
typedef std::pair<RegUpdate,MemUpdate> StateContainer;