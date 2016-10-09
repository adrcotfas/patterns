#pragma once
#include <memory>
#include <set>
#include <vector>
#include "Tweet.h"

struct Chronologcical {
	inline bool operator()(const Tweet& lhs, const Tweet& rhs) {
		return (lhs.getTime() < rhs.getTime());
	}
};

class User {
public:

	User(int userId);
	User(int userId, int tweetId, int time);

	int getUserId() const;

	std::set<Tweet, Chronologcical> getTweets();
	std::set<Tweet, Chronologcical> getFeed();

	void postTweet(int tweetId, int time);
	void addFollower(User& user);
	void addFollowing(User& user);
	void removeFollower(User& user);
	void removeFollowing(User& user);
	void notifyFollowers();
	void updateFeed();

private:
	int mId;
	std::set<Tweet, Chronologcical> mTweets;
	std::set<Tweet, Chronologcical> mFeed;
	std::vector<User* > mFollowers;
	std::vector<User* > mFollowing;
};
