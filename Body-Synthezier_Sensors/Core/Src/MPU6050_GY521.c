

#include "MPU6050_GY521.h"



MPU6050_STATUS MPU6050_init(I2C_HandleTypeDef* __hi2c, MPU6050_Data* Sensor_Data_pointer, MPU6050_ACCL_RES accl_resolution, MPU6050_GYRO_RES gyro_resolution, uint8_t samplerate){

	uint8_t Data=0x00;
	MPU6050_hi2c = __hi2c;
	Sensor_Data = Sensor_Data_pointer;
	printf("MPU6050 init beginn\r\n");
	//Check if device is ready: Let LED blink 3 times if yes
	if((HAL_I2C_IsDeviceReady(MPU6050_hi2c, MPU6050_ADDR, 2, 20)) != HAL_OK){
		printf("MPU 6050 No Connection\r\n");
		return MPU6050_Status_Notconnected;

    }



	//check WHO_AM_I: If answer is I_AM toggle LED
	HAL_I2C_Mem_Read(MPU6050_hi2c, MPU6050_ADDR, MPU6050_WHO_AM_I_REG, 1, &Data, 1, 1000);

	if ((Data =! MPU6050_I_AM)) // if-statement is 1 if MPU is present
	{
		return MPU6050_Status_Invalid;
	}



	// wake sensor
	Data=0x00;
	if(HAL_I2C_Mem_Write(MPU6050_hi2c, MPU6050_ADDR, MPU6050_PWR_MGMT_1_REG, 1, &Data, 1, 1000)!=HAL_OK)
	{
		return MPU6050_Status_Invalid;
	}


	// Config range/resolution Gyroscope
	Data = 0xE0 | (gyro_resolution<<3);
	if(HAL_I2C_Mem_Write(MPU6050_hi2c, MPU6050_ADDR, MPU6050_GYRO_CONFIG_REG, 1, &Data, 1, 1000) != HAL_OK){
		return MPU6050_Status_Error;
	}
	//for normalization of Gyroscope range
	switch (gyro_resolution){
		case MPU6050_GYRO_250deg:
			Sensor_Data->Gyro_mult = MPU6050_GYRO_SENS_250;
			break;
		case MPU6050_GYRO_500deg:
			Sensor_Data->Gyro_mult = MPU6050_GYRO_SENS_500;
			break;
		case MPU6050_GYRO_1000deg:
			Sensor_Data->Gyro_mult = MPU6050_GYRO_SENS_1000;
			break;
		case MPU6050_GYRO_2000deg:
			Sensor_Data->Gyro_mult = MPU6050_GYRO_SENS_2000;
			break;
		}


	// Config range/resolution of Accelerometer
	Data = 0xE0 | (accl_resolution<<3);
	if(HAL_I2C_Mem_Write(MPU6050_hi2c, MPU6050_ADDR, MPU6050_ACCL_CONFIG_REG, 1, &Data, 1, 1000) != HAL_OK){
		return MPU6050_Status_Error;
	}

	switch(accl_resolution){
	case MPU6050_ACCL_2G:
		Sensor_Data->Accl_mult = MPU6050_ACCL_SENS_2;
			break;
	case MPU6050_ACCL_4G:
		Sensor_Data->Accl_mult = MPU6050_ACCL_SENS_4;
			break;
	case MPU6050_ACCL_8G:
		Sensor_Data->Accl_mult = MPU6050_ACCL_SENS_8;
			break;
	case MPU6050_ACCL_16G:
		Sensor_Data->Accl_mult = MPU6050_ACCL_SENS_16;
			break;
	}


	// Config Sample Rate: Sample Rate=8/(1+Data)
	Data=samplerate;
	if(HAL_I2C_Mem_Write(MPU6050_hi2c, MPU6050_ADDR, MPU6050_SMPLRT_DIV_REG, 1, &Data, 1, 1000) != HAL_OK){
		return MPU6050_Status_Error;
	}

	//Set Gyroscope offset to zero
	Sensor_Data->Gx_offset = 0;
	Sensor_Data->Gy_offset = 0;
	Sensor_Data->Gz_offset = 0;

	//Set Accelerometer offset to zero
	Sensor_Data->Ax_offset = 0;
	Sensor_Data->Ay_offset = 0;
	Sensor_Data->Az_offset = 0;

//	//Set User Controll, Enable FIFO
	Data = MPU6050_USR_CRTL_FIFO_EN;
	if(HAL_I2C_Mem_Write(MPU6050_hi2c, MPU6050_ADDR, MPU6050_USR_CRTL_REG, 1, &Data, 1, 1000) != HAL_OK){
		return MPU6050_Status_Error;
	}
	HAL_I2C_Mem_Read(MPU6050_hi2c, MPU6050_ADDR, MPU6050_USR_CRTL_REG, 1, &Data, 1, 1000);
	printf("MPU6050_USR_CRTL_REG: %i\r\n",Data);
// Interruppt Enable
	Data = MPU6050_INT_EN_DATA_RDY;
	if(HAL_I2C_Mem_Write(MPU6050_hi2c, MPU6050_ADDR,MPU6050_RA_INT_ENABLE, 1, &Data, 1, 1000) != HAL_OK){
		return MPU6050_Status_Error;
	}


	//determines which sensor measurements are loaded into the FIFO buffer
//	Data = MPU6050_FIFO_EN_ACCEL | MPU6050_FIFO_EN_ZG | MPU6050_FIFO_EN_YG | MPU6050_FIFO_EN_XG;
	Data = 0x00;
	if(HAL_I2C_Mem_Write(MPU6050_hi2c, MPU6050_ADDR, MPU6050_FIFO_DATA_REG, 1, &Data, 1, 1000) != HAL_OK){
		return MPU6050_Status_Error;
	}
	printf("MPU6050 init end\r\n");
	return MPU6050_Status_OK;
}




