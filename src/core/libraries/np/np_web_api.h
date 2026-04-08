// SPDX-FileCopyrightText: Copyright 2026 shadPS4 Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <map>
#include <mutex>
#include "common/types.h"
#include "core/libraries/np/np_common.h"
#include "core/libraries/np/np_types.h"
#include "core/libraries/system/userservice.h"

namespace Core::Loader {
class SymbolsResolver;
}

namespace Libraries::Np::NpWebApi {

struct __attribute__((packed)) SceNpWebApiContentParameter {
    uint64_t content_length;
    const char* p_content_type;
    uint8_t reserved[16];
};

// For mocking responses
enum SceNpWebApiMockRequestType { REQ_INVALID = -1, REQ_BLOCK_LIST = 110, REQ_FRIEND_LIST = 120 };

#define ORBIS_NP_WEBAPI_DEFAULT_CONNECTION_NUM 1
#define ORBIS_NP_WEBAPI_MAX_CONNECTION_NUM 16
#define ORBIS_NP_WEBAPI_PUSH_EVENT_DATA_TYPE_LEN_MAX 64
#define ORBIS_NP_WEBAPI_EXTD_PUSH_EVENT_EXTD_DATA_KEY_LEN_MAX 32

struct OrbisNpWebApiPushEventDataType {
    char val[ORBIS_NP_WEBAPI_PUSH_EVENT_DATA_TYPE_LEN_MAX + 1];
};

struct OrbisNpWebApiExtdPushEventExtdDataKey {
    char val[ORBIS_NP_WEBAPI_EXTD_PUSH_EVENT_EXTD_DATA_KEY_LEN_MAX + 1];
};

struct OrbisNpWebApiPushEventFilterParameter {
    OrbisNpWebApiPushEventDataType dataType;
};

struct OrbisNpWebApiServicePushEventFilterParameter {
    OrbisNpWebApiPushEventDataType dataType;
};

struct OrbisNpWebApiExtdPushEventFilterParameter {
    OrbisNpWebApiPushEventDataType dataType;
    OrbisNpWebApiExtdPushEventExtdDataKey* pExtdDataKey;
    u64 extdDataKeyNum;
};

struct OrbisNpWebApiExtdPushEventExtdData {
    OrbisNpWebApiExtdPushEventExtdDataKey extdDataKey;
    char* pData;
    u64 dataLen;
};

struct OrbisNpWebApiHttpHeader {
    char* pName;
    char* pValue;
};

struct OrbisNpWebApiMultipartPartParameter {
    OrbisNpWebApiHttpHeader* pHeaders;
    u64 headerNum;
    u64 contentLength;
};

enum OrbisNpWebApiHttpMethod : s32 {
    ORBIS_NP_WEBAPI_HTTP_METHOD_GET,
    ORBIS_NP_WEBAPI_HTTP_METHOD_POST,
    ORBIS_NP_WEBAPI_HTTP_METHOD_PUT,
    ORBIS_NP_WEBAPI_HTTP_METHOD_DELETE,
    ORBIS_NP_WEBAPI_HTTP_METHOD_PATCH
};

struct OrbisNpWebApiContentParameter {
    u64 contentLength;
    const char* pContentType;
    u8 reserved[16];
};

struct OrbisNpWebApiResponseInformationOption {
    s32 httpStatus;
    char* pErrorObject;
    u64 errorObjectSize;
    u64 responseDataSize;
};

struct OrbisNpWebApiMemoryPoolStats {
    u64 poolSize;
    u64 maxInuseSize;
    u64 currentInuseSize;
    s32 reserved;
};

struct OrbisNpWebApiConnectionStats {
    u32 max;
    u32 used;
    u32 unused;
    u32 keepAlive;
    u64 reserved;
};

struct OrbisNpWebApiIntInitializeArgs {
    u32 libHttpCtxId;
    u8 reserved[4];
    u64 poolSize;
    const char* name;
    u64 structSize;
};

struct OrbisNpWebApiIntCreateRequestExtraArgs {
    void* unk_0;
    void* unk_1;
    void* unk_2;
};

using OrbisNpWebApiPushEventCallback = PS4_SYSV_ABI void (*)(); // dummy

using OrbisNpWebApiExtdPushEventCallback = PS4_SYSV_ABI void (*)(); // dummy
using OrbisNpWebApiExtdPushEventCallbackA = PS4_SYSV_ABI void (*)(
    s32 userCtxId, s32 callbackId, const char* pNpServiceName, OrbisNpServiceLabel npServiceLabel,
    const OrbisNpPeerAddressA* pTo, const OrbisNpOnlineId* pToOnlineId,
    const OrbisNpPeerAddressA* pFrom, const OrbisNpOnlineId* pFromOnlineId,
    const OrbisNpWebApiPushEventDataType* pDataType, const char* pData, u64 dataLen,
    const OrbisNpWebApiExtdPushEventExtdData* pExtdData, u64 extdDataNum, void* pUserArg);

using OrbisNpWebApiServicePushEventCallback = PS4_SYSV_ABI void (*)();          // dummy
using OrbisNpWebApiInternalServicePushEventCallback = PS4_SYSV_ABI void (*)();  // dummy
using OrbisNpWebApiInternalServicePushEventCallbackA = PS4_SYSV_ABI void (*)(); // dummy

using OrbisNpWebApiNotificationCallback = PS4_SYSV_ABI void (*)(); // dummy
s32 PS4_SYSV_ABI sceNpWebApiCreateRequest(s32 title_user_ctx_id, const char* p_api_group,
                                          const char* p_path, s32 method,
                                          SceNpWebApiContentParameter* p_content_parameter,
                                          s64* p_request_id);
s32 PS4_SYSV_ABI sceNpWebApiDeleteRequest(s64 request_id);
s32 PS4_SYSV_ABI sceNpWebApiGetHttpStatusCode(s64 request_id, s32* out_status_code);
s32 PS4_SYSV_ABI sceNpWebApiReadData(s64 request_id, char* data, u64 size);
s32 PS4_SYSV_ABI Func_064C4ED1EDBEB9E8();
s32 PS4_SYSV_ABI Func_0783955D4E9563DA();
s32 PS4_SYSV_ABI Func_1A6D77F3FD8323A8();
s32 PS4_SYSV_ABI Func_1E0693A26FE0F954();
s32 PS4_SYSV_ABI Func_24A9B5F1D77000CF();
s32 PS4_SYSV_ABI Func_24AAA6F50E4C2361();
s32 PS4_SYSV_ABI Func_24D8853D6B47FC79();
s32 PS4_SYSV_ABI Func_279B3E9C7C4A9DC5();
s32 PS4_SYSV_ABI Func_28461E29E9F8D697();
s32 PS4_SYSV_ABI Func_3C29624704FAB9E0();
s32 PS4_SYSV_ABI Func_3F027804ED2EC11E();
s32 PS4_SYSV_ABI Func_4066C94E782997CD();
s32 PS4_SYSV_ABI Func_47C85356815DBE90();
s32 PS4_SYSV_ABI Func_4FCE8065437E3B87();
s32 PS4_SYSV_ABI Func_536280BE3DABB521();
s32 PS4_SYSV_ABI Func_57A0E1BC724219F3();
s32 PS4_SYSV_ABI Func_5819749C040B6637();
s32 PS4_SYSV_ABI Func_6198D0C825E86319();
s32 PS4_SYSV_ABI Func_61F2B9E8AB093743();
s32 PS4_SYSV_ABI Func_6BC388E6113F0D44();
s32 PS4_SYSV_ABI Func_7500F0C4F8DC2D16();
s32 PS4_SYSV_ABI Func_75A03814C7E9039F();
s32 PS4_SYSV_ABI Func_789D6026C521416E();
s32 PS4_SYSV_ABI Func_7DED63D06399EFFF();
s32 PS4_SYSV_ABI Func_7E55A2DCC03D395A();
s32 PS4_SYSV_ABI Func_7E6C8F9FB86967F4();
s32 PS4_SYSV_ABI Func_7F04B7D4A7D41E80();
s32 PS4_SYSV_ABI Func_8E167252DFA5C957();
s32 PS4_SYSV_ABI Func_95D0046E504E3B09();
s32 PS4_SYSV_ABI Func_97284BFDA4F18FDF();
s32 PS4_SYSV_ABI Func_99E32C1F4737EAB4();
s32 PS4_SYSV_ABI Func_9CFF661EA0BCBF83();
s32 PS4_SYSV_ABI Func_9EB0E1F467AC3B29();
s32 PS4_SYSV_ABI Func_A2318FE6FBABFAA3();
s32 PS4_SYSV_ABI Func_BA07A2E1BF7B3971();
s32 PS4_SYSV_ABI Func_BD0803EEE0CC29A0();
s32 PS4_SYSV_ABI Func_BE6F4E5524BB135F();
s32 PS4_SYSV_ABI Func_C0D490EB481EA4D0();
s32 PS4_SYSV_ABI Func_C175D392CA6D084A();
s32 PS4_SYSV_ABI Func_CD0136AF165D2F2F();
s32 PS4_SYSV_ABI Func_D1C0ADB7B52FEAB5();
s32 PS4_SYSV_ABI Func_E324765D18EE4D12();
s32 PS4_SYSV_ABI Func_E789F980D907B653();
s32 PS4_SYSV_ABI Func_F9A32E8685627436();

void RegisterLib(Core::Loader::SymbolsResolver* sym);
} // namespace Libraries::Np::NpWebApi
