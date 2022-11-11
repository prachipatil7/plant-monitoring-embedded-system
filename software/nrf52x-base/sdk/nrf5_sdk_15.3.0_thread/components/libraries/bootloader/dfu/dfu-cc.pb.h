/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.9.3 at Fri Oct 11 23:29:17 2019. */

#ifndef PB_DFU_DFU_CC_PB_H_INCLUDED
#define PB_DFU_DFU_CC_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _dfu_FwType {
    dfu_FwType_APPLICATION = 0,
    dfu_FwType_SOFTDEVICE = 1,
    dfu_FwType_BOOTLOADER = 2,
    dfu_FwType_SOFTDEVICE_BOOTLOADER = 3,
    dfu_FwType_EXTERNAL_APPLICATION = 4
} dfu_FwType;
#define _dfu_FwType_MIN dfu_FwType_APPLICATION
#define _dfu_FwType_MAX dfu_FwType_EXTERNAL_APPLICATION
#define _dfu_FwType_ARRAYSIZE ((dfu_FwType)(dfu_FwType_EXTERNAL_APPLICATION+1))

typedef enum _dfu_HashType {
    dfu_HashType_NO_HASH = 0,
    dfu_HashType_CRC = 1,
    dfu_HashType_SHA128 = 2,
    dfu_HashType_SHA256 = 3,
    dfu_HashType_SHA512 = 4
} dfu_HashType;
#define _dfu_HashType_MIN dfu_HashType_NO_HASH
#define _dfu_HashType_MAX dfu_HashType_SHA512
#define _dfu_HashType_ARRAYSIZE ((dfu_HashType)(dfu_HashType_SHA512+1))

typedef enum _dfu_OpCode {
    dfu_OpCode_INIT = 1
} dfu_OpCode;
#define _dfu_OpCode_MIN dfu_OpCode_INIT
#define _dfu_OpCode_MAX dfu_OpCode_INIT
#define _dfu_OpCode_ARRAYSIZE ((dfu_OpCode)(dfu_OpCode_INIT+1))

typedef enum _dfu_ValidationType {
    dfu_ValidationType_NO_VALIDATION = 0,
    dfu_ValidationType_VALIDATE_GENERATED_CRC = 1,
    dfu_ValidationType_VALIDATE_SHA256 = 2,
    dfu_ValidationType_VALIDATE_ECDSA_P256_SHA256 = 3
} dfu_ValidationType;
#define _dfu_ValidationType_MIN dfu_ValidationType_NO_VALIDATION
#define _dfu_ValidationType_MAX dfu_ValidationType_VALIDATE_ECDSA_P256_SHA256
#define _dfu_ValidationType_ARRAYSIZE ((dfu_ValidationType)(dfu_ValidationType_VALIDATE_ECDSA_P256_SHA256+1))

typedef enum _dfu_SignatureType {
    dfu_SignatureType_ECDSA_P256_SHA256 = 0,
    dfu_SignatureType_ED25519 = 1
} dfu_SignatureType;
#define _dfu_SignatureType_MIN dfu_SignatureType_ECDSA_P256_SHA256
#define _dfu_SignatureType_MAX dfu_SignatureType_ED25519
#define _dfu_SignatureType_ARRAYSIZE ((dfu_SignatureType)(dfu_SignatureType_ED25519+1))

/* Struct definitions */
typedef PB_BYTES_ARRAY_T(64) dfu_BootValidation_bytes_t;
typedef struct _dfu_BootValidation {
    dfu_ValidationType type;
    dfu_BootValidation_bytes_t bytes;
/* @@protoc_insertion_point(struct:dfu_BootValidation) */
} dfu_BootValidation;

typedef PB_BYTES_ARRAY_T(32) dfu_Hash_hash_t;
typedef struct _dfu_Hash {
    dfu_HashType hash_type;
    dfu_Hash_hash_t hash;
/* @@protoc_insertion_point(struct:dfu_Hash) */
} dfu_Hash;

typedef struct _dfu_InitCommand {
    bool has_fw_version;
    uint32_t fw_version;
    bool has_hw_version;
    uint32_t hw_version;
    pb_size_t sd_req_count;
    uint32_t sd_req[16];
    bool has_type;
    dfu_FwType type;
    bool has_sd_size;
    uint32_t sd_size;
    bool has_bl_size;
    uint32_t bl_size;
    bool has_app_size;
    uint32_t app_size;
    bool has_hash;
    dfu_Hash hash;
    bool has_is_debug;
    bool is_debug;
    pb_size_t boot_validation_count;
    dfu_BootValidation boot_validation[3];
/* @@protoc_insertion_point(struct:dfu_InitCommand) */
} dfu_InitCommand;

