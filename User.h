#ifndef USER_H
#define USER_H

using UID = unsigned;

struct UserBase {
    const UID id;
};

class Admin: public UserBase {
public:
    enum Permission {
        Nothing,
        AddAdmin,
        RemoveAdmin
    } permissions;

    Admin(UID uid, Permission perm): UserBase(uid), permissions(perm) {}
};

#endif // !USER_H
