/******************************************************************************
 *
 * Name: acpredef - Information table for ACPI predefined methods and objects
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
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT, ASSISTANCE,
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

#ifndef __ACPREDEF_H__
#define __ACPREDEF_H__


/******************************************************************************
 *
 * Return Package types
 *
 * 1) PTYPE1 packages do not contain sub-packages.
 *
 * ACPI_PTYPE1_FIXED: Fixed-length length, 1 or 2 object types:
 *      object type
 *      count
 *      object type
 *      count
 *
 * ACPI_PTYPE1_VAR: Variable-length length:
 *      object type (Int/Buf/Ref)
 *
 * ACPI_PTYPE1_OPTION: Package has some required and some optional elements
 *      (Used for _PRW)
 *
 *
 * 2) PTYPE2 packages contain a Variable-length number of sub-packages. Each
 *    of the different types describe the contents of each of the sub-packages.
 *
 * ACPI_PTYPE2: Each subpackage contains 1 or 2 object types:
 *      object type
 *      count
 *      object type
 *      count
 *      (Used for _ALR,_MLS,_PSS,_TRT,_TSS)
 *
 * ACPI_PTYPE2_COUNT: Each subpackage has a count as first element:
 *      object type
 *      (Used for _CSD,_PSD,_TSD)
 *
 * ACPI_PTYPE2_PKG_COUNT: Count of subpackages at start, 1 or 2 object types:
 *      object type
 *      count
 *      object type
 *      count
 *      (Used for _CST)
 *
 * ACPI_PTYPE2_FIXED: Each subpackage is of Fixed-length
 *      (Used for _PRT)
 *
 * ACPI_PTYPE2_MIN: Each subpackage has a Variable-length but minimum length
 *      (Used for _HPX)
 *
 * ACPI_PTYPE2_REV_FIXED: Revision at start, each subpackage is Fixed-length
 *      (Used for _ART, _FPS)
 *
 *****************************************************************************/

enum AcpiReturnPackageTypes
{
    ACPI_PTYPE1_FIXED       = 1,
    ACPI_PTYPE1_VAR         = 2,
    ACPI_PTYPE1_OPTION      = 3,
    ACPI_PTYPE2             = 4,
    ACPI_PTYPE2_COUNT       = 5,
    ACPI_PTYPE2_PKG_COUNT   = 6,
    ACPI_PTYPE2_FIXED       = 7,
    ACPI_PTYPE2_MIN         = 8,
    ACPI_PTYPE2_REV_FIXED   = 9
};


#ifdef ACPI_CREATE_PREDEFINED_TABLE
/*
 * Predefined method/object information table.
 *
 * These are the names that can actually be evaluated via AcpiEvaluateObject.
 * Not present in this table are the following:
 *
 *      1) Predefined/Reserved names that are never evaluated via
 *         AcpiEvaluateObject:
 *              _Lxx and _Exx GPE methods
 *              _Qxx EC methods
 *              _T_x compiler temporary variables
 *
 *      2) Predefined names that never actually exist within the AML code:
 *              Predefined resource descriptor field names
 *
 *      3) Predefined names that are implemented within ACPICA:
 *              _OSI
 *
 *      4) Some predefined names that are not documented within the ACPI spec.
 *              _WDG, _WED
 *
 * The main entries in the table each contain the following items:
 *
 * Name                 - The ACPI reserved name
 * ParamCount           - Number of arguments to the method
 * ExpectedBtypes       - Allowed type(s) for the return value.
 *                        0 means that no return value is expected.
 *
 * For methods that return packages, the next entry in the table contains
 * information about the expected structure of the package. This information
 * is saved here (rather than in a separate table) in order to minimize the
 * overall size of the stored data.
 *
 * Note: The additional braces are intended to promote portability.
 */
