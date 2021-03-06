/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */

#ifndef __LIBSEL4_SEL4_SEL4_ARCH_SYSCALLS_H_
#define __LIBSEL4_SEL4_SEL4_ARCH_SYSCALLS_H_

#include <autoconf.h>

#if defined(CONFIG_SYSENTER)
#include <sel4/sel4_arch/syscalls_sysenter.h>
#elif defined(CONFIG_SYSCALL)
#include <sel4/sel4_arch/syscalls_syscall.h>
#else
#error Unknown method for kernel syscalls
#endif

LIBSEL4_INLINE_FUNC void
rwfm_RegisterSubject(char *compName, seL4_Word compNo, seL4_Word owner, seL4_Word reader, seL4_Word writer)
{
    x64_sys_rwfm_RegisterSubject(seL4_Sysrwfm_RegisterSubject, compName, compNo, owner, reader, writer);
}

LIBSEL4_INLINE_FUNC void
rwfm_RegisterInterface(char* intName, seL4_Word intNo, seL4_Word owner, seL4_Word reader, seL4_Word writer)
{
    x64_sys_rwfm_RegisterInterface(seL4_Sysrwfm_RegisterInterface, intName, intNo, owner, reader, writer);
}

LIBSEL4_INLINE_FUNC void
rwfm_RegisterEndpoint(seL4_Word epNo, seL4_Word compNo, char* compName, seL4_Word intNo, char* intName)
{
    x64_sys_rwfm_RegisterEndpoint(seL4_Sysrwfm_RegisterEndpoint, epNo, compNo, compName, intNo, intName);
}

LIBSEL4_INLINE_FUNC void
rwfm_RegisterThread(seL4_Word thrNo, char* thrName, seL4_Word compNo, char* compName)
{
    x64_sys_rwfm_RegisterThread(seL4_Sysrwfm_RegisterThread, thrNo, thrName, compNo, compName);
}

LIBSEL4_INLINE_FUNC seL4_Word
rwfm_CheckDataFlowStatus(seL4_Word compNo, seL4_Word epNo)
{
    seL4_Word status;
    x64_sys_rwfm_CheckDataFlowStatus(seL4_Sysrwfm_CheckDataFlowStatus, compNo, epNo, &status);
		return status;
}

LIBSEL4_INLINE_FUNC void
seL4_Send(seL4_CPtr dest, seL4_MessageInfo_t msgInfo)
{
    x64_sys_send(seL4_SysSend, dest, msgInfo.words[0], seL4_GetMR(0), seL4_GetMR(1), seL4_GetMR(2), seL4_GetMR(3));
}

LIBSEL4_INLINE_FUNC void
seL4_SendWithMRs(seL4_CPtr dest, seL4_MessageInfo_t msgInfo,
                 seL4_Word *mr0, seL4_Word *mr1, seL4_Word *mr2, seL4_Word *mr3)
{
    x64_sys_send(seL4_SysSend, dest, msgInfo.words[0],
                 (mr0 != seL4_Null) ? *mr0 : 0,
                 (mr1 != seL4_Null) ? *mr1 : 0,
                 (mr2 != seL4_Null) ? *mr2 : 0,
                 (mr3 != seL4_Null) ? *mr3 : 0
                );
}

LIBSEL4_INLINE_FUNC void
seL4_NBSend(seL4_CPtr dest, seL4_MessageInfo_t msgInfo)
{
    x64_sys_send(seL4_SysNBSend, dest, msgInfo.words[0], seL4_GetMR(0), seL4_GetMR(1), seL4_GetMR(2), seL4_GetMR(3));
}

LIBSEL4_INLINE_FUNC void
seL4_NBSendWithMRs(seL4_CPtr dest, seL4_MessageInfo_t msgInfo,
                   seL4_Word *mr0, seL4_Word *mr1, seL4_Word *mr2, seL4_Word *mr3)
{
    x64_sys_send(seL4_SysNBSend, dest, msgInfo.words[0],
                 (mr0 != seL4_Null) ? *mr0 : 0,
                 (mr1 != seL4_Null) ? *mr1 : 0,
                 (mr2 != seL4_Null) ? *mr2 : 0,
                 (mr3 != seL4_Null) ? *mr3 : 0
                );
}

