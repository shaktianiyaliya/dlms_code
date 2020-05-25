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
#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
#include <assert.h>
#endif
#include <time.h>
#include <string.h>

#ifndef GX_DLMS_MICROCONTROLLER
#include <stdio.h> //printf needs this or error is generated.
#endif //GX_DLMS_MICROCONTROLLER

#include "../include/gxmem.h"
#if _MSC_VER > 1400
#include <crtdbg.h>
#endif
#include "../include/date.h"

#ifndef DLMS_USE_EPOCH_TIME
//Get UTC offset in minutes.
void time_getUtcOffset(short* hours, short* minutes)
{
    time_t zero = 24 * 60 * 60L;
    struct tm tm;

    // local time for Jan 2, 1900 00:00 UTC
#if _MSC_VER > 1000
    localtime_s(&tm, &zero);
#else
    tm = *localtime(&zero);
#endif
    * hours = (short)tm.tm_hour;

    //If the local time is the "day before" the UTC, subtract 24 hours from the hours to get the UTC offset
    if (tm.tm_mday < 2)
    {
        *hours -= 24;
    }
    *minutes = (short)tm.tm_min;
}

void time_init3(
    gxtime* time,
    int year,
    int month,
    int day,
    int hour,
    int minute,
    int second,
    int millisecond)
{
    short devitation, hours, minutes;
    time_getUtcOffset(&hours, &minutes);
    devitation = -(hours * 60 + minutes);
    time_init(time, year, month, day, hour, minute, second, millisecond, devitation);
}
#endif //DLMS_USE_EPOCH_TIME

#ifndef DLMS_USE_EPOCH_TIME
time_t gxmktime(struct tm* value)
{
    struct tm orig = *value;
    time_t ret;
    if ((ret = mktime(value)) == (time_t)-1)
    {
        return ret;
    }
    if (value->tm_isdst == 1)
    {
        *value = orig;
        value->tm_isdst = 1;
        if ((ret = mktime(value)) == (time_t)-1)
        {
            return ret;
        }
        value->tm_isdst = 0;
    }
    return ret;
}
#endif //DLMS_USE_EPOCH_TIME

