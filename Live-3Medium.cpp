#define mediumNameMaxLen 30

class Medium {
public:
	static Boolean lookupByName(UsageEnvironment& env, char const* mediumName, Medium*& resultMedium);
	static void close(UsageEnvironment& env, char const* mediumName);
	static void close(Medium* medium); // alternative close() method using ptrs
	// (has no effect if medium == NULL)

	UsageEnvironment& envir() const { return fEnviron; }

	char const* name() const { return fMediumName; }

	// Test for specific types of media:
	virtual Boolean isSource() const;
	virtual Boolean isSink() const;
	virtual Boolean isRTCPInstance() const;
	virtual Boolean isRTSPClient() const;
	virtual Boolean isRTSPServer() const;
	virtual Boolean isMediaSession() const;
	virtual Boolean isServerMediaSession() const;

protected:
	friend class MediaLookupTable;
	Medium(class UsageEnvironment& env); // abstract base class
	virtual ~Medium(); // instances are deleted using close() only

	TaskToken& nextTask() {
		return fNextTask;
	}

private:
	UsageEnvironment& fEnviron;
	char fMediumName[mediumNameMaxLen];
	TaskToken fNextTask;
};