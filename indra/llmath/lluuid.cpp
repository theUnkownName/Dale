/** 
 * @file lluuid.cpp
 *
 * Copyright (c) 2000-2007, Linden Research, Inc.
 * 
 * Second Life Viewer Source Code
 * The source code in this file ("Source Code") is provided by Linden Lab
 * to you under the terms of the GNU General Public License, version 2.0
 * ("GPL"), unless you have obtained a separate licensing agreement
 * ("Other License"), formally executed by you and Linden Lab.  Terms of
 * the GPL can be found in doc/GPL-license.txt in this distribution, or
 * online at http://secondlife.com/developers/opensource/gplv2
 * 
 * There are special exceptions to the terms and conditions of the GPL as
 * it is applied to this Source Code. View the full text of the exception
 * in the file doc/FLOSS-exception.txt in this software distribution, or
 * online at http://secondlife.com/developers/opensource/flossexception
 * 
 * By copying, modifying or distributing this software, you acknowledge
 * that you have read and understood your obligations described above,
 * and agree to abide by those obligations.
 * 
 * ALL LINDEN LAB SOURCE CODE IS PROVIDED "AS IS." LINDEN LAB MAKES NO
 * WARRANTIES, EXPRESS, IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY,
 * COMPLETENESS OR PERFORMANCE.
 */

#include "linden_common.h"

// We can't use WIN32_LEAN_AND_MEAN here, needs lots of includes.
#if LL_WINDOWS
#	undef WIN32_LEAN_AND_MEAN
#	include <winsock2.h>
#	include <windows.h>
#endif

#include "stdtypes.h"
#include "lldefs.h"
#include "llerror.h"

#include "lluuid.h"
#include "llerror.h"
#include "llrand.h"
#include "llmd5.h"
#include "llstring.h"
#include "lltimer.h"

const LLUUID LLUUID::null;
const LLTransactionID LLTransactionID::tnull;

/*

NOT DONE YET!!!

static char BASE85_TABLE[] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
	'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
	'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
	'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
	'y', 'z', '!', '#', '$', '%', '&', '(', ')', '*',
	'+', '-', ';', '[', '=', '>', '?', '@', '^', '_',
	'`', '{', '|', '}', '~', '\0'
};


void encode( char * fiveChars, unsigned int word ) throw( )
{
for( int ix = 0; ix < 5; ++ix ) {
fiveChars[4-ix] = encodeTable[ word % 85];
word /= 85;
}
}

To decode:
unsigned int decode( char const * fiveChars ) throw( bad_input_data )
{
unsigned int ret = 0;
for( int ix = 0; ix < 5; ++ix ) {
char * s = strchr( encodeTable, fiveChars[ ix ] );
if( s == 0 ) throw bad_input_data();
ret = ret * 85 + (s-encodeTable);
}
return ret;
}

void LLUUID::toBase85(char* out)
{
	U32* me = (U32*)&(mData[0]);
	for(S32 i = 0; i < 4; ++i)
	{
		char* o = &out[i*i];
		for(S32 j = 0; j < 5; ++j)
		{
			o[4-j] = BASE85_TABLE[ me[i] % 85];
			word /= 85;
		}
	}
}

unsigned int decode( char const * fiveChars ) throw( bad_input_data )
{
	unsigned int ret = 0;
	for( S32 ix = 0; ix < 5; ++ix )
	{
		char * s = strchr( encodeTable, fiveChars[ ix ] );
		ret = ret * 85 + (s-encodeTable);
	}
	return ret;
} 
*/

#define LL_USE_JANKY_RANDOM_NUMBER_GENERATOR 0
#if LL_USE_JANKY_RANDOM_NUMBER_GENERATOR
/**
 * @brief a global for
 */
static U64 sJankyRandomSeed(LLUUID::getRandomSeed());

/**
 * @brief generate a random U32.
 */
U32 janky_fast_random_bytes()
{
	sJankyRandomSeed = U64L(1664525) * sJankyRandomSeed + U64L(1013904223); 
	return (U32)sJankyRandomSeed;
}

/**
 * @brief generate a random U32 from [0, val)
 */
U32 janky_fast_random_byes_range(U32 val)
{
	sJankyRandomSeed = U64L(1664525) * sJankyRandomSeed + U64L(1013904223); 
	return (U32)(sJankyRandomSeed) % val; 
}

/**
 * @brief generate a random U32 from [0, val)
 */
