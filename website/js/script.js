// define functions from WASM
wasm_int_sqrt = Module.cwrap('int_sqrt', 'number', ['number'])
wasm_convert_image = Module.cwrap('convert_image', 'number', ['number', 'number', 'number', 'number'])

function _arrayToHeap(typedArray){
    var numBytes = typedArray.length * typedArray.BYTES_PER_ELEMENT;
    var ptr = Module._malloc(numBytes);
    var heapBytes = new Uint8Array(Module.HEAPU8.buffer, ptr, numBytes);
    heapBytes.set(typedArray);
    return heapBytes;
}

function _freeArray(heapBytes){
    Module._free(heapBytes.byteOffset);
}

function WASM_CONVERT_IMAGE(data){
    var heapBytes = _arrayToHeap(data);
    var ret = wasm_convert_image(heapBytes.byteOffset, data.length, 0, 1);
    _freeArray(heapBytes);
    return ret;
}

function convert(){
    console.log("Hello World!");
    selectedFile = document.getElementById('imageInputFile').files[0];
    
    if(selectedFile === undefined){
        alert("Please select your file first!");
    }else{
        console.log(selectedFile)

        fileData = new Blob([selectedFile]);
        // Pass getBuffer to promise.
        var promise = new Promise(getBuffer);
        // Wait for promise to be resolved, or log error.
        promise.then(function(data) {
            // Here you can pass the bytes to another function.
            console.log(data);

            ret = WASM_CONVERT_IMAGE(data)
            console.log(ret)

        }).catch(function(err) {
            console.log('Error: ',err);
        });

        var blob = new Blob(["Hello, world!"], {type: "text/plain;charset=utf-8"});
        saveAs(blob, "hello world.txt");  
    }
}

function getBuffer(resolve) {
    var reader = new FileReader();
    reader.readAsArrayBuffer(fileData);
    reader.onload = function() {
      var arrayBuffer = reader.result
      var bytes = new Uint8Array(arrayBuffer);
      resolve(bytes);
    }
  }

function updateInput(){
    console.log("I was called!");
    inputElem = document.getElementById('imageInputFile');
    selectedFile = inputElem.files[0]

    fileNameField = document.getElementById("fileNameField")
    fileNameField.innerHTML = selectedFile.name;
}