// Constructor.
void time_init(
    gxtime* time,
    uint16_t year,
    unsigned char month,
    unsigned char day,
    unsigned char hour,
    unsigned char minute,
    unsigned char second,
    uint16_t millisecond,
    signed short devitation)
{
    if (devitation == -1)
    {
        devitation = 0x8000;
    }
#ifdef DLMS_USE_EPOCH_TIME
    //multiply to tmp variable or it'll fails for some compilers.
    uint32_t tmp;
    //January and February are counted as months 13 and 14 of the previous year
    if (month != 0xFF && month <= 2)
    {
        month += 12;
        year -= 1;
    }
    time->skip = DATETIME_SKIPS_NONE;
    time->status = DLMS_CLOCK_STATUS_OK;
    time->extraInfo = 0;
    //Convert years to days
    time->value = 0;
    if (year == 0xFFFF)
    {
        time->skip = (unsigned char)(DATETIME_SKIPS_YEAR | DATETIME_SKIPS_DEVITATION);
        year = 1970;
    }
    time->value = year;
    time->value *= 365L;
    tmp = year;
    tmp /= 4L;
    time->value += tmp;
    tmp = year;
    tmp /= 100L;
    time->value -= tmp;
    tmp = year;
    tmp /= 400L;
    time->value += tmp;
    //Convert months to days
    if (month == 0xFF)
    {
        time->skip |= DATETIME_SKIPS_MONTH | DATETIME_SKIPS_DEVITATION;
        month = 1;
    }
    else if (month == 0xFE)
    {
        time->extraInfo = DLMS_DATE_TIME_EXTRA_INFO_DST_BEGIN;
        month = 1;
    }
    else if (month == 0xFD)
    {
        time->extraInfo = DLMS_DATE_TIME_EXTRA_INFO_DST_END;
        month = 1;
    }
    if (day == 0xFF)
    {
        time->skip |= DATETIME_SKIPS_DAY | DATETIME_SKIPS_DEVITATION;
        day = 1;
    }
    else if (day == 0xFE)
    {
        time->extraInfo = DLMS_DATE_TIME_EXTRA_INFO_LAST_DAY;
        day = 1;
    }
    else if (day == 0xFD)
    {
        time->extraInfo = DLMS_DATE_TIME_EXTRA_INFO_LAST_DAY2;
        day = 1;
    }
    tmp = month;
    tmp *= 30L;
    time->value += tmp;
    tmp = 1 + month;
    tmp = tmp * 3L;
    tmp = tmp / 5L;
    time->value += tmp;
    time->value += day;
    //Unix time starts on January 1st, 1970
    if (time->value < 719561)
    {
        time->value = 0;
    }
    else
    {
        time->value -= 719561L;
    }
    //Convert days to seconds
    if (time->value != 0)
    {
        time->value *= 86400L;
    }
    //Add hours, minutes and seconds
    if (hour != 0xFF)
    {
        time->value += (3600L * hour);
    }
    else
    {
        time->skip |= DATETIME_SKIPS_HOUR;
    }
    if (minute != 0xFF)
    {
        time->value += (60L * minute);
    }
    else
    {
        time->skip |= DATETIME_SKIPS_MINUTE;
    }
    if (second != 0xFF)
    {
        time->value += second;
    }
    else
    {
        time->skip |= DATETIME_SKIPS_SECOND;
    }
    time->skip |= DATETIME_SKIPS_MS;
    if (devitation == (short)0x8000)
    {
        time->skip |= DATETIME_SKIPS_DEVITATION;
    }
    time->deviation = devitation;
#else
    int skip = DATETIME_SKIPS_NONE;
    memset(&time->value, 0, sizeof(time->value));
    time->extraInfo = 0;
    time->status = DLMS_CLOCK_STATUS_OK;
    if (year < 1 || year == 0xFFFF)
    {
        skip |= DATETIME_SKIPS_YEAR;
        year = 2000;
    }
    if (month == 0xFF)
    {
        skip |= DATETIME_SKIPS_MONTH;
        month = 0;
    }
    else
    {
        --month;
    }
    if (day == 0xFF)
    {
        skip |= DATETIME_SKIPS_DAY;
        day = 1;
    }
    else if (day == 0xFD)
    {
        day = date_daysInMonth(year, (short)month) - 1;
    }
    else if (day == 0xFE)
    {
        day = date_daysInMonth(year, (short)month);
    }
    if (hour == 0xFF)
    {
        skip |= DATETIME_SKIPS_HOUR;
        hour = 1;
    }
    if (minute == 0xFF)
    {
        skip |= DATETIME_SKIPS_MINUTE;
        minute = 0;
    }
    if (second == 0xFF)
    {
        skip |= DATETIME_SKIPS_SECOND;
        second = 0;
    }
    if (millisecond == 0xFFFF)
    {
        skip |= DATETIME_SKIPS_MS;
        millisecond = 0;
    }
    time->skip = (DATETIME_SKIPS)skip;
    if (year != 0)
    {
        time->value.tm_year = year - 1900;
    }
    time->value.tm_mon = month;
    time->value.tm_mday = day;
    time->value.tm_hour = hour;
    time->value.tm_min = minute;
    time->value.tm_sec = second;
    time->deviation = devitation;
    if (gxmktime(&time->value) == (time_t)-1)
    {
#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
        assert(0);
#endif
    }
#endif //DLMS_USE_EPOCH_TIME
}

void time_clearDate(
    gxtime* value)
{
#ifdef DLMS_USE_EPOCH_TIME
    //Get hours, minutes and seconds
    if (value->value > 60)
    {
        unsigned char seconds = value->value % 60;
        uint32_t t = value->value;
        t /= 60;
        unsigned char minutes = t % 60;
        t /= 60;
        unsigned char hours = t % 24;
        value->value = seconds;
        value->value += 60 * minutes;
        value->value += 3600 * hours;
    }
#else
    value->value.tm_year = value->value.tm_yday =
        value->value.tm_wday = value->value.tm_mon =
        value->value.tm_mday = value->value.tm_isdst = 0;
#endif
    value->skip &= ~(DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH | DATETIME_SKIPS_DAY | DATETIME_SKIPS_DAYOFWEEK | DATETIME_SKIPS_DEVITATION);
}

void time_clearTime(
    gxtime* value)
{
#ifdef DLMS_USE_EPOCH_TIME
    if (value->value != 0)
    {
        //Remove hours, minutes and seconds
        value->value -= value->value % 60;
        value->value -= (value->value / 60) % 60;
        value->value -= (value->value / 3600) % 24;
    }
#else
    value->value.tm_sec = value->value.tm_min = value->value.tm_hour = 0;
#endif
    value->skip &= ~(DATETIME_SKIPS_HOUR | DATETIME_SKIPS_MINUTE | DATETIME_SKIPS_SECOND | DATETIME_SKIPS_MS);
}

