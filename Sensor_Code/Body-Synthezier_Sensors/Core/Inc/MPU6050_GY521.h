/**
 * @file MPU6050_GY521.h
 * @author Paul Mamatis
 * @brief Software driver for the MPU6050 in combination with a STM32
 * @version 1.0
 * @date  Okt 10, 2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */


#ifndef INC_MPU6050_GY521_H_
#define INC_MPU6050_GY521_H_

/**
 * @defgroup MPU6050 MPU6050 Software driver
 * @ingroup SensorSTM
 * @brief Software driver for the MPU6050 Sensor
 * @{
 */

#include "stdlib.h"
#include "math.h"
#include "main.h"
#include <stdbool.h>

#define MPU6050_ADDR 0xD0

/** @brief Define I2C Register Addresses */

#define MPU6050_SMPLRT_DIV_REG 0x19
#define MPU6050_GYRO_CONFIG_REG 0x1B
#define MPU6050_ACCL_CONFIG_REG 0x1C
#define MPU6050_ACCL_XOUT_H_REG 0x3B
#define MPU6050_TEMP_OUT_H_REG 0x41
#define MPU6050_GYRO_XOUT_H_REG 0x43
#define MPU6050_PWR_MGMT_1_REG 0x6B
#define MPU6050_WHO_AM_I_REG 0x75
#define MPU6050_INT_STATUS_REG 0x3A
#define MPU6050_USR_CRTL_REG 0x6A
#define MPU6050_FIFO_EN_REG 0x23
#define MPU6050_FIFO_DATA_REG 0x74
#define MPU6050_FIFO_COUNT_L_REG 0x73
#define MPU6050_FIFO_COUNT_H_REG 0x72

