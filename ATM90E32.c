/* ATM90E32 Energy Monitor Functions

  The MIT License (MIT)

  Copyright (c) 2016 whatnick,Ryzee and Arun

  Modified to use with the CircuitSetup.us Split Phase Energy Meter by jdeglavina

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "ATM90E32.h"

#include "timeout.h"

/* CommEnergyIC - Communication Establishment */
/*
  - Defines Register Mask
  - Treats the Register and SPI Comms
  - Outputs the required value in the register
*/
unsigned short CommEnergyIC(unsigned char RW, unsigned short address, unsigned short val)
{
  unsigned char* data = (unsigned char*)&val;
  unsigned char* adata = (unsigned char*)&address;
  unsigned short output;
  unsigned short address1;

  // Switch MSB and LSB of value
  output = (val >> 8) | (val << 8);
  val = output;

  // Set R/W flag
  address |= RW << 15;

  // Swap byte address
  address1 = (address >> 8) | (address << 8);
  address = address1;

  // Chip enable and wait for SPI activation
  //ATM_CS_EN;

  __delay_cycles(10 * MCLK_FREQ_MHZ);
  char i;
  // ATM_WRITE address byte by byte
  for (i = 0; i < 2; i++)
  {
    spi_transfer(*adata);
    adata++;
  }

  /* Must wait 4 us for data to become valid */
  __delay_cycles(8 * MCLK_FREQ_MHZ);

  // ATM_READ Data
  // Do for each byte in transfer
  if (RW)
  {
    for (i = 0; i < 2; i++)
    {
      *data = spi_transfer(0x00);
      data++;
    }
  }
  else
  {
    for (i = 0; i < 2; i++)
    {
      spi_transfer(*data);
      data++;
    }
  }

  // Chip enable and wait for transaction to end
//  ATM_CS_DIS;
  __delay_cycles(10 * MCLK_FREQ_MHZ);

  output = (val >> 8) | (val << 8); // reverse MSB and LSB
  return output;
}

char spi_transfer(char data){
  UCA0TXBUF = data;
  while(!(UCA0IFG & UCRXIFG));
  return UCA0RXBUF;
}


double CalibrateVI(unsigned short reg, unsigned short actualVal) {
//input the Voltage or Current register, and the actual value that it should be
//actualVal can be from a calibration meter or known value from a power supply
  unsigned short gain, val, m, gainReg;
	//sample the ATM_READing
	val = CommEnergyIC(ATM_READ, reg, 0xFFFF);
	val += CommEnergyIC(ATM_READ, reg, 0xFFFF);
	val += CommEnergyIC(ATM_READ, reg, 0xFFFF);
	val += CommEnergyIC(ATM_READ, reg, 0xFFFF);
	
	//get value currently in gain register
	switch (reg) {
		case UrmsA: {
			gainReg = UgainA; }
		case UrmsB: {
			gainReg = UgainB; }
		case UrmsC: {
			gainReg = UgainC; }
		case IrmsA: {
			gainReg = IgainA; }
		case IrmsB: {
			gainReg = IgainB; }
		case IrmsC: {
			gainReg = IgainC; }
	}
		
	gain = CommEnergyIC(ATM_READ, gainReg, 0xFFFF);
	m = actualVal;
	m = ((m * gain) / val);
	gain = m;
	
	//ATM_WRITE new value to gain register
	CommEnergyIC(ATM_WRITE, gainReg, gain);
	
	return(gain);
}


  
/* Parameters Functions*/
/*
  - Gets main electrical parameters,
  such as: Voltage, Current, Power, Energy,
  and Frequency, and Temperature

*/
// VOLTAGE
double GetLineVoltageA() {
  unsigned short voltage = CommEnergyIC(ATM_READ, UrmsA, 0xFFFF);
  return (double)voltage / 100;
}
double GetLineVoltageB() {
  unsigned short voltage = CommEnergyIC(ATM_READ, UrmsB, 0xFFFF);
  return (double)voltage / 100;
}
double GetLineVoltageC() {
  unsigned short voltage = CommEnergyIC(ATM_READ, UrmsC, 0xFFFF);
  return (double)voltage / 100;
}

