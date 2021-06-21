EESchema Schematic File Version 4
LIBS:User_Interface_Board-cache
EELAYER 30 0
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
L power:GND #PWR01
U 1 1 5E2349BA
P 3350 3650
F 0 "#PWR01" H 3350 3400 50  0001 C CNN
F 1 "GND" H 3355 3477 50  0000 C CNN
F 2 "" H 3350 3650 50  0001 C CNN
F 3 "" H 3350 3650 50  0001 C CNN
	1    3350 3650
	1    0    0    -1  
$EndComp
Text Label 3350 3650 0    50   ~ 0
GND
$Comp
L Connector:Conn_01x02_Male J5
U 1 1 5E271F18
P 5500 4800
F 0 "J5" H 5608 4981 50  0000 C CNN
F 1 "Conn_01x02_Male" H 5608 4890 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5500 4800 50  0001 C CNN
F 3 "~" H 5500 4800 50  0001 C CNN
	1    5500 4800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Male J4
U 1 1 5E3013BB
P 5350 2300
F 0 "J4" H 5458 2781 50  0000 C CNN
F 1 "Conn_01x08_Male" H 5458 2690 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 5350 2300 50  0001 C CNN
F 3 "~" H 5350 2300 50  0001 C CNN
	1    5350 2300
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Male J6
U 1 1 5E305AD6
P 7050 3900
F 0 "J6" H 7158 4281 50  0000 C CNN
F 1 "Conn_01x05_Male" H 7158 4190 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 7050 3900 50  0001 C CNN
F 3 "~" H 7050 3900 50  0001 C CNN
	1    7050 3900
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J3
U 1 1 5E4ABD04
P 4500 4000
F 0 "J3" H 4608 4281 50  0000 C CNN
F 1 "Conn_01x03_Male" H 4608 4190 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4500 4000 50  0001 C CNN
F 3 "~" H 4500 4000 50  0001 C CNN
	1    4500 4000
	1    0    0    -1  
$EndComp
Text Label 4700 3900 0    50   ~ 0
3,3V
Text Label 4700 4100 0    50   ~ 0
GND
Text Label 4700 4000 0    50   ~ 0
POTI
$Comp
L Device:R C1
U 1 1 5E6CA5EA
P 2900 3750
F 0 "C1" H 2970 3796 50  0000 L CNN
F 1 "1u" H 2970 3705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" V 2830 3750 50  0001 C CNN
F 3 "~" H 2900 3750 50  0001 C CNN
	1    2900 3750
	1    0    0    -1  
$EndComp
Text Label 2900 3600 0    50   ~ 0
3,3V
Text Label 2900 3900 0    50   ~ 0
GND
Text Label 5550 2000 0    50   ~ 0
BUSY
Text Label 5550 2100 0    50   ~ 0
RST
Text Label 5550 2200 0    50   ~ 0
DC
Text Label 5550 2300 0    50   ~ 0
CS
Text Label 5550 2400 0    50   ~ 0
CLK
Text Label 5550 2500 0    50   ~ 0
DIN
Text Label 5550 2600 0    50   ~ 0
GND
Text Label 5550 2700 0    50   ~ 0
3,3V
Text Notes 5750 2300 0    50   ~ 0
WAVESHARE 1.54 INCH E-PAPER-DISPLAY
Text Label 7250 3700 0    50   ~ 0
SW
Text Label 7250 3800 0    50   ~ 0
VRy
Text Label 7250 3900 0    50   ~ 0
VRx
Text Label 7250 4000 0    50   ~ 0
3,3V
Text Label 7250 4100 0    50   ~ 0
GND
Text Notes 6350 3900 0    50   ~ 0
JOYSTICK
Text Notes 4950 4000 0    50   ~ 0
POTENTIOMETER
Text Label 5700 4550 0    50   ~ 0
3,3V
Wire Wire Line
	5700 4550 5700 4800
