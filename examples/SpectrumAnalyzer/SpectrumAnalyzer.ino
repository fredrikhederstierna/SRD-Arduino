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

#define SRD_CS_PIN  (53)

// create an instance of the SRD class, specifying the
// pins it's SPI bus nCS and nRESET are attached to.
SRD srd( SRD_CS_PIN );

void setup()
{
  Serial1.begin(9600);
  Serial1.print("SRD example.\n");

  // set the speed
  srd.reset();
}

void loop()
{
  // sanity check
  unsigned int chip_partnum = srd.readRegister(CC1101_PARTNUM | READ_BURST, 1);
  unsigned int chip_version = srd.readRegister(CC1101_VERSION | READ_BURST, 1);

  Serial1.print("Read PARTNUM: ");
  Serial1.print(chip_partnum, HEX);
  Serial1.print("\n");

  Serial1.print("Read VERSION: ");
  Serial1.print(chip_version, HEX);
  Serial1.print("\n");

  delay(1000);
}
