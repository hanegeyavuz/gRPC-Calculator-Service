#include "OperationRepository.h"
#include <iostream>

OperationRepository::OperationRepository(const std::string& connection_string)
    : connection_(connection_string)
{
    if (!connection_.is_open()) {
        throw std::runtime_error("Database connection failed!");
    }

    std::cout << "Connected to PostgreSQL successfully\n";
}

void OperationRepository::save_operation(
    const std::string& operation_type,
    const std::vector<double>& numbers, double result
) {
    try {
        pqxx::work txn(connection_);

        pqxx::result r = txn.exec_params(
            "INSERT INTO operations (operation_type,result) VALUES ($1, $2) RETURNING id",
            operation_type,result
        );

        int operation_id = r[0][0].as<int>();

        for (size_t i = 0; i < numbers.size(); ++i) {
            txn.exec_params(
                "INSERT INTO operation_numbers (operation_id, idx, value) "
                "VALUES ($1, $2, $3)",
                operation_id,
                static_cast<int>(i),
                numbers[i]
            );
        }

        txn.commit();
    }
    catch (const std::exception& e) {
        std::cerr << "DB error: " << e.what() << std::endl;
        throw;
    }
}