MPU6050_STATUS MPU6050_Read_Accl(){

	uint8_t Rec_Data[6];

	// Read 6Bytes (2byte per axis) starting from ACCL_XOUT_H register
	if(HAL_I2C_Mem_Read (MPU6050_hi2c, MPU6050_ADDR, MPU6050_ACCL_XOUT_H_REG, 1, Rec_Data, 6, 1000) != HAL_OK){
		return MPU6050_Status_Error;
	}

	// Data for all axis comes as 6Byte array, in the following it is filled into one 16-bit array for each axis
	Sensor_Data->Accl_X = (int16_t)(Rec_Data[0]<<8 | Rec_Data[1]) - Sensor_Data->Ax_offset;
	Sensor_Data->Accl_Y = (int16_t)(Rec_Data[2]<<8 | Rec_Data[3]) - Sensor_Data->Ay_offset;
	Sensor_Data->Accl_Z = (int16_t)(Rec_Data[4]<<8 | Rec_Data[5]) - Sensor_Data->Az_offset;

	return MPU6050_Read_OK;
}


MPU6050_STATUS MPU6050_Read_Gyro(){

	uint8_t Rec_Data[6];

	// Read 6Bytes (2byte per axis) starting from GYRO_XOUT_H register
	if(HAL_I2C_Mem_Read ( MPU6050_hi2c, MPU6050_ADDR, MPU6050_GYRO_XOUT_H_REG, 1, Rec_Data, 6, 1000) != HAL_OK){
		return MPU6050_Status_Error;
	}

	// Get time of new Measurement and safe time of last measurement
	Sensor_Data->Gyro_time	=	DWT->CYCCNT;
	DWT->CYCCNT				=	0;

	// Data for all axis comes as 6Byte array, in the following it is filled into one 16-bit array for each axis
	Sensor_Data->Gyro_X = (int16_t)(Rec_Data[0]<<8 | Rec_Data[1])-Sensor_Data->Gx_offset;
	Sensor_Data->Gyro_Y = (int16_t)(Rec_Data[2]<<8 | Rec_Data[3])-Sensor_Data->Gy_offset;
	Sensor_Data->Gyro_Z = (int16_t)(Rec_Data[4]<<8 | Rec_Data[5])-Sensor_Data->Gz_offset;


	return MPU6050_Read_OK;
}

