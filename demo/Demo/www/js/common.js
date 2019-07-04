//request model:
//{
//    id: number,
//    args: list,
//    callback: function
//}

//request message:
//{
//    id: number,
//    args: list,
//}

//response model:
//{
//    id: number,
//    exception: string,
//    result: object
//}



var common = {

    _modelList: {},

    _model: {
      create: function(module, method, args, callback){
          if(!(args instanceof Array)){
              args = [args];
          }
          var m = {
              'id': Math.random(),
              'module': module,
              'method': method,
              'args': args,
              'callback': callback
          };
          common._modelList[m.id] = m;
          return m;
      }
    },

    _postMessage: function(module, method, args, callback){
        var model = common._model.create(module, method, args, callback);

        var msg = {
            id: model.id,
            module: model.module,
            method: model.method,
            args: model.args
        }
        navigator.qt.postMessage(JSON.stringify(msg));
    },

    _onMessage: function(msg){
        var data = msg.data;
        if(data){
            var resultJSON = JSON.parse(data);
            var model = common._modeList[resultJSON.id];
            if(model){
                delete common._modeList[resultJSON.id];
                model.callback.call(resultJSON.result);
            }
        }
    },

    init: function(){
        navigator.qt.onmessage = common._onMessage;
    },


    downloadFile: function(url, pathCallback){
        common._postMessage('getHelper', 'downloadFile', url, pathCallback);
    }
}
