#include "data_recorder.h"

namespace DataRecord
{
    DataRecorder::DataRecorder(const std::string& filename):filename(filename){}
    
    /// @brief Append data to the named file. Create file if absent
    /// @param data 
    void DataRecorder::appendToFile(const std::string& data) {
        std::ofstream file(filename, std::ios_base::app); // Open file in append mode
        if (file.is_open()) {
            file << data << ""; // Append data to file
            std::cout << "Data appended to file successfully." << std::endl;
        } else {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }


} // namespace DataRecord

