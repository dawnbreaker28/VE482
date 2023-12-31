/******************************************************************************
 *
 * Name: actypes.h - Common data types for the entire ACPI subsystem
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999 - 2010, Intel Corp.
 * All rights reserved.
 *
 * 2. License
 *
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights.  You may have additional license terms from the party that provided
 * you this software, covering your right to use that party's intellectual
 * property rights.
 *
 * 2.2. Intel grants, free of charge, to any person ("Licensee") obtaining a
 * copy of the source code appearing in this file ("Covered Code") an
 * irrevocable, perpetual, worldwide license under Intel's copyrights in the
 * base code distributed originally by Intel ("Original Intel Code") to copy,
 * make derivatives, distribute, use and display any portion of the Covered
 * Code in any form, with the right to sublicense such rights; and
 *
 * 2.3. Intel grants Licensee a non-exclusive and non-transferable patent
 * license (with the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell,
 * offer to sell, and import the Covered Code and derivative works thereof
 * solely to the minimum extent necessary to exercise the above copyright
 * license, and in no event shall the patent license extend to any additions
 * to or modifications of the Original Intel Code.  No other license or right
 * is granted directly or by implication, estoppel or otherwise;
 *
 * The above copyright and patent license is granted only if the following
 * conditions are met:
 *
 * 3. Conditions
 *
 * 3.1. Redistribution of Source with Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification with rights to further distribute source must include
 * the above Copyright Notice, the above License, this list of Conditions,
 * and the following Disclaimer and Export Compliance provision.  In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change.  Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee.  Licensee
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution.  In
 * addition, Licensee may not authorize further sublicense of source of any
 * portion of the Covered Code, and must include terms to the effect that the
 * license from Licensee to its licensee is limited to the intellectual
 * property embodied in the software Licensee provides to its licensee, and
 * not to intellectual property embodied in modifications its licensee may
 * make.
 *
 * 3.3. Redistribution of Executable. Redistribution in executable form of any
 * substantial portion of the Covered Code or modification must reproduce the
 * above Copyright Notice, and the following Disclaimer and Export Compliance
 * provision in the documentation and/or other materials provided with the
 * distribution.
 *
 * 3.4. Intel retains all right, title, and interest in and to the Original
 * Intel Code.
 *
 * 3.5. Neither the name Intel nor any other trademark owned or controlled by
 * Intel shall be used in advertising or otherwise to promote the sale, use or
 * other dealings in products derived from or relating to the Covered Code
 * without prior written authorization from Intel.
 *
 * 4. Disclaimer and Export Compliance
 *
 * 4.1. INTEL MAKES NO WARRANTY OF ANY KIND REGARDING ANY SOFTWARE PROVIDED
 * HERE.  ANY SOFTWARE ORIGINATING FROM INTEL OR DERIVED FROM INTEL SOFTWARE
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT,  ASSISTANCE,
 * INSTALLATION, TRAINING OR OTHER SERVICES.  INTEL WILL NOT PROVIDE ANY
 * UPDATES, ENHANCEMENTS OR EXTENSIONS.  INTEL SPECIFICALLY DISCLAIMS ANY
 * IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT AND FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * 4.2. IN NO EVENT SHALL INTEL HAVE ANY LIABILITY TO LICENSEE, ITS LICENSEES
 * OR ANY OTHER THIRD PARTY, FOR ANY LOST PROFITS, LOST DATA, LOSS OF USE OR
 * COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, OR FOR ANY INDIRECT,
 * SPECIAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT, UNDER ANY
 * CAUSE OF ACTION OR THEORY OF LIABILITY, AND IRRESPECTIVE OF WHETHER INTEL
 * HAS ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.  THESE LIMITATIONS
 * SHALL APPLY NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL PURPOSE OF ANY
 * LIMITED REMEDY.
 *
 * 4.3. Licensee shall not export, either directly or indirectly, any of this
 * software or system incorporating such software without first obtaining any
 * required license or other approval from the U. S. Department of Commerce or
 * any other agency or department of the United States Government.  In the
 * event Licensee exports any such software from the United States or
 * re-exports any such software from a foreign destination, Licensee shall
 * ensure that the distribution and export/re-export of the software is in
 * compliance with all laws, regulations, orders, or other restrictions of the
 * U.S. Export Administration Regulations. Licensee agrees that neither it nor
 * any of its subsidiaries will export/re-export any technical data, process,
 * software, or service, directly or indirectly, to any country for which the
 * United States government or any agency thereof requires an export license,
 * other governmental approval, or letter of assurance, without first obtaining
 * such license, approval or letter.
 *
 *****************************************************************************/

#ifndef __ACTYPES_H__
#define __ACTYPES_H__

/* acpisrc:StructDefs -- for acpisrc conversion */

/*
 * ACPI_MACHINE_WIDTH must be specified in an OS- or compiler-dependent header
 * and must be either 32 or 64. 16-bit ACPICA is no longer supported, as of
 * 12/2006.
 */
#ifndef ACPI_MACHINE_WIDTH
#error ACPI_MACHINE_WIDTH not defined
#endif

/*! [Begin] no source code translation */

/*
 * Data type ranges
 * Note: These macros are designed to be compiler independent as well as
 * working around problems that some 32-bit compilers have with 64-bit
 * constants.
 */
#define ACPI_UINT8_MAX                  (UINT8) (~((UINT8)  0)) /* 0xFF               */
#define ACPI_UINT16_MAX                 (UINT16)(~((UINT16) 0)) /* 0xFFFF             */
#define ACPI_UINT32_MAX                 (UINT32)(~((UINT32) 0)) /* 0xFFFFFFFF         */
#define ACPI_UINT64_MAX                 (UINT64)(~((UINT64) 0)) /* 0xFFFFFFFFFFFFFFFF */
#define ACPI_ASCII_MAX                  0x7F