// CURRENT
double GetLineCurrentA() {
  unsigned short current = CommEnergyIC(ATM_READ, IrmsA, 0xFFFF);
  __no_operation();
  return (double)current / 1000;
}
double GetLineCurrentB() {
  unsigned short current = CommEnergyIC(ATM_READ, IrmsB, 0xFFFF);
  __no_operation();
  return (double)current / 1000;
}
double GetLineCurrentC() {
  unsigned short current = CommEnergyIC(ATM_READ, IrmsC, 0xFFFF);
  __no_operation();
  return (double)current / 1000;
}
double GetLineCurrentN() {
  unsigned short current = CommEnergyIC(ATM_READ, IrmsN, 0xFFFF);
  return (double)current / 1000;
}
// CURRENT * 1000
unsigned short GetLineCurrentAu16() {
  unsigned short current = CommEnergyIC(ATM_READ, IrmsA, 0xFFFF);
  __no_operation();
  return current;
}
unsigned short GetLineCurrentBu16() {
  unsigned short current = CommEnergyIC(ATM_READ, IrmsB, 0xFFFF);
  __no_operation();
  return current;
}
unsigned short GetLineCurrentCu16() {
  unsigned short current = CommEnergyIC(ATM_READ, IrmsC, 0xFFFF);
  __no_operation();
  return (double)current;
}
unsigned short GetLineCurrentNu16() {
  unsigned short current = CommEnergyIC(ATM_READ, IrmsN, 0xFFFF);
  return current;
}


// FREQUENCY
double GetFrequency() {
  unsigned short freq = CommEnergyIC(ATM_READ, Freq, 0xFFFF);
  return (double)freq / 100;
}

// POWER FACTOR
double GetPowerFactorA() {
  signed short pf = (signed short) CommEnergyIC(ATM_READ, PFmeanA, 0xFFFF);
  return (double)pf / 1000;
}
double GetPowerFactorB() {
  signed short pf = (signed short) CommEnergyIC(ATM_READ, PFmeanB, 0xFFFF);
  return (double)pf / 1000;
}
double GetPowerFactorC() {
  signed short pf = (signed short) CommEnergyIC(ATM_READ, PFmeanC, 0xFFFF);
  return (double)pf / 1000;
}
double GetTotalPowerFactor() {
  signed short pf = (signed short) CommEnergyIC(ATM_READ, PFmeanT, 0xFFFF);
  return (double)pf / 1000;
}

// MEAN PHASE ANGLE
double GetPhaseA() {
  unsigned short angleA = (unsigned short) CommEnergyIC(ATM_READ, PAngleA, 0xFFFF);
  return (double)angleA / 10;
}
double GetPhaseB() {
  unsigned short angleB = (unsigned short) CommEnergyIC(ATM_READ, PAngleB, 0xFFFF);
  return (double)angleB / 10;
}
double GetPhaseC() {
  unsigned short angleC = (unsigned short) CommEnergyIC(ATM_READ, PAngleC, 0xFFFF);
  return (double)angleC / 10;
}

// TEMPERATURE
double GetTemperature() {
  short int atemp = (short int) CommEnergyIC(ATM_READ, Temp, 0xFFFF);
  return (double)atemp;
}

/* Gets the Register Value if Desired */
// REGISTER
double GetValueRegister(unsigned short registerATM_READ) {
  return (double) CommEnergyIC(ATM_READ, registerATM_READ, 0xFFFF); //returns value register
}

// REGULAR ENERGY MEASUREMENT

// FORWARD ACTIVE ENERGY
// these registers accumulate energy and are cleared after being ATM_READ
double GetImportEnergy() {
  unsigned short ienergyT = CommEnergyIC(ATM_READ, APenergyT, 0xFFFF);
  return (double)ienergyT / 100 / 3200; //returns kWh
}

// FORWARD REACTIVE ENERGY
double GetImportReactiveEnergy() {
  unsigned short renergyT = CommEnergyIC(ATM_READ, RPenergyT, 0xFFFF);
  return (double)renergyT / 100 / 3200; //returns kWh
}

// APPARENT ENERGY
double GetImportApparentEnergy() {
  unsigned short senergyT = CommEnergyIC(ATM_READ, SAenergyT, 0xFFFF);
  return (double)senergyT / 100 / 3200; //returns kWh
}

// REVERSE ACTIVE ENERGY
double GetExportEnergy() {
  unsigned short eenergyT = CommEnergyIC(ATM_READ, ANenergyT, 0xFFFF);
  return (double)eenergyT / 100 / 3200; //returns kWh
}

// REVERSE REACTIVE ENERGY
double GetExportReactiveEnergy() {
  unsigned short reenergyT = CommEnergyIC(ATM_READ, RNenergyT, 0xFFFF);
  return (double)reenergyT / 100 / 3200; //returns kWh
}


