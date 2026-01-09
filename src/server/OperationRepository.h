#pragma once

#include <string>
#include <vector>
#include <pqxx/pqxx>

class OperationRepository {
public:
    explicit OperationRepository(const std::string& connection_string);

    void save_operation(
        const std::string& operation_type,
        const std::vector<double>& numbers, double result
    );

private:
    pqxx::connection connection_;
};
