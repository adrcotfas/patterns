/**
 * source: https://leetcode.com/problems/design-twitter/
 *
 * Design a simplified version of Twitter where users can post tweets,
 * follow/unfollow another user and is able to see the 10 most recent tweets
 * in the user's news feed. 
 *
 * Your design should support the following methods:
 *
 *     - postTweet(userId, tweetId): Compose a new tweet.
 *     - getNewsFeed(userId): Retrieve the 10 most recent tweet ids in the user's news feed. 
 *       Each item in the news feed must be posted by users who the user followed or by the user herself.
 *       Tweets must be ordered from most recent to least recent.
 *     - follow(followerId, followeeId): Follower follows a followee.
 *     - unfollow(followerId, followeeId): Follower unfollows a followee.
 */

#include <memory>
#include <algorithm>
#include <iostream>
#include "Twitter.h"
#include "User.h"
#include "Utilities.h"

Twitter::Twitter()
	    : mUsers()
	    , mTime(0) {
}

void Twitter::postTweet(int userId, int tweetId) {

	auto user = std::find_if(mUsers.begin(), mUsers.end(), FoundUser(userId));
	if (user != std::end(mUsers)) {
		user->postTweet(tweetId, ++mTime);

	}
	else {
		mUsers.push_back(User(userId, tweetId, ++mTime));
	}
}

std::vector<int> Twitter::getNewsFeed(int userId) {

    std::vector<int> result;
	auto user = std::find_if(mUsers.begin(), mUsers.end(), FoundUser(userId));
	if (user != std::end(mUsers)) {
		result.reserve(user->getFeed().size());
		int idx = 0;
		for (auto iter : user->getFeed()) {
			if (idx < 10) {
				result.push_back(iter.getId());
			}
			else {
				break;
			}
		}
	}
	return result;
}

void Twitter::follow(int followerId, int followeeId) {
	auto follower = std::find_if(mUsers.begin(), mUsers.end(), FoundUser(followerId));
	auto followee = std::find_if(mUsers.begin(), mUsers.end(), FoundUser(followeeId));

	if (follower == mUsers.end()) {
		mUsers.push_back(User(followerId));
	}
	if (followee == mUsers.end()) {
		mUsers.push_back(User(followeeId));
	}

	follower = std::find_if(mUsers.begin(), mUsers.end(), FoundUser(followerId));
	followee = std::find_if(mUsers.begin(), mUsers.end(), FoundUser(followeeId));

	follower->addFollowing(*followee);
	followee->addFollower(*follower);
}

void Twitter::unfollow(int followerId, int followeeId) {
	auto follower = std::find_if(mUsers.begin(), mUsers.end(), FoundUser(followerId));
	auto followee = std::find_if(mUsers.begin(), mUsers.end(), FoundUser(followeeId));

	if (follower != mUsers.end() && followee != mUsers.end()) {
		follower->removeFollowing(*followee);
		followee->removeFollower(*follower);
	}
}

int main()
{
	Twitter twitter;
	// User 1 posts a new tweet (id = 5).
	twitter.postTweet(1, 5);
	// User 1's news feed should return a list with 1 tweet id -> [5].
	std::vector<int> nF0 = twitter.getNewsFeed(1);
	// User 1 follows user 2.
	twitter.follow(1, 2);
	// User 2 posts a new tweet (id = 6).
	twitter.postTweet(2, 6);
	// User 1's news feed should return a list with 2 tweet ids -> [6, 5].
	// Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
	std::vector<int> nF1 = twitter.getNewsFeed(1);
	// User 1 unfollows user 2.
	twitter.unfollow(1, 2);
	// User 1's news feed should return a list with 1 tweet id -> [5],
	// since user 1 is no longer following user 2.
	std::vector<int> nF = twitter.getNewsFeed(1);
    return 0;
}