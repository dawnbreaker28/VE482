/******************************************************************************
 *
 * Name: acrestyp.h - Defines, types, and structures for resource descriptors
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

#ifndef __ACRESTYP_H__
#define __ACRESTYP_H__


/*
 * Definitions for Resource Attributes
 */
typedef UINT16                          ACPI_RS_LENGTH;    /* Resource Length field is fixed at 16 bits */
typedef UINT32                          ACPI_RSDESC_SIZE;  /* Max Resource Descriptor size is (Length+3) = (64K-1)+3 */

/*
 * Memory Attributes
 */
#define ACPI_READ_ONLY_MEMORY           (UINT8) 0x00
#define ACPI_READ_WRITE_MEMORY          (UINT8) 0x01

#define ACPI_NON_CACHEABLE_MEMORY       (UINT8) 0x00
#define ACPI_CACHABLE_MEMORY            (UINT8) 0x01
#define ACPI_WRITE_COMBINING_MEMORY     (UINT8) 0x02
#define ACPI_PREFETCHABLE_MEMORY        (UINT8) 0x03

/*
 * IO Attributes
 * The ISA IO ranges are:     n000-n0FFh,  n400-n4FFh, n800-n8FFh, nC00-nCFFh.
 * The non-ISA IO ranges are: n100-n3FFh,  n500-n7FFh, n900-nBFFh, nCD0-nFFFh.
 */
#define ACPI_NON_ISA_ONLY_RANGES        (UINT8) 0x01
#define ACPI_ISA_ONLY_RANGES            (UINT8) 0x02
#define ACPI_ENTIRE_RANGE               (ACPI_NON_ISA_ONLY_RANGES | ACPI_ISA_ONLY_RANGES)

/* Type of translation - 1=Sparse, 0=Dense */

#define ACPI_SPARSE_TRANSLATION         (UINT8) 0x01

/*
 * IO Port Descriptor Decode
 */
#define ACPI_DECODE_10                  (UINT8) 0x00    /* 10-bit IO address decode */
#define ACPI_DECODE_16                  (UINT8) 0x01    /* 16-bit IO address decode */

/*
 * IRQ Attributes
 */
#define ACPI_LEVEL_SENSITIVE            (UINT8) 0x00
#define ACPI_EDGE_SENSITIVE             (UINT8) 0x01

#define ACPI_ACTIVE_HIGH                (UINT8) 0x00
#define ACPI_ACTIVE_LOW                 (UINT8) 0x01

#define ACPI_EXCLUSIVE                  (UINT8) 0x00
#define ACPI_SHARED                     (UINT8) 0x01

/*
 * DMA Attributes
 */
#define ACPI_COMPATIBILITY              (UINT8) 0x00
#define ACPI_TYPE_A                     (UINT8) 0x01
#define ACPI_TYPE_B                     (UINT8) 0x02
#define ACPI_TYPE_F                     (UINT8) 0x03

#define ACPI_NOT_BUS_MASTER             (UINT8) 0x00
#define ACPI_BUS_MASTER                 (UINT8) 0x01

#define ACPI_TRANSFER_8                 (UINT8) 0x00
#define ACPI_TRANSFER_8_16              (UINT8) 0x01
#define ACPI_TRANSFER_16                (UINT8) 0x02

/*
 * Start Dependent Functions Priority definitions
 */
#define ACPI_GOOD_CONFIGURATION         (UINT8) 0x00
#define ACPI_ACCEPTABLE_CONFIGURATION   (UINT8) 0x01
#define ACPI_SUB_OPTIMAL_CONFIGURATION  (UINT8) 0x02

/*
 * 16, 32 and 64-bit Address Descriptor resource types
 */
#define ACPI_MEMORY_RANGE               (UINT8) 0x00
#define ACPI_IO_RANGE                   (UINT8) 0x01
#define ACPI_BUS_NUMBER_RANGE           (UINT8) 0x02

