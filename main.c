#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <string>

using namespace std;
 
string getCmdResult(const string &strCmd)
{  
    char buf[10240] = {0};  
    FILE *pf = NULL;  
      
    if( (pf = popen(strCmd.c_str(), "r")) == NULL )  
    {  
        return "";  
    }  
  
    string strResult;  
    while(fgets(buf, sizeof buf, pf))  
    {  
        strResult += buf;  
    }  
      
    pclose(pf);  
  
    unsigned int iSize =  strResult.size();  
    if(iSize > 0 && strResult[iSize - 1] == '\n')  // linux  
    {  
        strResult = strResult.substr(0, iSize - 1);  
    }  
  
    return strResult;  
}  
 
 
int ping_ip(char *ip)
{
	string strCmd = "ping " + string(ip) + " -w 1";
 
	string strRe = getCmdResult(strCmd);
 
	if(strRe.find("received") != string::npos && strRe.find(", 0 received") == string::npos)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main()
{
    char *ip = "192.168.1.1"; // get ip
    //char *ip = "192.168.1.111"; // no ip

    int ip_status = ping_ip(ip);
    if(ip_status == 0)
    {
        printf("no ip.\n\r");
    }
    else
    {
        printf("get ip.\n\r");
    }
    return 0;
}
