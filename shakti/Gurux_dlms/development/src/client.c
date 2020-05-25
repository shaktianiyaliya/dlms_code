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

#include "../include/gxignore.h"
#if !defined(DLMS_IGNORE_CLIENT)
#include "../include/gxmem.h"

#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
#include <assert.h>
#endif

#if _MSC_VER > 1400
#include <crtdbg.h>
#endif
#include "../include/apdu.h"
#include "../include/client.h"
#include "../include/gxkey.h"
#include "../include/gxset.h"
#include "../include/gxget.h"
#include "../include/dlms.h"
#include "../include/cosem.h"

int cl_snrmRequest(dlmsSettings* settings, message* messages)
{
    int ret;
    gxByteBuffer* reply;
    gxByteBuffer* pData;
    mes_clear(messages);
    settings->connected = DLMS_CONNECTION_STATE_NONE;
    settings->isAuthenticationRequired = 0;
    //SNRM request is not used in network connections.
    if (settings->interfaceType == DLMS_INTERFACE_TYPE_WRAPPER)
    {
        return DLMS_ERROR_CODE_OK;
    }
    resetFrameSequence(settings);
#ifdef DLMS_IGNORE_MALLOC
    if (!(messages->capacity > messages->size))
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    reply = messages->data[messages->size];
    ++messages->size;
    bb_clear(reply);
    pData = settings->serializedPdu;
    if (pData == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    bb_clear(pData);
#else
    reply = (gxByteBuffer*)gxmalloc(sizeof(gxByteBuffer));
    bb_init(reply);
    gxByteBuffer bb;
    bb_init(&bb);
    bb_capacity(&bb, 30);
    pData = &bb;
#endif //DLMS_IGNORE_MALLOC

    // FromatID
    if ((ret = bb_setUInt8(pData, 0x81)) == 0 &&
        // GroupID
        (ret = bb_setUInt8(pData, 0x80)) == 0 &&
        // Length is updated later.
        (ret = bb_setUInt8(pData, 0)) == 0)
    {
        // If custom HDLC parameters are used.
        if (ret == 0 && DEFAULT_MAX_INFO_TX != settings->maxInfoTX)
        {
            if ((ret = bb_setUInt8(pData, HDLC_INFO_MAX_INFO_TX)) == 0)
            {
                ret = dlms_appendHdlcParameter(pData, settings->maxInfoTX);
            }
        }
        if (ret == 0 && DEFAULT_MAX_INFO_RX != settings->maxInfoRX)
        {
            if ((ret = bb_setUInt8(pData, HDLC_INFO_MAX_INFO_RX)) == 0)
            {
                ret = dlms_appendHdlcParameter(pData, settings->maxInfoRX);
            }
        }
        if (ret == 0 && DEFAULT_MAX_WINDOW_SIZE_TX != settings->windowSizeTX)
        {
            if ((ret = bb_setUInt8(pData, HDLC_INFO_WINDOW_SIZE_TX)) == 0 &&
                (ret = bb_setUInt8(pData, 4)) == 0)
            {
                ret = bb_setUInt32(pData, settings->windowSizeTX);
            }
        }
        if (ret == 0 && DEFAULT_MAX_WINDOW_SIZE_RX != settings->windowSizeRX)
        {
            if ((ret = bb_setUInt8(pData, HDLC_INFO_WINDOW_SIZE_RX)) == 0 &&
                (ret = bb_setUInt8(pData, 4)) == 0)
            {
                ret = bb_setUInt32(pData, settings->windowSizeRX);
            }
        }
        // If default HDLC parameters are not used.
        if (ret == 0)
        {
            if (pData->size != 3)
            {
                // Length.
                ret = bb_setUInt8ByIndex(pData, 2, (unsigned char)(pData->size - 3));
            }
            else
            {
                bb_clear(pData);
            }
        }
        if (ret == 0 && (ret = dlms_getHdlcFrame(settings, DLMS_COMMAND_SNRM, pData, reply)) != 0)
        {
            bb_clear(pData);
            bb_clear(reply);
#ifndef DLMS_IGNORE_MALLOC
            gxfree(reply);
#endif //DLMS_IGNORE_MALLOC
            return ret;
        }
    }
    bb_clear(pData);
#ifndef DLMS_IGNORE_MALLOC
    mes_push(messages, reply);
#endif //DLMS_IGNORE_MALLOC
    return ret;
}

int cl_parseUAResponse(dlmsSettings* settings, gxByteBuffer* data)
{
    int ret = dlms_parseSnrmUaResponse(settings, data);
    settings->connected = DLMS_CONNECTION_STATE_HDLC;
    return ret;
}

int cl_aarqRequest(
    dlmsSettings* settings,
    message* messages)
{
    int ret;
    gxByteBuffer* pdu;
#ifdef DLMS_IGNORE_MALLOC
    if (!(messages->size < messages->capacity))
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    pdu = settings->serializedPdu;
    if (pdu == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    bb_clear(pdu);
#else
    gxByteBuffer buff;
    bb_init(&buff);
    pdu = &buff;
#endif //DLMS_IGNORE_MALLOC

    settings->connected &= ~DLMS_CONNECTION_STATE_DLMS;
    resetBlockIndex(settings);
    mes_clear(messages);
    ret = dlms_checkInit(settings);
    if (ret != DLMS_ERROR_CODE_OK)
    {
        return ret;
    }
    bb_clear(&settings->stoCChallenge);
    bb_clear(&settings->ctoSChallenge);
    if (settings->autoIncreaseInvokeID)
    {
        settings->invokeID = 0;
    }
    else
    {
        settings->invokeID = 1;
    }
    // If authentication or ciphering is used.
    if (settings->authentication > DLMS_AUTHENTICATION_LOW)
    {
        if ((ret = dlms_generateChallenge(&settings->ctoSChallenge)) != 0)
        {
            return ret;
        }
    }
    if ((ret = apdu_generateAarq(settings, pdu)) == 0)
    {
        if (settings->useLogicalNameReferencing)
        {
            gxLNParameters p;
            params_initLN(&p, settings, 0, DLMS_COMMAND_AARQ, 0, pdu, NULL, 0xFF, DLMS_COMMAND_NONE, 0, 0);
            ret = dlms_getLnMessages(&p, messages);
        }
        else
        {
#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
            gxSNParameters p;
            params_initSN(&p, settings, DLMS_COMMAND_AARQ, 0, 0, NULL, pdu, DLMS_COMMAND_NONE);
            ret = dlms_getSnMessages(&p, messages);
#else
            ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
#endif //DLMS_IGNORE_ASSOCIATION_SHORT_NAME
        }
        }
    settings->connected &= ~DLMS_CONNECTION_STATE_DLMS;
    bb_clear(pdu);
    return ret;
    }

int cl_parseAAREResponse(dlmsSettings* settings, gxByteBuffer* reply)
{
    int ret;
    unsigned char sd;
    DLMS_ASSOCIATION_RESULT result;
    unsigned char command = 0;
    if ((ret = apdu_parsePDU(settings, reply, &result, &sd, &command)) != 0)
    {
        return ret;
    }
    if (result != DLMS_ASSOCIATION_RESULT_ACCEPTED)
    {
        if (result == DLMS_ASSOCIATION_RESULT_TRANSIENT_REJECTED)
        {
            return DLMS_ERROR_CODE_REJECTED_TRANSIENT;
        }
        return DLMS_ERROR_CODE_REJECTED_PERMAMENT;
    }
    settings->isAuthenticationRequired = result == DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED && sd == DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_REQUIRED;
    if (!settings->isAuthenticationRequired)
    {
        settings->connected |= DLMS_CONNECTION_STATE_DLMS;
    }
    if (settings->dlmsVersionNumber != 6)
    {
        //Invalid DLMS version number.
        return DLMS_ERROR_CODE_INVALID_VERSION_NUMBER;
    }
    if (settings->isAuthenticationRequired != 0)
    {
        settings->connected |= DLMS_CONNECTION_STATE_DLMS;
    }
    return 0;
}

int cl_getApplicationAssociationRequest(
    dlmsSettings* settings,
    message* messages)
{
    int ret;
    gxByteBuffer challenge;
    gxByteBuffer* pw;
    dlmsVARIANT data;
#ifdef DLMS_IGNORE_MALLOC
#ifndef DLMS_IGNORE_HIGH_GMAC
    gxByteBuffer pw2;
#endif //DLMS_IGNORE_HIGH_GMAC
    unsigned char tmp[MAX_CHALLENGE_SIZE];
    bb_attach(&challenge, tmp, 0, sizeof(tmp));
#else
    bb_init(&challenge);
#endif //DLMS_IGNORE_MALLOC

    if (settings->authentication != DLMS_AUTHENTICATION_HIGH_ECDSA &&
#ifndef DLMS_IGNORE_HIGH_GMAC
        settings->authentication != DLMS_AUTHENTICATION_HIGH_GMAC &&
#endif // DLMS_IGNORE_HIGH_GMAC
        settings->password.size == 0)
    {
        //Password is invalid.
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    resetBlockIndex(settings);
#ifndef DLMS_IGNORE_HIGH_GMAC
    if (settings->authentication == DLMS_AUTHENTICATION_HIGH_GMAC)
    {
#ifndef DLMS_IGNORE_MALLOC
        pw = &settings->cipher.systemTitle;
#else
        bb_attach(&pw2, settings->cipher.systemTitle, 8, 8);
        pw = &pw2;
#endif //DLMS_IGNORE_MALLOC
    }
    else
#endif //DLMS_IGNORE_HIGH_GMAC
    {
        pw = &settings->password;
    }
    ret = dlms_secure(settings,
#ifndef DLMS_IGNORE_HIGH_GMAC
        settings->cipher.invocationCounter,
#else
        0,
#endif //DLMS_IGNORE_HIGH_GMAC
        & settings->stoCChallenge,
        pw,
        &challenge);
    if (ret == 0)
    {
        var_init(&data);
        data.vt = DLMS_DATA_TYPE_OCTET_STRING;
#ifdef DLMS_IGNORE_MALLOC
        data.byteArr = &challenge;
        if ((ret = bb_move(data.byteArr, 0, 2, data.byteArr->size)) == 0 &&
            (ret = bb_setUInt8ByIndex(data.byteArr, 0, DLMS_DATA_TYPE_OCTET_STRING)) == 0 &&
            (ret = bb_setUInt8ByIndex(data.byteArr, 1, (unsigned char)(data.byteArr->size - 2))) == 0)

#else
        data.byteArr = (gxByteBuffer*)gxmalloc(sizeof(gxByteBuffer));
        bb_init(data.byteArr);
        if ((ret = bb_setUInt8(data.byteArr, DLMS_DATA_TYPE_OCTET_STRING)) == 0 &&
            (ret = hlp_setObjectCount(challenge.size, data.byteArr)) == 0 &&
            (ret = bb_set2(data.byteArr, &challenge, 0, challenge.size)) == 0 &&
            (ret = bb_clear(&challenge)) == 0)
#endif //DLMS_IGNORE_MALLOC
        {
            if (settings->useLogicalNameReferencing)
            {
                unsigned char LN[6] = { 0, 0, 40, 0, 0, 255 };
                ret = cl_methodLN(settings, LN, DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME,
                    1, &data, messages);
            }
            else
            {
#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
                ret = cl_methodSN(settings, 0xFA00, DLMS_OBJECT_TYPE_ASSOCIATION_SHORT_NAME, 8, &data,
                    messages);
#else
                ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
#endif //DLMS_IGNORE_ASSOCIATION_SHORT_NAME
            }
        }
#ifndef DLMS_IGNORE_MALLOC
        var_clear(&data);
        bb_clear(&challenge);
#endif //DLMS_IGNORE_MALLOC
    }
    return ret;
}

int cl_parseApplicationAssociationResponse(
    dlmsSettings* settings,
    gxByteBuffer* reply)
{
    unsigned char empty, equals = 0;
    gxByteBuffer* secret;
    gxByteBuffer challenge;
#ifndef DLMS_IGNORE_HIGH_GMAC
    gxByteBuffer bb2;
#endif //DLMS_IGNORE_HIGH_GMAC
    int ret;
    unsigned long ic = 0;
#ifdef DLMS_IGNORE_MALLOC
    gxByteBuffer value;
    unsigned char tmp[MAX_CHALLENGE_SIZE];
    unsigned char tmp2[MAX_CHALLENGE_SIZE];
    bb_attach(&value, tmp, 0, sizeof(tmp));
    bb_attach(&challenge, tmp2, 0, sizeof(tmp2));
    if ((ret = cosem_getOctectString(reply, &value)) != 0)
    {
        settings->connected &= ~DLMS_CONNECTION_STATE_DLMS;
        //ParseApplicationAssociationResponse failed. Server to Client do not match.
        return DLMS_ERROR_CODE_AUTHENTICATION_FAILURE;
    }
    empty = value.size == 0;
#else
    gxDataInfo info;
    dlmsVARIANT value;
    var_init(&value);
    di_init(&info);
    if ((ret = dlms_getData(reply,
        &info,
        &value)) != 0)
    {
        return ret;
    }
    empty = value.vt == DLMS_DATA_TYPE_NONE;
    bb_init(&challenge);
#endif //DLMS_IGNORE_MALLOC
    if (!empty)
    {
#ifndef DLMS_IGNORE_HIGH_GMAC
        if (settings->authentication == DLMS_AUTHENTICATION_HIGH_GMAC)
        {
            unsigned char ch;
            bb_attach(&bb2, settings->sourceSystemTitle, sizeof(settings->sourceSystemTitle), sizeof(settings->sourceSystemTitle));
            secret = &bb2;
#ifdef DLMS_IGNORE_MALLOC
            if ((ret = bb_set(&challenge, value.data, value.size)) != 0 ||
#else
            if ((ret = bb_set(&challenge, value.byteArr->data, value.byteArr->size)) != 0 ||
#endif //DLMS_IGNORE_MALLOC
                (ret = bb_getUInt8(&challenge, &ch)) != 0 ||
                (ret = bb_getUInt32(&challenge, &ic)) != 0)
            {
#ifndef DLMS_IGNORE_MALLOC
                var_clear(&value);
#endif //DLMS_IGNORE_MALLOC
                    bb_clear(&challenge);
                    return ret;
            }
            bb_clear(&challenge);
        }
        else
#endif //DLMS_IGNORE_HIGH_GMAC
        {
            secret = &settings->password;
        }
        if ((ret = dlms_secure(
            settings,
            ic,
            &settings->ctoSChallenge,
            secret,
            &challenge)) != 0)
        {
#ifndef DLMS_IGNORE_MALLOC
            var_clear(&value);
#endif //DLMS_IGNORE_MALLOC
            bb_clear(&challenge);
            return ret;
}
#ifdef DLMS_IGNORE_MALLOC
        equals = bb_compare(
            &challenge,
            value.data,
            value.size);
#else
        equals = bb_compare(
            &challenge,
            value.byteArr->data,
            value.byteArr->size);
#endif //DLMS_IGNORE_MALLOC
    }
    else
    {
        // Server did not accept CtoS.
    }
#ifndef DLMS_IGNORE_MALLOC
    var_clear(&value);
    bb_clear(&challenge);
#endif //DLMS_IGNORE_MALLOC
    if (!equals)
    {
        settings->connected &= ~DLMS_CONNECTION_STATE_DLMS;
        //ParseApplicationAssociationResponse failed. Server to Client do not match.
        return DLMS_ERROR_CODE_AUTHENTICATION_FAILURE;
    }
    settings->connected |= DLMS_CONNECTION_STATE_DLMS;
    return 0;
}

#ifndef DLMS_IGNORE_MALLOC
// LN referencing
int cl_parseLNObjects(gxByteBuffer* data, objectArray* objects)
{
    gxObject* object;
    int ret;
    unsigned short pos, count;
    unsigned char size;
    oa_clear(objects);
    unsigned char version;
    gxDataInfo info;
    DLMS_OBJECT_TYPE class_id;
    dlmsVARIANT value;
    dlmsVARIANT* it1 = NULL, * it2 = NULL, * it3 = NULL, * ln = NULL;
    var_init(&value);
    //Get array tag.
    ret = bb_getUInt8(data, &size);
    if (ret != DLMS_ERROR_CODE_OK)
    {
        return 0;
    }
    //Check that data is in the array
    if (size != DLMS_DATA_TYPE_ARRAY)
    {
        return DLMS_ERROR_CODE_INVALID_RESPONSE;
    }
    //get object count
    if (hlp_getObjectCount2(data, &count) != 0)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    oa_capacity(objects, (unsigned short)count);
    for (pos = 0; pos != count; ++pos)
    {
        var_clear(&value);
        object = NULL;
        di_init(&info);
        if ((ret = dlms_getData(data, &info, &value)) != 0)
        {
            //This fix Iskraemeco (MT-880) bug.
            if (ret == DLMS_ERROR_CODE_OUTOFMEMORY)
            {
                break;
            }
            return ret;
        }
        if (value.vt != DLMS_DATA_TYPE_STRUCTURE || value.Arr->size != 4)
        {
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        if ((ret = va_getByIndex(value.Arr, 0, &it1)) != 0 ||
            (ret = va_getByIndex(value.Arr, 1, &it2)) != 0 ||
            (ret = va_getByIndex(value.Arr, 2, &ln)) != 0 ||
            (ret = va_getByIndex(value.Arr, 3, &it3)) != 0)
        {
            return ret;
        }
        if (it1->vt != DLMS_DATA_TYPE_UINT16 ||
            it2->vt != DLMS_DATA_TYPE_UINT8 ||
            ln->vt != DLMS_DATA_TYPE_OCTET_STRING ||
            it3->vt != DLMS_DATA_TYPE_STRUCTURE ||
            it3->Arr->size != 2)
        {
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        class_id = (DLMS_OBJECT_TYPE)var_toInteger(it1);
        version = (unsigned char)var_toInteger(it2);
        ret = cosem_createObject(class_id, &object);
        //If known object.
        if (ret != DLMS_ERROR_CODE_INVALID_PARAMETER)
        {
            object->version = version;
            ret = obj_updateAttributeAccessModes(object, it3->Arr);
            if (ret != 0)
            {
                return ret;
            }
            cosem_setLogicalName(object, ln->byteArr->data);
            oa_push(objects, object);
        }
    }
    var_clear(&value);
    return 0;
}
#endif //DLMS_IGNORE_MALLOC

int cl_getObjectsRequest(dlmsSettings* settings, message* messages)
{
    int ret;
    if (settings->useLogicalNameReferencing)
    {
        static unsigned char ln[] = { 0, 0, 40, 0, 0, 0xFF };
        ret = cl_readLN(settings, ln, DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, 2, NULL, messages);
}
    else
    {
#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
        ret = cl_readSN(settings, 0xFA00, 2, NULL, messages);
#else
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
#endif //DLMS_IGNORE_ASSOCIATION_SHORT_NAME
    }
    return ret;
}

#if !(defined(DLMS_IGNORE_ASSOCIATION_SHORT_NAME) || defined(DLMS_IGNORE_MALLOC))
// SN referencing
int cl_parseSNObjects(gxByteBuffer* data, objectArray* objects)
{
    gxDataInfo info;
    short sn;
    DLMS_OBJECT_TYPE class_id;
    dlmsVARIANT value;
    dlmsVARIANT* it1 = NULL, * it2 = NULL, * it3 = NULL, * ln = NULL;
    gxObject* object;
    int ret;
    unsigned short count, pos;
    unsigned char size, version;
    oa_clear(objects);
    var_init(&value);
    //Get array tag.
    ret = bb_getUInt8(data, &size);
    if (ret != DLMS_ERROR_CODE_OK)
    {
        return 0;
    }
    //Check that data is in the array
    if (size != 0x01)
    {
        return DLMS_ERROR_CODE_INVALID_RESPONSE;
    }
    //get object count
    if ((hlp_getObjectCount2(data, &count)) != 0)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    oa_capacity(objects, (unsigned short)count);
    for (pos = 0; pos != count; ++pos)
    {
        var_clear(&value);
        object = NULL;
        di_init(&info);
        if ((ret = dlms_getData(data, &info, &value)) != 0)
        {
            var_clear(&value);
            return ret;
        }
        if (value.vt != DLMS_DATA_TYPE_STRUCTURE || value.Arr->size != 4)
        {
            var_clear(&value);
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        if ((ret = va_getByIndex(value.Arr, 0, &it1)) != 0 ||
            (ret = va_getByIndex(value.Arr, 1, &it2)) != 0 ||
            (ret = va_getByIndex(value.Arr, 2, &it3)) != 0 ||
            (ret = va_getByIndex(value.Arr, 3, &ln)) != 0)
        {
            var_clear(&value);
            return ret;
        }
        if (it1->vt != DLMS_DATA_TYPE_INT16 ||
            it2->vt != DLMS_DATA_TYPE_UINT16 ||
            it3->vt != DLMS_DATA_TYPE_UINT8 ||
            ln->vt != DLMS_DATA_TYPE_OCTET_STRING)
        {
            var_clear(&value);
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        sn = (short)var_toInteger(it1);
        class_id = (DLMS_OBJECT_TYPE)var_toInteger(it2);
        version = (unsigned char)var_toInteger(it3);
        ret = cosem_createObject(class_id, &object);
        //If known object.
        if (ret != DLMS_ERROR_CODE_INVALID_PARAMETER)
        {
            object->shortName = sn;
            object->version = version;
            cosem_setLogicalName(object, ln->byteArr->data);
            oa_push(objects, object);
        }
    }
    var_clear(&value);
    return 0;
}

#endif //!(defined(DLMS_IGNORE_ASSOCIATION_SHORT_NAME) || defined(DLMS_IGNORE_MALLOC))

#ifndef DLMS_IGNORE_MALLOC
int cl_parseObjects(dlmsSettings* settings, gxByteBuffer* data)
{
    int ret;
    if (settings->useLogicalNameReferencing)
    {
        ret = cl_parseLNObjects(data, &settings->objects);
}
    else
    {
#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
        ret = cl_parseSNObjects(data, &settings->objects);
#else
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
#endif // DLMS_IGNORE_ASSOCIATION_SHORT_NAME
    }
    return ret;
}
#endif //DLMS_IGNORE_MALLOC

#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
int cl_readSN(
    dlmsSettings* settings,
    unsigned short address,
    unsigned char attributeOrdinal,
    gxByteBuffer* data,
    message* messages)
{
    int ret;
    DLMS_VARIABLE_ACCESS_SPECIFICATION requestType;
    gxSNParameters p;
    gxByteBuffer attributeDescriptor;
    if ((attributeOrdinal < 1))
    {
        //Invalid parameter
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    bb_init(&attributeDescriptor);
    resetBlockIndex(settings);
    address += (attributeOrdinal - 1) * 8;
    bb_setUInt16(&attributeDescriptor, address);
    // Add Selector.
    if (data != NULL && data->size != 0)
    {
        requestType = DLMS_VARIABLE_ACCESS_SPECIFICATION_PARAMETERISED_ACCESS;
    }
    else
    {
        requestType = DLMS_VARIABLE_ACCESS_SPECIFICATION_VARIABLE_NAME;
    }
    params_initSN(&p, settings, DLMS_COMMAND_READ_REQUEST, 1,
        requestType, &attributeDescriptor, data, DLMS_COMMAND_NONE);
    ret = dlms_getSnMessages(&p, messages);
    bb_clear(&attributeDescriptor);
    return ret;
}
#endif //DLMS_IGNORE_ASSOCIATION_SHORT_NAME

int cl_readLN(
    dlmsSettings* settings,
    unsigned char* name,
    DLMS_OBJECT_TYPE objectType,
    unsigned char attributeOrdinal,
    gxByteBuffer* data,
    message* messages)
{
    int ret;
    gxLNParameters p;
    gxByteBuffer* pdu;
    if ((attributeOrdinal < 1))
    {
        //Invalid parameter
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
#ifdef DLMS_IGNORE_MALLOC
    if (settings->serializedPdu == NULL)
    {
        //Invalid parameter
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    pdu = settings->serializedPdu;
    bb_clear(pdu);
#else
    gxByteBuffer attributeDescriptor;
    bb_init(&attributeDescriptor);
    pdu = &attributeDescriptor;
#endif //DLMS_IGNORE_MALLOC
    resetBlockIndex(settings);
    // CI
    if ((ret = bb_setUInt16(pdu, objectType)) == 0 &&
        // Add LN
        (ret = bb_set(pdu, name, 6)) == 0 &&
        // Attribute ID.
        (ret = bb_setUInt8(pdu, attributeOrdinal)) == 0)
    {
        if (data == NULL || data->size == 0)
        {
            // Access selection is not used.
            ret = bb_setUInt8(pdu, 0);
        }
        else
        {
            // Access selection is used.
            if ((ret = bb_setUInt8(pdu, 1)) == 0)
            {
                // Add data.
                ret = bb_set2(pdu, data, 0, data->size);
            }
        }
    }
    if (ret == 0)
    {
        params_initLN(&p, settings, 0,
            DLMS_COMMAND_GET_REQUEST, DLMS_GET_COMMAND_TYPE_NORMAL,
            pdu, data, 0xFF, DLMS_COMMAND_NONE, 0, 0);
        ret = dlms_getLnMessages(&p, messages);
    }
    bb_clear(pdu);
    return ret;
}

int cl_readList(
    dlmsSettings* settings,
    gxArray* list,
    message* reply)
{
    gxListItem* it;
    gxObject* obj;
    unsigned short pos = 0, count;
    int ret;
#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
    unsigned short sn;
#endif //DLMS_IGNORE_ASSOCIATION_SHORT_NAME
    gxByteBuffer bb;
    if (list->size == 0)
    {
        //Invalid parameter
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    bb_init(&bb);
    resetBlockIndex(settings);
    if (settings->useLogicalNameReferencing)
    {
        gxLNParameters p;
        params_initLN(&p, settings, 0, DLMS_COMMAND_GET_REQUEST, DLMS_GET_COMMAND_TYPE_WITH_LIST,
            &bb, NULL, 0xff, DLMS_COMMAND_NONE, 0, 0);
        //Request service primitive shall always fit in a single APDU.
        count = (settings->maxPduSize - 12) / 10;
        if (list->size < count)
        {
            count = list->size;
        }
        //All meters can handle 10 items.
        if (count > 10)
        {
            count = 10;
        }
        // Add length.
        hlp_setObjectCount(count, &bb);
        for (pos = 0; pos != list->size; )
        {
#ifdef DLMS_IGNORE_MALLOC
            if ((ret = arr_getByIndex(list, pos, (void**)&it, sizeof(gxObject*))) != 0)
            {
                break;
            }
#else
            if ((ret = arr_getByIndex(list, pos, (void**)&it)) != 0)
            {
                break;
            }
#endif //DLMS_IGNORE_MALLOC
            obj = (gxObject*)it->key;
            // CI.
            bb_setUInt16(&bb, obj->objectType);
            bb_set(&bb, obj->logicalName, 6);
            // Attribute ID.
            bb_setUInt8(&bb, it->value);
            // Attribute selector is not used.
            bb_setUInt8(&bb, 0);
            ++pos;
            if (pos % count == 0 && list->size != pos)
            {
                if ((ret = dlms_getLnMessages(&p, reply)) != 0)
                {
                    return ret;
                }
                bb_clear(&bb);
                if (list->size - pos < count)
                {
                    hlp_setObjectCount(list->size - pos, &bb);
                }
                else
                {
                    hlp_setObjectCount(count, &bb);
                }
            }
        }
        ret = dlms_getLnMessages(&p, reply);
    }
    else
    {
#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
        gxSNParameters p;
        for (pos = 0; pos != list->size; ++pos)
        {
#ifdef DLMS_IGNORE_MALLOC
            if ((ret = arr_getByIndex(list, pos, (void**)&it, sizeof(gxListItem))) != 0)
            {
                return ret;
            }
#else
            if ((ret = arr_getByIndex(list, pos, (void**)&it)) != 0)
            {
                return ret;
            }
#endif //DLMS_IGNORE_MALLOC

            // Add variable type.
            bb_setUInt8(&bb, 2);
            sn = ((gxObject*)it->key)->shortName;
            sn += ((unsigned short)it->value - 1) * 8;
            bb_setUInt16(&bb, sn);
        }
        params_initSN(&p, settings, DLMS_COMMAND_READ_REQUEST, list->size, 0xFF, &bb, NULL, DLMS_COMMAND_NONE);
        ret = dlms_getSnMessages(&p, reply);
#else
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
#endif //DLMS_IGNORE_ASSOCIATION_SHORT_NAME
    }
    bb_clear(&bb);
    return ret;
}

int cl_read(
    dlmsSettings* settings,
    gxObject* object,
    unsigned char attributeOrdinal,
    message* messages)
{
    int ret;
    if (object == NULL)
    {
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    else if (settings->useLogicalNameReferencing)
    {
        ret = cl_readLN(settings, object->logicalName, object->objectType, attributeOrdinal, NULL, messages);
}
    else
    {
#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
        ret = cl_readSN(settings, object->shortName, attributeOrdinal, NULL, messages);
#else
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
#endif //DLMS_IGNORE_ASSOCIATION_SHORT_NAME
    }
    return ret;
}

#ifndef DLMS_IGNORE_PROFILE_GENERIC
int cl_readRowsByEntry(dlmsSettings* settings, gxProfileGeneric* object, unsigned long index, unsigned long count, message* messages)
{
    return cl_readRowsByEntry2(settings, object, index, count, 1, 0, messages);
}

int cl_readRowsByEntry2(dlmsSettings* settings, gxProfileGeneric* object, unsigned long index, unsigned long count, unsigned short colStart, unsigned short colEnd, message* messages)
{
    int ret;
    gxByteBuffer data;
    if (object == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
#ifdef DLMS_IGNORE_MALLOC
    unsigned char buff[20];
    bb_attach(&data, buff, 0, sizeof(buff));
#else
    bb_init(&data);
#endif //DLMS_IGNORE_MALLOC
    //Add AccessSelector
    if ((ret = bb_setUInt8(&data, 2)) == 0 &&
        //Add structure tag.
        (ret = cosem_setStructure(&data, 4)) == 0 &&
        //Add start index
        (ret = cosem_setUInt32(&data, index)) == 0 &&
        //Add Count
        (ret = cosem_setUInt32(&data, count == 0 ? 0 : index + count - 1)) == 0 &&
        //Add columns.
        (ret = cosem_setUInt16(&data, colStart)) == 0 &&
        (ret = cosem_setUInt16(&data, colEnd)) == 0)
    {
        if (settings->useLogicalNameReferencing)
        {
            ret = cl_readLN(settings, object->base.logicalName, object->base.objectType, 2, &data, messages);
        }
        else
        {
#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
            ret = cl_readSN(settings, object->base.shortName, 2, &data, messages);
#endif //DLMS_IGNORE_ASSOCIATION_SHORT_NAME
        }
    }
    bb_clear(&data);
    return ret;
}

int cl_readRowsByRange2(
    dlmsSettings* settings,
    gxProfileGeneric* object,
    gxtime* start,
    gxtime* end,
    message* messages)
{
#ifdef DLMS_USE_EPOCH_TIME
    return cl_readRowsByRange(settings, object, start->value, end->value, messages);
#else
    return cl_readRowsByRange(settings, object, &start->value, &end->value, messages);
#endif //DLMS_USE_EPOCH_TIME
}

#ifdef DLMS_USE_EPOCH_TIME
int cl_readRowsByRange(
    dlmsSettings* settings,
    gxProfileGeneric* object,
    unsigned long start,
    unsigned long end,
    message* messages)
#else
int cl_readRowsByRange(
    dlmsSettings* settings,
    gxProfileGeneric* object,
    struct tm* start,
    struct tm* end,
    message* messages)
#endif //DLMS_USE_EPOCH_TIME
{
    unsigned char unixTime = 0;
    static unsigned char LN[] = { 0, 0, 1, 0, 0, 255 };
    DLMS_OBJECT_TYPE type = DLMS_OBJECT_TYPE_CLOCK;
    unsigned char* ln = LN;
    gxtime t;
    int ret;
    gxByteBuffer data;
    if (object == NULL || start == 0 || end == 0 || messages == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    if (object->captureObjects.size != 0)
    {
#ifdef DLMS_IGNORE_MALLOC
        gxTarget* kv;
        ret = arr_getByIndex(&object->captureObjects, 0, (void**)&kv, sizeof(gxTarget));
        if (ret != 0)
        {
            return ret;
        }
        type = kv->target->objectType;
        ln = kv->target->logicalName;
#else
        gxKey* kv;
        ret = arr_getByIndex(&object->captureObjects, 0, (void**)&kv);
        if (ret != 0)
        {
            return ret;
        }
        type = ((gxObject*)kv->key)->objectType;
        ln = ((gxObject*)kv->key)->logicalName;
#endif //DLMS_IGNORE_MALLOC
        unixTime = type == DLMS_OBJECT_TYPE_DATA;
    }
#ifndef DLMS_IGNORE_MALLOC
    if ((ret = obj_clearProfileGenericBuffer(&object->buffer)) != 0)
    {
        return ret;
    }
#endif //DLMS_IGNORE_MALLOC
    time_clear(&t);
#ifdef DLMS_IGNORE_MALLOC
    unsigned char buff[100];
    bb_attach(&data, buff, 0, sizeof(buff));
#else
    bb_init(&data);
#endif //DLMS_IGNORE_MALLOC
    //Add AccessSelector
    if ((ret = bb_setUInt8(&data, 1)) == 0 &&
        //Add structure tag.
        (ret = cosem_setStructure(&data, 4)) == 0 &&
        //Add structure tag.
        (ret = cosem_setStructure(&data, 4)) == 0 &&
        // Add class_id
        (ret = cosem_setUInt16(&data, type)) == 0 &&
        // Add parameter Logical name
        (ret = cosem_setOctectString2(&data, ln, 6)) == 0 &&
        //Add attribute index.
        (ret = cosem_setInt8(&data, 2)) == 0 &&
        //Add version.
        (ret = cosem_setUInt16(&data, 0)) == 0)
    {
        //Add start time
        if (unixTime)
        {
#ifdef DLMS_USE_EPOCH_TIME
            ret = cosem_setUInt32(&data, start);
#else
            ret = cosem_setUInt32(&data, time_toUnixTime(start));
#endif //DLMS_USE_EPOCH_TIME
        }
        else
        {
#ifdef DLMS_USE_EPOCH_TIME
            time_initUnix(&t, start);
#else
            time_init2(&t, start);
#endif //DLMS_USE_EPOCH_TIME
            if ((ret = cosem_setDateTimeAsOctectString(&data, &t)) != 0)
            {
                bb_clear(&data);
                return ret;
        }
    }
        //Add end time
        if (unixTime)
        {
#ifdef DLMS_USE_EPOCH_TIME
            ret = cosem_setUInt32(&data, end);
#else
            ret = cosem_setUInt32(&data, time_toUnixTime(end));
#endif //DLMS_USE_EPOCH_TIME
        }
        else
        {
#ifdef DLMS_USE_EPOCH_TIME
            time_initUnix(&t, end);
#else
            time_init2(&t, end);
#endif //DLMS_USE_EPOCH_TIME
            if ((ret = cosem_setDateTimeAsOctectString(&data, &t)) != 0)
            {
                bb_clear(&data);
                return ret;
            }
        }
        //Add array of read columns. Read All...
        bb_setUInt8(&data, 0x01);
        //Add item count
        bb_setUInt8(&data, 0x00);
        if (settings->useLogicalNameReferencing)
        {
            ret = cl_readLN(settings, object->base.logicalName, object->base.objectType, 2, &data, messages);
        }
        else
        {
#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
            ret = cl_readSN(settings, object->base.shortName, 2, &data, messages);
#endif //DLMS_IGNORE_ASSOCIATION_SHORT_NAME
        }
}
    bb_clear(&data);
    return ret;
}
#endif // DLMS_IGNORE_PROFILE_GENERIC

int cl_getData(dlmsSettings* settings, gxByteBuffer* reply, gxReplyData* data)
{
    return dlms_getData2(settings, reply, data, 0);
}

int cl_changeType(
    gxByteBuffer* value,
    DLMS_DATA_TYPE type,
    dlmsVARIANT* newValue)
{
    return dlms_changeType(value, type, newValue);
}

int cl_updateValue(
    dlmsSettings* settings,
    gxObject* target,
    unsigned char attributeIndex,
    dlmsVARIANT* value)
{
    gxValueEventArg e;
    if (target == NULL)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    e.target = target;
    e.index = attributeIndex;
    e.value = *value;
    return cosem_setValue(settings, &e);
}

int cl_updateValues(
    dlmsSettings* settings,
    gxArray* list,
    gxByteBuffer* data)
{
    unsigned short count;
    int pos, ret = 0;
    gxListItem* it;
    gxDataInfo info;
    unsigned char ch;
    gxValueEventArg e;
    ve_init(&e);
    if ((ret = hlp_getObjectCount2(data, &count)) != 0)
    {
        return ret;
    }
    if (count != list->size)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }

    for (pos = 0; pos != list->size; ++pos)
    {
        di_init(&info);
#ifdef DLMS_IGNORE_MALLOC
        if ((ret = arr_getByIndex(list, pos, (void**)&it, sizeof(gxListItem))) != 0)
        {
            break;
        }
#else
        if ((ret = arr_getByIndex(list, pos, (void**)&it)) != 0)
        {
            break;
        }
#endif //DLMS_IGNORE_MALLOC
        ret = bb_getUInt8(data, &ch);
        if (ret != 0)
        {
            break;
        }
        if (ch == 0)
        {
            if ((ret = dlms_getData(data, &info, &e.value)) != 0)
            {
                break;
            }
            e.target = (gxObject*)it->key;
            e.index = it->value;
            ret = cosem_setValue(settings, &e);
            ve_clear(&e);
            if (ret != 0)
            {
                break;
            }
        }
        else
        {
            ret = ch;
            break;
        }
    }
    ve_clear(&e);
    return ret;
}

int cl_receiverReady(dlmsSettings* settings, DLMS_DATA_REQUEST_TYPES type, gxByteBuffer* reply)
{
    return dlms_receiverReady(settings, type, reply);
}

/**
* Generates a release request.
*
* @return Release request, as byte array.
*/
int cl_releaseRequest(dlmsSettings* settings, message* packets)
{
    int ret;
    gxByteBuffer bb;
    mes_clear(packets);
    // If connection is not established, there is no need to send
    // DisconnectRequest.
    if (settings->connected != DLMS_CONNECTION_STATE_DLMS)
    {
        settings->connected &= ~DLMS_CONNECTION_STATE_DLMS;
        return 0;
    }
    settings->connected &= ~DLMS_CONNECTION_STATE_DLMS;
    bb_init(&bb);
    // Length.
    if ((ret = bb_setUInt8(&bb, 0x0)) != 0 ||
        (ret = bb_setUInt8(&bb, 0x80)) != 0 ||
        (ret = bb_setUInt8(&bb, 0x01)) != 0 ||
        (ret = bb_setUInt8(&bb, 0x0)) != 0)
    {
        return ret;
    }
#ifndef DLMS_IGNORE_HIGH_GMAC
    if (isCiphered(&settings->cipher))
    {
        ++settings->cipher.invocationCounter;
    }
#endif //DLMS_IGNORE_HIGH_GMAC
    apdu_generateUserInformation(settings, &bb);
    bb.data[0] = (unsigned char)(bb.size - 1);
    if (settings->useLogicalNameReferencing)
    {
        gxLNParameters p;
        params_initLN(&p, settings, 0,
            DLMS_COMMAND_RELEASE_REQUEST, DLMS_SET_COMMAND_TYPE_NORMAL,
            &bb, NULL, 0xff, DLMS_COMMAND_NONE, 0, 0);
        ret = dlms_getLnMessages(&p, packets);
    }
#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
    else
    {
        gxSNParameters p;
        params_initSN(&p, settings,
            DLMS_COMMAND_RELEASE_REQUEST, 1,
            DLMS_VARIABLE_ACCESS_SPECIFICATION_VARIABLE_NAME,
            NULL, &bb, DLMS_COMMAND_NONE);
        ret = dlms_getSnMessages(&p, packets);
}
#else
    ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
#endif //DLMS_IGNORE_ASSOCIATION_SHORT_NAME
    bb_clear(&bb);
    return ret;
}

int cl_disconnectRequest(dlmsSettings* settings, message* packets)
{
    int ret = 0;
#ifndef DLMS_IGNORE_WRAPPER
    gxByteBuffer bb;
#endif //DLMS_IGNORE_WRAPPER
    gxByteBuffer* reply = NULL;
    mes_clear(packets);
    settings->maxPduSize = 0xFFFF;
    // If connection is not established, there is no need to send DisconnectRequest.
    if ((settings->connected & DLMS_CONNECTION_STATE_HDLC) == 0)
    {
        return ret;
    }
    settings->connected &= ~DLMS_CONNECTION_STATE_HDLC;
#ifdef DLMS_IGNORE_MALLOC
    reply = packets->data[0];
    ++packets->size;
    bb_clear(reply);
#else
    reply = (gxByteBuffer*)gxmalloc(sizeof(gxByteBuffer));
    bb_init(reply);
#endif //DLMS_IGNORE_MALLOC
    if (settings->interfaceType == DLMS_INTERFACE_TYPE_HDLC)
    {
        ret = dlms_getHdlcFrame(settings, DLMS_COMMAND_DISC, NULL, reply);
#ifndef DLMS_IGNORE_MALLOC
        if (ret == 0)
        {
            mes_push(packets, reply);
        }
        else
        {
            gxfree(reply);
        }
#endif //DLMS_IGNORE_MALLOC
        return ret;
    }
#ifndef DLMS_IGNORE_WRAPPER
    bb_init(&bb);
    bb_setUInt8(&bb, DLMS_COMMAND_RELEASE_REQUEST);
    bb_setUInt8(&bb, 0x0);
    ret = dlms_getWrapperFrame(settings, &bb, reply);
#ifndef DLMS_IGNORE_MALLOC
    if (ret == 0)
    {
        mes_push(packets, reply);
    }
    else
    {
        gxfree(reply);
    }
#endif //DLMS_IGNORE_MALLOC
    bb_clear(&bb);
#endif //DLMS_IGNORE_WRAPPER
    return ret;
}

int cl_write(
    dlmsSettings* settings,
    gxObject* object,
    unsigned char index,
    message* messages)
{
    unsigned int ret;
    gxValueEventArg e;
    ve_init(&e);
    e.target = object;
    e.index = index;
    if ((ret = cosem_getValue(settings, &e)) != 0)
    {
        return ret;
    }
    if (settings->useLogicalNameReferencing)
    {
        ret = cl_writeLN(
            settings,
            object->logicalName,
            object->objectType,
            index,
            &e.value,
            e.byteArray,
            messages);
    }
    else
    {
#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
        ret = cl_writeSN(
            settings,
            object->shortName,
            index,
            &e.value,
            messages);
#endif //DLMS_IGNORE_ASSOCIATION_SHORT_NAME
    }
    ve_clear(&e);
    return ret;
}

int cl_writeLN(
    dlmsSettings* settings,
    unsigned char* name,
    DLMS_OBJECT_TYPE objectType,
    unsigned char index,
    dlmsVARIANT* value,
    unsigned char byteArray,
    message* messages)
{
    int ret;
    gxLNParameters p;
    gxByteBuffer* pdu;
    gxByteBuffer data;
    if (index < 1)
    {
        //Invalid parameter
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
#ifdef DLMS_IGNORE_MALLOC
    if (settings->serializedPdu == NULL)
    {
        //Invalid parameter
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    pdu = settings->serializedPdu;
    //Use same buffer for header and data. Header size is 10 bytes.
    bb_init(&data);
    bb_clear(pdu);
#else
    gxByteBuffer bb;
    bb_init(&bb);
    pdu = &bb;
    bb_init(&data);
#endif //DLMS_IGNORE_MALLOC
    resetBlockIndex(settings);
    // Add CI.
    bb_setUInt16(pdu, objectType);
    // Add LN
    bb_set(pdu, name, 6);
    // Attribute ID.
    bb_setUInt8(pdu, index);
    // Access selection is not used.
    bb_setUInt8(pdu, 0);
#ifdef DLMS_IGNORE_MALLOC
    if (byteArray != 0)
    {
        bb_set2(pdu, value->byteArr, 0, value->byteArr->size);
}
    else
    {
        if ((ret = dlms_setData(pdu, value->vt, value)) != 0)
        {
            return ret;
        }
    }
#else
    if (byteArray != 0)
    {
        bb_set2(&data, value->byteArr, 0, value->byteArr->size);
    }
    else
    {
        if ((ret = dlms_setData(&data, value->vt, value)) != 0)
        {
            return ret;
        }
    }
#endif //DLMS_IGNORE_MALLOC

    params_initLN(&p, settings, 0,
        DLMS_COMMAND_SET_REQUEST, DLMS_SET_COMMAND_TYPE_NORMAL,
        pdu, &data, 0xff, DLMS_COMMAND_NONE, 0, 0);
    ret = dlms_getLnMessages(&p, messages);
    bb_clear(pdu);
    return ret;
}

#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
int cl_writeSN(
    dlmsSettings* settings,
    unsigned short address,
    int index,
    dlmsVARIANT* value,
    message* messages)
{
    int ret;
    gxSNParameters p;
    gxByteBuffer bb, data;
    if (index < 1)
    {
        //Invalid parameter
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    resetBlockIndex(settings);
    bb_init(&bb);
    bb_init(&data);
    if ((ret = dlms_setData(&data, value->vt, value)) != 0)
    {
        return ret;
    }

    // Add name.
    address += (unsigned short)((index - 1) * 8);
    bb_setUInt16(&bb, address);
    // Add data count.
    bb_setUInt8(&bb, 1);
    params_initSN(&p, settings,
        DLMS_COMMAND_WRITE_REQUEST, 1,
        DLMS_VARIABLE_ACCESS_SPECIFICATION_VARIABLE_NAME,
        &bb, &data, DLMS_COMMAND_NONE);
    ret = dlms_getSnMessages(&p, messages);
    bb_clear(&data);
    bb_clear(&bb);
    return ret;
}

#endif //DLMS_IGNORE_ASSOCIATION_SHORT_NAME

int cl_method(
    dlmsSettings* settings,
    gxObject* object,
    unsigned char index,
    dlmsVARIANT* data,
    message* messages)
{
    int ret;
    if (settings->useLogicalNameReferencing)
    {
        ret = cl_methodLN(settings, object->logicalName, object->objectType, index, data, messages);
}
    else
    {
#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
        ret = cl_methodSN(settings, object->shortName, object->objectType, index, data, messages);
#else
        ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
#endif //DLMS_IGNORE_ASSOCIATION_SHORT_NAME
    }
    return ret;
    }

int cl_methodLN(
    dlmsSettings* settings,
    unsigned char* name,
    DLMS_OBJECT_TYPE objectType,
    unsigned char index,
    dlmsVARIANT* value,
    message* messages)
{
    int ret = 0;
    gxLNParameters p;
    gxByteBuffer* pdu;
    gxByteBuffer data;
    if (index < 1)
    {
        //Invalid parameter
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
#ifdef DLMS_IGNORE_MALLOC
    if (settings->serializedPdu == NULL)
    {
        //Invalid parameter
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    pdu = settings->serializedPdu;
    //Use same buffer for header and data. Header size is 10 bytes.
    bb_init(&data);
    bb_clear(pdu);
#else
    gxByteBuffer bb;
    bb_init(&bb);
    pdu = &bb;
    bb_init(&data);
#endif //DLMS_IGNORE_MALLOC
    resetBlockIndex(settings);
    // CI
    if ((ret = bb_setUInt16(pdu, objectType)) == 0 &&
        // Add LN
        (ret = bb_set(pdu, name, 6)) == 0 &&
        // Attribute ID.
        (ret = bb_setUInt8(pdu, index)) == 0 &&
        // Is Method Invocation Parameters used.
        (ret = bb_setUInt8(pdu, value == NULL || value->vt == DLMS_DATA_TYPE_NONE ? 0 : 1)) == 0)
    {
#ifdef DLMS_IGNORE_MALLOC
        if (value != NULL && value->vt != DLMS_DATA_TYPE_NONE)
        {
            if (value->vt == DLMS_DATA_TYPE_OCTET_STRING)
            {
                ret = bb_set(pdu, value->byteArr->data, value->byteArr->size);
            }
            else
            {
                ret = dlms_setData(pdu, value->vt, value);
            }
}
#else
        if (value != NULL && value->vt != DLMS_DATA_TYPE_NONE)
        {
            if (value->vt == DLMS_DATA_TYPE_OCTET_STRING)
            {
                ret = bb_set(&data, value->byteArr->data, value->byteArr->size);
            }
            else
            {
                ret = dlms_setData(&data, value->vt, value);
            }
        }
#endif //DLMS_IGNORE_MALLOC
    }
    if (ret == 0)
    {
        params_initLN(&p, settings, 0,
            DLMS_COMMAND_METHOD_REQUEST, DLMS_ACTION_COMMAND_TYPE_NORMAL,
            pdu, &data, 0xff, DLMS_COMMAND_NONE, 0, 0);
        ret = dlms_getLnMessages(&p, messages);
    }
    bb_clear(&data);
    bb_clear(pdu);
    return ret;
}

#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
int cl_methodSN(
    dlmsSettings* settings,
    unsigned short address,
    DLMS_OBJECT_TYPE objectType,
    int index,
    dlmsVARIANT* value,
    message* messages)
{
    int ret;
    unsigned char v, count;
    gxSNParameters p;
    unsigned char requestType;
    gxByteBuffer bb, data;
    if (index < 1)
    {
        //Invalid parameter
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    resetBlockIndex(settings);
    bb_init(&data);
    if (value != NULL && value->vt != DLMS_DATA_TYPE_NONE)
    {
        if (value->vt == DLMS_DATA_TYPE_OCTET_STRING)
        {
            bb_set(&data, value->byteArr->data, value->byteArr->size);
        }
        else
        {
            dlms_setData(&data, value->vt, value);
        }
    }
    bb_init(&bb);
    if (value == NULL || value->vt == DLMS_DATA_TYPE_NONE)
    {
        requestType = DLMS_VARIABLE_ACCESS_SPECIFICATION_VARIABLE_NAME;
    }
    else
    {
        requestType = DLMS_VARIABLE_ACCESS_SPECIFICATION_PARAMETERISED_ACCESS;
    }
    if ((ret = dlms_getActionInfo(objectType, &v, &count)) != 0)
    {
        return ret;
    }
    if (index > count)
    {
        //Invalid parameter
        bb_clear(&data);
        bb_clear(&bb);
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    index = (v + (index - 1) * 0x8);
    address += (unsigned short)index;
    // Add SN count.
    bb_setUInt8(&bb, 1);
    // Add name length.
    bb_setUInt8(&bb, 4);
    // Add name.
    bb_setUInt16(&bb, address);
    // Method Invocation Parameters is not used.
    if (value == NULL || value->vt == DLMS_DATA_TYPE_NONE)
    {
        bb_setUInt8(&bb, 0);
    }
    else
    {
        bb_setUInt8(&bb, 1);
    }
    params_initSN(&p, settings, DLMS_COMMAND_READ_REQUEST, 1,
        requestType, &bb, &data, DLMS_COMMAND_NONE);
    ret = dlms_getSnMessages(&p, messages);
    bb_clear(&data);
    bb_clear(&bb);
    return ret;
}

#endif //DLMS_IGNORE_ASSOCIATION_SHORT_NAME
#endif //!defined(DLMS_IGNORE_CLIENT)
