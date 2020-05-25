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

#ifndef OBJECTS_H
#define OBJECTS_H

#ifdef  __cplusplus
extern "C" {
#endif
#include "gxignore.h"
#include "enums.h"
#include "variant.h"
#include "date.h"
#include "gxarray.h"
#include "gxkey.h"

#ifdef DLMS_IGNORE_MALLOC
#include "gxdefine.h"
#endif //DLMS_IGNORE_MALLOC

    typedef enum
    {
        /*
         * Write attribute.
         */
        DLMS_SCRIPT_ACTION_TYPE_WRITE = 1,
        /*
         * Execute specific method
        */
        DLMS_SCRIPT_ACTION_TYPE_EXECUTE = 2
    } DLMS_SCRIPT_ACTION_TYPE;

    typedef enum
    {
        /**
         First in first out
         When circle buffer is full first item is removed.
        */
        DLMS_SORT_METHOD_FIFO = 1,
        /**
         Last in first out.
         When circle buffer is full last item is removed.
        */
        DLMS_SORT_METHOD_LIFO = 2,
        /**
         Largest is first.
        */
        DLMS_SORT_METHOD_LARGEST = 3,
        /**
         Smallest is first.
        */
        DLMS_SORT_METHOD_SMALLEST = 4,
        /**
         Nearst to zero is first.
        */
        DLMS_SORT_METHOD_NEAREST_TO_ZERO = 5,
        /**
         Farest from zero is first.
        */
        DLMS_SORT_METHOD_FAREST_FROM_ZERO = 6
    } DLMS_SORT_METHOD;

    typedef enum
    {
        /// Not defined
        DLMS_CLOCK_BASE_NONE,
        /// Internal Crystal
        DLMS_CLOCK_BASE_CRYSTAL,
        /// Mains frequency 50 Hz,
        DLMS_CLOCK_BASE_FREQUENCY_50,
        /// Mains frequency 60 Hz,
        DLMS_CLOCK_BASE_FREQUENCY_60,
        /// Global Positioning System.
        DLMS_CLOCK_BASE_GPS,
        /// Radio controlled.
        DLMS_CLOCK_BASE_RADIO
    } DLMS_CLOCK_BASE;

    typedef enum
    {
        /*
         * No auto dialling,
         */
        DLMS_AUTO_CONNECT_MODE_NO_AUTO_DIALLING = 0,
        /**
         * Auto dialling allowed anytime,
        */
        DLMS_AUTO_CONNECT_MODE_AUTO_DIALLING_ALLOWED_ANYTIME = 1,
        /**
         * Auto dialling allowed within the validity time of the calling window.
        */
        DLMS_AUTO_CONNECT_MODE_AUTO_DIALLING_ALLOWED_CALLING_WINDOW = 2,
        /**
         * Regular auto dialling allowed within the validity time
         * of the calling window; alarm initiated auto dialling allowed anytime,
        */
        DLMS_AUTO_CONNECT_MODE_REGULAR_AUTO_DIALLING_ALLOWED_CALLING_WINDOW = 3,
        /**
         * SMS sending via Public Land Mobile Network (PLMN),
        */
        DLMS_AUTO_CONNECT_MODE_SMS_SENDING_PLMN = 4,
        /*
         * SMS sending via PSTN.
        */
        DLMS_AUTO_CONNECT_MODE_SMS_SENDING_PSTN = 5,
        /*
         * Email sending.
        */
        DLMS_AUTO_CONNECT_MODE_EMAIL_SENDING = 6,
        /*
       * The device is permanently connected to the communication network.
       */
        AUTO_CONNECT_MODE_PERMANENTLY_CONNECT = 101,
        /*
        * The device is permanently connected to the communication network. No
        * connection possible outside the calling window.
        */
        AUTO_CONNECT_MODE_CONNECT_WITH_CALLING_WINDOW = 102,
        /*
        * The device is permanently connected to the communication network.
        * Connection is possible as soon as the connect method is invoked.
        */
        AUTO_CONNECT_MODE_CONNECT_INVOKED = 103,
        /*
        * The device is usually disconnected. It connects to the communication
        * network as soon as the connect method is invoked
        */
        AUTO_CONNECT_MODE_DISCONNECT_CONNECT_INVOKED = 104,
        /*
        * (200..255) manufacturer specific modes
        */
        AUTO_CONNECT_MODE_MANUFACTURE_SPESIFIC = 200
    } DLMS_AUTO_CONNECT_MODE;

    typedef enum
    {
        DLMS_AUTO_ANSWER_STATUS_INACTIVE = 0,
        DLMS_AUTO_ANSWER_STATUS_ACTIVE = 1,
        DLMS_AUTO_ANSWER_STATUS_LOCKED = 2
    } DLMS_AUTO_ANSWER_STATUS;

    /**
     Defines the protocol used by the meter on the port.
    */
    typedef enum
    {
        /**
         Protocol according to IEC 62056-21 (modes A�E),
        */
        DLMS_OPTICAL_PROTOCOL_MODE_DEFAULT = 0,
        /**
         Protocol according to IEC 62056-46.
         Using this enumeration value all other attributes of this IC are not applicable.
        */
        DLMS_OPTICAL_PROTOCOL_MODE_NET = 1,
        /**
         Protocol not specified. Using this enumeration value,
         ProposedBaudrate is used for setting the communication speed on the port.
         All other attributes are not applicable.
        */
        DLMS_OPTICAL_PROTOCOL_MODE_UNKNOWN = 2
    } DLMS_OPTICAL_PROTOCOL_MODE;

    typedef enum
    {
        /**
         Minimium time is 20 ms.
        */
        DLMS_LOCAL_PORT_RESPONSE_TIME_20_MS = 0,
        /**
         Minimium time is 200 ms.
        */
        DLMS_LOCAL_PORT_RESPONSE_TIME_200_MS = 1
    } DLMS_LOCAL_PORT_RESPONSE_TIME;

    /**
     *
     * Defines the baud rates.
     */
    typedef enum
    {
        /**
        Baudrate is 300.
        */
        DLMS_BAUD_RATE_300 = 0,
        /**
         Baudrate is 600.
        */
        DLMS_BAUD_RATE_600,
        /**
         Baudrate is 1200.
        */
        DLMS_BAUD_RATE_1200,
        /**
         Baudrate is 2400.
        */
        DLMS_BAUD_RATE_2400,
        /**
         Baudrate is 4800.
        */
        DLMS_BAUD_RATE_4800,
        /**
         Baudrate is 9600.
        */
        DLMS_BAUD_RATE_9600,
        /**
         Baudrate is 19200.
        */
        DLMS_BAUD_RATE_19200,
        /**
         Baudrate is 38400.
        */
        DLMS_BAUD_RATE_38400,
        /**
         Baudrate is 57600.
        */
        DLMS_BAUD_RATE_57600,
        /**
         Baudrate is 115200.
        */
        DLMS_BAUD_RATE_115200
    } DLMS_BAUD_RATE;

    typedef enum
    {
        /*
         * The output_state is set to false and the consumer is disconnected.
         */
        DLMS_CONTROL_STATE_DISCONNECTED,
        /*
         * The output_state is set to 1 and the consumer is connected.
        */
        DLMS_CONTROL_STATE_CONNECTED,
        /*
         * The output_state is set to false and the consumer is disconnected.
        */
        DLMS_CONTROL_STATE_READY_FOR_RECONNECTION
    } DLMS_CONTROL_STATE;

    /*
     * Configures the behaviour of the disconnect control object for all
    triggers, i.e. the possible state transitions.
     */
    typedef enum
    {
        /*
         * The disconnect control object is always in 'connected' state,
        */
        DLMS_CONTROL_MODE_NONE,
        /*
         * Disconnection: Remote (b, c), manual (f), local (g)
         * Reconnection: Remote (d), manual (e).
        */
        DLMS_CONTROL_MODE_MODE_1,
        /*
         * Disconnection: Remote (b, c), manual (f), local (g)
         * Reconnection: Remote (a), manual (e).
        */
        DLMS_CONTROL_MODE_MODE_2,
        /*
         * Disconnection: Remote (b, c), manual (-), local (g)
         * Reconnection: Remote (d), manual (e).
        */
        DLMS_CONTROL_MODE_MODE_3,
        /*
         * Disconnection: Remote (b, c), manual (-), local (g)
         * Reconnection: Remote (a), manual (e)
        */
        DLMS_CONTROL_MODE_MODE_4,
        /*
         * Disconnection: Remote (b, c), manual (f), local (g)
         * Reconnection: Remote (d), manual (e), local (h),
        */
        DLMS_CONTROL_MODE_MODE_5,
        /*
         * Disconnection: Remote (b, c), manual (-), local (g)
         * Reconnection: Remote (d), manual (e), local (h)
        */
        DLMS_CONTROL_MODE_MODE_6,
    } DLMS_CONTROL_MODE;

    /**
    PPP Authentication Type
     */
    typedef enum
    {
        /**
         No authentication.
        */
        DLMS_PPP_AUTHENTICATION_TYPE_NONE = 0,
        /**
         PAP Login
        */
        DLMS_PPP_AUTHENTICATION_TYPE_PAP = 1,
        /**
         CHAP-algorithm
        */
        DLMS_PPP_AUTHENTICATION_TYPE_CHAP = 2
    } DLMS_PPP_AUTHENTICATION_TYPE;

#ifdef DLMS_IGNORE_MALLOC
    typedef struct
    {
        unsigned char value[MAX_DESTINATION_LENGTH];
        unsigned short size;
    }gxDestination;
#endif //DLMS_IGNORE_MALLOC

    //Access modes are saved structure because they are not needed on server side and we want to save memory.
    /**
    ---------------------------------------------------------------------------
    */
    typedef struct
    {
        gxByteBuffer attributeAccessModes;
        gxByteBuffer methodAccessModes;
    }gxAccess;

    typedef struct
    {
        unsigned short objectType; //DLMS_OBJECT_TYPE
        unsigned char version;
#ifndef DLMS_IGNORE_MALLOC
        //Is this component free when collection is clear.
        unsigned char free;
#endif //DLMS_IGNORE_MALLOC
#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
        unsigned short shortName;
#endif // DLMS_IGNORE_ASSOCIATION_SHORT_NAME
        unsigned char logicalName[6];
        gxAccess* access;
    } gxObject;

    //Returns object's logical name.
    const unsigned char* obj_getLogicalName(gxObject* target);

    typedef struct
    {
        gxObject* key;
        unsigned char value;
    } gxListItem;

    typedef struct
    {
        gxObject** data;
        unsigned short capacity;
        unsigned short size;
#if !(defined(GX_DLMS_MICROCONTROLLER) || defined(DLMS_IGNORE_MALLOC))
        unsigned short position;
#endif //!(defined(GX_DLMS_MICROCONTROLLER) || defined(DLMS_IGNORE_MALLOC))
    } objectArray;

    //---------------------------------------------------------------------------
    // Online help:
    //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSData
#ifndef DLMS_IGNORE_DATA
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        dlmsVARIANT value;
    } gxData;