U32 janky_fast_random_seeded_bytes(U32 seed, U32 val)
{
	seed = U64L(1664525) * (U64)(seed) + U64L(1013904223); 
	return (U32)(seed) % val; 
}
#endif

// Common to all UUID implementations
void LLUUID::toString(char *out) const
{
	sprintf(out,
		"%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		(U8)(mData[0]),
		(U8)(mData[1]),
		(U8)(mData[2]),
		(U8)(mData[3]),
		(U8)(mData[4]),
		(U8)(mData[5]),
		(U8)(mData[6]),
		(U8)(mData[7]),
		(U8)(mData[8]),
		(U8)(mData[9]),
		(U8)(mData[10]),
		(U8)(mData[11]),
		(U8)(mData[12]),
		(U8)(mData[13]),
		(U8)(mData[14]),
		(U8)(mData[15]));
}

void LLUUID::toCompressedString(char *out) const
{
	memcpy(out, mData, UUID_BYTES);		/* Flawfinder: ignore */
	out[UUID_BYTES] = '\0';
}

std::string LLUUID::getString() const
{
	return asString();
}

std::string LLUUID::asString() const
{
	char str[UUID_STR_SIZE];		/* Flawfinder: ignore */
	toString(str);
	return std::string(str);
}

BOOL LLUUID::set(const std::string& in_string, BOOL emit)
{
	return set(in_string.c_str(), emit);
}

BOOL LLUUID::set(const char *in_string, BOOL emit)
{
	BOOL broken_format = FALSE;
	if (!in_string)
	{
		llerrs << "No string pointer in LLUUID::set!" << llendl;
		setNull();
		return FALSE;
	}

	// empty strings should make NULL uuid
	if (!in_string[0])
	{
		setNull();
		return TRUE;
	}

	if (strlen(in_string) != (UUID_STR_LENGTH - 1))		/* Flawfinder: ignore */
	{
		// I'm a moron.  First implementation didn't have the right UUID format.
		// Shouldn't see any of these any more
		if (strlen(in_string) == (UUID_STR_LENGTH - 2))	/* Flawfinder: ignore */
		{
			if(emit)
			{
				llinfos << "Warning! Using broken UUID string format" << llendl;
			}
			broken_format = TRUE;
		}
		else
		{
			// Bad UUID string.  Spam as INFO, as most cases we don't care.
			if(emit)
			{
				llinfos << "Bad UUID string: " << in_string << llendl;
			}
			setNull();
			return FALSE;
		}
	}

	U8 cur_pos = 0;
	S32 i;
	for (i = 0; i < UUID_BYTES; i++)
	{
		if ((i == 4) || (i == 6) || (i == 8) || (i == 10))
		{
			cur_pos++;
			if (broken_format && (i==10))
			{
				// Missing - in the broken format
				cur_pos--;
			}
		}

		mData[i] = 0;

		if ((*(in_string + cur_pos) >= '0') && (*(in_string+cur_pos) <= '9'))
		{
			mData[i] += (U8)(*(in_string + cur_pos) - '0');
		}
		else if ((*(in_string + cur_pos) >= 'a') && (*(in_string+cur_pos) <='f'))
		{
			mData[i] += (U8)(10 + *(in_string + cur_pos) - 'a');
		}
		else if ((*(in_string + cur_pos) >= 'A') && (*(in_string+cur_pos) <='F'))
		{
			mData[i] += (U8)(10 + *(in_string + cur_pos) - 'A');
		}
		else
		{
			if(emit)
			{							
				llwarns << "Invalid UUID string character" << llendl;
			}
			setNull();
			return FALSE;
		}

		mData[i] = mData[i] << 4;
		cur_pos++;

		if ((*(in_string + cur_pos) >= '0') && (*(in_string+cur_pos) <= '9'))
		{
			mData[i] += (U8)(*(in_string + cur_pos) - '0');
		}
		else if ((*(in_string + cur_pos) >= 'a') && (*(in_string+cur_pos) <='f'))
		{
			mData[i] += (U8)(10 + *(in_string + cur_pos) - 'a');
		}
		else if ((*(in_string + cur_pos) >= 'A') && (*(in_string+cur_pos) <='F'))
		{
			mData[i] += (U8)(10 + *(in_string + cur_pos) - 'A');
		}
		else
		{
			if(emit)
			{
				llwarns << "Invalid UUID string character" << llendl;
			}
			setNull();
			return FALSE;
		}
		cur_pos++;
	}

	return TRUE;
}

