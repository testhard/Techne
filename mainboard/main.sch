EESchema Schematic File Version 4
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_01x15_Female J2
U 1 1 5CD3358F
P 6150 2900
F 0 "J2" H 6178 2926 50  0000 L CNN
F 1 "Conn_01x15_Female" H 6178 2835 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x15_P2.54mm_Vertical" H 6150 2900 50  0001 C CNN
F 3 "~" H 6150 2900 50  0001 C CNN
	1    6150 2900
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x15_Female J4
U 1 1 5CD34891
P 6900 2900
F 0 "J4" H 6928 2926 50  0000 L CNN
F 1 "Conn_01x15_Female" H 6928 2835 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x15_P2.54mm_Vertical" H 6900 2900 50  0001 C CNN
F 3 "~" H 6900 2900 50  0001 C CNN
	1    6900 2900
	1    0    0    -1  
$EndComp
Text GLabel 7100 2200 0    50   Input ~ 0
D0
Text GLabel 7100 2300 0    50   Input ~ 0
D1
Text GLabel 7100 2400 0    50   Input ~ 0
D2
Text GLabel 7100 2500 0    50   Input ~ 0
D3
Text GLabel 7100 2600 0    50   Input ~ 0
D4
Text GLabel 7100 2900 0    50   Input ~ 0
CLK
Text GLabel 7100 3000 0    50   Input ~ 0
MISO
Text GLabel 7100 3100 0    50   Input ~ 0
MOSI
Text GLabel 7100 3200 0    50   Input ~ 0
HCS
Text GLabel 7100 3300 0    50   Input ~ 0
RX
Text GLabel 7100 3400 0    50   Input ~ 0
TX
Text GLabel 5850 3600 0    50   Input ~ 0
VI
Wire Wire Line
	7100 2200 6700 2200
Wire Wire Line
	7100 2300 6700 2300
Wire Wire Line
	7100 2600 6700 2600
Wire Wire Line
	7100 2900 6700 2900
Wire Wire Line
	7100 3000 6700 3000
Wire Wire Line
	7100 3100 6700 3100
Wire Wire Line
	7100 3200 6700 3200
Wire Wire Line
	7100 3300 6700 3300
Wire Wire Line
	7100 3400 6700 3400
Wire Wire Line
	5850 3600 5950 3600
$Comp
L Connector:Conn_01x11_Female J3
U 1 1 5CD3B41C
P 6450 4400
F 0 "J3" V 6523 4380 50  0000 C CNN
F 1 "Conn_01x11_Female" V 6614 4380 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x11_P2.54mm_Horizontal" H 6450 4400 50  0001 C CNN
F 3 "~" H 6450 4400 50  0001 C CNN
	1    6450 4400
	0    1    1    0   
$EndComp
Text GLabel 5950 4100 1    50   Input ~ 0
D1
Wire Wire Line
	5950 3500 6200 3500
Wire Wire Line
	6200 3500 6200 3900
Wire Wire Line
	6200 3900 6050 3900
Wire Wire Line
	6050 3900 6050 4200
Wire Wire Line
	5950 4100 5950 4200
Text GLabel 6150 4100 1    50   Input ~ 0
HCS
Text GLabel 6250 4100 1    50   Input ~ 0
D4
Text GLabel 6350 4100 1    50   Input ~ 0
MOSI
Text GLabel 6450 4100 1    50   Input ~ 0
CLK
Text GLabel 6550 4100 1    50   Input ~ 0
MISO
Wire Wire Line
	6650 4200 6650 3600
Wire Wire Line
	6650 3600 6700 3600
Wire Wire Line
	6550 4100 6550 4200
Wire Wire Line
	6450 4100 6450 4200
Wire Wire Line
	6350 4100 6350 4200
Wire Wire Line
	6250 4100 6250 4200
Wire Wire Line
	6150 4100 6150 4200
Text GLabel 6750 4100 1    50   Input ~ 0
Up
Text GLabel 6850 4100 1    50   Input ~ 0
Enter
Text GLabel 6950 4100 1    50   Input ~ 0
Down
Wire Wire Line
	6750 4200 6750 4100
Wire Wire Line
	6850 4200 6850 4100
Wire Wire Line
	6950 4200 6950 4100
$Comp
L Converter_ACDC:HLK-PM01 PS1
U 1 1 5CD430E6
P 4950 3450
F 0 "PS1" H 4950 3775 50  0000 C CNN
F 1 "HLK-PM01" H 4950 3684 50  0000 C CNN
F 2 "Converter_ACDC:Converter_ACDC_HiLink_HLK-PMxx" H 4950 3150 50  0001 C CNN
F 3 "http://www.hlktech.net/product_detail.php?ProId=54" H 5350 3100 50  0001 C CNN
	1    4950 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 3600 5700 3600
Wire Wire Line
	5700 3600 5700 3500
Wire Wire Line
	5700 3500 5950 3500
