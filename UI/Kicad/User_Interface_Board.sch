EESchema Schematic File Version 4
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
L Device:R R1
U 1 1 5E233E59
P 7550 2350
F 0 "R1" H 7620 2396 50  0000 L CNN
F 1 "10k" H 7620 2305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7480 2350 50  0001 C CNN
F 3 "~" H 7550 2350 50  0001 C CNN
	1    7550 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 2500 7550 2550
Text Label 7550 2200 0    50   ~ 0
+3,3V
Text Label 6650 2550 0    50   ~ 0
Button1
Text Label 7550 2650 0    50   ~ 0
GND
$Comp
L power:GND #PWR01
U 1 1 5E2349BA
P 5200 4600
F 0 "#PWR01" H 5200 4350 50  0001 C CNN
F 1 "GND" H 5205 4427 50  0000 C CNN
F 2 "" H 5200 4600 50  0001 C CNN
F 3 "" H 5200 4600 50  0001 C CNN
	1    5200 4600
	1    0    0    -1  
$EndComp
Text Label 5200 4600 0    50   ~ 0
GND
Wire Wire Line
	6050 2550 7550 2550
Wire Wire Line
	6050 2750 7850 2750
$Comp
L Device:R R2
U 1 1 5E240B5C
P 7850 2350
F 0 "R2" H 7920 2396 50  0000 L CNN
F 1 "10k" H 7920 2305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7780 2350 50  0001 C CNN
F 3 "~" H 7850 2350 50  0001 C CNN
	1    7850 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 2500 7850 2750
Text Label 7850 2200 0    50   ~ 0
+3,3V
Text Label 7550 2850 0    50   ~ 0
GND
Text Label 6650 2750 0    50   ~ 0
Button2
Wire Wire Line
	6050 2950 8150 2950
Wire Wire Line
	8150 2950 8150 2500
$Comp
L Device:R R3
U 1 1 5E241CC4
P 8150 2350
F 0 "R3" H 8220 2396 50  0000 L CNN
F 1 "10k" H 8220 2305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 8080 2350 50  0001 C CNN
F 3 "~" H 8150 2350 50  0001 C CNN
	1    8150 2350
	1    0    0    -1  
$EndComp
Text Label 8150 2200 0    50   ~ 0
+3,3V
Text Label 7550 3050 0    50   ~ 0
GND
Text Label 6650 2950 0    50   ~ 0
Button3
Wire Wire Line
	6050 3150 8450 3150
$Comp
L Device:R R4
U 1 1 5E2428E5
P 8450 2350
F 0 "R4" H 8520 2396 50  0000 L CNN
F 1 "10k" H 8520 2305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 8380 2350 50  0001 C CNN
F 3 "~" H 8450 2350 50  0001 C CNN
	1    8450 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 2500 8450 3150
Text Label 8450 2200 0    50   ~ 0
+3,3V
Text Label 7550 3250 0    50   ~ 0
GND
Text Label 6650 3150 0    50   ~ 0
Button4
$Comp
L User_Interface_Board-rescue:BHR-16-HUA-SelfdefinedParts J1
U 1 1 5E26D484
P 4450 3950
F 0 "J1" V 5915 3842 50  0000 C CNN
F 1 "BHR-16-HUA" V 5824 3842 50  0000 C CNN
F 2 "User_Interface_Board:BHR-16-HUA" H 4450 3950 50  0001 C CNN
F 3 "" H 4450 3950 50  0001 C CNN
	1    4450 3950
	0    -1   -1   0   
$EndComp
Text Label 4650 2750 0    50   ~ 0
+3,3V
Text Label 4650 2950 0    50   ~ 0
Busy
Text Label 4650 3050 0    50   ~ 0
RST
Text Label 4650 3150 0    50   ~ 0
DC
Text Label 4650 3250 0    50   ~ 0
CS
Text Label 4650 3350 0    50   ~ 0
CLK
Text Label 4650 3450 0    50   ~ 0
DIN
Text Label 4650 3650 0    50   ~ 0
SW
Text Label 4650 3750 0    50   ~ 0
GND
Text Label 4650 3850 0    50   ~ 0
Button1
Text Label 4650 3950 0    50   ~ 0
Button2
Text Label 4650 4050 0    50   ~ 0
Button3
Text Label 4650 4150 0    50   ~ 0
Button4
$Comp
L Connector:Conn_01x02_Male J2
U 1 1 5E271F18
P 5850 2550
F 0 "J2" H 5958 2731 50  0000 C CNN
F 1 "Conn_01x02_Male" H 5958 2640 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5850 2550 50  0001 C CNN
F 3 "~" H 5850 2550 50  0001 C CNN
	1    5850 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 2650 6050 2650