/*
 * Architecture-specific ACPICA Subsystem Data Types
 *
 * The goal of these types is to provide source code portability across
 * 16-bit, 32-bit, and 64-bit targets.
 *
 * 1) The following types are of fixed size for all targets (16/32/64):
 *
 * BOOLEAN      Logical boolean
 *
 * UINT8        8-bit  (1 byte) unsigned value
 * UINT16       16-bit (2 byte) unsigned value
 * UINT32       32-bit (4 byte) unsigned value
 * UINT64       64-bit (8 byte) unsigned value
 *
 * INT16        16-bit (2 byte) signed value
 * INT32        32-bit (4 byte) signed value
 * INT64        64-bit (8 byte) signed value
 *
 * COMPILER_DEPENDENT_UINT64/INT64 - These types are defined in the
 * compiler-dependent header(s) and were introduced because there is no common
 * 64-bit integer type across the various compilation models, as shown in
 * the table below.
 *
 * Datatype  LP64 ILP64 LLP64 ILP32 LP32 16bit
 * char      8    8     8     8     8    8
 * short     16   16    16    16    16   16
 * _int32         32
 * int       32   64    32    32    16   16
 * long      64   64    32    32    32   32
 * long long            64    64
 * pointer   64   64    64    32    32   32
 *
 * Note: ILP64 and LP32 are currently not supported.
 *
 *
 * 2) These types represent the native word size of the target mode of the
 * processor, and may be 16-bit, 32-bit, or 64-bit as required. They are
 * usually used for memory allocation, efficient loop counters, and array
 * indexes. The types are similar to the size_t type in the C library and are
 * required because there is no C type that consistently represents the native
 * data width. ACPI_SIZE is needed because there is no guarantee that a
 * kernel-level C library is present.
 *
 * ACPI_SIZE        16/32/64-bit unsigned value
 * ACPI_NATIVE_INT  16/32/64-bit signed value
 *
 */

/*******************************************************************************
 *
 * Common types for all compilers, all targets
 *
 ******************************************************************************/

typedef unsigned char                   BOOLEAN;
typedef unsigned char                   UINT8;
typedef unsigned short                  UINT16;
typedef COMPILER_DEPENDENT_UINT64       UINT64;
typedef COMPILER_DEPENDENT_INT64        INT64;

/*! [End] no source code translation !*/


/*******************************************************************************
 *
 * Types specific to 64-bit targets
 *
 ******************************************************************************/

#if ACPI_MACHINE_WIDTH == 64

/*! [Begin] no source code translation (keep the typedefs as-is) */

typedef unsigned int                    UINT32;
typedef int                             INT32;

/*! [End] no source code translation !*/


typedef INT64                           ACPI_NATIVE_INT;
typedef UINT64                          ACPI_SIZE;
typedef UINT64                          ACPI_IO_ADDRESS;
typedef UINT64                          ACPI_PHYSICAL_ADDRESS;

#define ACPI_MAX_PTR                    ACPI_UINT64_MAX
#define ACPI_SIZE_MAX                   ACPI_UINT64_MAX
#define ACPI_USE_NATIVE_DIVIDE          /* Has native 64-bit integer support */

/*
 * In the case of the Itanium Processor Family (IPF), the hardware does not
 * support misaligned memory transfers. Set the MISALIGNMENT_NOT_SUPPORTED flag
 * to indicate that special precautions must be taken to avoid alignment faults.
 * (IA64 or ia64 is currently used by existing compilers to indicate IPF.)
 *
 * Note: EM64T and other X86-64 processors support misaligned transfers,
 * so there is no need to define this flag.
 */
#if defined (__IA64__) || defined (__ia64__)
#define ACPI_MISALIGNMENT_NOT_SUPPORTED
#endif


/*******************************************************************************
 *
 * Types specific to 32-bit targets
 *
 ******************************************************************************/

#elif ACPI_MACHINE_WIDTH == 32

/*! [Begin] no source code translation (keep the typedefs as-is) */

typedef unsigned int                    UINT32;
typedef int                             INT32;

/*! [End] no source code translation !*/


typedef INT32                           ACPI_NATIVE_INT;
typedef UINT32                          ACPI_SIZE;
typedef UINT32                          ACPI_IO_ADDRESS;
typedef UINT32                          ACPI_PHYSICAL_ADDRESS;

#define ACPI_MAX_PTR                    ACPI_UINT32_MAX
#define ACPI_SIZE_MAX                   ACPI_UINT32_MAX

#else

/* ACPI_MACHINE_WIDTH must be either 64 or 32 */

#error unknown ACPI_MACHINE_WIDTH
#endif


/*******************************************************************************
 *
 * OS-dependent types
 *
 * If the defaults below are not appropriate for the host system, they can
 * be defined in the OS-specific header, and this will take precedence.
 *
 ******************************************************************************/

/* Value returned by AcpiOsGetThreadId */

#ifndef ACPI_THREAD_ID
#define ACPI_THREAD_ID                  ACPI_SIZE
#endif

/* Flags for AcpiOsAcquireLock/AcpiOsReleaseLock */

#ifndef ACPI_CPU_FLAGS
#define ACPI_CPU_FLAGS                  ACPI_SIZE
#endif

/* Object returned from AcpiOsCreateCache */

#ifndef ACPI_CACHE_T
#ifdef ACPI_USE_LOCAL_CACHE
#define ACPI_CACHE_T                    ACPI_MEMORY_LIST
#else
#define ACPI_CACHE_T                    void *
#endif
#endif

/*
 * Synchronization objects - Mutexes, Semaphores, and SpinLocks
 */
#if (ACPI_MUTEX_TYPE == ACPI_BINARY_SEMAPHORE)
/*
 * These macros are used if the host OS does not support a mutex object.
 * Map the OSL Mutex interfaces to binary semaphores.
 */
