/*
 * OGEmonitor.cpp
 *
 *  Created on: Dec 19, 2013
 *      Author: MacBookPro
 */

#include "OGEmonitor.h"

std::string exec(char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "00000";
    while(!feof(pipe)) {
    	if(fgets(buffer, 128, pipe) != NULL)
    		//std::cout<<buffer<<std::endl;
    		//if(strcmp (buffer, "unb") == 0)
    		result += buffer;

    }
    pclose(pipe);
    std::cout<<result;
    return result;
}