MPU6050_STATUS MPU6050_Read_Sensor(){

	uint8_t Rec_Data[14];

		// Read 6Bytes (2byte per axis) starting from ACCL_XOUT_H register
		if (HAL_I2C_Mem_Read (MPU6050_hi2c, MPU6050_ADDR, MPU6050_ACCL_XOUT_H_REG, 1, Rec_Data, 14, 1000) != HAL_OK ){
			return MPU6050_Status_Error;
		}
		// Get time of new Measurement and safe time of last measurement
		Sensor_Data->Gyro_time	=	DWT->CYCCNT;
		DWT->CYCCNT				=	0;
		// Data for all axis comes as 6Byte array, in the following it is filled into one 16-bit array for each axis
		Sensor_Data->Accl_X = (int16_t)(Rec_Data[0]<<8 | Rec_Data[1]) - Sensor_Data->Ax_offset;
		Sensor_Data->Accl_Y = (int16_t)(Rec_Data[2]<<8 | Rec_Data[3]) - Sensor_Data->Ay_offset;
		Sensor_Data->Accl_Z = (int16_t)(Rec_Data[4]<<8 | Rec_Data[5]) - Sensor_Data->Az_offset;
		// Data for all axis comes as 6Byte array, in the following it is filled into one 16-bit array for each axis
		Sensor_Data->Gyro_X = (int16_t)(Rec_Data[8]<<8 | Rec_Data[9]) - Sensor_Data->Gx_offset;
		Sensor_Data->Gyro_Y = (int16_t)(Rec_Data[10]<<8 | Rec_Data[11]) - Sensor_Data->Gy_offset;
		Sensor_Data->Gyro_Z = (int16_t)(Rec_Data[12]<<8 | Rec_Data[13]) - Sensor_Data->Gz_offset;

		return MPU6050_Read_OK;
}


MPU6050_STATUS MPU6050_Calculate_Mean(){
	// Temp memory to sum up values for mean calculation
	// Gyroscope
	int32_t Gx_mean_tempbuffer	=	0;
	int32_t Gy_mean_tempbuffer	=	0;
	int32_t Gz_mean_tempbuffer	=	0;
	// Accelerometer
	int32_t Ax_mean_tempbuffer	=	0;
	int32_t Ay_mean_tempbuffer	=	0;
	int32_t Az_mean_tempbuffer	=	0;
	// First measurements have to be skipped
	int n_skipping		=	100;
	int n_measurements 	=	500;
//	int n_skipping		=	10;
//	int n_measurements 	=	100;
	for (int i=n_skipping; i < n_measurements + n_skipping; i++){
		// Read Data

		// from Gyroscope
		if (MPU6050_Read_Sensor(Sensor_Data) != MPU6050_Read_OK){
			return MPU6050_Status_Error;
		}
		int16_t Gx = Sensor_Data	->	Gyro_X;
		int16_t Gy = Sensor_Data	->	Gyro_Y;
		int16_t Gz = Sensor_Data	->	Gyro_Z;
		// from Accelerometer
		if (MPU6050_Read_Accl(Sensor_Data) != MPU6050_Read_OK){
			return MPU6050_Status_Error;
		}
		int16_t Ax = Sensor_Data	->	Accl_X;
		int16_t Ay = Sensor_Data	->	Accl_Y;
		int16_t Az = Sensor_Data	->	Accl_Z;
		// sum it up
		Gx_mean_tempbuffer	+=	Gx;
		Gy_mean_tempbuffer	+=	Gy;
		Gz_mean_tempbuffer	+=	Gz;
		Ax_mean_tempbuffer	+=	Ax;
		Ay_mean_tempbuffer	+=	Ay;
		Az_mean_tempbuffer	+=	Az;
		// Wait to prevent double measurements
		HAL_Delay(2);
	}

	//Save offset to Sensor_Data
	//Gyroscope offset
	Sensor_Data->Gx_mean=Gx_mean_tempbuffer/n_measurements;
	Sensor_Data->Gy_mean=Gy_mean_tempbuffer/n_measurements;
	Sensor_Data->Gz_mean=Gz_mean_tempbuffer/n_measurements;
	//Accelerometer offset
	Sensor_Data->Ax_mean=Ax_mean_tempbuffer/n_measurements;
	Sensor_Data->Ay_mean=Ay_mean_tempbuffer/n_measurements;
	Sensor_Data->Az_mean=Az_mean_tempbuffer/n_measurements;

	return MPU6050_Read_OK;
}

