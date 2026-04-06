/**
 * @file friends.h
 * @brief Friend implementation.
 */

#pragma once

#include <nn/account.h>
#include <nn/os.h>

namespace nn {
namespace friends {
typedef char Url[0xA0];

class AsyncContext;
class Profile;

void Initialize();
Result GetProfileList(nn::friends::AsyncContext* context, nn::friends::Profile* profiles,
                      nn::account::Uid const& userID,
                      nn::account::NetworkServiceAccountId const* accountIDs, s32 numAccounts);

class Profile {
public:
    Profile();

    nn::account::NetworkServiceAccountId GetAccountId() const;
    nn::account::Nickname& GetNickname() const;
    bool IsValid() const;
    Result GetProfileImageUrl(nn::friends::Url*, s32);

    u8 data[0x100];  // [derived: Ghidra FUN_7103755cb0 shows memcpy with size 0x100]
};

class AsyncContext {
public:
    AsyncContext();
    ~AsyncContext();

    Result GetSystemEvent(nn::os::SystemEvent*);
    Result GetResult() const;
};
}  // namespace friends
}  // namespace nn
