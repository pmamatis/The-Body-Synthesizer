/**
 * @file MPU6050_GY521.c
 * @author  Paul Mamatis
 * @brief software driver for MPU6050 in combination with a STM32 
 * @version 0.1
 * @date  Okt 10, 2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "MPU6050_GY521.h"


/**
 * @brief Init for the MPU6050
 * 
 * @param __hi2c i2c handler 
 * @param Sensor_Data_pointer struct to save the data
 * @param accl_resolution 
 * @param gyro_resolution 
 * @param samplerate 
 * @return MPU6050_STATUS 
 */
MPU6050_STATUS MPU6050_init(I2C_HandleTypeDef* __hi2c, MPU6050_Data* Sensor_Data_pointer, MPU6050_ACCL_RES accl_resolution, MPU6050_GYRO_RES gyro_resolution, uint8_t samplerate){

	uint8_t Data=0x00;
	MPU6050_hi2c = __hi2c;
	Sensor_Data = Sensor_Data_pointer;
	printf("MPU6050 init begin\r\n");
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
	//	printf("MPU6050_USR_CRTL_REG: %i\r\n",Data);
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



/**
 * @brief reeads only accl data
 * 
 * @return MPU6050_STATUS 
 */
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

/**
 * @brief reads only gyro data
 * 
 * @return MPU6050_STATUS 
 */
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

/**
 * @brief Reads raw data from accl and gyro  
 * 
 * @return MPU6050_STATUS 
 */
MPU6050_STATUS MPU6050_Read_Sensor(){

	uint8_t Rec_Data[14];

	// Read 6Bytes (2byte per axis) starting from ACCL_XOUT_H register
	if (HAL_I2C_Mem_Read (MPU6050_hi2c, MPU6050_ADDR, MPU6050_ACCL_XOUT_H_REG, 1, Rec_Data, 14, 1000) != HAL_OK ){
		return MPU6050_Status_Error;
		printf("READ ERROR\r\n");
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

/**
 * @brief Gets the mean value of the gyro and accl over n_measurements
 * @note this function is in first order a helper function for the calibration process
 * 
 * @return MPU6050_STATUS 
 */
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
/**
 * @brief Calibrates the MPU6050 and sets the offsets, which needed to be subtracted from the Rawdata to get valid information
 * 
 * @return MPU6050_STATUS 
 */
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

/**
 * @brief Get the Roll with gyro-data
 * @note MPU6050_Read_Sensor or MPU6050_Read_Gyro must be called before
 */
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

/**
 * @brief Get the roll with accl-data  
 * @note MPU6050_Read_Sensor or MPU6050_Read_Accl must be called before 
 */
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

	//transform radians to degree
	float RAD_TO_DEG = 180/M_PI;

	// Get Roll
	Sensor_Data -> Ax_deg = atan2( Y ,   sign * sqrt(Z*Z+ mu*X*X)) * RAD_TO_DEG;
	Sensor_Data -> Ay_deg = atan2(-X, sqrt(Y*Y + Z*Z)) * RAD_TO_DEG;

}


/* @brief 3D-Rotation around x-,y- and z-Axis
 *
 */
void getAngleRoll(){

//	MPU6050_Read_Sensor(Sensor_Data);
	getAcclRoll(Sensor_Data);
	getGyroRoll(Sensor_Data);

	float X = Sensor_Data -> X_deg;
	float Y = Sensor_Data -> Y_deg;
	//komplement??r FIlter
	Sensor_Data -> X_deg =  0.98 * (X + Sensor_Data -> Gx_deg) + (0.02 * (Sensor_Data -> Ax_deg));
	Sensor_Data -> Y_deg =  0.98 * (Y + Sensor_Data -> Gy_deg) + (0.02 * (Sensor_Data -> Ay_deg)); 
	float X = Sensor_Data -> X_deg;
	float Y = Sensor_Data -> Y_deg;-> Gy_deg) + (0.02 * (Sensor_Data -> Ay_deg));
	Sensor_Data -> Z_deg = Sensor_Data -> Z_deg + Sensor_Data -> Gz_deg;
}

/**
 * @brief Displays all Gyro and Accl Axis
 * 
 */
void MPU6050_Display_Data(){
	//	uint8_t buffer[1024];
	MPU6050_Read_Sensor(Sensor_Data);
	printf("Gx: %i\r\n", Sensor_Data->Gyro_X);//+(buffer[5]<<8)+(buffer[6]<<16)+(buffer[7]<<24));
	printf("Gy: %i\r\n", Sensor_Data->Gyro_Y);
	printf("Gz: %i\r\n", Sensor_Data->Gyro_Z);
	printf("Ax: %i\r\n", Sensor_Data->Accl_X);
	printf("Ay: %i\r\n", Sensor_Data->Accl_Y);
	printf("Az: %i\r\n", Sensor_Data->Accl_Z);

}


/**
 * @brief detects the tilt of the Sensor in relation to the calibrated starting stance
 * 
 * @return tilt_direction_t 
 */
tilt_direction_t MPU6050_detectTilt(){
	//tilt Thresholds, right, left , front
	int16_t tilt_TH_X_r,tilt_TH_X_l,  tilt_TH_Y, tilt_TH_Y_f,tilt_TH_Y_b, tilt_TH_Z;
	int16_t tilt_TH_X_r_s, tilt_TH_X_l_s,  tilt_TH_Y_f_s, tilt_TH_Y_b_s;
	//slow tilt
	tilt_TH_X_r = -1500;
	tilt_TH_X_l = 1500;
	tilt_TH_Y   = 1500;
	tilt_TH_Y_f = -1500;
	tilt_TH_Y_b = 1500;
	tilt_TH_Z   = 3800;
	float angle_TH = 25.0;
	//strong tilt
	tilt_TH_X_r_s = -2500;
	tilt_TH_X_l_s = 2500;
	tilt_TH_Y_f_s = -3000;
	tilt_TH_Y_b_s = 3000;

	getAngleRoll(Sensor_Data);
	float alpha = sqrtf(Sensor_Data->X_deg*Sensor_Data->X_deg + Sensor_Data->Y_deg* Sensor_Data->Y_deg);
	//detect tilt in any diretion
	if ((alpha > angle_TH) &&  (abs(Sensor_Data->Accl_Z) < tilt_TH_Z)){
		//speciify direction
		if (abs(Sensor_Data->Accl_Y) < tilt_TH_Y){
			//tilt rigth when Accl_X is negative
			if (Sensor_Data->Accl_X < tilt_TH_X_r){
				//
				if (Sensor_Data->Accl_X < tilt_TH_X_r_s){
					//printf("tilt strong right \r\n");
					return TILT_RIGHT_S;
				}
				else {
					//printf("tilt right \r\n");
					return TILT_RIGHT;
				}

			}
			//tilt left when Accl_X is positiv
			else if ((Sensor_Data->Accl_X > tilt_TH_X_l) && abs(Sensor_Data->Accl_Y)){

				if (Sensor_Data->Accl_X > tilt_TH_X_l_s){
										//printf("tilt strong left\r\n");
					return TILT_LEFT_S;
				}
				else {
										//printf("tilt left\r\n");
					return TILT_LEFT;
				}
			}
		}
		else if (Sensor_Data->Accl_Y < tilt_TH_Y_f){
			if (Sensor_Data->Accl_Y < tilt_TH_Y_f_s){
								//printf("tilt strong front\r\n");
				return TILT_FRONT_S;
			}
			else{
								//printf("tilt front\r\n");
				return TILT_FRONT;
			}

		}
		else if (Sensor_Data->Accl_Y > tilt_TH_Y_b){
			if (Sensor_Data->Accl_Y > tilt_TH_Y_b_s){
								//printf("tilt strong back\r\n");
				return TILT_BACK_S;
			}
			else {
								//printf("tilt back\r\n");
				return TILT_BACK;
			}

		}
	}
	return TILT_NONE;
}



