/**
 * nn SDK dispatcher stubs — PLT-style trampolines that call through GOT entries
 * into the NintendoSDK runtime (nn_os, nn_socket, nn_ssl, nn_result modules).
 *
 * Each stub is 16 bytes:  adrp x16, PTR / ldr x17, [x16, :lo12:PTR]
 *                         add  x16, x16, :lo12:PTR / br x17
 *
 * Addresses 0x71039bfb60 – 0x71039c00c0
 */

#include "types.h"

// ---------------------------------------------------------------------------
// GOT entry declarations (function pointer table in original binary)
// ---------------------------------------------------------------------------
extern "C" {
    extern void* PTR_nnsocketGetPeerName;
    extern void* PTR_nnsocketGetLastErrno;
    extern void* PTR_nnsocketGetSockName;
    extern void* PTR_nnsocketInetNtohs;
    extern void* PTR_nnsocketClose;
    extern void* PTR_nnsocketGetSockOpt;
    extern void* PTR_nnsocketSetLastErrno;
    extern void* PTR_nnsocketSetSockOpt;
    extern void* PTR_nnsocketSocket;
    extern void* PTR_nnsocketInetHtons;
    extern void* PTR_nnsocketBind;
    extern void* PTR_nnsocketConnect;
    extern void* PTR_nnsocketResolverSetOption;
    extern void* PTR_nnosSleepThread;
    extern void* PTR_nnosLockMutex;
    extern void* PTR_nnosUnlockMutex;
    extern void* PTR_nnosFinalizeMutex;
    extern void* PTR_nnosInitializeMutex;
    extern void* PTR_nnsocketResolverGetOption;
    extern void* PTR_nnsocketFcntl;
    extern void* PTR_nnsocketPoll;
    extern void* PTR_nnsocketSend;
    extern void* PTR_nnsocketRecv;
    extern void* PTR_nnsslInitialize;
    extern void* PTR_nnResultIsFailure;
    extern void* PTR_nnResultGetModule;
    extern void* PTR_nnResultGetDescription;
    extern void* PTR_nnsslFinalize_71039bfe40;
    extern void* PTR_nnsslConnectionDoHandshakeWithCertBuffer;
    extern void* PTR_nnsslContextGetContextId;
    extern void* PTR_nnsslConnectionCreate;
    extern void* PTR_nnsslConnectionSetOption;
    extern void* PTR_nnsslConnectionSetSocketDescriptor;
    extern void* PTR_nnsslConnectionSetHostName;
    extern void* PTR_nnsslConnectionSetVerifyOption;
    extern void* PTR_nnsslConnectionSetSessionCacheMode;
    extern void* PTR_nnsslContextDestroy;
    extern void* PTR_nnsslConnectionGetVerifyCertError;
    extern void* PTR_nnsslConnectionGetConnectionId;
    extern void* PTR_nnsslConnectionDestroy;
    extern void* PTR_nnsslConnectionSetIoMode;
    extern void* PTR_nnsslConnectionPending;
    extern void* PTR_nnResultIsSuccess;
    extern void* PTR_nndetailDiagAbortFormatImpl;
    extern void* PTR_nnosGetSystemTick;
    extern void* PTR_nnosGetSystemTickFrequency;
    extern void* PTR_nnosConvertTickToNanoSeconds;
    extern void* PTR_nnsocketGetHostByNameWithOptions_stub;
    extern void* PTR_nnosGetCurrentThread;
    extern void* PTR_nnosGetThreadPriority;
    extern void* PTR_nnosCreateThread;
    extern void* PTR_nnosDestroyThread;
    extern void* PTR_nnosGetThreadCoreMask;
    extern void* PTR_nnosSetThreadCoreMask;
    extern void* PTR_nnosSetThreadNamePointer;
    extern void* PTR_nnosInitializeEvent;
    extern void* PTR_nnosStartThread;
    extern void* PTR_nnosWaitEvent;
    extern void* PTR_nnosFinalizeEvent;
    extern void* PTR_nnosSignalEvent;
    extern void* PTR_nnosWaitThread;
    extern void* PTR_nnsslFinalize_265a0;
}