#endif //DLMS_IGNORE_DATA

    //---------------------------------------------------------------------------
    // Online help:
    //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSRegister
#ifndef DLMS_IGNORE_REGISTER
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        dlmsVARIANT value;
        signed char scaler;
        unsigned char unit;
        unsigned char unitRead;
    } gxRegister;
#endif // DLMS_IGNORE_REGISTER

    //---------------------------------------------------------------------------
    // Online help:
    //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSExtendedRegister
#ifndef DLMS_IGNORE_EXTENDED_REGISTER
    typedef struct
    {
        gxObject base;
        dlmsVARIANT value;
        signed char scaler;
        unsigned char unit;
        gxtime captureTime;
        dlmsVARIANT status;
    } gxExtendedRegister;
#endif //DLMS_IGNORE_EXTENDED_REGISTER

    //---------------------------------------------------------------------------
    // Online help:
    //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSDemandRegister
#ifndef DLMS_IGNORE_DEMAND_REGISTER
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        dlmsVARIANT currentAvarageValue;
        dlmsVARIANT lastAvarageValue;
        signed char scaler;
        unsigned char unit;
        unsigned char unitRead;
        dlmsVARIANT status;
        gxtime captureTime;
        gxtime startTimeCurrent;
        unsigned short numberOfPeriods;
        unsigned long period;
    } gxDemandRegister;
#endif // DLMS_IGNORE_DEMAND_REGISTER

#ifdef DLMS_IGNORE_OBJECT_POINTERS
    typedef struct
    {
        DLMS_OBJECT_TYPE objectType;
        unsigned char logicalName[6];
    } gxObjectDefinition;
#endif //DLMS_IGNORE_OBJECT_POINTERS

#ifndef DLMS_IGNORE_REGISTER_ACTIVATION
#ifdef DLMS_IGNORE_MALLOC
    typedef struct
    {
        gxObject* target;
        unsigned char indexes[9];
    } gxRegisterActivationMask;
#endif //DLMS_IGNORE_MALLOC

    //---------------------------------------------------------------------------
    // Online help:
    //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSRegisterActivation
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;

#if !(defined(DLMS_IGNORE_OBJECT_POINTERS) || defined(DLMS_IGNORE_MALLOC))
        objectArray registerAssignment;
#else
        gxArray registerAssignment;
#endif //DLMS_IGNORE_OBJECT_POINTERS

        gxArray maskList;
#ifdef DLMS_IGNORE_MALLOC
        unsigned char activeMask[6];
#else
        gxByteBuffer activeMask;
#endif //DLMS_IGNORE_MALLOC


    } gxRegisterActivation;
#endif //DLMS_IGNORE_REGISTER_ACTIVATION

#if !(defined(DLMS_IGNORE_PROFILE_GENERIC) && defined(DLMS_IGNORE_COMPACT_DATA) && defined(DLMS_IGNORE_PUSH_SETUP) && defined(DLMS_IGNORE_PARAMETER_MONITOR))
    //---------------------------------------------------------------------------
    // Online help:
    //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSProfileGeneric
    //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSCompactData
    //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSParameterMonitor
    typedef struct
    {
        signed char attributeIndex;
        unsigned short dataIndex;
#ifdef DLMS_IGNORE_MALLOC
        gxObject* target;
#endif //DLMS_IGNORE_MALLOC
    } gxTarget;


    //---------------------------------------------------------------------------
    //deprecated: User gxTarget instead of gxCaptureObject.
    typedef struct
    {
        char attributeIndex;
        unsigned short dataIndex;
    } gxCaptureObject;

#endif //!(defined(DLMS_IGNORE_PROFILE_GENERIC) && defined(DLMS_IGNORE_COMPACT_DATA) && defined(DLMS_IGNORE_PUSH_SETUP) && defined(DLMS_IGNORE_PARAMETER_MONITOR))

#ifndef DLMS_IGNORE_PROFILE_GENERIC
#ifndef DLMS_IGNORE_MALLOC
    //Create capture object with given attribute and data indexes.
    gxTarget* co_init(unsigned char attributeIndex, unsigned char dataIndex);
#endif //DLMS_IGNORE_MALLOC

    //---------------------------------------------------------------------------
    // Online help:
    //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSProfileGeneric
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;

#ifndef DLMS_IGNORE_MALLOC
        //There is no buffer is malloc is not used.
        //Reason for this is that we don't know the structure of the data and where example octect string is saved.
        //User must do this manually!
        gxArray buffer;
#endif //DLMS_IGNORE_MALLOC
        gxArray captureObjects;
        int capturePeriod;
        DLMS_SORT_METHOD sortMethod;
        gxObject* sortObject;
        unsigned long profileEntries;
        unsigned long entriesInUse;
        signed char sortObjectAttributeIndex;
        unsigned short sortObjectDataIndex;

        /**
        * Max row count is used with Profile Generic to tell how many rows are read
        * to one PDU. Default value is 1. Change this for your needs.
        */
#ifndef DLMS_IGNORE_MALLOC
        unsigned short maxRowCount;
#endif //DLMS_IGNORE_MALLOC
    } gxProfileGeneric;
#endif //DLMS_IGNORE_PROFILE_GENERIC

    //---------------------------------------------------------------------------
    // Online help:
    //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSClock
#ifndef DLMS_IGNORE_CLOCK
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;

        DLMS_CLOCK_BASE clockBase;
        signed char deviation;
        unsigned char enabled;
        gxtime end;
        DLMS_CLOCK_STATUS status;
        gxtime begin;
        short timeZone;
        gxtime time;
        gxtime presetTime;
    } gxClock;

#ifndef DLMS_IGNORE_CLOCK
    //Update Daylight Saving time flag if DST is used.
    void clock_updateDST(
        gxClock* object,
        gxtime* value);

    //Convert UTC date time to meter date time.
    int clock_utcToMeterTime(
        gxClock* object,
        gxtime* value);
#endif // DLMS_IGNORE_CLOCK

#endif //DLMS_IGNORE_CLOCK

#ifndef DLMS_IGNORE_SCRIPT_TABLE
    //---------------------------------------------------------------------------
    // Online help:
    //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSScriptTable
    typedef struct
    {
#ifndef DLMS_IGNORE_OBJECT_POINTERS
        gxObject* target;
#else
        DLMS_OBJECT_TYPE objectType;
        unsigned char logicalName[6];
#endif //DLMS_IGNORE_OBJECT_POINTERS
        DLMS_SCRIPT_ACTION_TYPE type;
        dlmsVARIANT parameter;
        signed char index;
    } gxScriptAction;

    //---------------------------------------------------------------------------
    // Online help:
    //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSScriptTable
    typedef struct
    {
        //Script ID.
        unsigned short id;
        //Script actions.
        gxArray actions;
    } gxScript;

    //---------------------------------------------------------------------------
    // Online help:
    //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSScriptTable
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        gxArray scripts;
    } gxScriptTable;
#endif //DLMS_IGNORE_SCRIPT_TABLE

