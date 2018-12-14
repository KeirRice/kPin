
/*************************************************************
  All the pins.
*************************************************************/
#pragma once

namespace kPin{

	namespace utils{
		uint8_t maskToShifter(uint8_t mask);
	}

	/*
	*	Types
	*/
	typedef volatile const uint8_t reg_r_t; /**< Read only 8-bit register (volatile const unsigned int) */
	typedef volatile uint8_t reg_rw_t; 		/**< Read-Write 8-bit register (volatile unsigned int) */
		
	typedef reg_rw_t reg_ddr_t;  // Data Direction Register
	typedef reg_rw_t reg_port_t;  // Data Register
	typedef reg_r_t reg_pin_t;  // Input Pins Register

	/*
	*	PortID is for working with an entire port at once.
	*/
	class PortID {
		public:

			constexpr PortID(const uint8_t port_number) : mPortNumber(port_number) {}
			constexpr PortID(const PortID &obj) :	mPortNumber(obj.mPortNumber) {}

			// The port number of this class
			uint8_t port() const;
			constexpr operator uint8_t() const {return mPortNumber;}

			// Read values of the port
			int digitalRead() const;
			int digitalRead(uint8_t mask, uint8_t shift=0);

			// Write values to the port
			void digitalWrite(uint8_t value) const;
			void digitalWrite(uint8_t value, uint8_t mask, uint8_t shift=0);

			// Set the mode of the port
			void pinMode(uint8_t /*mode*/, uint8_t /*mask*/){};  // TODO

			// Set pin change interupt flags
			void EnablePCInterupt(uint8_t portMask) const;
			void DisablePCInterupt(uint8_t portMask) const;

		private:
			const uint8_t mPortNumber;

			reg_ddr_t *DDR() const;
			reg_port_t *PORT() const;
			reg_pin_t *PIN() const;
	};
	typedef PortID PortID;

	constexpr static const PortID PORT_A(1);
	constexpr static const PortID PORT_B(2);
	constexpr static const PortID PORT_C(3);
	constexpr static const PortID PORT_D(4);
	constexpr static const PortID PORT_E(5);
	constexpr static const PortID PORT_F(6);
	constexpr static const PortID PORT_G(7);
	constexpr static const PortID PORT_H(8);
	// TODO: Check what's up with I?
	constexpr static const PortID PORT_J(10);
	constexpr static const PortID PORT_K(11);
	constexpr static const PortID PORT_L(12);


	/*
	*	PinID is for working with indervidual pins.
	*/
	class PinID {
		public:
			constexpr PinID(const uint8_t pin) : mPin(pin) {}
			constexpr PinID(const PinID &obj) : mPin(obj.mPin) {}

			// The pin number of this class
			constexpr uint8_t pin() const;
			constexpr operator uint8_t() const {	return mPin; }

			// Convenience function for digitalRead
			int digitalRead() const;

			// Convenience function for digitalWrite
			void digitalWrite(const int value) const;

			// Convenience function for pinMode
		    void pinMode(int mode) const;

			// The bit mask of this pin relative to it's unlaying port.
			uint8_t PortMask() const;

			// The PortID object for the unlaying port.
			const PortID Port() const;

		private:
			const uint8_t mPin;
	};
	typedef PinID PinIDT;
	typedef PinID PinID;


	/*
	*	PinInt is for pins that support Pin Change interupts.
	*/
	class PinInt : public PinID {
		public: 
			constexpr PinInt(const uint8_t pin) : PinID(pin) {}
			constexpr PinInt(const PinID &obj) : PinID(obj) {}

			// Enable pin change interupts.
			void EnablePCInterupt() const;
			void DisablePCInterupt() const;
	};
	typedef PinInt PinInt;

