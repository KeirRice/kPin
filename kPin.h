
/*************************************************************
  All the pins.
*************************************************************/
#pragma once

namespace kPin{

	typedef volatile const uint8_t reg_r_t; /**< Read only 8-bit register (volatile const unsigned int) */
	typedef volatile uint8_t reg_rw_t; 		/**< Read-Write 8-bit register (volatile unsigned int) */
	
	typedef volatile reg_rw_t *port_ptr_t;
	
	typedef reg_rw_t port_t;
	typedef reg_rw_t reg_ddr_t;  // Data Direction Register
	typedef reg_rw_t reg_port_t;  // Data Register
	typedef reg_r_t reg_pin_t;  // Input Pins Register


	constexpr const uint8_t PROGMEM const_port_to_mode_PGM[] = {
		NOT_A_PORT,
		NOT_A_PORT,
		&DDRB,
		&DDRC,
		&DDRD,
	};

	constexpr const uint8_t PROGMEM const_port_to_output_PGM[] = {
		NOT_A_PORT,
		NOT_A_PORT,
		&PORTB,
		&PORTC,
		&PORTD,
	};

	constexpr const uint8_t PROGMEM const_port_to_input_PGM[] = {
		NOT_A_PORT,
		NOT_A_PORT,
		&PINB,
		&PINC,
		&PIND,
	};


	class PortID {

	private:
		const uint8_t mPortNumber;

		reg_ddr_t *mDDRPort;
		reg_port_t *mPort;
		const reg_pin_t *mPin;

	public:

		constexpr PortID(const uint8_t port) : 
		mPortNumber(port),
		mDDRPort(&const_port_to_mode_PGM[port]),
		mPort(&const_port_to_output_PGM[port]),
		mPin(&const_port_to_input_PGM[port])
		{}
		constexpr PortID(const PortID &obj) :
		mPortNumber(obj.mPortNumber),
		mDDRPort(obj.mDDRPort),
		mPort(obj.mPort),
		mPin(obj.mPin) {}

		constexpr uint8_t port() const {
			return mPortNumber;
		}

		constexpr operator uint8_t() const {
			return mPortNumber;
		}

		inline uint8_t digitalRead() const {
			return (*mPin);
		}
		inline uint8_t digitalRead(uint8_t mask, uint8_t shift=0) const {
			// Read the masked bits. Use shift value to align the results to LSB end.
			return ((*mPin) & mask) >> shift;
		}
		inline void digitalWrite(uint8_t value) const {
			(*mPort) = value;
		}
		inline void digitalWrite(uint8_t value, uint8_t mask, uint8_t shift=0) const {
			// Write the value into the masked bits.
			// Use shift to align value LSB with the start of the mask area.
			(*mPort) = ((*mPort) & ~mask) | ((value << shift) & mask);
		}

		inline void pinMode(uint8_t mode, uint8_t mask=255){
			switch(mode)
			{
				case INPUT:
			        *mDDRPort &= ~mask;
					break;
				case INPUT_PULLUP:
			        *mDDRPort &= ~mask;
			        *mPort |= mask;
					break;
				case OUTPUT:
			        *mDDRPort |= mask;
					break;
				default:
					break;
			}
		}

		void EnablePCInterupt(uint8_t portMask) const;
		void DisablePCInterupt(uint8_t portMask) const;
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
	constexpr static const PortID PORT_J(10);
	constexpr static const PortID PORT_K(11);
	constexpr static const PortID PORT_L(12);