void time_clearHours(gxtime* value)
{
    time_addHours(value, -time_getHours(value));
}

void time_clearMinutes(gxtime* value)
{
    time_addMinutes(value, -time_getMinutes(value));
}

void time_clearSeconds(gxtime* value)
{
    time_addSeconds(value, -time_getSeconds(value));
}

uint16_t time_getYears(
    const gxtime* value)
{
#ifdef DLMS_USE_EPOCH_TIME
    uint32_t t = value->value;
    //remove hours, minutes and seconds
    t /= 86400;
    //Convert Unix time to date
    uint32_t a = (uint32_t)((4 * t + 102032) / 146097 + 15);
    uint32_t b = (uint32_t)(t + 2442113 + a - (a / 4));
    uint32_t c = (20 * b - 2442) / 7305;
    uint32_t d = b - 365 * c - (c / 4);
    uint32_t e = d * 1000 / 30601;
    //January and February are counted as months 13 and 14 of the previous year
    if (e <= 13)
    {
        c -= 4716;
        e -= 1;
    }
    else
    {
        c -= 4715;
        e -= 13;
    }
    return (uint16_t)c;
#else
    return 1900 + value->value.tm_year;
#endif // DLMS_USE_EPOCH_TIME
}

unsigned char time_getMonths(
    const gxtime* value)
{
#ifdef DLMS_USE_EPOCH_TIME
    uint32_t t = value->value;
    //remove hours, minutes and seconds
    t /= 86400;
    //Convert Unix time to date
    uint32_t a = (uint32_t)((4 * t + 102032) / 146097 + 15);
    uint32_t b = (uint32_t)(t + 2442113 + a - (a / 4));
    uint32_t c = (20 * b - 2442) / 7305;
    uint32_t d = b - 365 * c - (c / 4);
    uint32_t e = d * 1000 / 30601;
    //January and February are counted as months 13 and 14 of the previous year
    if (e <= 13)
    {
        c -= 4716;
        e -= 1;
    }
    else
    {
        c -= 4715;
        e -= 13;
    }
    return (unsigned char)e;
#else
    return 1 + value->value.tm_mon;
#endif // DLMS_USE_EPOCH_TIME
}

unsigned char time_getDays(
    const gxtime* value)
{
#ifdef DLMS_USE_EPOCH_TIME
    uint32_t t = value->value;
    //remove hours, minutes and seconds
    t /= 86400;
    //Convert Unix time to date
    uint32_t a = (uint32_t)((4 * t + 102032) / 146097 + 15);
    uint32_t b = (uint32_t)(t + 2442113 + a - (a / 4));
    uint32_t c = (20 * b - 2442) / 7305;
    uint32_t d = b - 365 * c - (c / 4);
    uint32_t e = d * 1000 / 30601;
    uint32_t f = d - e * 30 - e * 601 / 1000;
    return (unsigned char)f;
#else
    return value->value.tm_mday;
#endif // DLMS_USE_EPOCH_TIME
}

unsigned char time_getHours(
    const gxtime* value)
{
#ifdef DLMS_USE_EPOCH_TIME
    return (unsigned char)((value->value % 86400) / 3600);
#else
    return value->value.tm_hour;
#endif // DLMS_USE_EPOCH_TIME
}

unsigned char time_getMinutes(
    const gxtime* value)
{
#ifdef DLMS_USE_EPOCH_TIME
    return (unsigned char)((value->value % 3600) / 60);
#else
    return value->value.tm_min;
#endif // DLMS_USE_EPOCH_TIME
}

unsigned char time_getSeconds(
    const gxtime* value)
{
#ifdef DLMS_USE_EPOCH_TIME
    return (unsigned char)(value->value % 60);
#else
    return value->value.tm_sec;
#endif // DLMS_USE_EPOCH_TIME
}

void time_addDays(
    gxtime* value,
    int days)
{
#ifdef DLMS_USE_EPOCH_TIME
    time_addHours(value, 24 * days);
#else
    value->value.tm_mday += days;
    if (gxmktime(&value->value) == (time_t)-1)
    {
#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
        assert(0);
#endif
    }
#endif //DLMS_USE_EPOCH_TIME
}

void time_addHours(
    gxtime* value,
    int hours)
{
#ifdef DLMS_USE_EPOCH_TIME
    time_addMinutes(value, 60 * hours);
#else
    value->value.tm_hour += hours;
    if (gxmktime(&value->value) == (time_t)-1)
    {
        //If OS
#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
        assert(0);
#endif
    }
#endif //DLMS_USE_EPOCH_TIME
}