#ifndef DLMS_IGNORE_SCHEDULE
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSSchedule
    */
    typedef struct
    {
        /**
        * Schedule entry index.
        */
        unsigned short index;

        /**
        * Is Schedule entry enabled.
        */
        unsigned char enable;
#ifndef DLMS_IGNORE_OBJECT_POINTERS
        gxScriptTable* scriptTable;
#else
        /**
        * Logical name of the Script table object.
        */
        unsigned char logicalName[6];
#endif //DLMS_IGNORE_OBJECT_POINTERS

        /**
        * Script identifier of the script to be executed.
        */
        short scriptSelector;

        /**
        *
        */
        gxtime switchTime;

        /**
        * Defines a period in minutes, in which an entry shall be processed after power fail.
        */
        short validityWindow;

        /**
        * BitArray days of the week on which the entry is valid.
        */
        unsigned char execWeekdays;

        /**
        * Perform the link to the IC Special days table, day_id.
        */
        bitArray execSpecDays;

        /**
        * Date starting period in which the entry is valid.
        */
        gxtime beginDate;

        /**
        * Date starting period in which the entry is valid.
        */
        gxtime endDate;
    }
    gxScheduleEntry;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSSchedule
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;

        /**
        * Specifies the scripts to be executed at given times.
        */
        gxArray entries; //gxScheduleEntry
    } gxSchedule;
#endif //DLMS_IGNORE_SCHEDULE

#ifndef DLMS_IGNORE_SPECIAL_DAYS_TABLE
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSSpecialDaysTable
    */
    typedef struct
    {
        unsigned short index;
        gxtime date;
        unsigned char dayId;
    } gxSpecialDay;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSSpecialDaysTable
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        gxArray entries;
    } gxSpecialDaysTable;
#endif //DLMS_IGNORE_SPECIAL_DAYS_TABLE

#ifndef DLMS_IGNORE_SECURITY_SETUP
    typedef struct
    {
        // Used certificate entity.
        DLMS_CERTIFICATE_ENTITY entity;

        // Used certificate type.
        DLMS_CERTIFICATE_TYPE type;

#ifdef DLMS_IGNORE_MALLOC
        // Certificate serial number.
        char serialNumber[MAX_CERTIFICATE_SERIAL_NUMBER_LENGTH];

        // Certificate issuer.
        char issuer[MAX_CERTIFICATE_ISSUER_LENGTH];

        // Certificate subject.
        char subject[MAX_CERTIFICATE_SUBJECT_LENGTH];
        // Certificate subject alt name.
        char subjectAltName[MAX_CERTIFICATE_SUBJECT_ALT_LENGTH];
#else
        // Certificate serial number.
        char* serialNumber;

        // Certificate issuer.
        char* issuer;

        // Certificate subject.
        char* subject;
        // Certificate subject alt name.
        char* subjectAltName;
#endif //DLMS_IGNORE_MALLOC
    }gxCertificateInfo;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSSecuritySetup
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        unsigned char securityPolicy;
        DLMS_SECURITY_SUITE securitySuite;
        gxByteBuffer serverSystemTitle;
        gxByteBuffer clientSystemTitle;
        gxArray certificates;
    } gxSecuritySetup;
#endif //DLMS_IGNORE_SECURITY_SETUP

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAssociationShortName
    */
#ifndef DLMS_IGNORE_ASSOCIATION_SHORT_NAME
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        objectArray objectList;
#if !(defined(DLMS_IGNORE_OBJECT_POINTERS) || defined(DLMS_IGNORE_SECURITY_SETUP))
        gxSecuritySetup* securitySetup;
#else
        unsigned char securitySetupReference[6];
#endif //DLMS_IGNORE_OBJECT_POINTERS
        gxByteBuffer secret;
    } gxAssociationShortName;
#endif //DLMS_IGNORE_ASSOCIATION_SHORT_NAME

#ifndef DLMS_IGNORE_ASSOCIATION_LOGICAL_NAME
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAssociationLogicalName
    */
    typedef struct
    {
        unsigned char logicalName[6];
        unsigned char jointIsoCtt;
        unsigned char country;
        unsigned short countryName;
        unsigned char identifiedOrganization;
        unsigned char dlmsUA;
        unsigned char applicationContext;
        unsigned char contextId;
    } gxApplicationContextName;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAssociationLogicalName
    */
    typedef struct
    {
        DLMS_CONFORMANCE conformance;
        unsigned short maxReceivePduSize;
        unsigned short maxSendPpuSize;
        unsigned char dlmsVersionNumber;
        signed char qualityOfService;
        gxByteBuffer cypheringInfo;
    } gxXDLMSContextType;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAssociationLogicalName
    */
    typedef struct
    {
        unsigned char jointIsoCtt;
        unsigned char country;
        unsigned short countryName;
        unsigned char identifiedOrganization;
        unsigned char dlmsUA;
        unsigned char authenticationMechanismName;
        DLMS_AUTHENTICATION mechanismId;
    } gxAuthenticationMechanismName;

#ifdef DLMS_IGNORE_MALLOC
    typedef struct
    {
        //User ID.
        unsigned char id;
        //User name
        char name[MAX_USER_NAME_LENGTH];
    }gxUser;
#endif //DLMS_IGNORE_MALLOC

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAssociationLogicalName
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;

        DLMS_ASSOCIATION_STATUS associationStatus;
        objectArray objectList;
        signed char clientSAP;
        unsigned short serverSAP;
        gxApplicationContextName applicationContextName;
        gxXDLMSContextType xDLMSContextInfo;
        gxAuthenticationMechanismName authenticationMechanismName;
        gxByteBuffer secret;
#if !(defined(DLMS_IGNORE_OBJECT_POINTERS) || defined(DLMS_IGNORE_SECURITY_SETUP))
        gxSecuritySetup* securitySetup;
#else
        unsigned char securitySetupReference[6];
#endif //!(defined(DLMS_IGNORE_OBJECT_POINTERS) || defined(DLMS_IGNORE_SECURITY_SETUP))
        /**
        * User list.
        */
        gxArray userList;
        /**
        * Current user.
        */
#ifdef DLMS_IGNORE_MALLOC
        gxUser currentUser;
#else
        gxKey2 currentUser;
#endif //DLMS_IGNORE_MALLOC
    } gxAssociationLogicalName;

#endif //DLMS_IGNORE_ASSOCIATION_LOGICAL_NAME

#ifndef DLMS_IGNORE_SAP_ASSIGNMENT

#ifdef DLMS_IGNORE_MALLOC
    typedef struct
    {
        unsigned char value[MAX_SAP_ITEM_NAME_LENGTH];
        unsigned short size;
    }gxSapItemName;
#endif //DLMS_IGNORE_MALLOC

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSSapAssignment
    */
    typedef struct
    {
        unsigned short id;
#ifdef DLMS_IGNORE_MALLOC
        gxSapItemName name;
#else
        gxByteBuffer name;
#endif //DLMS_IGNORE_MALLOC
    } gxSapItem;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSSapAssignment
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        gxArray sapAssignmentList;//List of gxSapItems.
    } gxSapAssignment;

#endif //DLMS_IGNORE_SAP_ASSIGNMENT

#ifndef DLMS_IGNORE_IMAGE_TRANSFER

#ifdef DLMS_IGNORE_MALLOC
    typedef struct
    {
        unsigned char data[MAX_IMAGE_IDENTIFICATION_LENGTH];
        unsigned short size;
    }gxImageIdentification;

    typedef struct
    {
        unsigned char data[MAX_IMAGE_SIGNATURE_LENGTH];
        unsigned short size;
    }gxImageSignature;
#endif //DLMS_IGNORE_MALLOC

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSImageTransfer
    */
    typedef struct
    {
        unsigned long size;

#ifdef DLMS_IGNORE_MALLOC
        gxImageIdentification identification;
        gxImageSignature signature;
#else
        gxByteBuffer identification;
        gxByteBuffer signature;
#endif //DLMS_IGNORE_MALLOC
    } gxImageActivateInfo;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSImageTransfer
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        unsigned long imageBlockSize;
        bitArray imageTransferredBlocksStatus;
        unsigned long imageFirstNotTransferredBlockNumber;
        unsigned char imageTransferEnabled;
        DLMS_IMAGE_TRANSFER_STATUS imageTransferStatus;
        gxArray imageActivateInfo; // gxImageActivateInfo
    } gxImageTransfer;
#endif //DLMS_IGNORE_IMAGE_TRANSFER

#ifndef DLMS_IGNORE_IEC_LOCAL_PORT_SETUP
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSIECLocalPortSetup
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        gxByteBuffer password1;
        gxByteBuffer password2;
        gxByteBuffer password5;
        DLMS_OPTICAL_PROTOCOL_MODE defaultMode;
        DLMS_BAUD_RATE defaultBaudrate;
        DLMS_BAUD_RATE proposedBaudrate;
        DLMS_LOCAL_PORT_RESPONSE_TIME responseTime;
        gxByteBuffer deviceAddress;
    } gxLocalPortSetup;
#endif //DLMS_IGNORE_IEC_LOCAL_PORT_SETUP

#ifndef DLMS_IGNORE_ACTIVITY_CALENDAR

#ifdef DLMS_IGNORE_MALLOC
    typedef struct
    {
        unsigned char value[MAX_SEASON_PROFILE_NAME_LENGTH];
        unsigned short size;
    }gxSeasonProfileName;
