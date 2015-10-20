/*
 * SpectumAnalyzer
 *
 * A simple spectrum analyzer.
 *
 * http://github.com/fredrikhederstierna
 * This example code is in the public domain.
 */

#include <SPI.h>
#include <SRD.h>

#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);  // Fast I2C / TWI 

#define SRD_CS_PIN  (53)

// create an instance of the SRD class, specifying the
// pins it's SPI bus nCS and nRESET are attached to.
SRD srd( SRD_CS_PIN );

struct rf_settings_s
{
    unsigned char FSCTRL1;   // Frequency synthesizer control.
    unsigned char FSCTRL0;   // Frequency synthesizer control.
    unsigned char FREQ2;     // Frequency control word, high unsigned char.
    unsigned char FREQ1;     // Frequency control word, middle unsigned char.
    unsigned char FREQ0;     // Frequency control word, low unsigned char.
    unsigned char MDMCFG4;   // Modem configuration.
    unsigned char MDMCFG3;   // Modem configuration.
    unsigned char MDMCFG2;   // Modem configuration.
    unsigned char MDMCFG1;   // Modem configuration.
    unsigned char MDMCFG0;   // Modem configuration.
    unsigned char CHANNR;    // Channel number.
    unsigned char DEVIATN;   // Modem deviation setting (when FSK modulation is enabled).
    unsigned char FREND1;    // Front end RX configuration.
    unsigned char FREND0;    // Front end RX configuration.
    unsigned char MCSM0;     // Main Radio Control State Machine configuration.
    unsigned char FOCCFG;    // Frequency Offset Compensation Configuration.
    unsigned char BSCFG;     // Bit synchronization Configuration.
    unsigned char AGCCTRL2;  // AGC control.
        unsigned char AGCCTRL1;  // AGC control.
    unsigned char AGCCTRL0;  // AGC control.
    unsigned char FSCAL3;    // Frequency synthesizer calibration.
    unsigned char FSCAL2;    // Frequency synthesizer calibration.
        unsigned char FSCAL1;    // Frequency synthesizer calibration.
    unsigned char FSCAL0;    // Frequency synthesizer calibration.
    unsigned char FSTEST;    // Frequency synthesizer calibration control
    unsigned char TEST2;     // Various test settings.
    unsigned char TEST1;     // Various test settings.
    unsigned char TEST0;     // Various test settings.
    unsigned char IOCFG2;    // GDO2 output pin configuration
    unsigned char IOCFG0;    // GDO0 output pin configuration
    unsigned char PKTCTRL1;  // Packet automation control.
    unsigned char PKTCTRL0;  // Packet automation control.
    unsigned char ADDR;      // Device address.
    unsigned char PKTLEN;    // Packet length.
};

typedef struct rf_settings_s rf_settings_t;

rf_settings_t pRfSettings =
{
    0x06,   // FSCTRL1   Frequency synthesizer control.
    0x00,   // FSCTRL0   Frequency synthesizer control.
    0x20,   // FREQ2     Frequency control word, high unsigned char.
    0x27,   // FREQ1     Frequency control word, middle unsigned char.
    0x59,   // FREQ0     Frequency control word, low unsigned char.
    0x8A,   // MDMCFG4   Modem configuration.
    0x75,   // MDMCFG3   Modem configuration.
    0x10,   // MDMCFG2   Modem configuration.
    0x22,   // MDMCFG1   Modem configuration.
    0x6C,   // MDMCFG0   Modem configuration.
    0x00,   // CHANNR    Channel number.
    0x46,   // DEVIATN   Modem deviation setting (when FSK modulation is enabled).
    0x56,   // FREND1    Front end RX configuration.
    0x17,   // FREND0    Front end RX configuration.
    0x18,   // MCSM0     Main Radio Control State Machine configuration.
    0x16,   // FOCCFG    Frequency Offset Compensation Configuration.
    0x6C,   // BSCFG     Bit synchronization Configuration.
    0x43,   // AGCCTRL2  AGC control.
    0x40,   // AGCCTRL1  AGC control.
    0x91,   // AGCCTRL0  AGC control.
    0xE9,   // FSCAL3    Frequency synthesizer calibration.
    0x2A,   // FSCAL2    Frequency synthesizer calibration.
    0x00,   // FSCAL1    Frequency synthesizer calibration.
    0x1F,   // FSCAL0    Frequency synthesizer calibration.
    0x59,   // FSTEST    Frequency synthesizer calibration.
    0x81,   // TEST2     Various test settings.
    0x35,   // TEST1     Various test settings.
    0x09,   // TEST0     Various test settings.
    0x0B,   // IOCFG2    GDO2 output pin configuration.
    0x02,   // IOCFG0D   GDO0 output pin configuration. Refer to SmartRF?Studio User Manual for detailed pseudo register explanation.
    0x04,   // PKTCTRL1  Packet automation control.
    0x12,   // PKTCTRL0  Packet automation control.
    0x00,   // ADDR      Device address.
    0x3D    // PKTLEN    Packet length.
};

