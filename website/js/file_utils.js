// File name and extension parsing utilities

// from https://stackoverflow.com/a/3820412
function file_basename(str)
{
   var base = new String(str).substring(str.lastIndexOf('/') + 1); 
    if(base.lastIndexOf(".") != -1)       
        base = base.substring(0, base.lastIndexOf("."));
   return base;
}

function file_extension(str)
{
   return str.split('.').pop().toLowerCase();
}

function imagetype_enum_from_filename(fn){
   ext = file_extension(fn);
   var inputImageFormatEnum = null;
   if (ext == "jpg" | ext == "jpeg"){
      inputImageFormatEnum = 0;
   } else if (ext == "png"){
      inputImageFormatEnum = 1;
   }

   return inputImageFormatEnum;
}