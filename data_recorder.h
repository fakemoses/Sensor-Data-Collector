#ifndef DATA_RECORDER_H
#define DATA_RECORDER_H

#include <iostream>
#include <fstream>

namespace DataRecord
{
    class DataRecorder
    {
    private:
        std::string filename;

    public:
        DataRecorder(const std::string &filename);
        void appendToFile(const std::string &data);
    };

} // namespace DataRecord

#endif