// Write register settings
void cc1101_write_settings(void) 
{
    srd.writeRegister(CC1101_FSCTRL1,  pRfSettings.FSCTRL1);
    srd.writeRegister(CC1101_FSCTRL0,  pRfSettings.FSCTRL0);
    srd.writeRegister(CC1101_FREQ2,    pRfSettings.FREQ2);
    srd.writeRegister(CC1101_FREQ1,    pRfSettings.FREQ1);
    srd.writeRegister(CC1101_FREQ0,    pRfSettings.FREQ0);
    srd.writeRegister(CC1101_MDMCFG4,  pRfSettings.MDMCFG4);
    srd.writeRegister(CC1101_MDMCFG3,  pRfSettings.MDMCFG3);
    srd.writeRegister(CC1101_MDMCFG2,  pRfSettings.MDMCFG2);
    srd.writeRegister(CC1101_MDMCFG1,  pRfSettings.MDMCFG1);
    srd.writeRegister(CC1101_MDMCFG0,  pRfSettings.MDMCFG0);
    srd.writeRegister(CC1101_CHANNR,   pRfSettings.CHANNR);
    srd.writeRegister(CC1101_DEVIATN,  pRfSettings.DEVIATN);
    srd.writeRegister(CC1101_FREND1,   pRfSettings.FREND1);
    srd.writeRegister(CC1101_FREND0,   pRfSettings.FREND0);
    srd.writeRegister(CC1101_MCSM0 ,   pRfSettings.MCSM0 );
    srd.writeRegister(CC1101_FOCCFG,   pRfSettings.FOCCFG);
    srd.writeRegister(CC1101_BSCFG,    pRfSettings.BSCFG);
    srd.writeRegister(CC1101_AGCCTRL2, pRfSettings.AGCCTRL2);
        srd.writeRegister(CC1101_AGCCTRL1, pRfSettings.AGCCTRL1);
    srd.writeRegister(CC1101_AGCCTRL0, pRfSettings.AGCCTRL0);
    srd.writeRegister(CC1101_FSCAL3,   pRfSettings.FSCAL3);
    srd.writeRegister(CC1101_FSCAL2,   pRfSettings.FSCAL2);
        srd.writeRegister(CC1101_FSCAL1,   pRfSettings.FSCAL1);
    srd.writeRegister(CC1101_FSCAL0,   pRfSettings.FSCAL0);
    srd.writeRegister(CC1101_FSTEST,   pRfSettings.FSTEST);
    srd.writeRegister(CC1101_TEST2,    pRfSettings.TEST2);
    srd.writeRegister(CC1101_TEST1,    pRfSettings.TEST1);
    srd.writeRegister(CC1101_TEST0,    pRfSettings.TEST0);
    srd.writeRegister(CC1101_IOCFG2,   pRfSettings.IOCFG2);
    srd.writeRegister(CC1101_IOCFG0,   pRfSettings.IOCFG0);    
    srd.writeRegister(CC1101_PKTCTRL1, pRfSettings.PKTCTRL1);
    srd.writeRegister(CC1101_PKTCTRL0, pRfSettings.PKTCTRL0);
    srd.writeRegister(CC1101_ADDR,     pRfSettings.ADDR);
    srd.writeRegister(CC1101_PKTLEN,   pRfSettings.PKTLEN);
}
/*
*/

void u8g_prepare(void)
{
  u8g.setFont(u8g_font_6x10);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setFontPosTop();
}

void setup()
{
  Serial1.begin(9600);
  Serial1.print("SRD example.\n");

#if defined(ARDUINO)
  pinMode(13, OUTPUT);           
  digitalWrite(13, HIGH);  
#endif

  u8g_prepare();

  // set the speed
  srd.reset();

  delay(10);
  
  // sanity check
  unsigned int chip_partnum = srd.readRegister(CC1101_PARTNUM | READ_BURST, 1);
  unsigned int chip_version = srd.readRegister(CC1101_VERSION | READ_BURST, 1);

  Serial1.print("Read CC1101 PARTNUM: ");
  Serial1.print(chip_partnum, HEX);
  Serial1.print("\n");

  Serial1.print("Read CC1101 VERSION: ");
  Serial1.print(chip_version, HEX);
  Serial1.print("\n");

  cc1101_write_settings();

  // goto IDLE
  srd.writeRegister(CC1101_SIDLE | WRITE_SINGLE, 1);

  // goto RX
  srd.writeRegister(CC1101_SRX | WRITE_SINGLE, 1);
}


signed int rssi_val[128];
int rssi_x = 0;

void draw_rssi(void)
{
  u8g.drawStr( 0, 0, "Frq 869.05 MHz (Ch 5)");

  int i;
  for (i = 0; i < 128; i++) {
    signed int val = rssi_val[ i ];
    u8g.drawLine(i, 16 + (48 - val), i, 64);
  }
  
  /*
  Serial1.print("PLOT: ");
  Serial1.print(val, DEC);
  Serial1.print("\n");
*/

//  u8g.drawLine(rssi_x, 16 + (48 - val), rssi_x, 64);
}

void draw(void)
{
  draw_rssi();
}

void loop()
{
  // read RSSI
  unsigned int rssi = srd.readRegister(CC1101_RSSI | READ_BURST, 1);
  signed int val = (signed char)rssi;
  val = val + 118; // 10 is 128
  if (val < 0) {
    val = 0;
  }
  if (val > 128) {
    val = 128;
  }
  // range [0.128] --> [0..48]
  val = (val * 375) / 1000;
  //
  rssi_val[ rssi_x ] =  val;

  rssi_x++;
  if (rssi_x == 128) {
    rssi_x = 0;
  }

/*
  Serial1.print("RSSI: ");
  Serial1.print(rssi_x, HEX);
  Serial1.print(" = ");
  Serial1.print(val, DEC);
  Serial1.print("\n");
*/

  // picture loop  
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
}

