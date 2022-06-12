#include "opencat/opencat.hpp"
#include <rclcpp/logger.hpp>

namespace OpenCat
{
ServiceClient::ServiceClient()
    : node(rclcpp::Node::make_shared("opencat_cpp_client")),
      send_task(node->create_client<BaseTask>("opencat_send_task"))
{
}

void ServiceClient::SendTask(const Task &task)
{
    auto request = std::make_shared<BaseTask::Request>();
    auto res = std::make_shared<BaseTask::Response>();
    request->cmd = task.cmd;
    request->delay = task.delay;
    request->arguments = task.arguments;
    auto result = send_task->async_send_request(request);
    // Wait for the result.
    rclcpp::spin_until_future_complete(node, result);
    if (!result.get()->res)
    {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "send task failed");
    }
}

void ServiceClient::SendMultipleTasks(const vector<Task> &tasks)
{
    for (auto &task : tasks)
        this->SendTask(task);
}
} // namespace OpenCat
