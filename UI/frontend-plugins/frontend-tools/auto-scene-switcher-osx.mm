#import <CoreGraphics/CGWindow.h>
#import <Cocoa/Cocoa.h>
#include <util/platform.h>
#include "auto-scene-switcher.hpp"

using namespace std;

#define WINDOW_NAME   ((__bridge NSString*)kCGWindowName)
#define WINDOW_LAYER  ((__bridge NSNumber*)kCGWindowLayer)
#define WINDOW_NUMBER ((__bridge NSString*)kCGWindowNumber)
#define OWNER_NAME    ((__bridge NSString*)kCGWindowOwnerName)
#define OWNER_PID     ((__bridge NSNumber*)kCGWindowOwnerPID)

static NSComparator win_info_cmp = ^(NSDictionary *o1, NSDictionary *o2)
{
	NSComparisonResult res = [o1[OWNER_NAME] compare:o2[OWNER_NAME]];
	if (res != NSOrderedSame)
		return res;

	res = [o1[OWNER_PID] compare:o2[OWNER_PID]];
	if (res != NSOrderedSame)
		return res;

	res = [o1[WINDOW_NAME] compare:o2[WINDOW_NAME]];
	if (res != NSOrderedSame)
		return res;

	return [o1[WINDOW_NUMBER] compare:o2[WINDOW_NUMBER]];
};

static NSArray *enumerate_windows(void)
{
	NSArray *arr = (__bridge NSArray*)CGWindowListCopyWindowInfo(
			kCGWindowListOptionOnScreenOnly,
			kCGNullWindowID);

	return [arr sortedArrayUsingComparator:win_info_cmp];
}

void GetWindowList(vector<string> &windows)
{
	windows.resize(0);

	@autoreleasepool {
		for (NSDictionary *dict in enumerate_windows()) {
			NSString *name = dict[WINDOW_NAME];
			windows.emplace_back(name.UTF8String);
		}
	}
}

void GetCurrentWindowTitle(string &title)
{
#if 0
	const char *cmd = "osascript "
		"-e 'global frontApp, frontAppName, windowTitle' "
		"-e 'set windowTitle to \"\"' "
		"-e 'tell application \"System Events\"' "
		"-e 'set frontApp to first application process whose "
			"frontmost is true' "
		"-e 'set frontAppName to name of frontApp' "
		"-e 'tell process frontAppName' "
		"-e 'tell (1st window whose value of attribute "
			"\"AXMain\" is true)' "
		"-e 'set windowTitle to value of attribute \"AXTitle\"' "
		"-e 'end tell' "
		"-e 'end tell' "
		"-e 'end tell' "
		"-e 'return windowTitle' ";

	char buffer[1024];
	FILE *f = popen(cmd.c_str(), "r");
	buffer[0] = 0;
	fgets(buffer, 1023, f);
	pclose(f);

	title = buffer;

	/* popen fgets will include a newline at the end of the string */
	windowname.pop_back();
#else
	title.resize(0);

	@autoreleasepool {
		for (NSDictionary *dict in enumerate_windows()) {
			NSNumber *layer = dict[WINDOW_LAYER];

			if ([layer isEqualToNumber:@0]) {
				NSString *name = dict[WINDOW_NAME];
				title = name.UTF8String;
				break;
			}
		}
	}
#endif
}