	constexpr const PortID PROGMEM const_digital_pin_to_port_PGM[] = {
		// PORTLIST		
		// -------------------------------------------		
		PORT_E	, // PE 0 ** 0 ** USART0_RX	
		PORT_E	, // PE 1 ** 1 ** USART0_TX	
		PORT_E	, // PE 4 ** 2 ** PWM2	
		PORT_E	, // PE 5 ** 3 ** PWM3	
		PORT_G	, // PG 5 ** 4 ** PWM4	
		PORT_E	, // PE 3 ** 5 ** PWM5	
		PORT_H	, // PH 3 ** 6 ** PWM6	
		PORT_H	, // PH 4 ** 7 ** PWM7	
		PORT_H	, // PH 5 ** 8 ** PWM8	
		PORT_H	, // PH 6 ** 9 ** PWM9	
		PORT_B	, // PB 4 ** 10 ** PWM10	
		PORT_B	, // PB 5 ** 11 ** PWM11	
		PORT_B	, // PB 6 ** 12 ** PWM12	
		PORT_B	, // PB 7 ** 13 ** PWM13	
		PORT_J	, // PJ 1 ** 14 ** USART3_TX	
		PORT_J	, // PJ 0 ** 15 ** USART3_RX
		PORT_H	, // PH 1 ** 16 ** USART2_TX	
		PORT_H	, // PH 0 ** 17 ** USART2_RX	
		PORT_D	, // PD 3 ** 18 ** USART1_TX	
		PORT_D	, // PD 2 ** 19 ** USART1_RX	
		PORT_D	, // PD 1 ** 20 ** I2C_SDA	
		PORT_D	, // PD 0 ** 21 ** I2C_SCL	
		PORT_A	, // PA 0 ** 22 ** D22	
		PORT_A	, // PA 1 ** 23 ** D23	
		PORT_A	, // PA 2 ** 24 ** D24	
		PORT_A	, // PA 3 ** 25 ** D25	
		PORT_A	, // PA 4 ** 26 ** D26	
		PORT_A	, // PA 5 ** 27 ** D27	
		PORT_A	, // PA 6 ** 28 ** D28	
		PORT_A	, // PA 7 ** 29 ** D29	
		PORT_C	, // PC 7 ** 30 ** D30	
		PORT_C	, // PC 6 ** 31 ** D31	
		PORT_C	, // PC 5 ** 32 ** D32	
		PORT_C	, // PC 4 ** 33 ** D33	
		PORT_C	, // PC 3 ** 34 ** D34	
		PORT_C	, // PC 2 ** 35 ** D35	
		PORT_C	, // PC 1 ** 36 ** D36	
		PORT_C	, // PC 0 ** 37 ** D37	
		PORT_D	, // PD 7 ** 38 ** D38	
		PORT_G	, // PG 2 ** 39 ** D39	
		PORT_G	, // PG 1 ** 40 ** D40	
		PORT_G	, // PG 0 ** 41 ** D41	
		PORT_L	, // PL 7 ** 42 ** D42	
		PORT_L	, // PL 6 ** 43 ** D43	
		PORT_L	, // PL 5 ** 44 ** D44	
		PORT_L	, // PL 4 ** 45 ** D45	
		PORT_L	, // PL 3 ** 46 ** D46	
		PORT_L	, // PL 2 ** 47 ** D47	
		PORT_L	, // PL 1 ** 48 ** D48	
		PORT_L	, // PL 0 ** 49 ** D49	
		PORT_B	, // PB 3 ** 50 ** SPI_MISO	
		PORT_B	, // PB 2 ** 51 ** SPI_MOSI	
		PORT_B	, // PB 1 ** 52 ** SPI_SCK	
		PORT_B	, // PB 0 ** 53 ** SPI_SS	
		PORT_F	, // PF 0 ** 54 ** A0	
		PORT_F	, // PF 1 ** 55 ** A1	
		PORT_F	, // PF 2 ** 56 ** A2	
		PORT_F	, // PF 3 ** 57 ** A3	
		PORT_F	, // PF 4 ** 58 ** A4	
		PORT_F	, // PF 5 ** 59 ** A5	
		PORT_F	, // PF 6 ** 60 ** A6	
		PORT_F	, // PF 7 ** 61 ** A7	
		PORT_K	, // PK 0 ** 62 ** A8	
		PORT_K	, // PK 1 ** 63 ** A9	
		PORT_K	, // PK 2 ** 64 ** A10	
		PORT_K	, // PK 3 ** 65 ** A11	
		PORT_K	, // PK 4 ** 66 ** A12	
		PORT_K	, // PK 5 ** 67 ** A13	
		PORT_K	, // PK 6 ** 68 ** A14	
		PORT_K	, // PK 7 ** 69 ** A15	
		PORT_J	, // PJ 2 ** 70 ** D70
		PORT_J	, // PJ 3 ** 71 ** D71
		PORT_J	, // PJ 4 ** 72 ** D72
		PORT_J	, // PJ 5 ** 73 ** D73
		PORT_J	, // PJ 6 ** 74 ** D74
		PORT_J	, // PJ 7 ** 75 ** D75
		PORT_H	, // PH 2 ** 76 ** D76
		PORT_H	, // PH 7 ** 77 ** D77
		PORT_G	, // PG 3 ** 78 ** D78
		PORT_G	, // PG 4 ** 79 ** D79
		PORT_E	, // PE 2 ** 80 ** D80
		PORT_E	, // PE 6 ** 81 ** D81
		PORT_E	, // PE 7 ** 82 ** D82
		PORT_D	, // PD 4 ** 83 ** D83
		PORT_D	, // PD 5 ** 84 ** D84
		PORT_D	, // PD 6 ** 85 ** D85
	};

	class PinID {

	public:
		constexpr PinID(const uint8_t pin) : mPin(pin), mPort(const_digital_pin_to_port_PGM[pin]) {}
		constexpr PinID(const PinID &obj) : mPin(obj.mPin), mPort(obj.mPort) {}

		constexpr uint8_t pin() const {
			return mPin;
		}

		constexpr operator uint8_t() const {
			return mPin;
		}

	    template <class T>
		inline void pinMode(T mode) const{
			return ::pinMode(mPin, mode);
		}

		inline int digitalRead() const {
			return ::digitalRead(mPin);
		}

		inline void digitalWrite(const int value) const{
			return ::digitalWrite(mPin, value);
		}

		const uint8_t PortMask() const{
			return digitalPinToBitMask(mPin);
		}

		const PortID Port() const{
			return mPort;
		}

		const uint8_t mPin;
		const PortID &mPort;
	};


	class PinInt : public PinID {


	public: 
		constexpr PinInt(const uint8_t pin) : PinID(pin) {}
		constexpr PinInt(const PinID &obj) : PinID(obj.mPin) {}

		void EnablePCInterupt() const;

		void DisablePCInterupt() const;

	};


	typedef PinID PinID;

	// Arduino
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

}