void time_addMinutes(
    gxtime* value,
    int minutes)
{
#ifdef DLMS_USE_EPOCH_TIME
    time_addSeconds(value, 60 * minutes);
#else
    value->value.tm_min += minutes;
    if (gxmktime(&value->value) == (time_t)-1)
    {
        //If OS
#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
        assert(0);
#endif
    }
#endif //DLMS_USE_EPOCH_TIME
}

void time_addSeconds(
    gxtime* value,
    int seconds)
{
#ifdef DLMS_USE_EPOCH_TIME
    value->value += seconds;
#else
    value->value.tm_sec += seconds;
    if (gxmktime(&value->value) == (time_t)-1)
    {
        //If OS
#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
        assert(0);
#endif
    }
#endif //DLMS_USE_EPOCH_TIME
}

#ifndef DLMS_USE_EPOCH_TIME
void time_init2(
    gxtime* time,
    struct tm* value)
{
#ifdef DLMS_USE_EPOCH_TIME
    uint16_t y;
    unsigned char m, d;
    //Year
    y = value->tm_year;
    //Month of year
    m = value->tm_mon;
    //Day of month
    d = value->tm_mday;

    //January and February are counted as months 13 and 14 of the previous year
    if (m <= 2)
    {
        m += 12;
        y -= 1;
    }

    //Convert years to days
    time->value = (365 * y) + (y / 4) - (y / 100) + (y / 400);
    //Convert months to days
    time->value += (30 * m) + (3 * (m + 1) / 5) + d;
    //Unix time starts on January 1st, 1970
    time->value -= 719561;
    //Convert days to seconds
    time->value *= 86400;
    //Add hours, minutes and seconds
    time->value += (3600 * value->tm_hour) + (60 * value->tm_min) + value->tm_sec;
#else
    short devitation, hours, minutes;
    time_getUtcOffset(&hours, &minutes);
    devitation = -(hours * 60 + minutes);
    time_init(time, value->tm_year + 1900, value->tm_mon + 1, value->tm_mday, value->tm_hour, value->tm_min,
        value->tm_sec, 0, devitation);
#endif //DLMS_USE_EPOCH_TIME
}
#endif //DLMS_USE_EPOCH_TIME

void time_initUnix(
    gxtime* time,
    uint32_t value)
{
    time->deviation = 0;
#ifdef DLMS_USE_EPOCH_TIME
    time->value = value;
#else
    time_fromUnixTime(value, &time->value);
    gxmktime(&time->value);
#endif //DLMS_USE_EPOCH_TIME
    time->extraInfo = 0;
    time->status = DLMS_CLOCK_STATUS_OK;
    time->skip = DATETIME_SKIPS_NONE;
}

void time_clear(
    gxtime* time)
{
#ifdef DLMS_USE_EPOCH_TIME
    time->value = 0;
#else
    memset(&time->value, 0, sizeof(struct tm));
#endif //DLMS_USE_EPOCH_TIME
    time->skip = DATETIME_SKIPS_NONE;
    time->extraInfo = 0;
    time->status = DLMS_CLOCK_STATUS_OK;
}

unsigned char date_daysInMonth(
    int year,
    short month)
{
    if (month == 0 || month == 2 || month == 4 ||
        month == 6 || month == 7 || month == 9 || month == 11)
    {
        return 31;
    }
    else if (month == 3 || month == 5 || month == 8 || month == 10)
    {
        return 30;
    }
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
            {
                return 29;
            }
            return 28;
        }
        return 29;
    }
    return 28;
}

//Constants for different orders of date components.
typedef enum
{
    GXDLMS_DATE_FORMAT_INVALID = -1,
    GXDLMS_DATE_FORMAT_DMY = 0,
    GXDLMS_DATE_FORMAT_MDY = 1,
    GXDLMS_DATE_FORMAT_YMD = 2,
    GXDLMS_DATE_FORMAT_YDM = 3
} GXDLMS_DATE_FORMAT;

