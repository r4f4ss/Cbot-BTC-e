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
#ifndef _MISC_H
#define _MISC_H

#ifndef HEADER_PEM_H
#include<openssl/pem.h>
#endif

#ifndef _TIME_H
#include<time.h>
#endif

char *base64encode(const void *b64_encode_me, int encode_this_many_bytes);
char *my_strcpy(char *destination,const char *origin,int limit);
int wait(const time_t init,const int wt);

#endif
