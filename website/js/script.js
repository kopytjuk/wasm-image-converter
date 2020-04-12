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

            // some fancy stuff


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