#if !defined(GX_DLMS_MICROCONTROLLER)
int getDateFormat(GXDLMS_DATE_FORMAT* format, char* separator)
{
    //If OS is used.
#if defined(_WIN32) || defined(_WIN64) || defined(__linux__)
    int ret = 0, value, lastPos = 0, pos;
    char buff[10];
    struct tm order = { 0 };
    order.tm_year = 0;
    order.tm_mday = 1;
    order.tm_mon = 1;//Month is zero based.
    ret = (int)strftime(buff, 10, "%x", &order);
    if (ret > 0)
    {
        for (pos = 0; pos != ret; ++pos)
        {
            //If numeric value
            if (buff[pos] >= '0' && buff[pos] <= '9')
            {

            }
            else //If date time separator.
            {
                *separator = buff[pos];
#if _MSC_VER > 1000
                if (sscanf_s(buff + lastPos, "%d", &value) == 1)
#else
                if (sscanf(buff + lastPos, "%d", &value) == 1)
#endif
                {
                    if (value == 1)
                    {
                        *format = lastPos == 0 ? GXDLMS_DATE_FORMAT_DMY : GXDLMS_DATE_FORMAT_YDM;
                        break;
                    }
                    else if (value == 2)
                    {
                        *format = lastPos == 0 ? GXDLMS_DATE_FORMAT_MDY : GXDLMS_DATE_FORMAT_YMD;
                        break;
                    }
                }
                lastPos = pos + 1;
            }
        }
    }
    return 0;
#else
    * format = GXDLMS_DATE_FORMAT_MDY;
    *separator = '/';
    return 0;
#endif
}

int time_print(const char* format, gxtime* time)
{
    int ret;
    char buff[50];
    if ((ret = time_toString2(time, buff, 50)) != 0)
    {
        return ret;
    }
    if (format != NULL)
    {
        printf(format, buff);
    }
    else
    {
        printf(buff);
    }
    return 0;
}

int time_toString2(
    const gxtime* time,
    char* buff,
    uint16_t len)
{
    gxByteBuffer bb;
    bb_attach(&bb, (unsigned char*)buff, 0, len);
    return time_toString(time, &bb);
}

int time_toString(
    const gxtime* time,
    gxByteBuffer* ba)
{
    int ret = 0;
    GXDLMS_DATE_FORMAT format;
    char separator;
    uint16_t year = 0;
    unsigned char mon = 0, day = 0, hour = 0, min = 0, sec = 0;
#ifdef DLMS_USE_EPOCH_TIME
    time_fromUnixTime2(time->value, &year, &mon, &day, &hour, &min, &sec, NULL);
#else
    year = time->value.tm_year;
    if (year != -1)
    {
        year += 1900;
    }
    mon = time->value.tm_mon;
    if (year != -1)
    {
        mon += 1;
    }
    day = time->value.tm_mday;
    hour = time->value.tm_hour;
    min = time->value.tm_min;
    sec = time->value.tm_sec;
#endif //DLMS_USE_EPOCH_TIME
    //Add year, month and date if used.
    if ((time->skip & (DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH | DATETIME_SKIPS_DAY)) != (DATETIME_SKIPS_YEAR | DATETIME_SKIPS_MONTH | DATETIME_SKIPS_DAY))
    {
        if ((ret = getDateFormat(&format, &separator)) != 0)
        {
            return ret;
        }
        switch (format)
        {
        case GXDLMS_DATE_FORMAT_DMY:
        {
            if ((time->skip & DATETIME_SKIPS_DAY) == 0)
            {
                bb_addIntAsString2(ba, day, 2);
            }
            if ((time->skip & DATETIME_SKIPS_MONTH) == 0)
            {
                if (ba->size != 0)
                {
                    bb_setUInt8(ba, separator);
                }
                bb_addIntAsString2(ba, mon, 2);
            }
            if ((time->skip & DATETIME_SKIPS_YEAR) == 0)
            {
                if (ba->size != 0)
                {
                    bb_setUInt8(ba, separator);
                }
                bb_addIntAsString(ba, year);
            }
        }
        break;
        case GXDLMS_DATE_FORMAT_YMD:
        {
            if ((time->skip & DATETIME_SKIPS_YEAR) == 0)
            {
                bb_addIntAsString(ba, year);
            }
            if ((time->skip & DATETIME_SKIPS_MONTH) == 0)
            {
                if (ba->size != 0)
                {
                    bb_setUInt8(ba, separator);
                }
                bb_addIntAsString2(ba, mon, 2);
            }
            if ((time->skip & DATETIME_SKIPS_DAY) == 0)
            {
                if (ba->size != 0)
                {
                    bb_setUInt8(ba, separator);
                }
                bb_addIntAsString2(ba, day, 2);
            }
        }
        break;
        case GXDLMS_DATE_FORMAT_YDM:
        {
            if ((time->skip & DATETIME_SKIPS_YEAR) == 0)
            {
                bb_addIntAsString(ba, year);
            }
            if ((time->skip & DATETIME_SKIPS_DAY) == 0)
            {
                if (ba->size != 0)
                {
                    bb_setUInt8(ba, separator);
                }
                bb_addIntAsString2(ba, day, 2);
            }
            if ((time->skip & DATETIME_SKIPS_MONTH) == 0)
            {
                if (ba->size != 0)
                {
                    bb_setUInt8(ba, separator);
                }
                bb_addIntAsString2(ba, mon, 2);
            }
        }
        break;
        default: //GXDLMS_DATE_FORMAT_MDY
        {
            if ((time->skip & DATETIME_SKIPS_MONTH) == 0)
            {
                bb_addIntAsString2(ba, mon, 2);
            }
            if ((time->skip & DATETIME_SKIPS_DAY) == 0)
            {
                if (ba->size != 0)
                {
                    bb_setUInt8(ba, separator);
                }
                bb_addIntAsString2(ba, day, 2);
            }
            if ((time->skip & DATETIME_SKIPS_YEAR) == 0)
            {
                if (ba->size != 0)
                {
                    bb_setUInt8(ba, separator);
                }
                bb_addIntAsString(ba, year);
            }
        }
        break;
        }
    }
    //Add hours.
    if ((time->skip & DATETIME_SKIPS_HOUR) == 0)
    {
        if (ba->size != 0)
        {
            bb_setUInt8(ba, ' ');
        }
        bb_addIntAsString2(ba, hour, 2);
    }
    //Add minutes.
    if ((time->skip & DATETIME_SKIPS_MINUTE) == 0)
    {
        if (ba->size != 0)
        {
            bb_setUInt8(ba, ':');
        }
        bb_addIntAsString2(ba, min, 2);
    }
    //Add seconds.
    if ((time->skip & DATETIME_SKIPS_SECOND) == 0)
    {
        if (ba->size != 0)
        {
            bb_setUInt8(ba, ':');
        }
        bb_addIntAsString2(ba, sec, 2);
    }
    if (time->deviation != (short)0x8000)
    {
        short tmp = time->deviation;
#ifndef DLMS_USE_UTC_TIME_ZONE
        tmp = -tmp;
#endif //DLMS_USE_UTC_TIME_ZONE
        bb_addString(ba, " UTC");
        if (tmp < 0)
        {
            bb_addString(ba, "-");
        }
        else
        {
            bb_addString(ba, "+");
        }
        bb_addIntAsString2(ba, (int)(tmp / 60), 2);
        bb_addString(ba, ":");
        bb_addIntAsString2(ba, (int)(tmp % 60), 2);
    }
    //Add end of string, but that is not added to the length.
    bb_setUInt8(ba, '\0');
    --ba->size;
    return 0;
}
#endif //!defined(GX_DLMS_MICROCONTROLLER)