#endif //DLMS_IGNORE_MALLOC

#define SET_OCTECT_STRING(X, V, S) memcpy(X.value, V, S);X.size=S

#ifdef DLMS_IGNORE_MALLOC
    typedef struct
    {
        unsigned char value[MAX_SEASON_PROFILE_WEEK_NAME_LENGTH];
        unsigned short size;
    }gxSeasonProfileWeekName;
#endif //DLMS_IGNORE_MALLOC

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSActivityCalendar
    */
    typedef struct
    {
#ifdef DLMS_IGNORE_MALLOC
        gxSeasonProfileName name;
#else
        gxByteBuffer name;
#endif //DLMS_IGNORE_MALLOC
        gxtime start;
#ifdef DLMS_IGNORE_MALLOC
        gxSeasonProfileWeekName weekName;
#else
        gxByteBuffer weekName;
#endif //DLMS_IGNORE_MALLOC
    } gxSeasonProfile;

#ifdef DLMS_IGNORE_MALLOC
    typedef struct
    {
        unsigned char value[MAX_SEASON_WEEK_PROFILE_NAME_LENGTH];
        unsigned short size;
    }gxWeekProfileName;
#endif //DLMS_IGNORE_MALLOC

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSActivityCalendar
    */
    typedef struct
    {
#ifdef DLMS_IGNORE_MALLOC
        gxWeekProfileName name;
#else
        gxByteBuffer name;
#endif //DLMS_IGNORE_MALLOC
        unsigned char monday;
        unsigned char tuesday;
        unsigned char wednesday;
        unsigned char thursday;
        unsigned char friday;
        unsigned char saturday;
        unsigned char sunday;
    } gxWeekProfile;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSActivityCalendar
    */
    typedef struct
    {
        gxtime startTime;
#ifndef DLMS_IGNORE_OBJECT_POINTERS
        gxObject* script;
#else
        unsigned char scriptLogicalName[6];
#endif //DLMS_IGNORE_OBJECT_POINTERS
        unsigned short scriptSelector;
    } gxDayProfileAction;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSActivityCalendar
    */
    typedef struct
    {
        unsigned char dayId;
        gxArray daySchedules; //gxDayProfileAction
    } gxDayProfile;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSActivityCalendar
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;

        gxByteBuffer calendarNameActive;
        gxByteBuffer calendarNamePassive;
        gxArray seasonProfileActive; // gxSeasonProfile
        gxArray weekProfileTableActive;// gxWeekProfile
        gxArray dayProfileTableActive;// gxDayProfile
        gxArray seasonProfilePassive;// gxSeasonProfile
        gxArray dayProfileTablePassive;// gxDayProfile
        gxArray weekProfileTablePassive;// gxWeekProfile
        gxtime time;
    } gxActivityCalendar;

#endif // DLMS_IGNORE_ACTIVITY_CALENDAR

#if !(defined(DLMS_IGNORE_LIMITER) && defined(DLMS_IGNORE_REGISTER_MONITOR))
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSRegisterMonitor
    */
    typedef struct
    {
#ifndef DLMS_IGNORE_OBJECT_POINTERS
        gxScriptTable* script;
#else
        unsigned char logicalName[6];
#endif //DLMS_IGNORE_OBJECT_POINTERS
        unsigned short scriptSelector;
    } gxActionItem;

#endif //!(defined(DLMS_IGNORE_LIMITER) && defined(DLMS_IGNORE_REGISTER_MONITOR))

#ifndef DLMS_IGNORE_REGISTER_MONITOR
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSRegisterMonitor
    */
    typedef struct
    {
#ifndef DLMS_IGNORE_OBJECT_POINTERS
        gxObject* target;
#else
        DLMS_OBJECT_TYPE objectType;
        unsigned char logicalName[6];
#endif //DLMS_IGNORE_OBJECT_POINTERS
        signed char attributeIndex;
    } gxMonitoredValue;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSRegisterMonitor
    */
    typedef struct
    {
        gxActionItem actionUp;
        gxActionItem actionDown;
    } gxActionSet;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSRegisterMonitor
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        gxArray actions; //gxActionSet
        gxMonitoredValue monitoredValue;
        variantArray thresholds; //dlmsVARIANT
    } gxRegisterMonitor;

#endif //DLMS_IGNORE_REGISTER_MONITOR

#ifndef DLMS_IGNORE_ACTION_SCHEDULE
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSActionSchedule
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;

#ifndef DLMS_IGNORE_OBJECT_POINTERS
        gxScriptTable* executedScript;
#else
        unsigned char executedScriptLogicalName[6];
#endif //DLMS_IGNORE_OBJECT_POINTERS
        unsigned short executedScriptSelector;
        DLMS_SINGLE_ACTION_SCHEDULE_TYPE type;
        gxArray executionTime; //gxTime
    } gxActionSchedule;

#endif //DLMS_IGNORE_ACTION_SCHEDULE

#ifndef DLMS_IGNORE_IEC_HDLC_SETUP
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSIecHdlcSetup
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        unsigned short inactivityTimeout;
        unsigned short deviceAddress;
        unsigned short maximumInfoLengthTransmit;
        DLMS_BAUD_RATE communicationSpeed;
        unsigned char windowSizeTransmit;
        unsigned char windowSizeReceive;
        unsigned short interCharachterTimeout;
        unsigned short maximumInfoLengthReceive;
    } gxIecHdlcSetup;

#endif //DLMS_IGNORE_IEC_HDLC_SETUP

#ifndef DLMS_IGNORE_IEC_TWISTED_PAIR_SETUP
    typedef enum
    {
        /**
         * The interface ignores all received frames.
        */
        DLMS_IEC_TWISTED_PAIR_SETUP_MODE_INACTIVE,

        /**
         * Active.
        */
        DLMS_IEC_TWISTED_PAIR_SETUP_MODE_ACTIVE
    } DLMS_IEC_TWISTED_PAIR_SETUP_MODE;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSIecTwistedPairSetup
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;


        /**
         * Working mode.
         */
        DLMS_IEC_TWISTED_PAIR_SETUP_MODE mode;

        /**
         * Communication speed.
         */
        DLMS_BAUD_RATE speed;

        /**
         * List of Primary Station Addresses.
         */
        gxByteBuffer primaryAddresses;

        /**
         * List of the TAB(i) for which the real equipment has been programmed in
         * the case of forgotten station call.
         */
        gxByteBuffer tabis;
    } gxIecTwistedPairSetup;
#endif //DLMS_IGNORE_IEC_TWISTED_PAIR_SETUP

#ifndef DLMS_IGNORE_MBUS_SLAVE_PORT_SETUP
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSMbusSlavePortSetup
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        DLMS_BAUD_RATE defaultBaud;
        DLMS_BAUD_RATE availableBaud;
        DLMS_ADDRESS_STATE addressState;
        unsigned char busAddress;
    } gxMbusSlavePortSetup;

#endif //DLMS_IGNORE_MBUS_SLAVE_PORT_SETUP

#ifndef DLMS_IGNORE_UTILITY_TABLES
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSUtilityTables
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        unsigned short tableId;
        gxByteBuffer buffer;
    } gxUtilityTables;
#endif //DLMS_IGNORE_UTILITY_TABLES

#ifndef DLMS_IGNORE_MODEM_CONFIGURATION

#ifdef DLMS_IGNORE_MALLOC
    typedef struct
    {
        unsigned char value[MAX_MODEM_INITIALIZATION_STRING_LENGTH];
        unsigned short size;
    }gxModemInitialisationString;
#endif //DLMS_IGNORE_MALLOC

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSModemConfiguration
    */
    typedef struct
    {
#ifdef DLMS_IGNORE_MALLOC
        gxModemInitialisationString request;
        gxModemInitialisationString response;
#else
        gxByteBuffer request;
        gxByteBuffer response;
#endif //DLMS_IGNORE_MALLOC
        unsigned short delay;
    } gxModemInitialisation;

#ifdef DLMS_IGNORE_MALLOC
    typedef struct
    {
        unsigned char value[MAX_MODEM_PROFILE_STRING_LENGTH];
        unsigned short size;
    }gxModemProfile;
#endif //DLMS_IGNORE_MALLOC

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSModemConfiguration
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        gxArray initialisationStrings; //gxModemInitialisation
        gxArray modemProfile; // gxByteBuffer
        DLMS_BAUD_RATE communicationSpeed;
    } gxModemConfiguration;

#endif //DLMS_IGNORE_MODEM_CONFIGURATION

    typedef struct
    {
        gxtime first;
        gxtime second;
    }gxTimePair;

#ifndef DLMS_IGNORE_AUTO_ANSWER
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAutoAnswer
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        unsigned char numberOfRingsInListeningWindow, numberOfRingsOutListeningWindow;
        DLMS_AUTO_CONNECT_MODE mode;
        gxArray listeningWindow;
        DLMS_AUTO_ANSWER_STATUS status;
        unsigned char numberOfCalls;
    } gxAutoAnswer;

#endif //DLMS_IGNORE_AUTO_ANSWER

