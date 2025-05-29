#include "EnergyTracker.h"
#include <iostream>
#include <bsoncxx/builder/stream/document.hpp>

EnergyTracker::EnergyTracker() : client(mongocxx::uri{}), collection(client["energyDB"]["energyUsage"]) {}

void EnergyTracker::addData(const std::string &date, const std::string &time, const std::string &appliance, double usage) {
    bsoncxx::builder::stream::document document{};
    document << "date" << date << "time" << time << "appliance" << appliance << "usage" << usage;
    collection.insert_one(document.view());
    std::cout << "Data added.\n";
}

void EnergyTracker::printPeakUsageTime(const std::string &appliance) {
    mongocxx::cursor cursor = collection.find(bsoncxx::builder::stream::document{} << "appliance" << appliance << bsoncxx::builder::stream::finalize);
    std::string peakTime;
    double maxUsage = 0;
    for (const auto &doc : cursor) {
        std::string time = doc["time"].get_utf8().value.to_string();
        double usage = doc["usage"].get_double().value;
        if (usage > maxUsage) {
            maxUsage = usage;
            peakTime = time;
        }
    }
    std::cout << "Peak usage time for " << appliance << " is " << peakTime << " with " << maxUsage << " kWh\n";
}

double EnergyTracker::forecastUsage(const std::string &appliance, int days) {
    double avgDailyUsage = getApplianceAverage(appliance);
    return avgDailyUsage * days;
}

void EnergyTracker::printUsageInRange(const std::string &appliance, const std::string &startDate, const std::string &endDate) {
    mongocxx::cursor cursor = collection.find(bsoncxx::builder::stream::document{}
                                              << "appliance" << appliance
                                              << "date" << bsoncxx::builder::stream::open_document
                                              << "$gte" << startDate << "$lte" << endDate
                                              << bsoncxx::builder::stream::close_document
                                              << bsoncxx::builder::stream::finalize);
    double totalUsage = 0;
    for (const auto &doc : cursor) {
        totalUsage += doc["usage"].get_double().value;
    }
    std::cout << "Total usage for " << appliance << " from " << startDate << " to " << endDate << " is " << totalUsage << " kWh\n";
}

double EnergyTracker::getApplianceAverage(const std::string &appliance) {
    mongocxx::cursor cursor = collection.find(bsoncxx::builder::stream::document{} << "appliance" << appliance << bsoncxx::builder::stream::finalize);
    double totalUsage = 0;
    int count = 0;
    for (const auto &doc : cursor) {
        totalUsage += doc["usage"].get_double().value;
        count++;
    }
    return count ? totalUsage / count : 0;
}
