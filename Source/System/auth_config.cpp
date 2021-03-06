﻿// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "pch.h"
#include "shared_macros.h"
#include "xsapi/system.h"
#include "utils.h"
#include "auth_config.h"

NAMESPACE_MICROSOFT_XBOX_SERVICES_SYSTEM_CPP_BEGIN


string_t get_endpoint_path(
    _In_ const string_t& serviceName,
    _In_ const string_t& environmentPrefix,
    _In_ const string_t& environment,
    _In_ bool appendProtocol = true
    )
{
    stringstream_t source;
    if (appendProtocol)
    {
        source << _T("https://");
    }
    source << environmentPrefix;
    source << serviceName;
    source << environment;
    source << _T(".xboxlive.com");
    return source.str();
}

auth_config::auth_config() :
    m_useCompactTicket(false),
    m_detailError(0),
    m_httpStatusCode(0)
{
    m_xtokenComposition = { token_identity_type::u_token, token_identity_type::d_token, token_identity_type::t_token };
}

auth_config::auth_config(
    _In_ string_t sandbox, 
    _In_ string_t environmentPrefix,
    _In_ string_t environment,
    _In_ bool useCompactTicket,
    _In_ bool isCreatorsSDK) :
    m_useCompactTicket(useCompactTicket),
    m_sandbox(std::move(sandbox)),
    m_detailError(0),
    m_rpsTicketPolicy(useCompactTicket? _T("MBI_SSL") : _T("DELEGATION")),
    m_xboxLiveRelyingParty(_T("http://auth.xboxlive.com")),
    m_xboxLiveEndpoint(_T("https://xboxlive.com")),
    m_environment(std::move(environment))
{
    m_xTitleEndpoint = get_endpoint_path(_T("title.mgt"), environmentPrefix, environment);
    m_deviceTokenEndpoint = get_endpoint_path(_T("device.auth"), environmentPrefix, environment);
    m_titleTokenEndpoint = get_endpoint_path(_T("title.auth"), environmentPrefix, environment);
    m_userTokenEndpoint = get_endpoint_path(_T("user.auth"), environmentPrefix, environment);
    m_serviceTokenEndpoint = get_endpoint_path(_T("service.auth"), environmentPrefix, environment);
    m_xTokenEndpoint = get_endpoint_path(_T("xsts.auth"), environmentPrefix, environment);
    m_userTokenSiteName = get_endpoint_path(_T("user.auth"), _T(""), environment, false); 
    m_rpsTicketService = isCreatorsSDK ? _T("xbl.signin xbl.friends") : (useCompactTicket ? m_userTokenSiteName : _T("xboxlive.signin"));
    m_xtokenComposition = { token_identity_type::u_token, token_identity_type::d_token, token_identity_type::t_token };
}

#if XSAPI_SERVER || XSAPI_U
bool auth_config::use_win10_auth() const
{
#if UWP_API || XSAPI_U
    return true;
#else
    return false;
#endif
}

bool auth_config::use_compact_ticket() const
{
    return m_useCompactTicket;
}
#endif

const string_t& auth_config::rps_ticket_service() const
{
    return m_rpsTicketService;
}

void auth_config::set_rps_ticket_service(
    _In_ string_t value
    )
{
    m_rpsTicketService = std::move(value);
}

const string_t& auth_config::rps_ticket_policy() const
{
    return m_rpsTicketPolicy;
}

void auth_config::set_rps_ticket_policy(
    _In_ string_t value
    )
{
    m_rpsTicketPolicy = std::move(value);
}

#if XSAPI_SERVER || XSAPI_U
const string_t& auth_config::environment() const
{
    return m_environment;
}

const string_t& auth_config::device_token_endpoint() const
{
    return m_deviceTokenEndpoint;
}

void auth_config::set_device_token_endpoint(
    _In_ string_t value
    )
{
    m_deviceTokenEndpoint = std::move(value);
}

const string_t& auth_config::title_token_endpoint() const
{
    return m_titleTokenEndpoint;
}

void auth_config::set_title_token_endpoint(
    _In_ string_t value
    )
{
    m_titleTokenEndpoint = std::move(value);
}

const string_t& auth_config::user_token_site_name() const
{
    return m_userTokenSiteName;
}

void auth_config::set_user_token_site_name(
    _In_ string_t value
    )
{
    m_userTokenSiteName = std::move(value);
}

const string_t& auth_config::user_token_endpoint() const
{
    return m_userTokenEndpoint;
}

void auth_config::set_user_token_endpoint(
    _In_ string_t value
    )
{
    m_userTokenEndpoint = std::move(value);
}

const string_t& auth_config::service_token_endpoint() const
{
    return m_serviceTokenEndpoint;
}

void auth_config::set_service_token_endpoint(
    _In_ string_t value
    )
{
    m_serviceTokenEndpoint = std::move(value);
}

const string_t& auth_config::xbox_live_relying_party() const
{
    return m_xboxLiveRelyingParty;
}

void auth_config::set_xbox_live_relying_party(
    _In_ string_t value
    )
{
    m_xboxLiveRelyingParty = std::move(value);
}
#endif

const string_t& auth_config::xbox_live_endpoint() const
{
    return m_xboxLiveEndpoint;
}

void auth_config::set_xbox_live_endpoint(
    _In_ string_t value
    )
{
    m_xboxLiveEndpoint = std::move(value);
}

#if XSAPI_SERVER || XSAPI_U
const string_t& auth_config::x_token_endpoint() const
{
    return m_xTokenEndpoint;
}

void auth_config::set_x_token_endpoint(
    _In_ string_t value
    )
{
    m_xTokenEndpoint = std::move(value);
}

const string_t& auth_config::x_title_endpoint() const
{
    return m_xTitleEndpoint;
}

void auth_config::set_x_title_endpoint(
    _In_ string_t value
    )
{
    m_xTitleEndpoint = std::move(value);
}

void auth_config::set_app_id(string_t appId)
{
    m_appId = std::move(appId);
}

const string_t& auth_config::app_id() const
{
    return m_appId;
}

void auth_config::set_microsoft_account_id(string_t accountId)
{
    m_accountId = std::move(accountId);
}

const string_t& auth_config::microsoft_account_id() const
{
    return m_accountId;
}

void auth_config::set_detail_error(uint32_t detail_error)
{
    m_detailError = detail_error;
}

uint32_t auth_config::detail_error() const
{
    return m_detailError;
}

void auth_config::reset()
{
    m_redirect.clear();
    m_detailError = 0;
}

void auth_config::set_redirect(_In_ string_t value)
{
    m_redirect = std::move(value);
}

const string_t& auth_config::redirect() const
{
    return m_redirect;
}

const std::vector<token_identity_type>& auth_config::xtoken_composition() const
{
    return m_xtokenComposition;
}

void auth_config::set_xtoken_composition(std::vector<token_identity_type> value)
{
    m_xtokenComposition = value;
}

uint32_t auth_config::http_status_code() const
{
    return m_httpStatusCode;
}
void auth_config::set_http_status_code(
    _In_ uint32_t httpStatusCode
    )
{
    m_httpStatusCode = httpStatusCode;
}
#endif

NAMESPACE_MICROSOFT_XBOX_SERVICES_SYSTEM_CPP_END