LIBSEL4_INLINE_FUNC void
seL4_Reply(seL4_MessageInfo_t msgInfo)
{
    x64_sys_reply(seL4_SysReply, msgInfo.words[0], seL4_GetMR(0), seL4_GetMR(1), seL4_GetMR(2), seL4_GetMR(3));
}

LIBSEL4_INLINE_FUNC void
seL4_ReplyWithMRs(seL4_MessageInfo_t msgInfo,
                  seL4_Word *mr0, seL4_Word *mr1, seL4_Word *mr2, seL4_Word *mr3)
{
    x64_sys_reply(seL4_SysReply, msgInfo.words[0],
                  (mr0 != seL4_Null) ? *mr0 : 0,
                  (mr1 != seL4_Null) ? *mr1 : 0,
                  (mr2 != seL4_Null) ? *mr2 : 0,
                  (mr3 != seL4_Null) ? *mr3 : 0
                 );
}

LIBSEL4_INLINE_FUNC void
seL4_Signal(seL4_CPtr dest)
{
    x64_sys_send_null(seL4_SysSend, dest, seL4_MessageInfo_new(0, 0, 0, 1).words[0]);
}

LIBSEL4_INLINE_FUNC seL4_MessageInfo_t
seL4_Recv(seL4_CPtr src, seL4_Word* sender)
{
    seL4_MessageInfo_t info;
    seL4_Word badge;
    seL4_Word mr0;
    seL4_Word mr1;
    seL4_Word mr2;
    seL4_Word mr3;

    x64_sys_recv(seL4_SysRecv, src, &badge, &info.words[0], &mr0, &mr1, &mr2, &mr3);

    seL4_SetMR(0, mr0);
    seL4_SetMR(1, mr1);
    seL4_SetMR(2, mr2);
    seL4_SetMR(3, mr3);

    if (sender) {
        *sender = badge;
    }

    return info;
}

LIBSEL4_INLINE_FUNC seL4_MessageInfo_t
seL4_RecvWithMRs(seL4_CPtr src, seL4_Word* sender,
                 seL4_Word *mr0, seL4_Word *mr1, seL4_Word *mr2, seL4_Word *mr3)
{
    seL4_MessageInfo_t info;
    seL4_Word badge;
    seL4_Word msg0;
    seL4_Word msg1;
    seL4_Word msg2;
    seL4_Word msg3;

    x64_sys_recv(seL4_SysRecv, src, &badge, &info.words[0], &msg0, &msg1, &msg2, &msg3);

    if (mr0 != seL4_Null) {
        *mr0 = msg0;
    }
    if (mr1 != seL4_Null) {
        *mr1 = msg1;
    }
    if (mr2 != seL4_Null) {
        *mr2 = msg2;
    }
    if (mr3 != seL4_Null) {
        *mr3 = msg3;
    }

    if (sender) {
        *sender = badge;
    }

    return info;
}

LIBSEL4_INLINE_FUNC seL4_MessageInfo_t
seL4_NBRecv(seL4_CPtr src, seL4_Word* sender)
{
    seL4_MessageInfo_t info;
    seL4_Word badge;
    seL4_Word mr0;
    seL4_Word mr1;
    seL4_Word mr2;
    seL4_Word mr3;

    x64_sys_recv(seL4_SysNBRecv, src, &badge, &info.words[0], &mr0, &mr1, &mr2, &mr3);

    seL4_SetMR(0, mr0);
    seL4_SetMR(1, mr1);
    seL4_SetMR(2, mr2);
    seL4_SetMR(3, mr3);

    if (sender) {
        *sender = badge;
    }

    return info;
}

LIBSEL4_INLINE_FUNC seL4_MessageInfo_t
seL4_Call(seL4_CPtr dest, seL4_MessageInfo_t msgInfo)
{

    seL4_MessageInfo_t info;
    seL4_Word mr0 = seL4_GetMR(0);
    seL4_Word mr1 = seL4_GetMR(1);
    seL4_Word mr2 = seL4_GetMR(2);
    seL4_Word mr3 = seL4_GetMR(3);

    x64_sys_send_recv(seL4_SysCall, dest, &dest, msgInfo.words[0], &info.words[0], &mr0, &mr1, &mr2, &mr3);

    seL4_SetMR(0, mr0);
    seL4_SetMR(1, mr1);
    seL4_SetMR(2, mr2);
    seL4_SetMR(3, mr3);

    return info;
}

