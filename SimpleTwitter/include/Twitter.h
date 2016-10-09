#pragma once
#include <vector>

class User;

class Twitter {
public:

    Twitter();

    /** Compose a new tweet.
     */
    void postTweet(int userId, int tweetId);

    /** Retrieve the 10 most recent tweet ids in the user's news feed.
     */
    std::vector<int> getNewsFeed(int userId);

    /** Follower follows a followee. If the operation is invalid, it should be a no-op.
     */
    void follow(int followerId, int followeeId);

    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op.
    */
    void unfollow(int followerId, int followeeId);

private:

    std::vector<User> mUsers;
    int mTime;
};