// ---------------------------------------------------------------------------
// nn socket stubs
// ---------------------------------------------------------------------------

// 71039bfb60
__attribute__((naked)) extern "C" void nnsocketGetPeerName() {
    asm("adrp x16, PTR_nnsocketGetPeerName\n"
        "ldr x17, [x16, :lo12:PTR_nnsocketGetPeerName]\n"
        "add x16, x16, :lo12:PTR_nnsocketGetPeerName\n"
        "br x17\n");
}

// 71039bfb70
__attribute__((naked)) extern "C" void nnsocketGetLastErrno() {
    asm("adrp x16, PTR_nnsocketGetLastErrno\n"
        "ldr x17, [x16, :lo12:PTR_nnsocketGetLastErrno]\n"
        "add x16, x16, :lo12:PTR_nnsocketGetLastErrno\n"
        "br x17\n");
}

// 71039bfb80
__attribute__((naked)) extern "C" void nnsocketGetSockName() {
    asm("adrp x16, PTR_nnsocketGetSockName\n"
        "ldr x17, [x16, :lo12:PTR_nnsocketGetSockName]\n"
        "add x16, x16, :lo12:PTR_nnsocketGetSockName\n"
        "br x17\n");
}

// 71039bfb90
__attribute__((naked)) extern "C" void nnsocketInetNtohs() {
    asm("adrp x16, PTR_nnsocketInetNtohs\n"
        "ldr x17, [x16, :lo12:PTR_nnsocketInetNtohs]\n"
        "add x16, x16, :lo12:PTR_nnsocketInetNtohs\n"
        "br x17\n");
}

// 71039bfbb0
__attribute__((naked)) extern "C" void nnsocketClose() {
    asm("adrp x16, PTR_nnsocketClose\n"
        "ldr x17, [x16, :lo12:PTR_nnsocketClose]\n"
        "add x16, x16, :lo12:PTR_nnsocketClose\n"
        "br x17\n");
}

// 71039bfbc0
__attribute__((naked)) extern "C" void nnsocketGetSockOpt() {
    asm("adrp x16, PTR_nnsocketGetSockOpt\n"
        "ldr x17, [x16, :lo12:PTR_nnsocketGetSockOpt]\n"
        "add x16, x16, :lo12:PTR_nnsocketGetSockOpt\n"
        "br x17\n");
}

// 71039bfbd0
__attribute__((naked)) extern "C" void nnsocketSetLastErrno() {
    asm("adrp x16, PTR_nnsocketSetLastErrno\n"
        "ldr x17, [x16, :lo12:PTR_nnsocketSetLastErrno]\n"
        "add x16, x16, :lo12:PTR_nnsocketSetLastErrno\n"
        "br x17\n");
}

// 71039bfbe0
__attribute__((naked)) extern "C" void nnsocketSetSockOpt() {
    asm("adrp x16, PTR_nnsocketSetSockOpt\n"
        "ldr x17, [x16, :lo12:PTR_nnsocketSetSockOpt]\n"
        "add x16, x16, :lo12:PTR_nnsocketSetSockOpt\n"
        "br x17\n");
}

// 71039bfbf0
__attribute__((naked)) extern "C" void nnsocketSocket() {
    asm("adrp x16, PTR_nnsocketSocket\n"
        "ldr x17, [x16, :lo12:PTR_nnsocketSocket]\n"
        "add x16, x16, :lo12:PTR_nnsocketSocket\n"
        "br x17\n");
}

// 71039bfc00
__attribute__((naked)) extern "C" void nnsocketInetHtons() {
    asm("adrp x16, PTR_nnsocketInetHtons\n"
        "ldr x17, [x16, :lo12:PTR_nnsocketInetHtons]\n"
        "add x16, x16, :lo12:PTR_nnsocketInetHtons\n"
        "br x17\n");
}

