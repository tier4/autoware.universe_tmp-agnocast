#pragma once

#include "agnocast.hpp"

#include <rclcpp/rclcpp.hpp>

namespace autoware::universe_utils
{

template <typename T>
class AgnocastPollingSubscriber
{
public:
  static std::shared_ptr<AgnocastPollingSubscriber<T>> create_subscription(
    const std::string & topic_name, const rclcpp::QoS & qos = rclcpp::QoS{1})
  {
    return std::make_shared<AgnocastPollingSubscriber<T>>(topic_name, qos);
  }

private:
  typename agnocast::TakeSubscription<T>::SharedPtr subscriber_;

public:
  explicit AgnocastPollingSubscriber(
    const std::string & topic_name, const rclcpp::QoS & qos = rclcpp::QoS{1})
  {
    subscriber_ = agnocast::create_subscription<T>(topic_name, qos);
    if (qos.get_rmw_qos_profile().depth > 1) {
      throw std::invalid_argument("unreachable");
    }
  };

  const agnocast::ipc_shared_ptr<T> takeData() { return subscriber_->take(); };
};

}  // namespace autoware::universe_utils