MPU6050_STATUS MPU6050_Calibrate(){

	// gravitational constant depending on accelerometer resolution
	int16_t gravitation	= (int16_t)((float)1 / Sensor_Data -> Accl_mult);
	// allowed deviation from mean for raw data from sensors
	int8_t	gyro_tolerance  = 1;
	int8_t	accl_tolerance  = 5;

	// Set offset Initially (offset is subtracted from future measurements)
	Sensor_Data -> Gx_offset		=	Sensor_Data -> Gx_mean;
	Sensor_Data -> Gy_offset		=	Sensor_Data -> Gy_mean;
	Sensor_Data -> Gz_offset		=	Sensor_Data -> Gz_mean;
	Sensor_Data -> Ax_offset		=	Sensor_Data -> Ax_mean;
	Sensor_Data -> Ay_offset		=	Sensor_Data -> Ay_mean;
	Sensor_Data -> Az_offset		=	(Sensor_Data -> Az_mean) + gravitation;

	// Indicator for correct calibration of all axis
	int calibrated = 0;
	while(calibrated <= 6){
	printf("%i\n\r",calibrated );
	// Calculate means of sensors
		if (MPU6050_Calculate_Mean(Sensor_Data)!= MPU6050_Read_OK){
			return MPU6050_Status_Error;
		}
	// Validate or Update Calibration
	// Gyroscope X Y Z
	if (abs(Sensor_Data -> Gx_mean)<gyro_tolerance) calibrated++;
	else Sensor_Data -> Gx_offset		=	(Sensor_Data -> Gx_offset)	+	(Sensor_Data -> Gx_mean);

	if (abs(Sensor_Data -> Gy_mean)<gyro_tolerance) calibrated++;
	else Sensor_Data -> Gy_offset		=	(Sensor_Data -> Gy_offset)	+	(Sensor_Data -> Gy_mean);

	if (abs(Sensor_Data -> Gz_mean)<gyro_tolerance) calibrated++;
	else Sensor_Data -> Gz_offset		=	(Sensor_Data -> Gz_offset)	+	(Sensor_Data -> Gz_mean);
	// Accelerometer X Y Z
	if (abs(Sensor_Data -> Ax_mean)<accl_tolerance) calibrated++;
	else Sensor_Data -> Ax_offset		=	(Sensor_Data -> Ax_offset)	+	(Sensor_Data -> Ax_mean);

	if (abs(Sensor_Data -> Ay_mean)<accl_tolerance) calibrated++;
	else Sensor_Data -> Ay_offset		=	(Sensor_Data -> Ay_offset)	+	(Sensor_Data -> Ay_mean);

	if ((abs((Sensor_Data -> Az_mean) - gravitation)) <accl_tolerance) calibrated++;
	else Sensor_Data -> Az_offset		=	(Sensor_Data -> Az_offset)	+	((Sensor_Data -> Az_mean) - gravitation);

	}
	return MPU6050_Read_OK;
}