// 71039bfc10
__attribute__((naked)) extern "C" void nnsocketBind() {
    asm("adrp x16, PTR_nnsocketBind\n"
        "ldr x17, [x16, :lo12:PTR_nnsocketBind]\n"
        "add x16, x16, :lo12:PTR_nnsocketBind\n"
        "br x17\n");
}

// 71039bfc20
__attribute__((naked)) extern "C" void nnsocketConnect() {
    asm("adrp x16, PTR_nnsocketConnect\n"
        "ldr x17, [x16, :lo12:PTR_nnsocketConnect]\n"
        "add x16, x16, :lo12:PTR_nnsocketConnect\n"
        "br x17\n");
}

// 71039bfc30
__attribute__((naked)) extern "C" void nnsocketResolverSetOption() {
    asm("adrp x16, PTR_nnsocketResolverSetOption\n"
        "ldr x17, [x16, :lo12:PTR_nnsocketResolverSetOption]\n"
        "add x16, x16, :lo12:PTR_nnsocketResolverSetOption\n"
        "br x17\n");
}

// ---------------------------------------------------------------------------
// nn os stubs
// ---------------------------------------------------------------------------

// 71039bfc40
__attribute__((naked)) extern "C" void nnosSleepThread() {
    asm("adrp x16, PTR_nnosSleepThread\n"
        "ldr x17, [x16, :lo12:PTR_nnosSleepThread]\n"
        "add x16, x16, :lo12:PTR_nnosSleepThread\n"
        "br x17\n");
}

// 71039bfc50
__attribute__((naked)) extern "C" void nnosLockMutex() {
    asm("adrp x16, PTR_nnosLockMutex\n"
        "ldr x17, [x16, :lo12:PTR_nnosLockMutex]\n"
        "add x16, x16, :lo12:PTR_nnosLockMutex\n"
        "br x17\n");
}

// 71039bfc60
__attribute__((naked)) extern "C" void nnosUnlockMutex() {
    asm("adrp x16, PTR_nnosUnlockMutex\n"
        "ldr x17, [x16, :lo12:PTR_nnosUnlockMutex]\n"
        "add x16, x16, :lo12:PTR_nnosUnlockMutex\n"
        "br x17\n");
}

// 71039bfc70
__attribute__((naked)) extern "C" void nnosFinalizeMutex() {
    asm("adrp x16, PTR_nnosFinalizeMutex\n"
        "ldr x17, [x16, :lo12:PTR_nnosFinalizeMutex]\n"
        "add x16, x16, :lo12:PTR_nnosFinalizeMutex\n"
        "br x17\n");
}

// 71039bfc80
__attribute__((naked)) extern "C" void nnosInitializeMutex() {
    asm("adrp x16, PTR_nnosInitializeMutex\n"
        "ldr x17, [x16, :lo12:PTR_nnosInitializeMutex]\n"
        "add x16, x16, :lo12:PTR_nnosInitializeMutex\n"
        "br x17\n");
}

// 71039bfc90
__attribute__((naked)) extern "C" void nnsocketResolverGetOption() {
    asm("adrp x16, PTR_nnsocketResolverGetOption\n"
        "ldr x17, [x16, :lo12:PTR_nnsocketResolverGetOption]\n"
        "add x16, x16, :lo12:PTR_nnsocketResolverGetOption\n"
        "br x17\n");
}

// 71039bfd30
__attribute__((naked)) extern "C" void nnsocketFcntl() {
    asm("adrp x16, PTR_nnsocketFcntl\n"
        "ldr x17, [x16, :lo12:PTR_nnsocketFcntl]\n"
        "add x16, x16, :lo12:PTR_nnsocketFcntl\n"
        "br x17\n");
}

// 71039bfd60
__attribute__((naked)) extern "C" void nnsocketPoll() {
    asm("adrp x16, PTR_nnsocketPoll\n"
        "ldr x17, [x16, :lo12:PTR_nnsocketPoll]\n"
        "add x16, x16, :lo12:PTR_nnsocketPoll\n"
        "br x17\n");
}