#define MPU6050_RA_SELF_TEST_X 0x0D
#define MPU6050_RA_SELF_TEST_Y 0x0E
#define MPU6050_RA_SELF_TEST_Z 0x0F
#define MPU6050_RA_SELF_TEST_A 0x10
#define MPU6050_RA_SMPLRT_DIV 0x19
#define MPU6050_RA_CONFIG 0x1A
#define MPU6050_RA_GYRO_CONFIG 0x1B
#define MPU6050_RA_ACCEL_CONFIG 0x1C
// Not in documentation
#define MPU6050_RA_FF_THR 0x1D
#define MPU6050_RA_FF_DUR 0x1E
#define MPU6050_RA_MOT_THR 0x1F
#define MPU6050_RA_MOT_DUR 0x20
#define MPU6050_RA_ZRMOT_THR 0x21
#define MPU6050_RA_ZRMOT_DUR 0x22
// Not in documentation end
#define MPU6050_RA_FIFO_EN 0x23
#define MPU6050_RA_I2C_MST_CTRL 0x24
#define MPU6050_RA_I2C_SLV0_ADDR 0x25
#define MPU6050_RA_I2C_SLV0_REG 0x26
#define MPU6050_RA_I2C_SLV0_CTRL 0x27
#define MPU6050_RA_I2C_SLV1_ADDR 0x28
#define MPU6050_RA_I2C_SLV1_REG 0x29
#define MPU6050_RA_I2C_SLV1_CTRL 0x2A
#define MPU6050_RA_I2C_SLV2_ADDR 0x2B
#define MPU6050_RA_I2C_SLV2_REG 0x2C
#define MPU6050_RA_I2C_SLV2_CTRL 0x2D
#define MPU6050_RA_I2C_SLV3_ADDR 0x2E
#define MPU6050_RA_I2C_SLV3_REG 0x2F
#define MPU6050_RA_I2C_SLV3_CTRL 0x30
#define MPU6050_RA_I2C_SLV4_ADDR 0x31
#define MPU6050_RA_I2C_SLV4_REG 0x32
#define MPU6050_RA_I2C_SLV4_DO 0x33
#define MPU6050_RA_I2C_SLV4_CTRL 0x34
#define MPU6050_RA_I2C_SLV4_DI 0x35
#define MPU6050_RA_I2C_MST_STATUS 0x36
#define MPU6050_RA_INT_PIN_CFG 0x37
#define MPU6050_RA_INT_ENABLE 0x38
// Not in documentation
#define MPU6050_RA_DMP_INT_STATUS 0x39
// Not in documentation end
#define MPU6050_RA_INT_STATUS 0x3A
#define MPU6050_RA_ACCEL_XOUT_H 0x3B
#define MPU6050_RA_ACCEL_XOUT_L 0x3C
#define MPU6050_RA_ACCEL_YOUT_H 0x3D
#define MPU6050_RA_ACCEL_YOUT_L 0x3E
#define MPU6050_RA_ACCEL_ZOUT_H 0x3F
#define MPU6050_RA_ACCEL_ZOUT_L 0x40
#define MPU6050_RA_TEMP_OUT_H 0x41
#define MPU6050_RA_TEMP_OUT_L 0x42
#define MPU6050_RA_GYRO_XOUT_H 0x43
#define MPU6050_RA_GYRO_XOUT_L 0x44
#define MPU6050_RA_GYRO_YOUT_H 0x45
#define MPU6050_RA_GYRO_YOUT_L 0x46
#define MPU6050_RA_GYRO_ZOUT_H 0x47
#define MPU6050_RA_GYRO_ZOUT_L 0x48
#define MPU6050_RA_EXT_SENS_DATA_00 0x49
#define MPU6050_RA_EXT_SENS_DATA_01 0x4A
#define MPU6050_RA_EXT_SENS_DATA_02 0x4B
#define MPU6050_RA_EXT_SENS_DATA_03 0x4C
#define MPU6050_RA_EXT_SENS_DATA_04 0x4D
#define MPU6050_RA_EXT_SENS_DATA_05 0x4E
#define MPU6050_RA_EXT_SENS_DATA_06 0x4F
#define MPU6050_RA_EXT_SENS_DATA_07 0x50
#define MPU6050_RA_EXT_SENS_DATA_08 0x51
#define MPU6050_RA_EXT_SENS_DATA_09 0x52
#define MPU6050_RA_EXT_SENS_DATA_10 0x53
#define MPU6050_RA_EXT_SENS_DATA_11 0x54
#define MPU6050_RA_EXT_SENS_DATA_12 0x55
#define MPU6050_RA_EXT_SENS_DATA_13 0x56
#define MPU6050_RA_EXT_SENS_DATA_14 0x57
#define MPU6050_RA_EXT_SENS_DATA_15 0x58
#define MPU6050_RA_EXT_SENS_DATA_16 0x59
#define MPU6050_RA_EXT_SENS_DATA_17 0x5A
#define MPU6050_RA_EXT_SENS_DATA_18 0x5B
#define MPU6050_RA_EXT_SENS_DATA_19 0x5C
#define MPU6050_RA_EXT_SENS_DATA_20 0x5D
#define MPU6050_RA_EXT_SENS_DATA_21 0x5E
#define MPU6050_RA_EXT_SENS_DATA_22 0x5F
#define MPU6050_RA_EXT_SENS_DATA_23 0x60
// Not in documentation
#define MPU6050_RA_MOT_DETECT_STATUS 0x61
// Not in documentation end
#define MPU6050_RA_I2C_SLV0_DO 0x63
#define MPU6050_RA_I2C_SLV1_DO 0x64
#define MPU6050_RA_I2C_SLV2_DO 0x65
#define MPU6050_RA_I2C_SLV3_DO 0x66
#define MPU6050_RA_I2C_MST_DELAY_CTRL 0x67
#define MPU6050_RA_SIGNAL_PATH_RESET 0x68
// Not in documentation
#define MPU6050_RA_MOT_DETECT_CTRL 0x69
// Not in documentation end
#define MPU6050_RA_USER_CTRL 0x6A
#define MPU6050_RA_PWR_MGMT_1 0x6B
#define MPU6050_RA_PWR_MGMT_2 0x6C
#define MPU6050_RA_FIFO_COUNTH 0x72
#define MPU6050_RA_FIFO_COUNTL 0x73
#define MPU6050_RA_FIFO_R_W 0x74
#define MPU6050_RA_WHO_AM_I 0x75

/** Device ID Check (WHO_AM_I_REG default value) */
#define MPU6050_I_AM 0x68
/** Gyro sensitivities in degrees/s */
#define MPU6050_GYRO_SENS_250 ((float)1 / ((float)131))
#define MPU6050_GYRO_SENS_500 ((float)1 / ((float)65.5))
#define MPU6050_GYRO_SENS_1000 ((float)1 / ((float)32.8))
#define MPU6050_GYRO_SENS_2000 ((float)1 / ((float)16.4))
/** Accel sensitivities in g/s */
#define MPU6050_ACCL_SENS_2 ((float)1 / ((float)16384.0))
#define MPU6050_ACCL_SENS_4 ((float)1 / ((float)8192.0))
#define MPU6050_ACCL_SENS_8 ((float)1 / ((float)4096.0))
#define MPU6050_ACCL_SENS_16 ((float)1 / ((float)2048.0))
/** @brief Define MPU Output variables */

