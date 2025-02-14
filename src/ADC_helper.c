//Matthew Matti & Lakeysha Green
#include "ADC_helper.h"

uint32_t ADC_Values[13];



void SetupADCPins(void);

//set up for 2 pots and accelerometer + 1 extra
void SetupADCPins()
{
	GPIOPinTypeADC(GPIO_PORTE_BASE,GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1); // pin 3 is AIN0 pin 2 is AIN1 pin 1 is AIN2 (bit wise or 0b00000111)
	GPIOPinTypeADC(GPIO_PORTD_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); //AIN7-pin 0, AIN6-pin 1, AIN5 - pin 2, AIN4- pin 3 (bit wise or 0b00001111)
	//GPIOPinTypeADC(GPIO_PORTE_BASE,GPIO_PIN_2);
	
}

void SetupADC()
{
	
	SetupADCPins(); //setup the GPIO
	
	//
	// Enable the ADC0 module.
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); //module 1/2.. module 2/2 not used
	//
	// Wait for the ADC0 module to be ready.
	//
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)) 
	{
	}
	
	ADCReferenceSet(ADC0_BASE, ADC_REF_EXT_3V); //for reference so a 3 V supply must be given to the AVREF pin
	//
	// Enable the first sample sequencer to capture the value of channel 0 when
	// the processor trigger occurs.
	//
	ADCSequenceDisable(ADC0_BASE,0); 
	ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0); 
	//ADCSequenceStepConfigure(ADC0_BASE, 0, 0,	ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH1 | ADC_CTL_CH2| ADC_CTL_CH4| ADC_CTL_CH5| ADC_CTL_CH6| ADC_CTL_CH7);
	ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH0 );
  ADCSequenceStepConfigure(ADC0_BASE, 0, 1, ADC_CTL_CH1 );	
  ADCSequenceStepConfigure(ADC0_BASE, 0, 2, ADC_CTL_CH2 );	
	ADCSequenceStepConfigure(ADC0_BASE, 0, 3, ADC_CTL_CH4 );	
	ADCSequenceStepConfigure(ADC0_BASE, 0, 4, ADC_CTL_CH5 );	
	ADCSequenceStepConfigure(ADC0_BASE, 0, 5, ADC_CTL_CH6 );	
	ADCSequenceStepConfigure(ADC0_BASE, 0, 6, ADC_CTL_CH7 | ADC_CTL_END);	
	
	
	//ADCSequenceStepConfigure(ADC0_BASE, 0, 0,	ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH1 );
	
	
	ADCSequenceEnable(ADC0_BASE, 0); //enables the sequence 0

		
}

void ADCReadChan()
{
	int32_t light;
	//
	//
	ADCProcessorTrigger(ADC0_BASE, 0); // Trigger the sample sequence above (sequence 0)

	//
	// Wait until the sample sequence has completed.
	//
	while(ADCBusy(ADC0_BASE)){};
	//while(!ADCIntStatus(ADC0_BASE, 0, false))
	{
	}
	//
	// Read the value from the ADC.
	//
	
	light = (ADCSequenceDataGet(ADC0_BASE, 0, ADC_Values));
	if (light < 13)
	{
		ADC_Values[12]=light; 
	}
}