void time_copy(
    gxtime* trg,
    gxtime* src)
{
    trg->extraInfo = src->extraInfo;
    trg->skip = src->skip;
    trg->status = src->status;
    trg->value = src->value;
    trg->deviation = src->deviation;
}

void time_addTime(
    gxtime* time,
    int hours,
    int minutes,
    int seconds)
{
#ifdef DLMS_USE_EPOCH_TIME
    time_addHours(time, hours);
    time_addMinutes(time, minutes);
    time_addSeconds(time, seconds);
#else
    time->value.tm_hour += hours;
    time->value.tm_min += minutes;
    time->value.tm_sec += seconds;
    gxmktime(&time->value);
#endif // DLMS_USE_EPOCH_TIME
}

int time_compareWithDiff(
    gxtime* value1,
    uint32_t value2,
    short deviationDiff)
{
    if (value2 == 0xFFFFFFFF)
    {
        return 1;
    }
    uint16_t year1;
    unsigned char month1, day1, hour1, minute1, second1;
    uint16_t year2;
    unsigned char month2, day2, hour2, minute2, second2;
#ifdef DLMS_USE_EPOCH_TIME
    time_fromUnixTime2(value1->value, &year1, &month1,
        &day1, &hour1, &minute1, &second1, NULL);
#else
    year1 = 1900 + value1->value.tm_year;
    month1 = 1 + value1->value.tm_mon;
    day1 = value1->value.tm_mday;
    hour1 = value1->value.tm_hour;
    minute1 = value1->value.tm_min;
    second1 = value1->value.tm_sec;
#endif //DLMS_USE_EPOCH_TIME

    if (deviationDiff != (short)0x8000)
    {
#ifndef DLMS_USE_UTC_TIME_ZONE
        value2 += (60 * deviationDiff);
#else
        value2 -= (60 * deviationDiff);
#endif //DLMS_USE_UTC_TIME_ZONE
    }
    time_fromUnixTime2(value2, &year2, &month2,
        &day2, &hour2, &minute2, &second2, NULL);
    if (value1->skip != 0)
    {
        if ((value1->skip & DATETIME_SKIPS_SECOND) == 0)
        {
            if (second1 != second2)
            {
                return second1 < second2 ? -1 : 1;
            }
        }
        if ((value1->skip & DATETIME_SKIPS_MINUTE) == 0)
        {
            if (minute1 != minute2)
            {
                return minute1 < minute2 ? -1 : 1;
            }
        }
        if ((value1->skip & DATETIME_SKIPS_HOUR) == 0)
        {
            if (hour1 != hour2)
            {
                return hour1 < hour2 ? -1 : 1;
            }
        }
        if ((value1->skip & DATETIME_SKIPS_DAY) == 0)
        {
            if (day1 != day2)
            {
                return day1 < day2 ? -1 : 1;
            }
        }
        if ((value1->skip & DATETIME_SKIPS_MONTH) == 0)
        {
            if (month1 != month2)
            {
                return month1 < month2 ? -1 : 1;
            }
        }
        if ((value1->skip & DATETIME_SKIPS_YEAR) == 0)
        {
            if (year1 != year2)
            {
                return year1 < year2 ? -1 : 1;
            }
        }
        return 0;
    }
    if (value1->value == value2)
    {
        return 0;
    }
    return value1->value < value2 ? -1 : 1;
}