void getAcclFilt(){

}

void getGyroRoll(){

	// time of measurement for integration
	float cycletime = 80000000;

	// Get Roll
	// RAW Gyrodata: Gyro_X; transformation to Deg/s: Gyro_mult; time since last measurement: Gyro_time; cycletime per second: cycletime
	Sensor_Data -> Gx_deg =  (float)( ((Sensor_Data -> Gyro_X) * Sensor_Data -> Gyro_mult ) * (Sensor_Data -> Gyro_time)) / cycletime;
	Sensor_Data -> Gy_deg =  (float)( ((Sensor_Data -> Gyro_Y) * Sensor_Data -> Gyro_mult ) * (Sensor_Data -> Gyro_time)) / cycletime;
	Sensor_Data -> Gz_deg =  (float)( ((Sensor_Data -> Gyro_Z) * Sensor_Data -> Gyro_mult ) * (Sensor_Data -> Gyro_time)) / cycletime;

	// Take into account that +-360 degrees is the same as 0 degrees
	if (Sensor_Data -> Gx_deg >=180) Sensor_Data -> Gx_deg = Sensor_Data -> Gx_deg - 360;
	if (Sensor_Data -> Gx_deg <=-180) Sensor_Data -> Gx_deg = Sensor_Data -> Gx_deg + 360;

	if (Sensor_Data -> Gy_deg >=180) Sensor_Data -> Gy_deg = Sensor_Data -> Gy_deg - 360;
	if (Sensor_Data -> Gy_deg <=-180) Sensor_Data -> Gy_deg = Sensor_Data -> Gy_deg + 360;

	if (Sensor_Data -> Gy_deg >=180) Sensor_Data -> Gz_deg = Sensor_Data -> Gz_deg - 360;
	if (Sensor_Data -> Gy_deg <=-180) Sensor_Data -> Gz_deg = Sensor_Data -> Gz_deg + 360;
}


void getAcclRoll(){

	//Parameter for stability in Regions where X and Z or Y and Z are near zero
	int16_t mu = 0.01;


	int16_t X = Sensor_Data -> Accl_X;
	int16_t Y = Sensor_Data -> Accl_Y;
	int16_t Z = Sensor_Data -> Accl_Z;

	// parameter for correct orientation
	int16_t 	sign;
	if (Z>0)	sign = 1;
	else 		sign = -1;

	//77transform radians to degree
	float RAD_TO_DEG = 180/M_PI;

	// Get Roll
	// RAW Gyrodata: Gyro_X; transformation to Deg/s: Gyro_mult; time since last measurement: Gyro_time; cycletime per second: cycletime
	Sensor_Data -> Ax_deg = atan2( Y ,   sign * sqrt(Z*Z+ mu*X*X)) * RAD_TO_DEG;
	Sensor_Data -> Ay_deg = atan2(-X, sqrt(Y*Y + Z*Z)) * RAD_TO_DEG;

}


/* 3D-Rotation around x-,y- and z-Axis
 *
 */
void getAngleRoll(){

	MPU6050_Read_Sensor(Sensor_Data);
	getAcclRoll(Sensor_Data);
	getGyroRoll(Sensor_Data);

	float X = Sensor_Data -> X_deg;
	float Y = Sensor_Data -> Y_deg;

	Sensor_Data -> X_deg =  0.98 * (X + Sensor_Data -> Gx_deg) + (0.02 * (Sensor_Data -> Ax_deg));
	Sensor_Data -> Y_deg =  0.98 * (Y + Sensor_Data -> Gy_deg) + (0.02 * (Sensor_Data -> Ay_deg));
	Sensor_Data -> Z_deg = Sensor_Data -> Z_deg + Sensor_Data -> Gz_deg;
}


