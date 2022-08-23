// Copyright 2015, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Injection point for custom user configurations. See README for details
//
// ** Custom implementation starts here **

#ifndef GOOGLETEST_INCLUDE_GTEST_INTERNAL_CUSTOM_GTEST_PORT_H_
#define GOOGLETEST_INCLUDE_GTEST_INTERNAL_CUSTOM_GTEST_PORT_H_


// The following macros can be defined:

// ### Logging:

// *   `GTEST_LOG_(severity)`
// *   `GTEST_CHECK_(condition)`
// *   Functions `LogToStderr()` and `FlushInfoLog()` have to be provided too.

// ### Threading:

// *   `GTEST_HAS_NOTIFICATION_` - Enabled if Notification is already provided.
// *   `GTEST_HAS_MUTEX_AND_THREAD_LOCAL_` - Enabled if `Mutex` and `ThreadLocal`
//     are already provided. Must also provide `GTEST_DECLARE_STATIC_MUTEX_(mutex)`
//     and `GTEST_DEFINE_STATIC_MUTEX_(mutex)`
// *   `GTEST_EXCLUSIVE_LOCK_REQUIRED_(locks)`
// *   `GTEST_LOCK_EXCLUDED_(locks)`

// ### Underlying library support features

// *   `GTEST_HAS_CXXABI_H_`

// ### Exporting API symbols:

// *   `GTEST_API_` - Specifier for exported symbols.

class Notification {
 public:
  Notification() : notified_(false) {}
  Notification(const Notification&) = delete;
  Notification& operator=(const Notification&) = delete;

  // Notifies all threads created with this notification to start. Must
  // be called from the controller thread.
  void Notify() {
    // std::lock_guard<std::mutex> lock(mu_);
    notified_ = true;
    // cv_.notify_all();
  }

  // Blocks until the controller thread notifies. Must be called from a test
  // thread.
  void WaitForNotification() {
    // std::unique_lock<std::mutex> lock(mu_);
    // cv_.wait(lock, [this]() { return notified_; });
  }

 private:
//   std::mutex mu_;
//   std::condition_variable cv_;
  bool notified_;
};

#define GTEST_LOG_(severity)                                           \
  ::testing::internal::GTestLog(::testing::internal::GTEST_##severity, \
                                __FILE__, __LINE__)                    \
      .GetStream()

#define GTEST_CHECK_(condition)               \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_               \
  if (condition) \
    ;                                         \
  else                                        \
    GTEST_LOG_(FATAL) << "Condition " #condition " failed. "


#define GTEST_HAS_NOTIFICATION_ 1
#define GTEST_HAS_MUTEX_AND_THREAD_LOCAL_ 0
#define GTEST_EXCLUSIVE_LOCK_REQUIRED_(locks)
#define GTEST_LOCK_EXCLUDED_(locks)

#define GTEST_HAS_CXXABI_H_ 0

#define GTEST_API_

#endif  // GOOGLETEST_INCLUDE_GTEST_INTERNAL_CUSTOM_GTEST_PORT_H_