#define ACPI_MUTEX                      ACPI_SEMAPHORE
#define AcpiOsCreateMutex(OutHandle)    AcpiOsCreateSemaphore (1, 1, OutHandle)
#define AcpiOsDeleteMutex(Handle)       (void) AcpiOsDeleteSemaphore (Handle)
#define AcpiOsAcquireMutex(Handle,Time) AcpiOsWaitSemaphore (Handle, 1, Time)
#define AcpiOsReleaseMutex(Handle)      (void) AcpiOsSignalSemaphore (Handle, 1)
#endif

/* Configurable types for synchronization objects */

#ifndef ACPI_SPINLOCK
#define ACPI_SPINLOCK                   void *
#endif

#ifndef ACPI_SEMAPHORE
#define ACPI_SEMAPHORE                  void *
#endif

#ifndef ACPI_MUTEX
#define ACPI_MUTEX                      void *
#endif


/*******************************************************************************
 *
 * Compiler-dependent types
 *
 * If the defaults below are not appropriate for the host compiler, they can
 * be defined in the compiler-specific header, and this will take precedence.
 *
 ******************************************************************************/

/* Use C99 uintptr_t for pointer casting if available, "void *" otherwise */

#ifndef ACPI_UINTPTR_T
#define ACPI_UINTPTR_T                  void *
#endif

/*
 * ACPI_PRINTF_LIKE is used to tag functions as "printf-like" because
 * some compilers can catch printf format string problems
 */
#ifndef ACPI_PRINTF_LIKE
#define ACPI_PRINTF_LIKE(c)
#endif

/*
 * Some compilers complain about unused variables. Sometimes we don't want to
 * use all the variables (for example, _AcpiModuleName). This allows us
 * to to tell the compiler in a per-variable manner that a variable
 * is unused
 */
#ifndef ACPI_UNUSED_VAR
#define ACPI_UNUSED_VAR
#endif

/*
 * All ACPICA functions that are available to the rest of the kernel are
 * tagged with this macro which can be defined as appropriate for the host.
 */
#ifndef ACPI_EXPORT_SYMBOL
#define ACPI_EXPORT_SYMBOL(Symbol)
#endif


/******************************************************************************
 *
 * ACPI Specification constants (Do not change unless the specification changes)
 *
 *****************************************************************************/

/* Number of distinct FADT-based GPE register blocks (GPE0 and GPE1) */

#define ACPI_MAX_GPE_BLOCKS             2

/* Default ACPI register widths */

#define ACPI_GPE_REGISTER_WIDTH         8
#define ACPI_PM1_REGISTER_WIDTH         16
#define ACPI_PM2_REGISTER_WIDTH         8
#define ACPI_PM_TIMER_WIDTH             32

/* Names within the namespace are 4 bytes long */

#define ACPI_NAME_SIZE                  4
#define ACPI_PATH_SEGMENT_LENGTH        5           /* 4 chars for name + 1 char for separator */
#define ACPI_PATH_SEPARATOR             '.'

/* Sizes for ACPI table headers */

#define ACPI_OEM_ID_SIZE                6
#define ACPI_OEM_TABLE_ID_SIZE          8

/* ACPI/PNP hardware IDs */

#define PCI_ROOT_HID_STRING             "PNP0A03"
#define PCI_EXPRESS_ROOT_HID_STRING     "PNP0A08"

/* PM Timer ticks per second (HZ) */

#define PM_TIMER_FREQUENCY              3579545


/*******************************************************************************
 *
 * Independent types
 *
 ******************************************************************************/

/* Logical defines and NULL */

#ifdef FALSE
#undef FALSE
#endif
#define FALSE                           (1 == 0)

#ifdef TRUE
#undef TRUE
#endif
#define TRUE                            (1 == 1)

#ifndef NULL
#define NULL                            (void *) 0
#endif


/*
 * Miscellaneous types
 */
typedef UINT32                          ACPI_STATUS;    /* All ACPI Exceptions */
typedef UINT32                          ACPI_NAME;      /* 4-byte ACPI name */
typedef char *                          ACPI_STRING;    /* Null terminated ASCII string */
typedef void *                          ACPI_HANDLE;    /* Actually a ptr to a NS Node */


/* Owner IDs are used to track namespace nodes for selective deletion */

typedef UINT8                           ACPI_OWNER_ID;
#define ACPI_OWNER_ID_MAX               0xFF


typedef struct uint64_struct
{
    UINT32                          Lo;
    UINT32                          Hi;

} UINT64_STRUCT;

typedef union uint64_overlay
{
    UINT64                          Full;
    UINT64_STRUCT                   Part;

} UINT64_OVERLAY;


#define ACPI_INTEGER_BIT_SIZE           64
#define ACPI_MAX_DECIMAL_DIGITS         20  /* 2^64 = 18,446,744,073,709,551,616 */
#define ACPI_MAX64_DECIMAL_DIGITS       20
#define ACPI_MAX32_DECIMAL_DIGITS       10
#define ACPI_MAX16_DECIMAL_DIGITS        5
#define ACPI_MAX8_DECIMAL_DIGITS         3

/*
 * Constants with special meanings
 */
#define ACPI_ROOT_OBJECT                ACPI_ADD_PTR (ACPI_HANDLE, NULL, ACPI_MAX_PTR)
#define ACPI_WAIT_FOREVER               0xFFFF  /* UINT16, as per ACPI spec */
#define ACPI_DO_NOT_WAIT                0

/*
 * Obsolete: Acpi integer width. In ACPI version 1 (1996), integers are 32 bits.
 * In ACPI version 2 (2000) and later, integers are 64 bits. Note that this
 * pertains to the ACPI integer type only, not to other integers used in the
 * implementation of the ACPICA subsystem.
 *
 * 01/2010: This type is obsolete and has been removed from the entire ACPICA
 * code base. It remains here for compatibility with device drivers that use
 * the type. However, it will be removed in the future.
 */
typedef UINT64                          ACPI_INTEGER;
#define ACPI_INTEGER_MAX                ACPI_UINT64_MAX