LIBSEL4_INLINE_FUNC seL4_MessageInfo_t
seL4_CallWithMRs(seL4_CPtr dest, seL4_MessageInfo_t msgInfo,
                 seL4_Word *mr0, seL4_Word *mr1, seL4_Word *mr2, seL4_Word *mr3)
{
    seL4_MessageInfo_t info;
    seL4_Word msg0 = 0;
    seL4_Word msg1 = 0;
    seL4_Word msg2 = 0;
    seL4_Word msg3 = 0;

    if (mr0 != seL4_Null && seL4_MessageInfo_get_length(msgInfo) > 0) {
        msg0 = *mr0;
    }
    if (mr1 != seL4_Null && seL4_MessageInfo_get_length(msgInfo) > 1) {
        msg1 = *mr1;
    }
    if (mr2 != seL4_Null && seL4_MessageInfo_get_length(msgInfo) > 2) {
        msg2 = *mr2;
    }
    if (mr3 != seL4_Null && seL4_MessageInfo_get_length(msgInfo) > 3) {
        msg3 = *mr3;
    }

    x64_sys_send_recv(seL4_SysCall, dest, &dest, msgInfo.words[0], &info.words[0], &msg0, &msg1, &msg2, &msg3);

    if (mr0 != seL4_Null) {
        *mr0 = msg0;
    }
    if (mr1 != seL4_Null) {
        *mr1 = msg1;
    }
    if (mr2 != seL4_Null) {
        *mr2 = msg2;
    }
    if (mr3 != seL4_Null) {
        *mr3 = msg3;
    }

    return info;
}

LIBSEL4_INLINE_FUNC seL4_MessageInfo_t
seL4_ReplyRecv(seL4_CPtr dest, seL4_MessageInfo_t msgInfo, seL4_Word *sender)
{
    seL4_MessageInfo_t info;
    seL4_Word badge;
    seL4_Word mr0 = seL4_GetMR(0);
    seL4_Word mr1 = seL4_GetMR(1);
    seL4_Word mr2 = seL4_GetMR(2);
    seL4_Word mr3 = seL4_GetMR(3);

    x64_sys_send_recv(seL4_SysReplyRecv, dest, &badge, msgInfo.words[0], &info.words[0], &mr0, &mr1, &mr2, &mr3);

    seL4_SetMR(0, mr0);
    seL4_SetMR(1, mr1);
    seL4_SetMR(2, mr2);
    seL4_SetMR(3, mr3);

    if (sender) {
        *sender = badge;
    }

    return info;
}

LIBSEL4_INLINE_FUNC seL4_MessageInfo_t
seL4_ReplyRecvWithMRs(seL4_CPtr dest, seL4_MessageInfo_t msgInfo, seL4_Word *sender,
                      seL4_Word *mr0, seL4_Word *mr1, seL4_Word *mr2, seL4_Word *mr3)
{
    seL4_MessageInfo_t info;
    seL4_Word badge;
    seL4_Word msg0 = 0;
    seL4_Word msg1 = 0;
    seL4_Word msg2 = 0;
    seL4_Word msg3 = 0;

    if (mr0 != seL4_Null && seL4_MessageInfo_get_length(msgInfo) > 0) {
        msg0 = *mr0;
    }
    if (mr1 != seL4_Null && seL4_MessageInfo_get_length(msgInfo) > 1) {
        msg1 = *mr1;
    }
    if (mr2 != seL4_Null && seL4_MessageInfo_get_length(msgInfo) > 2) {
        msg2 = *mr2;
    }
    if (mr3 != seL4_Null && seL4_MessageInfo_get_length(msgInfo) > 3) {
        msg3 = *mr3;
    }

    x64_sys_send_recv(seL4_SysReplyRecv, dest, &badge, msgInfo.words[0], &info.words[0], &msg0, &msg1, &msg2, &msg3);

    if (mr0 != seL4_Null) {
        *mr0 = msg0;
    }
    if (mr1 != seL4_Null) {
        *mr1 = msg1;
    }
    if (mr2 != seL4_Null) {
        *mr2 = msg2;
    }
    if (mr3 != seL4_Null) {
        *mr3 = msg3;
    }

    if (sender) {
        *sender = badge;
    }

    return info;
}

LIBSEL4_INLINE_FUNC void
seL4_Yield(void)
{
    x64_sys_null(seL4_SysYield);
    asm volatile("" ::: "memory");
}

