
/*************************************************************
  All the pins.
*************************************************************/
#include "Arduino.h"
#include "kPin.h"

namespace kPin{

	void PortID::EnablePCInterupt(uint8_t portMask) const {
		switch (mPortNumber){
			case PORT_B:
			PCICR |= 0b00000001;
			PCMSK0 |= portMask;
			break;

			case PORT_E:
			case PORT_J:
			PCICR |= 0b00000010;
			PCMSK1 |= portMask;
			break;

			case PORT_K:
			PCICR |= 0b00000100;
			PCMSK2 |= portMask;
			break;

			default :
			break;
		};
	}
	void PortID::DisablePCInterupt(uint8_t portMask) const {
		switch (mPortNumber){
			case PORT_B:
			PCMSK0 &= ~portMask;
			if (PCMSK0 == 0) { PCICR &= ~0b00000001; };
			break;

			case PORT_E:
			case PORT_J:
			PCMSK1 &= ~portMask;
			if (PCMSK1 == 0) { PCICR &= ~0b00000010; };
			break;

			case PORT_K:
			PCMSK2 &= ~portMask;
			if (PCMSK2 == 0) { PCICR &= ~0b00000100; };
			break;

			default :
			break;
		};
	}

	void PinInt::EnablePCInterupt() const {
		uint8_t portMask = PortMask();
		mPort.EnablePCInterupt(portMask);
	}

	void PinInt::DisablePCInterupt() const {
		uint8_t portMask = PortMask();
		mPort.DisablePCInterupt(portMask);
	}
}