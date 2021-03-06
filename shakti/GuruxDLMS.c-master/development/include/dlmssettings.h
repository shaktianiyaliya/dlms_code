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

#ifndef DLMS_SETTINGS_H
#define DLMS_SETTINGS_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "enums.h"
#include "variant.h"
#include "objectarray.h"
#include "message.h"
#include "gxvalueeventargs.h"
#include "replydata.h"
#include "ciphering.h"

    typedef struct
    {
        // Is custom challenges used. If custom challenge is used new challenge is
        // not generated if it is Set. This is for debugging purposes.
        unsigned char customChallenges;

        // Client to server challenge.
        gxByteBuffer ctoSChallenge;

        // Server to Client challenge.
        gxByteBuffer stoCChallenge;

        unsigned char sourceSystemTitle[8];

        // Invoke ID.
        unsigned char invokeID;

        //Long Invoke ID.
        int longInvokeID;

        // Priority.
        DLMS_PRIORITY priority;

        // Service class.
        DLMS_SERVICE_CLASS serviceClass;

        // Client address.
        uint16_t clientAddress;
        //Server address.
        uint16_t serverAddress;

        unsigned char useLogicalNameReferencing;
        DLMS_INTERFACE_TYPE interfaceType;
        DLMS_AUTHENTICATION authentication;
        gxByteBuffer password;
#ifndef DLMS_IGNORE_MALLOC
        gxByteBuffer kek;
#else
        unsigned char kek[16];
#endif //DLMS_IGNORE_MALLOC
        /**
        * DLMS version number.
        */
        unsigned char dlmsVersionNumber;

        /**
        * Max PDU size used in communicating.
        */
        uint16_t maxPduSize;

        /**
        * Max PDU size that server uses. Client can ask anything, but server will decide.
        */
        uint16_t maxServerPDUSize;

        /**
        * HDLC sender frame sequence number.
        */
        unsigned char senderFrame;

        /**
        * HDLC receiver block sequence number.
        */
        unsigned char receiverFrame;
        /**
        * Server functionality is not supported at the moment in ANSI C version.
        */
        unsigned char server;
        unsigned char isAuthenticationRequired;

        //When connection is made client tells what kind of services it want's to use.
        DLMS_CONFORMANCE proposedConformance;

        // Functionality what server can offer.
        DLMS_CONFORMANCE negotiatedConformance;

        //Used max info TX.
        uint16_t maxInfoTX;
        //Used max info RX.
        uint16_t maxInfoRX;
        //Used max window size in TX.
        unsigned char windowSizeTX;
        //Used max window size in RX.
        unsigned char windowSizeRX;
        objectArray objects;

        // Block packet index.
        uint32_t blockIndex;
        //Is connected to the meter.
        DLMS_CONNECTION_STATE connected;

#ifndef DLMS_IGNORE_HIGH_GMAC
        ciphering cipher;
#endif //DLMS_IGNORE_HIGH_GMAC

        int16_t userId;

        /**
        *  Protocol version.
        */
        unsigned char protocolVersion;

        unsigned char qualityOfService;
        //Pre-established Application Associations system title.

#ifndef DLMS_IGNORE_MALLOC
        gxByteBuffer* preEstablishedSystemTitle;
#else
        unsigned char preEstablishedSystemTitle[8];
#endif //DLMS_IGNORE_MALLOC

//Client serializes data to this PDU when malloc is not used.
#ifdef DLMS_IGNORE_MALLOC
        gxByteBuffer* serializedPdu;
#endif //DLMS_IGNORE_MALLOC
        //Auto increase Invoke ID.
        unsigned char autoIncreaseInvokeID;
    } dlmsSettings;

    typedef struct
    {
        /**
        * Executed command.
        */
        DLMS_COMMAND command;

        /**
         * Targets.
         */
        gxValueEventCollection targets;

#ifndef DLMS_IGNORE_MALLOC
        /**
         * Extra data from PDU.
         */
        gxByteBuffer data;
#endif //DLMS_IGNORE_MALLOC
    } gxLongTransaction;

    typedef struct
    {
        dlmsSettings base;

        gxReplyData info;
        /**
        * Received data frame.
        */
        gxByteBuffer receivedData;

        /**
        * Long get or read transaction information.
        */
        gxLongTransaction transaction;

        /**
        * Is server initialized.
        */
        unsigned char initialized;
#ifndef DLMS_IGNORE_IEC_HDLC_SETUP
        gxIecHdlcSetup *hdlc;
#endif //DLMS_IGNORE_IEC_HDLC_SETUP
#ifndef DLMS_IGNORE_TCP_UDP_SETUP
        gxTcpUdpSetup *wrapper;
#endif //DLMS_IGNORE_TCP_UDP_SETUP
        //Time when last frame was received. HDLC framing is using this.
        uint32_t dataReceived;
        //Time when last byte was received. HDLC framing is using this.
        uint32_t frameReceived;
        //Server is using push client address when sending push messages. Client address is used if PushAddress is zero.
        uint16_t pushClientAddress;
    } dlmsServerSettings;

    //Initialize server.
    void svr_init(
        dlmsServerSettings* settings,
        unsigned char useLogicalNameReferencing,
        DLMS_INTERFACE_TYPE interfaceType,
        //Max frame size.
        uint16_t frameSize,
        //Max PDU size.
        uint16_t pduSize,
        //Buffer where received frames are saved.
        unsigned char* frameBuffer,
        //Size of frame buffer.
        uint16_t frameBufferSize,
        //PDU Buffer.
        unsigned char* pduBuffer,
        //Size of PDU buffer.
        uint16_t pduBufferSize);

    //Initialize client.
    void cl_init(
        dlmsSettings* settings,
        unsigned char useLogicalNameReferencing,
        int clientAddress,
        int serverAddress,
        DLMS_AUTHENTICATION authentication,
        const char* password,
        DLMS_INTERFACE_TYPE interfaceType);

    //Clear DLMS settings.
    void cl_clear(
        dlmsSettings* settings);

    void svr_clear(
        dlmsServerSettings* settings);

    //Reset block index.
    void resetBlockIndex(
        dlmsSettings* settings);

    void resetFrameSequence(
        dlmsSettings* settings);

    unsigned char checkFrame(
        dlmsSettings* settings,
        unsigned char frame);

    void updateInvokeId(
        dlmsServerSettings* settings, unsigned char value);

    // Increase receiver sequence.
    //
    // value: Frame value.
    // Increased receiver frame sequence.
    unsigned char increaseReceiverSequence(
        unsigned char value);

    // Increase sender sequence.
    //
    // value : Frame value.
    // Increased sender frame sequence.
    unsigned char increaseSendSequence(
        unsigned char value);

    unsigned char getNextSend(
        dlmsSettings* settings, unsigned char first);

    unsigned char getReceiverReady(
        dlmsSettings* settings);

    unsigned char getKeepAlive(
        dlmsSettings* settings);

#ifndef DLMS_IGNORE_HIGH_GMAC
    unsigned char isCiphered(
        ciphering* cipher);
#endif //DLMS_IGNORE_HIGH_GMAC

    void trans_init(gxLongTransaction* trans);

    void trans_clear(gxLongTransaction* trans);

#ifdef  __cplusplus
}
#endif

#endif //DLMS_SETTINGS_H