/** Define possible Sample rates */
#define MPU6050_SampleRate_8KHz	0x00  ///< Sample rate set to 8 kHz 
#define MPU6050_SampleRate_4KHz 0x01  ///< Sample rate set to 4 kHz 
#define MPU6050_SampleRate_2KHz 0x03  ///< Sample rate set to 2 kHz 
#define MPU6050_SampleRate_1KHz 0x07  ///< Sample rate set to 1 kHz 
#define MPU6050_SampleRate_500Hz 0x0F ///< Sample rate set to 500 Hz 
#define MPU6050_SampleRate_250Hz 0x1F ///< Sample rate set to 250 Hz 
#define MPU6050_SampleRate_125Hz 0x3F ///< Sample rate set to 125 Hz 
#define MPU6050_SampleRate_100Hz 0x4F ///< Sample rate set to 100 Hz 
/** Define for filtering of accelerometerdata
#define NUM_ELEMENTS 11

/** define for amount of FIFO entries
#define MPU6050_FIFO_AMT 1024


/**
 * @brief struct with all neccesarry variables stored
 * @param Gyro_X last calculated Gyroscop value on X-axis, raw data
 * @param Gyro_Y last calculated Gyroscop value on Y-axis, raw data
 * @param Gyro_Z last calculated Gyroscop value on Z-axis, raw data
 * @param Accl_X last calculated Acclerometer value on X-axis,raw data
 * @param Accl_Y last calculated Acclerometer value on Y-axis,raw data
 * @param Accl_Y last calculated Acclerometer value on Y-axis,raw data
 * @param Accl_Z last calculated Acclerometer value on Z-axis,raw data
 * @param X_deg  calculated Angle in degree in relation to X-axis 
 * @param Y_deg  calculated Angle in degree in relation to Y-axis
 * @param Z_deg  calculated Angle in degree in relation to Z-axis
 * */

typedef struct
{
	int16_t Gyro_X;
	int16_t Gyro_Y;
	int16_t Gyro_Z;
	int16_t Gx_offset;
	int16_t Gy_offset;
	int16_t Gz_offset;
	int16_t Gx_mean;
	int16_t Gy_mean;
	int16_t Gz_mean;
	int32_t Gyro_time;
	float Gyro_mult;
	float Gx_deg;
	float Gy_deg;
	float Gz_deg;

	int16_t Accl_X;
	int16_t Accl_Y;
	int16_t Accl_Z;
	int16_t Accl_X_filt;
	int16_t Accl_Y_filt;
	int16_t Accl_Z_filt;
	int16_t Ax_offset;
	int16_t Ay_offset;
	int16_t Az_offset;
	int16_t Ax_mean;
	int16_t Ay_mean;
	int16_t Az_mean;
	float Accl_mult;
	float Ax_deg;
	float Ay_deg;

	float X_deg;
	float Y_deg;
	float Z_deg;

} MPU6050_Data;
/**
 * @brief MPU6050 return values
 * 
 */
typedef enum
{
	MPU6050_Status_OK = 0x00,
	MPU6050_Read_OK,
	MPU6050_Status_Error,
	MPU6050_Read_Error,
	MPU6050_Status_Notconnected,
	MPU6050_Status_Invalid
} MPU6050_STATUS;

/**Configuration ENUMS
 * BEGINN
 */

/** @brief Set Accl_Res to 0, 1, 2, 3 for following resolution: 
 *        
 * 		   
*/
typedef enum
{
	MPU6050_ACCL_2G = 0x00, ///->0 ±2g  16384 LSB/g
	MPU6050_ACCL_4G,		///->1 ±4g   8192 LSB/g
	MPU6050_ACCL_8G,		///->2 ±8g   4096 LSB/g
	MPU6050_ACCL_16G		///->3 ±16g  2048 LSB/g
} MPU6050_ACCL_RES;

/** @brief Set Gyro_Res to 0, 1, 2, 3 for following resolution: */
typedef enum MPU6050_GYRO_RES_ENUM
{
	MPU6050_GYRO_250deg = 0x00, // 0 ±  250 °/s 131   LSB/°/s
	MPU6050_GYRO_500deg,		// 1 ±  500 °/s  65.5 LSB/°/s
	MPU6050_GYRO_1000deg,		// 2 ± 1000 °/s  32.8 LSB/°/s
	MPU6050_GYRO_2000deg		// 3 ± 2000 °/s  16.4 LSB/°/s
} MPU6050_GYRO_RES;