	/*
	*	Labels for all the pins on the Mega
	*/
	constexpr static const PinID ARDUINO_D0(0),   ARDUINO_PE0(ARDUINO_D0);
	constexpr static const PinID ARDUINO_D1(1),   ARDUINO_PE1(ARDUINO_D1);
	constexpr static const PinID ARDUINO_D2(2),   ARDUINO_PE4(ARDUINO_D2);
	constexpr static const PinID ARDUINO_D3(3),   ARDUINO_PE5(ARDUINO_D3);
	constexpr static const PinID ARDUINO_D4(4),   ARDUINO_PG5(ARDUINO_D4);
	constexpr static const PinID ARDUINO_D5(5),   ARDUINO_PE3(ARDUINO_D5);
	constexpr static const PinID ARDUINO_D6(6),   ARDUINO_PH3(ARDUINO_D6);
	constexpr static const PinID ARDUINO_D7(7),   ARDUINO_PH4(ARDUINO_D7);
	constexpr static const PinID ARDUINO_D8(8),   ARDUINO_PH5(ARDUINO_D8);
	constexpr static const PinID ARDUINO_D9(9),   ARDUINO_PH6(ARDUINO_D9);
	constexpr static const PinID ARDUINO_D10(10), ARDUINO_PB4(ARDUINO_D10);
	constexpr static const PinID ARDUINO_D11(11), ARDUINO_PB5(ARDUINO_D11);
	constexpr static const PinID ARDUINO_D12(12), ARDUINO_PB6(ARDUINO_D12);
	constexpr static const PinID ARDUINO_D13(13), ARDUINO_PB7(ARDUINO_D13);
	constexpr static const PinID ARDUINO_D14(14), ARDUINO_PJ1(ARDUINO_D14);
	constexpr static const PinID ARDUINO_D15(15), ARDUINO_PJ0(ARDUINO_D15);
	constexpr static const PinID ARDUINO_D16(16), ARDUINO_PH1(ARDUINO_D16);
	constexpr static const PinID ARDUINO_D17(17), ARDUINO_PH0(ARDUINO_D17);
	constexpr static const PinID ARDUINO_D18(18), ARDUINO_PD3(ARDUINO_D18);
	constexpr static const PinID ARDUINO_D19(19), ARDUINO_PD2(ARDUINO_D19);
	constexpr static const PinID ARDUINO_D20(20), ARDUINO_PD1(ARDUINO_D20);
	constexpr static const PinID ARDUINO_D21(21), ARDUINO_PD0(ARDUINO_D21);
	constexpr static const PinID ARDUINO_D22(22), ARDUINO_PA0(ARDUINO_D22);
	constexpr static const PinID ARDUINO_D23(23), ARDUINO_PA1(ARDUINO_D23);
	constexpr static const PinID ARDUINO_D24(24), ARDUINO_PA2(ARDUINO_D24);
	constexpr static const PinID ARDUINO_D25(25), ARDUINO_PA3(ARDUINO_D25);
	constexpr static const PinID ARDUINO_D26(26), ARDUINO_PA4(ARDUINO_D26);
	constexpr static const PinID ARDUINO_D27(27), ARDUINO_PA5(ARDUINO_D27);
	constexpr static const PinID ARDUINO_D28(28), ARDUINO_PA6(ARDUINO_D28);
	constexpr static const PinID ARDUINO_D29(29), ARDUINO_PA7(ARDUINO_D29);
	constexpr static const PinID ARDUINO_D30(30), ARDUINO_PC7(ARDUINO_D30);
	constexpr static const PinID ARDUINO_D31(31), ARDUINO_PC6(ARDUINO_D31);
	constexpr static const PinID ARDUINO_D32(32), ARDUINO_PC5(ARDUINO_D32);
	constexpr static const PinID ARDUINO_D33(33), ARDUINO_PC4(ARDUINO_D33);
	constexpr static const PinID ARDUINO_D34(34), ARDUINO_PC3(ARDUINO_D34);
	constexpr static const PinID ARDUINO_D35(35), ARDUINO_PC2(ARDUINO_D35);
	constexpr static const PinID ARDUINO_D36(36), ARDUINO_PC1(ARDUINO_D36);
	constexpr static const PinID ARDUINO_D37(37), ARDUINO_PC0(ARDUINO_D37);
	constexpr static const PinID ARDUINO_D38(38), ARDUINO_PD7(ARDUINO_D38);
	constexpr static const PinID ARDUINO_D39(39), ARDUINO_PG2(ARDUINO_D39);
	constexpr static const PinID ARDUINO_D40(40), ARDUINO_PG1(ARDUINO_D40);
	constexpr static const PinID ARDUINO_D41(41), ARDUINO_PG0(ARDUINO_D41);
	constexpr static const PinID ARDUINO_D42(42), ARDUINO_PL7(ARDUINO_D42);
	constexpr static const PinID ARDUINO_D43(43), ARDUINO_PL6(ARDUINO_D43);
	constexpr static const PinID ARDUINO_D44(44), ARDUINO_PL5(ARDUINO_D44);
	constexpr static const PinID ARDUINO_D45(45), ARDUINO_PL4(ARDUINO_D45);
	constexpr static const PinID ARDUINO_D46(46), ARDUINO_PL3(ARDUINO_D46);
	constexpr static const PinID ARDUINO_D47(47), ARDUINO_PL2(ARDUINO_D47);
	constexpr static const PinID ARDUINO_D48(48), ARDUINO_PL1(ARDUINO_D48);
	constexpr static const PinID ARDUINO_D49(49), ARDUINO_PL0(ARDUINO_D49);
	constexpr static const PinID ARDUINO_D50(50), ARDUINO_PB3(ARDUINO_D50);
	constexpr static const PinID ARDUINO_D51(51), ARDUINO_PB2(ARDUINO_D51);
	constexpr static const PinID ARDUINO_D52(52), ARDUINO_PB1(ARDUINO_D52);
	constexpr static const PinID ARDUINO_D53(53), ARDUINO_PB0(ARDUINO_D53);
	constexpr static const PinID ARDUINO_D54(54), ARDUINO_PF0(ARDUINO_D54), ARDUINO_A0(ARDUINO_D54);
	constexpr static const PinID ARDUINO_D55(55), ARDUINO_PF1(ARDUINO_D55), ARDUINO_A1(ARDUINO_D55);
	constexpr static const PinID ARDUINO_D56(56), ARDUINO_PF2(ARDUINO_D56), ARDUINO_A2(ARDUINO_D56);
	constexpr static const PinID ARDUINO_D57(57), ARDUINO_PF3(ARDUINO_D57), ARDUINO_A3(ARDUINO_D57);
	constexpr static const PinID ARDUINO_D58(58), ARDUINO_PF4(ARDUINO_D58), ARDUINO_A4(ARDUINO_D58);
	constexpr static const PinID ARDUINO_D59(59), ARDUINO_PF5(ARDUINO_D59), ARDUINO_A5(ARDUINO_D59);
	constexpr static const PinID ARDUINO_D60(60), ARDUINO_PF6(ARDUINO_D60), ARDUINO_A6(ARDUINO_D60);
	constexpr static const PinID ARDUINO_D61(61), ARDUINO_PF7(ARDUINO_D61), ARDUINO_A7(ARDUINO_D61);
	constexpr static const PinID ARDUINO_D62(62), ARDUINO_PK0(ARDUINO_D62), ARDUINO_A8(ARDUINO_D62);
	constexpr static const PinID ARDUINO_D63(63), ARDUINO_PK1(ARDUINO_D63), ARDUINO_A9(ARDUINO_D63);
	constexpr static const PinID ARDUINO_D64(64), ARDUINO_PK2(ARDUINO_D64), ARDUINO_A10(ARDUINO_D64);
	constexpr static const PinID ARDUINO_D65(65), ARDUINO_PK3(ARDUINO_D65), ARDUINO_A11(ARDUINO_D65);
	constexpr static const PinID ARDUINO_D66(66), ARDUINO_PK4(ARDUINO_D66), ARDUINO_A12(ARDUINO_D66);
	constexpr static const PinID ARDUINO_D67(67), ARDUINO_PK5(ARDUINO_D67), ARDUINO_A13(ARDUINO_D67);
	constexpr static const PinID ARDUINO_D68(68), ARDUINO_PK6(ARDUINO_D68), ARDUINO_A14(ARDUINO_D68);
	constexpr static const PinID ARDUINO_D69(69), ARDUINO_PK7(ARDUINO_D69), ARDUINO_A15(ARDUINO_D69);