typedef struct _dfu_Command {
    bool has_op_code;
    dfu_OpCode op_code;
    bool has_init;
    dfu_InitCommand init;
/* @@protoc_insertion_point(struct:dfu_Command) */
} dfu_Command;

typedef PB_BYTES_ARRAY_T(64) dfu_SignedCommand_signature_t;
typedef struct _dfu_SignedCommand {
    dfu_Command command;
    dfu_SignatureType signature_type;
    dfu_SignedCommand_signature_t signature;
/* @@protoc_insertion_point(struct:dfu_SignedCommand) */
} dfu_SignedCommand;

typedef struct _dfu_Packet {
    bool has_command;
    dfu_Command command;
    bool has_signed_command;
    dfu_SignedCommand signed_command;
/* @@protoc_insertion_point(struct:dfu_Packet) */
} dfu_Packet;

/* Default values for struct fields */
extern const bool dfu_InitCommand_is_debug_default;

/* Initializer values for message structs */
#define dfu_Hash_init_default                    {_dfu_HashType_MIN, {0, {0}}}
#define dfu_BootValidation_init_default          {_dfu_ValidationType_MIN, {0, {0}}}
#define dfu_InitCommand_init_default             {false, 0, false, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, false, _dfu_FwType_MIN, false, 0, false, 0, false, 0, false, dfu_Hash_init_default, false, false, 0, {dfu_BootValidation_init_default, dfu_BootValidation_init_default, dfu_BootValidation_init_default}}
#define dfu_Command_init_default                 {false, _dfu_OpCode_MIN, false, dfu_InitCommand_init_default}
#define dfu_SignedCommand_init_default           {dfu_Command_init_default, _dfu_SignatureType_MIN, {0, {0}}}
#define dfu_Packet_init_default                  {false, dfu_Command_init_default, false, dfu_SignedCommand_init_default}
#define dfu_Hash_init_zero                       {_dfu_HashType_MIN, {0, {0}}}
#define dfu_BootValidation_init_zero             {_dfu_ValidationType_MIN, {0, {0}}}
#define dfu_InitCommand_init_zero                {false, 0, false, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, false, _dfu_FwType_MIN, false, 0, false, 0, false, 0, false, dfu_Hash_init_zero, false, 0, 0, {dfu_BootValidation_init_zero, dfu_BootValidation_init_zero, dfu_BootValidation_init_zero}}
#define dfu_Command_init_zero                    {false, _dfu_OpCode_MIN, false, dfu_InitCommand_init_zero}
#define dfu_SignedCommand_init_zero              {dfu_Command_init_zero, _dfu_SignatureType_MIN, {0, {0}}}
#define dfu_Packet_init_zero                     {false, dfu_Command_init_zero, false, dfu_SignedCommand_init_zero}

/* Field tags (for use in manual encoding/decoding) */
#define dfu_BootValidation_type_tag              1
#define dfu_BootValidation_bytes_tag             2
#define dfu_Hash_hash_type_tag                   1
#define dfu_Hash_hash_tag                        2
#define dfu_InitCommand_fw_version_tag           1
#define dfu_InitCommand_hw_version_tag           2
#define dfu_InitCommand_sd_req_tag               3
#define dfu_InitCommand_type_tag                 4
#define dfu_InitCommand_sd_size_tag              5
#define dfu_InitCommand_bl_size_tag              6
#define dfu_InitCommand_app_size_tag             7
#define dfu_InitCommand_hash_tag                 8
#define dfu_InitCommand_is_debug_tag             9
#define dfu_InitCommand_boot_validation_tag      10
#define dfu_Command_op_code_tag                  1
#define dfu_Command_init_tag                     2
#define dfu_SignedCommand_command_tag            1
#define dfu_SignedCommand_signature_type_tag     2
#define dfu_SignedCommand_signature_tag          3
#define dfu_Packet_command_tag                   1
#define dfu_Packet_signed_command_tag            2

/* Struct field encoding specification for nanopb */
extern const pb_field_t dfu_Hash_fields[3];
extern const pb_field_t dfu_BootValidation_fields[3];
extern const pb_field_t dfu_InitCommand_fields[11];
extern const pb_field_t dfu_Command_fields[3];
extern const pb_field_t dfu_SignedCommand_fields[4];
extern const pb_field_t dfu_Packet_fields[3];

/* Maximum encoded size of messages (where known) */
#define dfu_Hash_size                            36
#define dfu_BootValidation_size                  68
#define dfu_InitCommand_size                     378
#define dfu_Command_size                         383
#define dfu_SignedCommand_size                   454
#define dfu_Packet_size                          843

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define DFU_CC_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif