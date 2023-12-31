/******************************************************************************
 *
 * Module Name: evgpe - General Purpose Event handling and dispatch
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

#include "acpi.h"
#include "accommon.h"
#include "acevents.h"
#include "acnamesp.h"

#define _COMPONENT          ACPI_EVENTS
        ACPI_MODULE_NAME    ("evgpe")

/* Local prototypes */

static void ACPI_SYSTEM_XFACE
AcpiEvAsynchExecuteGpeMethod (
    void                    *Context);

static void ACPI_SYSTEM_XFACE
AcpiEvAsynchEnableGpe (
    void                    *Context);


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvUpdateGpeEnableMask
 *
 * PARAMETERS:  GpeEventInfo            - GPE to update
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Updates GPE register enable mask based upon whether there are
 *              runtime references to this GPE
 *
 ******************************************************************************/

ACPI_STATUS
AcpiEvUpdateGpeEnableMask (
    ACPI_GPE_EVENT_INFO     *GpeEventInfo)
{
    ACPI_GPE_REGISTER_INFO  *GpeRegisterInfo;
    UINT32                  RegisterBit;


    ACPI_FUNCTION_TRACE (EvUpdateGpeEnableMask);


    GpeRegisterInfo = GpeEventInfo->RegisterInfo;
    if (!GpeRegisterInfo)
    {
        return_ACPI_STATUS (AE_NOT_EXIST);
    }

    RegisterBit = AcpiHwGetGpeRegisterBit (GpeEventInfo, GpeRegisterInfo);

    /* Clear the run bit up front */

    ACPI_CLEAR_BIT (GpeRegisterInfo->EnableForRun, RegisterBit);

    /* Set the mask bit only if there are references to this GPE */

    if (GpeEventInfo->RuntimeCount)
    {
        ACPI_SET_BIT (GpeRegisterInfo->EnableForRun, (UINT8) RegisterBit);
    }

    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvEnableGpe
 *
 * PARAMETERS:  GpeEventInfo            - GPE to enable
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Clear a GPE of stale events and enable it.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiEvEnableGpe (
    ACPI_GPE_EVENT_INFO     *GpeEventInfo)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (EvEnableGpe);


    /*
     * We will only allow a GPE to be enabled if it has either an
     * associated method (_Lxx/_Exx) or a handler. Otherwise, the
     * GPE will be immediately disabled by AcpiEvGpeDispatch the
     * first time it fires.
     */
    if (!(GpeEventInfo->Flags & ACPI_GPE_DISPATCH_MASK))
    {
        return_ACPI_STATUS (AE_NO_HANDLER);
    }

    /* Clear the GPE (of stale events) */

    Status = AcpiHwClearGpe (GpeEventInfo);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Enable the requested GPE */

    Status = AcpiHwLowSetGpe (GpeEventInfo, ACPI_GPE_ENABLE);
    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvLowGetGpeInfo
 *
 * PARAMETERS:  GpeNumber           - Raw GPE number
 *              GpeBlock            - A GPE info block
 *
 * RETURN:      A GPE EventInfo struct. NULL if not a valid GPE (The GpeNumber
 *              is not within the specified GPE block)
 *
 * DESCRIPTION: Returns the EventInfo struct associated with this GPE. This is
 *              the low-level implementation of EvGetGpeEventInfo.
 *
 ******************************************************************************/

ACPI_GPE_EVENT_INFO *
AcpiEvLowGetGpeInfo (
    UINT32                  GpeNumber,
    ACPI_GPE_BLOCK_INFO     *GpeBlock)
{
    UINT32                  GpeIndex;


    /*
     * Validate that the GpeNumber is within the specified GpeBlock.
     * (Two steps)
     */
    if (!GpeBlock ||
        (GpeNumber < GpeBlock->BlockBaseNumber))
    {
        return (NULL);
    }

    GpeIndex = GpeNumber - GpeBlock->BlockBaseNumber;
    if (GpeIndex >= GpeBlock->GpeCount)
    {
        return (NULL);
    }

    return (&GpeBlock->EventInfo[GpeIndex]);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvGetGpeEventInfo
 *
 * PARAMETERS:  GpeDevice           - Device node. NULL for GPE0/GPE1
 *              GpeNumber           - Raw GPE number
 *
 * RETURN:      A GPE EventInfo struct. NULL if not a valid GPE
 *
 * DESCRIPTION: Returns the EventInfo struct associated with this GPE.
 *              Validates the GpeBlock and the GpeNumber
 *
 *              Should be called only when the GPE lists are semaphore locked
 *              and not subject to change.
 *
 ******************************************************************************/

ACPI_GPE_EVENT_INFO *
AcpiEvGetGpeEventInfo (
    ACPI_HANDLE             GpeDevice,
    UINT32                  GpeNumber)
{
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_GPE_EVENT_INFO     *GpeInfo;
    UINT32                  i;


    ACPI_FUNCTION_ENTRY ();


    /* A NULL GpeDevice means use the FADT-defined GPE block(s) */

    if (!GpeDevice)
    {
        /* Examine GPE Block 0 and 1 (These blocks are permanent) */

        for (i = 0; i < ACPI_MAX_GPE_BLOCKS; i++)
        {
            GpeInfo = AcpiEvLowGetGpeInfo (GpeNumber,
                        AcpiGbl_GpeFadtBlocks[i]);
            if (GpeInfo)
            {
                return (GpeInfo);
            }
        }

        /* The GpeNumber was not in the range of either FADT GPE block */

        return (NULL);
    }

    /* A Non-NULL GpeDevice means this is a GPE Block Device */

    ObjDesc = AcpiNsGetAttachedObject ((ACPI_NAMESPACE_NODE *) GpeDevice);
    if (!ObjDesc ||
        !ObjDesc->Device.GpeBlock)
    {
        return (NULL);
    }

    return (AcpiEvLowGetGpeInfo (GpeNumber, ObjDesc->Device.GpeBlock));
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvGpeDetect
 *
 * PARAMETERS:  GpeXruptList        - Interrupt block for this interrupt.
 *                                    Can have multiple GPE blocks attached.
 *
 * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED
 *
 * DESCRIPTION: Detect if any GP events have occurred. This function is
 *              executed at interrupt level.
 *
 ******************************************************************************/

UINT32
AcpiEvGpeDetect (
    ACPI_GPE_XRUPT_INFO     *GpeXruptList)
{
    ACPI_STATUS             Status;
    ACPI_GPE_BLOCK_INFO     *GpeBlock;
    ACPI_GPE_REGISTER_INFO  *GpeRegisterInfo;
    UINT32                  IntStatus = ACPI_INTERRUPT_NOT_HANDLED;
    UINT8                   EnabledStatusByte;
    UINT32                  StatusReg;
    UINT32                  EnableReg;
    ACPI_CPU_FLAGS          Flags;
    UINT32                  i;
    UINT32                  j;


    ACPI_FUNCTION_NAME (EvGpeDetect);

    /* Check for the case where there are no GPEs */

    if (!GpeXruptList)
    {
        return (IntStatus);
    }

    /*
     * We need to obtain the GPE lock for both the data structs and registers
     * Note: Not necessary to obtain the hardware lock, since the GPE
     * registers are owned by the GpeLock.
     */
    Flags = AcpiOsAcquireLock (AcpiGbl_GpeLock);

    /* Examine all GPE blocks attached to this interrupt level */

    GpeBlock = GpeXruptList->GpeBlockListHead;
    while (GpeBlock)
    {
        /*
         * Read all of the 8-bit GPE status and enable registers in this GPE
         * block, saving all of them. Find all currently active GP events.
         */
        for (i = 0; i < GpeBlock->RegisterCount; i++)
        {
            /* Get the next status/enable pair */

            GpeRegisterInfo = &GpeBlock->RegisterInfo[i];

            /* Read the Status Register */

            Status = AcpiHwRead (&StatusReg, &GpeRegisterInfo->StatusAddress);
            if (ACPI_FAILURE (Status))
            {
                goto UnlockAndExit;
            }

            /* Read the Enable Register */

            Status = AcpiHwRead (&EnableReg, &GpeRegisterInfo->EnableAddress);
            if (ACPI_FAILURE (Status))
            {
                goto UnlockAndExit;
            }

            ACPI_DEBUG_PRINT ((ACPI_DB_INTERRUPTS,
                "Read GPE Register at GPE%X: Status=%02X, Enable=%02X\n",
                GpeRegisterInfo->BaseGpeNumber, StatusReg, EnableReg));

            /* Check if there is anything active at all in this register */

            EnabledStatusByte = (UINT8) (StatusReg & EnableReg);
            if (!EnabledStatusByte)
            {
                /* No active GPEs in this register, move on */

                continue;
            }

            /* Now look at the individual GPEs in this byte register */

            for (j = 0; j < ACPI_GPE_REGISTER_WIDTH; j++)
            {
                /* Examine one GPE bit */

                if (EnabledStatusByte & (1 << j))
                {
                    /*
                     * Found an active GPE. Dispatch the event to a handler
                     * or method.
                     */
                    IntStatus |= AcpiEvGpeDispatch (
                        &GpeBlock->EventInfo[((ACPI_SIZE) i *
                            ACPI_GPE_REGISTER_WIDTH) + j],
                        j + GpeRegisterInfo->BaseGpeNumber);
                }
            }
        }

        GpeBlock = GpeBlock->Next;
    }

UnlockAndExit:

    AcpiOsReleaseLock (AcpiGbl_GpeLock, Flags);
    return (IntStatus);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvAsynchExecuteGpeMethod
 *
 * PARAMETERS:  Context (GpeEventInfo) - Info for this GPE
 *
 * RETURN:      None
 *
 * DESCRIPTION: Perform the actual execution of a GPE control method. This
 *              function is called from an invocation of AcpiOsExecute and
 *              therefore does NOT execute at interrupt level - so that
 *              the control method itself is not executed in the context of
 *              an interrupt handler.
 *
 ******************************************************************************/

static void ACPI_SYSTEM_XFACE
AcpiEvAsynchExecuteGpeMethod (
    void                    *Context)
{
    ACPI_GPE_EVENT_INFO     *GpeEventInfo = Context;
    ACPI_STATUS             Status;
    ACPI_GPE_EVENT_INFO     *LocalGpeEventInfo;
    ACPI_EVALUATE_INFO      *Info;


    ACPI_FUNCTION_TRACE (EvAsynchExecuteGpeMethod);


    /* Allocate a local GPE block */

    LocalGpeEventInfo = ACPI_ALLOCATE_ZEROED (sizeof (ACPI_GPE_EVENT_INFO));
    if (!LocalGpeEventInfo)
    {
        ACPI_EXCEPTION ((AE_INFO, AE_NO_MEMORY,
            "while handling a GPE"));
        return_VOID;
    }

    Status = AcpiUtAcquireMutex (ACPI_MTX_EVENTS);
    if (ACPI_FAILURE (Status))
    {
        return_VOID;
    }

    /* Must revalidate the GpeNumber/GpeBlock */

    if (!AcpiEvValidGpeEvent (GpeEventInfo))
    {
        Status = AcpiUtReleaseMutex (ACPI_MTX_EVENTS);
        return_VOID;
    }

    /*
     * Take a snapshot of the GPE info for this level - we copy the info to
     * prevent a race condition with RemoveHandler/RemoveBlock.
     */
    ACPI_MEMCPY (LocalGpeEventInfo, GpeEventInfo,
        sizeof (ACPI_GPE_EVENT_INFO));

    Status = AcpiUtReleaseMutex (ACPI_MTX_EVENTS);
    if (ACPI_FAILURE (Status))
    {
        return_VOID;
    }

    /*
     * Must check for control method type dispatch one more time to avoid a
     * race with EvGpeInstallHandler
     */
    if ((LocalGpeEventInfo->Flags & ACPI_GPE_DISPATCH_MASK) ==
            ACPI_GPE_DISPATCH_METHOD)
    {
        /* Allocate the evaluation information block */

        Info = ACPI_ALLOCATE_ZEROED (sizeof (ACPI_EVALUATE_INFO));
        if (!Info)
        {
            Status = AE_NO_MEMORY;
        }
        else
        {
            /*
             * Invoke the GPE Method (_Lxx, _Exx) i.e., evaluate the _Lxx/_Exx
             * control method that corresponds to this GPE
             */
            Info->PrefixNode = LocalGpeEventInfo->Dispatch.MethodNode;
            Info->Flags = ACPI_IGNORE_RETURN_VALUE;

            Status = AcpiNsEvaluate (Info);
            ACPI_FREE (Info);
        }

        if (ACPI_FAILURE (Status))
        {
            ACPI_EXCEPTION ((AE_INFO, Status,
                "while evaluating GPE method [%4.4s]",
                AcpiUtGetNodeName (LocalGpeEventInfo->Dispatch.MethodNode)));
        }
    }

    /* Defer enabling of GPE until all notify handlers are done */

    Status = AcpiOsExecute (OSL_NOTIFY_HANDLER,
                AcpiEvAsynchEnableGpe, LocalGpeEventInfo);
    if (ACPI_FAILURE (Status))
    {
        ACPI_FREE (LocalGpeEventInfo);
    }
    return_VOID;
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvAsynchEnableGpe
 *
 * PARAMETERS:  Context (GpeEventInfo) - Info for this GPE
 *
 * RETURN:      None
 *
 * DESCRIPTION: Asynchronous clear/enable for GPE. This allows the GPE to
 *              complete (i.e., finish execution of Notify)
 *
 ******************************************************************************/

static void ACPI_SYSTEM_XFACE
AcpiEvAsynchEnableGpe (
    void                    *Context)
{
    ACPI_GPE_EVENT_INFO     *GpeEventInfo = Context;
    ACPI_STATUS             Status;


    if ((GpeEventInfo->Flags & ACPI_GPE_XRUPT_TYPE_MASK) ==
            ACPI_GPE_LEVEL_TRIGGERED)
    {
        /*
         * GPE is level-triggered, we clear the GPE status bit after handling
         * the event.
         */
        Status = AcpiHwClearGpe (GpeEventInfo);
        if (ACPI_FAILURE (Status))
        {
            goto Exit;
        }
    }

    /*
     * Enable this GPE, conditionally. This means that the GPE will only be
     * physically enabled if the EnableForRun bit is set in the EventInfo
     */
    (void) AcpiHwLowSetGpe (GpeEventInfo, ACPI_GPE_CONDITIONAL_ENABLE);

Exit:
    ACPI_FREE (GpeEventInfo);
    return;
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiEvGpeDispatch
 *
 * PARAMETERS:  GpeEventInfo    - Info for this GPE
 *              GpeNumber       - Number relative to the parent GPE block
 *
 * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED
 *
 * DESCRIPTION: Dispatch a General Purpose Event to either a function (e.g. EC)
 *              or method (e.g. _Lxx/_Exx) handler.
 *
 *              This function executes at interrupt level.
 *
 ******************************************************************************/

UINT32
AcpiEvGpeDispatch (
    ACPI_GPE_EVENT_INFO     *GpeEventInfo,
    UINT32                  GpeNumber)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (EvGpeDispatch);


    AcpiGpeCount++;

    /*
     * If edge-triggered, clear the GPE status bit now. Note that
     * level-triggered events are cleared after the GPE is serviced.
     */
    if ((GpeEventInfo->Flags & ACPI_GPE_XRUPT_TYPE_MASK) ==
            ACPI_GPE_EDGE_TRIGGERED)
    {
        Status = AcpiHwClearGpe (GpeEventInfo);
        if (ACPI_FAILURE (Status))
        {
            ACPI_EXCEPTION ((AE_INFO, Status,
                "Unable to clear GPE[0x%2X]", GpeNumber));
            return_UINT32 (ACPI_INTERRUPT_NOT_HANDLED);
        }
    }

    /*
     * Dispatch the GPE to either an installed handler, or the control method
     * associated with this GPE (_Lxx or _Exx). If a handler exists, we invoke
     * it and do not attempt to run the method. If there is neither a handler
     * nor a method, we disable this GPE to prevent further such pointless
     * events from firing.
     */
    switch (GpeEventInfo->Flags & ACPI_GPE_DISPATCH_MASK)
    {
    case ACPI_GPE_DISPATCH_HANDLER:

        /*
         * Invoke the installed handler (at interrupt level)
         * Ignore return status for now.
         * TBD: leave GPE disabled on error?
         */
        (void) GpeEventInfo->Dispatch.Handler->Address (
                        GpeEventInfo->Dispatch.Handler->Context);

        /* It is now safe to clear level-triggered events. */

        if ((GpeEventInfo->Flags & ACPI_GPE_XRUPT_TYPE_MASK) ==
                ACPI_GPE_LEVEL_TRIGGERED)
        {
            Status = AcpiHwClearGpe (GpeEventInfo);
            if (ACPI_FAILURE (Status))
            {
                ACPI_EXCEPTION ((AE_INFO, Status,
                    "Unable to clear GPE[0x%2X]", GpeNumber));
                return_UINT32 (ACPI_INTERRUPT_NOT_HANDLED);
            }
        }
        break;

    case ACPI_GPE_DISPATCH_METHOD:

        /*
         * Disable the GPE, so it doesn't keep firing before the method has a
         * chance to run (it runs asynchronously with interrupts enabled).
         */
        Status = AcpiHwLowSetGpe (GpeEventInfo, ACPI_GPE_DISABLE);
        if (ACPI_FAILURE (Status))
        {
            ACPI_EXCEPTION ((AE_INFO, Status,
                "Unable to disable GPE[0x%2X]", GpeNumber));
            return_UINT32 (ACPI_INTERRUPT_NOT_HANDLED);
        }

        /*
         * Execute the method associated with the GPE
         * NOTE: Level-triggered GPEs are cleared after the method completes.
         */
        Status = AcpiOsExecute (OSL_GPE_HANDLER,
                    AcpiEvAsynchExecuteGpeMethod, GpeEventInfo);
        if (ACPI_FAILURE (Status))
        {
            ACPI_EXCEPTION ((AE_INFO, Status,
                "Unable to queue handler for GPE[0x%2X] - event disabled",
                GpeNumber));
        }
        break;

    default:

        /*
         * No handler or method to run!
         * 03/2010: This case should no longer be possible. We will not allow
         * a GPE to be enabled if it has no handler or method.
         */
        ACPI_ERROR ((AE_INFO,
            "No handler or method for GPE[0x%2X], disabling event",
            GpeNumber));

        /*
         * Disable the GPE. The GPE will remain disabled until a handler
         * is installed or ACPICA is restarted.
         */
        Status = AcpiHwLowSetGpe (GpeEventInfo, ACPI_GPE_DISABLE);
        if (ACPI_FAILURE (Status))
        {
            ACPI_EXCEPTION ((AE_INFO, Status,
                "Unable to disable GPE[0x%2X]", GpeNumber));
            return_UINT32 (ACPI_INTERRUPT_NOT_HANDLED);
        }
        break;
    }

    return_UINT32 (ACPI_INTERRUPT_HANDLED);
}