/*******************************************************************************
 *
 * Commonly used macros
 *
 ******************************************************************************/

/* Data manipulation */

#define ACPI_LOBYTE(Integer)            ((UINT8)   (UINT16)(Integer))
#define ACPI_HIBYTE(Integer)            ((UINT8) (((UINT16)(Integer)) >> 8))
#define ACPI_LOWORD(Integer)            ((UINT16)  (UINT32)(Integer))
#define ACPI_HIWORD(Integer)            ((UINT16)(((UINT32)(Integer)) >> 16))
#define ACPI_LODWORD(Integer64)         ((UINT32)  (UINT64)(Integer64))
#define ACPI_HIDWORD(Integer64)         ((UINT32)(((UINT64)(Integer64)) >> 32))

#define ACPI_SET_BIT(target,bit)        ((target) |= (bit))
#define ACPI_CLEAR_BIT(target,bit)      ((target) &= ~(bit))
#define ACPI_MIN(a,b)                   (((a)<(b))?(a):(b))
#define ACPI_MAX(a,b)                   (((a)>(b))?(a):(b))

/* Size calculation */

#define ACPI_ARRAY_LENGTH(x)            (sizeof(x) / sizeof((x)[0]))

/* Pointer manipulation */

#define ACPI_CAST_PTR(t, p)             ((t *) (ACPI_UINTPTR_T) (p))
#define ACPI_CAST_INDIRECT_PTR(t, p)    ((t **) (ACPI_UINTPTR_T) (p))
#define ACPI_ADD_PTR(t, a, b)           ACPI_CAST_PTR (t, (ACPI_CAST_PTR (UINT8, (a)) + (ACPI_SIZE)(b)))
#define ACPI_PTR_DIFF(a, b)             (ACPI_SIZE) (ACPI_CAST_PTR (UINT8, (a)) - ACPI_CAST_PTR (UINT8, (b)))

/* Pointer/Integer type conversions */

#define ACPI_TO_POINTER(i)              ACPI_ADD_PTR (void, (void *) NULL,(ACPI_SIZE) i)
#define ACPI_TO_INTEGER(p)              ACPI_PTR_DIFF (p, (void *) NULL)
#define ACPI_OFFSET(d, f)               (ACPI_SIZE) ACPI_PTR_DIFF (&(((d *)0)->f), (void *) NULL)
#define ACPI_PHYSADDR_TO_PTR(i)         ACPI_TO_POINTER(i)
#define ACPI_PTR_TO_PHYSADDR(i)         ACPI_TO_INTEGER(i)

#ifndef ACPI_MISALIGNMENT_NOT_SUPPORTED
#define ACPI_COMPARE_NAME(a,b)          (*ACPI_CAST_PTR (UINT32, (a)) == *ACPI_CAST_PTR (UINT32, (b)))
#else
#define ACPI_COMPARE_NAME(a,b)          (!ACPI_STRNCMP (ACPI_CAST_PTR (char, (a)), ACPI_CAST_PTR (char, (b)), ACPI_NAME_SIZE))
#endif


/*******************************************************************************
 *
 * Miscellaneous constants
 *
 ******************************************************************************/

/*
 * Initialization sequence
 */
#define ACPI_FULL_INITIALIZATION        0x00
#define ACPI_NO_ADDRESS_SPACE_INIT      0x01
#define ACPI_NO_HARDWARE_INIT           0x02
#define ACPI_NO_EVENT_INIT              0x04
#define ACPI_NO_HANDLER_INIT            0x08
#define ACPI_NO_ACPI_ENABLE             0x10
#define ACPI_NO_DEVICE_INIT             0x20
#define ACPI_NO_OBJECT_INIT             0x40

/*
 * Initialization state
 */
#define ACPI_SUBSYSTEM_INITIALIZE       0x01
#define ACPI_INITIALIZED_OK             0x02

/*
 * Power state values
 */
#define ACPI_STATE_UNKNOWN              (UINT8) 0xFF

#define ACPI_STATE_S0                   (UINT8) 0
#define ACPI_STATE_S1                   (UINT8) 1
#define ACPI_STATE_S2                   (UINT8) 2
#define ACPI_STATE_S3                   (UINT8) 3
#define ACPI_STATE_S4                   (UINT8) 4
#define ACPI_STATE_S5                   (UINT8) 5
#define ACPI_S_STATES_MAX               ACPI_STATE_S5
#define ACPI_S_STATE_COUNT              6

#define ACPI_STATE_D0                   (UINT8) 0
#define ACPI_STATE_D1                   (UINT8) 1
#define ACPI_STATE_D2                   (UINT8) 2
#define ACPI_STATE_D3                   (UINT8) 3
#define ACPI_D_STATES_MAX               ACPI_STATE_D3
#define ACPI_D_STATE_COUNT              4

#define ACPI_STATE_C0                   (UINT8) 0
#define ACPI_STATE_C1                   (UINT8) 1
#define ACPI_STATE_C2                   (UINT8) 2
#define ACPI_STATE_C3                   (UINT8) 3
#define ACPI_C_STATES_MAX               ACPI_STATE_C3
#define ACPI_C_STATE_COUNT              4

/*
 * Sleep type invalid value
 */
#define ACPI_SLEEP_TYPE_MAX             0x7
#define ACPI_SLEEP_TYPE_INVALID         0xFF

/*
 * Standard notify values
 */
#define ACPI_NOTIFY_BUS_CHECK           (UINT8) 0x00
#define ACPI_NOTIFY_DEVICE_CHECK        (UINT8) 0x01
#define ACPI_NOTIFY_DEVICE_WAKE         (UINT8) 0x02
#define ACPI_NOTIFY_EJECT_REQUEST       (UINT8) 0x03
#define ACPI_NOTIFY_DEVICE_CHECK_LIGHT  (UINT8) 0x04
#define ACPI_NOTIFY_FREQUENCY_MISMATCH  (UINT8) 0x05
#define ACPI_NOTIFY_BUS_MODE_MISMATCH   (UINT8) 0x06
#define ACPI_NOTIFY_POWER_FAULT         (UINT8) 0x07
#define ACPI_NOTIFY_CAPABILITIES_CHECK  (UINT8) 0x08
#define ACPI_NOTIFY_DEVICE_PLD_CHECK    (UINT8) 0x09
#define ACPI_NOTIFY_RESERVED            (UINT8) 0x0A
#define ACPI_NOTIFY_LOCALITY_UPDATE     (UINT8) 0x0B