	constexpr static const PinID ARDUINO_INT0(ARDUINO_D21);
	constexpr static const PinID ARDUINO_INT1(ARDUINO_D20);
	constexpr static const PinID ARDUINO_INT2(ARDUINO_D19);
	constexpr static const PinID ARDUINO_INT3(ARDUINO_D18);
	constexpr static const PinID ARDUINO_INT4(ARDUINO_D2);
	constexpr static const PinID ARDUINO_INT5(ARDUINO_D3);

	// PCI0 // PORTB
	constexpr static const PinInt ARDUINO_PCINT0(ARDUINO_D53);
	constexpr static const PinInt ARDUINO_PCINT1(ARDUINO_D52);
	constexpr static const PinInt ARDUINO_PCINT2(ARDUINO_D51);
	constexpr static const PinInt ARDUINO_PCINT3(ARDUINO_D50);
	constexpr static const PinInt ARDUINO_PCINT4(ARDUINO_D10);
	constexpr static const PinInt ARDUINO_PCINT5(ARDUINO_D11);
	constexpr static const PinInt ARDUINO_PCINT6(ARDUINO_D12);
	constexpr static const PinInt ARDUINO_PCINT7(ARDUINO_D13);

	// PCI1
	constexpr static const PinInt ARDUINO_PCINT8(ARDUINO_D0); // PORTE

