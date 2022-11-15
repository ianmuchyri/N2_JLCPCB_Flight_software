
#include <Adafruit_MPU6050.h>
#include <Adafruit_DPS310.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>
#include "readsensors.h"

// using uart 2 for serial communication
// SoftwareSerial GPSModule(GPS_RX_PIN, GPS_TX_PIN);

// void init_gps()
// {
//     GPSModule.begin(GPS_BAUD_RATE);
// }

Adafruit_MPU6050 mpu;
Adafruit_DPS310 dps;

void init_mpu()
{
    debugln("MPU6050 test!");
    if (!mpu.begin(0x69))
    {
        debugln("Could not find a valid MPU6050 sensor, check wiring!");
        while (1)
        {
            // produces a sound with a frequency of 3khz
            tone(buzzer_pin, 3000);
        }
    }
    else
    {
        debugln("MPU6050 FOUND");
        tone(buzzer_pin, 3000);
        delay(1000);
        noTone(buzzer_pin);
    }

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
}

void init_dps()
{
    debugln("DPS310 INITIALIZATION");
    if (!dps.begin_I2C())
    {
        debugln("could not find a valid DPS310 sensor, check wiring!");
        while (1)

        {
            // produces a sound with a frequency of 2khz
            tone(buzzer_pin, 2000);
        }
    }
    else
    {
        debugln("DPS310 FOUND");
        tone(buzzer_pin, 2000);
        delay(1000);
        noTone(buzzer_pin);
    }
    dps.configurePressure(DPS310_64HZ, DPS310_64SAMPLES);
    dps.configureTemperature(DPS310_64HZ, DPS310_64SAMPLES);
}
// void init_bmp()
// {
//     debugln("BMP180 INITIALIZATION");
//     if (!bmp.begin())
//     {
//         debugln("Could not find a valid BMP085 sensor, check wiring!");
//         while (1)
//         {
//          //produces a sound with a frequency of 2khz
//               tone(buzzer_pin,2000);
//         }
//     }
//     else
//     {
//         debugln("BMP180 FOUND");
//         tone(buzzer_pin,2000);
//         delay(1000);
//         noTone(buzzer_pin);
//     }
// }

// function to initialize bmp, mpu, and the sd card module
void init_sensors()
{
    // init_gps();
    // init_bmp();
    init_dps();
    init_mpu();
}

// String ConvertLat(String nmea[15])
// {
//     String posneg = "";
//     if (nmea[3] == "S")
//     {
//         posneg = "-";
//     }
//     String latfirst;
//     float latsecond;
//     for (int i = 0; i < nmea[2].length(); i++)
//     {
//         if (nmea[2].substring(i, i + 1) == ".")
//         {
//             latfirst = nmea[2].substring(0, i - 2);
//             latsecond = nmea[2].substring(i - 2).toFloat();
//         }
//     }
//     latsecond = latsecond / 60;
//     String CalcLat = "";

//     char charVal[9];
//     dtostrf(latsecond, 4, 6, charVal);
//     for (int i = 0; i < sizeof(charVal); i++)
//     {
//         CalcLat += charVal[i];
//     }
//     latfirst += CalcLat.substring(1);
//     latfirst = posneg += latfirst;
//     return latfirst;
// }

// String ConvertLng(String nmea[15])
// {
//     String posneg = "";
//     if (nmea[5] == "W")
//     {
//         posneg = "-";
//     }

//     String lngfirst;
//     float lngsecond;
//     for (int i = 0; i < nmea[4].length(); i++)
//     {
//         if (nmea[4].substring(i, i + 1) == ".")
//         {
//             lngfirst = nmea[4].substring(0, i - 2);
//             // debugln(lngfirst);
//             lngsecond = nmea[4].substring(i - 2).toFloat();
//             // debugln(lngsecond);
//         }
//     }
//     lngsecond = lngsecond / 60;
//     String CalcLng = "";
//     char charVal[9];
//     dtostrf(lngsecond, 4, 6, charVal);
//     for (int i = 0; i < sizeof(charVal); i++)
//     {
//         CalcLng += charVal[i];
//     }
//     lngfirst += CalcLng.substring(1);
//     lngfirst = posneg += lngfirst;
//     return lngfirst;
// }

// // Get the gps readings from the gps sensor
// struct GPSReadings get_gps_readings()
// {
//     String nmea[15];
//     int stringplace = 0;
//     int pos = 0;
//     struct GPSReadings gpsReadings;
//     GPSModule.flush();
//     while (GPSModule.available() > 0)
//     {
//         GPSModule.read();
//     }
//     if (GPSModule.find("$GPRMC,"))
//     {
//         debug("here");
//         String tempMsg = GPSModule.readStringUntil('\n');
//         for (int i = 0; i < tempMsg.length(); i++)
//         {
//             if (tempMsg.substring(i, i + 1) == ",")
//             {
//                 nmea[pos] = tempMsg.substring(stringplace, i);
//                 stringplace = i + 1;
//                 pos++;
//             }
//             if (i == tempMsg.length() - 1)
//             {
//                 nmea[pos] = tempMsg.substring(stringplace, i);
//             }
//         }
//         float lati = ConvertLat(nmea).toFloat();
//         float lngi = ConvertLng(nmea).toFloat();
//         gpsReadings.latitude = lati;
//         gpsReadings.longitude = lngi;
//     }

//     return gpsReadings;
// }

// Get the sensor readings
struct SensorReadings get_readings()
{
    struct SensorReadings return_val;
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    // return_val.altitude = bmp.readAltitude(SEA_LEVEL_PRESSURE);
       // return_val.temperature=bmp.readTemperature();
    return_val.ax = a.acceleration.x;
    return_val.ay = a.acceleration.y;
    return_val.az = a.acceleration.z;
    return_val.gx = g.gyro.x;
    return_val.gy = g.gyro.y;
    return_val.gz = g.gyro.z;
    return_val.temperature= temp.temperature;
    
   return_val.altitude= dps.readAltitude(SEA_LEVEL_PRESSURE);
   

    // check readings from mpu6050
    //  debug("ax: ");
    //  debugln(return_val.ax);
    //    debug("ay: ");
    //  debugln(return_val.ay);
    //    debug("az: ");
    //  debugln(return_val.az);
    //    debug("gx: ");
    //  debugln(return_val.gx);
    //    debug("gy: ");
    //  debugln(return_val.gy);
    //    debug("gz: ");
    //  debugln(return_val.gz);

    return return_val;
}