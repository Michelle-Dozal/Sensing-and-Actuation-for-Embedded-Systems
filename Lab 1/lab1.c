#include "fsl_device_registers.h"

void software_delay(unsigned long delay)
{
    while (delay > 0) delay--;
}

//Lab_2_Part_4
int main(void)
{
    int ROT_DIR;
    int CNT_DIR;
    int Switch = 0x00;
    int Switch2 = 0x01;
    int x = 0x00;
    unsigned long Delay = 0x100000;

    SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; //Configure Clock Gating for PortB
    SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK; //Configure Clock Gating for PortC
    SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; //Configure Clock Gating for PortD


    PORTD_GPCLR = 0x00FF0100; //Configure Port D Pins 0-7 for GPIO;
    PORTC_GPCLR = 0x01BF0100; //Configure Port C Pins 0-5 and 7-8 for GPIO;
    PORTB_GPCLR = 0x000C0100; //Configure Port B Pin 2 and 3 for GPIO;


    GPIOB_PDDR = 0x00000000;  //Configure Port B Pin 1 for Input;
    GPIOD_PDDR = 0x000000FF; //Configure Port D Pins 0-7 for Output;
    GPIOC_PDDR = 0x000001BF; //Configure Port C Pins 0-5 and 7-8 for Output;


    //Initialize Port C to 0;
    GPIOC_PDOR = 0x00;
    //Initialize Port D with 1 LED on;
    GPIOD_PDOR = 0x01;
    //Initialize CNT_DIR and ROT_DIR
    CNT_DIR = 0x00;
    ROT_DIR = 0x00;


    while (1)
        {
            software_delay(Delay);


            Switch = GPIOB_PDIR & 0x04;    //Set switch to input port B
            if (Switch == 0)
            {
                CNT_DIR++;
                if(GPIOC_PDOR == 0x1FF)   //When the LED's are already at max
                {
                CNT_DIR = 0x00;
                }
                GPIOC_PDOR = CNT_DIR;

            }
            else
            {
                CNT_DIR--;
                if(GPIOC_PDOR == 0x00)      //When the LED's are already at max
                {
                 CNT_DIR = 0x1FF;
                 }
                GPIOC_PDOR = CNT_DIR;


            }
            Switch2 = GPIOB_PDIR & 0x08; //Set switch2 to input port B
            if (Switch2 == 0)
            {
                ROT_DIR = GPIOD_PDOR << 1;    //left-rotate Port D
                if(GPIOD_PDOR == 0x80) //Case when unable to shift anymore
                {
                    ROT_DIR = 0x01;
                }
                GPIOD_PDOR = ROT_DIR;
            }
            else
            {
                ROT_DIR = GPIOD_PDOR >> 1;        //right-rotate Port D
                if(GPIOD_PDOR == 0x00)   //Case when unable to shift anymore
                {
                    ROT_DIR = 0x80;
                }
                GPIOD_PDOR = ROT_DIR;
            }
        }
        return 0;
    }