/* System Status Registers */
unsigned short GetSysStatus0() {
  return CommEnergyIC(ATM_READ, EMMIntState0, 0xFFFF);
}
unsigned short GetSysStatus1() {
  return CommEnergyIC(ATM_READ, EMMIntState1, 0xFFFF);
}
unsigned short GetMeterStatus0() {
  return CommEnergyIC(ATM_READ, EMMState0, 0xFFFF);
}
unsigned short GetMeterStatus1() {
  return CommEnergyIC(ATM_READ, EMMState1, 0xFFFF);
}

void SetFrequencyATM(unsigned short lineFreq){
  CommEnergyIC(ATM_WRITE, MMode0, _lineFreq);   // 33 Mode Config (frequency set in main program)
  return;
}

/* BEGIN FUNCTION */
/*
  - Define the pin to be used as Chip Select
  - Set serialFlag to true for serial debugging
  - Use SPI MODE 0 for the ATM90E32
*/
void atm_begin(unsigned short lineFreq, unsigned short pgagain, unsigned short ugain, unsigned short igainA, unsigned short igainB, unsigned short igainC)
{
  _lineFreq = lineFreq; //frequency of power
  _pgagain = pgagain; //PGA Gain for current channels
  _ugain = ugain; //voltage rms gain
  _igainA = igainA; //CT1
  _igainB = igainB; //CT2 - not used for single split phase meter
  _igainC = igainC; //CT2 for single split phase meter - CT3 otherwise

  //calculation for voltage sag threshold - assumes we do not want to go under 90v for split phase and 190v otherwise
  //determine proper low and high frequency threshold
  unsigned short vSagTh;
  unsigned short sagV;
  unsigned short FreqHiThresh;
  unsigned short FreqLoThresh;
  if (_lineFreq == 4485 || _lineFreq == 5231)
  {
    sagV = 90;
    FreqHiThresh = 61 * 100;
    FreqLoThresh = 59 * 100;
  }
  else
  {
    sagV = 190;
	  FreqHiThresh = 51 * 100;
    FreqLoThresh = 49 * 100;
  }

  vSagTh = (sagV * 100 * sqrt(2)) / (2 * _ugain / 32768);

  //Initialize registers
  CommEnergyIC(ATM_WRITE, SoftReset, 0x789A);     // 70 Perform soft reset
  CommEnergyIC(ATM_WRITE, CfgRegAccEn, 0x55AA);   // 7F enable register config access
  CommEnergyIC(ATM_WRITE, MeterEn, 0x0001);       // 00 Enable Metering

  CommEnergyIC(ATM_WRITE, SagPeakDetCfg, 0x143F); // 05 Sag and Voltage peak detect period set to 20ms
  CommEnergyIC(ATM_WRITE, SagTh, vSagTh);         // 08 Voltage sag threshold
  CommEnergyIC(ATM_WRITE, FreqHiTh, FreqHiThresh);  // 0D High frequency threshold
  CommEnergyIC(ATM_WRITE, FreqLoTh, FreqLoThresh);  // 0C Lo frequency threshold
  CommEnergyIC(ATM_WRITE, EMMIntEn0, 0xB76F);     // 75 Enable interrupts
  CommEnergyIC(ATM_WRITE, EMMIntEn1, 0xDDFD);     // 76 Enable interrupts
  CommEnergyIC(ATM_WRITE, EMMIntState0, 0x0001);  // 73 Clear interrupt flags
  CommEnergyIC(ATM_WRITE, EMMIntState1, 0x0001);  // 74 Clear interrupt flags
  CommEnergyIC(ATM_WRITE, ZXConfig, 0xD654);      // 07 ZX2, ZX1, ZX0 pin config - set to current channels, all polarity

  //Set metering config values (CONFIG)
  CommEnergyIC(ATM_WRITE, PLconstH, 0x0861);    // 31 PL Constant MSB (default) - Meter Constant = 3200 - PL Constant = 140625000
  CommEnergyIC(ATM_WRITE, PLconstL, 0xC468);    // 32 PL Constant LSB (default) - this is 4C68 in the application note, which is incorrect
  CommEnergyIC(ATM_WRITE, MMode0, _lineFreq);   // 33 Mode Config (frequency set in main program)
  CommEnergyIC(ATM_WRITE, MMode1, _pgagain);    // 34 PGA Gain Configuration for Current Channels - 0x002A (x4) // 0x0015 (x2) // 0x0000 (1x)
  CommEnergyIC(ATM_WRITE, PStartTh, 0x1D4C);    // 35 All phase Active Startup Power Threshold - 50% of startup current = 0.02A/0.00032 = 7500
  CommEnergyIC(ATM_WRITE, QStartTh, 0x1D4C);    // 36 All phase Reactive Startup Power Threshold
  CommEnergyIC(ATM_WRITE, SStartTh, 0x1D4C);    // 37 All phase Apparent Startup Power Threshold
  CommEnergyIC(ATM_WRITE, PPhaseTh, 0x02EE);    // 38 Each phase Active Phase Threshold = 10% of startup current = 0.002A/0.00032 = 750
  CommEnergyIC(ATM_WRITE, QPhaseTh, 0x02EE);    // 39 Each phase Reactive Phase Threshold
  CommEnergyIC(ATM_WRITE, SPhaseTh, 0x02EE);    // 3A Each phase Apparent Phase Threshold

  //Set metering calibration values (CALIBRATION)
  CommEnergyIC(ATM_WRITE, PQGainA, 0x0000);     // 47 Line calibration gain
  CommEnergyIC(ATM_WRITE, PhiA, 0x0000);        // 48 Line calibration angle
  CommEnergyIC(ATM_WRITE, PQGainB, 0x0000);     // 49 Line calibration gain
  CommEnergyIC(ATM_WRITE, PhiB, 0x0000);        // 4A Line calibration angle
  CommEnergyIC(ATM_WRITE, PQGainC, 0x0000);     // 4B Line calibration gain
  CommEnergyIC(ATM_WRITE, PhiC, 0x0000);        // 4C Line calibration angle
  CommEnergyIC(ATM_WRITE, PoffsetA, 0x0000);    // 41 A line active power offset FFDC
  CommEnergyIC(ATM_WRITE, QoffsetA, 0x0000);    // 42 A line reactive power offset
  CommEnergyIC(ATM_WRITE, PoffsetB, 0x0000);    // 43 B line active power offset
  CommEnergyIC(ATM_WRITE, QoffsetB, 0x0000);    // 44 B line reactive power offset
  CommEnergyIC(ATM_WRITE, PoffsetC, 0x0000);    // 45 C line active power offset
  CommEnergyIC(ATM_WRITE, QoffsetC, 0x0000);    // 46 C line reactive power offset

  //Set metering calibration values (HARMONIC)
  CommEnergyIC(ATM_WRITE, POffsetAF, 0x0000);   // 51 A Fund. active power offset
  CommEnergyIC(ATM_WRITE, POffsetBF, 0x0000);   // 52 B Fund. active power offset
  CommEnergyIC(ATM_WRITE, POffsetCF, 0x0000);   // 53 C Fund. active power offset
  CommEnergyIC(ATM_WRITE, PGainAF, 0x0000);     // 54 A Fund. active power gain
  CommEnergyIC(ATM_WRITE, PGainBF, 0x0000);     // 55 B Fund. active power gain
  CommEnergyIC(ATM_WRITE, PGainCF, 0x0000);     // 56 C Fund. active power gain

  //Set measurement calibration values (ADJUST)
  CommEnergyIC(ATM_WRITE, UgainA, _ugain);      // 61 A Voltage rms gain
  CommEnergyIC(ATM_WRITE, IgainA, _igainA);     // 62 A line current gain
  CommEnergyIC(ATM_WRITE, UoffsetA, 0x0000);    // 63 A Voltage offset - 61A8
  CommEnergyIC(ATM_WRITE, IoffsetA, 0x0000);    // 64 A line current offset - FE60
  CommEnergyIC(ATM_WRITE, UgainB, _ugain);      // 65 B Voltage rms gain
  CommEnergyIC(ATM_WRITE, IgainB, _igainB);     // 66 B line current gain
  CommEnergyIC(ATM_WRITE, UoffsetB, 0x0000);    // 67 B Voltage offset - 1D4C
  CommEnergyIC(ATM_WRITE, IoffsetB, 0x0000);    // 68 B line current offset - FE60
  CommEnergyIC(ATM_WRITE, UgainC, _ugain);      // 69 C Voltage rms gain
  CommEnergyIC(ATM_WRITE, IgainC, _igainC);     // 6A C line current gain
  CommEnergyIC(ATM_WRITE, UoffsetC, 0x0000);    // 6B C Voltage offset - 1D4C
  CommEnergyIC(ATM_WRITE, IoffsetC, 0x0000);    // 6C C line current offset

  CommEnergyIC(ATM_WRITE, CfgRegAccEn, 0x0000); // 7F end configuration
}
