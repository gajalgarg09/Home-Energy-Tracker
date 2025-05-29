#ifndef USER_AUTH_H
#define USER_AUTH_H

#include <mongocxx/client.hpp>
#include <string>

class UserAuth {
public:
    UserAuth(mongocxx::database &db);
    bool registerUser(const std::string &username, const std::string &password);
    bool loginUser(const std::string &username, const std::string &password);

private:
    mongocxx::collection usersCollection;
};

#endif
