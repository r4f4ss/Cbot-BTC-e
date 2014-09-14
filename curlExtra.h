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
#define _CURLEXTRA_H

#ifndef __CURL_CURL_H
#include<curl/curl.h>
#endif
#ifndef _MALLOC_H
#include<malloc.h>
#endif
#ifndef _STRING_H
#include<string.h>
#endif
#ifndef _TIME_H
#include<time.h>
#endif

#define CURL_TIMEOUT 3
#define CURL_SLEEP 2
#define CURL_ATTEMPTS 5

struct MemoryStruct{
char *memory;
size_t size;
};

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
int execRequest(CURL *pt);
void curlExtra_GlobalInitAll();
void curlExtra_GlobalInitSSL();
void curlExtra_GlobalCleanUp();

#endif
