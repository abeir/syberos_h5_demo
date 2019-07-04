#include "download.h"
#include "helper.h"
#include "httpclient.h"
#include <QObject>

Download::Download(QObject *parent) : QObject(parent)
{

}

QString Download::getDownloadDir(){
    return Helper::instance()->getDataRootPath();
}

/**
 * @brief cancel 取消下载
 * @param downloadID 要取消下载的任务Id
 * @return 成功则无返回。
 *      失败则返回错误码。
 */
long Download::cancel(long downloadID){
    return downloadID;
}
/**
 * @brief getFileInfos 获取所有下载文件信息
 * @return 成功则返回FileInfo数组。
          失败则返回错误码。
 */
QList<FileInfo> Download::getFileInfos(){
    QList<FileInfo> list;
    return list;
}
/**
 * @brief pause 暂停下载 (暂不支持)
 * @param downloadID 要暂停的下载任务Id
 * @return 成功则无返回。
                  失败则返回错误码。
 */
long Download::pause(long downloadID){
    return downloadID;
}
/**
 * @brief removeFileInfos 移除下载文件记录。
 * @param downloadIDs 整型数组, 要移除下载文件的Id。
 * @return 成功则无返回。
                  失败则返回错误码。
 */
long Download::removeFileInfos(long downloadIDs[]){
    return downloadIDs[0];
}
/**
 * @brief restart 重新下载。
 * @param downloadID 要重新下载的任务Id。
 * @return 成功则重新下载后的新任务Id。
            失败则返回错误码。
 */
long Download::restart(long downloadID){
    return downloadID;
}
/**
 * @brief resume 恢复下载 (暂不支持)。
 * @param downloadID 要恢复的下载任务Id
 * @return 成功则无返回。
                  失败则返回错误码。
 */
long Download::resume(long downloadID){
    return downloadID;
}
/**
 * @brief start 开始下载
 * @param url 下载文件地址
 * @param name 保存的文件名
 * @return 成功则下载任务Id。
                 失败则返回错误码。
 */
long Download::start(QString url, QString name){
    taskId += 1;
    DownloadTask task;
    task.url = url;
    task.name = name;

    QNetworkReply* reply = HttpClient::instance()->get(url);
    task.reply = reply;

    downloadTasks[taskId] = task;
    return taskId;
}


