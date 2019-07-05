import QtQuick 2.0
import QtWebKit 3.0
import com.syberos.basewidgets 2.0
import QtWebKit.experimental 1.0


CPageStackWindow {
    initialPage:CPage{
        id: root
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

                Component.onCompleted: {
                    global.modelMap = {};
                    console.log('@@@ completed init modelMap ', JSON.stringify(global.modelMap));
                }

                experimental.preferences.navigatorQtObjectEnabled: true

                experimental.onMessageReceived: {

                    console.log(">>>>> ", "WebView received Message: ", message.data, "\r\n")

                    var model = JSON.parse(message.data);

                    console.log('@@@  ', global.getHelper().getWebRootPath(), '\r\n');

                    var moduleObj = global[model.module]();
                    var func = moduleObj[model.method];

                    var result;
                    if(model.args){
                        //TODO
                        console.log('@@@ ', model.args, '\r\n');
                        func(model.id, model.args[0]);

                    }else{
                        result = func();
                    }
                    global.modelMap[model.id] = model;

                    console.log('@@@ function: ', func, '\r\n');



//                    experimental.postMessage();

//                    var result = {
//                        id: data.id,
//                        text: data.text + ' done! \r\n' + helper.getDataRootPath(),
//                        newMessage: 'Is ok!'
//                    }

//                    var rs = JSON.stringify(result);
//                    console.log('>>>>> ', 'Send to html: ', rs);


                }

                Connections {
                    target: global
                    onSuccess: {
                        var model = global.modelMap[id];
                        if(model){
                            delete global.modelMap[id];
                        }

                        console.log('@@@ id: ', id, ' json: ', json, ' model: ', JSON.stringify(model));

                        var resultJSON = JSON.parse(json);
                        //{
                        //    id: number,
                        //    exception: string,
                        //    result: object
                        //}
                        var result = {
                            'id': id,
                            'result': resultJSON
                        }
                        webview.experimental.postMessage(JSON.stringify(result));
                    }
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