#define ACPI_NOTIFY_MAX                 0x0B

/*
 * Types associated with ACPI names and objects. The first group of
 * values (up to ACPI_TYPE_EXTERNAL_MAX) correspond to the definition
 * of the ACPI ObjectType() operator (See the ACPI Spec). Therefore,
 * only add to the first group if the spec changes.
 *
 * NOTE: Types must be kept in sync with the global AcpiNsProperties
 * and AcpiNsTypeNames arrays.
 */
typedef UINT32                          ACPI_OBJECT_TYPE;

#define ACPI_TYPE_ANY                   0x00
#define ACPI_TYPE_INTEGER               0x01  /* Byte/Word/Dword/Zero/One/Ones */
#define ACPI_TYPE_STRING                0x02
#define ACPI_TYPE_BUFFER                0x03
#define ACPI_TYPE_PACKAGE               0x04  /* ByteConst, multiple DataTerm/Constant/SuperName */
#define ACPI_TYPE_FIELD_UNIT            0x05
#define ACPI_TYPE_DEVICE                0x06  /* Name, multiple Node */
#define ACPI_TYPE_EVENT                 0x07
#define ACPI_TYPE_METHOD                0x08  /* Name, ByteConst, multiple Code */
#define ACPI_TYPE_MUTEX                 0x09
#define ACPI_TYPE_REGION                0x0A
#define ACPI_TYPE_POWER                 0x0B  /* Name,ByteConst,WordConst,multi Node */
#define ACPI_TYPE_PROCESSOR             0x0C  /* Name,ByteConst,DWordConst,ByteConst,multi NmO */
#define ACPI_TYPE_THERMAL               0x0D  /* Name, multiple Node */
#define ACPI_TYPE_BUFFER_FIELD          0x0E
#define ACPI_TYPE_DDB_HANDLE            0x0F
#define ACPI_TYPE_DEBUG_OBJECT          0x10

#define ACPI_TYPE_EXTERNAL_MAX          0x10

/*
 * These are object types that do not map directly to the ACPI
 * ObjectType() operator. They are used for various internal purposes only.
 * If new predefined ACPI_TYPEs are added (via the ACPI specification), these
 * internal types must move upwards. (There is code that depends on these
 * values being contiguous with the external types above.)
 */
#define ACPI_TYPE_LOCAL_REGION_FIELD    0x11
#define ACPI_TYPE_LOCAL_BANK_FIELD      0x12
#define ACPI_TYPE_LOCAL_INDEX_FIELD     0x13
#define ACPI_TYPE_LOCAL_REFERENCE       0x14  /* Arg#, Local#, Name, Debug, RefOf, Index */
#define ACPI_TYPE_LOCAL_ALIAS           0x15
#define ACPI_TYPE_LOCAL_METHOD_ALIAS    0x16
#define ACPI_TYPE_LOCAL_NOTIFY          0x17
#define ACPI_TYPE_LOCAL_ADDRESS_HANDLER 0x18
#define ACPI_TYPE_LOCAL_RESOURCE        0x19
#define ACPI_TYPE_LOCAL_RESOURCE_FIELD  0x1A
#define ACPI_TYPE_LOCAL_SCOPE           0x1B  /* 1 Name, multiple ObjectList Nodes */

#define ACPI_TYPE_NS_NODE_MAX           0x1B  /* Last typecode used within a NS Node */

/*
 * These are special object types that never appear in
 * a Namespace node, only in an ACPI_OPERAND_OBJECT
 */
#define ACPI_TYPE_LOCAL_EXTRA           0x1C
#define ACPI_TYPE_LOCAL_DATA            0x1D

#define ACPI_TYPE_LOCAL_MAX             0x1D

/* All types above here are invalid */

#define ACPI_TYPE_INVALID               0x1E
#define ACPI_TYPE_NOT_FOUND             0xFF

#define ACPI_NUM_NS_TYPES               (ACPI_TYPE_INVALID + 1)


/*
 * All I/O
 */
#define ACPI_READ                       0
#define ACPI_WRITE                      1
#define ACPI_IO_MASK                    1

/*
 * Event Types: Fixed & General Purpose
 */
typedef UINT32                          ACPI_EVENT_TYPE;

/*
 * Fixed events
 */
#define ACPI_EVENT_PMTIMER              0
#define ACPI_EVENT_GLOBAL               1
#define ACPI_EVENT_POWER_BUTTON         2
#define ACPI_EVENT_SLEEP_BUTTON         3
#define ACPI_EVENT_RTC                  4
#define ACPI_EVENT_MAX                  4
#define ACPI_NUM_FIXED_EVENTS           ACPI_EVENT_MAX + 1

/*
 * Event Status - Per event
 * -------------
 * The encoding of ACPI_EVENT_STATUS is illustrated below.
 * Note that a set bit (1) indicates the property is TRUE
 * (e.g. if bit 0 is set then the event is enabled).
 * +-------------+-+-+-+
 * |   Bits 31:3 |2|1|0|
 * +-------------+-+-+-+
 *          |     | | |
 *          |     | | +- Enabled?
 *          |     | +--- Enabled for wake?
 *          |     +----- Set?
 *          +----------- <Reserved>
 */
typedef UINT32                          ACPI_EVENT_STATUS;