#ifdef CONFIG_VTX
static inline seL4_Word
seL4_VMEnter(seL4_Word *sender)
{
    seL4_Word fault;
    seL4_Word badge;
    seL4_Word mr0 = seL4_GetMR(0);
    seL4_Word mr1 = seL4_GetMR(1);
    seL4_Word mr2 = seL4_GetMR(2);
    seL4_Word mr3 = seL4_GetMR(3);

    x64_sys_send_recv(seL4_SysVMEnter, 0, &badge, 0, &fault, &mr0, &mr1, &mr2, &mr3);

    seL4_SetMR(0, mr0);
    seL4_SetMR(1, mr1);
    seL4_SetMR(2, mr2);
    seL4_SetMR(3, mr3);
    if (!fault && sender) {
        *sender = badge;
    }
    return fault;
}
#endif

#ifdef CONFIG_PRINTING
LIBSEL4_INLINE_FUNC void
seL4_DebugPutChar(char c)
{
    seL4_Word unused0 = 0;
    seL4_Word unused1 = 0;
    seL4_Word unused2 = 0;
    seL4_Word unused3 = 0;
    seL4_Word unused4 = 0;
    seL4_Word unused5 = 0;

    x64_sys_send_recv(seL4_SysDebugPutChar, c, &unused0, 0, &unused1, &unused2, &unused3, &unused4, &unused5);
}

LIBSEL4_INLINE_FUNC void
seL4_DebugDumpScheduler(void)
{
    seL4_Word unused0 = 0;
    seL4_Word unused1 = 0;
    seL4_Word unused2 = 0;
    seL4_Word unused3 = 0;
    seL4_Word unused4 = 0;
    seL4_Word unused5 = 0;

    x64_sys_send_recv(seL4_SysDebugDumpScheduler, 0, &unused0, 0, &unused1, &unused2, &unused3, &unused4, &unused5);
}
#endif

#ifdef CONFIG_DEBUG_BUILD
LIBSEL4_INLINE_FUNC void
seL4_DebugHalt(void)
{
    x64_sys_null(seL4_SysDebugHalt);
    asm volatile("" :::"memory");
}
#endif

#if defined(CONFIG_KERNEL_X86_DANGEROUS_MSR)
LIBSEL4_INLINE_FUNC void
seL4_X86DangerousWRMSR(seL4_Uint32 msr, seL4_Uint64 value)
{
    x64_sys_send(seL4_SysX86DangerousWRMSR, msr, 0, value, 0, 0, 0);
}
LIBSEL4_INLINE_FUNC seL4_Uint64
seL4_X86DangerousRDMSR(seL4_Uint32 msr)
{
    seL4_Word unused0 = 0;
    seL4_Word unused1 = 0;
    seL4_Word unused2 = 0;
    seL4_Word unused3 = 0;
    seL4_Word unused4 = 0;
    seL4_Word val;
    x64_sys_recv(seL4_SysX86DangerousRDMSR, msr, &unused0, &unused1, &val, &unused2, &unused3, &unused4);
    return val;
}
#endif

#if defined(CONFIG_DEBUG_BUILD)
LIBSEL4_INLINE_FUNC void
seL4_DebugSnapshot(void)
{
    x64_sys_null(seL4_SysDebugSnapshot);
    asm volatile("" :::"memory");
}
#endif

#ifdef CONFIG_DEBUG_BUILD
LIBSEL4_INLINE_FUNC seL4_Uint32
seL4_DebugCapIdentify(seL4_CPtr cap)
{
    seL4_Word unused0 = 0;
    seL4_Word unused1 = 0;
    seL4_Word unused2 = 0;
    seL4_Word unused3 = 0;
    seL4_Word unused4 = 0;

    x64_sys_send_recv(seL4_SysDebugCapIdentify, cap, &cap, 0, &unused0, &unused1, &unused2, &unused3, &unused4);
    return (seL4_Uint32)cap;
}
#endif

#ifdef CONFIG_DEBUG_BUILD
char *strcpy(char *, const char *);
LIBSEL4_INLINE_FUNC void
seL4_DebugNameThread(seL4_CPtr tcb, const char *name)
{

    strcpy((char*)seL4_GetIPCBuffer()->msg, name);

    seL4_Word unused0 = 0;
    seL4_Word unused1 = 0;
    seL4_Word unused2 = 0;
    seL4_Word unused3 = 0;
    seL4_Word unused4 = 0;
    seL4_Word unused5 = 0;

    x64_sys_send_recv(seL4_SysDebugNameThread, tcb, &unused0, 0, &unused1, &unused2, &unused3, &unused4, &unused5);
}
#endif

