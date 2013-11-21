#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>



int IsFileExists(const std::string& fname)
{
	struct stat64 buff64;

	int res = stat64(fname.c_str(), &buff64);
	if (-1 != res)
		return 0;

	// No assertion if the path path does not exist.
	if (ENOENT != errno) 
	{
		std::cout << "stat: " << fname << ": " << strerror(errno) << "[" << __FUNCTION__ << ":" << __LINE__ << "]" << std::endl;
	}

	return -1;
}

int SystemPipedCommand(const std::string & system_command, std::string & output_string)
{
    std::cout << "SystemPipedCommand in" << "[" << __FUNCTION__ << ":" << __LINE__ << "]" << std::endl;

	int STATUS_OK = 0;
	int STATUS_FAIL = -1;
	
    int ret = STATUS_OK;
  
    output_string = "";
    char line[256];
    FILE *fpipe = NULL;
    if ( !(fpipe = (FILE*)popen(system_command.c_str(),"r")) )
    {
        ret =  STATUS_FAIL;
    }
    else
    {
        std::cout << "fopen OK" << "[" << __FUNCTION__ << ":" << __LINE__ << "]" << std::endl;

        int i = 0;
        while ( fgets( line, sizeof line, fpipe))
        {
            std::cout << "fgets OK : " << i << " line: " << line << std::endl;
            output_string += line;

            i++;
        }
        
        int exit_value = pclose(fpipe);
        ret = (-1 == exit_value
               ?
               STATUS_FAIL : exit_value);
        
        std::cout << "pclose( exit_value == " << exit_value << " ) : " << ( STATUS_OK == ret ? "OK" : "FAIL") 
		          << "[" << __FUNCTION__ << ":" << __LINE__ << "]" << std::endl;
    }
    return ret;
}

int GetSSLPassPhrase(const char* fname, std::string& out)
{
	if(0 != IsFileExists(fname))
	{
		std::cout << fname << ": No Such file!" << "[" << __FUNCTION__ << ":" << __LINE__ << "]" << std::endl;
		return -1;
	}


	std::string ans;
	std::ostringstream cmd;
	
	std::string fname_cmd(fname);
	//fname_cmd += " readConf";
	cmd << fname_cmd << " 2>&1";
	//cmd << fname << " 2>&1";
	
	std::cout << cmd.str() << "    " << cmd.str().c_str() << "[" << __FUNCTION__ << ":" << __LINE__ << "]" << std::endl;
	
	int ret;
	ret = SystemPipedCommand(cmd.str().c_str(), ans);
	if (ret != 0)
		std::cout << "error! ret=" << ret << "[" << __FUNCTION__ << ":" << __LINE__ << "]" << std::endl;

	out = ans;
	std::cout << "shell script result: " << ans << "[" << __FUNCTION__ << ":" << __LINE__ << "]" << std::endl;
	
	return 0;
}

#define SSL_PASS_PHRASE_DIALOG_LINK "./passphrase.sh"

int main()
{
	std::cout << "main in" << std::endl;
	
	//const char *fname = SSL_PASS_PHRASE_DIALOG_LINK;
	std::string fname(SSL_PASS_PHRASE_DIALOG_LINK);
	//fname += " readConf";
	
	std::cout << "fname: " << fname.c_str() << "[" << __FUNCTION__ << ":" << __LINE__ << "]" << std::endl;
	
	std::string pass;
	int stat = GetSSLPassPhrase(fname.c_str(), pass);
	
	if (0 != stat)
		std::cout << "stat=" << stat << "[" << __FUNCTION__ << ":" << __LINE__ << "]" << std::endl;
	std::cout << std::endl;
	
	return 0;
}