#define ACPI_EVENT_FLAG_DISABLED        (ACPI_EVENT_STATUS) 0x00
#define ACPI_EVENT_FLAG_ENABLED         (ACPI_EVENT_STATUS) 0x01
#define ACPI_EVENT_FLAG_WAKE_ENABLED    (ACPI_EVENT_STATUS) 0x02
#define ACPI_EVENT_FLAG_SET             (ACPI_EVENT_STATUS) 0x04

/*
 * General Purpose Events (GPE)
 */
#define ACPI_GPE_INVALID                0xFF
#define ACPI_GPE_MAX                    0xFF
#define ACPI_NUM_GPE                    256

/* Actions for AcpiSetGpe, AcpiGpeWakeup, AcpiHwLowSetGpe */

#define ACPI_GPE_ENABLE                 0
#define ACPI_GPE_DISABLE                1
#define ACPI_GPE_CONDITIONAL_ENABLE     2

/*
 * GPE info flags - Per GPE
 * +-------+---+-+-+
 * |  7:4  |3:2|1|0|
 * +-------+---+-+-+
 *     |     |  | |
 *     |     |  | +--- Interrupt type: edge or level triggered
 *     |     |  +----- GPE can wake the system
 *     |     +-------- Type of dispatch:to method, handler, or none
 *     +-------------- <Reserved>
 */
#define ACPI_GPE_XRUPT_TYPE_MASK        (UINT8) 0x01
#define ACPI_GPE_LEVEL_TRIGGERED        (UINT8) 0x01
#define ACPI_GPE_EDGE_TRIGGERED         (UINT8) 0x00

#define ACPI_GPE_CAN_WAKE               (UINT8) 0x02

#define ACPI_GPE_DISPATCH_MASK          (UINT8) 0x0C
#define ACPI_GPE_DISPATCH_HANDLER       (UINT8) 0x04
#define ACPI_GPE_DISPATCH_METHOD        (UINT8) 0x08
#define ACPI_GPE_DISPATCH_NOT_USED      (UINT8) 0x00

/*
 * Flags for GPE and Lock interfaces
 */
#define ACPI_NOT_ISR                    0x1
#define ACPI_ISR                        0x0


/* Notify types */

#define ACPI_SYSTEM_NOTIFY              0x1
#define ACPI_DEVICE_NOTIFY              0x2
#define ACPI_ALL_NOTIFY                 (ACPI_SYSTEM_NOTIFY | ACPI_DEVICE_NOTIFY)
#define ACPI_MAX_NOTIFY_HANDLER_TYPE    0x3

#define ACPI_MAX_SYS_NOTIFY             0x7f


/* Address Space (Operation Region) Types */

typedef UINT8                           ACPI_ADR_SPACE_TYPE;

#define ACPI_ADR_SPACE_SYSTEM_MEMORY    (ACPI_ADR_SPACE_TYPE) 0
#define ACPI_ADR_SPACE_SYSTEM_IO        (ACPI_ADR_SPACE_TYPE) 1
#define ACPI_ADR_SPACE_PCI_CONFIG       (ACPI_ADR_SPACE_TYPE) 2
#define ACPI_ADR_SPACE_EC               (ACPI_ADR_SPACE_TYPE) 3
#define ACPI_ADR_SPACE_SMBUS            (ACPI_ADR_SPACE_TYPE) 4
#define ACPI_ADR_SPACE_CMOS             (ACPI_ADR_SPACE_TYPE) 5
#define ACPI_ADR_SPACE_PCI_BAR_TARGET   (ACPI_ADR_SPACE_TYPE) 6
#define ACPI_ADR_SPACE_IPMI             (ACPI_ADR_SPACE_TYPE) 7
#define ACPI_ADR_SPACE_DATA_TABLE       (ACPI_ADR_SPACE_TYPE) 8
#define ACPI_ADR_SPACE_FIXED_HARDWARE   (ACPI_ADR_SPACE_TYPE) 127


/*
 * BitRegister IDs
 *
 * These values are intended to be used by the hardware interfaces
 * and are mapped to individual bitfields defined within the ACPI
 * registers. See the AcpiGbl_BitRegisterInfo global table in utglobal.c
 * for this mapping.
 */

/* PM1 Status register */

#define ACPI_BITREG_TIMER_STATUS                0x00
#define ACPI_BITREG_BUS_MASTER_STATUS           0x01
#define ACPI_BITREG_GLOBAL_LOCK_STATUS          0x02
#define ACPI_BITREG_POWER_BUTTON_STATUS         0x03
#define ACPI_BITREG_SLEEP_BUTTON_STATUS         0x04
#define ACPI_BITREG_RT_CLOCK_STATUS             0x05
#define ACPI_BITREG_WAKE_STATUS                 0x06
#define ACPI_BITREG_PCIEXP_WAKE_STATUS          0x07

/* PM1 Enable register */

#define ACPI_BITREG_TIMER_ENABLE                0x08
#define ACPI_BITREG_GLOBAL_LOCK_ENABLE          0x09
#define ACPI_BITREG_POWER_BUTTON_ENABLE         0x0A
#define ACPI_BITREG_SLEEP_BUTTON_ENABLE         0x0B
#define ACPI_BITREG_RT_CLOCK_ENABLE             0x0C
#define ACPI_BITREG_PCIEXP_WAKE_DISABLE         0x0D

/* PM1 Control register */

#define ACPI_BITREG_SCI_ENABLE                  0x0E
#define ACPI_BITREG_BUS_MASTER_RLD              0x0F
#define ACPI_BITREG_GLOBAL_LOCK_RELEASE         0x10
#define ACPI_BITREG_SLEEP_TYPE                  0x11
#define ACPI_BITREG_SLEEP_ENABLE                0x12

/* PM2 Control register */

#define ACPI_BITREG_ARB_DISABLE                 0x13

#define ACPI_BITREG_MAX                         0x13
#define ACPI_NUM_BITREG                         ACPI_BITREG_MAX + 1


/* Status register values. A 1 clears a status bit. 0 = no effect */

