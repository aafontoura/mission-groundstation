#ifndef HELICOPTERDEFS_H
#define HELICOPTERDEFS_H

/* if the connection with the communication is direct(port communication) or virtual (external */
/* singnal to an extern communication handler) */
#define VIRTUAL_PORT_COMMUNICATION
//#define REAL_PORT_COMMUNICATION


#define START_PACKAGE '#'
#define STOP_PACKAGE  '\r'
#define INTERFACE_NULL_BYTE '='
#define ADDRESS_ADD_BYTE 'a'
#define PAYLOAD_PACKAGE 6

#define FC_ADDRESS      1
#define NC_ADDRESS      2
#define MK3MAG_ADDRESS  3
#define BL_CTRL_ADDRESS 5


#define FC_ADDRESS_REPLY      (FC_ADDRESS + 'a')
#define NC_ADDRESS_REPLY      (NC_ADDRESS + 'a')
#define MK3MAG_ADDRESS_REPLY  MK3MAG_ADDRESS + 'a'
#define BL_CTRL_ADDRESS_REPLY BL_CTRL_ADDRESS + 'a'

#define VERSION_INFO_HEADER  'v'
#define DEBUG_OUT_HEADER     'd'
#define DATA_3D_HEADER       'c'
#define REDIRECT_UART_HEADER 'u'
#define SEND_TARGET_POSITION 's'
#define SEND_WAYPOINT        'w'
#define REQUEST_WAYPOINT     'x'
#define REQUEST_OSD          'o'

#define VERSION_INFO_HEADER_REPLY 'V'
#define DEBUG_OUT_HEADER_REPLY    'D'
#define DATA_3D_HEADER_REPLY      'C'
#define SEND_WAYPOINT_REPLY       'W'
#define REQUEST_WAYPOINT_REPLY    'X'
#define REQUEST_OSD_REPLY         'O'

#define UART_FC     '\0'
#define UART_MK3MAG '\1'
#define UART_MKGPS  '\2'
#define UART_NC     "\x1B\x1B\x55\xAA\0"

#define UART_FC_REQ     0
#define UART_NC_REQ     1
#define UART_MK3MAG_REQ 2
#define UART_MKGPS_REQ  3
#define UART_INIT       4

#define FREQ_INTERVAL_100HZ 1
#define FREQ_INTERVAL_10HZ  10
#define FREQ_INTERVAL_1HZ   100

/* Helicopter Request info State Machine */
#define GET_FC_VERSION 0
#define GET_NC_VERSION 1
#define GET_FC_3D_INFO 2
#define GET_NC_3D_INFO 3
#define DEBUG_FC_MODE  4
#define DEBUG_NC_MODE  5
#define GET_OSD_DATA   6

#define NORMAL_REQUEST_MODE 0

/* Timers */
#define TIMER_1_SECOND  1000
#define TIMER_2_SECONDS 2000
#define TIMER_3_SECONDS 3000
#define TIMER_4_SECONDS 4000
#define TIMER_5_SECONDS 5000
#define TIMER_500_MILI  500
#define TIMER_100_MILI  100
#define TIMER_10_MILI   10
#define TIMER_1_MILI    1

/* Table Index */
#define NUM_3D_DEBUGS   3



#define DEFAULT_DEVICE_HEADER FC_ADDRESS

// bitmask for HardwareError[0]
#define FC_ERROR0_GYRO_NICK             0x01
#define FC_ERROR0_GYRO_ROLL             0x02
#define FC_ERROR0_GYRO_YAW              0x04
#define FC_ERROR0_ACC_NICK              0x08
#define FC_ERROR0_ACC_ROLL              0x10
#define FC_ERROR0_ACC_TOP               0x20
#define FC_ERROR0_PRESSURE              0x40
#define FC_ERROR0_CAREFREE              0x80

// bitmask for HardwareError[1]
#define FC_ERROR1_I2C                   0x01
#define FC_ERROR1_BL_MISSING            0x02
#define FC_ERROR1_SPI_RX                0x04
#define FC_ERROR1_PPM                   0x08
#define FC_ERROR1_MIXER                 0x10
#define FC_ERROR1_RES1                  0x20
#define FC_ERROR1_RES2                  0x40
#define FC_ERROR1_RES3                  0x80


#define DECODE_A 0
#define DECODE_B 1
#define DECODE_C 2
#define DECODE_D 3

#define ENCODE_A 0
#define ENCODE_B 1
#define ENCODE_C 2


/* Waypoints */
// type of point
#define POINT_TYPE_INVALID 255
#define POINT_TYPE_WP   0
#define POINT_TYPE_POI  1

// status
#define INVALID         0x00
#define NEWDATA         0x01
#define PROCESSED       0x02

#define ALTITUDE_DEFAULT    10000   /* 10 meters */
#define LONGITUDE_DEFAULT   0
#define LATITUDE_DEFAULT    0
#define HEADING_DEFAULT     0
#define TOLERANCE_RADIUS_DEFAULT    1
#define TYPE_WAYPOINT_DEFAULT       0
/*****************************************/


#endif // HELICOPTERDEFS_H
