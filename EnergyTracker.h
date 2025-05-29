#ifndef ENERGY_TRACKER_H
#define ENERGY_TRACKER_H

#include <mongocxx/client.hpp>
#include <string>

class EnergyTracker {
public:
    EnergyTracker();
    void addData(const std::string &date, const std::string &time, const std::string &appliance, double usage);
    void printPeakUsageTime(const std::string &appliance);
    double forecastUsage(const std::string &appliance, int days);
    void printUsageInRange(const std::string &appliance, const std::string &startDate, const std::string &endDate);

private:
    mongocxx::client client;
    mongocxx::collection collection;
    double getApplianceAverage(const std::string &appliance);
};

#endif
