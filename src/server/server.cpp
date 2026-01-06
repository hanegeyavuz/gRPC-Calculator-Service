#include <iostream>
#include <memory>

#include <grpcpp/grpcpp.h>
#include "calculator.grpc.pb.h"
#include "calculator.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using calculator::CalcResult;
using calculator::CalculatorService;
using calculator::NumberList;

class CalculatorServiceImpl final
    : public CalculatorService::Service
{
public:
    Status Sum(ServerContext *,
               const NumberList *request,
               CalcResult *response) override
    {
        double sum = 0;
        for (double n : request->numbers())
            sum += n;

        response->set_result(sum);
        return Status::OK;
    }

    Status Sub(ServerContext *,
               const NumberList *request,
               CalcResult *response) override
    {
        if (request->numbers_size() == 0)
            return Status::OK;

        double result = request->numbers(0);
        for (int i = 1; i < request->numbers_size(); ++i)
            result -= request->numbers(i);

        response->set_result(result);
        return Status::OK;
    }

    Status Mul(ServerContext *,
               const NumberList *request,
               CalcResult *response) override
    {
        double result = 1;
        for (double n : request->numbers())
            result *= n;

        response->set_result(result);
        return Status::OK;
    }

    Status Div(ServerContext *,
               const NumberList *request,
               CalcResult *response) override
    {
        if (request->numbers_size() == 0)
            return Status::OK;

        double result = request->numbers(0);

        for (int i = 1; i < request->numbers_size(); ++i)
        {
            double d = request->numbers(i);
            if (d == 0)
                return Status(grpc::INVALID_ARGUMENT,
                              "Division by zero");
            result /= d;
        }

        response->set_result(result);
        return Status::OK;
    }
};

int main()
{
    std::string server_address("0.0.0.0:50051");
    CalculatorServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(
        server_address,
        grpc::InsecureServerCredentials());

    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());

    std::cout << "Server listening on "
              << server_address << std::endl;

    server->Wait();
    return 0;
}
