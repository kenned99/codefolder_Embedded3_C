#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>        
#include <byteswap.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>


//made by udviklings-kenned
#define CONFIG_REG      0x01
#define TUPPER_REG      0x02
#define TLOWER_REG      0x03
#define TCRIT_REG       0x04
#define TA_REG          0x05
#define MANID_REG       0x06
#define DEVID_REG       0x07
#define RES_REG         0x08
#define MPC9808_BUS     "/dev/i2c-2"
#define MPC9808_ADR     0x18

int i2c_init(char *bus, unsigned int address) {
        int file;

        file = open(bus, O_RDWR);
        if (file < 0) { // If error
                fprintf(stderr, "ERROR: opening %s - %s\n", bus, strerror(errno));
                exit(1);
        }

        if (ioctl(file, I2C_SLAVE, address) == -1 ) { // If error
             fprintf(stderr, "ERROR: setting  address %d on i2c bus %s with ioctl() - %s", address, bus, strerror(errno));
             exit(1);
        }
        return(file);
}

/*int PrintToText( void ) {
    reg32 = i2c_smbus_write_byte_data(file, MANID_REG);
    printf("Hej Verden");
}*/

int main( void )
{
 int fd;
 struct ifreq ifr;
 unsigned char ip_adress[15];
 int file;
 file = i2c_init(MPC9808_BUS, 0x3e);
 fd = socket(AF_INET, SOCK_DGRAM, 0);

 // Henter IPv4 adresse 
 ifr.ifr_addr.sa_family = AF_INET;

 //address attached to "eth0"
 strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1); 

 ioctl(fd, SIOCGIFADDR, &ifr);

 close(fd);

 printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));

sprintf(ip_adress, inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr));

i2c_smbus_write_byte_data(file, 0x00, 0x28); //toline mode
i2c_smbus_write_byte_data(file, 0x00, 0x01); //display clear
i2c_smbus_write_byte_data(file, 0x00, 0x06); //entry mode


for (int i = 0; ;i++) {
    if (ip_adress[i] == 0x00)
            break;

i2c_smbus_write_byte_data(file, 0x40, ip_adress[i]);
}

// Read temperature
//reg32 = i2c_smbus_read_word_data(file, TA_REG);
//printf("TA_REG = (int32) %d\n", reg32);
//printf("TA_REG byte 0 = %d, byte 1 = %d\n", reg8poi[0], reg8poi[1] );
//<<

 close(file);
 return 0;
}
