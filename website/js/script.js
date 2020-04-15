// WASM call
function WASM_CONVERT_IMAGE(data, informat, outformat) {
    // data: Uint8Array
    // informat/outformat: 0:JPEG, 1:PNG
    ret = Module.convertImage(data, data.length, informat, outformat);
    return ret;
}

// adapted from https://stackoverflow.com/a/45831280
function download(blob, filename) {
    var element = document.createElement('a');
    url = URL.createObjectURL(blob)
    element.setAttribute('href', url);
    element.setAttribute('download', filename);

    element.style.display = 'none';
    document.body.appendChild(element);

    element.click();

    document.body.removeChild(element);
}

function convert() {

    console.log("Convert button pressed!");

    convertButtonElement = document.getElementById('convertButton');

    var selectedFile = document.getElementById('imageInputFile').files[0];

    inputFileExtension = file_extension(selectedFile.name);
    inputImageFormatEnum = imagetype_enum_from_filename(selectedFile.name);

    var outFiletypeElement = document.getElementById('inlineFormCustomSelectPref');
    var outputImageFormatEnum = parseInt(outFiletypeElement.options[outFiletypeElement.selectedIndex].value);
    var outputFileExtension = outFiletypeElement.options[outFiletypeElement.selectedIndex].text.toLowerCase();

    console.log("Output image format: " + outputFileExtension);

    if (selectedFile === undefined) {
        alert("Please select your file first!");
        return;
    } else {

        convertButtonElement.innerHTML = 'Converting...';

        console.log("Selected file:");
        console.log(selectedFile);

        fileData = new Blob([selectedFile]);

        // Pass getBuffer to promise.
        var promise = new Promise(getBuffer);

        // Wait for promise to be resolved, or log error.
        promise.then(function (bytesArr) {

            // Here you can pass the bytes to another function.

            console.log("Running WASM logic (" + inputFileExtension + " -> " + outputFileExtension + ")");
            retBytes = WASM_CONVERT_IMAGE(bytesArr, inputImageFormatEnum, outputImageFormatEnum);
            console.log("Done!");

            output_filename = file_basename(selectedFile.name) + "." + outputFileExtension;

            var blob = new Blob([retBytes], { type: "image/" + outputFileExtension });

            console.log("Showing SaveAs dialog to the user...");
            download(blob, output_filename);

            convertButtonElement.innerHTML = "Convert";

        }).catch(function (err) {
            console.log(err);
            alert(":( Error occured, please reload and try again.");
            convertButtonElement.innerHTML = "Convert";
        });

        console.log("Done!")
    }
}

// returns a byte array of file contents
function getBuffer(resolve) {
    var reader = new FileReader();
    reader.readAsArrayBuffer(fileData);
    reader.onload = function () {
        var arrayBuffer = reader.result
        var bytes = new Uint8Array(arrayBuffer);
        resolve(bytes);
    }
}

// sets the input file field to selected file name
function updateInputField() {
    inputElem = document.getElementById('imageInputFile');
    selectedFile = inputElem.files[0]

    fileNameField = document.getElementById("fileNameField")
    fileNameField.innerHTML = selectedFile.name;
}