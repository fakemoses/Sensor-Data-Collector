#include "DataRecorder.h"

namespace DataRecord
{
    DataRecorder::DataRecorder(const std::string &filename) : filename(filename) {}

    /// @brief Append data to the named file. Create file if absent
    /// @param data
    void DataRecorder::appendToFile(const std::string &data)
    {
        //TODO: Bad ending of the data -> ascii 0x7f in the end of the line!
        std::string finalData = data + ","+ getCurrentTime();
        std::ofstream file(filename, std::ios_base::app); // Open file in append mode
        if (file.is_open())
        {
            file << finalData << std::endl; // Append data to file
            std::cout << "Data appended to file successfully." << std::endl;
        }
        else
        {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }
    }

    /// @brief get current time in the format of HH:MM:SS
    /// @return 
    std::string DataRecorder::getCurrentTime()
    {
        // Get the current time
        std::time_t now = std::time(nullptr);
        std::tm ltime = *std::localtime(&now);

        // Use std::put_time to format the time as HH:MM:SS
        std::ostringstream oss;
        oss << std::put_time(&ltime, "%H:%M:%S");

        // Retrieve the formatted time as a std::string
        std::string formattedTime = oss.str();

        return formattedTime;
    }

} // namespace DataRecord