// 71039bfd70
__attribute__((naked)) extern "C" void nnsocketSend() {
    asm("adrp x16, PTR_nnsocketSend\n"
        "ldr x17, [x16, :lo12:PTR_nnsocketSend]\n"
        "add x16, x16, :lo12:PTR_nnsocketSend\n"
        "br x17\n");
}

// 71039bfd80
__attribute__((naked)) extern "C" void nnsocketRecv() {
    asm("adrp x16, PTR_nnsocketRecv\n"
        "ldr x17, [x16, :lo12:PTR_nnsocketRecv]\n"
        "add x16, x16, :lo12:PTR_nnsocketRecv\n"
        "br x17\n");
}

// ---------------------------------------------------------------------------
// nn ssl stubs
// ---------------------------------------------------------------------------

// 71039bfe00
__attribute__((naked)) extern "C" void nnsslInitialize() {
    asm("adrp x16, PTR_nnsslInitialize\n"
        "ldr x17, [x16, :lo12:PTR_nnsslInitialize]\n"
        "add x16, x16, :lo12:PTR_nnsslInitialize\n"
        "br x17\n");
}

// 71039bfe40
__attribute__((naked)) extern "C" void nnsslFinalize_71039bfe40() {
    asm("adrp x16, PTR_nnsslFinalize_71039bfe40\n"
        "ldr x17, [x16, :lo12:PTR_nnsslFinalize_71039bfe40]\n"
        "add x16, x16, :lo12:PTR_nnsslFinalize_71039bfe40\n"
        "br x17\n");
}

// 71039bfe50
__attribute__((naked)) extern "C" void nnsslConnectionDoHandshakeWithCertBuffer() {
    asm("adrp x16, PTR_nnsslConnectionDoHandshakeWithCertBuffer\n"
        "ldr x17, [x16, :lo12:PTR_nnsslConnectionDoHandshakeWithCertBuffer]\n"
        "add x16, x16, :lo12:PTR_nnsslConnectionDoHandshakeWithCertBuffer\n"
        "br x17\n");
}

// 71039bfe60
__attribute__((naked)) extern "C" void nnsslContextGetContextId() {
    asm("adrp x16, PTR_nnsslContextGetContextId\n"
        "ldr x17, [x16, :lo12:PTR_nnsslContextGetContextId]\n"
        "add x16, x16, :lo12:PTR_nnsslContextGetContextId\n"
        "br x17\n");
}

// 71039bfe70
__attribute__((naked)) extern "C" void nnsslConnectionCreate() {
    asm("adrp x16, PTR_nnsslConnectionCreate\n"
        "ldr x17, [x16, :lo12:PTR_nnsslConnectionCreate]\n"
        "add x16, x16, :lo12:PTR_nnsslConnectionCreate\n"
        "br x17\n");
}

// 71039bfe80
__attribute__((naked)) extern "C" void nnsslConnectionSetOption() {
    asm("adrp x16, PTR_nnsslConnectionSetOption\n"
        "ldr x17, [x16, :lo12:PTR_nnsslConnectionSetOption]\n"
        "add x16, x16, :lo12:PTR_nnsslConnectionSetOption\n"
        "br x17\n");
}

// 71039bfe90
__attribute__((naked)) extern "C" void nnsslConnectionSetSocketDescriptor() {
    asm("adrp x16, PTR_nnsslConnectionSetSocketDescriptor\n"
        "ldr x17, [x16, :lo12:PTR_nnsslConnectionSetSocketDescriptor]\n"
        "add x16, x16, :lo12:PTR_nnsslConnectionSetSocketDescriptor\n"
        "br x17\n");
}

// 71039bfea0
__attribute__((naked)) extern "C" void nnsslConnectionSetHostName() {
    asm("adrp x16, PTR_nnsslConnectionSetHostName\n"
        "ldr x17, [x16, :lo12:PTR_nnsslConnectionSetHostName]\n"
        "add x16, x16, :lo12:PTR_nnsslConnectionSetHostName\n"
        "br x17\n");
}

