#pragma once

#include "IEvent.h"
#include "Helpers.h"

namespace event {

class IQueue {
 public:
  virtual ~IQueue() = default;

  virtual void Complete() noexcept = 0;
  virtual void Enqueue(const EventSharedPtr& event) noexcept = 0;
  virtual tl::expected<EventSharedPtr, std::error_code> Dequeue() noexcept = 0;
};

}