#define ACPI_CLEAR_STATUS                       1

/* Enable and Control register values */

#define ACPI_ENABLE_EVENT                       1
#define ACPI_DISABLE_EVENT                      0


/*
 * External ACPI object definition
 */

/*
 * Note: Type == ACPI_TYPE_ANY (0) is used to indicate a NULL package element
 * or an unresolved named reference.
 */
typedef union acpi_object
{
    ACPI_OBJECT_TYPE                Type;   /* See definition of AcpiNsType for values */
    struct
    {
        ACPI_OBJECT_TYPE                Type;       /* ACPI_TYPE_INTEGER */
        UINT64                          Value;      /* The actual number */
    } Integer;

    struct
    {
        ACPI_OBJECT_TYPE                Type;       /* ACPI_TYPE_STRING */
        UINT32                          Length;     /* # of bytes in string, excluding trailing null */
        char                            *Pointer;   /* points to the string value */
    } String;

    struct
    {
        ACPI_OBJECT_TYPE                Type;       /* ACPI_TYPE_BUFFER */
        UINT32                          Length;     /* # of bytes in buffer */
        UINT8                           *Pointer;   /* points to the buffer */
    } Buffer;

    struct
    {
        ACPI_OBJECT_TYPE                Type;       /* ACPI_TYPE_PACKAGE */
        UINT32                          Count;      /* # of elements in package */
        union acpi_object               *Elements;  /* Pointer to an array of ACPI_OBJECTs */
    } Package;

    struct
    {
        ACPI_OBJECT_TYPE                Type;       /* ACPI_TYPE_LOCAL_REFERENCE */
        ACPI_OBJECT_TYPE                ActualType; /* Type associated with the Handle */
        ACPI_HANDLE                     Handle;     /* object reference */
    } Reference;

    struct
    {
        ACPI_OBJECT_TYPE                Type;       /* ACPI_TYPE_PROCESSOR */
        UINT32                          ProcId;
        ACPI_IO_ADDRESS                 PblkAddress;
        UINT32                          PblkLength;
    } Processor;

    struct
    {
        ACPI_OBJECT_TYPE                Type;       /* ACPI_TYPE_POWER */
        UINT32                          SystemLevel;
        UINT32                          ResourceOrder;
    } PowerResource;

} ACPI_OBJECT;


/*
 * List of objects, used as a parameter list for control method evaluation
 */
typedef struct acpi_object_list
{
    UINT32                          Count;
    ACPI_OBJECT                     *Pointer;

} ACPI_OBJECT_LIST;


/*
 * Miscellaneous common Data Structures used by the interfaces
 */
#define ACPI_NO_BUFFER              0
#define ACPI_ALLOCATE_BUFFER        (ACPI_SIZE) (-1)
#define ACPI_ALLOCATE_LOCAL_BUFFER  (ACPI_SIZE) (-2)

typedef struct acpi_buffer
{
    ACPI_SIZE                       Length;         /* Length in bytes of the buffer */
    void                            *Pointer;       /* pointer to buffer */

} ACPI_BUFFER;


/*
 * NameType for AcpiGetName
 */
#define ACPI_FULL_PATHNAME              0
#define ACPI_SINGLE_NAME                1
#define ACPI_NAME_TYPE_MAX              1


/*
 * Predefined Namespace items
 */
typedef struct acpi_predefined_names
{
    char                            *Name;
    UINT8                           Type;
    char                            *Val;

} ACPI_PREDEFINED_NAMES;


/*
 * Structure and flags for AcpiGetSystemInfo
 */
#define ACPI_SYS_MODE_UNKNOWN           0x0000
#define ACPI_SYS_MODE_ACPI              0x0001
#define ACPI_SYS_MODE_LEGACY            0x0002
#define ACPI_SYS_MODES_MASK             0x0003


/*
 * System info returned by AcpiGetSystemInfo()
 */
typedef struct acpi_system_info
{
    UINT32                          AcpiCaVersion;
    UINT32                          Flags;
    UINT32                          TimerResolution;
    UINT32                          Reserved1;
    UINT32                          Reserved2;
    UINT32                          DebugLevel;
    UINT32                          DebugLayer;

} ACPI_SYSTEM_INFO;


/*
 * System statistics returned by AcpiGetStatistics()
 */
typedef struct acpi_statistics
{
    UINT32                          SciCount;
    UINT32                          GpeCount;
    UINT32                          FixedEventCount[ACPI_NUM_FIXED_EVENTS];
    UINT32                          MethodCount;

} ACPI_STATISTICS;


/* Table Event Types */

#define ACPI_TABLE_EVENT_LOAD           0x0
#define ACPI_TABLE_EVENT_UNLOAD         0x1
#define ACPI_NUM_TABLE_EVENTS           2


/*
 * Types specific to the OS service interfaces
 */
typedef UINT32
(ACPI_SYSTEM_XFACE *ACPI_OSD_HANDLER) (
    void                            *Context);

typedef void
(ACPI_SYSTEM_XFACE *ACPI_OSD_EXEC_CALLBACK) (
    void                            *Context);

/*
 * Various handlers and callback procedures
 */
typedef
UINT32 (*ACPI_EVENT_HANDLER) (
    void                            *Context);

typedef
void (*ACPI_NOTIFY_HANDLER) (
    ACPI_HANDLE                     Device,
    UINT32                          Value,
    void                            *Context);

typedef
void (*ACPI_OBJECT_HANDLER) (
    ACPI_HANDLE                     Object,
    void                            *Data);

typedef
ACPI_STATUS (*ACPI_INIT_HANDLER) (
    ACPI_HANDLE                     Object,
    UINT32                          Function);

#define ACPI_INIT_DEVICE_INI        1

typedef
ACPI_STATUS (*ACPI_EXCEPTION_HANDLER) (
    ACPI_STATUS                     AmlStatus,
    ACPI_NAME                       Name,
    UINT16                          Opcode,
    UINT32                          AmlOffset,
    void                            *Context);