// 71039bfeb0
__attribute__((naked)) extern "C" void nnsslConnectionSetVerifyOption() {
    asm("adrp x16, PTR_nnsslConnectionSetVerifyOption\n"
        "ldr x17, [x16, :lo12:PTR_nnsslConnectionSetVerifyOption]\n"
        "add x16, x16, :lo12:PTR_nnsslConnectionSetVerifyOption\n"
        "br x17\n");
}

// 71039bfec0
__attribute__((naked)) extern "C" void nnsslConnectionSetSessionCacheMode() {
    asm("adrp x16, PTR_nnsslConnectionSetSessionCacheMode\n"
        "ldr x17, [x16, :lo12:PTR_nnsslConnectionSetSessionCacheMode]\n"
        "add x16, x16, :lo12:PTR_nnsslConnectionSetSessionCacheMode\n"
        "br x17\n");
}

// 71039bfed0
__attribute__((naked)) extern "C" void nnsslContextDestroy() {
    asm("adrp x16, PTR_nnsslContextDestroy\n"
        "ldr x17, [x16, :lo12:PTR_nnsslContextDestroy]\n"
        "add x16, x16, :lo12:PTR_nnsslContextDestroy\n"
        "br x17\n");
}

// 71039bfee0
__attribute__((naked)) extern "C" void nnsslConnectionGetVerifyCertError() {
    asm("adrp x16, PTR_nnsslConnectionGetVerifyCertError\n"
        "ldr x17, [x16, :lo12:PTR_nnsslConnectionGetVerifyCertError]\n"
        "add x16, x16, :lo12:PTR_nnsslConnectionGetVerifyCertError\n"
        "br x17\n");
}

// 71039bfef0
__attribute__((naked)) extern "C" void nnsslConnectionGetConnectionId() {
    asm("adrp x16, PTR_nnsslConnectionGetConnectionId\n"
        "ldr x17, [x16, :lo12:PTR_nnsslConnectionGetConnectionId]\n"
        "add x16, x16, :lo12:PTR_nnsslConnectionGetConnectionId\n"
        "br x17\n");
}

// 71039bff00
__attribute__((naked)) extern "C" void nnsslConnectionDestroy() {
    asm("adrp x16, PTR_nnsslConnectionDestroy\n"
        "ldr x17, [x16, :lo12:PTR_nnsslConnectionDestroy]\n"
        "add x16, x16, :lo12:PTR_nnsslConnectionDestroy\n"
        "br x17\n");
}

// 71039bff10
__attribute__((naked)) extern "C" void nnsslConnectionSetIoMode() {
    asm("adrp x16, PTR_nnsslConnectionSetIoMode\n"
        "ldr x17, [x16, :lo12:PTR_nnsslConnectionSetIoMode]\n"
        "add x16, x16, :lo12:PTR_nnsslConnectionSetIoMode\n"
        "br x17\n");
}

// 71039bff30
__attribute__((naked)) extern "C" void nnsslConnectionPending() {
    asm("adrp x16, PTR_nnsslConnectionPending\n"
        "ldr x17, [x16, :lo12:PTR_nnsslConnectionPending]\n"
        "add x16, x16, :lo12:PTR_nnsslConnectionPending\n"
        "br x17\n");
}

// ---------------------------------------------------------------------------
// nn result stubs
// ---------------------------------------------------------------------------

// 71039bfe10
__attribute__((naked)) extern "C" void nnResultIsFailure() {
    asm("adrp x16, PTR_nnResultIsFailure\n"
        "ldr x17, [x16, :lo12:PTR_nnResultIsFailure]\n"
        "add x16, x16, :lo12:PTR_nnResultIsFailure\n"
        "br x17\n");
}

// 71039bfe20
__attribute__((naked)) extern "C" void nnResultGetModule() {
    asm("adrp x16, PTR_nnResultGetModule\n"
        "ldr x17, [x16, :lo12:PTR_nnResultGetModule]\n"
        "add x16, x16, :lo12:PTR_nnResultGetModule\n"
        "br x17\n");
}