#define ACPI_ADDRESS_NOT_FIXED          (UINT8) 0x00
#define ACPI_ADDRESS_FIXED              (UINT8) 0x01

#define ACPI_POS_DECODE                 (UINT8) 0x00
#define ACPI_SUB_DECODE                 (UINT8) 0x01

#define ACPI_PRODUCER                   (UINT8) 0x00
#define ACPI_CONSUMER                   (UINT8) 0x01


/*
 * If possible, pack the following structures to byte alignment
 */
#ifndef ACPI_MISALIGNMENT_NOT_SUPPORTED
#pragma pack(1)
#endif

/* UUID data structures for use in vendor-defined resource descriptors */

typedef struct acpi_uuid
{
    UINT8                           Data[ACPI_UUID_LENGTH];
} ACPI_UUID;

typedef struct acpi_vendor_uuid
{
    UINT8                           Subtype;
    UINT8                           Data[ACPI_UUID_LENGTH];

} ACPI_VENDOR_UUID;

/*
 * Structures used to describe device resources
 */
typedef struct acpi_resource_irq
{
    UINT8                           DescriptorLength;
    UINT8                           Triggering;
    UINT8                           Polarity;
    UINT8                           Sharable;
    UINT8                           InterruptCount;
    UINT8                           Interrupts[1];

} ACPI_RESOURCE_IRQ;

typedef struct ACPI_RESOURCE_DMA
{
    UINT8                           Type;
    UINT8                           BusMaster;
    UINT8                           Transfer;
    UINT8                           ChannelCount;
    UINT8                           Channels[1];

} ACPI_RESOURCE_DMA;

typedef struct acpi_resource_start_dependent
{
    UINT8                           DescriptorLength;
    UINT8                           CompatibilityPriority;
    UINT8                           PerformanceRobustness;

} ACPI_RESOURCE_START_DEPENDENT;


/*
 * The END_DEPENDENT_FUNCTIONS_RESOURCE struct is not
 * needed because it has no fields
 */


typedef struct acpi_resource_io
{
    UINT8                           IoDecode;
    UINT8                           Alignment;
    UINT8                           AddressLength;
    UINT16                          Minimum;
    UINT16                          Maximum;

} ACPI_RESOURCE_IO;

typedef struct acpi_resource_fixed_io
{
    UINT16                          Address;
    UINT8                           AddressLength;

} ACPI_RESOURCE_FIXED_IO;

typedef struct acpi_resource_vendor
{
    UINT16                          ByteLength;
    UINT8                           ByteData[1];

} ACPI_RESOURCE_VENDOR;

/* Vendor resource with UUID info (introduced in ACPI 3.0) */

typedef struct acpi_resource_vendor_typed
{
    UINT16                          ByteLength;
    UINT8                           UuidSubtype;
    UINT8                           Uuid[ACPI_UUID_LENGTH];
    UINT8                           ByteData[1];

} ACPI_RESOURCE_VENDOR_TYPED;

typedef struct acpi_resource_end_tag
{
    UINT8                           Checksum;

} ACPI_RESOURCE_END_TAG;

typedef struct acpi_resource_memory24
{
    UINT8                           WriteProtect;
    UINT16                          Minimum;
    UINT16                          Maximum;
    UINT16                          Alignment;
    UINT16                          AddressLength;

} ACPI_RESOURCE_MEMORY24;

typedef struct acpi_resource_memory32
{
    UINT8                           WriteProtect;
    UINT32                          Minimum;
    UINT32                          Maximum;
    UINT32                          Alignment;
    UINT32                          AddressLength;

} ACPI_RESOURCE_MEMORY32;

typedef struct acpi_resource_fixed_memory32
{
    UINT8                           WriteProtect;
    UINT32                          Address;
    UINT32                          AddressLength;

} ACPI_RESOURCE_FIXED_MEMORY32;

