/*
 * Copyright (c) 2018, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>
#include <vector>
#include <map>

#include "gtest/gtest.h"
#include "mobile/on_vehicle_data_notification.h"

#include "utils/custom_string.h"
#include "smart_objects/smart_object.h"
#include "application_manager/smart_object_keys.h"
#include "application_manager/commands/commands_test.h"
#include "application_manager/commands/command_impl.h"
#include "application_manager/message_helper.h"
#include "application_manager/mock_message_helper.h"
#include "utils/helpers.h"

namespace test {
namespace components {
namespace commands_test {
namespace mobile_commands_test {
namespace on_vehicle_data_notification {

namespace am = ::application_manager;

using ::testing::_;
using ::testing::Return;
using ::testing::ReturnRef;

using am::commands::MessageSharedPtr;
using vehicle_info_plugin::commands::OnVehicleDataNotification;

typedef std::shared_ptr<OnVehicleDataNotification> NotificationPtr;

namespace {
const uint32_t kAppId = 1u;
}  // namespace

class OnVehicleDataNotificationTest
    : public CommandsTest<CommandsTestMocks::kIsNice> {
 public:
  OnVehicleDataNotificationTest()
      : command_msg_(CreateMessage(smart_objects::SmartType_Map))
      , command_(CreateCommand<OnVehicleDataNotification>(command_msg_)) {}

  MessageSharedPtr command_msg_;
  NotificationPtr command_;
};

MATCHER_P2(CheckMessageData, key, value, "") {
  const bool kIsMobileProtocolTypeCorrect =
      (*arg)[am::strings::params][am::strings::protocol_type].asInt() ==
      am::commands::CommandImpl::mobile_protocol_type_;

  const bool kIsProtocolVersionCorrect =
      (*arg)[am::strings::params][am::strings::protocol_version].asInt() ==
      am::commands::CommandImpl::protocol_version_;

  const bool kIsNotificationCorrect =
      (*arg)[am::strings::params][am::strings::message_type].asInt() ==
      am::MessageType::kNotification;

  const bool kIsConnectionKeyCorrect =
      (*arg)[am::strings::params][am::strings::connection_key].asUInt() ==
      kAppId;

  const bool kAreMsgParamsCorrect =
      (*arg)[am::strings::msg_params][key].asInt() == value;

  using namespace helpers;
  return Compare<bool, EQ, ALL>(true,
                                kIsMobileProtocolTypeCorrect,
                                kIsProtocolVersionCorrect,
                                kIsNotificationCorrect,
                                kIsConnectionKeyCorrect,
                                kAreMsgParamsCorrect);
}

}  // namespace on_vehicle_data_notification
}  // namespace mobile_commands_test
}  // namespace commands_test
}  // namespace components
}  // namespace test
