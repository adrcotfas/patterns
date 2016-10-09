#include <algorithm>
#include "User.h"
#include "Utilities.h"

class Tweet;

User::User(int userId)
	: mId(userId)
	, mTweets()
	, mFeed()
	, mFollowers()
	, mFollowing() {
}

User::User(int userId, int tweetId, int time)
	: mId(userId)
	, mTweets()
	, mFeed()
	, mFollowers()
	, mFollowing() {

	mTweets.insert(Tweet(userId, tweetId, time));
	updateFeed();
}

int User::getUserId() const {
	return mId;
}

std::set<Tweet, Chronologcical> User::getTweets() {
	return mTweets;
}

std::set<Tweet, Chronologcical> User::getFeed() {
	return mFeed;
}

void User::postTweet(int tweetId, int time) {
	mTweets.insert(Tweet(mId, tweetId, time));
	updateFeed();
	notifyFollowers();
}

void User::addFollower(User& user) {
	mFollowers.push_back(&user);
	notifyFollowers();
}

void User::addFollowing(User& user) {
	mFollowing.push_back(&user);
	updateFeed();
}

void User::removeFollower(User& user) {

	auto exFollower = std::find(mFollowers.begin(), mFollowers.end(), &user);
	if (exFollower != mFollowers.end()) {
		mFollowers.erase(exFollower);
	}
	notifyFollowers();
}

void User::removeFollowing(User& user) {
	auto exFollowing = std::find(mFollowing.begin(), mFollowing.end(), &user);
	if (exFollowing != mFollowing.end()) {
		mFollowing.erase(exFollowing);
	}
	updateFeed();
}

void User::notifyFollowers() {
	for (auto iter = mFollowers.begin(); iter != mFollowers.end(); ++iter) {
		(*iter)->updateFeed();
	}
}

void User::updateFeed() {
	mFeed.clear();
	for (auto iter : mFollowing) {
		for (auto jter : iter->getTweets()) {
			mFeed.insert(jter);
		}
	}
	mFeed.insert(mTweets.begin(), mTweets.end());
}