$Comp
L Device:R R3
U 1 1 60D1CC7A
P 5700 5200
F 0 "R3" H 5770 5246 50  0000 L CNN
F 1 "100k" H 5770 5155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5630 5200 50  0001 C CNN
F 3 "~" H 5700 5200 50  0001 C CNN
	1    5700 5200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 60D1D73F
P 6150 4900
F 0 "R4" V 5943 4900 50  0000 C CNN
F 1 "220" V 6034 4900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6080 4900 50  0001 C CNN
F 3 "~" H 6150 4900 50  0001 C CNN
	1    6150 4900
	0    1    1    0   
$EndComp
Text Label 5700 5500 0    50   ~ 0
GND
Wire Wire Line
	5700 5350 5700 5500
Wire Wire Line
	5700 4900 6000 4900
Wire Wire Line
	5700 5050 5700 4900
Connection ~ 5700 4900
Text Label 6300 4900 0    50   ~ 0
ENTER_BUTTON
Text Label 4600 4900 0    50   ~ 0
BACK_BUTTON
Connection ~ 4000 4900
Wire Wire Line
	4000 5050 4000 4900
Wire Wire Line
	4000 4900 4300 4900
Wire Wire Line
	4000 5350 4000 5500
Text Label 4000 5500 0    50   ~ 0
GND
$Comp
L Device:R R2
U 1 1 60D21225
P 4450 4900
F 0 "R2" V 4243 4900 50  0000 C CNN
F 1 "220" V 4334 4900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4380 4900 50  0001 C CNN
F 3 "~" H 4450 4900 50  0001 C CNN
	1    4450 4900
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 60D2121B
P 4000 5200
F 0 "R1" H 4070 5246 50  0000 L CNN
F 1 "100k" H 4070 5155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3930 5200 50  0001 C CNN
F 3 "~" H 4000 5200 50  0001 C CNN
	1    4000 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 4550 4000 4800
Text Label 4000 4550 0    50   ~ 0
3,3V
$Comp
L Connector:Conn_01x02_Male J2
U 1 1 60D2120F
P 3800 4800
F 0 "J2" H 3908 4981 50  0000 C CNN
F 1 "Conn_01x02_Male" H 3908 4890 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3800 4800 50  0001 C CNN
F 3 "~" H 3800 4800 50  0001 C CNN
	1    3800 4800
	1    0    0    -1  
$EndComp
Text Label 3450 1800 0    50   ~ 0
BUSY
Text Label 3450 1900 0    50   ~ 0
RST
Text Label 3450 2000 0    50   ~ 0
DC
Text Label 3450 2100 0    50   ~ 0
CS
Text Label 3450 2200 0    50   ~ 0
CLK
Text Label 3450 2300 0    50   ~ 0
DIN
Text Label 3450 2400 0    50   ~ 0
GND
Text Label 3450 2500 0    50   ~ 0
3,3V
Text Label 3450 2600 0    50   ~ 0
POTI
Text Label 3450 2700 0    50   ~ 0
SW
Text Label 3450 2800 0    50   ~ 0
VRx
Text Label 3450 2900 0    50   ~ 0
VRy
Text Label 3450 3000 0    50   ~ 0
BACK_BUTTON
Text Label 3450 3100 0    50   ~ 0
ENTER_BUTTON
$Comp
L User_Interface_Board-rescue:BHR-14-HUA J1
U 1 1 60D09066
P 3250 2800
F 0 "J1" V 4515 2692 50  0000 C CNN
F 1 "BHR-14-HUA" V 4424 2692 50  0000 C CNN
F 2 "User_Interface_Board:BHR-14-HUA" H 3250 2800 50  0001 C CNN
F 3 "" H 3250 2800 50  0001 C CNN
	1    3250 2800
	0    -1   -1   0   
$EndComp
Text Notes 3700 2300 0    50   ~ 0
OUTPUT ADAPTER
$EndSCHEMATC