// 71039bfe30
__attribute__((naked)) extern "C" void nnResultGetDescription() {
    asm("adrp x16, PTR_nnResultGetDescription\n"
        "ldr x17, [x16, :lo12:PTR_nnResultGetDescription]\n"
        "add x16, x16, :lo12:PTR_nnResultGetDescription\n"
        "br x17\n");
}

// 71039bff40
__attribute__((naked)) extern "C" void nnResultIsSuccess() {
    asm("adrp x16, PTR_nnResultIsSuccess\n"
        "ldr x17, [x16, :lo12:PTR_nnResultIsSuccess]\n"
        "add x16, x16, :lo12:PTR_nnResultIsSuccess\n"
        "br x17\n");
}

// 71039bff70
__attribute__((naked)) extern "C" void nndetailDiagAbortFormatImpl() {
    asm("adrp x16, PTR_nndetailDiagAbortFormatImpl\n"
        "ldr x17, [x16, :lo12:PTR_nndetailDiagAbortFormatImpl]\n"
        "add x16, x16, :lo12:PTR_nndetailDiagAbortFormatImpl\n"
        "br x17\n");
}

// ---------------------------------------------------------------------------
// nn os system tick / thread stubs
// ---------------------------------------------------------------------------

// 71039bffb0
__attribute__((naked)) extern "C" void nnosGetSystemTick() {
    asm("adrp x16, PTR_nnosGetSystemTick\n"
        "ldr x17, [x16, :lo12:PTR_nnosGetSystemTick]\n"
        "add x16, x16, :lo12:PTR_nnosGetSystemTick\n"
        "br x17\n");
}

// 71039bffc0
__attribute__((naked)) extern "C" void nnosGetSystemTickFrequency() {
    asm("adrp x16, PTR_nnosGetSystemTickFrequency\n"
        "ldr x17, [x16, :lo12:PTR_nnosGetSystemTickFrequency]\n"
        "add x16, x16, :lo12:PTR_nnosGetSystemTickFrequency\n"
        "br x17\n");
}

// 71039bffd0
__attribute__((naked)) extern "C" void nnosConvertTickToNanoSeconds() {
    asm("adrp x16, PTR_nnosConvertTickToNanoSeconds\n"
        "ldr x17, [x16, :lo12:PTR_nnosConvertTickToNanoSeconds]\n"
        "add x16, x16, :lo12:PTR_nnosConvertTickToNanoSeconds\n"
        "br x17\n");
}

// 71039bffe0
__attribute__((naked)) extern "C" void nnsocketGetHostByNameWithOptions_71039bffe0() {
    asm("adrp x16, PTR_nnsocketGetHostByNameWithOptions_stub\n"
        "ldr x17, [x16, :lo12:PTR_nnsocketGetHostByNameWithOptions_stub]\n"
        "add x16, x16, :lo12:PTR_nnsocketGetHostByNameWithOptions_stub\n"
        "br x17\n");
}

// 71039bfff0
__attribute__((naked)) extern "C" void nnosGetCurrentThread() {
    asm("adrp x16, PTR_nnosGetCurrentThread\n"
        "ldr x17, [x16, :lo12:PTR_nnosGetCurrentThread]\n"
        "add x16, x16, :lo12:PTR_nnosGetCurrentThread\n"
        "br x17\n");
}

// 71039c0000
__attribute__((naked)) extern "C" void nnosGetThreadPriority() {
    asm("adrp x16, PTR_nnosGetThreadPriority\n"
        "ldr x17, [x16, :lo12:PTR_nnosGetThreadPriority]\n"
        "add x16, x16, :lo12:PTR_nnosGetThreadPriority\n"
        "br x17\n");
}

// 71039c0010
__attribute__((naked)) extern "C" void nnosCreateThread() {
    asm("adrp x16, PTR_nnosCreateThread\n"
        "ldr x17, [x16, :lo12:PTR_nnosCreateThread]\n"
        "add x16, x16, :lo12:PTR_nnosCreateThread\n"
        "br x17\n");
}

