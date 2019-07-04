import QtQuick 2.0
import QtWebKit 3.0
import com.syberos.basewidgets 2.0
import QtWebKit.experimental 1.0

CPageStackWindow {
    initialPage:CPage{
        width:parent.width
        height:parent.height

        contentAreaItem: Item{


            WebView{
                id: webview
                focus: true
                width: parent.width
                height: parent.height
                anchors.top: parent.top
                anchors.bottom: parent.bottom

                url: "file://" + helper.getWebRootPath() + "/index.html"

                experimental.preferences.navigatorQtObjectEnabled: true

                experimental.onMessageReceived: {

                    console.log(">>>>> ", "WebView received Message: ", message.data, "\r\n")

                    var model = JSON.parse(message.data);

//                    var func = eval('(' + model.module + '.' + model.method + ')');
//                    console.log('### ', func, '\r\n');
//                    for(var i in Qt){
//                        console.log('---- ', i, ' = ', Qt[i], '\r\n');
//                    }

                    console.log('@@@  ', global.getHelper().getWebRootPath(), '\r\n');

                    var moduleObj = global[model.module]();
                    var func = moduleObj[model.method];

                    var result;
                    if(model.args){
                        //TODO
                        console.log('@@@ ', model.args, '\r\n');
                        func(model.args[0]);

                    }else{
                        result = func();
                    }

                    console.log(func, '\r\n');



//                    experimental.postMessage();

//                    var result = {
//                        id: data.id,
//                        text: data.text + ' done! \r\n' + helper.getDataRootPath(),
//                        newMessage: 'Is ok!'
//                    }

//                    var rs = JSON.stringify(result);
//                    console.log('>>>>> ', 'Send to html: ', rs);

//                    experimental.postMessage(rs);
                }

                Component.onCompleted:{
                    console.log("Component.onCompleted====")
                }

                experimental.alertDialog: CAlertDialog{
                    id: messageDialog
                    canceledOnOutareaClicked: false
                    messageText: model.message
                    onAccepted:{
                        model.accept()
                    }

                    Component.onCompleted:{
                        show()
                    }
                }
            }
        }


    }
}
