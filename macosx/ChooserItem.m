
/**
 * OpenEmulator
 * Mac OS X Chooser Item
 * (C) 2009 by Marc S. Ressl (mressl@umich.edu)
 * Released under the GPL
 *
 * Implements an chooser item for template and device choosing.
 */

#import "ChooserItem.h"

@implementation ChooserItem

- (id)initWithItem:(NSString *) theItemPath
			 label:(NSString *) theLabel
		 imagePath:(NSString *) theImagePath
	   description:(NSString *) theDescription
{
	if (self = [super init])
	{
		if (theItemPath)
			itemPath = [theItemPath retain];
		if (theLabel)
			label = [theLabel retain];
		if (theImagePath)
			imagePath = [theImagePath retain];
		if (theDescription)
			description = [theDescription retain];
	}
	
	return self;
}

- (void)dealloc
{
    [itemPath release];
    [label release];
    [imagePath release];
    [description release];
	
    [super dealloc];
}

- (NSString *) imageRepresentationType
{
	return IKImageBrowserPathRepresentationType;
}

- (id) imageRepresentation
{
	return imagePath;
}

- (NSString *) imageTitle
{
	return label;
}

- (NSString *) imageSubtitle
{
	return description;
}

- (NSString *) imageUID
{
    return [[itemPath retain] autorelease];
}

- (NSString *) itemPath
{
	return [[itemPath retain] autorelease];
}

@end