typedef struct acpi_memory_attribute
{
    UINT8                           WriteProtect;
    UINT8                           Caching;
    UINT8                           RangeType;
    UINT8                           Translation;

} ACPI_MEMORY_ATTRIBUTE;

typedef struct acpi_io_attribute
{
    UINT8                           RangeType;
    UINT8                           Translation;
    UINT8                           TranslationType;
    UINT8                           Reserved1;

} ACPI_IO_ATTRIBUTE;

typedef union acpi_resource_attribute
{
    ACPI_MEMORY_ATTRIBUTE           Mem;
    ACPI_IO_ATTRIBUTE               Io;

    /* Used for the *WordSpace macros */

    UINT8                           TypeSpecific;

} ACPI_RESOURCE_ATTRIBUTE;

typedef struct acpi_resource_source
{
    UINT8                           Index;
    UINT16                          StringLength;
    char                            *StringPtr;

} ACPI_RESOURCE_SOURCE;

/* Fields common to all address descriptors, 16/32/64 bit */

#define ACPI_RESOURCE_ADDRESS_COMMON \
    UINT8                           ResourceType; \
    UINT8                           ProducerConsumer; \
    UINT8                           Decode; \
    UINT8                           MinAddressFixed; \
    UINT8                           MaxAddressFixed; \
    ACPI_RESOURCE_ATTRIBUTE         Info;

typedef struct acpi_resource_address
{
    ACPI_RESOURCE_ADDRESS_COMMON

} ACPI_RESOURCE_ADDRESS;

typedef struct acpi_resource_address16
{
    ACPI_RESOURCE_ADDRESS_COMMON
    UINT16                          Granularity;
    UINT16                          Minimum;
    UINT16                          Maximum;
    UINT16                          TranslationOffset;
    UINT16                          AddressLength;
    ACPI_RESOURCE_SOURCE            ResourceSource;

} ACPI_RESOURCE_ADDRESS16;

typedef struct acpi_resource_address32
{
    ACPI_RESOURCE_ADDRESS_COMMON
    UINT32                          Granularity;
    UINT32                          Minimum;
    UINT32                          Maximum;
    UINT32                          TranslationOffset;
    UINT32                          AddressLength;
    ACPI_RESOURCE_SOURCE            ResourceSource;

} ACPI_RESOURCE_ADDRESS32;

typedef struct acpi_resource_address64
{
    ACPI_RESOURCE_ADDRESS_COMMON
    UINT64                          Granularity;
    UINT64                          Minimum;
    UINT64                          Maximum;
    UINT64                          TranslationOffset;
    UINT64                          AddressLength;
    ACPI_RESOURCE_SOURCE            ResourceSource;

} ACPI_RESOURCE_ADDRESS64;

typedef struct acpi_resource_extended_address64
{
    ACPI_RESOURCE_ADDRESS_COMMON
    UINT8                           RevisionID;
    UINT64                          Granularity;
    UINT64                          Minimum;
    UINT64                          Maximum;
    UINT64                          TranslationOffset;
    UINT64                          AddressLength;
    UINT64                          TypeSpecific;

} ACPI_RESOURCE_EXTENDED_ADDRESS64;

typedef struct acpi_resource_extended_irq
{
    UINT8                           ProducerConsumer;
    UINT8                           Triggering;
    UINT8                           Polarity;
    UINT8                           Sharable;
    UINT8                           InterruptCount;
    ACPI_RESOURCE_SOURCE            ResourceSource;
    UINT32                          Interrupts[1];

} ACPI_RESOURCE_EXTENDED_IRQ;

typedef struct acpi_resource_generic_register
{
    UINT8                           SpaceId;
    UINT8                           BitWidth;
    UINT8                           BitOffset;
    UINT8                           AccessSize;
    UINT64                          Address;

} ACPI_RESOURCE_GENERIC_REGISTER;


/* ACPI_RESOURCE_TYPEs */

