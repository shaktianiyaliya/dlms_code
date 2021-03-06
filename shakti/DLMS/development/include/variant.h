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

#ifndef VARIANT_H
#define VARIANT_H

#ifdef  __cplusplus
extern "C" {
#endif
#include "gxignore.h"
#include "date.h"
#include "enums.h"
#include "errorcodes.h"
#include "bytebuffer.h"
#include "bitarray.h"
#if _MSC_VER > 1400
#pragma warning(disable : 4201)
#endif

#define VARIANT_ARRAY_CAPACITY 10

#define GET_DLMS_TYPE()
#define V_VT(X)         ((X)->vt)
#define GX_UNION(X, Y, Z, S, C)  (X)->size=S;(X)->capacity=C;V_VT(X)=Z;(X)->Y
#define GX_UINT8(X) GX_UNION(&X, bVal, DLMS_DATA_TYPE_UINT8, 0, 0)
#define GX_UINT16(X) GX_UNION(&X, uiVal, DLMS_DATA_TYPE_UINT16, 0, 0)
#define GX_UINT32(X) GX_UNION(&X, ulVal, DLMS_DATA_TYPE_UINT32, 0, 0)
#define GX_UINT64(X) GX_UNION(&X, ullVal, DLMS_DATA_TYPE_UINT64, 0, 0)
#define GX_INT8(X) GX_UNION(&X, cVal, DLMS_DATA_TYPE_INT8, 0, 0)
#define GX_INT16(X) GX_UNION(&X, iVal, DLMS_DATA_TYPE_INT16, 0, 0)
#define GX_INT32(X) GX_UNION(&X, lVal, DLMS_DATA_TYPE_INT32, 0, 0)
#define GX_INT64(X) GX_UNION(&X, llVal, DLMS_DATA_TYPE_INT64, 0, 0)
#define GX_FLOAT(X) GX_UNION(&X, fltVal, DLMS_DATA_TYPE_FLOAT32, 0, 0)
#define GX_DOUBLE(X) GX_UNION(&X, dblVal, DLMS_DATA_TYPE_FLOAT64, 0, 0)
#define GX_DATETIME(X) GX_UNION(&X, pVal, (DLMS_DATA_TYPE)(DLMS_DATA_TYPE_BYREF | DLMS_DATA_TYPE_DATETIME), 0, 0)
#define GX_DATE(X) GX_UNION(&X, pVal, (DLMS_DATA_TYPE)(DLMS_DATA_TYPE_BYREF | DLMS_DATA_TYPE_DATE), 0, 0)
#define GX_TIME(X) GX_UNION(&X, pVal, (DLMS_DATA_TYPE)(DLMS_DATA_TYPE_BYREF | DLMS_DATA_TYPE_TIME), 0, 0)
#define GX_UINT8_BYREF(X) GX_UNION(&X, pbVal, (DLMS_DATA_TYPE)(DLMS_DATA_TYPE_BYREF | DLMS_DATA_TYPE_UINT8), 0, 0)
#define GX_UINT16_BYREF(X) GX_UNION(&X, puiVal, (DLMS_DATA_TYPE)(DLMS_DATA_TYPE_BYREF | DLMS_DATA_TYPE_UINT16), 0, 0)
#define GX_UINT32_BYREF(X) GX_UNION(&X, pulVal, (DLMS_DATA_TYPE)(DLMS_DATA_TYPE_BYREF | DLMS_DATA_TYPE_UINT32), 0, 0)
#define GX_UINT64_BYREF(X) GX_UNION(&X, pullVal, (DLMS_DATA_TYPE)(DLMS_DATA_TYPE_BYREF | DLMS_DATA_TYPE_UINT64), 0, 0)
#define GX_INT8_BYREF(X) GX_UNION(&X, pcVal, (DLMS_DATA_TYPE)(DLMS_DATA_TYPE_BYREF | DLMS_DATA_TYPE_INT8), 0, 0)
#define GX_INT16_BYREF(X) GX_UNION(&X, piVal, (DLMS_DATA_TYPE)(DLMS_DATA_TYPE_BYREF | DLMS_DATA_TYPE_INT16), 0, 0)
#define GX_INT32_BYREF(X) GX_UNION(&X, plVal, (DLMS_DATA_TYPE)(DLMS_DATA_TYPE_BYREF | DLMS_DATA_TYPE_INT32), 0, 0)
#define GX_INT64_BYREF(X) GX_UNION(&X, pllVal, (DLMS_DATA_TYPE)(DLMS_DATA_TYPE_BYREF | DLMS_DATA_TYPE_INT64), 0, 0)
#define GX_FLOAT_BYREF(X) GX_UNION(&X, pfltVal, (DLMS_DATA_TYPE)(DLMS_DATA_TYPE_BYREF | DLMS_DATA_TYPE_FLOAT32), 0, 0)
#define GX_DOUBLE_BYREF(X) GX_UNION(&X, pdblVal, (DLMS_DATA_TYPE)(DLMS_DATA_TYPE_BYREF | DLMS_DATA_TYPE_FLOAT64), 0, 0)
#define GX_OCTECT_STRING(X, VALUE_, SIZE_) GX_UNION(&X, pVal = VALUE_, (DLMS_DATA_TYPE) (DLMS_DATA_TYPE_BYREF | DLMS_DATA_TYPE_OCTET_STRING), SIZE_, sizeof(VALUE_)/sizeof(VALUE_[0]))
#define GX_STRING(X, VALUE_, SIZE_) GX_UNION(&X, pVal = VALUE_, (DLMS_DATA_TYPE)(DLMS_DATA_TYPE_BYREF | DLMS_DATA_TYPE_STRING), SIZE_, sizeof(VALUE_)/sizeof(VALUE_[0]))
#define GX_ARRAY(X, VALUE_, SIZE_) GX_UNION(&X, pVal = VALUE_, (DLMS_DATA_TYPE)(DLMS_DATA_TYPE_BYREF | DLMS_DATA_TYPE_ARRAY), SIZE_, sizeof(VALUE_)/sizeof(VALUE_[0]))
#define GX_STRUCT(X, VALUE_, SIZE_) GX_UNION(&X, pVal = VALUE_, (DLMS_DATA_TYPE)(DLMS_DATA_TYPE_BYREF | DLMS_DATA_TYPE_STRUCTURE), SIZE_, 1)

    typedef struct
    {
#ifdef DLMS_IGNORE_MALLOC
        void* data;
#else
        void** data;
#endif //DLMS_IGNORE_MALLOC
        unsigned short capacity;
        unsigned short size;
    } variantArray;

    typedef struct tagdlmsVARIANT
    {
        DLMS_DATA_TYPE vt;
        union
        {
            unsigned char bVal;
            signed char cVal;
            short iVal;
            long lVal;
            long long llVal;
#ifndef DLMS_IGNORE_FLOAT32
            float fltVal;
#endif //DLMS_IGNORE_FLOAT32
#ifndef DLMS_IGNORE_FLOAT64
            double dblVal;
#endif //DLMS_IGNORE_FLOAT64
            unsigned char boolVal;
            unsigned short uiVal;
            unsigned long ulVal;
            unsigned long long ullVal;
#ifndef DLMS_IGNORE_MALLOC
            gxtime* dateTime;
            gxByteBuffer* strVal;
            gxByteBuffer* strUtfVal;
            bitArray* bitArr;
#endif //DLMS_IGNORE_MALLOC
            variantArray* Arr;
            gxByteBuffer* byteArr;
            unsigned char* pbVal;
            signed char* pcVal;
            short* piVal;
            long* plVal;
            long long* pllVal;
            float* pfltVal;
            double* pdblVal;
            unsigned char* pboolVal;
            unsigned short* puiVal;
            unsigned long* pulVal;
            unsigned long long* pullVal;
            void* pVal;
        };
#ifdef DLMS_IGNORE_MALLOC
        unsigned short size;
        unsigned short capacity;
#endif //DLMS_IGNORE_MALLOC
    } dlmsVARIANT;


#ifdef DLMS_IGNORE_MALLOC
    typedef dlmsVARIANT* dlmsVARIANT_PTR;
#else
    typedef dlmsVARIANT* dlmsVARIANT_PTR;
#endif //DLMS_IGNORE_MALLOC

    //Initialize variantArray.
    void va_init(
        variantArray* arr);

#ifdef DLMS_IGNORE_MALLOC
    void va_attach(
        variantArray* trg,
        dlmsVARIANT* src,
        unsigned short size,
        unsigned short capacity);
#endif //DLMS_IGNORE_MALLOC

    void va_attach2(
        variantArray* trg,
        variantArray* src);

    //Is variant array attached.
    char va_isAttached(variantArray* arr);

    ///Get variant array capacity.
    unsigned short va_getCapacity(
        variantArray* arr);


    //Allocate new size for the array in bytes.
    int va_capacity(
        variantArray* arr,
        unsigned short capacity);

    //Push new data to the variantArray.
    int va_push(
        variantArray* arr,
        dlmsVARIANT* item);

    void va_clear(
        variantArray* arr);

    //Set byte value to variant.
    int var_setUInt8(
        dlmsVARIANT* data,
        unsigned char value);

    //Set UInt16 value to variant.
    int var_setUInt16(
        dlmsVARIANT* data,
        unsigned short value);

    //Set UInt32 value to variant.
    int var_setUInt32(dlmsVARIANT
        * data,
        unsigned long value);

    //Set UInt64 value to variant.
    int var_setUInt64(
        dlmsVARIANT* data,
        unsigned long long value);

    //Set signed byte value to variant.
    int var_setInt8(
        dlmsVARIANT* data,
        char value);

    //Set Int16 value to variant.
    int var_setInt16(
        dlmsVARIANT* data,
        short value);

    //Set Int32 value to variant.
    int var_setInt32(
        dlmsVARIANT* data,
        long value);

    //Set Int64 value to variant.
    int var_setInt64(
        dlmsVARIANT* data,
        long long value);

#ifndef DLMS_IGNORE_FLOAT64
    int var_setDouble(
        dlmsVARIANT* data,
        double value);
#endif //DLMS_IGNORE_FLOAT64

#ifndef DLMS_IGNORE_MALLOC
    int var_setDateTime(
        dlmsVARIANT* target,
        gxtime* value);

    int var_setDate(
        dlmsVARIANT* target,
        gxtime* value);

    int var_setTime(
        dlmsVARIANT* target,
        gxtime* value);

#endif //DLMS_IGNORE_MALLOC
    int var_setBoolean(
        dlmsVARIANT* target,
        char value);

    int var_getDateTime(
        dlmsVARIANT* target,
        gxtime* value);

    int var_getDateTime2(
        gxtime* dateTime,
        gxByteBuffer* ba);

    int var_getDate(
        gxtime* date,
        gxByteBuffer* ba);

    int var_getTime(
        gxtime* date,
        gxByteBuffer* ba);

    int var_setDateTimeAsOctetString(
        dlmsVARIANT* target,
        gxtime* value);

    int var_setDateAsOctetString(
        dlmsVARIANT* target,
        gxtime* value);

    int var_setTimeAsOctetString(
        dlmsVARIANT* target,
        gxtime* value);

    //Get byte value from variant.
    int var_getUInt8(
        dlmsVARIANT* data,
        unsigned char* value);

    //Get UInt16 value from variant.
    int var_getUInt16(
        dlmsVARIANT* data,
        unsigned short* value);

    //Get UInt32 value from variant.
    int var_getUInt32(
        dlmsVARIANT* data,
        unsigned long* value);

    //Get UInt64 value from variant.
    int var_getUInt64(
        dlmsVARIANT* data,
        unsigned long long* value);

    //Get signed byte value from variant.
    int var_getInt8(
        dlmsVARIANT* data,
        char* value);

    //Get Int16 value from variant.
    int var_getInt16(
        dlmsVARIANT* data,
        short* value);

    //Get Int32 value from variant.
    int var_getInt32(
        dlmsVARIANT* data,
        long* value);

    //Get Int64 value from variant.
    int var_getInt64(
        dlmsVARIANT* data,
        long long* value);

#ifndef DLMS_IGNORE_MALLOC
    int var_addBytes(
        dlmsVARIANT* data,
        const unsigned char* value,
        unsigned short count);
#endif //DLMS_IGNORE_MALLOC

#ifndef DLMS_IGNORE_MALLOC
    int var_setString(
        dlmsVARIANT* data,
        const char* value,
        unsigned short count);
#endif //DLMS_IGNORE_MALLOC

#ifndef DLMS_IGNORE_MALLOC
    void var_attach(
        dlmsVARIANT* target,
        gxByteBuffer* source);
#endif //DLMS_IGNORE_MALLOC

    int var_addOctetString(
        dlmsVARIANT* data,
        gxByteBuffer* ba);

    int var_setEnum(dlmsVARIANT* data,
        unsigned char value);

    int var_addByteArray(
        dlmsVARIANT* data,
        gxByteBuffer* ba,
        unsigned short index,
        unsigned short count);

    //Initialize variant.
    int var_init(
        dlmsVARIANT* data);

#ifndef DLMS_IGNORE_MALLOC
    //attach static array.
    void var_attachArray(
        dlmsVARIANT* data,
        const variantArray* arr,
        const unsigned short count);
#endif //DLMS_IGNORE_MALLOC

#ifndef DLMS_IGNORE_MALLOC
    //attach static structure.
    void var_attachStructure(
        dlmsVARIANT* data,
        const dlmsVARIANT** arr,
        const unsigned short count);
#endif //DLMS_IGNORE_MALLOC

    //copy variant.
    int var_copy(
        dlmsVARIANT* value,
        dlmsVARIANT* copy);

    //Clear variant.
    int var_clear(
        dlmsVARIANT* data);

    //Get bytes from variant value.
    int var_getBytes(
        dlmsVARIANT* data,
        gxByteBuffer* ba);

    //Get bytes from variant value.
    int var_getBytes2(
        dlmsVARIANT* data,
        DLMS_DATA_TYPE type,
        gxByteBuffer* ba);

    //Get size in bytes.
    int var_getSize(
        DLMS_DATA_TYPE vt);

    //Convert variant value to integer.
    int var_toInteger(
        dlmsVARIANT* data);

    //Get item from variant array by index.
    int va_getByIndex(
        variantArray* arr,
        int index,
        dlmsVARIANT_PTR* item);

#ifndef DLMS_IGNORE_MALLOC
    //copy variant array.
    int va_copyArray(
        variantArray* target,
        variantArray* source);
#endif //DLMS_IGNORE_MALLOC

#ifndef DLMS_IGNORE_MALLOC
    int var_changeType(
        dlmsVARIANT* value,
        DLMS_DATA_TYPE newType);
#endif //DLMS_IGNORE_MALLOC

#ifndef DLMS_IGNORE_MALLOC
    //Convert variant to string.
    //Note! toString do not clear existing byte array.
    int var_toString(
        dlmsVARIANT* item,
        gxByteBuffer* value);

    //Convert variant array to string.
    //Note! toString do not clear existing byte array.
    int va_toString(
        variantArray* items,
        gxByteBuffer* ba);

#endif //DLMS_IGNORE_MALLOC
    //Convert variant to double.
    double var_toDouble(
        dlmsVARIANT* target);

#ifdef DLMS_IGNORE_MALLOC
    //Attach value by ref.
    int var_byRef(
        dlmsVARIANT* target,
        DLMS_DATA_TYPE type,
        void* value);
#endif //DLMS_IGNORE_MALLOC

#ifndef GX_DLMS_MICROCONTROLLER
    //Print content of the variant to cout.
    int var_print(
        //Format.
        const char* format,
        dlmsVARIANT* target);

    //Print content of the variant array to cout.
    int va_print(
        variantArray* target);

#endif //GX_DLMS_MICROCONTROLLER

#define VA_ATTACH(X, V, S) va_attach(&X, V, S, sizeof(V)/sizeof(V[0]))

#ifdef  __cplusplus
}
#endif

#endif //VARIANT_H
