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
#include"misc.h"
#endif

/* A BASE-64 ENCODER USING OPENSSL (by Len Schulwitz)
 * pairameter 1: A pointer to the data you want to base-64 encode.
 * pairameter 2: The number of bytes you want encoded.
 * Return: A character pointer to the base-64 encoded data (null-terminated for string output).
 * On linux, compile with "gcc base64_encode.c -o b64enc -lcrypto" and run with "./b64enc".
 * This software has no warranty and is provided "AS IS".  Use at your own risk.
 * Published at http://stackoverflow.com/questions/342409/how-do-i-base64-encode-decode-in-c
 */

/*This function will Base-64 encode your data.*/
char * base64encode (const void *b64_encode_me, int encode_this_many_bytes){
    BIO *b64_bio, *mem_bio;   //Declare two BIOs.  One base64 encodes, the other stores memory.
    BUF_MEM *mem_bio_mem_ptr; //Pointer to the "memory BIO" structure holding the base64 data.

    b64_bio = BIO_new(BIO_f_base64());  //Initialize our base64 filter BIO.
    mem_bio = BIO_new(BIO_s_mem());  //Initialize our memory sink BIO.
    BIO_push(b64_bio, mem_bio);  //Link the BIOs (i.e. create a filter-sink BIO chain.)
    BIO_set_flags(b64_bio, BIO_FLAGS_BASE64_NO_NL);  //Don't add a newline every 64 characters.

    BIO_write(b64_bio, b64_encode_me, encode_this_many_bytes); //Encode and write our b64 data.
    BIO_flush(b64_bio);  //Flush data.  Necessary for b64 encoding, because of pad characters.

    BIO_get_mem_ptr(mem_bio, &mem_bio_mem_ptr);  //Store address of mem_bio's memory structure.
    BIO_set_close(mem_bio,BIO_NOCLOSE); //Permit access to mem_ptr after BIOs are destroyed.
    BIO_free_all(b64_bio);  //Destroys all BIOs in chain, starting with b64 (i.e. the 1st one).

    (*mem_bio_mem_ptr).data[(*mem_bio_mem_ptr).length] = '\0';  //Adds a null-terminator.

    return (*mem_bio_mem_ptr).data; //Returns base-64 encoded data. (See: "buf_mem_st" struct).
}

char *my_strcpy(char *destination,const char *origin,int limit){

	while(*origin!='\0'&&limit!=0){

		*destination=*origin;
		destination++;
		origin++;
		limit--;

	}

	*destination='\0';
	return destination;

}

int wait(const time_t init,const int wt){
	time_t actual;

	actual=time(NULL);
	if(actual==-1)return -1;
	while(difftime((actual=time(NULL)),init)<wt);

	return 0;
}



