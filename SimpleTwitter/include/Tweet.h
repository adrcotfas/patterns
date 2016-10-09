#pragma once

class Tweet {
public:
	Tweet(int userId, int tweetId, int time)
		: mUserId(userId)
		, mId(tweetId)
		, mTime(time)
	{}

	int getTime() const {
		return mTime;
	}

	int getId() const {
		return mId;
	}

private:
	int mUserId;
	int mId;
	int mTime;
};