// 71039c0020
__attribute__((naked)) extern "C" void nnosDestroyThread() {
    asm("adrp x16, PTR_nnosDestroyThread\n"
        "ldr x17, [x16, :lo12:PTR_nnosDestroyThread]\n"
        "add x16, x16, :lo12:PTR_nnosDestroyThread\n"
        "br x17\n");
}

// 71039c0030
__attribute__((naked)) extern "C" void nnosGetThreadCoreMask() {
    asm("adrp x16, PTR_nnosGetThreadCoreMask\n"
        "ldr x17, [x16, :lo12:PTR_nnosGetThreadCoreMask]\n"
        "add x16, x16, :lo12:PTR_nnosGetThreadCoreMask\n"
        "br x17\n");
}

// 71039c0040
__attribute__((naked)) extern "C" void nnosSetThreadCoreMask() {
    asm("adrp x16, PTR_nnosSetThreadCoreMask\n"
        "ldr x17, [x16, :lo12:PTR_nnosSetThreadCoreMask]\n"
        "add x16, x16, :lo12:PTR_nnosSetThreadCoreMask\n"
        "br x17\n");
}

// 71039c0050
__attribute__((naked)) extern "C" void nnosSetThreadNamePointer() {
    asm("adrp x16, PTR_nnosSetThreadNamePointer\n"
        "ldr x17, [x16, :lo12:PTR_nnosSetThreadNamePointer]\n"
        "add x16, x16, :lo12:PTR_nnosSetThreadNamePointer\n"
        "br x17\n");
}

// 71039c0060
__attribute__((naked)) extern "C" void nnosInitializeEvent() {
    asm("adrp x16, PTR_nnosInitializeEvent\n"
        "ldr x17, [x16, :lo12:PTR_nnosInitializeEvent]\n"
        "add x16, x16, :lo12:PTR_nnosInitializeEvent\n"
        "br x17\n");
}

// 71039c0070
__attribute__((naked)) extern "C" void nnosStartThread() {
    asm("adrp x16, PTR_nnosStartThread\n"
        "ldr x17, [x16, :lo12:PTR_nnosStartThread]\n"
        "add x16, x16, :lo12:PTR_nnosStartThread\n"
        "br x17\n");
}

// 71039c0080
__attribute__((naked)) extern "C" void nnosWaitEvent() {
    asm("adrp x16, PTR_nnosWaitEvent\n"
        "ldr x17, [x16, :lo12:PTR_nnosWaitEvent]\n"
        "add x16, x16, :lo12:PTR_nnosWaitEvent\n"
        "br x17\n");
}

// 71039c0090
__attribute__((naked)) extern "C" void nnosFinalizeEvent() {
    asm("adrp x16, PTR_nnosFinalizeEvent\n"
        "ldr x17, [x16, :lo12:PTR_nnosFinalizeEvent]\n"
        "add x16, x16, :lo12:PTR_nnosFinalizeEvent\n"
        "br x17\n");
}

// 71039c00a0
__attribute__((naked)) extern "C" void nnosSignalEvent() {
    asm("adrp x16, PTR_nnosSignalEvent\n"
        "ldr x17, [x16, :lo12:PTR_nnosSignalEvent]\n"
        "add x16, x16, :lo12:PTR_nnosSignalEvent\n"
        "br x17\n");
}

// 71039c00b0
__attribute__((naked)) extern "C" void nnosWaitThread() {
    asm("adrp x16, PTR_nnosWaitThread\n"
        "ldr x17, [x16, :lo12:PTR_nnosWaitThread]\n"
        "add x16, x16, :lo12:PTR_nnosWaitThread\n"
        "br x17\n");
}

// ---------------------------------------------------------------------------
// Standalone nnsslFinalize stub (different address from table stub)
// ---------------------------------------------------------------------------

// 71000265a0
__attribute__((naked)) extern "C" void nnsslFinalize() {
    asm("adrp x16, PTR_nnsslFinalize_265a0\n"
        "ldr x17, [x16, :lo12:PTR_nnsslFinalize_265a0]\n"
        "add x16, x16, :lo12:PTR_nnsslFinalize_265a0\n"
        "br x17\n");
}