int time_compare2(
    gxtime* value1,
    uint32_t value2)
{
    return time_compareWithDiff(value1, value2, value1->deviation);
}

int time_compare(
    gxtime* value1,
    gxtime* value2)
{
    //Compare using UTC times.
    return time_compareWithDiff(value1, time_toUnixTime2(value2), value1->deviation);
}

int time_fromUnixTime2(
    uint32_t epoch,
    uint16_t* year,
    unsigned char* month,
    unsigned char* day,
    unsigned char* hour,
    unsigned char* minute,
    unsigned char* second,
    unsigned char* dayOfWeek)
{
    //Retrieve hours, minutes and seconds
    if (second != NULL)
    {
        *second = epoch % 60;
    }
    epoch /= 60;
    if (minute != NULL)
    {
        *minute = epoch % 60;
    }
    epoch /= 60;
    if (hour != NULL)
    {
        *hour = epoch % 24;
    }
    epoch /= 24;
    //Convert Unix time to date
    uint32_t a = (uint32_t)((4 * epoch + 102032) / 146097 + 15);
    uint32_t b = (uint32_t)(epoch + 2442113 + a - (a / 4));
    uint32_t c = (20 * b - 2442) / 7305;
    uint32_t d = b - 365 * c - (c / 4);
    uint32_t e = d * 1000 / 30601;
    uint32_t f = d - e * 30 - e * 601 / 1000;
    //January and February are counted as months 13 and 14 of the previous year
    if (e <= 13)
    {
        c -= 4716;
        e -= 1;
    }
    else
    {
        c -= 4715;
        e -= 13;
    }
    //Retrieve year, month and day
    if (year != NULL)
    {
        *year = (uint16_t)c;
    }
    if (month != NULL)
    {
        *month = (unsigned char)e;
    }
    if (day != NULL)
    {
        *day = (unsigned char)f;
    }
    if (dayOfWeek != NULL && year != NULL && month != NULL && day != NULL)
    {
        //Calculate day of week
        *dayOfWeek = time_dayOfWeek(*year, *month, *day);
    }
    return 0;
}

int time_fromUnixTime3(
    const gxtime* time,
    uint16_t* year,
    unsigned char* month,
    unsigned char* day,
    unsigned char* hour,
    unsigned char* minute,
    unsigned char* second,
    unsigned char* dayOfWeek)
{
#ifdef DLMS_USE_EPOCH_TIME
    return time_fromUnixTime2(time->value, year, month,
        day, hour, minute, second, dayOfWeek);
#else
    if (year != NULL)
    {
        *year = 1900 + time->value.tm_year;
    }
    if (month != NULL)
    {
        *month = 1 + time->value.tm_mon;
    }
    if (day != NULL)
    {
        *day = time->value.tm_mday;
    }
    if (hour != NULL)
    {
        *hour = time->value.tm_hour;
    }
    if (minute != NULL)
    {
        *minute = time->value.tm_min;
    }
    if (second != NULL)
    {
        *second = time->value.tm_sec;
    }
    if (dayOfWeek != NULL)
    {
        *dayOfWeek = time->value.tm_year;
    }
    return 0;
#endif //DLMS_USE_EPOCH_TIME
}

