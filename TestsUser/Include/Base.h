/** @file
  Copyright (C) 2016 - 2019, vit9696. All rights reserved.

  All rights reserved.

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
**/


#ifndef UEFI_BASE_H
#define UEFI_BASE_H

//
// Includes
//
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <cpuid.h>

//
// Types and limits
//

#define MAX_UINT8     UINT8_MAX
#define MAX_UINT16    UINT16_MAX
#define MAX_UINT32    UINT32_MAX
#define MAX_UINT64    UINT64_MAX
#define MAX_BIT       0x8000000000000000
#define EFI_PAGE_SIZE  0x1000
#define EFI_PAGE_MASK  0xFFF
#define EFI_PAGE_SHIFT 12

#define MDE_CPU_X64
#define VOID void
#define CONST const
#define STATIC static
typedef char CHAR8;
typedef short CHAR16;
typedef signed char INT8;
typedef unsigned char UINT8;
typedef ssize_t INTN;
typedef size_t UINTN;
typedef bool BOOLEAN;
typedef int32_t INT32;
typedef uint32_t UINT32;
typedef int64_t INT64;
typedef uint64_t UINT64;
typedef int16_t INT16;
typedef uint16_t UINT16;
typedef size_t EFI_STATUS;
typedef UINTN RETURN_STATUS;
typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64 EFI_VIRTUAL_ADDRESS;
typedef VOID *EFI_HANDLE;
typedef VOID *EFI_EVENT;
typedef UINTN *BASE_LIST;

typedef struct {
  UINT32  Data1;
  UINT16  Data2;
  UINT16  Data3;
  UINT8   Data4[8];
} GUID;

