CREATE TABLE operations (
    id SERIAL PRIMARY KEY,
    operation_type VARCHAR(16) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE operation_numbers (
    id SERIAL PRIMARY KEY,
    operation_id INTEGER NOT NULL,
    idx INTEGER NOT NULL,
    value DOUBLE PRECISION NOT NULL,
    CONSTRAINT fk_operation
        FOREIGN KEY (operation_id)
        REFERENCES operations(id)
        ON DELETE CASCADE
);