BOOL LLUUID::validate(const std::string& in_string)
{
	return validate(in_string.c_str());
}

BOOL LLUUID::validate(const char *in_string) 
{
	BOOL broken_format = FALSE;
	if (!in_string)
	{
		return FALSE;
	}
	if (strlen(in_string) != (UUID_STR_LENGTH - 1))		/* Flawfinder: ignore */
	{
		// I'm a moron.  First implementation didn't have the right UUID format.
		if (strlen(in_string) == (UUID_STR_LENGTH - 2))		/* Flawfinder: ignore */
		{
			broken_format = TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	U8 cur_pos = 0;
	U32 i;
	for (i = 0; i < 16; i++)
	{
		if ((i == 4) || (i == 6) || (i == 8) || (i == 10))
		{
			cur_pos++;
			if (broken_format && (i==10))
			{
				// Missing - in the broken format
				cur_pos--;
			}
		}

		if ((*(in_string + cur_pos) >= '0') && (*(in_string+cur_pos) <= '9'))
		{
		}
		else if ((*(in_string + cur_pos) >= 'a') && (*(in_string+cur_pos) <='f'))
		{
		}
		else if ((*(in_string + cur_pos) >= 'A') && (*(in_string+cur_pos) <='F'))
		{
		}
		else
		{
			return FALSE;
		}

		cur_pos++;

		if ((*(in_string + cur_pos) >= '0') && (*(in_string+cur_pos) <= '9'))
		{
		}
		else if ((*(in_string + cur_pos) >= 'a') && (*(in_string+cur_pos) <='f'))
		{
		}
		else if ((*(in_string + cur_pos) >= 'A') && (*(in_string+cur_pos) <='F'))
		{
		}
		else
		{
			return FALSE;
		}
		cur_pos++;
	}
	return TRUE;
}

const LLUUID& LLUUID::operator^=(const LLUUID& rhs)
{
	U32* me = (U32*)&(mData[0]);
	const U32* other = (U32*)&(rhs.mData[0]);
	for(S32 i = 0; i < 4; ++i)
	{
		me[i] = me[i] ^ other[i];
	}
	return *this;
}

LLUUID LLUUID::operator^(const LLUUID& rhs) const
{
	LLUUID id(*this);
	id ^= rhs;
	return id;
}

void LLUUID::combine(const LLUUID& other, LLUUID& result) const
{
	LLMD5 md5_uuid;
	md5_uuid.update((unsigned char*)mData, 16);
	md5_uuid.update((unsigned char*)other.mData, 16);
	md5_uuid.finalize();
	md5_uuid.raw_digest(result.mData);
}

LLUUID LLUUID::combine(const LLUUID &other) const
{
	LLUUID combination;
	combine(other, combination);
	return combination;
}

std::ostream& operator<<(std::ostream& s, const LLUUID &uuid)
{
	char uuid_str[UUID_STR_LENGTH];

	uuid.toString(uuid_str);
	s << uuid_str;
	return s;
}

std::istream& operator>>(std::istream &s, LLUUID &uuid)
{
	U32 i;
	char uuid_str[UUID_STR_LENGTH];		/* Flawfinder: ignore */
	for (i = 0; i < UUID_STR_LENGTH-1; i++)
	{
		s >> uuid_str[i];
	}
	uuid_str[i] = '\0';
	uuid.set(uuid_str);
	return s;
}

static void get_random_bytes(void *buf, int nbytes)
{
	int i;
	char *cp = (char *) buf;

	// *NOTE: If we are not using the janky generator ll_rand()
	// generates at least 3 good bytes of data since it is 0 to
	// RAND_MAX. This could be made more efficient by copying all the
	// bytes.
	for (i=0; i < nbytes; i++)
#if LL_USE_JANKY_RANDOM_NUMBER_GENERATOR
		*cp++ = janky_fast_random_bytes() & 0xFF;
#else
		*cp++ = ll_rand() & 0xFF;
#endif
	return;	
}

#if LL_WINDOWS
typedef struct _ASTAT_
{
	ADAPTER_STATUS adapt;
	NAME_BUFFER    NameBuff [30];
}ASTAT, * PASTAT;

// static
S32 LLUUID::getNodeID(unsigned char * node_id)
{
	  ASTAT Adapter;
      NCB Ncb;
      UCHAR uRetCode;
      LANA_ENUM   lenum;
      int      i;
	  int retval = 0;

      memset( &Ncb, 0, sizeof(Ncb) );
      Ncb.ncb_command = NCBENUM;
      Ncb.ncb_buffer = (UCHAR *)&lenum;
      Ncb.ncb_length = sizeof(lenum);
      uRetCode = Netbios( &Ncb );
 //     printf( "The NCBENUM return code is: 0x%x \n", uRetCode );

      for(i=0; i < lenum.length ;i++)
      {
          memset( &Ncb, 0, sizeof(Ncb) );
          Ncb.ncb_command = NCBRESET;
          Ncb.ncb_lana_num = lenum.lana[i];

          uRetCode = Netbios( &Ncb );
 //         printf( "The NCBRESET on LANA %d return code is: 0x%x \n",
 //                 lenum.lana[i], uRetCode );

          memset( &Ncb, 0, sizeof (Ncb) );
          Ncb.ncb_command = NCBASTAT;
          Ncb.ncb_lana_num = lenum.lana[i];

          strcpy( (char *)Ncb.ncb_callname,  "*              " );		/* Flawfinder: ignore */
          Ncb.ncb_buffer = (unsigned char *)&Adapter;
          Ncb.ncb_length = sizeof(Adapter);

          uRetCode = Netbios( &Ncb );
//          printf( "The NCBASTAT on LANA %d return code is: 0x%x \n",
//                 lenum.lana[i], uRetCode );
          if ( uRetCode == 0 )
          {
//            printf( "The Ethernet Number on LANA %d is: %02x%02x%02x%02x%02x%02x\n",
//	 			  lenum.lana[i],
//                  Adapter.adapt.adapter_address[0],
//                  Adapter.adapt.adapter_address[1],
//                  Adapter.adapt.adapter_address[2],
//                  Adapter.adapt.adapter_address[3],
//                  Adapter.adapt.adapter_address[4],
//                  Adapter.adapt.adapter_address[5] );
			memcpy(node_id,Adapter.adapt.adapter_address,6);		/* Flawfinder: ignore */
			retval = 1;

          }
	  }
	return retval;
}

#elif LL_DARWIN
// Mac OS X version of the UUID generation code...
/*
 * Get an ethernet hardware address, if we can find it...
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_types.h>
#include <net/if_dl.h>
#include <net/route.h>
#include <ifaddrs.h>

// static
S32 LLUUID::getNodeID(unsigned char *node_id)
{
	int i;
	unsigned char 	*a = NULL;
	struct ifaddrs *ifap, *ifa;
	int rv;
	S32 result = 0;

	if ((rv=getifaddrs(&ifap))==-1)
	{       
		return -1;
	}
	if (ifap == NULL)
	{
		return -1;
	}

	for (ifa = ifap; ifa != NULL; ifa = ifa->ifa_next)
	{       
//		printf("Interface %s, address family %d, ", ifa->ifa_name, ifa->ifa_addr->sa_family);
		for(i=0; i< ifa->ifa_addr->sa_len; i++)
		{
//			printf("%02X ", (unsigned char)ifa->ifa_addr->sa_data[i]);
		}
//		printf("\n");
		
		if(ifa->ifa_addr->sa_family == AF_LINK)
		{
			// This is a link-level address
			struct sockaddr_dl *lla = (struct sockaddr_dl *)ifa->ifa_addr;
			
//			printf("\tLink level address, type %02X\n", lla->sdl_type);

			if(lla->sdl_type == IFT_ETHER)
			{
				// Use the first ethernet MAC in the list.
				// For some reason, the macro LLADDR() defined in net/if_dl.h doesn't expand correctly.  This is what it would do.
				a = (unsigned char *)&((lla)->sdl_data);
				a += (lla)->sdl_nlen;
				
				if (!a[0] && !a[1] && !a[2] && !a[3] && !a[4] && !a[5])
				{
					continue;
				}

				if (node_id) 
				{
					memcpy(node_id, a, 6);
					result = 1;
				}
				
				// We found one.
				break;
			}
		}
	}
	freeifaddrs(ifap);

	return result;
}

#else

// Linux version of the UUID generation code...
/*
 * Get the ethernet hardware address, if we can find it...
 */
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#define HAVE_NETINET_IN_H
#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#if !LL_DARWIN
#include <linux/sockios.h>
#endif
#endif

// static
S32 LLUUID::getNodeID(unsigned char *node_id)
{
	int 		sd;
	struct ifreq 	ifr, *ifrp;
	struct ifconf 	ifc;
	char buf[1024];
	int		n, i;
	unsigned char 	*a;
	
/*
 * BSD 4.4 defines the size of an ifreq to be
 * max(sizeof(ifreq), sizeof(ifreq.ifr_name)+ifreq.ifr_addr.sa_len
 * However, under earlier systems, sa_len isn't present, so the size is 
 * just sizeof(struct ifreq)
 */
#ifdef HAVE_SA_LEN
#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif
#define ifreq_size(i) max(sizeof(struct ifreq),\
     sizeof((i).ifr_name)+(i).ifr_addr.sa_len)
#else
#define ifreq_size(i) sizeof(struct ifreq)
#endif /* HAVE_SA_LEN*/

	sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (sd < 0) {
		return -1;
	}
	memset(buf, 0, sizeof(buf));
	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = buf;
	if (ioctl (sd, SIOCGIFCONF, (char *)&ifc) < 0) {
		close(sd);
		return -1;
	}
	n = ifc.ifc_len;
	for (i = 0; i < n; i+= ifreq_size(*ifr) ) {
		ifrp = (struct ifreq *)((char *) ifc.ifc_buf+i);
		strncpy(ifr.ifr_name, ifrp->ifr_name, IFNAMSIZ);		/* Flawfinder: ignore */
#ifdef SIOCGIFHWADDR
		if (ioctl(sd, SIOCGIFHWADDR, &ifr) < 0)
			continue;
		a = (unsigned char *) &ifr.ifr_hwaddr.sa_data;
#else
#ifdef SIOCGENADDR
		if (ioctl(sd, SIOCGENADDR, &ifr) < 0)
			continue;
		a = (unsigned char *) ifr.ifr_enaddr;
#else
		/*
		 * XXX we don't have a way of getting the hardware
		 * address
		 */
		close(sd);
		return 0;
#endif /* SIOCGENADDR */
#endif /* SIOCGIFHWADDR */
		if (!a[0] && !a[1] && !a[2] && !a[3] && !a[4] && !a[5])
			continue;
		if (node_id) {
			memcpy(node_id, a, 6);		/* Flawfinder: ignore */
			close(sd);
			return 1;
		}
	}
	close(sd);
	return 0;
}

#endif

S32 LLUUID::cmpTime(uuid_time_t *t1, uuid_time_t *t2)
{
   // Compare two time values.

   if (t1->high < t2->high) return -1;
   if (t1->high > t2->high) return 1;
   if (t1->low  < t2->low)  return -1;
   if (t1->low  > t2->low)  return 1;
   return 0;
}

void LLUUID::getSystemTime(uuid_time_t *timestamp)
{
   // Get system time with 100ns precision. Time is since Oct 15, 1582.
#if LL_WINDOWS
   ULARGE_INTEGER time;
   GetSystemTimeAsFileTime((FILETIME *)&time);
   // NT keeps time in FILETIME format which is 100ns ticks since
   // Jan 1, 1601. UUIDs use time in 100ns ticks since Oct 15, 1582.
   // The difference is 17 Days in Oct + 30 (Nov) + 31 (Dec)
   // + 18 years and 5 leap days.
   time.QuadPart +=
            (unsigned __int64) (1000*1000*10)       // seconds
          * (unsigned __int64) (60 * 60 * 24)       // days
          * (unsigned __int64) (17+30+31+365*18+5); // # of days

   timestamp->high = time.HighPart;
   timestamp->low  = time.LowPart;
#else
   struct timeval tp;
   gettimeofday(&tp, 0);

   // Offset between UUID formatted times and Unix formatted times.
   // UUID UTC base time is October 15, 1582.
   // Unix base time is January 1, 1970.
   U64 uuid_time = ((U64)tp.tv_sec * 10000000) + (tp.tv_usec * 10) +
                           U64L(0x01B21DD213814000);
   timestamp->high = (U32) (uuid_time >> 32);
   timestamp->low  = (U32) (uuid_time & 0xFFFFFFFF);
#endif
}

void LLUUID::getCurrentTime(uuid_time_t *timestamp)
{
   // Get current time as 60 bit 100ns ticks since whenever.
   // Compensate for the fact that real clock resolution is less
   // than 100ns.

   const U32 uuids_per_tick = 1024;

   static uuid_time_t time_last;
   static U32    uuids_this_tick;
   static BOOL     init = FALSE;

   if (!init) {
      getSystemTime(&time_last);
      uuids_this_tick = uuids_per_tick;
      init = TRUE;
   }

   uuid_time_t time_now = {0,0};

   while (1) {
      getSystemTime(&time_now);

      // if clock reading changed since last UUID generated
      if (cmpTime(&time_last, &time_now))  {
         // reset count of uuid's generated with this clock reading
         uuids_this_tick = 0;
         break;
      }
      if (uuids_this_tick < uuids_per_tick) {
         uuids_this_tick++;
         break;
      }
      // going too fast for our clock; spin
   }

   time_last = time_now;

   if (uuids_this_tick != 0) {
      if (time_now.low & 0x80000000) {
         time_now.low += uuids_this_tick;
         if (!(time_now.low & 0x80000000))
            time_now.high++;
      } else
         time_now.low += uuids_this_tick;
   }

   timestamp->high = time_now.high;
   timestamp->low  = time_now.low;
}

void LLUUID::generate()
{
	// Create a UUID.
	uuid_time_t timestamp;

	static unsigned char node_id[6];	/* Flawfinder: ignore */
	static int has_init = 0;
   
	// Create a UUID.
	static uuid_time_t time_last = {0,0};
	static U16 clock_seq = 0;
#if LL_USE_JANKY_RANDOM_NUMBER_GENERATOR
	static U32 seed = 0L; // dummy seed.  reset it below
#endif
	if (!has_init) 
	{
		if (getNodeID(node_id) <= 0) 
		{
			get_random_bytes(node_id, 6);
			/*
			 * Set multicast bit, to prevent conflicts
			 * with IEEE 802 addresses obtained from
			 * network cards
			 */
			node_id[0] |= 0x80;
		}

		getCurrentTime(&time_last);
#if LL_USE_JANKY_RANDOM_NUMBER_GENERATOR
		seed = time_last.low;
#endif

#if LL_USE_JANKY_RANDOM_NUMBER_GENERATOR
		clock_seq = (U16)janky_fast_random_seeded_bytes(seed, 65536);
#else
		clock_seq = (U16)ll_rand(65536);
#endif
		has_init = 1;
	}

	// get current time
	getCurrentTime(&timestamp);

	// if clock went backward change clockseq
	if (cmpTime(&timestamp, &time_last) == -1) {
		clock_seq = (clock_seq + 1) & 0x3FFF;
		if (clock_seq == 0) clock_seq++;
	}

	memcpy(mData+10, node_id, 6);		/* Flawfinder: ignore */
	U32 tmp;
	tmp = timestamp.low;
	mData[3] = (unsigned char) tmp;
	tmp >>= 8;
	mData[2] = (unsigned char) tmp;
	tmp >>= 8;
	mData[1] = (unsigned char) tmp;
	tmp >>= 8;
	mData[0] = (unsigned char) tmp;
	
	tmp = (U16) timestamp.high;
	mData[5] = (unsigned char) tmp;
	tmp >>= 8;
	mData[4] = (unsigned char) tmp;

	tmp = (timestamp.high >> 16) | 0x1000;
	mData[7] = (unsigned char) tmp;
	tmp >>= 8;
	mData[6] = (unsigned char) tmp;

	tmp = clock_seq;
	mData[9] = (unsigned char) tmp;
	tmp >>= 8;
	mData[8] = (unsigned char) tmp;

	LLMD5 md5_uuid;
	
	md5_uuid.update(mData,16);
	md5_uuid.finalize();
	md5_uuid.raw_digest(mData);

    time_last = timestamp;
}


U32 LLUUID::getRandomSeed()
{
   static unsigned char seed[16];		/* Flawfinder: ignore */
   
   getNodeID(&seed[0]);
   seed[6]='\0';
   seed[7]='\0';
   getSystemTime((uuid_time_t *)(&seed[8]));

   LLMD5 md5_seed;
	
   md5_seed.update(seed,16);
   md5_seed.finalize();
   md5_seed.raw_digest(seed);
   
   return(*(U32 *)seed);
}

BOOL LLUUID::parseUUID(const char* buf, LLUUID* value)
{
	if( buf == NULL || buf[0] == '\0' || value == NULL)
	{
		return FALSE;
	}

	LLString temp( buf );
	LLString::trim(temp);
	if( LLUUID::validate( temp ) )
	{
		value->set( temp );
		return TRUE;
	}
	return FALSE;
}

LLAssetID LLTransactionID::makeAssetID(const LLUUID& session) const
{
	LLAssetID result;
	if (isNull())
	{
		result.setNull();
	}
	else
	{
		combine(session, result);
	}
	return result;
}