	constexpr static const PinInt ARDUINO_PCINT9(ARDUINO_D15); // PORTJ
	constexpr static const PinInt ARDUINO_PCINT10(ARDUINO_D14); // PORTJ
	/* PCINT11 to PCINT15 on PORTJ not exposed on Arduino */

	// PCI2 // PORTK
	constexpr static const PinInt ARDUINO_PCINT16(ARDUINO_D62);
	constexpr static const PinInt ARDUINO_PCINT17(ARDUINO_D63);
	constexpr static const PinInt ARDUINO_PCINT18(ARDUINO_D64);
	constexpr static const PinInt ARDUINO_PCINT19(ARDUINO_D65);
	constexpr static const PinInt ARDUINO_PCINT20(ARDUINO_D66);
	constexpr static const PinInt ARDUINO_PCINT21(ARDUINO_D67);
	constexpr static const PinInt ARDUINO_PCINT22(ARDUINO_D68);
	constexpr static const PinInt ARDUINO_PCINT23(ARDUINO_D69);


	constexpr static const PinID ARDUINO_ICSP_MISO(ARDUINO_D50);
	constexpr static const PinID ARDUINO_ICSP_MOSI(ARDUINO_D51);
	constexpr static const PinID ARDUINO_ICSP_SCK(ARDUINO_D52);
	constexpr static const PinID ARDUINO_ICSP_NOT_SS(ARDUINO_D53);
	constexpr static const PinID ARDUINO_TX3(ARDUINO_D14);
	constexpr static const PinID ARDUINO_RX3(ARDUINO_D15);
	constexpr static const PinID ARDUINO_TX2(ARDUINO_D16);
	constexpr static const PinID ARDUINO_RX2(ARDUINO_D17);
	constexpr static const PinID ARDUINO_TX1(ARDUINO_D18);
	constexpr static const PinID ARDUINO_RX1(ARDUINO_D19);
	constexpr static const PinID ARDUINO_I2C_SDA(ARDUINO_D20);
	constexpr static const PinID ARDUINO_I2C_SCL(ARDUINO_D21);


	namespace Group{
		class PinsInterface {
			public:
				uint8_t mPinCount;
				uint8_t pins[];

				virtual int digitalRead();
				virtual void digitalWrite(int /*value*/);
				virtual void pinMode(int /*mode*/);
		};

		/*
		*	Manage reading and writing blocks of bits to a single port.
		*/
		class Port : public PinsInterface {
			PortID &mPort;

			uint8_t mMask;
			uint8_t mShift;
			
			public:
				Port(PortID port, uint8_t mask, uint8_t shift=0) : mPort(port), mMask(mask), mShift(shift) {};

				int digitalRead() override{
					return mPort.digitalRead(mMask, mShift);
				};
				void digitalWrite(int value) override{
					return mPort.digitalWrite(value, mMask, mShift);
				};

				void pinMode(int mode) override{
					mPort.pinMode(mode, mMask);
				};
		};
		
		/*
		*	Manage reading and writing blocks of bits spread across many pins.
		*/

		// First pin is the MSB, last pin is LSB
		template<PinID*... Args>
		class Pins : public PinsInterface {
			uint8_t mPinCount = sizeof...(Args);
			uint8_t pins[sizeof...(Args)] = {(Args)...};  

			public:

				Pins(){};

				/* Digital write bits from the LSB end of value */
				int digitalRead() override {
					int value = 0;
					for(uint8_t i=0; i < this->mPinCount; ++i){
						value |= this->pins[i].digitalRead() << i;
					}
					return value;
				};

				/* Digital write bits from the LSB end of value */
				void digitalWrite(int value) override {
					// TODO: Check we are not off by one here...
					for(uint8_t i=this->mPinCount; i > 0; --i){
						this->pins[i].digitalWrite(value & (1 << i));
					}
					return value;
				};

				void pinMode(int mode) override {
					for(uint8_t i=0; i < this->mPinCount; ++i){
						::pinMode(this->pins[i], mode);
					}
				};
		};

	} // namespace kPin.Group

} // namespace kPin