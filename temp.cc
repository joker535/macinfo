#include <iostream>

using namespace std;

#include <mach/mach.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <unistd.h>

#define CP_USER 0
#define CP_SYS  1
#define CP_IDLE 2
#define CP_NICE 3
#define CP_STATES 4

enum BYTE_UNITS
{
  BYTES = 0,
  KILOBYTES = 1,
  MEGABYTES = 2,
  GIGABYTES = 3
};

template <class T>
T convert_unit( T num, int to, int from = BYTES)
{
  for( ; from < to; from++)
  {
    num /= 1024;
  }
  return num;
}

host_cpu_load_info_data_t _get_cpu_percentage()
{
  kern_return_t              error;
  mach_msg_type_number_t     count;
  host_cpu_load_info_data_t  r_load;
  mach_port_t                mach_port;

  count = HOST_CPU_LOAD_INFO_COUNT;
  mach_port = mach_host_self();
  error = host_statistics(mach_port, HOST_CPU_LOAD_INFO,
      ( host_info_t )&r_load, &count );

  if ( error != KERN_SUCCESS )
  {
    return host_cpu_load_info_data_t();
  }

  return r_load;
}

void getCpuUsePercentage()
{
    host_cpu_load_info_data_t load1 = _get_cpu_percentage();

    sleep(1);

    host_cpu_load_info_data_t load2 = _get_cpu_percentage();

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

    float value = static_cast<float>( diff_user + diff_system + diff_nice ) /
      static_cast<float>( diff_user + diff_system + diff_nice + diff_idle ) *
      100.0;


    vm_size_t page_size;
    mach_port_t mach_port;
    mach_msg_type_number_t count;
    vm_statistics64_data_t vm_stat;

    mach_port = mach_host_self();
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

        printf("m:%.2f%%c:%.2f%%\n",used * 1.0 / (free + used) * 100,value);

    }

}

int main()
{
    while (1)
    {
        getCpuUsePercentage();
    }
    return 0;
}