Connection ~ 5950 3500
Text GLabel 5600 3400 0    50   Input ~ 0
VI
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5CD46AD1
P 4150 3400
F 0 "J1" H 4230 3392 50  0000 L CNN
F 1 "Conn_01x02" H 4230 3301 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x02_P5.08mm_Drill1.5mm" H 4150 3400 50  0001 C CNN
F 3 "~" H 4150 3400 50  0001 C CNN
	1    4150 3400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Female J5
U 1 1 5CD4D64F
P 7500 2400
F 0 "J5" H 7528 2376 50  0000 L CNN
F 1 "Conn_01x04_Female" H 7528 2285 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 7500 2400 50  0001 C CNN
F 3 "~" H 7500 2400 50  0001 C CNN
	1    7500 2400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Female J6
U 1 1 5CD4DC7C
P 8200 2350
F 0 "J6" H 8228 2326 50  0000 L CNN
F 1 "Conn_01x06_Female" H 8228 2235 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical" H 8200 2350 50  0001 C CNN
F 3 "~" H 8200 2350 50  0001 C CNN
	1    8200 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 2400 7300 2400
Wire Wire Line
	6700 2500 7300 2500
Wire Wire Line
	7300 2300 7600 2300
Wire Wire Line
	7300 2600 7300 2800
Wire Wire Line
	7300 2800 6700 2800
$Comp
L MCU_Microchip_ATtiny:ATtiny45-20PU U1
U 1 1 5CD531BD
P 8300 3800
F 0 "U1" H 7771 3846 50  0000 R CNN
F 1 "ATtiny45-20PU" H 7771 3755 50  0000 R CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 8300 3800 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 8300 3800 50  0001 C CNN
	1    8300 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 3200 8300 3200
Wire Wire Line
	6050 4200 6050 4650
Wire Wire Line
	6050 4650 8300 4650
Wire Wire Line
	8300 4650 8300 4400
Connection ~ 6050 4200
Text GLabel 9200 3800 0    50   Input ~ 0
Enter
Text GLabel 9200 3900 0    50   Input ~ 0
Up
Text GLabel 9200 3500 0    50   Input ~ 0
Down
Text GLabel 9200 3700 0    50   Input ~ 0
RX
Wire Wire Line
	9200 3500 8900 3500
Wire Wire Line
	9200 3800 8900 3800
Wire Wire Line
	9200 3900 8900 3900
Wire Wire Line
	4550 3350 3950 3350
Wire Wire Line
	3950 3350 3950 3400
Wire Wire Line
	5350 3350 5350 3400
Wire Wire Line
	5350 3400 5600 3400
Wire Wire Line
	5350 3550 5450 3550
Wire Wire Line
	5450 3550 5450 3600
Wire Wire Line
	7750 2300 7750 3200
Wire Wire Line
	5950 3200 5800 3200
Wire Wire Line
	5800 3200 5800 2100
Wire Wire Line
	5800 2100 7600 2100
Wire Wire Line
	7600 2100 7600 2300
Connection ~ 7600 2300
Wire Wire Line
	7600 2300 7750 2300
$Comp
L Switch:SW_MEC_5G SW1
U 1 1 5CD67C34
P 4400 3850
F 0 "SW1" H 4400 4135 50  0000 C CNN
F 1 "SW_MEC_5G" H 4400 4044 50  0000 C CNN
F 2 "Button_Switch_THT:SW_NKK_GW12LJP" H 4400 4050 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=488" H 4400 4050 50  0001 C CNN
	1    4400 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 3700 8900 3700
$Comp
L Mechanical:MountingHole H1
U 1 1 5CDAFBAC
P 6000 1550
F 0 "H1" H 6100 1596 50  0000 L CNN
F 1 "MountingHole" H 6100 1505 50  0000 L CNN
F 2 "MountingHole:MountingHole_3mm" H 6000 1550 50  0001 C CNN
F 3 "~" H 6000 1550 50  0001 C CNN
	1    6000 1550
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5CDB1941
P 6400 1550
F 0 "H2" H 6500 1596 50  0000 L CNN
F 1 "MountingHole" H 6500 1505 50  0000 L CNN
F 2 "MountingHole:MountingHole_3mm" H 6400 1550 50  0001 C CNN
F 3 "~" H 6400 1550 50  0001 C CNN
	1    6400 1550
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 5CDB2830
P 6750 1600
F 0 "H3" H 6850 1646 50  0000 L CNN
F 1 "MountingHole" H 6850 1555 50  0000 L CNN
F 2 "MountingHole:MountingHole_3mm" H 6750 1600 50  0001 C CNN
F 3 "~" H 6750 1600 50  0001 C CNN
	1    6750 1600
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 5CDB367F
P 7100 1650
F 0 "H4" H 7200 1696 50  0000 L CNN
F 1 "MountingHole" H 7200 1605 50  0000 L CNN
F 2 "MountingHole:MountingHole_3mm" H 7100 1650 50  0001 C CNN
F 3 "~" H 7100 1650 50  0001 C CNN
	1    7100 1650
	1    0    0    -1  
$EndComp
$EndSCHEMATC
