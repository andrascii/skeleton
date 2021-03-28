#pragma once

namespace event {

class IEvent {
 public:
  virtual ~IEvent() = default;

  virtual void Handle() noexcept = 0;
};

using EventSharedPtr = std::shared_ptr<IEvent>;
using EventUniquePtr = std::unique_ptr<IEvent>;

}
