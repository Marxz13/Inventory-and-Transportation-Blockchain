#ifndef BLOCK_H
#define BLOCK_H

#include <string>

// Enumeration for different stages of product lifecycle
enum Stage {
    Manufacturing = 1,
    QualityAssurance,
    Packaging,
    Warehousing,
    Transportation,
    RetailShelving,
};

class Block {
private:
    int id; // Unique block ID
    std::string current_hash, previous_hash, timestamp, info; // Block data

public:
    // Constructors
    Block() = default;
    // Optionally, add constructors that initialize the block

    // Getters
    int getId() const { return id; }
    std::string getCurrentHash() const { return current_hash; }
    std::string getPreviousHash() const { return previous_hash; }
    std::string getTimestamp() const { return timestamp; }
    std::string getInfo() const { return info; }

    // Setters
    void setId(int newId) { id = newId; }
    void setCurrentHash(const std::string& newHash) { current_hash = newHash; }
    void setPreviousHash(const std::string& newHash) { previous_hash = newHash; }
    void setTimestamp(const std::string& newTimestamp) { timestamp = newTimestamp; }
    void setInfo(const std::string& newInfo) { info = newInfo; }
};

#endif // BLOCK_H
