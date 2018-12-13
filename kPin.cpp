
/*************************************************************
  All the pins.
*************************************************************/
#include "Arduino.h"
#include "kPin.h"

using namespace kPin;
	/*
	*	PortID
	*/

	uint8_t PortID::port() const {
		return mPortNumber;
	}

	int PortID::digitalRead() const {
		reg_pin_t *blah = PIN();
		return (*blah);
	}
	int PortID::digitalRead(uint8_t mask, uint8_t shift/*=0*/) {
		// Read the masked bits. Use shift value to align the results to LSB end.
		return (*(PIN()) & mask) >> shift;
	}
	void PortID::digitalWrite(uint8_t value) const {
		*(PORT()) = value;
	}
	void PortID::digitalWrite(uint8_t value, uint8_t mask, uint8_t shift/*=0*/) {
		// Write the value into the masked bits.
		// Use shift to align value LSB with the start of the mask area.
		*(PORT()) = (*(PORT()) & ~mask) | ((value << shift) & mask);
	}

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

	reg_ddr_t *PortID::DDR() const {
			switch (mPortNumber){
				case 1:
					return &DDRA;
				case 2:
					return &DDRB;
				case 3:
					return &DDRC;
				case 4:
					return &DDRD;
				case 5:
					return &DDRE;
				case 6:
					return &DDRF;
				case 7:
					return &DDRG;
				case 8:
					return &DDRH;
				case 10:
					return &DDRJ;
				case 11:
					return &DDRK;
				case 12:
					return &DDRL;
				default:
					return nullptr;
			}
		}

	reg_port_t *PortID::PORT() const {
			switch (mPortNumber){
				case 1:
					return &PORTA;
				case 2:
					return &PORTB;
				case 3:
					return &PORTC;
				case 4:
					return &PORTD;
				case 5:
					return &PORTE;
				case 6:
					return &PORTF;
				case 7:
					return &PORTG;
				case 8:
					return &PORTH;
				case 10:
					return &PORTJ;
				case 11:
					return &PORTK;
				case 12:
					return &PORTL;
				default:
					return nullptr;
			}
		}

	reg_pin_t *PortID::PIN() const {
			switch (mPortNumber){
				case 1:
					return &PINA;
				case 2:
					return &PINB;
				case 3:
					return &PINC;
				case 4:
					return &PIND;
				case 5:
					return &PINE;
				case 6:
					return &PINF;
				case 7:
					return &PING;
				case 8:
					return &PINH;
				case 10:
					return &PINJ;
				case 11:
					return &PINK;
				case 12:
					return &PINL;
				default:
					return nullptr;
			}
		}

	const PortID PinID::Port() const {
		switch (digital_pin_to_port_PGM[mPin]){
			case 1:
				return PORT_A;
			case 2:
				return PORT_B;
			case 3:
				return PORT_C;
			case 4:
				return PORT_D;
			case 5:
				return PORT_E;
			case 6:
				return PORT_F;
			case 7:
				return PORT_G;
			case 8:
				return PORT_H;
			case 10:
				return PORT_J;
			case 11:
				return PORT_K;
			case 12:
				return PORT_L;
			default:
				break;
		}
		// DEBUG_PRINTLN("No port registered to this pin.");
		exit(1);
	}



	/*
	*	PinID
	*/

	constexpr uint8_t PinID::pin() const {
		return mPin;
	}

	void PinID::pinMode(int mode) const{
		return ::pinMode(mPin, mode);
	}

	int PinID::digitalRead() const {
		return ::digitalRead(mPin);
	}

	void PinID::digitalWrite(const int value) const{
		return ::digitalWrite(mPin, value);
	}

	uint8_t PinID::PortMask() const {
		return digitalPinToBitMask(mPin);
	}



	/*
	*	PinInt
	*/

	void PinInt::EnablePCInterupt() const {
		uint8_t portMask = PortMask();
		Port().EnablePCInterupt(portMask);
	}

	void PinInt::DisablePCInterupt() const {
		uint8_t portMask = PortMask();
		Port().DisablePCInterupt(portMask);
	}