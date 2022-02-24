/*
   Copyright 2016 rm5248

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
*/

#include <stdint.h>
#include <stdio.h>
#include <c_serial.h>
#include <mach/mach.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <unistd.h>

#include<sys/stat.h>
#include<unistd.h>
#include<signal.h>


#define CP_USER 0
#define CP_SYS  1
#define CP_IDLE 2
#define CP_NICE 3
#define CP_STATES 4


void getCpuUsePercentage(char *dataout)
{
    mach_msg_type_number_t count;
    mach_port_t mach_port;
    mach_port = mach_host_self();
    count = HOST_CPU_LOAD_INFO_COUNT;

    host_cpu_load_info_data_t  load1;
    host_cpu_load_info_data_t  load2;
    host_statistics(mach_port, HOST_CPU_LOAD_INFO,
      ( host_info_t )&load1, &count );


    sleep(1);

     host_statistics(mach_port, HOST_CPU_LOAD_INFO,
      ( host_info_t )&load2, &count );

    // pre load times
    unsigned long long current_user = load1.cpu_ticks[CP_USER];
    unsigned long long current_system = load1.cpu_ticks[CP_SYS];
    unsigned long long current_nice = load1.cpu_ticks[CP_NICE];
    unsigned long long current_idle = load1.cpu_ticks[CP_IDLE];

    // Current load times
    unsigned long long next_user = load2.cpu_ticks[CP_USER];
    unsigned long long next_system = load2.cpu_ticks[CP_SYS];
    unsigned long long next_nice = load2.cpu_ticks[CP_NICE];
    unsigned long long next_idle = load2.cpu_ticks[CP_IDLE];

    // Difference between the two
    unsigned long long diff_user = next_user - current_user;
    unsigned long long diff_system = next_system - current_system;
    unsigned long long diff_nice = next_nice - current_nice;
    unsigned long long diff_idle = next_idle - current_idle;

    float value = (float)(diff_user + diff_system + diff_nice) /
      ( diff_user + diff_system + diff_nice + diff_idle );


    vm_size_t page_size;
   
   
    vm_statistics64_data_t vm_stat;

  
    count = HOST_VM_INFO64_COUNT;

    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO64,
                                          (host_info64_t)&vm_stat, &count))
    {

        // 仅仅打印了内存压力，你可以打印其他的值
        // 这里的page_size就是4096，是由平台决定的，64位机器的值就是4096
       // 使用long long仅仅是害怕数值太大，不是必要的
        long long useAndCache = (vm_stat.active_count + vm_stat.inactive_count + vm_stat.speculative_count + vm_stat.wire_count + vm_stat.compressor_page_count) * page_size;
        
        long long cache = (vm_stat.purgeable_count + vm_stat.external_page_count)  * page_size;
        
        long long used = useAndCache - cache;
        
        long long free = useAndCache + vm_stat.free_count - used;
        
        long long pressure = (vm_stat.wire_count + vm_stat.compressor_page_count) * page_size;

        printf("m:%.2f%%c:%.2f%%\n",used * 1.0 / (free + used) * 100,value*100.0);
        sprintf(dataout,"mc s%d s%d",(int)(231 * used * 1.0 / (free + used)),(int)(231 * value));

    }

}

/**
 */

int main( int argc, char** argv ){
    c_serial_port_t* m_port;
    c_serial_control_lines_t m_lines;
    int status;
    int bytes_read;
    char data[ 255 ];
    int data_length;
    int x;

    /*
     * Use the first argument as the port to open
     */
    if( argc != 2 ){
        fprintf( stderr, "ERROR: First argument must be serial port\n" );
		/*
		 * Since no port was provided, print the available ports
		 */
		const char** port_list = c_serial_get_serial_ports_list();
		x = 0;
		printf("Available ports:\n");
		while( port_list[ x ] != NULL ){
      char *rst = strstr(port_list[ x ],"/dev/tty");
      char *ptyrst = strstr(port_list[ x ],"/dev/pty");
      if(!rst && !ptyrst){
        printf( "%s\n", port_list[ x ] );
      }
			x++;
		}
		c_serial_free_serial_ports_list( port_list );
        return 1;
    }


    // //1.首先设置权限
    // umask(0);
 
    // //2.创建父子进程
    // pid_t id = fork();
 
    // if(id > 0)
    // {//father
    //     return 1;
    // }
    // else
    // {//child
    // }
 
    // //setsid
    // setsid();
    // // //更改目录为工作目录
    // // if(chdir("/") < 0)
    // // {   
    // //     printf("chdir");
    // //     return;
    // // }
 
    // //关闭文件描述符
    // close(0);
    // close(1);
    // close(2);
    // //屏蔽SIGCHLD信号
    // signal(SIGCHLD, SIG_IGN);

    /*
     * Set the global log function.
     * We will use a simple log function that prints to stderr
     */
    c_serial_set_global_log_function( c_serial_stderr_log_function );

    /*
     * Allocate the serial port struct.
     * This defaults to 9600-8-N-1
     */
    if( c_serial_new( &m_port, NULL ) < 0 ){
        fprintf( stderr, "ERROR: Unable to create new serial port\n" );
        return 1;
    }

    /*
     * The port name is the device to open(/dev/ttyS0 on Linux,
     * COM1 on Windows)
     */
    if( c_serial_set_port_name( m_port, argv[ 1 ] ) < 0 ){
        fprintf( stderr, "ERROR: can't set port name\n" );
    }

    /*
     * Set various serial port settings.  These are the default.
     */
    c_serial_set_baud_rate( m_port, CSERIAL_BAUD_9600 );
    c_serial_set_data_bits( m_port, CSERIAL_BITS_8 );
    c_serial_set_stop_bits( m_port, CSERIAL_STOP_BITS_1 );
    c_serial_set_parity( m_port, CSERIAL_PARITY_NONE );
    c_serial_set_flow_control( m_port, CSERIAL_FLOW_NONE );

    printf( "Baud rate is %d\n", c_serial_get_baud_rate( m_port ) );

    /*
     * We want to get all line flags when they change
     */
    c_serial_set_serial_line_change_flags( m_port, CSERIAL_LINE_FLAG_ALL );

    status = c_serial_open( m_port );
    if( status < 0 ){
        fprintf( stderr, "ERROR: Can't open serial port\n" );
        return 1;
    }

    /*
     * Listen for anything that comes across, and echo it back.
     */
    do{
        memset(data,0,255);
        getCpuUsePercentage(data);
        data_length = strlen(data);
        printf("%s",data);
        status = c_serial_write_data( m_port, data, &data_length );    
        if( status < 0 ){
            break;
        }
        c_serial_flush(m_port);
        // status = c_serial_read_data( m_port, data, &data_length, &m_lines );
        // if( status < 0 ){
        //     break;
        // }


        // printf( "Got %d bytes of data\n", data_length );
        // for( x = 0; x < data_length; x++ ){
        //     printf( "    0x%02X (ASCII: %c)\n", data[ x ], data[ x ] );
        // }
        // printf( "Serial line state: CD: %d CTS: %d DSR: %d DTR: %d RTS: %d RI: %d\n",
        //     m_lines.cd, 
        //     m_lines.cts,
        //     m_lines.dsr,
        //     m_lines.dtr,
        //     m_lines.rts,
        //     m_lines.ri );

       
    }while( 1 );
}
