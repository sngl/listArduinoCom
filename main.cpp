/** -----------------------------
Created by Angelo Scialabba
email: scialabba.angelo@gmail.com
On 19/07/2013
-------------------------------**/
#include <stdio.h>
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>


int main()
{
    HDEVINFO DevInfoHandle;
    SP_DEVINFO_DATA DevInfoData;
    DWORD i;
    GUID arduinoguid;

    //creating the Arduino GUID object
    arduinoguid.Data1=0x4D36E978;
    arduinoguid.Data2=0xE325;
    arduinoguid.Data3=0x11CE;
    arduinoguid.Data4[0]=0xBF;
    arduinoguid.Data4[1]=0xC1;
    arduinoguid.Data4[2]=0x08;
    arduinoguid.Data4[3]=0x00;
    arduinoguid.Data4[4]=0x2B;
    arduinoguid.Data4[5]=0xE1;
    arduinoguid.Data4[6]=0x03;
    arduinoguid.Data4[7]=0x18;

    DevInfoHandle = SetupDiGetClassDevs(&arduinoguid,
                                   NULL,
                                   0,
                                   DIGCF_PRESENT);

    if (DevInfoHandle == INVALID_HANDLE_VALUE)
    {
        printf("Error: invalid handle value\n");
        return 1;
    }

    DevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    for (i=0; SetupDiEnumDeviceInfo(DevInfoHandle,i,
                                    &DevInfoData); i++)
    {
        DWORD DataT;
        char friendlyName[128];
        char hardwareId[128];
        DWORD buffersize = 128;
        //get the Displayed name and COM port
        while (!SetupDiGetDeviceRegistryProperty(
                    DevInfoHandle,
                    &DevInfoData,
                    SPDRP_FRIENDLYNAME ,
                    &DataT,
                    (PBYTE)friendlyName,
                    buffersize,
                    NULL))
        {
            if (GetLastError() ==
                    ERROR_INSUFFICIENT_BUFFER)
            {
                printf("Error: Insufficent buffer\n");
                break;
            }
            else
            {
                printf("Error: Unknown\n");
                break;
            }
        }
        //get the Hardware ID string
        while (!SetupDiGetDeviceRegistryProperty(
                    DevInfoHandle,
                    &DevInfoData,
                    SPDRP_HARDWAREID ,
                    &DataT,
                    (PBYTE)hardwareId,
                    buffersize,
                    NULL))
        {
            if (GetLastError() ==
                    ERROR_INSUFFICIENT_BUFFER)
            {
                printf("Error: Insufficent buffer\n");
                break;
            }
            else
            {
                printf("Error: Unknown\n");
                break;
            }
        }

        printf("%s",friendlyName);
        printf(" %s\n",hardwareId);
    }






    SetupDiDestroyDeviceInfoList(DevInfoHandle);

    return 0;
}