void MPU6050_Display_Data(){
//	uint8_t buffer[1024];
	MPU6050_Read_Sensor(Sensor_Data);
	printf("Gx: %i\r\n", Sensor_Data->Gyro_X);//+(buffer[5]<<8)+(buffer[6]<<16)+(buffer[7]<<24));
	printf("Gy: %i\r\n", Sensor_Data->Gyro_Y);
	printf("Gz: %i\r\n", Sensor_Data->Gyro_Z);
	printf("Ax: %i\r\n", Sensor_Data->Accl_X);
	printf("Ay: %i\r\n", Sensor_Data->Accl_Y);
	printf("Az: %i\r\n", Sensor_Data->Accl_Z);

//	printf("Gx: %i		**Gy: %i		**Gz: %i\r\n",Sensor_Data->Gyro_X ,Sensor_Data->Gyro_Y ,Sensor_Data->Gyro_Z);
//	printf("Ax: %i		**Ay: %i		**Az: %i\r\n", Sensor_Data->Accl_X,Sensor_Data->Accl_Y, Sensor_Data->Accl_Z);
}


/** DMP functions
 */
uint8_t MPU6050_GetIntReg(void){
	uint8_t retval = 0;
	HAL_I2C_Mem_Read(MPU6050_hi2c, MPU6050_ADDR, MPU6050_INT_STATUS_REG, 1, &retval, 1,100);
	return retval;
}
uint8_t MPU6050_GetDMPIntReg(void){
	uint8_t retval = 0;
	HAL_I2C_Mem_Read(MPU6050_hi2c, MPU6050_ADDR,MPU6050_RA_DMP_INT_STATUS ,  1, &retval, 1,100);
	return retval;
}

uint16_t MPU6050_Read_FIFOcount(void){

	uint8_t retval[2];
	HAL_I2C_Mem_Read (MPU6050_hi2c, MPU6050_ADDR, MPU6050_FIFO_COUNT_H_REG, 1, &retval[1],1, 1000) ;
	HAL_I2C_Mem_Read (MPU6050_hi2c, MPU6050_ADDR, MPU6050_FIFO_COUNT_L_REG, 1, &retval[0],1, 1000) ;
	printf("%i,\r\n",retval[0]);
	printf("%i,\r\n",retval[1]);
	return (retval[0]<<8) + retval[1];


}

/**Gets the Data out of the FIFO-Buffer, Data inside the FIFO depends on the FIFO_EN Register set in the Init
 *
 */
void MPU6050_GetFiFoData(uint8_t buffer[1024]){
	if ((MPU6050_GetIntReg() & 0x01) == MPU6050_INT_DATA_RDY){
		uint16_t count =  MPU6050_Read_FIFOcount();
		// for (int fifo_counter  = 0; fifo_counter < count; fifo_counter++){
			HAL_I2C_Mem_Read(MPU6050_hi2c, MPU6050_ADDR, MPU6050_FIFO_DATA_REG, 1024, buffer, 1,100);
		// }
	}
}

