#include <iostream>
#include <memory>
#include <vector>

#include <grpcpp/grpcpp.h>
#include "calculator.grpc.pb.h"
#include "calculator.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using calculator::CalcResult;
using calculator::CalculatorService;
using calculator::NumberList;

class CalculatorClient
{
public:
    CalculatorClient(std::shared_ptr<Channel> channel)
        : stub_(CalculatorService::NewStub(channel)) {}

    double Sum(const std::vector<double> &nums)
    {
        return CallUnary("Sum", nums);
    }

    double Sub(const std::vector<double> &nums)
    {
        return CallUnary("Sub", nums);
    }

    double Mul(const std::vector<double> &nums)
    {
        return CallUnary("Mul", nums);
    }

    double Div(const std::vector<double> &nums)
    {
        return CallUnary("Div", nums);
    }

private:
    double CallUnary(const std::string &op,
                     const std::vector<double> &nums)
    {
        NumberList request;
        for (double n : nums)
            request.add_numbers(n);

        CalcResult reply;
        ClientContext context;
        Status status;

        if (op == "Sum")
            status = stub_->Sum(&context, request, &reply);
        else if (op == "Sub")
            status = stub_->Sub(&context, request, &reply);
        else if (op == "Mul")
            status = stub_->Mul(&context, request, &reply);
        else if (op == "Div")
            status = stub_->Div(&context, request, &reply);
        else
            return 0;

        if (!status.ok())
        {
            std::cerr << op << " failed: "
                      << status.error_message() << std::endl;
            return 0;
        }
        return reply.result();
    }

    std::unique_ptr<CalculatorService::Stub> stub_;
};

int main()
{
    CalculatorClient client(
        grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    std::cout << "-------------gRPC Calculator Test-------------\n";

    std::cout << "Sum(1,2,3,4) = "
              << client.Sum({1, 2, 3, 4}) << std::endl;

    std::cout << "Sub(10,3,2) = "
              << client.Sub({10, 3, 2}) << std::endl;

    std::cout << "Mul(2,3,4) = "
              << client.Mul({2, 3, 4}) << std::endl;

    std::cout << "Div(-7,2,3,-2) = "
              << client.Div({-7, 2, 3, -2}) << std::endl;

    std::cout << "Div(10,0) = "
              << client.Div({10, 0}) << std::endl; /*error case */

    return 0;
}
