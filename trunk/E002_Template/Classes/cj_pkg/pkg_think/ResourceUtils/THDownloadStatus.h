//
//  THDownloadStatus.h
//  Think
//
//  Created by pureye4u BX on 12. 9. 26..
//  Copyright CJ Educations 2012. All rights reserved.
//

#ifndef Think_THDownloadStatus_h
#define Think_THDownloadStatus_h

typedef enum
{
	THDownloadStatusNone,
	THDownloadStatusPrepareDownload,
	THDownloadStatusDownloading,
	THDownloadStatusWaitDownloading,
	THDownloadStatusInstalling,
	THDownloadStatusDownloadComplete,
	THDownloadStatusNetworkDisconnected,
	THDownloadStatusNetworkError,
	THDownloadStatusNetworkTryConnect,
    THDownloadStatusWifiStrength,
	THDownloadStatusSpaceError,
	THDownloadStatusInstallError,
}THDownloadStatus;

#endif
