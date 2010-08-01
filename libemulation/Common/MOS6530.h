
/**
 * libemulation
 * MOS6530
 * (C) 2009-2010 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Implements a MOS 6530 (ROM, RAM, I/O, Timer)
 */

#include "OEComponent.h"

class MOS6530 : public OEComponent
{
public:
	MOS6530();
	
	bool setProperty(const string &name, const string &value);
	bool getProperty(const string &name, string &value);
	bool connect(const string &name, OEComponent *component);

	OEUInt8 read(int address);
	void write(int address, OEUInt8 value);
	
private:
	OEComponent *reset;
	int resetNotification;
	
	OEComponent *irq;
	int irqEvent;
	
	string mmuMap;
	
	OEComponent *portA;
	int ddrA;
	int dataA;
	
	OEComponent *portB;
	int ddrB;
	int dataB;
};