$Comp
L Connector:Conn_01x02_Male J3
U 1 1 5E27325A
P 5850 2750
F 0 "J3" H 5958 2931 50  0000 C CNN
F 1 "Conn_01x02_Male" H 5958 2840 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5850 2750 50  0001 C CNN
F 3 "~" H 5850 2750 50  0001 C CNN
	1    5850 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 2850 6050 2850
$Comp
L Connector:Conn_01x02_Male J4
U 1 1 5E274252
P 5850 2950
F 0 "J4" H 5958 3131 50  0000 C CNN
F 1 "Conn_01x02_Male" H 5958 3040 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5850 2950 50  0001 C CNN
F 3 "~" H 5850 2950 50  0001 C CNN
	1    5850 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 3050 6050 3050
$Comp
L Connector:Conn_01x02_Male J5
U 1 1 5E275067
P 5850 3150
F 0 "J5" H 5958 3331 50  0000 C CNN
F 1 "Conn_01x02_Male" H 5958 3240 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5850 3150 50  0001 C CNN
F 3 "~" H 5850 3150 50  0001 C CNN
	1    5850 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 3250 6050 3250
Text Label 6050 3750 0    50   ~ 0
Busy
Text Label 6050 3850 0    50   ~ 0
RST
Text Label 6050 3950 0    50   ~ 0
DC
Text Label 6050 4050 0    50   ~ 0
CS
Text Label 6050 4150 0    50   ~ 0
CLK
Text Label 6050 4250 0    50   ~ 0
DIN
Text Label 6050 4900 0    50   ~ 0
X
Text Label 6050 5000 0    50   ~ 0
Y
Text Label 6050 5100 0    50   ~ 0
GND
$Comp
L Connector:Conn_01x08_Male J6
U 1 1 5E3013BB
P 5850 4050
F 0 "J6" H 5958 4531 50  0000 C CNN
F 1 "Conn_01x08_Male" H 5958 4440 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 5850 4050 50  0001 C CNN
F 3 "~" H 5850 4050 50  0001 C CNN
	1    5850 4050
	1    0    0    -1  
$EndComp
Text Label 6050 4350 0    50   ~ 0
GND
Text Label 6050 4450 0    50   ~ 0
+3,3V
$Comp
L Connector:Conn_01x05_Male J7
U 1 1 5E305AD6
P 5850 4900
F 0 "J7" H 5958 5281 50  0000 C CNN
F 1 "Conn_01x05_Male" H 5958 5190 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 5850 4900 50  0001 C CNN
F 3 "~" H 5850 4900 50  0001 C CNN
	1    5850 4900
	1    0    0    -1  
$EndComp
Text Label 6050 4700 0    50   ~ 0
+3,3V
Text Label 6050 4800 0    50   ~ 0
SW
$Comp
L Connector:Conn_01x03_Male J8
U 1 1 5E4ABD04
P 7300 4150
F 0 "J8" H 7408 4431 50  0000 C CNN
F 1 "Conn_01x03_Male" H 7408 4340 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7300 4150 50  0001 C CNN
F 3 "~" H 7300 4150 50  0001 C CNN
	1    7300 4150
	1    0    0    -1  
$EndComp
Text Label 7500 4050 0    50   ~ 0
+3,3V
Text Label 7500 4250 0    50   ~ 0
GND
Text Label 7500 4150 0    50   ~ 0
Poti
Text Label 4650 4250 0    50   ~ 0
Poti
Text Label 4650 2850 0    50   ~ 0
Y
Text Label 4650 3550 0    50   ~ 0
X
$Comp
L Device:R C1
U 1 1 5E6CA5EA
P 3550 3050
F 0 "C1" H 3620 3096 50  0000 L CNN
F 1 "1u" H 3620 3005 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3480 3050 50  0001 C CNN
F 3 "~" H 3550 3050 50  0001 C CNN
	1    3550 3050
	1    0    0    -1  
$EndComp
Text Label 3550 2900 0    50   ~ 0
+3,3V
Text Label 3550 3200 0    50   ~ 0
GND
$EndSCHEMATC