typedef enum {
  AllocateAnyPages,
  AllocateMaxAddress,
  AllocateAddress,
  MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef enum {
  EfiReservedMemoryType,
  EfiLoaderCode,
  EfiLoaderData,
  EfiBootServicesCode,
  EfiBootServicesData,
  EfiRuntimeServicesCode,
  EfiRuntimeServicesData,
  EfiConventionalMemory,
  EfiUnusableMemory,
  EfiACPIReclaimMemory,
  EfiACPIMemoryNVS,
  EfiMemoryMappedIO,
  EfiMemoryMappedIOPortSpace,
  EfiPalCode,
  EfiPersistentMemory,
  EfiMaxMemoryType
} EFI_MEMORY_TYPE;

typedef GUID EFI_GUID;
typedef struct EFI_SYSTEM_TABLE_ EFI_SYSTEM_TABLE;
typedef struct EFI_BOOT_SERVICES_ EFI_BOOT_SERVICES;
typedef struct EFI_RUNTIME_SERVICES_ EFI_RUNTIME_SERVICES;
typedef VOID (*EFI_EVENT_NOTIFY)(EFI_EVENT Event, VOID *Context);

#define IN
#define OUT
#define OPTIONAL
#define EFIAPI
#define TRUE true
#define FALSE false
#define VA_LIST va_list
#define VA_ARG va_arg
#define VA_START va_start
#define VA_END va_end
#define VERIFY_SIZE_OF(TYPE, Size) extern unsigned char _VerifySizeof##TYPE[(sizeof(TYPE) == (Size)) / (sizeof(TYPE) == (Size))]
#define EFI_D_ERROR stderr
#define EFI_D_VERBOSE stdout
#define DEBUG_ERROR stderr
#define DEBUG_INFO stdout
#define DEBUG_VERBOSE stdout
#define DEBUG_WARN stderr
#define PACKED
#define GLOBAL_REMOVE_IF_UNREFERENCED

//
// Return codes
//
#define ENCODE_ERROR(a)              ((RETURN_STATUS)(MAX_BIT | (a)))

#define ENCODE_WARNING(a)            ((RETURN_STATUS)(a))
#define RETURN_ERROR(a)              (((INTN)(RETURN_STATUS)(a)) < 0)

#define RETURN_SUCCESS               0
#define RETURN_LOAD_ERROR            ENCODE_ERROR (1)
#define RETURN_INVALID_PARAMETER     ENCODE_ERROR (2)
#define RETURN_UNSUPPORTED           ENCODE_ERROR (3)
#define RETURN_BAD_BUFFER_SIZE       ENCODE_ERROR (4)
#define RETURN_BUFFER_TOO_SMALL      ENCODE_ERROR (5)
#define RETURN_NOT_READY             ENCODE_ERROR (6)
#define RETURN_DEVICE_ERROR          ENCODE_ERROR (7)
#define RETURN_WRITE_PROTECTED       ENCODE_ERROR (8)
#define RETURN_OUT_OF_RESOURCES      ENCODE_ERROR (9)
#define RETURN_VOLUME_CORRUPTED      ENCODE_ERROR (10)
#define RETURN_VOLUME_FULL           ENCODE_ERROR (11)
#define RETURN_NO_MEDIA              ENCODE_ERROR (12)
#define RETURN_MEDIA_CHANGED         ENCODE_ERROR (13)
#define RETURN_NOT_FOUND             ENCODE_ERROR (14)
#define RETURN_ACCESS_DENIED         ENCODE_ERROR (15)
#define RETURN_NO_RESPONSE           ENCODE_ERROR (16)
#define RETURN_NO_MAPPING            ENCODE_ERROR (17)
#define RETURN_TIMEOUT               ENCODE_ERROR (18)
#define RETURN_NOT_STARTED           ENCODE_ERROR (19)
#define RETURN_ALREADY_STARTED       ENCODE_ERROR (20)
#define RETURN_ABORTED               ENCODE_ERROR (21)
#define RETURN_ICMP_ERROR            ENCODE_ERROR (22)
#define RETURN_TFTP_ERROR            ENCODE_ERROR (23)
#define RETURN_PROTOCOL_ERROR        ENCODE_ERROR (24)
#define RETURN_INCOMPATIBLE_VERSION  ENCODE_ERROR (25)
#define RETURN_SECURITY_VIOLATION    ENCODE_ERROR (26)
#define RETURN_CRC_ERROR             ENCODE_ERROR (27)
#define RETURN_END_OF_MEDIA          ENCODE_ERROR (28)
#define RETURN_END_OF_FILE           ENCODE_ERROR (31)

#define EFI_SUCCESS               RETURN_SUCCESS
#define EFI_LOAD_ERROR            RETURN_LOAD_ERROR
#define EFI_INVALID_PARAMETER     RETURN_INVALID_PARAMETER
#define EFI_UNSUPPORTED           RETURN_UNSUPPORTED
#define EFI_BAD_BUFFER_SIZE       RETURN_BAD_BUFFER_SIZE
#define EFI_BUFFER_TOO_SMALL      RETURN_BUFFER_TOO_SMALL
#define EFI_NOT_READY             RETURN_NOT_READY
#define EFI_DEVICE_ERROR          RETURN_DEVICE_ERROR
#define EFI_WRITE_PROTECTED       RETURN_WRITE_PROTECTED
#define EFI_OUT_OF_RESOURCES      RETURN_OUT_OF_RESOURCES
#define EFI_VOLUME_CORRUPTED      RETURN_VOLUME_CORRUPTED
#define EFI_VOLUME_FULL           RETURN_VOLUME_FULL
#define EFI_NO_MEDIA              RETURN_NO_MEDIA
#define EFI_MEDIA_CHANGED         RETURN_MEDIA_CHANGED
#define EFI_NOT_FOUND             RETURN_NOT_FOUND
#define EFI_ACCESS_DENIED         RETURN_ACCESS_DENIED
#define EFI_NO_RESPONSE           RETURN_NO_RESPONSE
#define EFI_NO_MAPPING            RETURN_NO_MAPPING
#define EFI_TIMEOUT               RETURN_TIMEOUT
#define EFI_NOT_STARTED           RETURN_NOT_STARTED
#define EFI_ALREADY_STARTED       RETURN_ALREADY_STARTED
#define EFI_ABORTED               RETURN_ABORTED
#define EFI_ICMP_ERROR            RETURN_ICMP_ERROR
#define EFI_TFTP_ERROR            RETURN_TFTP_ERROR
#define EFI_PROTOCOL_ERROR        RETURN_PROTOCOL_ERROR
#define EFI_INCOMPATIBLE_VERSION  RETURN_INCOMPATIBLE_VERSION
#define EFI_SECURITY_VIOLATION    RETURN_SECURITY_VIOLATION
#define EFI_CRC_ERROR             RETURN_CRC_ERROR
#define EFI_END_OF_MEDIA          RETURN_END_OF_MEDIA
#define EFI_END_OF_FILE           RETURN_END_OF_FILE

#define EFI_WARN_UNKNOWN_GLYPH    RETURN_WARN_UNKNOWN_GLYPH
#define EFI_WARN_DELETE_FAILURE   RETURN_WARN_DELETE_FAILURE
#define EFI_WARN_WRITE_FAILURE    RETURN_WARN_WRITE_FAILURE
#define EFI_WARN_BUFFER_TOO_SMALL RETURN_WARN_BUFFER_TOO_SMALL

//
// Bits
//

#define  BIT0     0x00000001
#define  BIT1     0x00000002
#define  BIT2     0x00000004
#define  BIT3     0x00000008
#define  BIT4     0x00000010
#define  BIT5     0x00000020
#define  BIT6     0x00000040
#define  BIT7     0x00000080
#define  BIT8     0x00000100
#define  BIT9     0x00000200
#define  BIT10    0x00000400
#define  BIT11    0x00000800
#define  BIT12    0x00001000
#define  BIT13    0x00002000
#define  BIT14    0x00004000
#define  BIT15    0x00008000
#define  BIT16    0x00010000
#define  BIT17    0x00020000
#define  BIT18    0x00040000
#define  BIT19    0x00080000
#define  BIT20    0x00100000
#define  BIT21    0x00200000
#define  BIT22    0x00400000
#define  BIT23    0x00800000
#define  BIT24    0x01000000
#define  BIT25    0x02000000
#define  BIT26    0x04000000
#define  BIT27    0x08000000
#define  BIT28    0x10000000
#define  BIT29    0x20000000
#define  BIT30    0x40000000
#define  BIT31    0x80000000
#define  BIT32    0x0000000100000000ULL
#define  BIT33    0x0000000200000000ULL
#define  BIT34    0x0000000400000000ULL
#define  BIT35    0x0000000800000000ULL
#define  BIT36    0x0000001000000000ULL
#define  BIT37    0x0000002000000000ULL
#define  BIT38    0x0000004000000000ULL
#define  BIT39    0x0000008000000000ULL
#define  BIT40    0x0000010000000000ULL
#define  BIT41    0x0000020000000000ULL
#define  BIT42    0x0000040000000000ULL
#define  BIT43    0x0000080000000000ULL
#define  BIT44    0x0000100000000000ULL
#define  BIT45    0x0000200000000000ULL
#define  BIT46    0x0000400000000000ULL
#define  BIT47    0x0000800000000000ULL
#define  BIT48    0x0001000000000000ULL
#define  BIT49    0x0002000000000000ULL
#define  BIT50    0x0004000000000000ULL
#define  BIT51    0x0008000000000000ULL
#define  BIT52    0x0010000000000000ULL
#define  BIT53    0x0020000000000000ULL
#define  BIT54    0x0040000000000000ULL
#define  BIT55    0x0080000000000000ULL
#define  BIT56    0x0100000000000000ULL
#define  BIT57    0x0200000000000000ULL
#define  BIT58    0x0400000000000000ULL
#define  BIT59    0x0800000000000000ULL
#define  BIT60    0x1000000000000000ULL
#define  BIT61    0x2000000000000000ULL
#define  BIT62    0x4000000000000000ULL
#define  BIT63    0x8000000000000000ULL

//
// Bases
//

#define  BASE_1KB    0x00000400
#define  BASE_2KB    0x00000800
#define  BASE_4KB    0x00001000
#define  BASE_8KB    0x00002000
#define  BASE_16KB   0x00004000
#define  BASE_32KB   0x00008000
#define  BASE_64KB   0x00010000
#define  BASE_128KB  0x00020000
#define  BASE_256KB  0x00040000
#define  BASE_512KB  0x00080000
#define  BASE_1MB    0x00100000
#define  BASE_2MB    0x00200000
#define  BASE_4MB    0x00400000
#define  BASE_8MB    0x00800000
#define  BASE_16MB   0x01000000
#define  BASE_32MB   0x02000000
#define  BASE_64MB   0x04000000
#define  BASE_128MB  0x08000000
#define  BASE_256MB  0x10000000
#define  BASE_512MB  0x20000000
#define  BASE_1GB    0x40000000
#define  BASE_2GB    0x80000000
#define  BASE_4GB    0x0000000100000000ULL
#define  BASE_8GB    0x0000000200000000ULL
#define  BASE_16GB   0x0000000400000000ULL
#define  BASE_32GB   0x0000000800000000ULL
#define  BASE_64GB   0x0000001000000000ULL
#define  BASE_128GB  0x0000002000000000ULL
#define  BASE_256GB  0x0000004000000000ULL
#define  BASE_512GB  0x0000008000000000ULL
#define  BASE_1TB    0x0000010000000000ULL
#define  BASE_2TB    0x0000020000000000ULL
#define  BASE_4TB    0x0000040000000000ULL
#define  BASE_8TB    0x0000080000000000ULL
#define  BASE_16TB   0x0000100000000000ULL
#define  BASE_32TB   0x0000200000000000ULL
#define  BASE_64TB   0x0000400000000000ULL
#define  BASE_128TB  0x0000800000000000ULL
#define  BASE_256TB  0x0001000000000000ULL
#define  BASE_512TB  0x0002000000000000ULL
#define  BASE_1PB    0x0004000000000000ULL
#define  BASE_2PB    0x0008000000000000ULL
#define  BASE_4PB    0x0010000000000000ULL
#define  BASE_8PB    0x0020000000000000ULL
#define  BASE_16PB   0x0040000000000000ULL
#define  BASE_32PB   0x0080000000000000ULL
#define  BASE_64PB   0x0100000000000000ULL
#define  BASE_128PB  0x0200000000000000ULL
#define  BASE_256PB  0x0400000000000000ULL
#define  BASE_512PB  0x0800000000000000ULL
#define  BASE_1EB    0x1000000000000000ULL
#define  BASE_2EB    0x2000000000000000ULL
#define  BASE_4EB    0x4000000000000000ULL
#define  BASE_8EB    0x8000000000000000ULL

//
// Functional macros
//

#define DEBUG(X) do { ppprintf X ; } while (0)
#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))
#define EFI_ERROR(x) ((x) != 0)
#define OFFSET_OF(Base, Type) offsetof(Base, Type)
#define ALIGN_VALUE(Value, Alignment) ((Value) + (((Alignment) - (Value)) & ((Alignment) - 1)))
#define MAX(a, b) \
  (((a) > (b)) ? (a) : (b))
#define MIN(a, b) \
  (((a) < (b)) ? (a) : (b))
#define DEBUG_CODE_BEGIN()  do { if (DebugCodeEnabled ()) { UINT8  __DebugCodeLocal
#define DEBUG_CODE_END()    __DebugCodeLocal = 0; __DebugCodeLocal++; } } while (FALSE)
#define DEBUG_CODE(Expression)  \
  DEBUG_CODE_BEGIN ();          \
  Expression                    \
  DEBUG_CODE_END ()
#define EFI_SIZE_TO_PAGES(a)  (((a) >> EFI_PAGE_SHIFT) + (((a) & EFI_PAGE_MASK) ? 1 : 0))
#define EFI_PAGES_TO_SIZE(a)   ( (a) << EFI_PAGE_SHIFT)


//
// Functions
//

#define AllocatePool(x) malloc(x)
#define AllocateZeroPool(x) calloc(1, x)
#define ReallocatePool(a,b,c) realloc(c,b)
#define FreePool(x) free(x)
#define CopyMem(a,b,c) memcpy((a),(b),(c))
#define ZeroMem(a,b) memset(a, 0, b)
#define AsciiSPrint snppprintf
#define AsciiStrCmp strcmp
#define AsciiStrLen strlen
#define AsciiStrStr strstr
#define AsciiStrnCmp strncmp
#define AsciiStrSize(x) (strlen(x) + 1)
#define AsciiStrnCpyS(a, b, c, d) strlcpy(a, c, b)
#define AsciiStrDecimalToUint64(a) strtoull(a, NULL, 10)
#define AsciiStrHexToUint64(a) strtoull(a, NULL, 16)
#define ASSERT assert
#define DebugCodeEnabled() true
#define FreePages(a,b) do {} while (0)

EFI_STATUS EfiGetSystemConfigurationTable (EFI_GUID *TableGuid, OUT VOID **Table);

//
// Dirty printf implementation
//

STATIC
VOID
ppptransform (
  CHAR8  *Buffer
  )
{
  char *AAA = NULL;

  #define REPL(P, I, V) \
    do { \
      AAA = strstr(Buffer, P); \
      if (AAA) \
        AAA[I] = V; \
    } while (AAA != NULL)


  REPL("%a", 1, 's');
  REPL("%-16a", 4, 's');
  REPL("%r", 1, 'p');
  REPL("%g", 1, 'p');

  #undef REPL
}

STATIC
VOID
ppprintf (
  FILE        *Shit,
  CONST CHAR8  *Src,
  ...
) {
  char  Buffer[1024];
  strlcpy (Buffer, Src, sizeof (Buffer));

  ppptransform(Buffer);

  va_list args;

  va_start(args, Src);
  vprintf(Buffer, args);
  va_end(args);
}

STATIC
VOID
snppprintf (
  CHAR8  *Buf,
  UINTN  Size,
  CONST CHAR8 *Src,
  ...
  )
{
  char  Buffer[1024];
  strlcpy(Buffer, Src, sizeof (Buffer));

  ppptransform(Buffer);

  va_list args;

  va_start(args, Src);
  vsnprintf(Buf, Size, Buffer, args);
  va_end(args);
}

STATIC
UINT64
MultU64x32 (
  UINT64 Multiplicand,
  UINT32 Multiplier
  )
{
  return Multiplicand * Multiplier;
}

STATIC
UINT64
DivU64x32 (
  UINT64 Dividend,
  UINT32 Divisor
  )
{
  return Dividend / Divisor;
}

STATIC
UINT64
LShiftU64 (
  UINT64 Operand,
  UINTN Count
  )
{
  return Operand << Count;
}

STATIC
UINT64
RShiftU64 (
  UINT64 Operand,
  UINTN Count
  )
{
  return Operand >> Count;
}

STATIC
UINT8
CalculateSum8 (
  IN UINT8  *Buffer,
  IN UINTN  Size
  )
{
  UINTN Index;
  UINT8 Sum;

  Sum = 0;

  //
  // Perform the byte sum for buffer
  //
  for (Index = 0; Index < Size; Index++) {
    Sum = (UINT8) (Sum + Buffer[Index]);
  }

  return Sum;
}

STATIC
UINT8
CalculateCheckSum8 (
  IN UINT8        *Buffer,
  IN UINTN        Size
  )
{
  return (UINT8) (0x100 - CalculateSum8 (Buffer, Size));
}

STATIC
UINT32
AsmCpuid (
  UINT32 Index,
  UINT32 *Eax,
  UINT32 *Ebx,
  UINT32 *Ecx,
  UINT32 *Edx
  )
{
  uint32_t eax = 0, ebx = 0, ecx = 0, edx = 0;

  asm ("xchgq %%rbx, %q1\n"
       "cpuid\n"
       "xchgq %%rbx, %q1"
       : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
       : "0" (Index));

  if (Eax) *Eax = eax;
  if (Ebx) *Ebx = ebx;
  if (Ecx) *Ecx = ecx;
  if (Edx) *Edx = edx;

  return Index;
}

STATIC
UINT64
AsmReadMsr64 (
  UINT32 Index
  )
{
  return 0;
}

STATIC
UINT64
EFIAPI
GetPerformanceCounterProperties (
  UINT64  *StartValue,
  UINT64  *EndValue
  )
{
  return 0;
}

//
// Services
//

struct EFI_BOOT_SERVICES_ {
  EFI_STATUS (*LocateProtocol)(EFI_GUID *ProtocolGuid, VOID *Registration, VOID **Interface);
  EFI_STATUS (*AllocatePages)(EFI_ALLOCATE_TYPE Type, EFI_MEMORY_TYPE MemoryType, UINTN Pages, EFI_PHYSICAL_ADDRESS *Memory);
  EFI_STATUS (*InstallConfigurationTable)(EFI_GUID *Guid, VOID *Table);
};

STATIC EFI_STATUS NilLocateProtocol(EFI_GUID *ProtocolGuid, VOID *Registration, VOID **Interface) {
  (VOID) ProtocolGuid;
  (VOID) Registration;
  (VOID) Interface;
  return EFI_NOT_FOUND;
}

#define TOTAL_PAGES 1000
extern _Thread_local uint32_t externalUsedPages;
extern _Thread_local uint8_t externalBlob[EFI_PAGE_SIZE*TOTAL_PAGES];

STATIC EFI_STATUS NilAllocatePages(EFI_ALLOCATE_TYPE Type, EFI_MEMORY_TYPE MemoryType, UINTN Pages, EFI_PHYSICAL_ADDRESS *Memory) {
  if (TOTAL_PAGES - externalUsedPages >= Pages) {
    *Memory = (EFI_PHYSICAL_ADDRESS)(externalBlob + externalUsedPages * EFI_PAGE_SIZE);
    externalUsedPages += Pages;
    return EFI_SUCCESS;
  }
  return EFI_OUT_OF_RESOURCES;
}

STATIC EFI_STATUS NilInstallConfigurationTable(EFI_GUID *Guid, VOID *Table) {
  (VOID) Guid;
  (VOID) Table;
  return EFI_SUCCESS;
}


STATIC EFI_BOOT_SERVICES gNilBS = {
  .LocateProtocol = NilLocateProtocol,
  .AllocatePages = NilAllocatePages,
  .InstallConfigurationTable = NilInstallConfigurationTable
};

STATIC EFI_BOOT_SERVICES *gBS = &gNilBS;

#endif
