#pragma once

#include "IQueue.h"

namespace event {

class Queue final : public IQueue {
 public:
  Queue();
  Queue(Queue&& other) = delete;
  Queue(const Queue& other) = delete;
  Queue& operator=(Queue&& other) = delete;
  Queue& operator=(const Queue& other) = delete;

  void Complete() noexcept override;
  void Enqueue(const EventSharedPtr& event) noexcept override;
  tl::expected<EventSharedPtr, std::error_code> Dequeue() noexcept override;

 private:
  mutable std::mutex mutex_;
  std::condition_variable condition_;
  std::deque<EventSharedPtr> queue_;
  bool completed_;
};

} 
