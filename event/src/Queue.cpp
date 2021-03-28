#include "Queue.h"

namespace event {

Queue::Queue() : completed_(false) {}

void Queue::Complete() noexcept {
  std::lock_guard lk{ mutex_ };
  completed_ = true;
  condition_.notify_all();
}

void Queue::Enqueue(const EventSharedPtr& event) noexcept {
  std::lock_guard locke{ mutex_ };
  queue_.push_back(event);
  condition_.notify_all();
}

tl::expected<EventSharedPtr, std::error_code> Queue::Dequeue() noexcept {
  std::unique_lock locker{ mutex_ };

  condition_.wait(locker, [this]{
    return completed_ || !queue_.empty();
  });

  if (completed_) {
    return tl::unexpected<std::error_code>{ std::make_error_code(std::errc::interrupted) };
  }

  const auto event = queue_.front();
  queue_.pop_front();

  return event;
}

}