#ifndef DLMS_IGNORE_AUTO_CONNECT
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAutoConnect
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        DLMS_AUTO_CONNECT_MODE mode;
        gxArray callingWindow;
        //Array of destination strings.
        gxArray destinations;
        unsigned short repetitionDelay;
        unsigned char repetitions;
    } gxAutoConnect;
#endif //DLMS_IGNORE_AUTO_CONNECT

#ifndef DLMS_IGNORE_TCP_UDP_SETUP
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSTcpUdpSetup
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        unsigned short port;
#ifndef DLMS_IGNORE_OBJECT_POINTERS
        gxObject* ipSetup;
#else
        //Logical name.
        unsigned char ipReference[6];
#endif //DLMS_IGNORE_OBJECT_POINTERS
        unsigned char maximumSimultaneousConnections;
        unsigned short inactivityTimeout;
        unsigned short maximumSegmentSize;
    } gxTcpUdpSetup;

#endif //DLMS_IGNORE_TCP_UDP_SETUP

#ifndef DLMS_IGNORE_IP4_SETUP
#ifdef DLMS_IGNORE_MALLOC
    typedef struct
    {
        unsigned char value[MAX_IP4_SETUP_IP_OPTION_DATA_LENGTH];
        unsigned short size;
    }gxip4SetupIpOptionData;
#endif //DLMS_IGNORE_MALLOC
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSip4SetupIpOption
    */
    typedef struct
    {
        DLMS_IP_OPTION_TYPE type;
        unsigned char length;
#ifdef DLMS_IGNORE_MALLOC
        gxip4SetupIpOptionData data;
#else
        gxByteBuffer data;
#endif //DLMS_IGNORE_MALLOC
    } gxip4SetupIpOption;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSIp4Setup
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
#ifndef DLMS_IGNORE_OBJECT_POINTERS
        gxObject* dataLinkLayer;
#else
        unsigned char dataLinkLayerReference[6];
#endif //DLMS_IGNORE_OBJECT_POINTERS
        unsigned int ipAddress;
#ifdef DLMS_IGNORE_MALLOC
        gxArray multicastIPAddress;
#else
        variantArray multicastIPAddress;
#endif //DLMS_IGNORE_MALLOC
        gxArray ipOptions; //gxip4SetupIpOption
        unsigned long subnetMask;
        unsigned long gatewayIPAddress;
        unsigned char useDHCP;
        unsigned long primaryDNSAddress;
        unsigned long secondaryDNSAddress;
        dlmsVARIANT value;
    } gxIp4Setup;
#endif //DLMS_IGNORE_IP4_SETUP

#ifndef DLMS_IGNORE_MAC_ADDRESS_SETUP

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSMacAddressSetup
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        gxByteBuffer macAddress;
    } gxMacAddressSetup;
#endif //DLMS_IGNORE_MAC_ADDRESS_SETUP

#ifndef DLMS_IGNORE_PPP_SETUP
    typedef enum
    {
        DLMS_PPP_SETUP_LCP_OPTION_TYPE_MAX_REC_UNIT = 1,
        DLMS_PPP_SETUP_LCP_OPTION_TYPE_ASYNC_CONTROL_CHAR_MAP = 2,
        DLMS_PPP_SETUP_LCP_OPTION_TYPE_AUTH_PROTOCOL = 3,
        DLMS_PPP_SETUP_LCP_OPTION_TYPE_MAGIC_NUMBER = 5,
        DLMS_PPP_SETUP_LCP_OPTION_TYPE_PROTOCOL_FIELD_COMPRESSION = 7,
        DLMS_PPP_SETUP_LCP_OPTION_TYPE_ADDRESS_AND_CTR_COMPRESSION = 8,
        DLMS_PPP_SETUP_LCP_OPTION_TYPE_FCS_ALTERNATIVES = 9,
        DLMS_PPP_SETUP_LCP_OPTION_TYPE_CALLBACK = 13
    } DLMS_PPP_SETUP_LCP_OPTION_TYPE;

    typedef enum
    {
        DLMS_PPP_SETUP_IPCP_OPTION_TYPE_IPCOMPRESSIONPROTOCOL = 2,
        DLMS_PPP_SETUP_IPCP_OPTION_TYPE_PREFLOCALIP = 3,
        DLMS_PPP_SETUP_IPCP_OPTION_TYPE_PREFPEERIP = 20,
        DLMS_PPP_SETUP_IPCP_OPTION_TYPE_GAO = 21,
        DLMS_PPP_SETUP_IPCP_OPTION_TYPE_USIP = 22
    } DLMS_PPP_SETUP_IPCP_OPTION_TYPE;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSPppSetup
    */
    typedef struct
    {
        DLMS_PPP_SETUP_LCP_OPTION_TYPE type;
        unsigned char length;
        dlmsVARIANT data;
    } gxpppSetupLcpOption;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSPppSetup
    */
    typedef struct
    {
        DLMS_PPP_SETUP_IPCP_OPTION_TYPE type;
        unsigned char length;
        dlmsVARIANT data;
    } gxpppSetupIPCPOption;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSPppSetup
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        gxArray ipcpOptions; // gxpppSetupIPCPOption
#ifndef DLMS_IGNORE_OBJECT_POINTERS
        gxObject* phy;
#else
        unsigned char PHYReference[6];
#endif //DLMS_IGNORE_OBJECT_POINTERS
        gxArray lcpOptions; //CGXDLMSPppSetupLcpOption
        gxByteBuffer userName;
        gxByteBuffer password;
        DLMS_PPP_AUTHENTICATION_TYPE authentication;
    } gxPppSetup;
#endif //DLMS_IGNORE_PPP_SETUP

#ifndef DLMS_IGNORE_GPRS_SETUP
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSGPRSSetup
    */
    typedef struct
    {
        unsigned char precedence;
        unsigned char delay;
        unsigned char reliability;
        unsigned char peakThroughput;
        unsigned char meanThroughput;
    } gxQualityOfService;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSGPRSSetup
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        gxByteBuffer apn;
        unsigned short pinCode;
        gxQualityOfService defaultQualityOfService;
        gxQualityOfService requestedQualityOfService;
    } gxGPRSSetup;
#endif //DLMS_IGNORE_GPRS_SETUP

#ifndef DLMS_IGNORE_SMTP_SETUP
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSSmtpSetup
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
    } gxSmtpSetup;
#endif //DLMS_IGNORE_SMTP_SETUP

#ifndef DLMS_IGNORE_GSM_DIAGNOSTIC
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSGsmDiagnostic
    */
    typedef struct
    {
        /*
        * Cell ID.
        */
        unsigned long cellId;

        /*
        * Location area code (LAC).
        */
        unsigned short locationId;

        /*
        * Signal quality.
        */
        unsigned char signalQuality;
        /*
        * Bit Error Rate.
        */
        unsigned char ber;
        /*
        * Mobile Country Code.
        */
        unsigned short mobileCountryCode;

        /*
        * Mobile Network Code.
        */
        unsigned short mobileNetworkCode;

        /*
        * Absolute radio frequency channel number.
        */
        unsigned long channelNumber;
    }gxGSMCellInfo;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSGsmDiagnostic
    */
    typedef struct
    {
        /**
        * Four-byte cell ID.
        */
        unsigned long cellId;

        /**
        * Signal quality.
        */
        unsigned char signalQuality;
    }gxAdjacentCell;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSGsmDiagnostic
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        /**
        * Name of network operator.
        */
#ifdef DLMS_IGNORE_MALLOC
        gxByteBuffer operatorName;
#else
        char* operatorName;
#endif //DLMS_IGNORE_MALLOC

        /**
        * Registration status of the modem.
        */
        DLMS_GSM_STATUS status;

        /**
        * Registration status of the modem.
        */
        DLMS_GSM_CIRCUIT_SWITCH_STATUS circuitSwitchStatus;

        /**
        * Registration status of the modem.
        */
        DLMS_GSM_PACKET_SWITCH_STATUS packetSwitchStatus;

        /**
        * Registration status of the modem.
        */
        gxGSMCellInfo cellInfo;

        /**
        * Adjacent cells.
        */
        gxArray adjacentCells; //<GXAdjacentCell*>

        /**
        * Date and time when the data have been last captured.
        */
        gxtime captureTime;
    } gxGsmDiagnostic;
#endif //DLMS_IGNORE_GSM_DIAGNOSTIC

#ifndef DLMS_IGNORE_REGISTER_TABLE
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSRegisterTable
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;

        variantArray tableCellValues;
        gxArray tableCellDefinition;
        signed char scaler;
        unsigned char unit;
        unsigned char unitRead;
    } gxRegisterTable;
#endif //DLMS_IGNORE_REGISTER_TABLE

#ifndef DLMS_IGNORE_STATUS_MAPPING
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSStatusMapping
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        //TODO:
    } gxStatusMapping;
#endif //DLMS_IGNORE_STATUS_MAPPING

#ifndef DLMS_IGNORE_DISCONNECT_CONTROL
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSDisconnectControl
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        unsigned char outputState;
        DLMS_CONTROL_STATE controlState;
        DLMS_CONTROL_MODE controlMode;
    } gxDisconnectControl;