unsigned char time_dayOfWeek(
    uint16_t year,
    unsigned char month,
    unsigned char day)
{
    uint16_t h, j, k;
    //January and February are counted as months 13 and 14 of the previous year
    if (month <= 2)
    {
        month += 12;
        year -= 1;
    }
    //J is century
    j = year / 100;
    //K is year of the century
    k = year % 100;
    h = day + (26 * (month + 1) / 10) + k + (k / 4) + (5 * j) + (j / 4);
    //Return the day of the week
    return ((h + 5) % 7) + 1;
}

#ifndef DLMS_USE_EPOCH_TIME
//Get date time from Epoch time.
int time_fromUnixTime(uint32_t epoch, struct tm* time)
{
    uint16_t year;
    unsigned char month, day, hour, minute, second, dayOfWeek;
    time_fromUnixTime2(epoch, &year, &month,
        &day, &hour, &minute, &second, &dayOfWeek);
    memset(time, 0, sizeof(struct tm));
    time->tm_sec = second;
    time->tm_min = minute;
    time->tm_hour = hour;
    time->tm_year = year - 1900;
    time->tm_mon = month - 1;
    time->tm_mday = day;
    time->tm_wday = dayOfWeek;
    return 0;
}

// Convert date time to Epoch time.
uint32_t time_toUnixTime(struct tm* time)
{
    return (uint32_t)gxmktime(time);
}
#endif //DLMS_USE_EPOCH_TIME

// Convert date time to Epoch time.
uint32_t time_toUnixTime2(gxtime* time)
{
    uint32_t value;
#ifdef DLMS_USE_EPOCH_TIME
    value = time->value;
    if (time->deviation != 0 && time->deviation != (short)0x8000)
    {
#ifdef DLMS_USE_UTC_TIME_ZONE
        value -= 60 * time->deviation;
#else
        value += 60 * time->deviation;
#endif //DLMS_USE_UTC_TIME_ZONE
    }
#else
    value = (uint32_t)gxmktime(&time->value);
#endif //DLMS_USE_EPOCH_TIME
    return value;
}

int time_getDeviation(gxtime* value1)
{
#ifdef DLMS_USE_UTC_TIME_ZONE
    return -value1->deviation;
#else
    return value1->deviation;
#endif //DLMS_USE_UTC_TIME_ZONE
}

int time_toUTC(gxtime* value)
{
    //Convert time to UCT if time zone is given.
    if (value->deviation != 0 && value->deviation != (short)0x8000)
    {
        time_addMinutes(value, time_getDeviation(value));
        value->deviation = 0;
        //DST deviation is included to deviation. Remove status.
        value->status &= ~DLMS_CLOCK_STATUS_DAYLIGHT_SAVE_ACTIVE;
    }
    return 0;
}

// Get next scheduled date in UTC time.
uint32_t time_getNextScheduledDate(uint32_t start, gxtime* value)
{
    if ((value->skip & DATETIME_SKIPS_SECOND) == 0)
    {
        uint32_t offset = ((60 + (value->value % 60)) - (start % 60));
        if (offset % 60 == 0)
        {
            start += 60;
        }
        else
        {
            start += offset % 60;
        }
    }
    if ((value->skip & DATETIME_SKIPS_MINUTE) == 0)
    {
        start += 60 - (start % 60);
    }
    if ((value->skip & DATETIME_SKIPS_HOUR) == 0)
    {
        start += 3600 - (time_getMinutes(value) * 60 - time_getSeconds(value));
    }
    if ((value->skip & DATETIME_SKIPS_DAY) == 0)
    {
        start += (24 * 3600) - (time_getHours(value) * 3600 - (time_getMinutes(value) * 60 - time_getSeconds(value)));
    }
    if ((value->skip & DATETIME_SKIPS_MONTH) == 0)
    {
        start += (24 * 3600) - (time_getHours(value) * 3600 - (time_getMinutes(value) * 60 - time_getSeconds(value)));
    }
    if ((value->skip & DATETIME_SKIPS_YEAR) == 0)
    {
        start += (24 * 3600) - (time_getHours(value) * 3600 - (time_getMinutes(value) * 60 - time_getSeconds(value)));
    }
    if (value->skip == 0)
    {
        start = time_toUnixTime2(value) - start;
    }
    return start;
}