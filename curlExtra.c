//Cbot BTC-e is a wrapper to hide the low work and allow more easily programing to access the BTC-e API.
    /*Copyright (C) 2014  Rafael Sampaio

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A pairTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

    //author contact:rafasampaio1@gmail.com
#ifndef _CURLEXTRA_H
#include"curlExtra.h"
#endif

//extracted from curl examples
//http://curl.haxx.se/libcurl/c/getinmemory.html
size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp){
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userp;

	mem->memory = realloc(mem->memory, mem->size + realsize + 1);
	if(mem->memory == NULL) {
		/* out of memory! */
		printf("not enough memory (realloc returned NULL)\n");
 		return 0;
  	}

  	memcpy(&(mem->memory[mem->size]), contents, realsize);
  	mem->size += realsize;
  	mem->memory[mem->size] = 0;

  	return realsize;
}

int execRequest(CURL *pt){

	int i=0,control;

	do{
		if((control=curl_easy_perform(pt))){
			i++;
			sleep(CURL_SLEEP);
		}
		else return control;
	}while(i<CURL_ATTEMPTS);
	return control;
}

void curlExtra_GlobalInitAll(){
	curl_global_init(CURL_GLOBAL_ALL);
}

void curlExtra_GlobalInitSSL(){
	curl_global_init(CURL_GLOBAL_SSL);
}

void curlExtra_GlobalCleanUp(){
	curl_global_cleanup();
}