#endif //DLMS_IGNORE_DISCONNECT_CONTROL

#ifndef DLMS_IGNORE_LIMITER
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSLimiter
    */
    typedef struct
    {
        unsigned short id;
        gxtime activationTime;
        unsigned long duration;
    } gxEmergencyProfile;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSLimiter
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;

        gxObject* monitoredValue;
        //Selected attribute index of monitored value.
        signed char selectedAttributeIndex;

        dlmsVARIANT thresholdActive;
        dlmsVARIANT thresholdNormal;
        dlmsVARIANT thresholdEmergency;
        long minOverThresholdDuration;
        long minUnderThresholdDuration;
        gxEmergencyProfile emergencyProfile;
#ifdef DLMS_IGNORE_MALLOC
        gxArray emergencyProfileGroupIDs;
#else
        variantArray emergencyProfileGroupIDs;
#endif //DLMS_IGNORE_MALLOC
        unsigned char emergencyProfileActive;
        gxActionItem actionOverThreshold;
        gxActionItem actionUnderThreshold;
    } gxLimiter;
#endif //DLMS_IGNORE_LIMITER

#ifndef DLMS_IGNORE_MBUS_CLIENT

typedef enum
{
    DLMS_MBUS_ENCRYPTION_KEY_STATUS_NO_ENCRYPTION_KEY = 0,
    DLMS_MBUS_ENCRYPTION_KEY_STATUS_ENCRYPTION_KEY_SET,
    DLMS_MBUS_ENCRYPTION_KEY_STATUS_ENCRYPTION_KEY_TRANSFERRED,
    DLMS_MBUS_ENCRYPTION_KEY_STATUS_ENCRYPTION_KEY_SET_AND_TRANSFERRED,
    DLMS_MBUS_ENCRYPTION_KEY_STATUS_ENCRYPTION_KEY_INUSE
}DLMS_MBUS_ENCRYPTION_KEY_STATUS;

#ifdef DLMS_IGNORE_MALLOC
    typedef struct
    {
        unsigned char value[MAX_CAPTURE_DEFINITION_ELEMENT_LENGTH];
        unsigned short size;
    }gxCaptureDefinitionElement;

    typedef struct
    {
        gxCaptureDefinitionElement data;
        gxCaptureDefinitionElement value;
    }gxCaptureDefinition;
#endif //DLMS_IGNORE_MALLOC

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSMBusClient
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        unsigned long capturePeriod;
        unsigned char primaryAddress;
#ifndef DLMS_IGNORE_OBJECT_POINTERS
        gxObject* mBusPort;
#else
        unsigned char mBusPortReference[6];
#endif //DLMS_IGNORE_OBJECT_POINTERS
        gxArray captureDefinition;
        unsigned long identificationNumber;
        unsigned short manufacturerID;
        unsigned char dataHeaderVersion;
        unsigned char deviceType;
        unsigned char accessNumber;
        unsigned char status;
        unsigned char alarm;
        unsigned short configuration;
        DLMS_MBUS_ENCRYPTION_KEY_STATUS encryptionKeyStatus;
    } gxMBusClient;
#endif //DLMS_IGNORE_MBUS_CLIENT

#ifndef DLMS_IGNORE_PUSH_SETUP

#ifdef DLMS_IGNORE_MALLOC
    typedef struct
    {
        unsigned char value[MAX_PUSH_SETUP_TARGET_LENGTH];
        unsigned short size;
    }gxPushSetupDestination;
#endif //DLMS_IGNORE_MALLOC

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSPushSetup
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        gxArray pushObjectList;

        DLMS_SERVICE_TYPE service;

#ifdef DLMS_IGNORE_MALLOC
        gxPushSetupDestination destination;
#else
        char* destination;
#endif //DLMS_IGNORE_MALLOC

        DLMS_MESSAGE_TYPE message;

        gxArray communicationWindow;
        unsigned short randomisationStartInterval;
        unsigned char numberOfRetries;
        unsigned short repetitionDelay;
    } gxPushSetup;
#endif //DLMS_IGNORE_PUSH_SETUP

#ifndef DLMS_IGNORE_MESSAGE_HANDLER
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSMessageHandler
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        gxArray listeningWindow;
        variantArray allowedSenders;
        gxArray sendersAndActions;
    } gxMessageHandler;
#endif //DLMS_IGNORE_MESSAGE_HANDLER

#ifndef DLMS_IGNORE_PARAMETER_MONITOR

    typedef struct
    {
#ifndef DLMS_IGNORE_OBJECT_POINTERS
        gxObject* target;
#else
        DLMS_OBJECT_TYPE type;
        //Logical name.
        unsigned char logicalName[6];
#endif //DLMS_IGNORE_OBJECT_POINTERS
        signed char attributeIndex;
        dlmsVARIANT value;
    } gxChangedParameter;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSParameterMonitor
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;

        //Changed parameter.
        gxChangedParameter changedParameter;

        // Capture time.
        gxtime captureTime;

        // Changed Parameter
        gxArray parameters;
    } gxParameterMonitor;
#endif //DLMS_IGNORE_PARAMETER_MONITOR

#ifndef DLMS_IGNORE_WIRELESS_MODE_Q_CHANNEL
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSWirelessModeQChannel
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
    } gxWirelessModeQChannel;

#endif //DLMS_IGNORE_WIRELESS_MODE_Q_CHANNEL

#ifndef DLMS_IGNORE_MBUS_MASTER_PORT_SETUP
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSMBusMasterPortSetup
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        DLMS_BAUD_RATE commSpeed;
    } gxMBusMasterPortSetup;

#endif //DLMS_IGNORE_MBUS_MASTER_PORT_SETUP
    typedef enum
    {
        DLMS_PROTECTION_TYPE_AUTHENTICATION = 1,
        DLMS_PROTECTION_TYPE_ENCRYPTION = 2,
        DLMS_PROTECTION_TYPE_AUTHENTICATION_ENCRYPTION = 3
    } DLMS_PROTECTION_TYPE;

#ifndef DLMS_IGNORE_DATA_PROTECTION
    typedef enum
    {
        //Used with identified_key_info_options.
        DLMS_KEY_INFO_TYPE_IDENTIFIED_KEY = 0,
        //Used with wrapped_key_info_options.
        DLMS_KEY_INFO_TYPE_WRAPPED_KEY = 1,
        //Used with agreed_key_info_options.
        DLMS_KEY_INFO_TYPE_AGREED_KEY = 2
    } DLMS_KEY_INFO_TYPE;

    typedef enum
    {
        DLMS_IDENTIFIED_KEY_INFO_OPTIONS_GLOBAL_UNICAST_ENCRYPTION_KEY = 0,
        DLMS_IDENTIFIED_KEY_INFO_OPTIONS_GLOBAL_BROADCAST_ENCRYPTION_KEY = 1
    } DLMS_IDENTIFIED_KEY_INFO_OPTIONS;

    typedef enum
    {
        DLMS_RESTRICTION_TYPE_NONE = 0,
        //Restriction by date.
        DLMS_RESTRICTION_TYPE_DATE = 1,
        //Restriction by entry.
        DLMS_RESTRICTION_TYPE_ENTRY = 2
    } DLMS_RESTRICTION_TYPE;

    //Global key types.
    typedef enum
    {
        /**
        * Global unicast encryption key. <br>
        * Client and server uses this message to send Ephemeral Public Key to other
        * party.
        */
        DLMS_GLOBAL_KEY_TYPE_UNICAST_ENCRYPTION,
        /**
         * Global broadcast encryption key.
        */
        DLMS_GLOBAL_KEY_TYPE_BROADCAST_ENCRYPTION,
        /**
         * Authentication key.
        */
        DLMS_GLOBAL_KEY_TYPE_AUTHENTICATION,
        /**
         * Key Encrypting Key, also known as Master key.
        */
        DLMS_GLOBAL_KEY_TYPE_KEK
    }DLMS_GLOBAL_KEY_TYPE;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMS
    */
    typedef struct
    {
        unsigned char id;
        //Key ciphered data.
        gxByteBuffer data;
    } gxWrappedKeyInfoOptions;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMS
    */
    typedef struct
    {
        gxByteBuffer parameters;
        gxByteBuffer cipheredData;
    }
    gxAgreedKeyInfoOptions;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMS
    */
    typedef struct
    {
        DLMS_KEY_INFO_TYPE type;
        DLMS_IDENTIFIED_KEY_INFO_OPTIONS identifiedOptions;
        gxWrappedKeyInfoOptions wrappedKeyoptions;
        gxAgreedKeyInfoOptions agreedOptions;
    } gxKeyinfo;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMS
    */
    typedef struct
    {
        //Transaction id.
        gxByteBuffer id;
        //Originator_system_title
        gxByteBuffer originator;
        //Recipient System title.
        gxByteBuffer recipient;
        //Other information
        gxByteBuffer information;
        gxKeyinfo info;
    } gxProtectionOptions;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMS
    */
    typedef struct
    {
        DLMS_PROTECTION_TYPE type;
        gxProtectionOptions options;
    } gxProtectionParameter;

#endif //DLMS_IGNORE_DATA_PROTECTION

