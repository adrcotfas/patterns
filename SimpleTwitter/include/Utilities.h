#pragma once

#include "User.h"

struct FoundUser {
	explicit FoundUser(int userId)
		: mId(userId) {}

	inline bool operator()(User user) {
        return user.getUserId() == mId;
	}
private:
	int mId;
};
