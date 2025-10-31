/* ====================  IO Mapping  ==================== */

#ifndef IO_H
#define IO_H

/* ----------  Touch  ---------- */
#define IO_TOUCH_1      12      // Touch Input 1
#define IO_TOUCH_2      14      // Touch Input 2 
#define IO_TOUCH_3      27      // Touch Input 3

/* ----------  LED Outputs  ---------- */
#define IO_LED_1        0       // Red LED Output
#define IO_LED_2        2       // Green LED Output

/* ----------  I2C  ---------- */
#define IO_I2C_SCL      22      // I2C SCL
#define IO_I2C_SDA      21      // I2C SDA

/* ----------  SPI  ---------- */
#define IO_SPI_MISO     19      // SPI MISO
#define IO_SPI_MOSI     23      // SPI MOSI
#define IO_SPI_SCK      18      // SPI SCK
#define IO_SPI_CS       5       // SPI CS

/* ----------  UART  ---------- */
#define IO_UART1_TX     1       // UART1 TX
#define IO_UART1_RX     4       // UART1 RX
#define IO_UART2_TX     17      // UART2 TX
#define IO_UART2_RX     16      // UART2 RX

/* ----------  External IO  ---------- */
#define IO_EXT_1        4       // External Input 1 (GPIO 4)
#define IO_EXT_2        25      // External Input 2 (GPIO 25)

/* ----------  External Power IO  ---------- */
/*  External Power Inputs  */
#define IO_OPTO_IN      39      // Opto-Isolated Digital Input
/* External Power Outputs  */
#define IO_SSR_OUT      26      // SSR Enable Output
#define IO_5V_MOS_OUT   15      // 5V MOSFET controlled output

/* ----------  Sensor IO  ---------- */
/*  IMU Inputs  */
#define IO_IMU_INT      36      // IMU Interrupt Digital Input
/*  Analog Inputs  */
#define IO_LIGHT_AIN    34      // Light Sensor Analog Input
#define IO_NTC_AIN      35      // NTC Sensor Analog Input
#define IO_TC1046_AIN   32      // TC1046 Analog Input
#define IO_VREF_AIN     33      // VRef Analog Input

#endif  // IO_H