#ifndef DLMS_IGNORE_EVENT
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSEvent
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
    } gxEvent;
#endif //DLMS_IGNORE_EVENT

#ifndef DLMS_IGNORE_ZIG_BEE_SAS_STARTUP
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSZigBeeSasStartup
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
    } gxZigBeeSasStartup;

#endif //DLMS_IGNORE_ZIG_BEE_SAS_STARTUP

#ifndef DLMS_IGNORE_ZIG_BEE_SAS_JOIN
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSZigBeeSasJoin
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
    } gxZigBeeSasJoin;
#endif //DLMS_IGNORE_ZIG_BEE_SAS_JOIN

#ifndef DLMS_IGNORE_ZIG_BEE_SAS_APS_FRAGMENTATION
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSZigBeeSasApsFragmentation
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
    } gxZigBeeSasApsFragmentation;
#endif //DLMS_IGNORE_ZIG_BEE_SAS_APS_FRAGMENTATION

#ifndef DLMS_IGNORE_DATA_PROTECTION
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSDataProtection
    */
    typedef struct
    {
#ifndef DLMS_IGNORE_OBJECT_POINTERS
        gxObject* target;
#else
        DLMS_OBJECT_TYPE type;
        //Logical name.
        unsigned char logicalName[6];
#endif //DLMS_IGNORE_OBJECT_POINTERS
        //attribute index.
        int attributeIndex;
        //data index
        int dataIndex;
    }gxDataProtectionObject;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSDataProtection
    */
    typedef struct
    {
        gxObject base;
        gxByteBuffer protection_buffer;
        objectArray protectionObjectList;
        gxArray protectionParametersGet; //gxProtectionParameter.
        gxArray protectionParametersSet; //gxProtectionParameter.
        DLMS_REQUIRED_PROTECTION requiredProtection;
    } gxDataProtection;
#endif //DLMS_IGNORE_DATA_PROTECTION

#ifndef DLMS_IGNORE_ACCOUNT
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccountModeAndStatus
    */
    typedef struct
    {
        //CREDIT_MODE = 1, PREPAYMENT_MODE = 2
        unsigned char paymentMode;
        // NEW_INACTIVE_ACCOUNT = 1, ACCOUNT_ACTIVE = 2, ACCOUNT_CLOSED = 3
        unsigned char accountStatus;
    }gxAccountModeAndStatus;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSCreditChargeConfiguration
    */
    typedef struct
    {
        unsigned char creditReference[6];
        unsigned char chargeReference[6];
        DLMS_CREDIT_COLLECTION_CONFIGURATION collectionConfiguration;
    }gxCreditChargeConfiguration;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSTokenGatewayConfiguration
    */
    typedef struct
    {
        unsigned char creditReference[6];
        unsigned char tokenProportion;
    }gxTokenGatewayConfiguration;

#ifdef DLMS_IGNORE_MALLOC
    typedef struct
    {
        char value[MAX_CURRENCY_NAME_LENGTH];
        unsigned short size;
    }gxCurrencyName;
#endif //DLMS_IGNORE_MALLOC

    /**
    Used currency.
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
    */
    typedef struct
    {
        // Currency name.
#ifdef DLMS_IGNORE_MALLOC
        gxCurrencyName name;
#else
        char* name;
#endif //DLMS_IGNORE_MALLOC
        // Currency scale.
        signed char scale;
        // Currency unit.
        DLMS_CURRENCY unit;
    }gxCurrency;

    /**
    * Online help:<br/>
    * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;

        /**
        * Payment mode.<br/>
        * Online help:<br/>
        * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
        */
        DLMS_ACCOUNT_PAYMENT_MODE paymentMode;

        /**
        * Account status.<br/>
        * Online help:<br/>
        * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
        */
        DLMS_ACCOUNT_STATUS accountStatus;

        /**
        * Credit In Use.<br/>
        * Online help:<br/>
        * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
        */
        unsigned char currentCreditInUse;

        /**
        * Credit status.<br/>
        * Online help:<br/>
        * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
        */
        DLMS_ACCOUNT_CREDIT_STATUS currentCreditStatus;

        /**
        * The available_credit attribute is the sum of the positive current credit
        * amount values in the instances of the Credit class. <br/>
        * Online help:<br/>
        * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
        */
        int availableCredit;

        /**
        * Amount to clear.<br/>
        * Online help:<br/>
        * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
        */
        int amountToClear;

        /**
        * Conjunction with the amount to clear, and is included in the description
        * of that attribute.<br/>
        * Online help:<br/>
        * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
        */
        int clearanceThreshold;

        /**
        * Aggregated debt.<br/>
        * Online help:<br/>
        * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
        */
        int aggregatedDebt;

        /**
        * Credit references.<br/>
        * Online help:<br/>
        * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
        */
        gxArray creditReferences;//List<String>

        /**
        * Charge references.<br/>
        * Online help:<br/>
        * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
        */
        gxArray chargeReferences;//List<String>
        /**
        * Credit charge configurations.<br/>
        * Online help:<br/>
        * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
        */
        gxArray creditChargeConfigurations;//List<GXCreditChargeConfiguration>

        /**
        * Token gateway configurations.<br/>
        * Online help:<br/>
        * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
        */
        gxArray tokenGatewayConfigurations;//List<GXTokenGatewayConfiguration>
        /**
        * Account activation time.<br/>
        * Online help:<br/>
        * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
        */
        gxtime accountActivationTime;

        /**
        * Account closure time.<br/>
        * Online help:<br/>
        * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
        */
        gxtime accountClosureTime;

        /**
        * Currency.<br/>
        * Online help:<br/>
        * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
        */
        gxCurrency currency;
        /**
        * Low credit threshold.<br/>
        * Online help:<br/>
        * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
        */
        int lowCreditThreshold;
        /**
        * Next credit available threshold.<br/>
        * Online help:<br/>
        * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
        */
        int nextCreditAvailableThreshold;
        /**
        * Max Provision.<br/>
        * Online help:<br/>
        * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
        */
        unsigned short maxProvision;

        /**
        * Max provision period.<br/>
        * Online help:<br/>
        * http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSAccount
        */
        int maxProvisionPeriod;
    } gxAccount;
#endif //DLMS_IGNORE_ACCOUNT

#ifndef DLMS_IGNORE_CREDIT
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSCredit
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;

        long currentCreditAmount;
        unsigned char type;
        unsigned char priority;
        long warningThreshold;
        long limit;
        bitArray creditConfiguration;
        unsigned char status;
        long presetCreditAmount;
        long creditAvailableThreshold;
        gxtime period;
    } gxCredit;

#endif //DLMS_IGNORE_CREDIT

#ifndef DLMS_IGNORE_CHARGE
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSCharge
    */
    typedef struct
    {
        signed char commodityScale;
        signed char priceScale;
    } gxChargePerUnitScaling;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSCharge
    */
    typedef struct
    {
#ifndef DLMS_IGNORE_OBJECT_POINTERS
        gxObject* target;
#else
        DLMS_OBJECT_TYPE type;
        unsigned char logicalName[6];
#endif //DLMS_IGNORE_OBJECT_POINTERS
        signed char attributeIndex;
    } gxCommodity;

#ifdef DLMS_IGNORE_MALLOC
    typedef struct
    {
        unsigned char data[MAX_CHARGE_TABLE_INDEX_LENGTH];
        unsigned short size;
    }gxChargeTableIndex;
#endif //DLMS_IGNORE_MALLOC

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSCharge
    */
    typedef struct
    {
#ifdef DLMS_IGNORE_MALLOC
        gxChargeTableIndex index;
#else
        gxByteBuffer index;
#endif //DLMS_IGNORE_MALLOC
        short chargePerUnit;
    } gxChargeTable;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSCharge
    */
    typedef struct
    {
        gxChargePerUnitScaling chargePerUnitScaling;
        gxCommodity commodity;
        gxArray chargeTables;
    } gxUnitCharge;

    //---------------------------------------------------------------------------
    // Online help:
    //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSCharge
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        short totalAmountPaid;

        //CONSUMPTION_BASED_COLLECTION, TIME_BASED_COLLECTION, PAYMENT_EVENT_BASED_COLLECTION
        unsigned char chargeType;
        unsigned char priority;
        gxUnitCharge unitChargeActive;
        gxUnitCharge unitChargePassive;
        gxtime unitChargeActivationTime;
        unsigned int period;
        bitArray chargeConfiguration;
        gxtime lastCollectionTime;
        long lastCollectionAmount;
        long totalAmountRemaining;
        unsigned short proportion;
    } gxCharge;
#endif //DLMS_IGNORE_CHARGE

#ifndef DLMS_IGNORE_TOKEN_GATEWAY
#ifdef DLMS_IGNORE_MALLOC
    typedef struct
    {
        unsigned char value[MAX_TOKEN_GATEWAY_DESCRIPTION_LENGTH];
        unsigned short size;
    }gxTokenGatewayDescription;