/* Table Event handler (Load, LoadTable, etc.) and types */

typedef
ACPI_STATUS (*ACPI_TABLE_HANDLER) (
    UINT32                          Event,
    void                            *Table,
    void                            *Context);

#define ACPI_TABLE_LOAD             0x0
#define ACPI_TABLE_UNLOAD           0x1
#define ACPI_NUM_TABLE_EVENTS       2


/* Address Spaces (For Operation Regions) */

typedef
ACPI_STATUS (*ACPI_ADR_SPACE_HANDLER) (
    UINT32                          Function,
    ACPI_PHYSICAL_ADDRESS           Address,
    UINT32                          BitWidth,
    UINT64                          *Value,
    void                            *HandlerContext,
    void                            *RegionContext);

#define ACPI_DEFAULT_HANDLER            NULL

typedef
ACPI_STATUS (*ACPI_ADR_SPACE_SETUP) (
    ACPI_HANDLE                     RegionHandle,
    UINT32                          Function,
    void                            *HandlerContext,
    void                            **RegionContext);

#define ACPI_REGION_ACTIVATE    0
#define ACPI_REGION_DEACTIVATE  1

typedef
ACPI_STATUS (*ACPI_WALK_CALLBACK) (
    ACPI_HANDLE                     Object,
    UINT32                          NestingLevel,
    void                            *Context,
    void                            **ReturnValue);


/* Interrupt handler return values */

#define ACPI_INTERRUPT_NOT_HANDLED      0x00
#define ACPI_INTERRUPT_HANDLED          0x01

/* Length of 32-bit EISAID values when converted back to a string */

#define ACPI_EISAID_STRING_SIZE         8   /* Includes null terminator */

/* Length of UUID (string) values */

#define ACPI_UUID_LENGTH                16


/* Structures used for device/processor HID, UID, CID */

typedef struct acpi_device_id
{
    UINT32                          Length;             /* Length of string + null */
    char                            *String;

} ACPI_DEVICE_ID;

typedef struct acpi_device_id_list
{
    UINT32                          Count;              /* Number of IDs in Ids array */
    UINT32                          ListSize;           /* Size of list, including ID strings */
    ACPI_DEVICE_ID                  Ids[1];             /* ID array */

} ACPI_DEVICE_ID_LIST;

/*
 * Structure returned from AcpiGetObjectInfo.
 * Optimized for both 32- and 64-bit builds
 */
typedef struct acpi_device_info
{
    UINT32                          InfoSize;           /* Size of info, including ID strings */
    UINT32                          Name;               /* ACPI object Name */
    ACPI_OBJECT_TYPE                Type;               /* ACPI object Type */
    UINT8                           ParamCount;         /* If a method, required parameter count */
    UINT8                           Valid;              /* Indicates which optional fields are valid */
    UINT8                           Flags;              /* Miscellaneous info */
    UINT8                           HighestDstates[4];  /* _SxD values: 0xFF indicates not valid */
    UINT8                           LowestDstates[5];   /* _SxW values: 0xFF indicates not valid */
    UINT32                          CurrentStatus;      /* _STA value */
    UINT64                          Address;            /* _ADR value */
    ACPI_DEVICE_ID                  HardwareId;         /* _HID value */
    ACPI_DEVICE_ID                  UniqueId;           /* _UID value */
    ACPI_DEVICE_ID_LIST             CompatibleIdList;   /* _CID list <must be last> */

} ACPI_DEVICE_INFO;

/* Values for Flags field above (AcpiGetObjectInfo) */

#define ACPI_PCI_ROOT_BRIDGE            0x01

/* Flags for Valid field above (AcpiGetObjectInfo) */

#define ACPI_VALID_STA                  0x01
#define ACPI_VALID_ADR                  0x02
#define ACPI_VALID_HID                  0x04
#define ACPI_VALID_UID                  0x08
#define ACPI_VALID_CID                  0x10
#define ACPI_VALID_SXDS                 0x20
#define ACPI_VALID_SXWS                 0x40

/* Flags for _STA method */

#define ACPI_STA_DEVICE_PRESENT         0x01
#define ACPI_STA_DEVICE_ENABLED         0x02
#define ACPI_STA_DEVICE_UI              0x04
#define ACPI_STA_DEVICE_FUNCTIONING     0x08
#define ACPI_STA_DEVICE_OK              0x08 /* Synonym */
#define ACPI_STA_BATTERY_PRESENT        0x10


/* Context structs for address space handlers */

typedef struct acpi_pci_id
{
    UINT16                          Segment;
    UINT16                          Bus;
    UINT16                          Device;
    UINT16                          Function;

} ACPI_PCI_ID;

typedef struct acpi_mem_space_context
{
    UINT32                          Length;
    ACPI_PHYSICAL_ADDRESS           Address;
    ACPI_PHYSICAL_ADDRESS           MappedPhysicalAddress;
    UINT8                           *MappedLogicalAddress;
    ACPI_SIZE                       MappedLength;

} ACPI_MEM_SPACE_CONTEXT;


/*
 * ACPI_MEMORY_LIST is used only if the ACPICA local cache is enabled
 */
typedef struct acpi_memory_list
{
    char                            *ListName;
    void                            *ListHead;
    UINT16                          ObjectSize;
    UINT16                          MaxDepth;
    UINT16                          CurrentDepth;
    UINT16                          LinkOffset;

#ifdef ACPI_DBG_TRACK_ALLOCATIONS

    /* Statistics for debug memory tracking only */

    UINT32                          TotalAllocated;
    UINT32                          TotalFreed;
    UINT32                          MaxOccupied;
    UINT32                          TotalSize;
    UINT32                          CurrentTotalSize;
    UINT32                          Requests;
    UINT32                          Hits;
#endif

} ACPI_MEMORY_LIST;


#endif /* __ACTYPES_H__ */