void MPU6050_FIFO_RESET(){
	uint8_t buffer;
	HAL_I2C_Mem_Read(MPU6050_hi2c,MPU6050_ADDR, MPU6050_USR_CRTL_REG, 1,&buffer , 1,100);
	printf("%i\r\n", buffer);
	buffer = MPU6050_USR_CRTL_FIFO_EN | MPU6050_USR_CRTL_FIFO_RESET;

	HAL_I2C_Mem_Write(MPU6050_hi2c,MPU6050_ADDR, MPU6050_USR_CRTL_REG, 1,&buffer,1,100);
	HAL_I2C_Mem_Read(MPU6050_hi2c,MPU6050_ADDR, MPU6050_USR_CRTL_REG, 1,&buffer , 1,100);
	printf("%i\r\n", buffer);
}
void MPU6050_Display_Data_DMP(){
	uint8_t buffer[1024];
	MPU6050_GetFiFoData(buffer);
//	printf("w: %i\r\n", buffer[0]);//+(buffer[1]<<8)+(buffer[2]<<16)+(buffer[3]<<24));
//	printf("Gx: %i\r\n", buffer[4]);//+(buffer[5]<<8)+(buffer[6]<<16)+(buffer[7]<<24));
//	printf("Gy: %i\r\n", buffer[8]);//+(buffer[9]<<8)+(buffer[10]<<16)+(buffer[12]<<24));
//	printf("Gz: %i\r\n", buffer[12]);//+(buffer[9]<<8)+(buffer[10]<<16)+(buffer[12]<<24));
//	printf("Ax: %i\r\n", buffer[4]);//+(buffer[5]<<8)+(buffer[6]<<16)+(buffer[7]<<24));
//	printf("Ay: %i\r\n", buffer[8]);//+(buffer[9]<<8)+(buffer[10]<<16)+(buffer[12]<<24));
//	printf("Az: %i\r\n", buffer[12]);//+(buffer[9]<<8)+(buffer[10]<<16)+(buffer[12]<<24));
	printf("Gx: %i ** Gy: %i ** Gz: %i\r\n",buffer[4] ,buffer[8], buffer[12]);
	printf("Az: %i ** Ay: %i ** Az: %i\r\n", buffer[4],buffer[8],buffer[12]);

}

//float getAbsMax(float a, float b , float c){
//	float tmp1,tmp2,tmp3;
//	a_abs = abs(a);
//	b_abs = abs(b);
//	c_abs = abs(c);
//	if(a_abs < b_abs){
//		if(b_abs < c_abs){
//			return c;
//		}
//		else return b;
//	}
//
//	else if(a_abs < c_abs){
//			return c;
//		}
//
//	else return a;
//}

tilt_direction_t MPU6050_detectTilt(){
	//tilt Thresholds, right, left , front
	int16_t tilt_TH_X_r,tilt_TH_X_l,  tilt_TH_Y, tilt_TH_Y_f,tilt_TH_Y_b, tilt_TH_Z;
	tilt_TH_X_r = -2000;
	tilt_TH_X_l = 2000;
	tilt_TH_Y   = 1500;
	tilt_TH_Y_f = -2500;
	tilt_TH_Y_b = 2500;
	tilt_TH_Z   = 3800;
	float angle_TH = 25.0;

	getAngleRoll(Sensor_Data);
	float alpha = sqrtf(Sensor_Data->X_deg*Sensor_Data->X_deg + Sensor_Data->Y_deg* Sensor_Data->Y_deg);
	if ((alpha > angle_TH) &&  (abs(Sensor_Data->Accl_Z) < tilt_TH_Z)){
		if (abs(Sensor_Data->Accl_Y) < tilt_TH_Y){
			if (Sensor_Data->Accl_X < tilt_TH_X_r){
				printf("tilt right \r\n");
				return TILT_RIGHT;
			}
			else if ((Sensor_Data->Accl_X > tilt_TH_X_l) && abs(Sensor_Data->Accl_Y)){
				printf("tilt left\r\n");
				return TILT_LEFT;
			}
		}
		else if (Sensor_Data->Accl_Y < tilt_TH_Y_f){
			printf("tilt front\r\n");
			return TILT_FRONT;
		}
		else if (Sensor_Data->Accl_Y > tilt_TH_Y_b){
			printf("tilt back\r\n");
			return TILT_BACK;
		}
	}
	return TILT_NONE;
}
	//Get maximum
//	if(maxArray[i] <= maxArray[1]){
//		i = 1;
//	}
//	if(maxArray[i] <= maxArray[2]){
//		i = 2;
//	}
//	if(degArray[i] < 0){
//		return -(i+1);
//	}
//	else return i+1;
//	float Max = getAbsMax();

//uint8_t MPU6050_detectUp(){
//
//}


