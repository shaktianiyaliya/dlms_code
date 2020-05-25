//
// --------------------------------------------------------------------------
//  Gurux Ltd
//
//
//
// Filename:        $HeadURL$
//
// Version:         $Revision$,
//                  $Date$
//                  $Author$
//
// Copyright (c) Gurux Ltd
//
//---------------------------------------------------------------------------
//
//  DESCRIPTION
//
// This file is a part of Gurux Device Framework.
//
// Gurux Device Framework is Open Source software; you can redistribute it
// and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// This code is licensed under the GNU General Public License v2.
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#ifndef GXREPLYDATA_H
#define GXREPLYDATA_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "variant.h"

    typedef struct
    {
        /**
        * Is more data available.
        */
        DLMS_DATA_REQUEST_TYPES moreData;
        /**
         * Received command.
         */
        DLMS_COMMAND command;
        /**
         * Encrypted command.
         */
        DLMS_COMMAND encryptedCommand;

        unsigned char commandType;

        /**
        * Received data.
        */
        gxByteBuffer data;

        /**
         * Is frame complete.
         */
        unsigned char complete;

        /**
         * Read value.
         */
        dlmsVARIANT dataValue;

        /**
         * Expected count of element in the array.
         */
        unsigned short totalCount;

#if !defined(GX_DLMS_MICROCONTROLLER) && (defined(_WIN32) || defined(_WIN64) || defined(__linux__))
        /**
        * Last read position. This is used in peek to solve how far data is read.
        */
        unsigned long readPosition;
        /**
        * Packet length.
        */
        unsigned long packetLength;
#else
        /**
        * Last read position. This is used in peek to solve how far data is read.
        */
        unsigned short readPosition;
        /**
        * Packet length.
        */
        unsigned short packetLength;
#endif
        /**
         * Try Get value.
         */
        unsigned char peek;

        /**
        * Value is not try to parse. This is used in data collector.
        */
        unsigned char ignoreValue;

        DLMS_DATA_TYPE dataType;

        /**
        * Cipher index is position where data is decrypted.
        */
        unsigned short cipherIndex;

        /**
         * Data notification date time.
         */
#ifdef DLMS_USE_EPOCH_TIME
        unsigned long time;
#else
        struct tm time;
#endif // DLMS_USE_EPOCH_TIME
        /**
        * Pre-established connection.
        */
        unsigned char preEstablished;
        unsigned char invokeId;

        //GBT block number.
        unsigned short blockNumber;
        //GBT block number ACK.
        unsigned short blockNumberAck;
        //GBT is streaming used.
        unsigned streaming;
        //GBT window size
        unsigned windowSize;
    } gxReplyData;

    unsigned char reply_isMoreData(gxReplyData* reply);

    /**
    * Initialize reply structure.
    */
    void reply_init(gxReplyData* reply);

    void reply_clear(gxReplyData* reply);

    void reply_clear2(gxReplyData* reply, unsigned char clearData);

#ifdef  __cplusplus
}
#endif

#endif //GXREPLYDATA_H
