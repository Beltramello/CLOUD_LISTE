//****************************************************//
//                                                    //
//                 CLOUD   Repeater                   //     
//                                                    // 
//****************************************************//

/*
Name:		Repeater
Created:	09/09/2016 3:17:16 PM
Author:		Carlos Beltramello
Company:	QL Labor - Continental AG
*/


//Required libraries
#include "variant.h"
#include <due_can.h>

int interval = 300;
uint32_t previousMillis = 0;
uint32_t currentMillis = 0;



void sendData()
{
	CAN_FRAME myFrame;
	myFrame.id = 0x25A;
	myFrame.length = 1;
	myFrame.data.bytes[0] = 22;
	myFrame.extended = false;
	Can0.sendFrame(myFrame);

	//myFrame.id = 0x26A;
	//myFrame.length = 1;
	//myFrame.data.bytes[0] = 23;
	//myFrame.extended = false;
	//Can1.sendFrame(myFrame);

	//myFrame.id = 0x27A;
	//myFrame.length = 1;
	//myFrame.data.bytes[0] = 24;
	//myFrame.extended = false;
	//Can1.sendFrame(myFrame);

}

//********************INIT Parameters*****************//
void setup()
{
	Can0.begin(CAN_BPS_500K); // Initialize Can1, Set the proper baud rates here//
	Can1.disable();

	// Initialize Can1 Mailboxs
	/*Can1.reset_all_mailbox();
	Can1.disable_interrupt(CAN_DISABLE_ALL_INTERRUPT_MASK);*/

	//---------------------------IER_Register------------------------------------------------//
	//   | - | - | - |BERR||FERR|AERR|SERR|CERR||TSTP|TOVF|WAKE|SLEEP||BOFF|ERRP|WARN|ERRA|| //
	//   | 0 | 0 | 0 |  1 ||  1 |  1 |  1 | 1  ||  1 |  1 |  0 |  0  || 1  | 1  | 0  |  1 || //
	//																    			    	 //
	//   |- | - | - | - || - | - | - | - ||MB7|MB6|MB5|MB4||MB3|MB2|MB1|MB0|				 //
	//   |0 | 0 | 0 | 0 || 0 | 0 | 0 | 0 || 0 | 1 | 1 | 1 || 1 | 1 | 0 | 1 |				 //												
	//---------------------------------------------------------------------------------------//
	Can0.enable_interrupt(0x1FCD007D);

	//Can1.disable_time_triggered_mode();
	//Can1.set_timestamp_capture_point(0);
	//Can1.enable_overload_frame();

	//***********************************************//
	//			Mode of Mailboxes					 //
	//***********************************************//
	Can0.mailbox_set_mode(0, CAN_MB_RX_MODE);	//MAILBOX 0 Receive mailbox
	Can0.mailbox_set_mode(1, CAN_MB_TX_MODE);	//MAILBOX 1 Transmit mailbox
	Can0.mailbox_set_mode(2, CAN_MB_RX_MODE);	//MAILBOX 2 Receive mailbox
	Can0.mailbox_set_mode(3, CAN_MB_RX_MODE);	//MAILBOX 3 Receive mailbox
	Can0.mailbox_set_mode(4, CAN_MB_RX_MODE);	//MAILBOX 4 Receive mailbox
	Can0.mailbox_set_mode(5, CAN_MB_RX_MODE);	//MAILBOX 5 Receive mailbox
	Can0.mailbox_set_mode(6, CAN_MB_RX_MODE);	//MAILBOX 6 Receive mailbox
	Can0.mailbox_set_mode(7, CAN_MB_TX_MODE);	//MAILBOX 7 Transmit mailbox


	//***********************************************//
	//			Mask filter of Mailboxes			 //
	//***********************************************//
	Can0.setRXFilter(0,0x000, 0x700, false);
	Can0.setRXFilter(2, 0x100, 0x7F0, false);
	//Can1.setRXFilter(3, 0x210, 0x210, false);
	//Can1.setRXFilter(4, 0x000FF, 0x000FF, false);
	//Can1.setRXFilter(5, 0x100, 0x100, true);
	//Can1.setRXFilter(6, 0x100, 0x100, true);
	//Can1.setRXFilter(7, 0x100, 0x100, true);
	//Can1.setRXFilter(3, 0x00, 0x00, false); //catch all mailbox
	Can0.watchFor();

	//***********************************************//
	//  now register all of the callback functions   //
	//***********************************************//

	Can0.setCallback(0, Repeater_callback00);
	Can0.setCallback(2, Repeater_callback02);
	//Can1.setCallback(3, Repeater_callback3);
	//Can1.setCallback(4, Repeater_callback4);
	//Can1.setCallback(5, Repeater_callback5);
	//Can1.setCallback(6, Repeater_callback6);
	Can0.setGeneralCallback(Repeater_callback0G);

	////to low current consumption
	USBDevice.detach();		  //USB Core disable	

	//pinMode(68, OUTPUT); // CAN0 RX PUll-Up Disable
	//digitalWrite(68, LOW);

	//pinMode(1, OUTPUT); // RX PUll-Up Disable
	//digitalWrite(1, LOW);

	//pinMode(69, OUTPUT); // CAN0 TX PUll-Up Disable
	//digitalWrite(69, LOW);

	//pinMode(0, OUTPUT); // RX PUll-Up Disable
	//digitalWrite(0, LOW);

	pmc_disable_periph_clk(ID_ADC); //AD converter Disable

}


void loop()
{
	//uint32_t currentMillis = millis();
	//if (currentMillis - previousMillis >= interval)
	//{
	//		sendData();
	//	
	//	previousMillis = currentMillis;
	//}
}