#define ACPI_RESOURCE_TYPE_IRQ                  0
#define ACPI_RESOURCE_TYPE_DMA                  1
#define ACPI_RESOURCE_TYPE_START_DEPENDENT      2
#define ACPI_RESOURCE_TYPE_END_DEPENDENT        3
#define ACPI_RESOURCE_TYPE_IO                   4
#define ACPI_RESOURCE_TYPE_FIXED_IO             5
#define ACPI_RESOURCE_TYPE_VENDOR               6
#define ACPI_RESOURCE_TYPE_END_TAG              7
#define ACPI_RESOURCE_TYPE_MEMORY24             8
#define ACPI_RESOURCE_TYPE_MEMORY32             9
#define ACPI_RESOURCE_TYPE_FIXED_MEMORY32       10
#define ACPI_RESOURCE_TYPE_ADDRESS16            11
#define ACPI_RESOURCE_TYPE_ADDRESS32            12
#define ACPI_RESOURCE_TYPE_ADDRESS64            13
#define ACPI_RESOURCE_TYPE_EXTENDED_ADDRESS64   14  /* ACPI 3.0 */
#define ACPI_RESOURCE_TYPE_EXTENDED_IRQ         15
#define ACPI_RESOURCE_TYPE_GENERIC_REGISTER     16
#define ACPI_RESOURCE_TYPE_MAX                  16

/* Master union for resource descriptors */

typedef union acpi_resource_data
{
    ACPI_RESOURCE_IRQ                       Irq;
    ACPI_RESOURCE_DMA                       Dma;
    ACPI_RESOURCE_START_DEPENDENT           StartDpf;
    ACPI_RESOURCE_IO                        Io;
    ACPI_RESOURCE_FIXED_IO                  FixedIo;
    ACPI_RESOURCE_VENDOR                    Vendor;
    ACPI_RESOURCE_VENDOR_TYPED              VendorTyped;
    ACPI_RESOURCE_END_TAG                   EndTag;
    ACPI_RESOURCE_MEMORY24                  Memory24;
    ACPI_RESOURCE_MEMORY32                  Memory32;
    ACPI_RESOURCE_FIXED_MEMORY32            FixedMemory32;
    ACPI_RESOURCE_ADDRESS16                 Address16;
    ACPI_RESOURCE_ADDRESS32                 Address32;
    ACPI_RESOURCE_ADDRESS64                 Address64;
    ACPI_RESOURCE_EXTENDED_ADDRESS64        ExtAddress64;
    ACPI_RESOURCE_EXTENDED_IRQ              ExtendedIrq;
    ACPI_RESOURCE_GENERIC_REGISTER          GenericReg;

    /* Common fields */

    ACPI_RESOURCE_ADDRESS                   Address;        /* Common 16/32/64 address fields */

} ACPI_RESOURCE_DATA;


/* Common resource header */

typedef struct acpi_resource
{
    UINT32                          Type;
    UINT32                          Length;
    ACPI_RESOURCE_DATA              Data;

} ACPI_RESOURCE;

/* restore default alignment */

#pragma pack()


#define ACPI_RS_SIZE_NO_DATA                8       /* Id + Length fields */
#define ACPI_RS_SIZE_MIN                    (UINT32) ACPI_ROUND_UP_TO_NATIVE_WORD (12)
#define ACPI_RS_SIZE(Type)                  (UINT32) (ACPI_RS_SIZE_NO_DATA + sizeof (Type))

#define ACPI_NEXT_RESOURCE(Res)             (ACPI_RESOURCE *)((UINT8 *) Res + Res->Length)


typedef struct acpi_pci_routing_table
{
    UINT32                          Length;
    UINT32                          Pin;
    UINT64                          Address;        /* here for 64-bit alignment */
    UINT32                          SourceIndex;
    char                            Source[4];      /* pad to 64 bits so sizeof() works in all cases */

} ACPI_PCI_ROUTING_TABLE;

#endif /* __ACRESTYP_H__ */

