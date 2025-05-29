#include "UserAuth.h"
#include <bsoncxx/builder/stream/document.hpp>

UserAuth::UserAuth(mongocxx::database &db) : usersCollection(db["users"]) {}

bool UserAuth::registerUser(const std::string &username, const std::string &password) {
    bsoncxx::builder::stream::document document{};
    document << "username" << username << "password" << password;
    usersCollection.insert_one(document.view());
    return true;
}

bool UserAuth::loginUser(const std::string &username, const std::string &password) {
    auto result = usersCollection.find_one(bsoncxx::builder::stream::document{} << "username" << username << "password" << password << bsoncxx::builder::stream::finalize);
    return static_cast<bool>(result);
}