#endif //DLMS_IGNORE_MALLOC

    //---------------------------------------------------------------------------
    // Online help:
    //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSTokenGateway
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;
        // Token.
        //  Online help:<br/>
        //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSTokenGateway
        gxByteBuffer token;

        // Time.
        //  Online help:<br/>
        //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSTokenGateway
        gxtime time;

        // Descriptions.
        //  Online help:<br/>
        //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSTokenGateway
        gxArray descriptions;

        // Token Delivery method.
        //  Online help:<br/>
        //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSTokenGateway
        DLMS_TOKEN_DELIVERY deliveryMethod;

        //  Token status code.
        //  Online help:<br/>
        //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSTokenGateway
        DLMS_TOKEN_STATUS_CODE status;

        // Token data value.
        //  Online help:<br/>
        //  http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSTokenGateway
        bitArray dataValue;
    } gxTokenGateway;
#endif //DLMS_IGNORE_TOKEN_GATEWAY

#ifndef DLMS_IGNORE_ZIG_BEE_NETWORK_CONTROL
    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSZigBeeNetworkControl
    */
    typedef struct
    {
        gxByteBuffer macAddress;
        bitArray status;
        char maxRSSI;
        char averageRSSI;
        char minRSSI;
        unsigned char maxLQI;
        unsigned char averageLQI;
        unsigned char minLQI;
        gxtime lastCommunicationDateTime;
        unsigned char numberOfHops;
        unsigned char transmissionFailures;
        unsigned char transmissionSuccesses;
        unsigned char applicationVersion;
        unsigned char stackVersion;
    } gxActiveDevice;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSZigBeeNetworkControl
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;

        unsigned char enableDisableJoining;
        unsigned short joinTimeout;
        gxArray activeDevices;
    } gxZigBeeNetworkControl;

#endif //DLMS_IGNORE_ZIG_BEE_NETWORK_CONTROL

#ifndef DLMS_IGNORE_COMPACT_DATA

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSCompactData
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;

        gxByteBuffer buffer;
        gxArray captureObjects; //gxkey<gxObject*, gxTarget*>
        unsigned char templateId;
        gxByteBuffer templateDescription;
        DLMS_CAPTURE_METHOD captureMethod;
#ifdef DLMS_ITALIAN_STANDARD
        //Some meters require that there is a array count in data.
        unsigned char appendAA;
#endif //DLMS_ITALIAN_STANDARD
    } gxCompactData;
#endif //DLMS_IGNORE_COMPACT_DATA

#ifdef DLMS_ITALIAN_STANDARD

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSTariffPlan
    */
    typedef enum
    {
        // 1st january of every year.
        DLMS_WEEKLY_ACTIVATION_JANUARY_1,
        // 6st january of every year.
        DLMS_WEEKLY_ACTIVATION_JANUARY_6,
        // Easter Monday of of every year.
        DLMS_WEEKLY_ACTIVATION_EASTER_MONDAY,
        // 25th April of every year
        DLMS_WEEKLY_ACTIVATION_APRIL_25,
        // 1st May of every year.
        DLMS_WEEKLY_ACTIVATION_MAY_1,
        // 2nd June of every year.
        DLMS_WEEKLY_ACTIVATION_JUNE_2,
        // 15th August of every year
        DLMS_WEEKLY_ACTIVATION_AUGUST_15,
        // 1st November of every year.
        DLMS_WEEKLY_ACTIVATION_NOVEMBER_1,
        // 8th December of every year
        DLMS_WEEKLY_ACTIVATION_DECEMBER_8,
        // 25th December of every year.
        DLMS_WEEKLY_ACTIVATION_DECEMBER_25,
        //  26th December of every year.
        DLMS_WEEKLY_ACTIVATION_DECEMBER_26
    }DLMS_WEEKLY_ACTIVATION;


    /**
    The default tariff.
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSTariffPlan
    */
    typedef enum
    {
        // Not active.
        DLMS_DEFAULT_TARIFF_BAND_NONE = 0,
        // Tariff band 1.
        DLMS_DEFAULT_TARIFF_BAND_TARIFF_BAND_1,
        // Tariff band 2.
        DLMS_DEFAULT_TARIFF_BAND_TARIFF_BAND_2,
        // Tariff band 3.
        DLMS_DEFAULT_TARIFF_BAND_TARIFF_BAND_3
    }DLMS_DEFAULT_TARIFF_BAND;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSTariffPlan
    */
    typedef struct
    {
        // Start hour of the interval.
        unsigned char startHour;
        // Tariff used in the current interval
        DLMS_DEFAULT_TARIFF_BAND intervalTariff;
        // Is interval used.
        unsigned char useInterval;
    } gxInterval;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSTariffPlan
    */
    typedef struct
    {
        // Day of month when the season will become active.
        unsigned char dayOfMonth;
        // Month of the year when the season will become active.
        unsigned char month;
        // Working day intervals.
        gxInterval workingDayIntervals[5];
        // Saturday intervals.
        gxInterval saturdayIntervals[5];
        // Saturday intervals.
        gxInterval holidayIntervals[5];
    } gxBandDescriptor;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSTariffPlan
    */
    typedef struct
    {
        // Is tariff plan enabled.
        unsigned char defaultTariffBand;
        // Winter season.
        gxBandDescriptor winterSeason;
        // Summer season.
        gxBandDescriptor summerSeason;
        // Seasons.
        bitArray weeklyActivation;
        // Seasons.
        gxArray specialDays; //UInt16[]
    } gxPlan;

    /**
    ---------------------------------------------------------------------------
    Online help:
    http://www.gurux.fi/Gurux.DLMS.Objects.GXDLMSTariffPlan
    */
    typedef struct
    {
        /**
        * Base class where class is derived.
        */
        gxObject base;

        // Calendar Name.
        char* calendarName;
        //Is tariff plan enabled.
        unsigned char enabled;
        // Tariff plan.
        gxPlan plan;
        // Activation date and time.
        gxtime activationTime;
    } gxTariffPlan;

#endif //DLMS_ITALIAN_STANDARD

    void obj_clear(gxObject* object);

    int obj_clearProfileGenericBuffer(gxArray* buffer);

    int obj_clearSapList(gxArray* buffer);

#if !(defined(DLMS_IGNORE_PROFILE_GENERIC) && defined(DLMS_IGNORE_COMPACT_DATA) && defined(DLMS_IGNORE_PUSH_SETUP))
    int obj_clearPushObjectList(gxArray* buffer);
    int obj_clearProfileGenericCaptureObjects(gxArray* captureObjects);
#endif //!(defined(DLMS_IGNORE_PROFILE_GENERIC) && defined(DLMS_IGNORE_COMPACT_DATA))

    int obj_clearSeasonProfile(gxArray* list);

    int obj_clearWeekProfileTable(gxArray* list);

    int obj_clearDayProfileTable(gxArray* list);

    int obj_clearRegisterMonitorActions(gxArray* list);

    int obj_clearModemConfigurationInitialisationStrings(gxArray* list);

    int obj_clearScriptTable(gxArray* list);

#if !(defined(DLMS_IGNORE_OBJECT_POINTERS) || defined(DLMS_IGNORE_MALLOC))
    int obj_clearRegisterActivationAssignment(objectArray* list);
#else
    int obj_clearRegisterActivationAssignment(gxArray* list);
#endif //!(defined(DLMS_IGNORE_OBJECT_POINTERS) || defined(DLMS_IGNORE_MALLOC))

    int obj_clearRegisterActivationMaskList(gxArray* list);

    int obj_clearIP4SetupOptions(gxArray* list);

    int obj_clearPPPSetupIPCPOptions(gxArray* list);
    int obj_clearPPPSetupLCPOptions(gxArray* list);

    int obj_clearActiveDevices(gxArray* list);

    int obj_clearChargeTables(gxArray* list);

    int obj_clearCreditChargeConfigurations(gxArray* list);

    int obj_clearTokenGatewayConfigurations(gxArray* list);

    //Get amount of attributes in COSEM object.
    unsigned char obj_attributeCount(
        gxObject* object);

    //Get amount of methods in COSEM object.
    unsigned char obj_methodCount(
        gxObject* object);

    int obj_getAttributeIndexToRead(
        gxObject* object,
        gxByteBuffer* ba);

#if !defined(DLMS_IGNORE_MALLOC)
    int obj_updateAttributeAccessModes(gxObject* object, variantArray* arr);
#endif //!defined(DLMS_IGNORE_MALLOC)

    //Returns collection of attributes to read.
    int obj_getAttributeIndexToRead(
        gxObject* object,
        gxByteBuffer* ba);

#ifndef DLMS_IGNORE_DATA_PROTECTION
    void clear_ProtectionParameter(gxProtectionParameter* target);
    void init_ProtectionParameter(gxProtectionParameter* target);
#endif //DLMS_IGNORE_DATA_PROTECTION

#ifndef DLMS_IGNORE_PARAMETER_MONITOR
    int obj_clearParametersList(gxArray* buffer);
#endif //DLMS_IGNORE_PARAMETER_MONITOR

    int obj_clearCertificateInfo(gxArray* arr);

    //Clear user list.
    int obj_clearUserList(
        gxArray* list);

#define BASE(X) &X.base

#define INIT_OBJECT(X, Y, Z) cosem_init2(&X.base, Y, Z)

#ifdef  __cplusplus
}
#endif

#endif //OBJECTS_H