static const ACPI_PREDEFINED_INFO     PredefinedNames[] =
{
    {{"_AC0", 0, ACPI_RTYPE_INTEGER}},
    {{"_AC1", 0, ACPI_RTYPE_INTEGER}},
    {{"_AC2", 0, ACPI_RTYPE_INTEGER}},
    {{"_AC3", 0, ACPI_RTYPE_INTEGER}},
    {{"_AC4", 0, ACPI_RTYPE_INTEGER}},
    {{"_AC5", 0, ACPI_RTYPE_INTEGER}},
    {{"_AC6", 0, ACPI_RTYPE_INTEGER}},
    {{"_AC7", 0, ACPI_RTYPE_INTEGER}},
    {{"_AC8", 0, ACPI_RTYPE_INTEGER}},
    {{"_AC9", 0, ACPI_RTYPE_INTEGER}},
    {{"_ADR", 0, ACPI_RTYPE_INTEGER}},
    {{"_AL0", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_AL1", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_AL2", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_AL3", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_AL4", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_AL5", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_AL6", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_AL7", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_AL8", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_AL9", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_ALC", 0, ACPI_RTYPE_INTEGER}},
    {{"_ALI", 0, ACPI_RTYPE_INTEGER}},
    {{"_ALP", 0, ACPI_RTYPE_INTEGER}},
    {{"_ALR", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Pkgs) each 2 (Ints) */
                    {{{ACPI_PTYPE2, ACPI_RTYPE_INTEGER, 2,0}, 0,0}},

    {{"_ALT", 0, ACPI_RTYPE_INTEGER}},
    {{"_ART", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (1 Int(rev), n Pkg (2 Ref/11 Int) */
                    {{{ACPI_PTYPE2_REV_FIXED,ACPI_RTYPE_REFERENCE, 2, ACPI_RTYPE_INTEGER}, 11,0}},

    {{"_BBN", 0, ACPI_RTYPE_INTEGER}},
    {{"_BCL", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Ints) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER, 0,0}, 0,0}},

    {{"_BCM", 1, 0}},
    {{"_BCT", 1, ACPI_RTYPE_INTEGER}},
    {{"_BDN", 0, ACPI_RTYPE_INTEGER}},
    {{"_BFS", 1, 0}},
    {{"_BIF", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (9 Int),(4 Str) */
                    {{{ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 9, ACPI_RTYPE_STRING}, 4,0}},

    {{"_BIX", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (16 Int),(4 Str) */
                    {{{ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 16, ACPI_RTYPE_STRING}, 4,0}},

    {{"_BLT", 3, 0}},
    {{"_BMA", 1, ACPI_RTYPE_INTEGER}},
    {{"_BMC", 1, 0}},
    {{"_BMD", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (5 Int) */
                    {{{ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 5,0}, 0,0}},

    {{"_BMS", 1, ACPI_RTYPE_INTEGER}},
    {{"_BQC", 0, ACPI_RTYPE_INTEGER}},
    {{"_BST", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (4 Int) */
                    {{{ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 4,0}, 0,0}},

    {{"_BTM", 1, ACPI_RTYPE_INTEGER}},
    {{"_BTP", 1, 0}},
    {{"_CBA", 0, ACPI_RTYPE_INTEGER}}, /* See PCI firmware spec 3.0 */
    {{"_CDM", 0, ACPI_RTYPE_INTEGER}},
    {{"_CID", 0, ACPI_RTYPE_INTEGER | ACPI_RTYPE_STRING | ACPI_RTYPE_PACKAGE}}, /* Variable-length (Ints/Strs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER | ACPI_RTYPE_STRING, 0,0}, 0,0}},

    {{"_CRS", 0, ACPI_RTYPE_BUFFER}},
    {{"_CRT", 0, ACPI_RTYPE_INTEGER}},
    {{"_CSD", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (1 Int(n), n-1 Int) */
                    {{{ACPI_PTYPE2_COUNT, ACPI_RTYPE_INTEGER, 0,0}, 0,0}},

    {{"_CST", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (1 Int(n), n Pkg (1 Buf/3 Int) */
                    {{{ACPI_PTYPE2_PKG_COUNT,ACPI_RTYPE_BUFFER, 1, ACPI_RTYPE_INTEGER}, 3,0}},

    {{"_DCK", 1, ACPI_RTYPE_INTEGER}},
    {{"_DCS", 0, ACPI_RTYPE_INTEGER}},
    {{"_DDC", 1, ACPI_RTYPE_INTEGER | ACPI_RTYPE_BUFFER}},
    {{"_DDN", 0, ACPI_RTYPE_STRING}},
    {{"_DGS", 0, ACPI_RTYPE_INTEGER}},
    {{"_DIS", 0, 0}},
    {{"_DMA", 0, ACPI_RTYPE_BUFFER}},
    {{"_DOD", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Ints) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER, 0,0}, 0,0}},

    {{"_DOS", 1, 0}},
    {{"_DSM", 4, ACPI_RTYPE_ALL}},     /* Must return a type, but it can be of any type */
    {{"_DSS", 1, 0}},
    {{"_DSW", 3, 0}},
    {{"_DTI", 1, 0}},
    {{"_EC_", 0, ACPI_RTYPE_INTEGER}},
    {{"_EDL", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs)*/
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_EJ0", 1, 0}},
    {{"_EJ1", 1, 0}},
    {{"_EJ2", 1, 0}},
    {{"_EJ3", 1, 0}},
    {{"_EJ4", 1, 0}},
    {{"_EJD", 0, ACPI_RTYPE_STRING}},
    {{"_FDE", 0, ACPI_RTYPE_BUFFER}},
    {{"_FDI", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (16 Int) */
                    {{{ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 16,0}, 0,0}},

    {{"_FDM", 1, 0}},
    {{"_FIF", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (4 Int) */
                    {{{ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 4,0}, 0,0}},

    {{"_FIX", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Ints) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER, 0,0}, 0,0}},

    {{"_FPS", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (1 Int(rev), n Pkg (5 Int) */
                    {{{ACPI_PTYPE2_REV_FIXED,ACPI_RTYPE_INTEGER, 5, 0}, 0,0}},

    {{"_FSL", 1, 0}},
    {{"_FST", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (3 Int) */
                    {{{ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 3,0}, 0,0}},


    {{"_GAI", 0, ACPI_RTYPE_INTEGER}},
    {{"_GHL", 0, ACPI_RTYPE_INTEGER}},
    {{"_GLK", 0, ACPI_RTYPE_INTEGER}},
    {{"_GPD", 0, ACPI_RTYPE_INTEGER}},
    {{"_GPE", 0, ACPI_RTYPE_INTEGER}}, /* _GPE method, not _GPE scope */
    {{"_GSB", 0, ACPI_RTYPE_INTEGER}},
    {{"_GTF", 0, ACPI_RTYPE_BUFFER}},
    {{"_GTM", 0, ACPI_RTYPE_BUFFER}},
    {{"_GTS", 1, 0}},
    {{"_HID", 0, ACPI_RTYPE_INTEGER | ACPI_RTYPE_STRING}},
    {{"_HOT", 0, ACPI_RTYPE_INTEGER}},
    {{"_HPP", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (4 Int) */
                    {{{ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 4,0}, 0,0}},

    /*
     * For _HPX, a single package is returned, containing a Variable-length number
     * of sub-packages. Each sub-package contains a PCI record setting.
     * There are several different type of record settings, of different
     * lengths, but all elements of all settings are Integers.
     */
    {{"_HPX", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Pkgs) each (var Ints) */
                    {{{ACPI_PTYPE2_MIN, ACPI_RTYPE_INTEGER, 5,0}, 0,0}},

    {{"_IFT", 0, ACPI_RTYPE_INTEGER}}, /* See IPMI spec */
    {{"_INI", 0, 0}},
    {{"_IRC", 0, 0}},
    {{"_LCK", 1, 0}},
    {{"_LID", 0, ACPI_RTYPE_INTEGER}},
    {{"_MAT", 0, ACPI_RTYPE_BUFFER}},
    {{"_MBM", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (8 Int) */
                    {{{ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 8,0}, 0,0}},

    {{"_MLS", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Pkgs) each (2 Str) */
                    {{{ACPI_PTYPE2, ACPI_RTYPE_STRING, 2,0}, 0,0}},

    {{"_MSG", 1, 0}},
    {{"_MSM", 4, ACPI_RTYPE_INTEGER}},
    {{"_NTT", 0, ACPI_RTYPE_INTEGER}},
    {{"_OFF", 0, 0}},
    {{"_ON_", 0, 0}},
    {{"_OS_", 0, ACPI_RTYPE_STRING}},
    {{"_OSC", 4, ACPI_RTYPE_BUFFER}},
    {{"_OST", 3, 0}},
    {{"_PAI", 1, ACPI_RTYPE_INTEGER}},
    {{"_PCL", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_PCT", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (2 Buf) */
                    {{{ACPI_PTYPE1_FIXED, ACPI_RTYPE_BUFFER, 2,0}, 0,0}},

    {{"_PDC", 1, 0}},
    {{"_PDL", 0, ACPI_RTYPE_INTEGER}},
    {{"_PIC", 1, 0}},
    {{"_PIF", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (3 Int),(3 Str) */
                    {{{ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 3, ACPI_RTYPE_STRING}, 3,0}},

    {{"_PLD", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Bufs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_BUFFER, 0,0}, 0,0}},

    {{"_PMC", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (11 Int),(3 Str) */
                    {{{ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 11, ACPI_RTYPE_STRING}, 3,0}},

    {{"_PMD", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_PMM", 0, ACPI_RTYPE_INTEGER}},
    {{"_PPC", 0, ACPI_RTYPE_INTEGER}},
    {{"_PPE", 0, ACPI_RTYPE_INTEGER}}, /* See dig64 spec */
    {{"_PR0", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_PR1", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_PR2", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_PR3", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_PRL", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_PRS", 0, ACPI_RTYPE_BUFFER}},

    /*
     * For _PRT, many BIOSs reverse the 3rd and 4th Package elements (Source
     * and SourceIndex). This bug is so prevalent that there is code in the
     * ACPICA Resource Manager to detect this and switch them back. For now,
     * do not allow and issue a warning. To allow this and eliminate the
     * warning, add the ACPI_RTYPE_REFERENCE type to the 4th element (index 3)
     * in the statement below.
     */
    {{"_PRT", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Pkgs) each (4): Int,Int,Int/Ref,Int */
                    {{{ACPI_PTYPE2_FIXED, 4, ACPI_RTYPE_INTEGER,ACPI_RTYPE_INTEGER},
                    ACPI_RTYPE_INTEGER | ACPI_RTYPE_REFERENCE,
                    ACPI_RTYPE_INTEGER}},

    {{"_PRW", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Pkgs) each: Pkg/Int,Int,[Variable-length Refs] (Pkg is Ref/Int) */
                    {{{ACPI_PTYPE1_OPTION, 2, ACPI_RTYPE_INTEGER | ACPI_RTYPE_PACKAGE,
                    ACPI_RTYPE_INTEGER}, ACPI_RTYPE_REFERENCE,0}},

    {{"_PS0", 0, 0}},
    {{"_PS1", 0, 0}},
    {{"_PS2", 0, 0}},
    {{"_PS3", 0, 0}},
    {{"_PSC", 0, ACPI_RTYPE_INTEGER}},
    {{"_PSD", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Pkgs) each (5 Int) with count */
                    {{{ACPI_PTYPE2_COUNT, ACPI_RTYPE_INTEGER,0,0}, 0,0}},

    {{"_PSL", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_PSR", 0, ACPI_RTYPE_INTEGER}},
    {{"_PSS", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Pkgs) each (6 Int) */
                    {{{ACPI_PTYPE2, ACPI_RTYPE_INTEGER, 6,0}, 0,0}},

    {{"_PSV", 0, ACPI_RTYPE_INTEGER}},
    {{"_PSW", 1, 0}},
    {{"_PTC", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (2 Buf) */
                    {{{ACPI_PTYPE1_FIXED, ACPI_RTYPE_BUFFER, 2,0}, 0,0}},

    {{"_PTP", 2, ACPI_RTYPE_INTEGER}},
    {{"_PTS", 1, 0}},
    {{"_PUR", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (2 Int) */
                    {{{ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 2,0}, 0,0}},

    {{"_PXM", 0, ACPI_RTYPE_INTEGER}},
    {{"_REG", 2, 0}},
    {{"_REV", 0, ACPI_RTYPE_INTEGER}},
    {{"_RMV", 0, ACPI_RTYPE_INTEGER}},
    {{"_ROM", 2, ACPI_RTYPE_BUFFER}},
    {{"_RTV", 0, ACPI_RTYPE_INTEGER}},

    /*
     * For _S0_ through _S5_, the ACPI spec defines a return Package
     * containing 1 Integer, but most DSDTs have it wrong - 2,3, or 4 integers.
     * Allow this by making the objects "Variable-length length", but all elements
     * must be Integers.
     */
    {{"_S0_", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (1 Int) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER, 1,0}, 0,0}},

    {{"_S1_", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (1 Int) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER, 1,0}, 0,0}},

    {{"_S2_", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (1 Int) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER, 1,0}, 0,0}},

    {{"_S3_", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (1 Int) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER, 1,0}, 0,0}},

    {{"_S4_", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (1 Int) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER, 1,0}, 0,0}},

    {{"_S5_", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (1 Int) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_INTEGER, 1,0}, 0,0}},

    {{"_S1D", 0, ACPI_RTYPE_INTEGER}},
    {{"_S2D", 0, ACPI_RTYPE_INTEGER}},
    {{"_S3D", 0, ACPI_RTYPE_INTEGER}},
    {{"_S4D", 0, ACPI_RTYPE_INTEGER}},
    {{"_S0W", 0, ACPI_RTYPE_INTEGER}},
    {{"_S1W", 0, ACPI_RTYPE_INTEGER}},
    {{"_S2W", 0, ACPI_RTYPE_INTEGER}},
    {{"_S3W", 0, ACPI_RTYPE_INTEGER}},
    {{"_S4W", 0, ACPI_RTYPE_INTEGER}},
    {{"_SBS", 0, ACPI_RTYPE_INTEGER}},
    {{"_SCP", 0x13, 0}},               /* Acpi 1.0 allowed 1 arg. Acpi 3.0 expanded to 3 args. Allow both. */
                                       /* Note: the 3-arg definition may be removed for ACPI 4.0 */
    {{"_SDD", 1, 0}},
    {{"_SEG", 0, ACPI_RTYPE_INTEGER}},
    {{"_SHL", 1, ACPI_RTYPE_INTEGER}},
    {{"_SLI", 0, ACPI_RTYPE_BUFFER}},
    {{"_SPD", 1, ACPI_RTYPE_INTEGER}},
    {{"_SRS", 1, 0}},
    {{"_SRV", 0, ACPI_RTYPE_INTEGER}}, /* See IPMI spec */
    {{"_SST", 1, 0}},
    {{"_STA", 0, ACPI_RTYPE_INTEGER}},
    {{"_STM", 3, 0}},
    {{"_STP", 2, ACPI_RTYPE_INTEGER}},
    {{"_STR", 0, ACPI_RTYPE_BUFFER}},
    {{"_STV", 2, ACPI_RTYPE_INTEGER}},
    {{"_SUN", 0, ACPI_RTYPE_INTEGER}},
    {{"_SWS", 0, ACPI_RTYPE_INTEGER}},
    {{"_TC1", 0, ACPI_RTYPE_INTEGER}},
    {{"_TC2", 0, ACPI_RTYPE_INTEGER}},
    {{"_TIP", 1, ACPI_RTYPE_INTEGER}},
    {{"_TIV", 1, ACPI_RTYPE_INTEGER}},
    {{"_TMP", 0, ACPI_RTYPE_INTEGER}},
    {{"_TPC", 0, ACPI_RTYPE_INTEGER}},
    {{"_TPT", 1, 0}},
    {{"_TRT", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Pkgs) each 2Ref/6Int */
                    {{{ACPI_PTYPE2, ACPI_RTYPE_REFERENCE, 2, ACPI_RTYPE_INTEGER}, 6, 0}},

    {{"_TSD", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Pkgs) each 5Int with count */
                    {{{ACPI_PTYPE2_COUNT,ACPI_RTYPE_INTEGER, 5,0}, 0,0}},

    {{"_TSP", 0, ACPI_RTYPE_INTEGER}},
    {{"_TSS", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Pkgs) each 5Int */
                    {{{ACPI_PTYPE2, ACPI_RTYPE_INTEGER, 5,0}, 0,0}},

    {{"_TST", 0, ACPI_RTYPE_INTEGER}},
    {{"_TTS", 1, 0}},
    {{"_TZD", 0, ACPI_RTYPE_PACKAGE}}, /* Variable-length (Refs) */
                    {{{ACPI_PTYPE1_VAR, ACPI_RTYPE_REFERENCE, 0,0}, 0,0}},

    {{"_TZM", 0, ACPI_RTYPE_REFERENCE}},
    {{"_TZP", 0, ACPI_RTYPE_INTEGER}},
    {{"_UID", 0, ACPI_RTYPE_INTEGER | ACPI_RTYPE_STRING}},
    {{"_UPC", 0, ACPI_RTYPE_PACKAGE}}, /* Fixed-length (4 Int) */
                    {{{ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 4,0}, 0,0}},

    {{"_UPD", 0, ACPI_RTYPE_INTEGER}},
    {{"_UPP", 0, ACPI_RTYPE_INTEGER}},
    {{"_VPO", 0, ACPI_RTYPE_INTEGER}},

    /* Acpi 1.0 defined _WAK with no return value. Later, it was changed to return a package */

    {{"_WAK", 1, ACPI_RTYPE_NONE | ACPI_RTYPE_INTEGER | ACPI_RTYPE_PACKAGE}},
                    {{{ACPI_PTYPE1_FIXED, ACPI_RTYPE_INTEGER, 2,0}, 0,0}}, /* Fixed-length (2 Int), but is optional */

    /* _WDG/_WED are MS extensions defined by "Windows Instrumentation" */

    {{"_WDG", 0, ACPI_RTYPE_BUFFER}},
    {{"_WED", 1, ACPI_RTYPE_INTEGER | ACPI_RTYPE_STRING | ACPI_RTYPE_BUFFER}},

    {{{0,0,0,0}, 0,0}} /* Table terminator */
};

#if 0

    /* This is an internally implemented control method, no need to check */
    {{"_OSI", 1, ACPI_RTYPE_INTEGER}},

    /* TBD: */

    _PRT - currently ignore reversed entries. Attempt to fix here?
    Think about possibly fixing package elements like _BIF, etc.
#endif
#endif
#endif