#if defined(CONFIG_DANGEROUS_CODE_INJECTION)
LIBSEL4_INLINE_FUNC void
seL4_DebugRun(void (*userfn) (void *), void* userarg)
{
    x64_sys_send_null(seL4_SysDebugRun, (seL4_Word)userfn, (seL4_Word)userarg);
    asm volatile("" ::: "memory");
}
#endif

#if CONFIG_ENABLE_BENCHMARKS
LIBSEL4_INLINE_FUNC seL4_Error
seL4_BenchmarkResetLog(void)
{
    seL4_Word unused0 = 0;
    seL4_Word unused1 = 0;
    seL4_Word unused2 = 0;
    seL4_Word unused3 = 0;
    seL4_Word unused4 = 0;

    seL4_Word ret;

    x64_sys_send_recv(seL4_SysBenchmarkResetLog, 0, &ret, 0, &unused0, &unused1, &unused2, &unused3, &unused4);

    return (seL4_Error)ret;
}

LIBSEL4_INLINE_FUNC seL4_Word
seL4_BenchmarkFinalizeLog(void)
{
    seL4_Word unused0 = 0;
    seL4_Word unused1 = 0;
    seL4_Word unused2 = 0;
    seL4_Word unused3 = 0;
    seL4_Word unused4 = 0;
    seL4_Word index_ret;
    x64_sys_send_recv(seL4_SysBenchmarkFinalizeLog, 0, &index_ret, 0, &unused0, &unused1, &unused2, &unused3, &unused4);

    return (seL4_Word)index_ret;
}

LIBSEL4_INLINE_FUNC seL4_Error
seL4_BenchmarkSetLogBuffer(seL4_Word frame_cptr)
{
    seL4_Word unused0 = 0;
    seL4_Word unused1 = 0;
    seL4_Word unused2 = 0;
    seL4_Word unused3 = 0;
    seL4_Word unused4 = 0;

    x64_sys_send_recv(seL4_SysBenchmarkSetLogBuffer, frame_cptr, &frame_cptr, 0, &unused0, &unused1, &unused2, &unused3, &unused4);

    return (seL4_Error) frame_cptr;
}

LIBSEL4_INLINE_FUNC void
seL4_BenchmarkNullSyscall(void)
{
    x64_sys_null(seL4_SysBenchmarkNullSyscall);
    asm volatile("" ::: "memory");
}

LIBSEL4_INLINE_FUNC void
seL4_BenchmarkFlushCaches(void)
{
    x64_sys_null(seL4_SysBenchmarkFlushCaches);
    asm volatile("" ::: "memory");
}

#ifdef CONFIG_BENCHMARK_TRACK_UTILISATION
LIBSEL4_INLINE_FUNC void
seL4_BenchmarkGetThreadUtilisation(seL4_Word tcb_cptr)
{
    seL4_Word unused0 = 0;
    seL4_Word unused1 = 0;
    seL4_Word unused2 = 0;
    seL4_Word unused3 = 0;
    seL4_Word unused4 = 0;
    seL4_Word unused5 = 0;

    x64_sys_send_recv(seL4_SysBenchmarkGetThreadUtilisation, tcb_cptr, &unused0, 0, &unused1, &unused2, &unused3, &unused4, &unused5);
}

LIBSEL4_INLINE_FUNC void
seL4_BenchmarkResetThreadUtilisation(seL4_Word tcb_cptr)
{
    seL4_Word unused0 = 0;
    seL4_Word unused1 = 0;
    seL4_Word unused2 = 0;
    seL4_Word unused3 = 0;
    seL4_Word unused4 = 0;
    seL4_Word unused5 = 0;

    x64_sys_send_recv(seL4_SysBenchmarkResetThreadUtilisation, tcb_cptr, &unused0, 0, &unused1, &unused2, &unused3, &unused4, &unused5);
}
#endif /* CONFIG_BENCHMARK_TRACK_UTILISATION */
#endif /* CONFIG_ENABLE_BENCHMARKS */

#endif /* __LIBSEL4_SEL4_SEL4_ARCH_SYSCALLS_H_ */
