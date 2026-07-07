/*
Author: MysticWiz
Date:06-07-2026

This is a simple sensor management system implementation.
this code uses Pointers, Structs, Arrays, Bit Manipulation

*/




#include <stdio.h>
#include <stdlib.h>

typedef enum sensor
{
    TEMPERATURE,
    HUMIDITY,
    PRESSURE
} sensor_t;

typedef enum status
{
    ACTIVE,
    INACTIVE,
    ERROR
} status_t;

typedef struct temp
{
    short int min_range;
    short int max_range;
    float reading;

} temp_t;

typedef struct humidity
{
    float calibration;
    float reading;
} humidity_t;

typedef struct pressure
{
    short int altitude;
    float reading;
} pressure_t;

typedef union sensordata
{
    temp_t temperature;
    humidity_t humidity;
    pressure_t pressure;
} sensordata_t;

typedef struct sensor_info
{
    unsigned char id;
    char name[20];
    sensor_t type;
    sensordata_t data;
    status_t status;
} sensor_info_t;

void init_sensor(sensor_info_t *sensors, unsigned char *count, unsigned char max_sensors);
void read_sensor_data(sensor_info_t *sensor);
void process_sensor_data(sensor_info_t *sensor);
void display_sensors(sensor_info_t *sensors, unsigned char count);
// Main function with sample usage
int main()
{
    sensor_info_t sensors[10] = {0}; // Static array for max 10 sensors
    unsigned char count = 0;
    char choice;

    printf("========== SENSOR MANAGEMENT SYSTEM ==========\n\n");

    do
    {
        printf("\n========== MENU ==========\n");
        printf("1. Initialize Sensor\n");
        printf("2. Read Sensor Data\n");
        printf("3. Process and Validate Data\n");
        printf("4. Display All Sensors\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf(" %c", &choice);

        switch (choice)
        {
            case '1':
                init_sensor(sensors, &count, 10);
                break;
            case '2':
                if (count == 0)
                {
                    printf("No sensors initialized. Please initialize sensors first.\n");
                }
                else
                {
                    printf("\nSelect sensor to read (1-%u): ", count);
                    unsigned char sensor_num;
                    scanf("%hhu", &sensor_num);
                    scanf("%*c");

                    if (sensor_num > 0 && sensor_num <= count)
                    {
                        read_sensor_data(&sensors[sensor_num - 1]);
                    }
                    else
                    {
                        printf("Invalid sensor number!\n");
                    }
                }
                break;
            case '3':
                if (count == 0)
                {
                    printf("No sensors initialized.\n");
                }
                else
                {
                    printf("\nProcessing all sensor data...\n");
                    for (unsigned char i = 0; i < count; i++)
                    {
                        process_sensor_data(&sensors[i]);
                    }
                }
                break;
            case '4':
                display_sensors(sensors, count);
                break;
            case '5':
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (1);

    return 0;
}
// Function implementations
void init_sensor(sensor_info_t *sensors, unsigned char *count, unsigned char max_sensors)
{
    if (*count >= max_sensors)
    {
        printf("Maximum sensors reached!\n");
        return;
    }

    sensor_info_t *sensor = &sensors[*count];

    printf("=== Initialize Sensor %d ===\n", (*count) + 1);

    printf("Please Enter the Sensor ID: ");
    scanf("%hhu", &sensor->id);
    scanf("%*c");

    printf("Please Enter the Sensor Name: ");
    scanf("%20s", sensor->name);
    scanf("%*c");

    printf("Please Enter the Sensor Type A(Temperature), B(Humidity), C(Pressure): ");
    char type;
    scanf("%c", &type);
    scanf("%*c");

    switch (type)
    {
        case 'A':
            sensor->type = TEMPERATURE;
            break;
        case 'B':
            sensor->type = HUMIDITY;
            break;
        case 'C':
            sensor->type = PRESSURE;
            break;
        default:
            printf("Invalid sensor type!\n");
            return;
    }

    sensor->status = INACTIVE;
    (*count)++;
    printf("Sensor initialized successfully!\n");
}
void read_sensor_data(sensor_info_t *sensor)
{
    printf("\n=== Reading Sensor Data: %s ===\n", sensor->name);

    switch (sensor->type)
    {
        case TEMPERATURE:
            printf("Please Enter the Temperature Sensor MIN Value: ");
            scanf("%hd", &sensor->data.temperature.min_range);
            scanf("%*c");
            printf("Please Enter the Temperature Sensor MAX Value: ");
            scanf("%hd", &sensor->data.temperature.max_range);
            scanf("%*c");
            printf("Please Enter the Temperature Sensor Reading: ");
            scanf("%f", &sensor->data.temperature.reading);
            scanf("%*c");
            break;
        case PRESSURE:
            printf("Please Enter the Pressure Sensor Altitude: ");
            scanf("%hd", &sensor->data.pressure.altitude);
            scanf("%*c");
            printf("Please Enter the Pressure Sensor Reading: ");
            scanf("%f", &sensor->data.pressure.reading);
            scanf("%*c");
            break;
        case HUMIDITY:
            printf("Please Enter the Humidity Sensor Calibration: ");
            scanf("%f", &sensor->data.humidity.calibration);
            scanf("%*c");
            printf("Please Enter the Humidity Sensor Reading: ");
            scanf("%f", &sensor->data.humidity.reading);
            scanf("%*c");
            break;
        default:
            printf("Unknown sensor type!\n");
            break;
    }

    sensor->status = ACTIVE;
}
void process_sensor_data(sensor_info_t *sensor)
{
    if (sensor->status == INACTIVE)
    {
        printf("Warning: Sensor %s is inactive!\n", sensor->name);
        return;
    }

    switch (sensor->type)
    {
        case TEMPERATURE:
            if (sensor->data.temperature.reading < sensor->data.temperature.min_range ||
                sensor->data.temperature.reading > sensor->data.temperature.max_range)
            {
                sensor->status = ERROR;
                printf("ERROR: Temperature reading out of range for sensor %s!\n", sensor->name);
            }
            else
            {
                sensor->status = ACTIVE;
                printf("Temperature reading is within valid range.\n");
            }
            break;
        case PRESSURE:
            if (sensor->data.pressure.reading < 0)
            {
                sensor->status = ERROR;
                printf("ERROR: Invalid pressure reading for sensor %s!\n", sensor->name);
            }
            else
            {
                sensor->status = ACTIVE;
                printf("Pressure reading is valid.\n");
            }
            break;
        case HUMIDITY:
            if (sensor->data.humidity.reading < 0 || sensor->data.humidity.reading > 100)
            {
                sensor->status = ERROR;
                printf("ERROR: Humidity reading out of range (0-100%%) for sensor %s!\n", sensor->name);
            }
            else
            {
                sensor->status = ACTIVE;
                printf("Humidity reading is valid.\n");
            }
            break;
        default:
            sensor->status = ERROR;
            break;
    }
}
void display_sensors(sensor_info_t *sensors, unsigned char count)
{
    if (count == 0)
    {
        printf("No sensors initialized yet!\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        printf("\n========== SENSOR INFORMATION: %d ==========\n", (i + 1));
        printf("Sensor ID: %u\n", sensors[i].id);
        printf("Sensor Name: %s\n", sensors[i].name);
        printf("Sensor Type: ");

        switch (sensors[i].type)
        {
            case TEMPERATURE:
                printf("Temperature\n");
                printf("  Min Range: %hd°C\n", sensors[i].data.temperature.min_range);
                printf("  Max Range: %hd°C\n", sensors[i].data.temperature.max_range);
                printf("  Current Reading: %.2f°C\n", sensors[i].data.temperature.reading);
                break;
            case PRESSURE:
                printf("Pressure\n");
                printf("  Altitude: %hd m\n", sensors[i].data.pressure.altitude);
                printf("  Current Reading: %.2f hPa\n", sensors[i].data.pressure.reading);
                break;
            case HUMIDITY:
                printf("Humidity\n");
                printf("  Calibration: %.2f\n", sensors[i].data.humidity.calibration);
                printf("  Current Reading: %.2f%%\n", sensors[i].data.humidity.reading);
                break;
            default:
                printf("Unknown\n");
                break;
        }

        printf("Sensor Status: ");
        switch (sensors[i].status)
        {
            case ACTIVE:
                printf("ACTIVE\n");
                break;
            case INACTIVE:
                printf("INACTIVE\n");
                break;
            case ERROR:
                printf("ERROR\n");
                break;
        }
    }
}