/** @brief User Controll  enum */
typedef enum MPU6050_USR_CRTL_ENUM
{
	MPU6050_USR_CRTL_SIG_COND_RESET = 0x01,
	MPU6050_USR_CRTL_I2C_MST_RESET = 0x02,
	MPU6050_USR_CRTL_FIFO_RESET = 0x04,
	MPU6050_USR_CRTL_I2C_TO_SPI = 0x10,
	MPU6050_USR_CRTL_I2C_MST_E = 0x20,
	MPU6050_USR_CRTL_FIFO_EN = 0x40
} MPU6050_USR_CRTL;

/** @brief Interrupt enable enum
 */
typedef enum MPU6050_INT_EN_ENUM
{
	MPU6050_INT_EN_DATA_RDY = 0x01,
	MPU6050_INT_EN_I2C_INT = 0x08,
	MPU6050_INT_EN_FIFO_OVERFLOW = 0x10
} MPU6050_INT_EN;

/** @brief Interrupt status enum */
typedef enum MPU6050_INT_STATUS_ENUM
{
	MPU6050_INT_DATA_RDY = 0x01,
	MPU6050_INT_I2C_INT = 0x08,
	MPU6050_INT_FIFO_OVERFLOW = 0x10
} MPU6050_INT_STATUS;

/** @brief FIFO_ENABLE enum */
typedef enum MPU6050_FIFO_EN_ENUM
{
	MPU6050_FIFO_EN_SLV0 = 0x01,
	MPU6050_FIFO_EN_SLV1 = 0x02,
	MPU6050_FIFO_EN_SLV2 = 0x04,
	MPU6050_FIFO_EN_ACCEL = 0x08,
	MPU6050_FIFO_EN_ZG = 0x10,
	MPU6050_FIFO_EN_YG = 0x20,
	MPU6050_FIFO_EN_XG = 0x40,
	MPU6050_FIFO_EN_TEMP = 0x80
} MPU6050_FIFO_EN;

/** @brief Tilt direction enumeration */
typedef enum tilt_direction_t
{

	TILT_NONE = 0x00,
	TILT_RIGHT = 0x01,
	TILT_LEFT,
	TILT_FRONT,
	TILT_BACK,
	TILT_RIGHT_S, // Fast
	TILT_LEFT_S,
	TILT_FRONT_S,
	TILT_BACK_S
} tilt_direction_t;

/** Movement direction enum */
typedef enum Movement_direction_t
{

	MOVEMENT_NONE = 0x00,
	MOVEMENT_HIGH = 0x01,
	MOVEMENT_DOWN,
	MOVEMENT_RIGHT,
	MOVEMENT_LEFT
} Movement_direction_t;

/**Configuration ENUMS
 * END
 */

// Data Struct
MPU6050_Data *Sensor_Data;
// I2C handler
I2C_HandleTypeDef *MPU6050_hi2c;



/**
 * Functions
 */
MPU6050_STATUS MPU6050_init(I2C_HandleTypeDef *__hi2c, MPU6050_Data *DataStruct, MPU6050_ACCL_RES accl_resolution, MPU6050_GYRO_RES gyro_resolution, uint8_t samplerate);
MPU6050_STATUS MPU6050_Read_Accl();
MPU6050_STATUS MPU6050_Read_Gyro();
MPU6050_STATUS MPU6050_Read_Sensor();
MPU6050_STATUS MPU6050_Calibrate();
MPU6050_STATUS MPU6050_Calculate_Mean();
Movement_direction_t MPU6050_Detect_Movement();
void getGyroRoll();
void getAcclRoll();
uint8_t MPU6050_GetIntReg(void);
void MPU6050_GetFiFoData(uint8_t buffer[1024]);
uint16_t MPU6050_Read_FIFOcount(void);
void MPU6050_Display_FIFO();
void MPU6050_FIFO_RESET();
uint8_t MPU6050_GetDMPIntReg(void);
void MPU6050_Display_Data();
float getAbsMax(float a, float b, float c);
uint8_t MPU6050_detectTilt();

/**
 * @} 
 * 
 */
#endif /* INC_MPU6050_GY521_H_ */
