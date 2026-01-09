#include <iostream>
#include <memory>

#include <grpcpp/grpcpp.h>
#include "calculator.grpc.pb.h"
#include "calculator.pb.h"
#include "OperationRepository.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using calculator::CalcResult;
using calculator::CalculatorService;
using calculator::NumberList;

class CalculatorServiceImpl final : public CalculatorService::Service
{
public:

    explicit CalculatorServiceImpl(OperationRepository& repo):repo_(repo){}

    Status Sum(ServerContext *,
               const NumberList *request,
               CalcResult *response) override
    {
        double result = 0;
        std::vector<double> numbers;
        for (double n : request->numbers()){
            result += n;
            numbers.push_back(n);
        }
        repo_.save_operation("sum",numbers,result);
        response->set_result(result);
        return Status::OK;
    }

    Status Sub(ServerContext *,
               const NumberList *request,
               CalcResult *response) override
    {
        if (request->numbers_size() == 0)
            return Status::OK;

        std::vector<double> numbers;
        double result = request->numbers(0);
        numbers.push_back(result);
        for (int i = 1; i < request->numbers_size(); ++i) {
            double n = request->numbers(i);
            result -= n;
            numbers.push_back(n);
        }
        repo_.save_operation("sub",numbers,result);
        response->set_result(result);
        return Status::OK;
    }

    Status Mul(ServerContext *,
               const NumberList *request,
               CalcResult *response) override
    {
        double result = 1;
        std::vector<double> numbers;

        for (double n : request->numbers()) {
            result *= n;
            numbers.push_back(n);
        }

        repo_.save_operation("mul", numbers,result);

        response->set_result(result);
        return Status::OK;
    }

    Status Div(ServerContext *,
               const NumberList *request,
               CalcResult *response) override
    {
        if (request->numbers_size() == 0)
            return Status::OK;

        std::vector<double> numbers;
        double result = request->numbers(0);
        numbers.push_back(result);

        for (int i = 1; i < request->numbers_size(); ++i) {
            double d = request->numbers(i);
            if (d == 0)
                return Status(grpc::INVALID_ARGUMENT,
                              "Division by zero");

            result /= d;
            numbers.push_back(d);
        }
        repo_.save_operation("div", numbers,result);
        response->set_result(result);
        return Status::OK;
    }

private:
    OperationRepository& repo_;
};

int main()
{
    try
    {
        std::string conn_str =
            "host=localhost "
            "port=5432 "
            "dbname=calc_db "
            "user=calc_use "
            "password=calc_pass";

        OperationRepository repo(conn_str);

        std::string server_address("0.0.0.0:50051");
        CalculatorServiceImpl service(repo);

        grpc::ServerBuilder builder;
        builder.AddListeningPort(
            server_address,
            grpc::InsecureServerCredentials());

        builder.RegisterService(&service);

        std::unique_ptr<grpc::Server> server(
            builder.BuildAndStart());

        std::cout << "Server listening on "
                  << server_address << std::endl;

        server->Wait();
    }
    catch (const std::exception& e)
    {
        std::cerr << "FATAL ERROR: "
                  << e.what() << std::endl;
    }
}
